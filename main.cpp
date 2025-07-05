#include "controller.h"
#include "sensor.h"
#include "system.h"
#include <cstdlib> // for std::atoi

int main(int argc, char* argv[])
{
    system_init();
    int iterations = 1000;
    if (argc > 1)
    {
        int arg_iters = std::atoi(argv[1]);
        if (arg_iters > 0)
            iterations = arg_iters;
    }

    for (int i = 0; i < iterations; ++i)
    {
        read_sensor();
        update_control();
    }
    return 0;
}
