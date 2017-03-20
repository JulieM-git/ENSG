# TD/TP2 : Convolution #

```
gcc -o convol convol.c -lm
./convol femme10.ras 4 100
Temps total de calcul : 3.77337 seconde(s) 
```



La convolution est faite plusieurs fois est elles sont dépendante de la précédente.
On stocke la nouvelle convultion pour ne pas ecraser l'image originale.

Paralléliser le calcul sur chaque pixel de la convolution
Pas paral entre elles car dépendance

9 multiplisactions et 8 additions donc o(17)~O(1)
Equilibrage de charge statique

Par ligne

Lecture de l'image
```
Params : tableau [2] contenant les tailles (h,w) de l'image
debut
	si rank == MAITRE alors
		lecture du fichier
		récupération des params
	fin si
	//envoi des params
	MPI_Bcast(params,2, MPI_INT, MAITRE, MPI_COMM_WORLD)
``` 

calcul de h_loc
allocation dynamique de chaque bloc
test de l'allocation dynamique
envoi des blocs d'image aux processus
MPI_SCATTER(ima, w*h/P, MPI_CHAR, ima + (rank > 0 ? w:0, w*h/P, ...))

Se charge de répartir statiquement la charge de travail entre les processus.

Pour la division des blocs : 
Le bloc doit prendre la ligne d'avant et la ligne d'après dans le calcul de la convolution
h_local = h_loc + (1 si 0<rank<p-2 sinon 0) + (1 si 1<rank<p-1 sinon 0)

Allocation de la mémoire
Données r,h,w,rank
Résultat : h_local : hauteur d'un bloc
	ima : pointeur vers le début de l'image

H_local = H_loc + (rank > 0 ? 1:0) + (rank < P-1 ? 1:0)>


Si rank == MAITRE alors
ima = r.data
sinon 
ima = malloc(H_local*w*sizeof(unsigned char))
test d'allocation

Effet de bord : 
Communication entre les ouvriers

