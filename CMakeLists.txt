CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

# project
SET(project_prefix "capi")
SET(prefix "/usr")
SET(libdir ${LIB_INSTALL_DIR})
SET(version "0.0.1")
SET(maintainer "Jihoon Jung <jh8801.jung@samsung.com>")
SET(description "A MTP library in Tizen Native API")
SET(service "network")
SET(submodule "mtp")

# for package file
SET(dependents "dlog glib-2.0 gio-2.0 capi-base-common gio-unix-2.0 sqlite3 capi-system-info")
SET(pc_dependents "capi-base-common")

SET(fw_name "${project_prefix}-${service}-${submodule}")

FIND_PROGRAM(GDBUS_CODEGEN NAMES gdbus-codegen)
EXEC_PROGRAM(${GDBUS_CODEGEN} ARGS
                " \\
                --generate-c-code ${CMAKE_CURRENT_SOURCE_DIR}/src/mtp_gdbuslib \\
                --c-namespace mtp_gdbuslib \\
                --interface-prefix org.tizen.mtp. \\
                ${CMAKE_CURRENT_SOURCE_DIR}/src/mtp_gdbuslib.xml \\
                ")

PROJECT(${fw_name})

SET(CMAKE_INSTALL_PREFIX ${prefix})
SET(PREFIX ${CMAKE_INSTALL_PREFIX})
SET(VERSION ${version})

SET(INC_DIR include)
INCLUDE_DIRECTORIES(${INC_DIR})
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src)

INCLUDE(FindPkgConfig)
pkg_check_modules(${fw_name} REQUIRED ${dependents})
FOREACH(flag ${${fw_name}_CFLAGS})
    SET(EXTRA_CFLAGS "${EXTRA_CFLAGS} ${flag}")
ENDFOREACH(flag)

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${EXTRA_CFLAGS} -fPIC -Wall -Werror")
SET(CMAKE_C_FLAGS_DEBUG "-O0 -g")

ADD_DEFINITIONS("-DPREFIX=\"${CMAKE_INSTALL_PREFIX}\"")
ADD_DEFINITIONS("-DTIZEN_DEBUG")

SET(CMAKE_EXE_LINKER_FLAGS "-Wl,--as-needed -Wl,--rpath=%{_libdir}")

SET(SOURCES src/mtp.c
	    src/mtp_gdbuslib.c
	    src/mtp_gdbus_deviceinfo.c
	    src/mtp_gdbus_manager.c
	    src/mtp_gdbus_storageinfo.c
	    src/mtp_gdbus_objectinfo.c
	    src/mtp_db.c)

ADD_LIBRARY(${fw_name} SHARED ${SOURCES})

TARGET_LINK_LIBRARIES(${fw_name} ${${fw_name}_LDFLAGS})

SET_TARGET_PROPERTIES(${fw_name}
     PROPERTIES
     VERSION ${FULLVER}
     SOVERSION ${MAJORVER}
     CLEAN_DIRECT_OUTPUT 1
)

INSTALL(TARGETS ${fw_name} DESTINATION ${libdir})
INSTALL(
        DIRECTORY ${INC_DIR}/ DESTINATION include
        FILES_MATCHING
        PATTERN "${INC_DIR}/*.h"
        )

SET(PC_NAME ${fw_name})
SET(PC_REQUIRED ${pc_dependents})
SET(PC_LDFLAGS -l${fw_name})

CONFIGURE_FILE(
    ${fw_name}.pc.in
    ${CMAKE_CURRENT_SOURCE_DIR}/${fw_name}.pc
    @ONLY
)
INSTALL(FILES ${CMAKE_CURRENT_SOURCE_DIR}/${fw_name}.pc DESTINATION ${libdir}/pkgconfig)

ADD_SUBDIRECTORY(test)

