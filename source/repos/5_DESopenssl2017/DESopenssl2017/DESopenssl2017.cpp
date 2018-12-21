#pragma comment(lib, "Ws2_32.lib")//system
#pragma comment(lib, "crypt32.lib") //system
#pragma comment(lib, "D:\\1\\openssl-1.1.0f-vs2010\\lib\\libcryptoMT.lib")
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/des.h>
#include <openssl/rand.h>
#include <winsock2.h>
#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>
#define BUFSIZE 1024*64
using namespace std;


int main()
{

	ifstream mykey;
	mykey.open("D:\mykey.txt");
	ofstream encyptfile("D:\DES_encypt.txt");
	std::string line;
	unsigned int Hkey;
	if (mykey.is_open())
	{
		getline(mykey, line);
		mykey.close();
	}
	Hkey= std::stoi(line, 0, 16);
	char txt[1000] ;
	cout << "Input text : "; cin >> txt;
	unsigned char in[BUFSIZE], out[BUFSIZE], back[BUFSIZE];
	unsigned char *e = out;
	
	DES_cblock key = { Hkey };
	DES_key_schedule keysched;
	mykey.close();
	memset(in, 0, sizeof(in));
	memset(out, 0, sizeof(out));
	memset(back, 0, sizeof(back));

	DES_set_key((const_DES_cblock *)key, &keysched);

	/* 8 bytes of plaintext */
	strcpy_s((char*)in,sizeof(in),txt);

	printf("Plaintext: [%s]\n", in);

	DES_ecb_encrypt((const_DES_cblock *)in, (const_DES_cblock *)out, &keysched, DES_ENCRYPT);

	printf("Ciphertext:");
	while (*e) printf(" [%02x]", *e++);
	printf("\n");

	DES_ecb_encrypt((const_DES_cblock *)out, (const_DES_cblock *)back, &keysched, DES_DECRYPT);

	printf("Decrypted Text: [%s]\n", back);

	return(0);

}

