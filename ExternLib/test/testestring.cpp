
#include "../include/log.h"
#include <gtest/gtest.h>

TEST(LoggerTest, CanLogMessage)
{
    LOG("Hello test");
    SUCCEED(); // We just test that it runs without crashing
}