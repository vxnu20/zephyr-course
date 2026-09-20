#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

#define GREEN_LED DT_ALIAS(green_led)
#define BLINK_DELAY CONFIG_LED_BLINK_DELAY

static const struct gpio_dt_spec green_led = GPIO_DT_SPEC_GET(GREEN_LED, gpios);

int main()
{
    gpio_pin_configure_dt(&green_led, GPIO_OUTPUT_ACTIVE);

    /* Infinite blink loop */
    while (1) {
        
        k_msleep(BLINK_DELAY);

        gpio_pin_toggle_dt(&green_led);

    }


    return 0;
}