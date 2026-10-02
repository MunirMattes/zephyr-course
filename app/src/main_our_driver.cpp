#include <zephyr/drivers/sensor.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <our_drivers/our_driver.h>

#define SLEEP_TIME_MS 1000

const struct device *dev = DEVICE_DT_GET(DT_NODELABEL(our_driver0));

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

int main(void)
{
    struct sensor_value val;

    if (!device_is_ready(dev)) return -ENODEV;

    while (1) {
        int ret = sensor_sample_fetch(dev);
        LOG_INF("Fetch: %d", ret);
        k_msleep(SLEEP_TIME_MS);

        ret = sensor_channel_get(dev, SENSOR_CHAN_AMBIENT_TEMP, &val);
        LOG_INF("Get: %d", ret);
        k_msleep(SLEEP_TIME_MS);

        ret = our_driver_increment_counter(dev);
        LOG_INF("Increment: %d", ret);
    }
    return 0;
}
