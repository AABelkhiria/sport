#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <stdio.h>

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(sport_app, CONFIG_SPORT_LOG_LEVEL);

static const struct device* gyro_sensor = DEVICE_DT_GET(DT_ALIAS(gyro_sensor));

int main(void)
{

  if (!device_is_ready(gyro_sensor)) {
    LOG_ERR("MPU-6500 device not ready yet.");
  }
  else {
    LOG_INF("MPU-6500 device is ready.");
  }

  while (1) {
    struct sensor_value accel_x, accel_y, accel_z;
    struct sensor_value gyro_x, gyro_y, gyro_z;

    // Fetch sensor data
    if (sensor_sample_fetch(gyro_sensor) < 0) {
      LOG_ERR("Sensor sample fetch failed");
      k_sleep(K_MSEC(10000));
    }
    else {
      // Get accelerometer data
      sensor_channel_get(gyro_sensor, SENSOR_CHAN_ACCEL_X, &accel_x);
      sensor_channel_get(gyro_sensor, SENSOR_CHAN_ACCEL_Y, &accel_y);
      sensor_channel_get(gyro_sensor, SENSOR_CHAN_ACCEL_Z, &accel_z);

      // Get gyroscope data
      sensor_channel_get(gyro_sensor, SENSOR_CHAN_GYRO_X, &gyro_x);
      sensor_channel_get(gyro_sensor, SENSOR_CHAN_GYRO_Y, &gyro_y);
      sensor_channel_get(gyro_sensor, SENSOR_CHAN_GYRO_Z, &gyro_z);

      LOG_INF("Accel: X=%.2f Y=%.2f Z=%.2f m/s^2", sensor_value_to_double(&accel_x), sensor_value_to_double(&accel_y),
              sensor_value_to_double(&accel_z));

      LOG_INF("Gyro: X=%.2f Y=%.2f Z=%.2f rad/s", sensor_value_to_double(&gyro_x), sensor_value_to_double(&gyro_y),
              sensor_value_to_double(&gyro_z));
    }

    k_sleep(K_MSEC(1000));  // Read every 1 second
  }

  return 0;
}
