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

set(LIB_SRCS
    lib/cpu/Cpu.cpp
    lib/cpu/CpuRegs.cpp
    lib/emulator/Emulator.cpp
    lib/mem_controller/MemController.cpp
    lib/helpers/FileHelper.cpp
)

set(LIB_HEADERS
    lib/cpu/Cpu.h
    lib/cpu/CpuRegs.h
    lib/emulator/Emulator.h
    lib/mem_controller/MemController.h
    lib/helpers/FileHelper.h
)

add_library(FinalDMGLib ${LIB_SRCS} ${LIB_HEADERS})

target_include_directories(FinalDMGLib PRIVATE lib)

# Tests
set(TEST_SRCS
    test/CpuTest.cpp)
set(TEST_HEADERS
    test/CpuTest.h)
enable_testing()
add_executable(FinalDMGTest ${TEST_SRCS} ${TEST_HEADERS})
target_link_libraries(FinalDMGTest FinalDMGLib gtest_main)
target_include_directories(FinalDMGTest PRIVATE lib)
include(GoogleTest)
gtest_discover_tests(FinalDMGTest)
