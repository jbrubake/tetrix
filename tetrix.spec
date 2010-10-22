Name: tetrix
Version: 2.3
Release: 1
URL: http://www.catb.org/~esr/tetrix/
Source0: %{name}-%{version}.tar.gz
License: BSD
Group: Games
Summary: Tetrix (screen mode)
BuildRoot: %{_tmppath}/%{name}-root

%description
A UNIX-hosted, curses-based clone of Tetris.  Probably obsolete
unless you can't use X for some reason.

%prep
%setup -q

%build
make %{?_smp_mflags} tetrix tetrix.6

%install
[ "$RPM_BUILD_ROOT" -a "$RPM_BUILD_ROOT" != / ] && rm -rf "$RPM_BUILD_ROOT"
mkdir -p "$RPM_BUILD_ROOT"%{_bindir}
mkdir -p "$RPM_BUILD_ROOT"%{_mandir}/man6/
cp tetrix "$RPM_BUILD_ROOT"%{_bindir}
cp tetrix.6 "$RPM_BUILD_ROOT"%{_mandir}/man6/

%clean
[ "$RPM_BUILD_ROOT" -a "$RPM_BUILD_ROOT" != / ] && rm -rf "$RPM_BUILD_ROOT"

%files
%doc README COPYING
%defattr(-,root,root,-)
%{_mandir}/man6/tetrix.6*
%{_bindir}/tetrix

%changelog
* Fri Oct 22 2010 Eric S. Raymond <esr@snark.thyrsus.com> 2.3-1
- Polish code for modern C.
- Choose a reasonable default for the intermove pause.

* Mon Dec 29 2003 Eric S. Raymond <esr@snark.thyrsus.com> 2.2-1
- RPMS can now be built by non-root users.

