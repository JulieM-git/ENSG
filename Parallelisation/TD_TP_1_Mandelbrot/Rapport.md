# TD/TP1 : Ensemble de Mandelbrot #

### Question 1 ###

Les indices pour parcourir les pixels de l'image sont : 
- i de 0 à H-1
- j de 0 à W-1

Il y a une allocation de la mémoire de : H*W*Tpixel
On calcule pixel par pixel, qui est codé sur 8 bits car c'est un unsigned char (1 octet). On est en noir et blanc;
Le calcul s'effectue dan sle plan complexe, on associe une coordonnée (x,y) à chaque pixel.

### Question 2 ###

Compilation et exécution : 
```sh
gcc -o Mandel mandel.c -lm; ./Mandel
```

Exécution avec des paramètres : 
```sh
./Mandel h w xmin ymin xmax ymax profondeur
```


### Question 3 ###

Le calcul aux différentes profondeurs (fonction xy2color) n'est pas parallélisable, puisque la valeur d'un pixel à la profondeur n+1 est une fonction complexe de la valeur de ce pixel à la profondeur n ( la valeur à la profondeur n+1 écrase en mémoire celle à la profondeur n). En revanche, chaque pixel de l'image subit le même traitement (les 2 boucles for embriquées) qui ne dépend pas de la valeur d'autres pixels. Cette partie est parallélisable.

Nous allons découper le tableau en fonction du nombre de processeur. Il faut s'intérresser à quel rang va commencer le traitement ainsi que la taille.

##### Architecture des processeurs à mémoire distribuée : #####

Si P : nombre de processus
h_local = H/P, si n'est pas entier
	si H[P] différent de 0 alors on sort du programme et on demande un autre P
Par choix on découpe suivant la hauteur. La largeur reste la même. Le tableau est rangé par ligne dans la mémoire, c'est un choix de facilité et d'optimisation.

Xinc et Yinc ne change pas pendant l'exécution, ils dépendent des paramètres d'entrée.
En découpant, Ymin change en Ymin_loc pour chaque processus et X min reste le même.
Ymin_loc = Ymin * rank * Yinc

Données : 
H : Hauteur tableau
W : largeur tableau
rank : rang du processus
H_local : hauteur d'un bloc
```
Si rank == MAITRE 
alors pima = ima = malloc(w*h*sizeof(unsigned char));
sinon pima = ima = malloc(w*h_local*sizeof(unsigned char));
```
Algo du Maitre
```
si rank == MAITRE
alors 
//allocation dynamique de l'image global
//test de l'allocation
//calcul de la position du début de l'image local du maitre pima <- rank*w*H_local>
```

Algo Envoi
```
Si rank == MAITRE
alors pour tous les ouvriers
//attente d'un message
MPI_Probe();
s = 

si s == MAITRE
alors 
//assemblage des bloc
MPI_Recv()
fin si

sinon 
MPI_Send()
fin si
```


Commandes : 
```sh
mpicc -o mandel_paral mandel_paral.c -lm
mpirun -np 4 ./mandel_paral
```

Sur ordi :
```sh
mpirun -np 2 ./mandel_paral
Temps total de calcul : 1.53169 sec
mpirun -np 4 ./mandel_paral
Temps total de calcul : 1.53605 sec
mpirun -np 8 ./mandel_paral
Temps total de calcul : 1.38156 sec
mpirun -np 16 ./mandel_paral
Temps total de calcul : 1.84954 sec
```

Copier un fichier sur un raspberry:
```sh
scp -r -p source user@serveur:/home/pi/destination
```


Connexion des Raspberry entre eux 

https://www.raspberrypi.org/documentation/remote-access/ssh/passwordless.md
http://raspberrypi.stackexchange.com/questions/1686/how-do-i-set-up-ssh-keys-to-log-into-my-rpi
```
ssh-keygen -t dsa
ssh-copy-id -i ~/.ssh/id_dsa.pub pi@piensg005
```

Sur raspberry :

```sh
Domaine: {[-2,-2]x[2,2]}
Increment : 0.00500626 0.00500626
Prof: 10000
Dim image: 800x800
```

```sh
mpiexec -np 4 ./mandel_paral

Temps total de calcul : 0.0415709 sec
Temps total de calcul : 9.45125 sec
Temps total de calcul : 9.56446 sec
Temps total de calcul : 9.5655 sec
```

```sh
mpiexec -np 8 ./mandel_paral

Temps total de calcul : 0.270028 sec
Temps total de calcul : 0.253835 sec
Temps total de calcul : 0.289698 sec
Temps total de calcul : 3.14804 sec
Temps total de calcul : 3.31648 sec
Temps total de calcul : 14.7327 sec
Temps total de calcul : 15.4475 sec
Temps total de calcul : 15.4195 sec
```

```sh
mpiexec -np 2 ./mandel_paral

Temps total de calcul : 9.48552 sec
Temps total de calcul : 9.48569 sec
```

```sh
mpiexec -np 16 ./mandel_paral

Temps total de calcul : 0.380733 sec
Temps total de calcul : 0.378004 sec
Temps total de calcul : 0.376818 sec
Temps total de calcul : 0.434868 sec
Temps total de calcul : 0.443689 sec
Temps total de calcul : 0.422737 sec
Temps total de calcul : 0.472882 sec
Temps total de calcul : 0.868729 sec
Temps total de calcul : 1.15343 sec
Temps total de calcul : 5.56303 sec
Temps total de calcul : 5.87968 sec
Temps total de calcul : 12.4698 sec
Temps total de calcul : 12.529 sec
Temps total de calcul : 19.0554 sec
Temps total de calcul : 19.2067 sec
Temps total de calcul : 19.2355 sec
```

