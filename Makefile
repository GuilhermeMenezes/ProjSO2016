

main-make: commandlinereader.o contas.o i-banco.o worker.o buffer.o
	gcc -pthread -O4 -o main commandlinereader.o contas.o i-banco.o worker.o buffer.o

commandlinereader.o: commandlinereader.c commandlinereader.h
	gcc -pthread -O4 -Wall -g -c commandlinereader.c

contas.o: contas.c contas.h
	gcc -pthread -O4 -Wall -g -c contas.c

buffer.o: buffer.c buffer.h
	gcc -pthread -O4 -Wall -g -c buffer.c

worker.o: worker.c worker.h
	gcc -pthread -O4 -Wall -g -c worker.c

i-banco.o: i-banco.c contas.h commandlinereader.h buffer.h worker.h
	gcc -pthread -O4 -Wall -g -c i-banco.c

clean:
	rm -f *.o main

