all: programa

programa: itree.o intervalo.o queue.o
	gcc -Wall -Wextra -Werror -g -std=c99 -o interprete interprete.c itree.o intervalo.o queue.o

itree.o: ./ITree/itree.c
	gcc -Wall -Wextra -Werror -g -std=c99 -c ./ITree/itree.c

intervalo.o: ./Intervalo/intervalo.c
	gcc -Wall -Wextra -Werror -g -std=c99 -c ./Intervalo/intervalo.c

queue.o: ./Queue/queue.c
	gcc -Wall -Wextra -Werror -g -std=c99 -c ./Queue/queue.c

clean:
	rm -f programa *.o
