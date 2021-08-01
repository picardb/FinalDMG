project (FinalDMGPlay)

set(SRC_DIR src)

set(SRCS
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/ConsoleHelper.cpp
)
set(HEADERS
    ${SRC_DIR}/ConsoleHelper.h
)
add_executable(${PROJECT_NAME} ${SRCS} ${HEADERS})
target_include_directories(${PROJECT_NAME} PUBLIC ${SRC_DIR})
target_link_libraries(${PROJECT_NAME} FinalDMGLib)
assign_source_group(${SRCS})
assign_source_group(${HEADERS})