cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED)
project(my_zephyr_app)

if (CONFIG_OUR_DRIVER)
    target_sources(app PRIVATE src/main_our_driver.cpp)
    add_subdirectory(drivers/our_driver)
else ()
    target_sources(app PRIVATE src/main.cpp)
endif ()

