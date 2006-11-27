######################################################################
# Automatically generated by qmake (1.07a) Fri Oct 27 13:32:17 2006
######################################################################

TEMPLATE = lib

DESTDIR = ../../lib
TARGET = $$LIB

include(../../common.pri)

CONFIG += qt
CONFIG += staticlib

contains(DEFINES, HAVE_MML) {
  COPASI_LIBS += mml
}
COPASI_LIBS += plotUI
COPASI_LIBS += UI
COPASI_LIBS += wizard


BuildLib.commands = \
  rm -rf $@; \
  $$join(COPASI_LIBS, ".a; $$QMAKE_AR $@ *.o; rm *.o; tar -xzf $$DESTDIR/lib", "tar -xzf $$DESTDIR/lib", ".a; $$QMAKE_AR $@ *.o; rm *.o");
contains(BUILD_OS, Darwin) {
  BuildLib.commands += ranlib -s $@
}
BuildLib.target = $$DESTDIR/$(TARGET)
BuildLib.depends = Makefile $$join(COPASI_LIBS, ".a ../../lib/lib", ../../lib/lib, .a)
QMAKE_EXTRA_UNIX_TARGETS += BuildLib


contains(BUILD_OS, WIN32) {
  OBJECTS += $$join(COPASI_LIBS, ".lib ..\..\lib\", ..\..\lib\, .lib)
}

!contains(BUILD_OS, WIN32) {
  OBJECTS += Makefile
  TARGETDEPS += $$DESTDIR/$(TARGET)
  DESTDIR = .
}
