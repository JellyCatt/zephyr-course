#include <stdlib.h>
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

static int cmd_set_handler(const struct shell* sh, int argc, char** argv) {
  shell_print(sh, "cmd_set_handler");
  if (argc < 2) {
    shell_error(sh, "Need an input argument!");
    return -EINVAL;
  }
  if (argc > 2) {
    shell_error(sh, "Too many argument!");
    return -EINVAL;
  }
  char *endptr;
  int value = strtol(argv[1], endptr, 10);
  if (endptr != NULL) {
    shell_error(sh, "Invalid argument");
    return -EINVAL;
  }
  if ((value < 0) || (value >= 100)) {
    shell_error(sh, "Argument value out of range");
    return -EINVAL;
  }
  shell_print(sh, "Calling sensor_attr_set");
  struct sensor_value val;
  val.val1 = value; //just for dummy, we don't do anything with the value in sensor_attr_set anyway
  sensor_attr_set(driver, SENSOR_CHAN_AMBIENT_TEMP, SENSOR_ATTR_COMMON_COUNT, &val);
  return 0;
}

SHELL_STATIC_SUBCMD_SET_CREATE(
  sensor_subcmd,
  SHELL_CMD_ARG(fetch, NULL, "Sensor sample fetch", cmd_fetch_handler, 0, 2),
  SHELL_CMD_ARG(read, NULL, "Sensor channel get", cmd_read_handler, 0, 2),
  SHELL_CMD_ARG(info, NULL, "Sensor info", cmd_info_handler, 0, 2),
  SHELL_CMD_ARG(set, NULL, "Set sensor data to <value>", cmd_set_handler, 2, 0),
  SHELL_SUBCMD_SET_END);

SHELL_CMD_REGISTER(sensor, &sensor_subcmd, "Sensor interaction", NULL);