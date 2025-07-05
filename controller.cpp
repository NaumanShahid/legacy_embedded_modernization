#include "controller.h"
#include "sensor.h"
#include <stdio.h>

// Legacy global control state
int control_output = 0;

void update_control()
{
    if (SENSOR_DATA > 500)
    {
        control_output++;
    }
    else
    {
        control_output--;
    }
    printf("Control output: %d\n", control_output);
}
