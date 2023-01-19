# libolivecore
# Copyright (C) 2023 Olive Studios LLC
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

project(libolivecore VERSION 1.0.0 LANGUAGES CXX)

option(OLIVECORE_BUILD_TESTS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# Link avutil
find_package(FFMPEG 3.0 REQUIRED
  COMPONENTS avutil
)

# Link Imath
find_package(Imath REQUIRED CONFIG)

# Link OpenGL
if(UNIX AND NOT APPLE AND NOT DEFINED OpenGL_GL_PREFERENCE)
  set(OpenGL_GL_PREFERENCE LEGACY)
endif()
find_package(OpenGL REQUIRED)

add_library(olivecore
  src/core.h
  src/util/color.cpp
  src/util/color.h
  src/util/pixelformat.h
  src/util/rational.cpp
  src/util/rational.h
  src/util/stringutils.cpp
  src/util/stringutils.h
  src/util/tests.cpp
  src/util/tests.h
  src/util/timecodefunctions.cpp
  src/util/timecodefunctions.h
  src/util/timerange.cpp
  src/util/timerange.h
  src/util/value.cpp
  src/util/value.h
)

set(INSTALL_HEADERS
  src/core.h
  src/util/color.h
  src/util/pixelformat.h
  src/util/rational.h
  src/util/stringutils.h
  src/util/tests.h
  src/util/timecodefunctions.h
  src/util/timerange.h
  src/util/value.h
)

target_include_directories(olivecore PRIVATE
  ${FFMPEG_INCLUDE_DIRS}
  "${CMAKE_SOURCE_DIR}/src"
)

target_link_libraries(olivecore PRIVATE
  OpenGL::GL
  Imath::Imath
  FFMPEG::avutil
)

set_target_properties(olivecore PROPERTIES PUBLIC_HEADER
  "${INSTALL_HEADERS}"
)

install(TARGETS olivecore
  PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_PREFIX}/include/olive/core"
)

if (OLIVECORE_BUILD_TESTS)
  enable_testing()

  function(make_test name)
    add_executable(${name}
      tests/${name}.cpp
    )
    target_link_libraries(${name} PRIVATE olivecore)
    target_include_directories(${name} PRIVATE
      "${CMAKE_SOURCE_DIR}/src"
    )
    add_test(${name} ${name})
  endfunction()

  make_test(rational-test)
  make_test(stringutils-test)
  make_test(timecode-test)
  make_test(timerange-test)
endif()
