CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(poti)
SET(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

EXEC_PROGRAM("git --git-dir=${PROJECT_SOURCE_DIR}/.git log --oneline -1"
  OUTPUT_VARIABLE "POTI_GITVERSION")
EXEC_PROGRAM("git --git-dir=${PROJECT_SOURCE_DIR}/.git log -n 1 --format=%ai"
  OUTPUT_VARIABLE "POTI_GITDATE")

SET(CMAKE_C_FLAGS "-Wall -Wunused -Wmissing-prototypes -Wmissing-declarations -Wpointer-arith -Wchar-subscripts -Wcomment -Wformat -Wwrite-strings -Wno-unused-function -Wno-unused-parameter -Wno-strict-aliasing -Wno-format-nonliteral -Werror ")

# poti_config.h.in file
CONFIGURE_FILE("${poti_SOURCE_DIR}/include/poti_config.h.in"
               "${CMAKE_BINARY_DIR}/include/poti_config.h" @ONLY IMMEDIATE)


SET(POTI_SRC
  src/poti.c
)

SET(POTI_HEADERS
  include/poti.h
  ${CMAKE_BINARY_DIR}/include/poti_config.h
)

INCLUDE_DIRECTORIES(${poti_SOURCE_DIR}/include/)
INCLUDE_DIRECTORIES(${poti_SOURCE_DIR}/src/)
INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR}/include/)

ADD_LIBRARY(poti SHARED ${POTI_SRC})
