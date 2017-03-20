# TD/TP3 : OpenMP #

cat /proc/cpuinfo
4

gcc -o mandel_openmp mandel.c -lm -fopenmp
export OMP_NUM_THREADS=4


./mandel_openmp 
Usage:
      mandel dimx dimy xmin ymin xmax ymax prof

      dimx,dimy : dimensions de l'image a generer
      xmin,ymin,xmax,ymax : domaine a calculer dans le plan complexe
      prof : nombre maximale d'iteration

Quelques exemples d'execution
      mandel 800 800 0.35 0.355 0.353 0.358 200
      mandel 800 800 -0.736 -0.184 -0.735 -0.183 500
      mandel 800 800 -0.736 -0.184 -0.735 -0.183 300
      mandel 800 800 -1.48478 0.00006 -1.48440 0.00044 100
      mandel 800 800 -1.5 -0.1 -1.3 0.1 10000

Domaine: {[-2,-2]x[2,2]}
Increment : 0.00500626 0.00500626
Prof: 10000
Dim image: 800x800
Temps total de calcul : 17.3403 sec
17.3403



Probleme : Calcul déjà en cours sur l'ordi : MPI

Avec OpenMP


Static

2
4
8
16
32

Dynamic

2
4
8
16
32

Convolution 

export OMP_NUM_THREADS=2
./convol_openmp femme10.ras 4 100
Temps total de calcul : 1.24005 seconde(s) 
export OMP_NUM_THREADS=1
./convol_openmp femme10.ras 4 100
Temps total de calcul : 2.44535 seconde(s) 
export OMP_NUM_THREADS=4
./convol_openmp femme10.ras 4 100
Temps total de calcul : 1.10771 seconde(s) 
export OMP_NUM_THREADS=8
./convol_openmp femme10.ras 4 100
Temps total de calcul : 0.973735 seconde(s) 

