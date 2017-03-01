# TP 

JMarcuzzi

Avec : 
</br>CParisel
</br>RMaziere

Composants utilisés :

- Raspberry pi 2
- Camera : http://www.pihomeserver.fr/2014/01/09/raspberry-pi-home-server-installer-facilement-la-camera-raspberry-pi/
- Pololu Proximity Sensor: https://www.pololu.com/product/2578
	- OUT sur la pin 22
	- VDD sur 3,3 V ou 5 VDD
	- GND sur ground

Ligne de commande pour compiler et lancer le programme : 

```sh
gcc -o detect_cam detect_cam.c -l bcm2835; ./detect_cam
```
