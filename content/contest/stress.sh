set -e
./c gen > in.txt
./c real < in.txt > real.out
./c brute < in.txt > brute.out
for ((i = 1; ; i++)); do
    echo $i
    ./gen > in.txt
    ./real <in.txt> real.out
    ./brute <in.txt> brute.out
    diff -w real.out brute.out || break
done