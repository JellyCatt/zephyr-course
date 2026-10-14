#include <zephyr/shell/shell.h>
#include <zephyr/drivers/sensor.h>

const struct device* driver = DEVICE_DT_GET(DT_NODELABEL(our_driver0));

static int cmd_fetch_handler(const struct shell* sh, int argc, char** argv) {
  shell_print(sh, "cmd_fetch_handler");
  sensor_sample_fetch(driver);
  return 0;
}

static int cmd_read_handler(const struct shell* sh, int argc, char** argv) {
  shell_print(sh, "cmd_read_handler");
  struct sensor_value val;
  sensor_channel_get(driver, SENSOR_CHAN_AMBIENT_TEMP, &val);
  return 0;
}

static int cmd_info_handler(const struct shell* sh, int argc, char** argv) {
  shell_print(sh, "cmd_info_handler");
  bool ready = device_is_ready(driver);
  shell_print(sh, "device name: %s, device state: %d", driver->name, (ready ? 1 : 0));
  return 0;
}

SHELL_STATIC_SUBCMD_SET_CREATE(
  sensor_subcmd,
  SHELL_CMD_ARG(fetch, NULL, "Sensor sample fetch", cmd_fetch_handler, 0, 2),
  SHELL_CMD_ARG(read, NULL, "Sensor channel get", cmd_read_handler, 0, 2),
  SHELL_CMD_ARG(info, NULL, "Sensor info", cmd_info_handler, 0, 2),
  SHELL_SUBCMD_SET_END);

SHELL_CMD_REGISTER(sensor, &sensor_subcmd, "Sensor interaction", NULL);