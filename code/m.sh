#!/bin/bash

for x in 2 3 4 5
do
        out="samples/grids/dpll_"$x".txt";
        touch $out;
        for i in 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 18 20 22 24 26 28 30
        do
                # echo "Runing instance "$i".cpf"
                inst="samples/maze/maze-32-32-2_a"$i".cpf";
                ./mapf24 $inst >> $out;
        done
        cat $out | grep Time;
        rm $out;
done