```sh
mpiexec -np 1 ./mandel_paral

Temps total de calcul : 18.8605 sec
``` 

```sh
mpiexec -np 32 ./mandel_paral
Temps total de calcul : 19.8775 sec


Sans les printf: Temps équivalent
```

Contraintes : 
Travail à plusieurs sur les raspberry
moins puissant qu'un ordi

En mode débug: 
```sh
mpirun -np 4 xterm -e gdb ./mandel_dyn
```

##### Architecture des processeurs à répartition dynamique des charges : ##### 

Pas la même charge de travaille : la partie centrale travaille plus.
MAITRE ne travaille pas et à le role du chef, envoie le travail aux esclaves.
Le processus MAITRE devrait recevoir les lignes traitées par les ouvriers et sibesoin de leur envoyer de nouveau d'autres lignes à traiter.
Le nombre de blocs est un argument du programme, caractérisé par le nombre de lignes à traiter.
A chaque fois qu'un ouvrier finit une portion de calcul à traîter, il l'envoie au MAITRE qui devrait le mettre au bon endroit.

Algo Maitre

- allocation dynamique de l'image globale
- test de l'allocation dynamique
Pour i de 0 à nb_proc faire
Si i != MAITRE
- on envoie au esclave de rang i num_bloc
-on incrémente num_bloc

Pour i de 0 à h/nb_lignes 
- on recoit le numéro du bloc fait par l'ouvrier
- on détermine le rang de l'émetteur
- on recoit le calcul
- test de fin de l'image
	- s'il reste de calcul à faire ou encore un numéro de bloc à calculer au ouvrier (qui a envoyé le calcul)
	- sinon on envoie un message en indiquant la fin du travail

2
Rang 0 | Temps total de calcul : 18.8841 sec
Rang 1 | Temps total de calcul : 18.8841 sec


4
Rang 1 | Temps total de calcul : 6.33867 sec
Rang 3 | Temps total de calcul : 6.33677 sec
Rang 0 | Temps total de calcul : 6.36012 sec
Rang 2 | Temps total de calcul : 6.36196 sec

8
Rang 4 | Temps total de calcul : 5.61404 sec
Rang 2 | Temps total de calcul : 5.63944 sec
Rang 5 | Temps total de calcul : 5.62283 sec
Rang 3 | Temps total de calcul : 5.6264 sec
Rang 6 | Temps total de calcul : 5.61745 sec
Rang 7 | Temps total de calcul : 5.62684 sec
Rang 0 | Temps total de calcul : 5.69873 sec
Rang 1 | Temps total de calcul : 5.69873 sec


16
Rang 8 | Temps total de calcul : 5.33621 sec
Rang 14 | Temps total de calcul : 5.28943 sec
Rang 7 | Temps total de calcul : 5.38163 sec
Rang 9 | Temps total de calcul : 5.36378 sec
Rang 6 | Temps total de calcul : 5.43166 sec
Rang 5 | Temps total de calcul : 5.44604 sec
Rang 1 | Temps total de calcul : 5.55885 sec
Rang 15 | Temps total de calcul : 5.52849 sec
Rang 2 | Temps total de calcul : 5.61659 sec
Rang 12 | Temps total de calcul : 5.60953 sec
Rang 13 | Temps total de calcul : 5.60347 sec
Rang 3 | Temps total de calcul : 5.66156 sec
Rang 11 | Temps total de calcul : 5.64777 sec
Rang 10 | Temps total de calcul : 5.76604 sec
Rang 0 | Temps total de calcul : 5.95502 sec
Rang 4 | Temps total de calcul : 5.90874 sec

32
Rang 21 | Temps total de calcul : 4.87835 sec
Rang 14 | Temps total de calcul : 4.96605 sec
Rang 23 | Temps total de calcul : 4.94374 sec
Rang 20 | Temps total de calcul : 4.96719 sec
Rang 31 | Temps total de calcul : 4.92732 sec
Rang 18 | Temps total de calcul : 4.99209 sec
Rang 30 | Temps total de calcul : 4.94877 sec
Rang 15 | Temps total de calcul : 5.01801 sec
Rang 29 | Temps total de calcul : 4.97739 sec
Rang 2 | Temps total de calcul : 5.12677 sec
Rang 19 | Temps total de calcul : 5.10957 sec
Rang 17 | Temps total de calcul : 5.19229 sec
Rang 22 | Temps total de calcul : 5.23714 sec
Rang 27 | Temps total de calcul : 5.22666 sec
Rang 11 | Temps total de calcul : 5.28394 sec
Rang 24 | Temps total de calcul : 5.31219 sec
Rang 25 | Temps total de calcul : 5.36653 sec
Rang 26 | Temps total de calcul : 5.68716 sec
Rang 28 | Temps total de calcul : 5.66304 sec
Rang 16 | Temps total de calcul : 6.6346 sec
Rang 1 | Temps total de calcul : 6.69792 sec
Rang 3 | Temps total de calcul : 6.90212 sec
Rang 13 | Temps total de calcul : 6.88613 sec
Rang 12 | Temps total de calcul : 7.1387 sec
Rang 4 | Temps total de calcul : 7.22854 sec
Rang 10 | Temps total de calcul : 7.29178 sec
Rang 5 | Temps total de calcul : 7.31189 sec
Rang 6 | Temps total de calcul : 7.49401 sec
Rang 9 | Temps total de calcul : 7.59892 sec
Rang 0 | Temps total de calcul : 7.7279 sec
Rang 8 | Temps total de calcul : 7.74399 sec
Rang 7 | Temps total de calcul : 7.76593 sec




 