Sur ordi :
```
mpirun -np 2 ./convol_paral femme10.ras 4 100
Temps total de calcul de 0: 1.57255 seconde(s) 
Temps total de calcul de 1: 1.57254 seconde(s) 

mpirun -np 4 ./convol_paral femme10.ras 4 100
Temps total de calcul de 3: 0.83973 seconde(s) 
Temps total de calcul de 2: 0.839973 seconde(s) 
Temps total de calcul de 1: 0.840336 seconde(s) 
Temps total de calcul de 0: 0.840347 seconde(s) 

mpirun -np 8 ./convol_paral femme10.ras 4 100
Temps total de calcul de 1: 1.73732 seconde(s) 
Temps total de calcul de 3: 1.74542 seconde(s) 
Temps total de calcul de 2: 1.73753 seconde(s) 
Temps total de calcul de 5: 1.75986 seconde(s) 
Temps total de calcul de 7: 1.81573 seconde(s) 
Temps total de calcul de 6: 1.83598 seconde(s) 
Temps total de calcul de 4: 1.82804 seconde(s) 
Temps total de calcul de 0: 1.84399 seconde(s) 


mpirun -np 16 ./convol_paral femme10.ras 4 100
Temps total de calcul de 1: 2.94194 seconde(s) 
Temps total de calcul de 3: 2.9779 seconde(s) 
Temps total de calcul de 2: 2.9661 seconde(s) 
Temps total de calcul de 5: 3.00194 seconde(s) 
Temps total de calcul de 9: 3.03099 seconde(s) 
Temps total de calcul de 7: 3.05202 seconde(s) 
Temps total de calcul de 6: 3.03207 seconde(s) 
Temps total de calcul de 4: 3.05214 seconde(s) 
Temps total de calcul de 11: 3.0979 seconde(s) 
Temps total de calcul de 10: 3.11008 seconde(s) 
Temps total de calcul de 13: 3.11396 seconde(s) 
Temps total de calcul de 15: 3.13378 seconde(s) 
Temps total de calcul de 14: 3.12995 seconde(s) 
Temps total de calcul de 12: 3.13598 seconde(s) 
Temps total de calcul de 8: 3.16798 seconde(s) 
Temps total de calcul de 0: 3.16615 seconde(s)


mpirun -np 32 ./convol_paral femme10.ras 4 100
Temps total de calcul de 1: 4.18495 seconde(s) 
Temps total de calcul de 3: 4.26893 seconde(s) 
Temps total de calcul de 2: 4.26702 seconde(s) 
Temps total de calcul de 5: 4.32894 seconde(s) 
Temps total de calcul de 7: 4.38587 seconde(s) 
Temps total de calcul de 6: 4.4 seconde(s) 
Temps total de calcul de 4: 4.41992 seconde(s) 
Temps total de calcul de 9: 4.40893 seconde(s) 
Temps total de calcul de 11: 4.49695 seconde(s) 
Temps total de calcul de 13: 4.52498 seconde(s) 
Temps total de calcul de 10: 4.50397 seconde(s) 
Temps total de calcul de 15: 4.54899 seconde(s) 
Temps total de calcul de 14: 4.54102 seconde(s) 
Temps total de calcul de 8: 4.548 seconde(s) 
Temps total de calcul de 12: 4.57195 seconde(s) 
Temps total de calcul de 17: 4.60095 seconde(s) 
Temps total de calcul de 19: 4.7409 seconde(s) 
Temps total de calcul de 18: 4.74796 seconde(s) 
Temps total de calcul de 21: 4.77692 seconde(s) 
Temps total de calcul de 23: 4.82082 seconde(s) 
Temps total de calcul de 22: 4.84797 seconde(s) 
Temps total de calcul de 20: 4.8639 seconde(s) 
Temps total de calcul de 25: 4.85692 seconde(s) 
Temps total de calcul de 27: 4.86094 seconde(s) 
Temps total de calcul de 29: 4.88723 seconde(s) 
Temps total de calcul de 26: 4.89997 seconde(s) 
Temps total de calcul de 31: 4.90482 seconde(s) 
Temps total de calcul de 30: 4.93197 seconde(s) 
Temps total de calcul de 28: 4.96396 seconde(s) 
Temps total de calcul de 24: 4.98391 seconde(s) 
Temps total de calcul de 16: 5.00399 seconde(s) 
Temps total de calcul de 0: 5.03995 seconde(s) 
```

