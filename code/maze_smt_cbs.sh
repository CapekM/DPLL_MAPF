#!/bin/bash

out="output/dpll.csv";
rm $out;
touch $out;
for i in {2..30..2}
do
        echo -n "maze-32-32-2_a"$i >> $out
        for x in {1..6}
        do
                # echo "Runing instance "$i".cpf"
                inst="samples/maze/maze-32-32-2_a"$i".cpf";
                ./mapf $inst 1 1 >> $out;
        done
        echo >> $out
done
