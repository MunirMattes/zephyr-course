#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/gpio.h>

#define DT_DRV_COMPAT our_driver
LOG_MODULE_REGISTER(our_driver, LOG_LEVEL_INF);

struct our_driver_data {
    int32_t counter;
};

static const struct gpio_dt_spec led = 
    GPIO_DT_SPEC_GET(DT_ALIAS(our_driver_led), gpios);

static int our_driver_sample_fetch(const struct device *dev,
                                   enum sensor_channel chan)
{
    LOG_INF("our_driver_sample_fetch %d", chan);
    gpio_pin_set_dt(&led, 1);

    return 0;
}

static int our_driver_channel_get(const struct device *dev,
                                  enum sensor_channel chan, struct sensor_value *val)
{
    LOG_INF("our_driver_channel_get %d", chan);
    gpio_pin_set_dt(&led, 0);

    return 0;
}

int our_driver_increment_counter(const struct device * dev)
{
    struct our_driver_data *data = dev->data;

    data->counter++;
    LOG_INF("our_driver_increment_counter %d", data->counter);

    return 0;
}

static DEVICE_API(sensor, our_driver_api) = {
    .sample_fetch = our_driver_sample_fetch, 
    .channel_get = our_driver_channel_get,
};

static int our_driver_init(const struct device *dev)
{
    if (!gpio_is_ready_dt(&led)) return -1;

    if (gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE) < 0) return -1;

    LOG_INF("Device initialized");

    return 0;
}

#define OUR_DRIVER_DEFINE(inst)                             \
    static struct our_driver_data data_##inst;              \
    DEVICE_DT_INST_DEFINE(inst,                             \
        our_driver_init, NULL,                              \
        &data_##inst, NULL,                                 \
        POST_KERNEL, 80,                                    \
        &our_driver_api)

DT_INST_FOREACH_STATUS_OKAY(OUR_DRIVER_DEFINE)
