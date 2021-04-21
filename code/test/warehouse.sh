#!/bin/bash

out="../output/warehouse/smt_cbs.csv";
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
for n in exp_16 exp_14 exp_2
do
        out="../output/warehouse/dpll_mapf_"$n".csv";
        rm $out;
        touch $out;
        for i in {2..16..2}
        do
                echo -n "warehouse_a"$i >> $out
                for _ in {1..10}
                do
                        inst="../samples/warehouse/warehouse_a"$i".cpf";
                        ./mapf_$n $inst 1 1 >> $out;
                done
                echo >> $out
        done
done

# DPLL MAPF LINEAR
for n in 10 # 3 5
do
        out="../output/warehouse/dpll_mapf_"$n".csv";
        rm $out;
        touch $out;
        for i in {2..16..2}
        do
                echo -n "warehouse_a"$i >> $out
                for _ in {1..10}
                do
                        inst="../samples/warehouse/warehouse_a"$i".cpf";
                        ./mapf $inst $n 1 >> $out;
                done
                echo >> $out
        done
done
