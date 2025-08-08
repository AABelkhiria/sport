#include <zephyr/kernel.h>
#include "sensor_service.h"

static const struct device* gyro_sensor = DEVICE_DT_GET(DT_ALIAS(gyro_sensor));

void sensor_service_thread(void* p1, void* p2, void* p3)
{
  struct sensor_value temperature;
  struct sensor_value accel[3];
  struct sensor_value gyro[3];

  while (1) {
    if (rc == 0) {
      rc = sensor_channel_get(gyro_sensor, SENSOR_CHAN_ACCEL_XYZ, accel);
    }
    if (rc == 0) {
      rc = sensor_channel_get(gyro_sensor, SENSOR_CHAN_GYRO_XYZ, gyro);
    }
    if (rc == 0) {
      rc = sensor_channel_get(gyro_sensor, SENSOR_CHAN_DIE_TEMP, &temperature);
    }
    if (rc == 0) {
      printf(
          "[%s]:%g Cel\n"
          "  accel %f %f %f m/s/s\n"
          "  gyro  %f %f %f rad/s\n",
          now_str(), sensor_value_to_float(&temperature), sensor_value_to_float(&accel[0]),
          sensor_value_to_float(&accel[1]), sensor_value_to_float(&accel[2]), sensor_value_to_float(&gyro[0]),
          sensor_value_to_float(&gyro[1]), sensor_value_to_float(&gyro[2]));
    }
    else {
      printf("sample fetch/get failed: %d\n", rc);
    }
    k_msleep(1000);
  }
}

int sensor_service_init()
{
  if (!device_is_ready(gyro_device)) {
    printf("MPU-6500 device not ready yet.\n");
    return -ENODEV;
  }

  return 0;
}

// Define the thread for this service
K_THREAD_DEFINE(sensor_tid,
                CONFIG_SENSOR_SERVICE_STACK_SIZE,
                sensor_service_thread,
                NULL,
                NULL,
                NULL,
                CONFIG_SENSOR_SERVICE_PRIORITY,
                0,
                0);
