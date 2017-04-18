# docker

### Trucs et astuces ###
- Supprimer tous les conteneurs
```
docker rm $(docker ps -a -q) -f
```
- Supprimer toutes les images
```
docker rmi $(docker images -q) -f
```
- Version du docker-compose
```
docker-compose --version
```
si 1.9 -> docker-compose { version: 2.0 }

- Copie d'un dossier d'un ordi sur RPI:
</br>dans /tmp et IP rpi : 172.31.57.62
```
scp -r ./*  pirate@172.31.57.62:/tmp
```
- Copie d'un dossier d'un RPI sur un ordi:
</br>dans /home/prof/Bureau/Docker-raspberry et IP ordi : 172.31.57.136
```
scp -r ./* prof@172.31.57.136:/home/prof/Bureau/Docker-raspberry
```
