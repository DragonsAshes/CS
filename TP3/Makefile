main : main.o fat.o
	gcc -Wall $^ -o $@ -lm

main.o : main.c fat.h
	gcc -Wall $< -c -g -lm

fat.o : fat.c 
	gcc -Wall $< -c -g -lm

clean:
	rm -rf *.o main


