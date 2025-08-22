#include "ble.h"

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(BLE, CONFIG_BT_LOG_LEVEL);

// #include <zephyr/bluetooth/hci.h>

int16_t gyro_x_val = 0;
int16_t gyro_y_val = 0;
int16_t gyro_z_val = 0;

int16_t accel_x_val = 0;
int16_t accel_y_val = 0;
int16_t accel_z_val = 0;

/* Gyroscope Service UUID */
#define BT_UUID_GYRO_SER_VAL BT_UUID_128_ENCODE(0x12345678, 0x1234, 0x5678, 0x1234, 0x56789abc0000)
#define BT_UUID_GYRO_SERVICE BT_UUID_DECLARE_128(BT_UUID_GYRO_SER_VAL)

/* Gyroscope Characteristic UUIDs */
#define BT_UUID_GYRO_X_VAL BT_UUID_128_ENCODE(0x12345678, 0x1234, 0x5678, 0x1234, 0x56789abc0001)
#define BT_UUID_GYRO_X BT_UUID_DECLARE_128(BT_UUID_GYRO_X_VAL)
#define BT_UUID_GYRO_Y_VAL BT_UUID_128_ENCODE(0x12345678, 0x1234, 0x5678, 0x1234, 0x56789abc0002)
#define BT_UUID_GYRO_Y BT_UUID_DECLARE_128(BT_UUID_GYRO_Y_VAL)
#define BT_UUID_GYRO_Z_VAL BT_UUID_128_ENCODE(0x12345678, 0x1234, 0x5678, 0x1234, 0x56789abc0003)
#define BT_UUID_GYRO_Z BT_UUID_DECLARE_128(BT_UUID_GYRO_Z_VAL)

#define BT_UUID_ACCEL_X_VAL BT_UUID_128_ENCODE(0x12345678, 0x1234, 0x5678, 0x1234, 0x56789abc0011)
#define BT_UUID_ACCEL_X BT_UUID_DECLARE_128(BT_UUID_ACCEL_X_VAL)
#define BT_UUID_ACCEL_Y_VAL BT_UUID_128_ENCODE(0x12345678, 0x1234, 0x5678, 0x1234, 0x56789abc0012)
#define BT_UUID_ACCEL_Y BT_UUID_DECLARE_128(BT_UUID_ACCEL_Y_VAL)
#define BT_UUID_ACCEL_Z_VAL BT_UUID_128_ENCODE(0x12345678, 0x1234, 0x5678, 0x1234, 0x56789abc0013)
#define BT_UUID_ACCEL_Z BT_UUID_DECLARE_128(BT_UUID_ACCEL_Z_VAL)


/* ===== Advertising Data ===== */
static const struct bt_data ad[] = {
    BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
    BT_DATA_BYTES(BT_DATA_UUID128_ALL, BT_UUID_GYRO_SER_VAL),
};

/* ===== Read Callbacks ===== */
static ssize_t read_gyro_x(struct bt_conn *conn, const struct bt_gatt_attr *attr,
                           void *buf, uint16_t len, uint16_t offset)
{
  return bt_gatt_attr_read(conn, attr, buf, len, offset,
                           &gyro_x_val, sizeof(gyro_x_val));
}

static ssize_t read_gyro_y(struct bt_conn *conn, const struct bt_gatt_attr *attr,
                           void *buf, uint16_t len, uint16_t offset)
{
  return bt_gatt_attr_read(conn, attr, buf, len, offset,
                           &gyro_y_val, sizeof(gyro_y_val));
}

static ssize_t read_gyro_z(struct bt_conn *conn, const struct bt_gatt_attr *attr,
                           void *buf, uint16_t len, uint16_t offset)
{
  return bt_gatt_attr_read(conn, attr, buf, len, offset,
                           &gyro_z_val, sizeof(gyro_z_val));
}

static ssize_t read_accel_x(struct bt_conn *conn, const struct bt_gatt_attr *attr,
                            void *buf, uint16_t len, uint16_t offset)
{
  return bt_gatt_attr_read(conn, attr, buf, len, offset,
                           &accel_x_val, sizeof(accel_x_val));
}

static ssize_t read_accel_y(struct bt_conn *conn, const struct bt_gatt_attr *attr,
                            void *buf, uint16_t len, uint16_t offset)
{
  return bt_gatt_attr_read(conn, attr, buf, len, offset,
                           &accel_y_val, sizeof(accel_y_val));
}

