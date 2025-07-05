#include "sensor.h"
#include <stdio.h>

// Simulated global hardware register
volatile int SENSOR_DATA = 0;

void read_sensor()
{
    // Simulated direct register access
    SENSOR_DATA = (SENSOR_DATA + 1) % 1024;
    printf("Sensor read: %d\n", SENSOR_DATA);
}
