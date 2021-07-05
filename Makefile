main.exe:main.o cJSON.o  skujson.o io_json.o
	gcc -o main.exe main.o cJSON.o skujson.o io_json.o
main.o:main.c cJSON.h
	gcc -c main.c
cJSON.o:cJSON.c cJSON.h
	gcc -c cJSON.c

skujson.o:skujson.c 
	gcc -c skujson.c

io_json.o:io_json.c 
	gcc -c io_json.c
.PHONY:clean
clean:
	rm *.exe  *.o

