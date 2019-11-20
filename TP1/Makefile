main : main.o fonctions.o
	gcc -Wall $^ -o $@ -lm

main.o : main.c fonctions.h
	gcc -Wall $< -c -lm

fonctions.o : fonctions.c 
	gcc -Wall $< -c -lm

clean:
	rm -rf *.o main


