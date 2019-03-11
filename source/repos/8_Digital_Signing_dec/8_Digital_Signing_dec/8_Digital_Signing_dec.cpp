// 8_Digital_Signing_enc.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#define _CRT_SECURE_NO_WARNINGS
//#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <openssl/md5.h>
#include <iostream>
#include <cstdio>
#include <string>
#include <fstream>
#include <conio.h>
#include <cstdlib>
#include <sstream>
#include <math.h>
#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/rsa.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/err.h>
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

int public_encrypt(unsigned char * data, int data_len, unsigned char * key, unsigned char *encrypted)
{
	padding = 1;
	RSA * rsa = createRSA(key, 1);
	int result = RSA_public_encrypt(data_len, data, encrypted, rsa, padding);
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

int private_decrypt(unsigned char * enc_data, int data_len, unsigned char * key, unsigned char *decrypted)
{
	RSA * rsa = createRSA(key, 0);
	int  result = RSA_private_decrypt(data_len, enc_data, decrypted, rsa, padding);
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

string MD5encrypt(string txt) {
	unsigned char digest[16];
	char string[100];
	char mdString[67];
	strcpy_s(string, txt.c_str());

	MD5_CTX context;
	MD5_Init(&context);
	MD5_Update(&context, string, strlen(string));
	MD5_Final(digest, &context);
	for (int i = 0; i < 16; i++) {
		sprintf_s(&mdString[i * 2], 34, "%02x", (unsigned int)digest[i]);
	}
	return mdString;
}



int main()
{
	errno_t err, err1;
	int c, d;
	string cipher_text;
	string privKey;
	string in_cipher_text;
	string pubKey;
	FILE *fp, *fpub, *cipher_txt;
	err = fopen_s(&fp, "C:\\openssl-1.1.0f-vs2017\\bin64\\blob.private.key", "r");
	err1 = fopen_s(&fpub, "C:\\openssl-1.1.0f-vs2017\\bin64\\blob.pub.key", "r");
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
	
	
	//cout << in_cipher_text.size() << endl;
	char privateKey[5000];
	char publicKey[900];
	strcpy_s(privateKey, privKey.c_str());
	strcpy_s(publicKey, pubKey.c_str());
	char CipherText[1024 * 10];
	unsigned char  encrypted[1024 * 10] = { };
	unsigned char decrypted[1024 * 10] = {};
	char buffer[100];
	int j;
	fopen_s(&cipher_txt, "D:\\Digital_signature\\Ciphertext.txt", "r");
	//cipher_txt = fopen("D:\\Digital_signature\\Ciphertext.txt", "r");
	while (1) {
		j = fgetc(cipher_txt);
		if (feof(cipher_txt)) {
			break;
		}
		in_cipher_text += j;
		printf("%c", j);
	}
	cout << endl;
	fclose(cipher_txt);
	cout <<"test string : "<< in_cipher_text << endl;
	in_cipher_text = convertHextochar(in_cipher_text);
	strcpy_s(CipherText, in_cipher_text.c_str());
	//cout << CipherText << endl;
	int encrypted_length = 512;
	int decrypted_length = public_decrypt((unsigned char *)CipherText, encrypted_length, (unsigned char *)publicKey, (unsigned char *)decrypted);
	if (decrypted_length == -1)
	{
		printLastError("Private Decrypt failed ");
		exit(0);
	}
	
	printf("Decrypted Text =%s\n", decrypted);
	string r;
	unsigned char *pd = decrypted;
}