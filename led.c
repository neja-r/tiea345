#include <stdio.h>    // Used for printf() statements
#include <wiringPi.h> // Include WiringPi library!
#include <time.h>
#include <stdlib.h>

// Pin number declarations. We're using the Broadcom chip pin numbers.
const int merkki = 20; //keltainen led
const int painike = 21;
const int pir = 12; // liiketunnistin pir
const int akt = 1; //active value = 1


int main(void)
{
    time_t endwait;
    time_t start = time(NULL);
    time_t seconds = 20; // after 20s, end loop.

    endwait = start + seconds;
    
    // Setup stuff:
    wiringPiSetupGpio(); // Initialize wiringPi -- using Broadcom pin numbers

    pinMode(merkki, OUTPUT); // led outputiksi
    pinMode(painike, INPUT);     // painike inputiksi
    pinMode(pir, INPUT);      // pir inputiksi
    //pullUpDnControl(butPin, PUD_UP); Enable pull-up resistor on button
    int tila = akt; //Init state to HIGH

    // Loop (while(!)):
    while(start < endwait)
    {
	  digitalWrite(merkki, LOW);
	tila = digitalRead(pir);
	if(tila != akt)
	{
	  digitalWrite(merkki, LOW);	
	}
	else //pir havaitsee liiketta
	{
	  digitalWrite(merkki, HIGH); // Turn LED ON
	}

        start = time(NULL);
    }

    //CLEANUP: kaikki inputiksi lopuksi
    pinMode(merkki, INPUT);
    pinMode(painike, INPUT);
    pinMode(pir, INPUT);

    return 0;
}