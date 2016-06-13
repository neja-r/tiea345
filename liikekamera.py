import RPi.GPIO as GPIO
import time
from time import sleep
import picamera
import datetime

PIR=12
camera = picamera.PiCamera()

GPIO.setmode(GPIO.BCM)
GPIO.setup (PIR, GPIO.IN)

#kuinka kauan otetaan kuvia liiketta havaittaessa
loppu = time.time() + 10

indeksi = 0
while time.time() < loppu:
	if GPIO.input(PIR) == 1:
		#ota kuva jos liiketta
		kuvanimi = 'kuva' + str(indeksi)+'.jpg' #aikaleima kuviin
		camera.capture(kuvanimi)
		indeksi = indeksi + 1
GPIO.cleanup()