#!/bin/bash

out="../output/smt_cbs.csv";
rm $out;
touch $out;
for i in {2..30..2}
do
        echo -n "maze-32-32-2_a"$i >> $out
        for  _ in {1..10}
        do
                # echo "Runing instance "$i".cpf"
                inst="../samples/maze/maze-32-32-2_a"$i".cpf";
                ./smt_cbs $inst 1 1 >> $out;
        done
        echo >> $out
done

# DPLL MAPF DYN
for n in 1.6 1.4 2
do
        out="../output/dpll_mapf_exp_"$n".csv";
        rm $out;
        touch $out;
        for i in {2..30..2}
        do
                echo -n "maze-32-32-2_a"$i >> $out
                for  _ in {1..10}
                do
                        # echo "Runing instance "$i".cpf"
                        inst="../samples/maze/maze-32-32-2_a"$i".cpf";
                        ./mapf $inst $n 1 1 >> $out;
                done
                echo >> $out
        done
done

# DPLL MAPF Uniform
for n in 3 5 10
do
        out="../output/dpll_mapf_"$n".csv";
        rm $out;
        touch $out;
        for i in {2..30..2}
        do
                echo -n "maze-32-32-2_a"$i >> $out
                for  _ in {1..10}
                do
                        # echo "Runing instance "$i".cpf"
                        inst="../samples/maze/maze-32-32-2_a"$i".cpf";
                        ./mapf $inst $n 1 0 >> $out;
                done
                echo >> $out
        done
done
