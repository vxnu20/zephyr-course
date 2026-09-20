#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

/* Extract the device tree node using the alias defined in app.overlay */
#define RED_LED DT_ALIAS(red_led)
#define GREEN_LED DT_ALIAS(green_led)
#define BLUE_LED DT_ALIAS(blue_led)

/* Validate that the node exists at build time */
#if ((!DT_NODE_HAS_STATUS(RED_LED, okay)) && !DT_NODE_HAS_STATUS(GREEN_LED, okay) && !DT_NODE_HAS_STATUS(BLUE_LED, okay))
#error "Unsupported board: my-led devicetree alias is not defined or enabled"
#endif

/* Initialize the GPIO specification structure */
static const struct gpio_dt_spec red_led = GPIO_DT_SPEC_GET(RED_LED, gpios);
static const struct gpio_dt_spec green_led = GPIO_DT_SPEC_GET(GREEN_LED, gpios);
static const struct gpio_dt_spec blue_led = GPIO_DT_SPEC_GET(BLUE_LED, gpios);

/* Map the Kconfig variable to our C code */
#define SLEEP_TIME_MS CONFIG_APP_BLINK_DELAY_MS

int main(void)
{
    int ret;

    /* Verify the GPIO port is ready before interacting with it */
    if (!gpio_is_ready_dt(&red_led)) {
        return 0;
    }

    /* Configure the pin as an output */
    gpio_pin_configure_dt(&red_led, GPIO_OUTPUT_ACTIVE);
    gpio_pin_configure_dt(&green_led, GPIO_OUTPUT_ACTIVE);
    gpio_pin_configure_dt(&blue_led, GPIO_OUTPUT_ACTIVE);

    /* Infinite blink loop */
    while (1) {
        gpio_pin_toggle_dt(&red_led);
        
        k_msleep(SLEEP_TIME_MS);

        gpio_pin_toggle_dt(&green_led);
    
        k_msleep(SLEEP_TIME_MS);

        gpio_pin_toggle_dt(&blue_led);
        
        k_msleep(SLEEP_TIME_MS);

    }
    
    return 0;
}