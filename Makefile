io_en_de_test.exe:
	gcc -o io_en_de_test.exe  io_en_de_test.c   -lmcrypt -lcrypto -lmbedtls -lmbedcrypto  -lmbedx509
clean:
	rm -rf io_en_de_test.exe
