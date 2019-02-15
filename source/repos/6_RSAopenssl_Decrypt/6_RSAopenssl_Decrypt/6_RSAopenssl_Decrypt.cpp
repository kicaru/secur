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


#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/rsa.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <stdio.h>
#include <string>
#include <bitset>
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

int public_decrypt(unsigned char * enc_data, int data_len, unsigned char * key, unsigned char *decrypted)
{
	RSA * rsa = createRSA(key, 1);
	int  result = RSA_public_decrypt(data_len, enc_data, decrypted, rsa, padding);
	cout << enc_data << endl;
	cout << data_len << endl;
	cout << decrypted << endl;
	cout << rsa << endl;
	cout << "padding  "<<padding << endl;
	return result;
}


void printLastError(string msg)
{
	char mss[25];
	strcpy_s(mss, msg.c_str());
	char * err = (char *)malloc(130);;
	ERR_load_crypto_strings();
	ERR_error_string(ERR_get_error(), err);
	printf("%s ERROR: %s\n", mss, err);
	free(err);
}


string GetBinaryStringFromHexString(string sHex)
{
	string sReturn = "";
	for (int i = 0; i < sHex.length(); ++i)
	{
		switch (sHex[i])
		{
		case '0': sReturn.append("0000"); break;
		case '1': sReturn.append("0001"); break;
		case '2': sReturn.append("0010"); break;
		case '3': sReturn.append("0011"); break;
		case '4': sReturn.append("0100"); break;
		case '5': sReturn.append("0101"); break;
		case '6': sReturn.append("0110"); break;
		case '7': sReturn.append("0111"); break;
		case '8': sReturn.append("1000"); break;
		case '9': sReturn.append("1001"); break;
		case 'a': sReturn.append("1010"); break;
		case 'b': sReturn.append("1011"); break;
		case 'c': sReturn.append("1100"); break;
		case 'd': sReturn.append("1101"); break;
		case 'e': sReturn.append("1110"); break;
		case 'f': sReturn.append("1111"); break;
		}
	}
	return sReturn;
}



string convertHextochar(string c) {
	string r, a, result;
	a = c;

	char buffer[200];
	string temp;
	for (int i = 0; i < c.length(); i++) {
		r = GetBinaryStringFromHexString(a);
	}
	for (int i = 0; i < r.length(); i += 8) {
		temp = r.substr(i, 8);
		std::bitset<8> foo(temp);
		sprintf_s(buffer, 200, "%c", foo.to_ulong());
		result += buffer;
	}
	return result;
}



int main() {

	errno_t err1, err_in_cipher;
	int d, in_cipher;
	string in_cipher_text;
	string pubKey;
	FILE *fpub, *in_cipher_txt, *decryp_txt;
	err1 = fopen_s(&fpub, "D:\\1\\openssl-1.1.0f-vs2010\\bin64\\blob.pub.key", "r");
	err_in_cipher = fopen_s(&in_cipher_txt, "D:\\RSA\\Ciphertext.txt", "r");
	if (err1 == 0)
	{
		while ((d = getc(fpub)) != EOF) {
			pubKey += d;
		}
		fclose(fpub);
	}
	if (err_in_cipher == 0)
	{
		while ((in_cipher = getc(in_cipher_txt)) != EOF) {
			in_cipher_text += in_cipher;
		}
		fclose(in_cipher_txt);
	}

	char publicKey[801];
	strcpy_s(publicKey, pubKey.c_str());
	unsigned char  encrypted[4098] = {};
	unsigned char decrypted[4098] = {};
	in_cipher_text = convertHextochar(in_cipher_text);
	strcpy_s((char *)encrypted, in_cipher_text.size() + 1, in_cipher_text.c_str());
	int encrypted_length = 512;
	int decrypted_length = public_decrypt(encrypted, encrypted_length, (unsigned char *)publicKey, decrypted);
	if (decrypted_length == -1)
	{
		printLastError("Private Decrypt failed ");
		exit(0);
	}
	printf("Decrypted Text =%s\n", decrypted);
	printf("Decrypted Length =%d\n", decrypted_length);
	fopen_s(&decryp_txt, "D:\\RSA\\Decrypt.txt", "w");
	fwrite(decrypted, sizeof(char), sizeof(decrypted), decryp_txt);
	fclose(decryp_txt);
}



