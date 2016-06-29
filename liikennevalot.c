//Käännösohje: gcc -o liikennevalot liikennevalot.c -l wiringPi
// sudo ./liikennevalot
#include <stdio.h> 
#include <wiringPi.h> // Include WiringPi library!
#include <time.h>

// Pin number declarations. We're using the Broadcom chip pin numbers.
const int merkki = 20; //keltainen merkkiled
const int painike = 21;
//autoilijoiden valot:
const int apun = 26;
const int akelt = 22;
const int avihr = 13;
//jalankulkijoiden valot:
const int jpun = 6;
const int jvihr = 5;

const int pir = 12; // liiketunnistin pir
const int akt = 1; //active value = 1


int main(void)
{
    time_t endwait;
    time_t start = time(NULL);
    time_t seconds = 15; //  s jälkeen lopeta loop

    endwait = start + seconds;
    
    // Setup stuff:
    wiringPiSetupGpio(); // Initialize wiringPi -- using Broadcom pin numbers

    pinMode(merkki, OUTPUT); // led outputiksi
    pinMode(painike, INPUT);     // painike inputiksi
    pinMode(apun, OUTPUT);
    pinMode(akelt, OUTPUT);
    pinMode(avihr, OUTPUT);
    pinMode(jpun, OUTPUT);
    pinMode(jvihr, OUTPUT);
    pinMode(pir, INPUT);      // pir inputiksi
    //pullUpDnControl(butPin, PUD_UP); Enable pull-up resistor on button
    
    int tila = akt; //Init TILA to HIGH 
    
    int state = 0; //lähtötilanteen alustus. tiloja yhteensä 5.
    int napintila = 0; //napin tila 0 eli ei painettu
    
    while(start < endwait)
    {
	napintila = digitalRead(painike); //luetaan napin tila
        
	if(state == 0 && napintila > 0) //nappia painettu niin katsotaan tuleeko autoja
	{
	  digitalWrite(merkki, HIGH); //nappi painettu, merkkivalo päälle
          tila = digitalRead(pir); //luetaan pirin tila, tuleeko liikettä
	  if(tila == 0)
          {
	     printf("ei näy autoja..");
             state = 2;
	  }
	  if(tila==1)
	  {
	    printf("tulee autoja, odotetaan hetki"); 
	    state = 1;
	  }
	 
	} 
	
	//oletustila: autoilijoille vihreä, jalankulkijoille punainen
	if (state == 0)
	{
	 digitalWrite(avihr, HIGH);
	 digitalWrite(akelt, LOW);
	 digitalWrite(apun, LOW);
	 digitalWrite(jpun, HIGH); 
	 digitalWrite(jvihr, LOW);
	}
	
	//odotetaan, kun autoja tulee
	if (state == 1)
	{
	  sleep(5);
	  state = 2;
	}

	//autoilijoille keltainen
	if (state ==2)
	{
	 digitalWrite(avihr, LOW);
	 digitalWrite(akelt, HIGH);
	 sleep(1);
	 state = 3;
	}
	
	//autoilijoille punainen
	if (state == 3)
	{
	 digitalWrite(akelt, LOW);
	 digitalWrite(apun, HIGH);
	 sleep(2);
	 state = 4;
	}

	//jalankulkijoille vihreä
	if (state == 4)
	{
	 digitalWrite(merkki, LOW); //merkkivalo pois päältä
	 digitalWrite(jpun, LOW); 
	 digitalWrite(jvihr, HIGH);
	 sleep(4);
         int count = 4;
         while ( count > 0)
         {
	   digitalWrite(jvihr, HIGH);
	   delay(200);
           digitalWrite(jvihr, LOW);
           delay(200);
           count = count - 1;
           state = 5;
         }
	}
	
	//jalankulkijoille punainen, autoilijoille keltainen
	if (state == 5)
        {
	 digitalWrite(jvihr, LOW);
	 digitalWrite(jpun, HIGH);
	 sleep(2);
	 digitalWrite(akelt, HIGH); //autoille keltainen
	 sleep(1);
	 digitalWrite(apun, LOW);
	 digitalWrite(akelt, LOW);
	 digitalWrite(avihr, HIGH);
	 state = 0; //takasiin oletustilaan
 	}
	
        start = time(NULL);
    }

    //CLEANUP: kaikki inputiksi lopuksi
    pinMode(merkki, INPUT);
    pinMode(painike, INPUT);
    pinMode(apun, INPUT);
    pinMode(akelt, INPUT);
    pinMode(avihr, INPUT);
    pinMode(jpun, INPUT);
    pinMode(jvihr, INPUT);
    pinMode(pir, INPUT);
    
    return 0;
}
