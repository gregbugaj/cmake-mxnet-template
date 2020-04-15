cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(mxnet_template C CXX)
set(TARGET_NAME "mxnet_template")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# This is to prevent : -- Set runtime path of "./bin/matchbox" to ""
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

#SET(GCC_CUSTOM_COMPILE_FLAGS "-fverbose-asm -std=gnu++17  -mpopcnt -static-libgcc -static-libstdc++ -static")

SET(GCC_CUSTOM_COMPILE_FLAGS "-fverbose-asm -std=gnu++17  -mpopcnt")
SET(GCC_CUSTOM_LINK_FLAGS    "-lstdc++fs")

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_CUSTOM_COMPILE_FLAGS}" )
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_CUSTOM_LINK_FLAGS}" )


# Set a default build type if none was specified
if(NOT CMAKE_BUILD_TYPE)
    message(STATUS "Setting build type to 'Release' as none was specified.")
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
endif()

message("EnvParameter : CMAKE_BUILD_TYPE          = ${CMAKE_BUILD_TYPE}")
message("EnvParameter : CMAKE_SOURCE_DIR          = ${CMAKE_SOURCE_DIR}")
message("EnvParameter : CMAKE_CURRENT_SOURCE_DIR  = ${CMAKE_CURRENT_SOURCE_DIR}")
message("EnvParameter : CMAKE_BINARY_DIR          = ${CMAKE_BINARY_DIR}")
message("EnvParameter : CMAKE_CURRENT_BINARY_DIR  = ${CMAKE_CURRENT_BINARY_DIR}")
message("EnvParameter : CMAKE_INSTALL_PREFIX      = ${CMAKE_INSTALL_PREFIX}")

###########################################################
# Where are the additional libraries installed? Note: provide includes
# path here, subsequent checks will resolve everything else
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/modules")

find_program(GIT "git")
if (GIT)
    execute_process(
            COMMAND git log -1 --format=%H
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            OUTPUT_VARIABLE GIT_COMMIT_HASH
            OUTPUT_STRIP_TRAILING_WHITESPACE
    )
else ()
    set(GIT_COMMIT_HASH "unknown")
endif ()

configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/version.h.in
        ${CMAKE_CURRENT_BINARY_DIR}/version.h
)

# Source files

set(SOURCE_FILES main.cpp)

# Build as executable
add_executable(${TARGET_NAME} ${SOURCE_FILES})
set_target_properties(${TARGET_NAME} PROPERTIES LINKER_LANGUAGE CXX)
#set_target_properties(${TARGET_NAME} PROPERTIES LINK_SEARCH_END_STATIC 1)


### Leptonica
include(FindLeptonica)

if (LEPTONICA_FOUND)
    message(STATUS "Leptonica ready")
    include_directories(${LEPTONICA_INCLUDE_DIRS})
    target_link_libraries(${TARGET_NAME} ${LEPTONICA_LIBRARIES})
else ()
    message(FATAL_ERROR "libleptonica-dev is required install with 'apt-get install libleptonica-dev'")
endif(LEPTONICA_FOUND)
### Leptonica


### OpenCV
include(FindOpenCV)

message(STATUS "OpenCV found   =  ${OpenCV_FOUND}")
message(STATUS "OpenCV include =  ${OpenCV_INCLUDE_DIRS}")
message(STATUS "OpenCV lib     =  ${OpenCV_LIBRARIES}")
# message(FATAL_ERROR "OpenCV not setup")

if (OpenCV_FOUND)
    message(STATUS "OpenCV ready")
    include_directories(${OpenCV_INCLUDE_DIRS})
    target_link_libraries(${TARGET_NAME} ${OpenCV_LIBRARIES})
else ()
    message(FATAL_ERROR "OpenCV not setup")
endif(OpenCV_FOUND)
### OpenCV


# MxNet
include(FindMxNet)

find_package(Threads)

if (MxNet_FOUND)
    message(STATUS "MxNet ready")
    include_directories(${MxNet_INCLUDE_DIRS})
    
    target_link_libraries(${TARGET_NAME} ${MxNet_LIB})

    # Setup for static linking
    #target_link_libraries(${TARGET_NAME}  ${CMAKE_THREAD_LIBS_INIT} ${CMAKE_SOURCE_DIR}/lib/libmxnet.a)

else ()
    message(FATAL_ERROR "MXNET not ready, compile from source with 'USE_CPP_PACKAGE=1' ")
endif(MxNet_FOUND)

# Generated
include_directories(${CMAKE_CURRENT_BINARY_DIR}/generated)

# copy test-deck files if any
message("++ EnvParameter : CMAKE_BINARY_DIR     = ${CMAKE_BINARY_DIR}")

file(GLOB MY_TESTDECK_FILES "${CMAKE_SOURCE_DIR}/test-deck")
file(COPY ${MY_TESTDECK_FILES} DESTINATION "${CMAKE_BINARY_DIR}/")

# Filesystem support
target_link_libraries(${TARGET_NAME} stdc++fs)

# Install
install(TARGETS ${TARGET_NAME} DESTINATION bin)