#ifndef _STRUCTS_H_
#define _STRUCTS_H_

/*
 * @brief   FIXME
 */
struct sensor_data
{
    uint8_t content[2];
    uint8_t error;
};

/*
 * @brief   FIXME
 */
struct track_segment
{
    uint8_t nr;
    uint8_t next1;
    uint8_t prev1;
    uint8_t next2;
    uint8_t prev2;
    uint8_t next_switch;
    uint8_t prev_switch;
    uint8_t next_sensor;
    uint8_t prev_sensor;
};

#endif

