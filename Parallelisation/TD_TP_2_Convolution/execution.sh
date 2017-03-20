#!/bin/bash

#gcc -o convol convol.c -lm

#echo convol >> result.txt

list_nbiters="10 100 1000"
list_np="2 4 8 16 32" 


#for i in `seq 0 4`;
#do
#	for j in $list_nbiters; 
#	do
#		echo $i $j >> result.txt       
#		./convol Sukhothai_4080x6132.ras $i $j >> result.txt
#	done
#done

mpicc -o convol_paral convol_paral.c -lm

echo convol_paral >> result.txt

for k in $list_np; 
do
	for i in `seq 0 4`;
	do
		for j in $list_nbiters; 
		do
			echo $i $j $k >> result.txt       
			mpirun -np $k ./convol_paral Sukhothai_4080x6132.ras $i $j >> result.txt
		done
	done
done

