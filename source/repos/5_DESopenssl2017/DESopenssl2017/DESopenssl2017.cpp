#pragma comment(lib, "Ws2_32.lib")//system
#pragma comment(lib, "crypt32.lib") //system
#pragma comment(lib, "D:\\1\\openssl-1.1.0f-vs2010\\lib\\libcryptoMT.lib")
#include <stdio.h>
#include <iomanip>
#include <string.h>
#include <stdlib.h>
#include <openssl/des.h>
#include <openssl/rand.h>
#include <winsock2.h>
#include "pch.h"
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#define BUFSIZE 1024*64
using namespace std;

char convertChartoHextochar(unsigned char c) {
	static char bin[CHAR_BIT + 1] = { 0 };
	int i;

	for (i = CHAR_BIT - 1; i >= 0; i--)
	{
		
			bin[i] = (c % 2) + '0';
			c /= 2;
	}
	cout << "bin: " << bin << endl;
	
	return bin[CHAR_BIT + 1] = { 0 };
}



int main()
{
	errno_t err, err1,err_encyp,err_cipher;
	int c, d,encp,cipher;
	string privateKey;
	string pubKey;
	string input_txt;
	string cipher_text;
	FILE *fp, *fpub,*encp_txt,*cipher_txt;
	err = fopen_s(&fp, "D:\\1\\openssl-1.1.0f-vs2010\\bin64\\blob.private.key", "r");
	err1 = fopen_s(&fpub, "D:\\1\\openssl-1.1.0f-vs2010\\bin64\\blob.pub.key", "r");
	err_encyp = fopen_s(&encp_txt, "D:\\DES\\Encype.txt", "r");
	err_cipher = fopen_s(&cipher_txt, "D:\\DES\\Ciphertext.txt", "w");
	if (err == 0)
	{
		while ((c = getc(fp)) != EOF) {
			privateKey += c;
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
	if (err_encyp == 0)
	{
		while ((encp = getc(encp_txt)) != EOF) {
			input_txt += encp;
		}
		fclose(encp_txt);
	}

	struct nodez {
		string x = NULL;
	};

	cout << privateKey << endl;
	//cout << pubKey << "  " << pubKey.size() << endl;
	cout << pubKey << endl;;
	
	char cstr[3244];
	char pub[801];
	strcpy_s(cstr, privateKey.c_str());
	strcpy_s(pub, pubKey.c_str());
	unsigned char in[BUFSIZE], out[BUFSIZE], back[BUFSIZE];
	unsigned char *e = out;

	DES_cblock key = {*cstr};
	DES_key_schedule keysched;

	memset(in, 0, sizeof(in));
	memset(out, 0, sizeof(out));
	memset(back, 0, sizeof(back));

	DES_set_key((const_DES_cblock *)key, &keysched);
	/* 8 bytes of plaintext */
	strcpy_s((char*)in, input_txt.size()+1, input_txt.c_str());

	printf("Plaintext: [%s]\n", in);

	DES_ecb_encrypt((const_DES_cblock *)in, (const_DES_cblock *)out, &keysched, DES_ENCRYPT);
	char temp[] = {' '};
	int j=0;
	string r;
	char  buffer[200];
	printf("Ciphertext:");
	while (*e) {
		//printf_s(buffer,1 , 1,"%02x", *e);
		//putc(*buffer, cipher_txt);
		//printf(buffer);
		//cout << "TEST :::::  " << printf_s(buffer, 1, 1, "%02x", *e) << endl;
		//temp[] += convertChartoHextochar(*e);
		printf(" [%d]", *e);
		printf(" [%c]", *e);
		printf(" [%02x]", *e++); 
	}
	printf("\n");
	//cout <<"TEST :::::  "<< buffer << endl;
	fwrite(&r, sizeof(r),1, cipher_txt);
	/*for (int i = 0; i <strlen(temp); i++) {
		putc(temp[i], cipher_txt);
	}*/
	while ((cipher = getc(cipher_txt)) != EOF) {
		cipher_text += cipher;
	}
	fclose(cipher_txt);
	//cout << "Des" << cipher_text <<endl;
	//cout << "Des" << sizeof(r) << endl;
	//strcpy_s((char*)out, cipher_text.size() + 1, cipher_text.c_str());
	DES_cblock key2 = { *pub };
	DES_key_schedule keysched2;
	DES_set_key((const_DES_cblock *)key2, &keysched2);
	DES_ecb_encrypt((const_DES_cblock *)out, (const_DES_cblock *)back, &keysched, DES_DECRYPT);

	printf("Decrypted Text: [%s]\n", back);

	return(0);


}
