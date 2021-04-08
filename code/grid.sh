#!/bin/bash

SIZE=32x32 # 16x16

# # SMT-CBS
# out="output/smt_cbs.csv";
# rm $out;
# touch $out;
# for i in {2..30..2}
# do
#         echo -n "grid_"$SIZE"_a"$i >> $out
#         for x in {1..6}
#         do
#                 # echo "Runing instance "$i".cpf"
#                 inst="samples/grids/grid_"$SIZE"_a"$i".cpf";
#                 ./smt_cbs $inst 1 1 >> $out;
#         done
#         echo >> $out
# done

# DPLL MAPF DYN
for n in exp # 8_2 10_3
do
        out="output/dpll_mapf_"$n".csv";
        rm $out;
        touch $out;
        for i in {2..30..2}
        do
                echo -n "grid_"$SIZE"_a"$i >> $out
                for x in {1..6}
                do
                        # echo "Runing instance "$i".cpf"
                        inst="samples/grids/grid_"$SIZE"_a"$i".cpf";
                        ./mapf_$n $inst $n 1 >> $out;
                done
                echo >> $out
        done
done

# # DPLL MAPF
# for n in 3 5 10
# do
#         out="output/dpll_mapf_"$n".csv";
#         rm $out;
#         touch $out;
#         for i in {2..30..2}
#         do
#                 echo -n "grid_"$SIZE"_a"$i >> $out
#                 for x in {1..6}
#                 do
#                         # echo "Runing instance "$i".cpf"
#                         inst="samples/grids/grid_"$SIZE"_a"$i".cpf";
#                         ./mapf $inst $n 1 >> $out;
#                 done
#                 echo >> $out
#         done
# done
