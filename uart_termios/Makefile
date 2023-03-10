all:uread.exe uwrite.exe
CC = gcc
uread.exe:uread.o uart_tios.o 
	$(CC) $^ -o $@	

uwrite.exe:uwrite.o uart_tios.o 
	$(CC) $^ -o $@	

%.o:%.c
	$(CC) -c $< -o $@


.PHONY clean:
clean:
	rm -rf uread.exe uwrite.exe uread.o uwrite.o uart_tios.o
