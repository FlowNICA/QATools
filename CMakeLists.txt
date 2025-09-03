# CMakeLists.txt for FAS package. It creates a library with dictionary and a main program
cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(QAtools)

# You need to tell CMake where to find the ROOT installation. This can be done
# in a number of ways:
#   - ROOT built with classic configure/make use the provided
#   $ROOTSYS/etc/cmake/FindROOT.cmake
#   - ROOT built with CMake. Add in CMAKE_PREFIX_PATH the installation prefix
#   for ROOT

find_package(Git)

list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

#---Locate the ROOT package and defines a number of variables (e.g. ROOT_INCLUDE_DIRS)
find_package(ROOT REQUIRED COMPONENTS MathCore RIO Hist Tree Net EG)

#---Define useful ROOT functions and macros (e.g. ROOT_GENERATE_DICTIONARY)
include(${ROOT_USE_FILE})

add_definitions(${ROOT_CXX_FLAGS})

#---Locate MCINI package
find_library(MCINI NAMES McIniData PATHS $ENV{MCINI}/build)
IF(MCINI)
  message(STATUS "mcini is found: ${MCINI}")
  add_definitions("-D_MCINI_")
endif()
IF(NOT MCINI)
  message(STATUS "mcini is not found. Building without it.")
endif()

#---Locate PHQMDEvent library
find_library(PHQMD NAMES PHQMDEvent PATHS $ENV{PHQMD_PATH}/phqmd2root/lib/)
if(PHQMD)
  message(STATUS "libPHQMDEvent is found: ${PHQMD}")
  add_definitions("-D_PHQMD_")
  add_definitions("-D_HSD_ROOT_")
endif()
if(NOT PHQMD)
  message(STATUS "libPHQMDEvent is not found. Building without it.")
endif()

set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -Wall -pthread")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall -ffast-math")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall")

set(QATOOLS_INCLUDE_DIRECTORIES
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/bin
  ${CMAKE_CURRENT_SOURCE_DIR}/format
  ${CMAKE_CURRENT_SOURCE_DIR}/readers
  ${CMAKE_CURRENT_SOURCE_DIR}/utility
  ${ROOT_INLCUDE_DIRS}
)

set(QATOOLS_INCLUDE_LIBRARIES
  ${ROOT_LIBRARIES}
)

set(QATOOLS_LIBRARY_h_files
  ${CMAKE_CURRENT_SOURCE_DIR}/format/qaParticle.h
  ${CMAKE_CURRENT_SOURCE_DIR}/format/qaParticleLight.h
  ${CMAKE_CURRENT_SOURCE_DIR}/format/qaEvent.h
  ${CMAKE_CURRENT_SOURCE_DIR}/readers/qaReader_smash_root.h
  ${CMAKE_CURRENT_SOURCE_DIR}/readers/qaReader_mcpico.h
  ${CMAKE_CURRENT_SOURCE_DIR}/readers/qaReader_manager.h
  ${CMAKE_CURRENT_SOURCE_DIR}/utility/Utility.h
)

set(QATOOLS_LIBRARY_cxx_files
  ${CMAKE_CURRENT_SOURCE_DIR}/format/qaParticle.cxx
  ${CMAKE_CURRENT_SOURCE_DIR}/format/qaParticleLight.cxx
  ${CMAKE_CURRENT_SOURCE_DIR}/format/qaEvent.cxx
  ${CMAKE_CURRENT_SOURCE_DIR}/readers/qaReader_smash_root.cxx
  ${CMAKE_CURRENT_SOURCE_DIR}/readers/qaReader_mcpico.cxx
  ${CMAKE_CURRENT_SOURCE_DIR}/readers/qaReader_manager.cxx
  ${CMAKE_CURRENT_SOURCE_DIR}/utility/Utility.cxx
)

if(MCINI)
  list(APPEND QATOOLS_INCLUDE_DIRECTORIES $ENV{MCINI}/include)
  list(APPEND QATOOLS_INCLUDE_LIBRARIES ${MCINI})
  list(APPEND QATOOLS_LIBRARY_h_files ${CMAKE_CURRENT_SOURCE_DIR}/readers/qaReader_mcini.h)
  list(APPEND QATOOLS_LIBRARY_cxx_files ${CMAKE_CURRENT_SOURCE_DIR}/readers/qaReader_mcini.cxx)
endif()

if(PHQMD)
  list(APPEND QATOOLS_INCLUDE_DIRECTORIES $ENV{PHQMD_PATH})
  list(APPEND QATOOLS_INCLUDE_LIBRARIES ${PHQMD})
  list(APPEND QATOOLS_LIBRARY_h_files ${CMAKE_CURRENT_SOURCE_DIR}/readers/qaReader_phqmd.h)
  list(APPEND QATOOLS_LIBRARY_cxx_files ${CMAKE_CURRENT_SOURCE_DIR}/readers/qaReader_phqmd.cxx)
  list(APPEND QATOOLS_LIBRARY_h_files ${CMAKE_CURRENT_SOURCE_DIR}/readers/qaReader_hsd_root.h)
  list(APPEND QATOOLS_LIBRARY_cxx_files ${CMAKE_CURRENT_SOURCE_DIR}/readers/qaReader_hsd_root.cxx)
endif()

include_directories(${QATOOLS_INCLUDE_DIRECTORIES})

set(QATOOLS_LinkDef
  ${CMAKE_CURRENT_SOURCE_DIR}/qaTools.LinkDef.h
)

#---Generate dictionary
ROOT_GENERATE_DICTIONARY(G__qaTools
  ${QATOOLS_LIBRARY_h_files}
  LINKDEF ${QATOOLS_LinkDef}
)

#---Compile library
add_library(qaTools SHARED ${QATOOLS_LIBRARY_cxx_files} G__qaTools.cxx)
target_link_libraries(qaTools ${QATOOLS_INCLUDE_LIBRARIES})

# Get the current working branch
execute_process(
  COMMAND git rev-parse --abbrev-ref HEAD
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE GIT_BRANCH
  RESULT_VARIABLE GIT_BRANCH_ERROR_CODE
  OUTPUT_STRIP_TRAILING_WHITESPACE
)
if( GIT_BRANCH_ERROR_CODE )
  set(GIT_BRANCH 0)
endif()

# Get the latest abbreviated commit hash of the working branch
execute_process(
  COMMAND git rev-parse --short HEAD
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE GIT_COMMIT_HASH
  RESULT_VARIABLE GIT_COMMIT_HASH_ERROR_CODE
  OUTPUT_STRIP_TRAILING_WHITESPACE
)
if( GIT_COMMIT_HASH_ERROR_CODE )
  set(GIT_COMMIT_HASH 0)
endif()

# Get the current version
execute_process(
  COMMAND git describe --tags --match "*"
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE GIT_TAG_VERSION
  RESULT_VARIABLE GIT_TAG_VERSION_ERROR_CODE
  OUTPUT_STRIP_TRAILING_WHITESPACE
)
if( GIT_TAG_VERSION_ERROR_CODE )
  set(GIT_TAG_VERSION 0.0)
endif()

set_target_properties (qaTools 
  PROPERTIES 
  VERSION ${GIT_TAG_VERSION} SOVERSION ${GIT_BRANCH}-${GIT_COMMIT_HASH}
)

#---Compile main executable
add_executable(qaProcess "${CMAKE_CURRENT_SOURCE_DIR}/bin/main.cpp")
target_link_libraries(qaProcess qaTools)
