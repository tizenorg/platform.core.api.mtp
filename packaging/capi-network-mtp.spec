Name:       capi-network-mtp
Summary:    A MTP library in Native API
Version:    1.3.0
Release:    1
Group:      Network & Connectivity/Other
License:    Apache-2.0
Source0:    %{name}-%{version}.tar.gz

ExcludeArch: %ix86 x86_64

BuildRequires:  cmake
BuildRequires:  pkgconfig(dlog)
BuildRequires:  pkgconfig(glib-2.0)
BuildRequires:  pkgconfig(gobject-2.0)
BuildRequires:  pkgconfig(capi-base-common)
BuildRequires:  pkgconfig(sqlite3)
BuildRequires:  python
Buildrequires:  python-xml

Requires(post): /sbin/ldconfig
Requires(postun): /sbin/ldconfig

%description

%package devel
Summary:  A MTP library in Native API (Development)
Group:    Network & Connectivity/Other
Requires: %{name} = %{version}-%{release}

%description devel

%prep
%setup -q

%build
MAJORVER=`echo %{version} | awk 'BEGIN {FS="."}{print $1}'`

cmake . -DCMAKE_INSTALL_PREFIX=%{_prefix} \
	-DLIB_INSTALL_DIR=%{_libdir} \
	-DFULLVER=%{version} \
	-DMAJORVER=${MAJORVER}

make %{?jobs:-j%jobs}

%install
rm -rf %{buildroot}
mkdir -p %{buildroot}/usr/share/license/mtp/
cp -af %{_builddir}/%{name}-%{version}/LICENSE.APLv2 %{buildroot}/usr/share/license/mtp/

%make_install

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig


%files
%manifest capi-network-mtp.manifest
%{_libdir}/libcapi-network-mtp.so*
/usr/share/license/mtp/LICENSE.APLv2

%files devel
%{_includedir}/*.h
%{_libdir}/pkgconfig/*.pc
%{_libdir}/libcapi-network-mtp.so
