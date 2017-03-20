#!/bin/bash

cd Convolution/
gcc -o convol_openmp convol_openmp.c -lm -fopenmp


echo convol >> result.txt

list_np="1 2 4 8 16 32" 


for j in $list_np; 
do
	export OMP_NUM_THREADS=$j
	echo $j >> result.txt       
	./convol_openmp femme10.ras 4 100 >> result.txt
done

cd ..
cd Mandelbrot/

gcc -o mandel_openmp mandel_openmp.c -lm -fopenmp

echo mandel_openmp >> result.txt

for j in $list_np; 
do
	export OMP_NUM_THREADS=$j
	echo $j >> result.txt       
	./mandel_openmp >> result.txt
done
