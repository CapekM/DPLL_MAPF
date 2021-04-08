#!/bin/bash

out="output/maze/smt_cbs.csv";
rm $out;
touch $out;
for i in {2..30..2}
do
        echo -n "maze-32-32-2_a"$i >> $out
        for x in {1..6}
        do
                # echo "Runing instance "$i".cpf"
                inst="samples/maze/maze-32-32-2_a"$i".cpf";
                ./smt_cbs $inst 1 1 >> $out;
        done
        echo >> $out
done

for n in 3 5 10
do
        out="output/maze/dpll_mapf_"$n".csv";
        rm $out;
        touch $out;
        for i in {2..30..2}
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
