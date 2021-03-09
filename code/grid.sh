#!/bin/bash

for x in 2 3 4 5
do
        out="samples/grids/dpll_24_"$x".txt";
        touch $out;
        for i in {2..30..2}
        do
                # echo "Runing instance "$i".cpf"
                inst="samples/grids/grid_16x16_a"$i".cpf";
                ./smt-cbs $inst >> $out;
        done
        cat $out | grep Time;
        rm $out;
done
