#ifndef OUR_DRIVER_H_
#define OUR_DRIVER_H_

#include <stdint.h>
#include <zephyr/drivers/sensor.h>

struct dummy_sensor_data {
  uint32_t total_blink_cycles;
};

#ifdef __cplusplus
extern "C" {
#endif

int custom_driver_reset(const struct device *dev);

#ifdef __cplusplus
}
#endif

#endif // OUR_DRIVER_H_