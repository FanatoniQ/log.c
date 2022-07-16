cmake_minimum_required(VERSION 3.0)
project(log.c VERSION "0.2.0" LANGUAGES C)

include(CheckSymbolExists)
include(CheckIncludeFile)

###########
# OPTIONS #
###########

option(LOG_USE_COLOR "Enable ANSI color features" ON)
option(LOG_FORCE_COLOR "Force ANSI color features" OFF)
option(LOG_USE_BRIGHT_COLOR "Use brighter ANSI colors" OFF)

if (LOG_FORCE_COLOR OR LOG_USE_BRIGHT_COLOR)
    set(LOG_USE_COLOR ON)
endif ()

###########
# C FLAGS #
###########

if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
    message(DEBUG "Compiler is GNU compliant !")  # cmake --log-level=DEBUG
    add_compile_options(-std=c99 -Werror -Wall -Wextra -pedantic)
endif ()

###############
# OS FEATURES #
###############

if (WIN32 OR __WIN32)
    check_symbol_exists(ENABLE_VIRTUAL_TERMINAL_PROCESSING "windows.h" HAVE_WIN32_VT100)
else ()
    check_include_file("unistd.h" HAVE_UNISTD_H)
endif ()

if (NOT HAVE_WIN32_VT100 AND NOT HAVE_UNISTD_H)
    message(WARNING "Terminal colors will not be supported !")
    if (LOG_USE_COLOR AND NOT LOG_FORCE_COLOR)
        message(WARNING "Use `-DLOG_FORCE_COLOR` to force color support !")
    endif ()
endif ()

###############################
# HEADER FILE build/gen/log.h #
###############################

configure_file(
    ${PROJECT_SOURCE_DIR}/include/log.h.in
    ${PROJECT_BINARY_DIR}/gen/log.h
    @ONLY
)

###########################
# STATIC LIBRARY liblog.c #
###########################

add_library(log.c STATIC ${PROJECT_SOURCE_DIR}/src/log.c)
target_include_directories(log.c PUBLIC ${PROJECT_BINARY_DIR}/gen)

if (LOG_USE_COLOR)
    target_compile_definitions(log.c PRIVATE -DLOG_USE_COLOR)
    message(STATUS "Option LOG_USE_COLOR is ON")
endif ()

if (LOG_FORCE_COLOR)
    target_compile_definitions(log.c PRIVATE -DLOG_FORCE_COLOR)
    message(STATUS "Option LOG_FORCE_COLOR is ON")
endif ()

if (LOG_USE_BRIGHT_COLOR)
    target_compile_definitions(log.c PRIVATE -DLOG_USE_BRIGHT_COLOR)
    message(STATUS "Option LOG_USE_BRIGHT_COLOR is ON")
endif ()

if (LOG_USE_COLOR)
    ############################
    # EXECUTABLE color_example #
    ############################

    add_executable(color_example EXCLUDE_FROM_ALL ${PROJECT_SOURCE_DIR}/examples/color_example.c)
    target_include_directories(color_example PUBLIC ${PROJECT_BINARY_DIR}/gen)
    target_link_libraries(color_example log.c)

    #################################
    # EXECUTABLE color_full_example #
    #################################

    add_executable(color_full_example EXCLUDE_FROM_ALL ${PROJECT_SOURCE_DIR}/examples/color_full_example.c)
    target_include_directories(color_full_example PUBLIC ${PROJECT_BINARY_DIR}/gen)
    target_link_libraries(color_full_example log.c)
endif ()

######################
# EXECUTABLE example #
######################

add_executable(example EXCLUDE_FROM_ALL ${PROJECT_SOURCE_DIR}/examples/example.c)
target_include_directories(example PUBLIC ${PROJECT_BINARY_DIR}/gen)
target_link_libraries(example log.c)
