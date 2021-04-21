for i in {1..16}
do
        # echo "Runing instance "$i".cpf"
        inst="../samples/grid_04x04_a"$i".cpf"
        ./mapf $inst 
done
