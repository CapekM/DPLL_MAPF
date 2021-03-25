#!/bin/bash

for i in 2 3 4 8 10
do
        # echo "Runing instance "$i".cpf"
        inst="samples/maze/maze-128-128-1_a"$i".cpf";
        ./mapf $inst;
done
