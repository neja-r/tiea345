import RPi.GPIO as GPIO
import time

#autojen valot
PUN=26
KELT=19
VIHR=13
#jalankulkijoiden valot
JPUN=6
JVIHR=5
MERKKI=20 #keltainen merkkivalo
PAINIKE=21
PIR=12

GPIO.setmode (GPIO.BCM)

GPIO.setup (PUN, GPIO.OUT)
GPIO.setup (KELT, GPIO.OUT)
GPIO.setup (VIHR, GPIO.OUT)
GPIO.setup (JPUN, GPIO.OUT)
GPIO.setup (JVIHR, GPIO.OUT)
GPIO.setup (MERKKI, GPIO.OUT)
GPIO.setup (PAINIKE, GPIO.IN)
GPIO.setup (PIR, GPIO.IN)

# kuinka kauan pyoritetaan ohjelmaa
LOPPU = time.time() + 30

# lahtotilanteen alustus
TILA = 0
NAPPI = 0

while time.time() < LOPPU:

	# lue jalankulkijapainikkeen tila
	NAPPI = GPIO.input (PAINIKE)
	time.sleep (0.1)

	# jos painike painettu oletustilassa (0) niin siirrytään seuraavaan tilaan
	if TILA == 0 and NAPPI > 0:
		GPIO.output(MERKKI,1) #merkkivalo paalle
		if GPIO.input(PIR) == 0: #jos ei liiketta
			print u"ei nay autoja"
			TILA = 2
		if GPIO.input(PIR) == 1: #jos on liiketta
			print u"autoja tulee... odotetaan"
			TILA = 1

	# oletustila: autoilijoille vihrea, jalankulkijoille punainen, merkkivalo ei pala
	if TILA == 0:
		GPIO.output (PUN, 0)
		GPIO.output (KELT, 0)
		GPIO.output (VIHR, 1)
		GPIO.output (JPUN, 1)
		GPIO.output (JVIHR, 0)
		GPIO.output (MERKKI, 0)

	# odotetaan kun autoja tulee
	if TILA == 1:
		time.sleep (5)
		TILA = 2

	# autoille keltainen
	if TILA == 2:
		GPIO.output (VIHR, 0)
		GPIO.output (KELT, 1)
		time.sleep (1)
		TILA = 3

	# punainen kaikille
	if TILA == 3:
		GPIO.output (KELT, 0)
		GPIO.output (PUN, 1)
		time.sleep (3)
		TILA = 4

	# vihrea jalankulkijoille
	if TILA == 4:
		GPIO.output (MERKKI, 0) #merkkivalo pois päältä
		GPIO.output (JPUN, 0)
		GPIO.output (JVIHR, 1)
		time.sleep (4)
		count = 3
		while count > 0: #vilkutetaan lopussa
			GPIO.output (JVIHR, 0)
			time.sleep (0.5)
			GPIO.output (JVIHR, 1)
			time.sleep (0.5)
			count = count - 1
		TILA = 5

	# punainen kaikille
	if TILA == 5:
		GPIO.output (JVIHR, 0)
		GPIO.output (JPUN, 1)
		time.sleep (3)
		TILA = 6

	# autoille vihrea palaa alkutilaan
	if TILA == 6:
		GPIO.output (KELT, 1)
		time.sleep (1)
		GPIO.output (PUN, 0)
		GPIO.output (KELT, 0)
		GPIO.output (VIHR, 1)
		TILA = 0

GPIO.cleanup ()
