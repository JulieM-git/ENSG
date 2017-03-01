#include <bcm2835.h>
#include <stdio.h>
// PIN
#define PIN RPI_V2_GPIO_P1_22

int main(int argc, char **argv)
{
    if (!bcm2835_init())
      return 1;
	
    bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_INPT);
	// Valeur 1 si pololu detecte rien sinon 0
    uint8_t value = 1;
    while (1)
    {
        // Recupere la valeur
		uint8_t value1 = bcm2835_gpio_lev(PIN);
        printf("read from pin 22: %d\n", value);
        // Si la valeur est differente de la precedente
		if (value != value1){
			// On garde la nouvelle valeur
			value = value1;
			printf("changed");
			// Si cette valeur est 0 alors on prend un photo :)
			if (value == 0){
				system("./photo.sh");		
			}
		}
		
        // On fait patienter un peu
        delay(500);
    }
    bcm2835_close();
    return 0;
}
