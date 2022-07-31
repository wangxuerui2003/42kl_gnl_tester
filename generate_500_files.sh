for ((i = 1; i <= 500; i++))
do
	cat /usr/share/dict/words | sort -R | head -10 > random_tests/"$i"
done
