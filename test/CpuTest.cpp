#include <gtest/gtest.h>

#include "cpu/Cpu.h"

namespace FinalDMG {

    TEST(CpuTest, BasicAssertions) {
        FinalDMG::Cpu cpu = new Cpu();
        EXPECT_EQ(1, 1);
    }
}
