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
	string r,a,result;
	a = c;
	
	char buffer[200];
	string temp;
	for (int i = 0; i < c.length(); i++) {
		r =GetBinaryStringFromHexString(a);
	}
	for (int i = 0; i < r.length(); i+=8) {
		temp = r.substr(i, 8);
		std::bitset<8> foo(temp);
		sprintf_s(buffer, 200, "%c", foo.to_ulong());
		result += buffer;
	}
	return result;
}



int main()
{
	errno_t err, err1,err_encyp,err_cipher, err_in_cipher;
	int c, d,encp,cipher,in_cipher;
	string privateKey;
	string pubKey;
	string input_txt;
	string cipher_text;
	string in_cipher_text;
	FILE *fp, *fpub,*encp_txt,*cipher_txt, *in_cipher_txt,*decryp_txt;
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


	char cstr[3244];
	char pub[801];
	string EncypDeskey;
	strcpy_s(cstr, privateKey.c_str());
	strcpy_s(pub, pubKey.c_str());
	unsigned char in[BUFSIZE], out[BUFSIZE], back[BUFSIZE];
	unsigned char *e = out;
	unsigned char *b = back;

	DES_cblock keyDes = { 0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10 };
	DES_cblock key = {*cstr};

	memset(in, 0, sizeof(in));
	memset(out, 0, sizeof(out));
	memset(back, 0, sizeof(back));

	DES_key_schedule keyschedDes;
	DES_set_key((const_DES_cblock *)keyDes, &keyschedDes);
	strcpy_s((char*)in, input_txt.size() + 1, input_txt.c_str());
	printf("Plaintext: [%s]\n", in);
	DES_ecb_encrypt((const_DES_cblock *)in, (const_DES_cblock *)out, &keyschedDes, DES_ENCRYPT);
	while (*e) {
		EncypDeskey += *e;
		printf(" [%02x]", *e++);
	}
	printf("\n");


	
	DES_key_schedule keysched;
	DES_set_key((const_DES_cblock *)key, &keysched);
	
	strcpy_s((char*)in, EncypDeskey.size()+1, EncypDeskey.c_str());
	printf("Encrypted DES key : [%s]\n", in);
	DES_ecb_encrypt((const_DES_cblock *)in, (const_DES_cblock *)out, &keysched, DES_ENCRYPT);
	string r;
	unsigned char *pd = out;
	char  buffer[200];
	while (*pd) {
		sprintf_s(buffer,200 ,"%02x", *pd);
		r += buffer;
	  *pd++;
	}
	cout << "Encrypted DES key and Private Key : " << r << endl;
	printf("\n\n");
	fputs(r.c_str(), cipher_txt);
	fclose(cipher_txt);

	

	//------------Decrypted----------
	cout << "------------Decrypted----------" << endl;
	err_in_cipher = fopen_s(&in_cipher_txt, "D:\\DES\\Ciphertext.txt", "r");
	if (err_in_cipher == 0)
	{
		while ((in_cipher  = getc(in_cipher_txt)) != EOF) {
			in_cipher_text += in_cipher;
		}
		fclose(in_cipher_txt);
	}
	cout << "CipherText [ " << in_cipher_text <<" ]"<<endl;
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
	fclose(cipher_txt);
	return(0);


}
