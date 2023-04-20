all:server_tcp.exe client_tcp.exe
CC = gcc
server_tcp.exe:server_tcp.o  
	$(CC) $^ -o $@	

client_tcp.exe:client_tcp.o 
	$(CC) $^ -o $@	

%.o:%.c
	$(CC) -c $< -o $@


.PHONY clean:
clean:
	rm -rf server_tcp.exe client_tcp.exe server_tcp.o client_tcp.o 
