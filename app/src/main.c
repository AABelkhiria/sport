#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <stdio.h>

int main(void)
{
  k_sleep(K_MSEC(2000));

  const struct device* mpu6500_dev = DEVICE_DT_GET_ANY(invensense_mpu6050);

  while (!device_is_ready(mpu6500_dev)) {
    printf("MPU-6500 device not ready yet.\n");
    k_sleep(K_MSEC(10000));
  }

  printf("MPU-6500 device is ready!\n");

  while (1) {
    struct sensor_value accel_x, accel_y, accel_z;
    struct sensor_value gyro_x, gyro_y, gyro_z;

    // Fetch sensor data
    if (sensor_sample_fetch(mpu6500_dev) < 0) {
      printf("Sensor sample fetch failed\n");
      k_sleep(K_MSEC(10000));
    }

    // Get accelerometer data
    sensor_channel_get(mpu6500_dev, SENSOR_CHAN_ACCEL_X, &accel_x);
    sensor_channel_get(mpu6500_dev, SENSOR_CHAN_ACCEL_Y, &accel_y);
    sensor_channel_get(mpu6500_dev, SENSOR_CHAN_ACCEL_Z, &accel_z);

    // Get gyroscope data
    sensor_channel_get(mpu6500_dev, SENSOR_CHAN_GYRO_X, &gyro_x);
    sensor_channel_get(mpu6500_dev, SENSOR_CHAN_GYRO_Y, &gyro_y);
    sensor_channel_get(mpu6500_dev, SENSOR_CHAN_GYRO_Z, &gyro_z);

    printf("Accel: X=%.2f Y=%.2f Z=%.2f m/s^2\n", sensor_value_to_double(&accel_x), sensor_value_to_double(&accel_y),
           sensor_value_to_double(&accel_z));

    printf("Gyro: X=%.2f Y=%.2f Z=%.2f rad/s\n", sensor_value_to_double(&gyro_x), sensor_value_to_double(&gyro_y),
           sensor_value_to_double(&gyro_z));

    k_sleep(K_MSEC(1000));  // Read every 1 second
  }

  return 0;
}

const struct device* const rtc = DEVICE_DT_GET(DT_ALIAS(rtc));