static ssize_t read_accel_z(struct bt_conn *conn, const struct bt_gatt_attr *attr,
                            void *buf, uint16_t len, uint16_t offset)
{
  return bt_gatt_attr_read(conn, attr, buf, len, offset,
                           &accel_z_val, sizeof(accel_z_val));
}

BT_GATT_SERVICE_DEFINE(gyro_svc,
  BT_GATT_PRIMARY_SERVICE(BT_UUID_GYRO_SERVICE),

  BT_GATT_CHARACTERISTIC(BT_UUID_GYRO_X,
                        BT_GATT_CHRC_READ | BT_GATT_CHRC_NOTIFY,
                        BT_GATT_PERM_READ,
                        read_gyro_x, NULL, &gyro_x_val
  ),
  BT_GATT_CHARACTERISTIC(BT_UUID_GYRO_Y,
                        BT_GATT_CHRC_READ | BT_GATT_CHRC_NOTIFY,
                        BT_GATT_PERM_READ,
                        read_gyro_y, NULL, &gyro_y_val
  ),
  BT_GATT_CHARACTERISTIC(BT_UUID_GYRO_Z,
                        BT_GATT_CHRC_READ | BT_GATT_CHRC_NOTIFY,
                        BT_GATT_PERM_READ,
                        read_gyro_z, NULL, &gyro_z_val
  ),

  BT_GATT_CHARACTERISTIC(BT_UUID_ACCEL_X,
                        BT_GATT_CHRC_READ | BT_GATT_CHRC_NOTIFY,
                        BT_GATT_PERM_READ,
                        read_accel_x, NULL, &accel_x_val
  ),
  BT_GATT_CHARACTERISTIC(BT_UUID_ACCEL_Y,
                        BT_GATT_CHRC_READ | BT_GATT_CHRC_NOTIFY,
                        BT_GATT_PERM_READ,
                        read_accel_y, NULL, &accel_y_val
  ),
  BT_GATT_CHARACTERISTIC(BT_UUID_ACCEL_Z,
                        BT_GATT_CHRC_READ | BT_GATT_CHRC_NOTIFY,
                        BT_GATT_PERM_READ,
                        read_accel_z, NULL, &accel_z_val
  )
);

static void connected(struct bt_conn *conn, uint8_t err)
{
    if (err) {
        LOG_INF("Connection failed (err 0x%02x)\n", err);
    } else {
        LOG_INF("Connected\n");
    }
}

static void disconnected(struct bt_conn *conn, uint8_t reason)
{
    LOG_INF("Disconnected (reason 0x%02x)\n", reason);
}

static struct bt_conn_cb conn_callbacks = {
    .connected = connected,
    .disconnected = disconnected,
};

void pairing_complete(struct bt_conn *conn, bool bonded)
{
	LOG_INF("Pairing completed. Rebooting in 5 seconds...\n");

	k_sleep(K_SECONDS(5));
	// sys_reboot(SYS_REBOOT_WARM);
}

static void pairing_failed(struct bt_conn *conn, enum bt_security_err reason)
{
	LOG_INF("Pairing Failed (%d). Disconnecting.\n", reason);
}

static void pacs_bond_deleted(uint8_t id, const bt_addr_le_t *peer)
{
  LOG_INF("Bond deleted for peer with ID %d\n", id);
}

static struct bt_conn_auth_info_cb bt_conn_auth_info = {
	.pairing_complete = pairing_complete,
  .pairing_failed = pairing_failed,
  .bond_deleted = pacs_bond_deleted,
};

void bt_ready(void)
{
  int err;

  LOG_INF("Bluetooth initialized\n");

  // if (IS_ENABLED(CONFIG_SETTINGS)) {
  //   settings_load();
  // }

  err = bt_le_adv_start(BT_LE_ADV_CONN, ad, ARRAY_SIZE(ad), NULL, 0);
  if (err) {
    LOG_INF("Advertising failed to start (err %d)\n", err);
    return;
  }

  LOG_INF("Advertising successfully started\n");
}

bool bt_init(void)
{
  bool err = bt_enable(NULL);
  if (err) {
    LOG_INF("Bluetooth init failed (err %d)\n", err);
    return false;
  }

  bt_conn_cb_register(&conn_callbacks);
  bt_conn_auth_info_cb_register(&bt_conn_auth_info);
  
  bt_ready();
  return true;
}
