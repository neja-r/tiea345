#!/bin/bash
#Skripti, joka ottaa kuvan aikaleimalla
#Muokkasin configuration tiedostoa kutsumalla komentorivilla crontab -e
#Tahan tiedostoon kirjoitin seuraavan rivin:
# 0 * * * * /home/pi/kuvatasatunti.sh
#Talla tavalla sain kameran ottamaan kuvan aina tasatunnein automaattisesti
DATE=$(date +"%Y-%m-%d_%H%M")

raspistill -vf -hf -o /home/pi/$DATE.jpg
