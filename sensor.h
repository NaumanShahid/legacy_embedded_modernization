#ifndef SENSOR_H
#define SENSOR_H

#ifdef __cplusplus
extern "C"
{
#endif

    // Declare the simulated hardware register for visibility across modules
    extern volatile int SENSOR_DATA;

    void read_sensor();

#ifdef __cplusplus
}
#endif

#endif // SENSOR_H
