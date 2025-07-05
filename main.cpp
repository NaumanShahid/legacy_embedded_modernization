#include "controller.h"
#include "sensor.h"
#include "system.h"

int main()
{
    system_init();

    while (1)
    {
        read_sensor();
        update_control();
    }

    return 0;
}
