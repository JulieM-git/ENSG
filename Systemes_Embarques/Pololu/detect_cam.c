
#include <bcm2835.h>
#include <stdio.h>
// Blinks on RPi Plug P1 pin 11 (which is GPIO pin 17)
#define PIN RPI_V2_GPIO_P1_22

int main(int argc, char **argv)
{
    if (!bcm2835_init())
      return 1;

    bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_INPT);
    uint8_t value = 1;
    while (1)
    {
        uint8_t value1 = bcm2835_gpio_lev(PIN);
        printf("read from pin 22: %d\n", value);
        if (value != value1){
		value = value1;
		printf("changed");
		if (value == 0){
			system("./photo.sh");		
		}
		
	}
        
        // wait a bit
        delay(500);
    }
    bcm2835_close();
    return 0;
}
