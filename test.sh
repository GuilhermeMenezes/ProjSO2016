set -m

f1() {
	echo creditar 1 100
	echo simular 100
	sleep 3
	echo sair agora
	sleep 100
}

make
./main &
echo $(f1) > %main

read x
