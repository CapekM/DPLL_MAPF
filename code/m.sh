#!/bin/bash

for n in 3 5 10
do
        out="output/maze/dpll_mapf_"$n".csv";
        rm $out;
        touch $out;
        for i in 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 18 20 22 24 26 28 30
        do
                echo -n "maze-32-32-2_a"$i >> $out
                for x in {1..6}
                do
                        # echo "Runing instance "$i".cpf"
                        inst="samples/maze/maze-32-32-2_a"$i".cpf";
                        ./mapf $inst $n 1 >> $out;
                done
                echo >> $out
        done
done
