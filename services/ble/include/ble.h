#ifndef BT_H
#define BT_H

#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/services/bas.h>
#include <zephyr/bluetooth/services/cts.h>
#include <zephyr/bluetooth/gatt.h>
#include <zephyr/bluetooth/conn.h>

// extern State currentState;

// extern struct ring_buf process_ringbuf;
// extern uint8_t process_buf[2048];

// extern const struct device *gyro_sensor;

// extern struct k_work_delayable measurement_work;

// extern struct bt_uuid_128 custom_service_uuid;
// extern struct bt_uuid_128 gyro_x_uuid;
// extern struct bt_uuid_128 gyro_y_uuid;
// extern struct bt_uuid_128 gyro_z_uuid;

extern int16_t gyro_x_val;
extern int16_t gyro_y_val;
extern int16_t gyro_z_val;

extern int16_t accel_x_val;
extern int16_t accel_y_val;
extern int16_t accel_z_val;

bool bt_init(void);

#endif // BT_H