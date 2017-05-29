# This file is part of Poti
#
# Poti is free software: you can redistribute it and/or modify it
# under the terms of the GNU Lesser Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Poti is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser Public License for more details.
#
# You should have received a copy of the GNU Lesser Public License
# along with Poti. If not, see <http://www.gnu.org/licenses/>.
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(poti)
SET(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
enable_testing()

EXEC_PROGRAM("git --git-dir=${PROJECT_SOURCE_DIR}/.git log --oneline -1 2>/dev/null || echo '(unknown)'" OUTPUT_VARIABLE "POTI_GITVERSION")
EXEC_PROGRAM("git --git-dir=${PROJECT_SOURCE_DIR}/.git log -n 1 --format=%ai 2>/dev/null || echo '(unknown)'" OUTPUT_VARIABLE "POTI_GITDATE")

# poti_config.h.in file
CONFIGURE_FILE("${poti_SOURCE_DIR}/include/poti_config.h.in" "${CMAKE_BINARY_DIR}/include/poti_config.h" ESCAPE_QUOTES @ONLY IMMEDIATE)


SET(POTI_SRC src/poti.c src/poti_header.c src/poti_header_default.c src/poti_events.c src/poti_events_unique.c src/poti_events_unaliased.c)
SET(POTI_HEADERS include/poti.h ${CMAKE_BINARY_DIR}/include/poti_config.h)

INCLUDE_DIRECTORIES(${poti_SOURCE_DIR}/include/)
INCLUDE_DIRECTORIES(${poti_SOURCE_DIR}/src/)
INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR}/include/)

ADD_LIBRARY(poti SHARED ${POTI_SRC})
SET_TARGET_PROPERTIES(
  poti
PROPERTIES
# bump when new function are added in the library
  VERSION 4.9
# bump when ABI is broken (symbols removed or parameters changed)
  SOVERSION 8
)
# bump when the API change (new functions in the header file)
SET(POTI_APIVERSION 6)

INSTALL(TARGETS poti
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)
INSTALL(FILES include/poti.h
  DESTINATION include)

ADD_SUBDIRECTORY(examples)
ADD_SUBDIRECTORY(pkgconfig)

INSTALL(TARGETS poti DESTINATION lib)
INSTALL(FILES ${POTI_HEADERS} DESTINATION include)


#
# test with tesh (thanks SimGrid team)
#
#testing the pajeng suite (with pj_dump and pj_validate) through tesh
FILE(COPY ${CMAKE_HOME_DIRECTORY}/tests/scripts/ DESTINATION ${CMAKE_BINARY_DIR}/bin)

# the macro to add tesh'es
SET(TESH_COMMAND perl -I${CMAKE_BINARY_DIR}/bin/ ${CMAKE_BINARY_DIR}/bin/tesh)
MACRO(ADD_TESH NAME)
  SET(ARGT ${ARGV})
  LIST(REMOVE_AT ARGT 0)
  ADD_TEST(${NAME} ${TESH_COMMAND} ${TESH_OPTION} ${ARGT})
ENDMACRO()

# include all tesh scripts in the tests directory
FILE(GLOB tests "${CMAKE_HOME_DIRECTORY}/tests/*.tesh")
LIST(SORT tests)
FOREACH(file ${tests})
  STRING(REGEX REPLACE "^.*/tests/" "" name ${file})
  STRING(REGEX REPLACE ".tesh$" "" testname ${name})
  ADD_TESH(${testname}  --cd "${CMAKE_BINARY_DIR}" ${file})
ENDFOREACH()
