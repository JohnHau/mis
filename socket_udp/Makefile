all:server_udp.exe client_udp.exe
CC = gcc
server_udp.exe:server_udp.o  
	$(CC) $^ -o $@	

client_udp.exe:client_udp.o 
	$(CC) $^ -o $@	

%.o:%.c
	$(CC) -c $< -o $@


.PHONY clean:
clean:
	rm -rf server_udp.exe client_udp.exe server_udp.o client_udp.o 
