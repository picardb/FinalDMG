project (FinalDMGTest)

set(SRC_DIR src)

# GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(SRCS
    ${SRC_DIR}/CpuTest.cpp
)
set(HEADERS
    ${SRC_DIR}/CpuTest.h
)

enable_testing()
add_executable(${PROJECT_NAME} ${SRCS} ${HEADERS})
target_include_directories(${PROJECT_NAME} PUBLIC ${SRC_DIR})
target_link_libraries(${PROJECT_NAME} FinalDMGLib gtest_main)
# target_include_directories(FinalDMGTest PRIVATE ${SRC_DIR}/lib)
include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})

assign_source_group(${SRCS})
assign_source_group(${HEADERS})