#include <zephyr/drivers/sensor.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>

#include "our_driver/our_driver.h"

#define DT_DRV_COMPAT our_driver


#define LED_NODE DT_ALIAS(led0)
static const struct gpio_dt_spec dummy_led = GPIO_DT_SPEC_GET(LED_NODE, gpios);

LOG_MODULE_REGISTER(our_driver, LOG_LEVEL_INF);

static struct dummy_sensor_data dummy_sensor_data_instance;

static int channel_get_my_impl(const struct device *dev,
                               enum sensor_channel chan,
                               struct sensor_value *val) {
  LOG_INF("Hello from channel get, channel %d", chan);
  gpio_pin_set_dt(&dummy_led, 0);
  return 0;
}

static int sample_fetch_my_impl(const struct device *dev,
				     enum sensor_channel chan) {
  LOG_INF("Hello from sample fetch, channel %d", chan);
  gpio_pin_set_dt(&dummy_led, 1);
  return 0;
}

static int custom_attr_set(const struct device *dev,
				 enum sensor_channel chan,
				 enum sensor_attribute attr,
				 const struct sensor_value *val) {
  struct dummy_sensor_data *sensor_data = dev->data;
  sensor_data->total_blink_cycles++;
  if (sensor_data->total_blink_cycles >= 100) {
    sensor_data->total_blink_cycles = 0;
  }
  LOG_INF("Hello from custom_attr_set, channel %d, changed sensor data to = %d", chan, sensor_data->total_blink_cycles);
  return 0;
}

static DEVICE_API(sensor, api_iomico_lecture) = {
  .attr_set = custom_attr_set,
  .sample_fetch = sample_fetch_my_impl,
  .channel_get = channel_get_my_impl,
};

static int init(const struct device* dev) {
  if (!gpio_is_ready_dt(&dummy_led)) return -ENODEV;
  struct dummy_sensor_data *sensor_data = dev->data;
  sensor_data->total_blink_cycles = 0;
  LOG_INF("Led sensor driver is being initialized, data value = %d", sensor_data->total_blink_cycles);

  return gpio_pin_configure_dt(&dummy_led, GPIO_OUTPUT_ACTIVE);
}

DEVICE_DT_INST_DEFINE(0, init, NULL, &dummy_sensor_data_instance, NULL, POST_KERNEL, 80, &api_iomico_lecture);



// Customized extended API
int custom_driver_reset(const struct device *dev) {
  LOG_INF("custom_driver_reset is called");
  if (dev == NULL) {
    LOG_ERR("dev is NULL!");
    return -ENXIO;
  }
  struct dummy_sensor_data *sensor_data = dev->data;
  if (sensor_data == NULL) {
    LOG_ERR("sensor_data is NULL!");
    return -ENXIO;
  }
  sensor_data->total_blink_cycles = 0;
  LOG_INF("custom_driver_reset successfully!");
  return 0;
}