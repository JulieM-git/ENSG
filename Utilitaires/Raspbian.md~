# Installer raspbian sur Raspberry #

Sur Linux:

## Installation ##

- Télécharger l'image sur : 
https://www.raspberrypi.org/downloads/raspbian/

- Raspbian Jessie Lite en Zip
- De-zipper le dossier : récupérer l'image


Tutoriel d'installation de l'image: https://www.raspberrypi.org/documentation/installation/installing-images/linux.md

Mettre le carte SD sur un lecteur de carte SD sur l'ordi

```sh
df -h
```
Récupérer le nom de la carte SD : /dev/sdX ou /dev/mmcblk0  (un truc dans le genre)

Interface graphique de gestion de partition : GParted

Etape 1 : sélectionner le bon disque/carte SD (en haut à droite)
Etape 2 : sélectionner toutes les partitions présentes dans la liste et supprimer les (avec "Supprimer la partition sélectionnée)

```sh
dd bs=4M if=2017-02-16-raspbian-jessie.img of=/dev/sdX
```

Récupérer la carte SD et la mettre sur le RaspberryPi

Brancher et connecter au raspberry l'écran, le réseau et le clavier.

Attention : le clavier est en qwerty par défaut

## Configuration ##

Tutoriel de configuration : https://www.raspberrypi.org/documentation/configuration/raspi-config.md
```sh
sudo raspi-config
```
- Configuration du clavier : http://www.soft-alternative.com/raspberry-pi-configurer-clavier-francais-raspbian.php ou https://raspbian-france.fr/installer-raspbian-premier-demarrage-configuration/
- Activer le ssh : https://www.raspberrypi.org/documentation/remote-access/ssh/

## Proxy de l'école ##
```sh
cd /etc/apt/apt.conf.d/ 
echo 'Acquire::http::Proxy "http://10.0.4.2:3128";' >> 10proxy
echo 'Acquire::https::Proxy "https://10.0.4.2:3128";' >> 10proxy
echo 'Acquire::ftp::Proxy "ftp://10.0.4.2:3128";' >> 10proxy
sudo apt-get update
```

#### Possible problème ####
Si internet ne fonctionne pas encore, ajouter dans ~/.bashrc :
export http_proxy="http://10.0.4.2:3128"
export https_proxy="https://10.0.4.2:3128"
export ftp_proxy="ftp://10.0.4.2:3128"
```sh
cd ~/
source .bashrc
```

