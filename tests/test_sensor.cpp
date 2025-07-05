#include "../sensor.h"
#include "gtest/gtest.h"

TEST(SensorTest, InitialSensorDataIsZero)
{
    EXPECT_EQ(SENSOR_DATA, 0);
}

TEST(SensorTest, SensorDataWrapsCorrectly)
{
    SENSOR_DATA = 1023;
    read_sensor(); // adds 1
    EXPECT_EQ(SENSOR_DATA, 0);
}
