#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * MCrypt API available online:
 * http://linux.die.net/man/3/mcrypt
 */
#include <mcrypt.h>

#include <math.h>
#include <stdint.h>
#include <stdlib.h>

int encrypt(
		void* buffer,
		int buffer_len, /* Because the plaintext could include null bytes*/
		char* IV, 
		char* key,
		int key_len 
	   ){
	MCRYPT td = mcrypt_module_open("rijndael-128", NULL, "cbc", NULL);
	//MCRYPT td = mcrypt_module_open("rijndael-128", NULL, "ecb", NULL);
	int blocksize = mcrypt_enc_get_block_size(td);
	if( buffer_len % blocksize != 0 ){return 1;}

	mcrypt_generic_init(td, key, key_len, IV);
	mcrypt_generic(td, buffer, buffer_len);
	mcrypt_generic_deinit (td);
	mcrypt_module_close(td);

	return 0;
}

int decrypt(
		void* buffer,
		int buffer_len,
		char* IV, 
		char* key,
		int key_len 
	   ){
	MCRYPT td = mcrypt_module_open("rijndael-128", NULL, "cbc", NULL);
	int blocksize = mcrypt_enc_get_block_size(td);
	if( buffer_len % blocksize != 0 ){return 1;}

	mcrypt_generic_init(td, key, key_len, IV);
	mdecrypt_generic(td, buffer, buffer_len);
	mcrypt_generic_deinit (td);
	mcrypt_module_close(td);

	return 0;
}

void display(char* ciphertext, int len){
	int v;
	for (v=0; v<len; v++){
		//printf("%d ", ciphertext[v]);
		printf("%#02x ", ciphertext[v]);
	}
	printf("\n");
}


uint8_t keyAes128[] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
	               0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};

uint8_t plainAes128[] = {0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96,
	                 0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a};

uint8_t cipherAes128[] = {0x3a, 0xd7, 0x7b, 0xb4, 0x0d, 0x7a, 0x36, 0x60,
	                  0xa8, 0x9e, 0xca, 0xf3, 0x24, 0x66, 0xef, 0x97};

uint8_t ive[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
	         0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};

int mencrypt(
		void* buffer,
		int buffer_len, /* Because the plaintext could include null bytes*/
		char* IV, 
		char* key,
		int key_len 
	    ){
	MCRYPT td = mcrypt_module_open("rijndael-128", NULL, "ecb", NULL);
	int blocksize = mcrypt_enc_get_block_size(td);
	if( buffer_len % blocksize != 0 ){return 1;}

	mcrypt_generic_init(td, key, key_len, NULL);
	mcrypt_generic(td, buffer, buffer_len);
	mcrypt_generic_deinit (td);
	mcrypt_module_close(td);

	return 0;
}


int main()
{
	MCRYPT td, td2;
	char * plaintext = "test text 123";
	char* IV = "AAAAAAAAAAAAAAAA";
	char *key = "0123456789abcdef";
	int keysize = 16; /* 128 bits */
	char* buffer;
	int buffer_len = 16;

	buffer = calloc(1, buffer_len);
	//strncpy(buffer, plaintext, buffer_len);
	strncpy(buffer, plainAes128, buffer_len);

	printf("==C==\n");
	//printf("plain:   %s\n", plaintext);
//	encrypt(buffer, buffer_len, IV, key, keysize); 
	encrypt(buffer, buffer_len, ive, keyAes128, keysize); 
	//mencrypt(buffer, buffer_len, NULL, keyAes128, keysize); 

	printf("cipher:  "); display(buffer , buffer_len);
	//decrypt(buffer, buffer_len, IV, key, keysize);
	//printf("decrypt: %s\n", buffer);

	return 0;
}
