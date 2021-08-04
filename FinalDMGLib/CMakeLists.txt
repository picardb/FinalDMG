project (FinalDMGLib)

set(SRC_DIR src)

set(SRCS
    ${SRC_DIR}/bus/Bus.cpp
    ${SRC_DIR}/cpu/Cpu.cpp
    ${SRC_DIR}/cpu/CpuInstr.cpp
    ${SRC_DIR}/emulator/Emulator.cpp
    ${SRC_DIR}/memory/BootstrapRom.cpp
)
set(HEADERS
    ${SRC_DIR}/bus/Bus.h
    ${SRC_DIR}/bus/BusDevice.h
    ${SRC_DIR}/cpu/Cpu.h
    ${SRC_DIR}/emulator/Emulator.h
    ${SRC_DIR}/memory/BootstrapRom.h
)
add_library(${PROJECT_NAME} ${SRCS} ${HEADERS})
target_include_directories(${PROJECT_NAME} PUBLIC ${SRC_DIR})
target_link_libraries(${PROJECT_NAME} HelperLib)
assign_source_group(${SRCS})
assign_source_group(${HEADERS})