cmake_minimum_required(VERSION 3.14)

project(FinalDMG)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 11)

# GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(SRC_DIR src)

# Lib
set(LIB_SRCS
    ${SRC_DIR}/lib/cpu/Cpu.cpp
    ${SRC_DIR}/lib/emulator/Emulator.cpp
    ${SRC_DIR}/lib/mem_controller/MemController.cpp
    ${SRC_DIR}/lib/helpers/FileHelper.cpp
)
set(LIB_HEADERS
    ${SRC_DIR}/lib/cpu/Cpu.h
    ${SRC_DIR}/lib/emulator/Emulator.h
    ${SRC_DIR}/lib/mem_controller/MemController.h
    ${SRC_DIR}/lib/helpers/FileHelper.h
)
add_library(FinalDMGLib ${LIB_SRCS} ${LIB_HEADERS})
target_include_directories(FinalDMGLib PRIVATE ${SRC_DIR}/lib)

# Playground
set(PLAY_SRCS
    ${SRC_DIR}/play/main.cpp
    ${SRC_DIR}/play/ConsoleHelper.cpp
)
set(PLAY_HEADERS
    ${SRC_DIR}/play/main.h
    ${SRC_DIR}/play/ConsoleHelper.h
)
add_executable(FinalDMGPlay ${PLAY_SRCS} ${PLAY_HEADERS})
target_link_libraries(FinalDMGPlay FinalDMGLib)
target_include_directories(FinalDMGPlay PRIVATE ${SRC_DIR}/lib)


# Tests
set(TEST_SRCS
    ${SRC_DIR}/test/CpuTest.cpp)
set(TEST_HEADERS
    ${SRC_DIR}/test/CpuTest.h)
enable_testing()
add_executable(FinalDMGTest ${TEST_SRCS} ${TEST_HEADERS})
target_link_libraries(FinalDMGTest FinalDMGLib gtest_main)
target_include_directories(FinalDMGTest PRIVATE ${SRC_DIR}/lib)
include(GoogleTest)
gtest_discover_tests(FinalDMGTest)

# Visual Studio filters
function(assign_source_group)
    foreach(_source IN ITEMS ${ARGN})
        if (IS_ABSOLUTE "${_source}")
            file(RELATIVE_PATH _source_rel "${CMAKE_CURRENT_SOURCE_DIR}" "${_source}")
        else()
            set(_source_rel "${_source}")
        endif()
        get_filename_component(_source_path "${_source_rel}" PATH)
        string(REPLACE "/" "\\" _source_path_msvc "${_source_path}")
        source_group("${_source_path_msvc}" FILES "${_source}")
    endforeach()
endfunction(assign_source_group)
assign_source_group(${LIB_SRCS})
assign_source_group(${LIB_HEADERS})
assign_source_group(${PLAY_SRCS})
assign_source_group(${PLAY_HEADERS})
assign_source_group(${TEST_SRCS})
assign_source_group(${TEST_HEADERS})
