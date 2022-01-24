#########################################################################
#
#  CMAKE
#
#########################################################################

###
#  Minimum Version
#  ---------------
#  The CMake version required.
###
cmake_minimum_required(VERSION 3.1)

###
#  CMake Configuration
#  -------------------
#  Configuration settings for CMake.
#
#  NOTE:
#  These settings have to be applied before the project() setting!
###
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_STANDARD 14)

###
#  Project Info
#  ------------
#  General simple information about our project.
###
project(mrhpspasswd VERSION 1.0.0
                    DESCRIPTION "MRH password platform service executable"
                    LANGUAGES CXX)

#########################################################################
#
#  PATHS
#
#########################################################################

###
#  Install Paths
#  -------------
#  The paths for our created binary file(s).
###
set(BIN_INSTALL_PATH "/usr/local/bin/")

###
#  Build Paths
#  -----------
#  The paths for the cmake build.
###
set(BUILD_DIR_PATH "${CMAKE_SOURCE_DIR}/build/")
file(MAKE_DIRECTORY ${BUILD_DIR_PATH})

###
#  Source Paths
#  ------------
#  The paths to the source files to use.
#  Add OS specific source files in their own list.
###
set(SRC_DIR_PATH "${CMAKE_SOURCE_DIR}/src/")
			 
set(SRC_LIST_CALLBACK "${SRC_DIR_PATH}/Callback/Service/CBAvail.cpp"
                      "${SRC_DIR_PATH}/Callback/Service/CBAvail.h"
                      "${SRC_DIR_PATH}/Callback/Service/CBCustomCommand.cpp"
                      "${SRC_DIR_PATH}/Callback/Service/CBCustomCommand.h"
                      "${SRC_DIR_PATH}/Callback/Password/CBCheck.cpp"
                      "${SRC_DIR_PATH}/Callback/Password/CBCheck.h"
                      "${SRC_DIR_PATH}/Callback/Password/CBSet.cpp"
                      "${SRC_DIR_PATH}/Callback/Password/CBSet.h")
                     
set(SRC_LIST_PASSWORD "${SRC_DIR_PATH}/Password/PasswordFile.cpp"
                      "${SRC_DIR_PATH}/Password/PasswordFile.h"
                      "${SRC_DIR_PATH}/Password/Lockout.cpp"
                      "${SRC_DIR_PATH}/Password/Lockout.h"
                      "${SRC_DIR_PATH}/Password/Encryption.cpp"
                      "${SRC_DIR_PATH}/Password/Encryption.h")
                       
set(SRC_LIST_SERVICE "${SRC_DIR_PATH}/Exception.h"
                     "${SRC_DIR_PATH}/Revision.h"
                     "${SRC_DIR_PATH}/Main.cpp")

#########################################################################
#
#  TARGET
#
#########################################################################

###
#  Target
#  ------
#  The target(s) to build.
###
add_executable(mrhpspasswd ${SRC_LIST_CALLBACK}
                           ${SRC_LIST_PASSWORD}
                           ${SRC_LIST_SERVICE})

###
#  Required Libraries
#  ------------------
#  Libraries required by this platform service.
###
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)

find_package(Threads REQUIRED)
find_library(libmrhbf NAMES mrhbf REQUIRED)
find_library(libmrhev NAMES mrhev REQUIRED)
find_library(libmrhevdata NAMES mrhevdata REQUIRED)
find_library(libmrhpsb NAMES mrhpsb REQUIRED)
find_library(libsodium NAMES sodium REQUIRED)

target_link_libraries(mrhpspasswd PUBLIC Threads::Threads)
target_link_libraries(mrhpspasswd PUBLIC mrhbf)
target_link_libraries(mrhpspasswd PUBLIC mrhev)
target_link_libraries(mrhpspasswd PUBLIC mrhevdata)
target_link_libraries(mrhpspasswd PUBLIC mrhpsb)
target_link_libraries(mrhpspasswd PUBLIC sodium)

###
#  Source Definitions
#  ------------------
#  Preprocessor source definitions.
###
target_compile_definitions(mrhpspasswd PRIVATE MRH_PASSWORD_SERVICE_THREAD_COUNT=1)
target_compile_definitions(mrhpspasswd PRIVATE MRH_PASSWORD_FILE_PATH="/usr/local/etc/mrh/mrhpservice/Password.conf")

###
#  Install
#  -------
#  Application installation.
###
install(TARGETS mrhpspasswd
        DESTINATION ${BIN_INSTALL_PATH})