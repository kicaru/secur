#pragma comment(lib, "Ws2_32.lib")//system
#pragma comment(lib, "crypt32.lib") //system
#pragma comment(lib, "D:\\1\\openssl-1.1.0f-vs2010\\lib64\\libcryptoMT.lib")
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
#include <bitset>
#define BUFSIZE 1024*64
using namespace std;



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



int main()
{
	errno_t err1, err_in_cipher, err_key;
	int d, cipher, in_cipher, in_key;
	string pubKey;
	string keystr;
	string in_cipher_text;
	FILE *fpub, *cipher_txt, *in_cipher_txt, *decryp_txt,*key_txt;
	err1 = fopen_s(&fpub, "D:\\1\\openssl-1.1.0f-vs2010\\bin64\\blob.pub.key", "r");
	err_in_cipher = fopen_s(&in_cipher_txt, "D:\\DES\\Ciphertext.txt", "r");
	err_key = fopen_s(&key_txt, "D:\\DES\\Encype.txt", "r");


	if (err_key == 0)
	{
		while ((in_key = getc(key_txt)) != EOF) {
			keystr += in_key;
		}
		fclose(key_txt);
	}
	if (err_in_cipher == 0)
	{
		while ((in_cipher = getc(in_cipher_txt)) != EOF) {
			in_cipher_text += in_cipher;
		}
		fclose(in_cipher_txt);
	}

	if (err1 == 0)
	{
		while ((d = getc(fpub)) != EOF) {
			pubKey += d;
		}
		fclose(fpub);
	}


	char pub[801];
	char keystring[1000];
	string EncypDeskey;
	strcpy_s(keystring, keystr.c_str());
	strcpy_s(pub, pubKey.c_str());
	unsigned char in[BUFSIZE], out[BUFSIZE], back[BUFSIZE];
	unsigned char *b = back;
	DES_cblock keyDes = { *keystring };

	memset(in, 0, sizeof(in));
	memset(out, 0, sizeof(out));
	memset(back, 0, sizeof(back));

	

	//------------Decrypted----------
	cout << "------------Decrypted----------" << endl;
	
	cout << "CipherText [ " << in_cipher_text << " ]" << endl;
	in_cipher_text = convertHextochar(in_cipher_text);
	strcpy_s((char*)out, in_cipher_text.size() + 1, in_cipher_text.c_str());
	string decrypt;
	DES_cblock keypub = { *pub };
	DES_key_schedule keyschedpub;
	DES_set_key((const_DES_cblock *)keypub, &keyschedpub);
	DES_ecb_encrypt((const_DES_cblock *)out, (const_DES_cblock *)back, &keyschedpub, DES_DECRYPT);
	while (*b) {
		decrypt += *b;
		*b++;
	}
	strcpy_s((char*)out, decrypt.size() + 1, decrypt.c_str());
	DES_key_schedule keysched2;
	DES_set_key((const_DES_cblock *)keyDes, &keysched2);
	printf("Decrypted DES key and Public Key : [%s]\n", out);
	DES_ecb_encrypt((const_DES_cblock *)out, (const_DES_cblock *)back, &keysched2, DES_DECRYPT);
	unsigned char *bup = back;
	fopen_s(&decryp_txt, "D:\\DES\\Decryptext.txt", "w");
	string r0;
	char  buffer0[200];
	while (*bup) {
		sprintf_s(buffer0, 200, "%c", *bup);
		r0 += buffer0;
		*bup++;
	}
	cout << "Decrypted DES key : " << r0 << endl;
	fputs(r0.c_str(), decryp_txt);
	fclose(decryp_txt);
	return(0);


}
