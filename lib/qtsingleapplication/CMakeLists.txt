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

PROJECT(qtsingleapplication)

# This line adds the include path of the Qt
# directory to the compiler include path
INCLUDE(${QT_USE_FILE})
INCLUDE_DIRECTORIES(${QT_INCLUDE_DIR})

# Define the MOC source files used by QtSingleApplication
SET(QtSA_MOCs
    src/qtlocalpeer.h
    src/qtsingleapplication.h
    src/qtsinglecoreapplication.h
)

# Define the C++ source files used by QtSingleApplication
SET(QtSA_Srcs
    src/qtlocalpeer.cpp
    src/qtsingleapplication.cpp
    src/qtsinglecoreapplication.cpp
)

# This script runs the meta object compiler moc.
QT4_WRAP_CPP(QtSA_MOCs_Srcs ${QtSA_MOCs})

ADD_DEFINITIONS(${QT_DEFINITIONS})
ADD_DEFINITIONS(-DQT_STATIC)

ADD_LIBRARY(qtsingleapplication STATIC ${QtSA_Srcs} ${QtSA_MOCs_Srcs})

TARGET_LINK_LIBRARIES(qtsingleapplication)