Sur raspberry:
```
mpiexec -np 2 ./convol_paral femme10.ras 4 100
Temps total de calcul de 1: 6.11744 seconde(s) 
Temps total de calcul de 0: 6.11865 seconde(s) 

mpiexec -np 4 ./convol_paral femme10.ras 4 100
Temps total de calcul de 3: 3.12086 seconde(s) 
Temps total de calcul de 2: 3.12179 seconde(s) 
Temps total de calcul de 1: 3.12262 seconde(s) 
Temps total de calcul de 0: 3.12348 seconde(s) 

mpiexec -np 8 ./convol_paral femme10.ras 4 100
Temps total de calcul de 1: 4.16478 seconde(s) 
Temps total de calcul de 3: 4.18549 seconde(s) 
Temps total de calcul de 2: 4.19163 seconde(s) 
Temps total de calcul de 5: 4.1848 seconde(s) 
Temps total de calcul de 7: 4.18429 seconde(s) 
Temps total de calcul de 6: 4.20488 seconde(s) 
Temps total de calcul de 0: 4.22005 seconde(s) 
Temps total de calcul de 4: 4.20996 seconde(s) 

mpiexec -np 16 ./convol_paral femme10.ras 4 100
Temps total de calcul de 1: 4.82252 seconde(s) 
Temps total de calcul de 3: 4.80719 seconde(s) 
Temps total de calcul de 2: 4.8099 seconde(s) 
Temps total de calcul de 5: 4.90746 seconde(s) 
Temps total de calcul de 7: 4.90765 seconde(s) 
Temps total de calcul de 6: 4.92989 seconde(s) 
Temps total de calcul de 4: 4.96991 seconde(s) 
Temps total de calcul de 9: 4.99718 seconde(s) 
Temps total de calcul de 11: 4.98718 seconde(s) 
Temps total de calcul de 10: 5.0299 seconde(s) 
Temps total de calcul de 13: 5.05728 seconde(s) 
Temps total de calcul de 15: 5.1068 seconde(s) 
Temps total de calcul de 14: 5.09002 seconde(s) 
Temps total de calcul de 12: 5.12984 seconde(s) 
Temps total de calcul de 8: 5.10032 seconde(s) 
Temps total de calcul de 0: 5.15975 seconde(s) 

mpiexec -np 32 ./convol_paral femme10.ras 4 100
Temps total de calcul de 1: 8.67345 seconde(s) 
Temps total de calcul de 3: 8.7534 seconde(s) 
Temps total de calcul de 5: 8.78349 seconde(s) 
Temps total de calcul de 2: 8.71989 seconde(s) 
Temps total de calcul de 7: 8.83343 seconde(s) 
Temps total de calcul de 9: 8.94336 seconde(s) 
Temps total de calcul de 6: 8.9247 seconde(s) 
Temps total de calcul de 4: 8.90483 seconde(s) 
Temps total de calcul de 11: 9.04336 seconde(s) 
Temps total de calcul de 10: 9.06994 seconde(s) 
Temps total de calcul de 13: 9.13363 seconde(s) 
Temps total de calcul de 15: 9.19357 seconde(s) 
Temps total de calcul de 14: 9.27982 seconde(s) 
Temps total de calcul de 17: 9.3435 seconde(s) 
Temps total de calcul de 12: 9.35992 seconde(s) 
Temps total de calcul de 19: 9.35349 seconde(s) 
Temps total de calcul de 18: 9.41431 seconde(s) 
Temps total de calcul de 8: 9.36541 seconde(s) 
Temps total de calcul de 21: 9.50346 seconde(s) 
Temps total de calcul de 23: 9.59335 seconde(s) 
Temps total de calcul de 25: 9.68343 seconde(s) 
Temps total de calcul de 22: 9.67395 seconde(s) 
Temps total de calcul de 20: 9.69979 seconde(s) 
Temps total de calcul de 27: 9.75353 seconde(s) 
Temps total de calcul de 26: 9.77985 seconde(s) 
Temps total de calcul de 29: 9.82365 seconde(s) 
Temps total de calcul de 31: 9.73762 seconde(s) 
Temps total de calcul de 30: 9.90007 seconde(s) 
Temps total de calcul de 28: 9.89979 seconde(s) 
Temps total de calcul de 24: 9.90987 seconde(s) 
Temps total de calcul de 16: 10 seconde(s) 
Temps total de calcul de 0: 9.98972 seconde(s) 
```

Communications bloquantes : les envois et les receptions des lignes (manquantes) sont réalisés par des fonctions bloquantes (MPI_Send(), MPI_receive()) c'est-à-dire le processus reste bloqué tant qu'il n'a pas reçu toutes les données attendues ou qu'il n'y a pas envoyé toutes les données.
Communication non-bloquantes (Amélioration): on peut commencer le calcul de la convolution de la grande partie de l'image locole en attendant la reception des lignes manquantes.


pour i de 0 à nbiter faire
si rank > 0 faire
envoyer la ligne 1 et 2 au processus précédent
fin si
si rank < P-1 > faire
envoyer la ligne h_loc - 2 h_loc - 3 au processus suivant
fin si
faire la convolution du bloc (qui va de la ligne 1 à h_loc - 1)
si rank > 0 faire 
recevoir la ligne 0 et 1 du processus précédent
fin si
si rank < P-1 > faire
recevoir la ligne h_loc - 1 et h_loc - 2 du processus suivant
fin si
faire la convolution de la première ligne 
faire la convolution de la dernière ligne
fin pour

