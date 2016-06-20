#Lahde: http://docs.opencv.org/3.1.0/d7/d8b/tutorial_py_face_detection.html#gsc.tab=0
import numpy as np
import cv2
import picamera

camera = picamera.PiCamera()

face_cascade = cv2.CascadeClassifier('/home/pi/opencv-3.1.0/data/haarcascades/haarcascade_frontalface_default.xml')  

camera.capture('kasvokuva1.jpg') #Otetaan pikameralla kuva, josta etsitaan kasvot (bonustehtava 8)
#img = cv2.imread('johnnydepp.jpg')
img = cv2.imread('kasvokuva1.jpg')

# Muunna kuva harmaasavyiseksi
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)  

faces = face_cascade.detectMultiScale(gray, 1.3, 5)  
# Tuloksena kasvojen sijainti muodossa (x,y,width,height)

for (x,y,w,h) in faces:
 cv2.rectangle(img,(x,y),(x+w,y+h),(255,0,0),2)
 roi_gray = gray[y:y+h, x:x+w]
 roi_color = img[y:y+h, x:x+w]
     
cv2.imwrite('kasvokuva.png',img) #tallennetaan kuva
cv2.waitKey(0)
