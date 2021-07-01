main.exe:main.o cJSON.o  skujson.o
	gcc -o main.exe main.o cJSON.o skujson.o
main.o:main.c cJSON.h
	gcc -c main.c
cJSON.o:cJSON.c cJSON.h
	gcc -c cJSON.c

skujson.o:skujson.c 
	gcc -c skujson.c

.PHONY:clean
clean:
	rm *.exe  *.o

