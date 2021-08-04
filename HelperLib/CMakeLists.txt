project (HelperLib)

set(SRC_DIR src)

set(SRCS
    ${SRC_DIR}/File.cpp
)
set(HEADERS
    ${SRC_DIR}/Bitwise8.h
    ${SRC_DIR}/Bitwise16.h
    ${SRC_DIR}/File.h
)
add_library(${PROJECT_NAME} ${SRCS} ${HEADERS})
target_include_directories(${PROJECT_NAME} PUBLIC ${SRC_DIR})
assign_source_group(${SRCS} ${HEADERS})