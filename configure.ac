#
# Copyright 2011 Karolis Petrauskas
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
AC_PREREQ(2.69)
AC_INIT([biosensor], [0.6.10])
AC_CONFIG_AUX_DIR(admin)
AC_CONFIG_SRCDIR([src/README])
AC_CONFIG_HEADERS([ src/libbiosensor-xml/biosensor-xml.hxx src/libbiosensor/biosensor.hxx src/libbiosensor-slv-fd/biosensor-slv-fd.hxx ])
AC_CONFIG_MACRO_DIR([acinclude])
AM_INIT_AUTOMAKE([subdir-objects -Wall])

ASTYLE_OPTS="--style=ansi --options=none"
#CXXFLAGS="-g -O2 -ansi -Wall"


#### Checks for programs.
AM_PROG_AR
AC_PROG_CXX
AC_PROG_LIBTOOL
KP_PROG_XSD

#### Checks for libraries.
#AM_PATH_LOG4CPP(1.0)
#KP_LIB_LOG4CPP
#KP_LIB_LOG4CXX
KP_LIB_XERCESC

#### Checks for header files.
# ...
AX_BOOST_BASE([1.53.0])
AX_BOOST_SYSTEM
AX_BOOST_FILESYSTEM
LIBS="$LIBS $BOOST_SYSTEM_LIB $BOOST_FILESYSTEM_LIB"

#### Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_C_INLINE

#### Checks for library functions.
# ...


#### Check for parameter ROOTNS
AC_ARG_VAR([ROOTNS], [Root namespace for this package (default is "bio").])
test -z "$ROOTNS" && ROOTNS="bio"
AC_MSG_NOTICE([Using root namespace: $ROOTNS])
AC_DEFINE_UNQUOTED([BIO_NS], [$ROOTNS], [Library namespace.])


AC_DEFINE_UNQUOTED([BIO_VERSION], ["$PACKAGE_VERSION"], [A biosensor simulation package version])


AC_SUBST(BIO_NS, [$ROOTNS])
AC_SUBST(BIO_VERSION)
AC_SUBST(ASTYLE_OPTS)
AC_CONFIG_FILES([
    Makefile
    src/Makefile
    src/bio-editor/Makefile
    src/bio-solver/Makefile
    src/bio-output/Makefile
    src/libbiosensor/Makefile
    src/libbiosensor-slv-fd/Makefile
    src/libbiosensor-xml/Makefile
    Doxyfile
])

AC_OUTPUT

