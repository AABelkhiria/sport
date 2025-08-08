#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <stdio.h>

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(sport_app, CONFIG_SPORT_LOG_LEVEL);

static const struct device* gyro_sensor = DEVICE_DT_GET(DT_ALIAS(gyro_sensor));

struct k_work_delayable measurement_work;

static void measurement_work_fn(struct k_work *work)
{
  LOG_INF("Measurement work function called.");
  k_work_reschedule(&measurement_work, K_SECONDS(1));

  if (sensor_sample_fetch(gyro_sensor) < 0) {
    LOG_ERR("Sensor sample fetch failed");
    return;
  }

  struct sensor_value accel_x, accel_y, accel_z;
  struct sensor_value gyro_x, gyro_y, gyro_z;

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

int main(void)
{

  k_work_init_delayable(&measurement_work, measurement_work_fn);

  if (!device_is_ready(gyro_sensor)) {
    LOG_ERR("MPU-6500 device not ready yet.");
  }
  else {
    k_work_reschedule(&measurement_work, K_SECONDS(1));
  }

  return 0;
}
