#############################################################################
# Tano - An Open IP TV Player
# Copyright (C) 2011 Tadej Novak <tadej@tano.si>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>./
#############################################################################

PROJECT(tano)
cmake_minimum_required(VERSION 2.6)

CONFIGURE_FILE(
    "${CMAKE_SOURCE_DIR}/cmake_uninstall.cmake.in"
    "${CMAKE_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

ADD_CUSTOM_TARGET(uninstall
    "${CMAKE_COMMAND}" -P "${CMAKE_BINARY_DIR}/cmake_uninstall.cmake")

set(CMAKE_MODULE_PATH
    ${CMAKE_SOURCE_DIR}/cmake
)

# Set MingW bin dir, if MingW present
IF(MINGW)
    STRING(REGEX REPLACE "([^ ]+)[/\\].*" "\\1" MINGW_BIN_DIR_TMP "${CMAKE_CXX_COMPILER}")
    STRING(REGEX REPLACE "\\\\" "/" MINGW_BIN_DIR "${MINGW_BIN_DIR_TMP}") # Replace back slashes to slashes
ENDIF(MINGW)

# Show all warnings
SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall -W")
SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -W")

SET(CMAKE_VERBOSE_MAKEFILE ON)

# Windows compatibility
IF(MINGW)
    SET(CMAKE_EXE_LINKER_FLAGS "-enable-stdcall-fixup -Wl,-enable-auto-import -Wl,-enable-runtime-pseudo-reloc -Wl,-s -mthreads -Wl -Wl,-subsystem,windows")
ENDIF(MINGW)

# Search for Qt4 and other libraries
SET(QT_MIN_VERSION "4.6.0")

FIND_PACKAGE(Qt4 REQUIRED)
FIND_PACKAGE(LIBVLCQT REQUIRED)

# Set Qt4 bin dir to find QtCore4.dll and other libs to install
STRING(REGEX REPLACE "([^ ]+)[/\\].*" "\\1" QT_BIN_DIR_TMP "${QT_QMAKE_EXECUTABLE}")
STRING(REGEX REPLACE "\\\\" "/" QT_BIN_DIR "${QT_BIN_DIR_TMP}")  # Replace back slashes to slashes

# Set default install path:
# In *nix environments this is /usr/local 
# Under M$ Windows this is C:\Program files\Tano
# WARNING: Leading slash should be added - this is for easier concatenation of the strings due to slash/backslash issues
IF(MINGW)
    IF (NOT CMAKE_INSTALL_PREFIX)
        SET(CMAKE_INSTALL_PREFIX "C:/Program files/Tano")
    ENDIF (NOT CMAKE_INSTALL_PREFIX)
    SET(TANO_INSTALL_DATA_DIR "")
    SET(TANO_INSTALL_PLUGIN_DIR "plugins")
    SET(TANO_INSTALL_BIN_DIR "")
ELSE(MINGW)
    IF (NOT CMAKE_INSTALL_PREFIX)
        SET(CMAKE_INSTALL_PREFIX "/usr/local")
    ENDIF (NOT CMAKE_INSTALL_PREFIX)
    SET(TANO_INSTALL_DATA_DIR "share/tano")
    SET(TANO_INSTALL_PLUGIN_DIR "lib/tano")
    SET(TANO_INSTALL_BIN_DIR "bin")
ENDIF(MINGW)


###########
# Version #
###########
# Tano version number.
FILE(READ VERSION TANO_VERSION)
STRING(REGEX REPLACE "\n" "" TANO_VERSION "${TANO_VERSION}") # get rid of the newline at the end
MESSAGE("You are compiling Tano ${TANO_VERSION}")

# System Information
SITE_NAME(HOSTNAME)
SET(SYSNAME ${CMAKE_SYSTEM}-${CMAKE_SYSTEM_PROCESSOR})

# Find Git Version Patch
FIND_PROGRAM(GIT git)
IF(GIT)
    EXECUTE_PROCESS(
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMAND ${GIT} rev-parse --short HEAD
        OUTPUT_VARIABLE GIT_OUT OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    SET(PROJECT_VERSION_PATCH "${GIT_OUT}-git")
    MESSAGE(STATUS "Git Version Patch: ${GIT_OUT}")
ELSE(GIT)
    IF(GITBUILD)
        SET(PROJECT_VERSION_PATCH "${GITBUILD}-git")
    ELSE(GITBUILD)
        SET(GIT_OUT 0)
    ENDIF(GITBUILD)
ENDIF(GIT)

#################
# Configuration #
#################
OPTION(EDITOR_WITH_VLCQT "Compile Tano Editor with VLC-Qt" OFF)
MESSAGE("Compile Tano Editor with VLC-Qt: ${EDITOR_WITH_VLCQT}")
OPTION(REFRESH_TRANSLATIONS "Refresh translations on compile" OFF)
MESSAGE("Refresh translations on compile: ${REFRESH_TRANSLATIONS}")

IF(EDITOR_WITH_VLCQT)
    SET(EDITOR_VLCQT 1)
ELSE(EDITOR_WITH_VLCQT)
    SET(EDITOR_VLCQT 0)
ENDIF(EDITOR_WITH_VLCQT)

SET(QT_SINGLE_APPLICATION "${CMAKE_BINARY_DIR}/lib/qtsingleapplication/libqtsingleapplication.a")

###################
# Compile and set #
###################
ADD_SUBDIRECTORY(lib)
ADD_SUBDIRECTORY(lang)
ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(daemon)
ADD_SUBDIRECTORY(editor)

SET(Tano_Files
    LICENSE.GPL
    data/logo/64x64/logo.png
    data/logo/64x64/logo-daemon.png
    data/logo/64x64/logo-editor.png
)

# Windows
IF(MINGW)
    SET(Tano_Installer
        windows/LICENSE.GPL.TXT
        windows/tano.nsi
        windows/tano-editor.nsi
        windows/tano-install.nsh
        windows/tano-install-editor.nsh
        windows/tano-language.nsh
        windows/tano-ui.nsh
        windows/tano-uninstall.nsh
        windows/tano-uninstall-editor.nsh
    )
    SET(Tano_Installer_Theme
        windows/installer-theme/header.bmp
        windows/installer-theme/installer.ico
        windows/installer-theme/installer-nopng.ico
        windows/installer-theme/installer.png
        windows/installer-theme/License.txt
        windows/installer-theme/uninstaller.ico
        windows/installer-theme/uninstaller-nopng.ico
        windows/installer-theme/uninstaller.png
        windows/installer-theme/wizard.bmp
    )

    STRING(REGEX REPLACE "\\\\" "/" LIBVLCQT_INCLUDE_DIR "${LIBVLCQT_INCLUDE_DIR}")
    STRING(REGEX REPLACE "include" "bin" LIBVLCQT_BIN_DIR "${LIBVLCQT_INCLUDE_DIR}")
    STRING(REGEX REPLACE "bin" "plugins" QT_PLUGINS_DIR "${QT_BIN_DIR}")
    STRING(REGEX REPLACE "bin" "etc/dbus-1" DBUS_ETC_DIR "${QT_BIN_DIR}")

    SET(Tano_Qt_Lib
        ${QT_BIN_DIR}/QtCore4.dll
        ${QT_BIN_DIR}/QtDBus4.dll
        ${QT_BIN_DIR}/QtGui4.dll
        ${QT_BIN_DIR}/QtNetwork4.dll
        ${QT_BIN_DIR}/QtSvg4.dll
        ${QT_BIN_DIR}/QtXml4.dll
        ${QT_BIN_DIR}/libeay32.dll
        ${QT_BIN_DIR}/ssleay32.dll
    )
    FILE(GLOB Tano_Qt_Plugins ${QT_PLUGINS_DIR}/imageformats/*.dll)
    SET(Tano_Dbus_Bin
        ${QT_BIN_DIR}/dbus-daemon.exe
        ${QT_BIN_DIR}/libdbus-1.dll
        ${QT_BIN_DIR}/libexpat.dll
    )
    SET(Tano_Dbus_Config
        ${DBUS_ETC_DIR}/session.conf
        ${DBUS_ETC_DIR}/system.conf
    )
    SET(Tano_Vlc_Libs
        ${LIBVLCQT_BIN_DIR}/libvlc-qt.dll
        ${LIBVLCQT_BIN_DIR}/libvlc.dll
        ${LIBVLCQT_BIN_DIR}/libvlccore.dll
    )
    FILE(GLOB Tano_Vlc_Plugins ${LIBVLCQT_BIN_DIR}/plugins/*.dll)
ENDIF(MINGW)

################
# Installation #
################
# Install data
INSTALL(FILES ${Tano_Files} DESTINATION "${CMAKE_INSTALL_PREFIX}/${TANO_INSTALL_DATA_DIR}")

# Windows Extra
IF(MINGW)
    INSTALL(FILES ${Tano_Installer} DESTINATION "${CMAKE_INSTALL_PREFIX}/${TANO_INSTALL_DATA_DIR}/windows")
    INSTALL(FILES ${Tano_Installer_Theme} DESTINATION "${CMAKE_INSTALL_PREFIX}/${TANO_INSTALL_DATA_DIR}/windows/installer-theme")
    INSTALL(FILES ${Tano_Qt_Lib} DESTINATION "${CMAKE_INSTALL_PREFIX}/${TANO_INSTALL_DATA_DIR}")
    INSTALL(FILES ${Tano_Qt_Plugins} DESTINATION "${CMAKE_INSTALL_PREFIX}/${TANO_INSTALL_DATA_DIR}/imageformats")
    INSTALL(FILES ${Tano_Dbus_Bin} DESTINATION "${CMAKE_INSTALL_PREFIX}/${TANO_INSTALL_DATA_DIR}")
    INSTALL(FILES ${Tano_Dbus_Config} DESTINATION "${CMAKE_INSTALL_PREFIX}/${TANO_INSTALL_DATA_DIR}/etc/dbus-1")
    INSTALL(FILES ${Tano_Vlc_Libs} DESTINATION "${CMAKE_INSTALL_PREFIX}/${TANO_INSTALL_DATA_DIR}")
    INSTALL(FILES ${Tano_Vlc_Plugins} DESTINATION "${CMAKE_INSTALL_PREFIX}/${TANO_INSTALL_DATA_DIR}/vlc/plugins")
ENDIF(MINGW)
