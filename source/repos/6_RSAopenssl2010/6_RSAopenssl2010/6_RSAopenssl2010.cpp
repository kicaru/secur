#pragma comment(lib, "Ws2_32.lib")//system
#pragma comment(lib, "crypt32.lib") //system
#pragma comment(lib, "D:\\1\\openssl-1.1.0f-vs2010\\lib\\libcryptoMT.lib")
#include "pch.h"
#include <iostream>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cstring>
#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/rsa.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <stdio.h>
#include <string>
using namespace std;

int padding = RSA_PKCS1_PADDING;

RSA * createRSA(unsigned char * key, int publickey)
{
	RSA *rsa = NULL;
	BIO *keybio;
	keybio = BIO_new_mem_buf(key, -1);
	if (keybio == NULL)
	{
		printf("Failed to create key BIO");
		return 0;
	}
	if (publickey)
	{
		rsa = PEM_read_bio_RSA_PUBKEY(keybio, &rsa, NULL, NULL);
	}
	else
	{
		rsa = PEM_read_bio_RSAPrivateKey(keybio, &rsa, NULL, NULL);
	}
	if (rsa == NULL)
	{
		printf("Failed to create RSA");
	}

	return rsa;
}

int public_encrypt(unsigned char * data, int data_len, unsigned char * key, unsigned char *encrypted)
{
	RSA * rsa = createRSA(key, 1);
	int result = RSA_public_encrypt(data_len, data, encrypted, rsa, padding);
	return result;
}
int private_decrypt(unsigned char * enc_data, int data_len, unsigned char * key, unsigned char *decrypted)
{
	RSA * rsa = createRSA(key, 0);
	int  result = RSA_private_decrypt(data_len, enc_data, decrypted, rsa, padding);
	return result;
}


int private_encrypt(unsigned char * data, int data_len, unsigned char * key, unsigned char *encrypted)
{
	RSA * rsa = createRSA(key, 0);
	int result = RSA_private_encrypt(data_len, data, encrypted, rsa, padding);
	return result;
}
int public_decrypt(unsigned char * enc_data, int data_len, unsigned char * key, unsigned char *decrypted)
{
	RSA * rsa = createRSA(key, 1);
	int  result = RSA_public_decrypt(data_len, enc_data, decrypted, rsa, padding);
	return result;
}

void printLastError(char *msg[24])
{
	char * err = (char *)malloc(130);;
	ERR_load_crypto_strings();
	ERR_error_string(ERR_get_error(), err);
	printf("%s ERROR: %s\n", msg, err);
	free(err);
}






int main() {

	errno_t err, err1;
	int c, d;
	string privKey;
	string pubKey;
	FILE *fp, *fpub, *encp_txt, *cipher_txt, *in_cipher_txt, *decryp_txt;
	err = fopen_s(&fp, "D:\\1\\openssl-1.1.0f-vs2010\\bin64\\blob.private.key", "r");
	err1 = fopen_s(&fpub, "D:\\1\\openssl-1.1.0f-vs2010\\bin64\\blob.pub.key", "r");
	if (err == 0)
	{
		while ((c = getc(fp)) != EOF) {
			privKey += c;
		}
		fclose(fp);
	}
	if (err1 == 0)
	{
		while ((d = getc(fpub)) != EOF) {
			pubKey += d;
		}
		fclose(fpub);
	}
	char privateKey[3244];
	char publicKey[801];
	strcpy_s(privateKey, privKey.c_str());
	strcpy_s(publicKey, pubKey.c_str());
	char plainText[2048 / 8] = "Hello this is Ravi"; //key length : 2048


	unsigned char  encrypted[4098] = {};
	unsigned char decrypted[4098] = {};
	

	int encrypted_length = public_encrypt((unsigned char *)plainText,
		strlen(plainText),
		(unsigned char *)publicKey,
		(unsigned char *)encrypted);
	printf("Encrypted length =%d\n", encrypted_length);

	int decrypted_length = private_decrypt(encrypted, encrypted_length, (unsigned char *)privateKey, decrypted);
	if (decrypted_length == -1)
	{
		printLastError("Private Decrypt failed ");
		exit(0);
	}
	printf("Decrypted Text =%s\n", decrypted);
	printf("Decrypted Length =%d\n", decrypted_length);


	encrypted_length = private_encrypt((unsigned char *)plainText, strlen(plainText), (unsigned char *)privateKey, encrypted);
	printf("Encrypted length =%d\n", encrypted_length);

	decrypted_length = public_decrypt(encrypted, encrypted_length, (unsigned char *)publicKey, decrypted);
	printf("Decrypted Text =%s\n", decrypted);
	printf("Decrypted Length =%d\n", decrypted_length);

}




