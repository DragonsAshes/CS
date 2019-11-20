main : main.o AlgoGenetique.o
	gcc -Wall $^ -o $@ -lm

main.o : main.c AlgoGenetique.h
	gcc -Wall $< -c -g -lm

AlgoGenetique.o : AlgoGenetique.c 
	gcc -Wall $< -c -g -lm

clean:
	rm -rf *.o main


