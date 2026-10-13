#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/sensor.h>

/* The devicetree node identifier for the "led0" alias. */
// #define LED_NODE DT_ALIAS(led0)

// static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED_NODE, gpios);

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

// namespace 
// {
//     void test() {
//         const struct device* driver = DEVICE_DT_GET(DT_NODELABEL(our_driver0));
//         struct sensor_value val;
//         auto ret = sensor_channel_get(driver, SENSOR_CHAN_AMBIENT_TEMP, &val);
//         LOG_INF("Channel ret %d", ret);
//     }
    
// } // namespace 

int main(void)
{
    // bool led_state = true;

    // if (!gpio_is_ready_dt(&led)) return 0;

    // if (gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE) < 0) return 0;
    const struct device* driver = DEVICE_DT_GET(DT_NODELABEL(our_driver0));
    if (!device_is_ready(driver)) {
        LOG_INF("Sensor driver failed initialization\n");
        return 0;
    }
    struct sensor_value val;
    while (1) {
        // if (gpio_pin_toggle_dt(&led) < 0) return 0;
        
        // led_state = !led_state;
        // LOG_INF("LED state: %s", led_state ? "ON" : "OFF");
        sensor_channel_get(driver, SENSOR_CHAN_AMBIENT_TEMP, &val);
        k_msleep(CONFIG_BLINK_SLEEP_TIME_MS);
        sensor_sample_fetch(driver);
        k_msleep(CONFIG_BLINK_SLEEP_TIME_MS);
    }
    return 0;
}
