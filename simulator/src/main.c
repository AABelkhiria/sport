#include <zephyr/kernel.h>
#include <zephyr/drivers/sensor.h>
#include <math.h>
#include "ble.h"

#include <stdio.h>

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(simulator_app, CONFIG_SIMULATOR_LOG_LEVEL);

struct k_work_delayable measurement_work;

/* ===== Helpers ===== */
static inline int16_t sensor_to_int16(const struct sensor_value* val, double scale)
{
  double d = sensor_value_to_double(val);
  return (int16_t)(d * scale);
}

static double time_step = 0.0;

/* ===== Measurement Task ===== */
static void measurement_work_fn(struct k_work* work)
{
  k_work_reschedule(&measurement_work, K_SECONDS(3));

  struct sensor_value accel_x, accel_y, accel_z;
  struct sensor_value gyro_x, gyro_y, gyro_z;

  double accel_x_sim = sin(time_step);
  double accel_y_sim = sin(time_step + 3.14 / 2);
  double accel_z_sim = -9.8 + sin(time_step);

  double gyro_x_sim = 0.5 * sin(time_step);
  double gyro_y_sim = 0.5 * sin(time_step + 3.14);
  double gyro_z_sim = 0.5 * sin(time_step * 2);

  accel_x.val1 = (int)(accel_x_sim * 100);
  accel_x.val2 = (int)((accel_x_sim - (int)accel_x_sim) * 1000000);
  accel_y.val1 = (int)(accel_y_sim * 100);
  accel_y.val2 = (int)((accel_y_sim - (int)accel_y_sim) * 1000000);
  accel_z.val1 = (int)(accel_z_sim * 100);
  accel_z.val2 = (int)((accel_z_sim - (int)accel_z_sim) * 1000000); 

  gyro_x.val1 = (int)(gyro_x_sim * 100);
  gyro_x.val2 = (int)((gyro_x_sim - (int)gyro_x_sim) * 1000000);
  gyro_y.val1 = (int)(gyro_y_sim * 100);
  gyro_y.val2 = (int)((gyro_y_sim - (int)gyro_y_sim) * 1000000);
  gyro_z.val1 = (int)(gyro_z_sim * 100);
  gyro_z.val2 = (int)((gyro_z_sim - (int)gyro_z_sim) * 1000000);


  LOG_INF("Accel: X=%.2f Y=%.2f Z=%.2f m/s^2\r", sensor_value_to_double(&accel_x), sensor_value_to_double(&accel_y),
          sensor_value_to_double(&accel_z));

  LOG_INF("Gyro: X=%.2f Y=%.2f Z=%.2f rad/s\r", sensor_value_to_double(&gyro_x), sensor_value_to_double(&gyro_y),
          sensor_value_to_double(&gyro_z));

  gyro_x_val = sensor_to_int16(&gyro_x, 100);
  gyro_y_val = sensor_to_int16(&gyro_y, 100);
  gyro_z_val = sensor_to_int16(&gyro_z, 100);

  accel_x_val = sensor_to_int16(&accel_x, 100);
  accel_y_val = sensor_to_int16(&accel_y, 100);
  accel_z_val = sensor_to_int16(&accel_z, 100);
}

int main(void)
{
  bool err = bt_init();
  if (!err) {
    LOG_ERR("Bluetooth initialization failed");
    return -1;
  }

  k_work_init_delayable(&measurement_work, measurement_work_fn);

  k_work_reschedule(&measurement_work, K_SECONDS(3));

  return 0;
}
