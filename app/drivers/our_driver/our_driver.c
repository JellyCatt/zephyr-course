#include <zephyr/drivers/sensor.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>

#define DT_DRV_COMPAT our_driver


#define LED_NODE DT_ALIAS(led0)
static const struct gpio_dt_spec dummy_led = GPIO_DT_SPEC_GET(LED_NODE, gpios);

LOG_MODULE_REGISTER(our_driver, LOG_LEVEL_INF);



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

static DEVICE_API(sensor, api_iomico_lecture) = {
  .sample_fetch = sample_fetch_my_impl,
  .channel_get = channel_get_my_impl,
};

static int init(const struct device* dev) {
  if (!gpio_is_ready_dt(&dummy_led)) return -ENODEV;

  LOG_INF("Led sensor driver is being initialized");

  return gpio_pin_configure_dt(&dummy_led, GPIO_OUTPUT_ACTIVE);
}

DEVICE_DT_INST_DEFINE(0, init, NULL, NULL, NULL, POST_KERNEL, 80, &api_iomico_lecture);