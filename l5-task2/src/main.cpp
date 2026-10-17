#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/init.h>
#include <zephyr/sys/printk.h>

#define RED_LED DT_ALIAS(red_led)
#define BLINK_DELAY CONFIG_LED_BLINK_DELAY

static const struct gpio_dt_spec red_led = GPIO_DT_SPEC_GET(RED_LED, gpios);

static int board_initialized(void)
{
    printk("Board Initialized\n");
    return 0;
}

SYS_INIT(board_initialized, APPLICATION, 0);

int main()
{
    gpio_pin_configure_dt(&red_led, GPIO_OUTPUT_ACTIVE);

    /* Infinite blink loop */
    while (1) {
        
        k_msleep(BLINK_DELAY);

        gpio_pin_toggle_dt(&red_led);

    }


    return 0;
}