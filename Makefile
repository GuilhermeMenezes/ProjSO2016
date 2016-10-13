

main: commandlinereader.o contas.o i-banco.o
	gcc -O4 -o main commandlinereader.o contas.o i-banco.o 

commandlinereader.o: commandlinereader.c commandlinereader.h
	gcc -O4 -Wall -g -c commandlinereader.c

contas.o: contas.c contas.h
	gcc -O4 -Wall -g -c contas.c

i-banco.o: i-banco.c contas.h commandlinereader.h
	gcc -O4 -Wall -g -c i-banco.c

clean:
	rm -f *.o main

