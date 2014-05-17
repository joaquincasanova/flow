#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <bcm2835.h>
#define PIN0 RPI_V2_GPIO_P1_11 
#define PIN1 RPI_V2_GPIO_P1_15 
#define PIN2 RPI_V2_GPIO_P1_07
using namespace std;

int func=3;
int start=0;
int num=4;
int i, j;
int ticks=0;

int main( int argc, char** argv ){
  int onvol[2]={0, 0};
  //solenoid time in seconds
  for (j=0; j<2; j++){
    for (i=0; argv[j+1][i] != '\0'; i++) {
      onvol[j] *= 10;
      onvol[j] += argv[j+1][i] - '0';
    };
  };
  if (!bcm2835_init())
    return 1;
  // Set RPI pin P1-7 to be an input
  bcm2835_gpio_fsel(PIN2, BCM2835_GPIO_FSEL_INPT);
  // And a high detect enable
  bcm2835_gpio_hen(PIN2);

  //open solenoids
  bcm2835_gpio_fsel(PIN0, BCM2835_GPIO_FSEL_OUTP);
  bcm2835_gpio_write(PIN0, HIGH);
  ticks=0;
  cout<<"Solenoid 1"<<std::endl;
  while (ticks<=onvol[0]*100)
    {
      if (bcm2835_gpio_eds(PIN2))
	{
	  // Now clear the eds flag by setting it to 1
	  bcm2835_gpio_set_eds(PIN2);
	  cout<<ticks<<std::endl;
	  ticks+=206;
	}
    }
  bcm2835_gpio_write(PIN0, LOW);
  
  bcm2835_gpio_fsel(PIN1, BCM2835_GPIO_FSEL_OUTP);
  bcm2835_gpio_write(PIN1, HIGH);
  ticks=0;
  cout<<"Solenoid 2"<<std::endl;
  while (ticks<=onvol[1]*100)
    {
      if (bcm2835_gpio_eds(PIN2))
	{
	  // Now clear the eds flag by setting it to 1
	  bcm2835_gpio_set_eds(PIN2);
	  cout<<ticks<<std::endl;
	  ticks+=206;
	}
    }
  bcm2835_gpio_write(PIN1, LOW);

  bcm2835_close();
  return 0;

}
