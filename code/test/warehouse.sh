#!/bin/bash

out="../output/smt_cbs.csv";
rm $out;
touch $out;
for i in {2..16..2}
do
        echo -n "warehouse_a"$i >> $out
        for _ in {1..10}
        do
                inst="../samples/warehouse/warehouse_a"$i".cpf";
                ./smt_cbs $inst 1 1 >> $out;
        done
        echo >> $out
done

# DPLL MAPF EXP
for n in 1.6 1.4 2
do
        out="../output/dpll_mapf_exp_"$n".csv";
        rm $out;
        touch $out;
        for i in {2..16..2}
        do
                echo -n "warehouse_a"$i >> $out
                for _ in {1..10}
                do
                        inst="../samples/warehouse/warehouse_a"$i".cpf";
                        ./mapf $inst $n 1 1 >> $out;
                done
                echo >> $out
        done
done

# DPLL MAPF Uniform
for n in 10 3 5
do
        out="../output/dpll_mapf_"$n".csv";
        rm $out;
        touch $out;
        for i in {2..16..2}
        do
                echo -n "warehouse_a"$i >> $out
                for _ in {1..10}
                do
                        inst="../samples/warehouse/warehouse_a"$i".cpf";
                        ./mapf $inst $n 1 0 >> $out;
                done
                echo >> $out
        done
done
