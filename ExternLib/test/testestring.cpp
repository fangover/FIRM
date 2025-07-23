
#include <gtest/gtest.h>
#include "../include/log.h"

TEST(LoggerTest, CanLogMessage)
{
    LOG("wtd");
    SUCCEED(); // We just test that it runs without crashing
}