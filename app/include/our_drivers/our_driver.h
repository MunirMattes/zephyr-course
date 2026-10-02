/**
 * @file our_drivers/our_driver.h
 *
 * @brief Extension APIs for the our driver.
 */

#ifndef INCLUDE_OUR_DRIVERS_OUR_DRIVER_H_
#define INCLUDE_OUR_DRIVERS_OUR_DRIVER_H_

#include <zephyr/device.h>

#ifdef __cplusplus
extern "C" {
#endif

int our_driver_increment_counter(const struct device * dev);

#ifdef __cplusplus
}
#endif

#endif /* INCLUDE_OUR_DRIVERS_OUR_DRIVER_H_ */
