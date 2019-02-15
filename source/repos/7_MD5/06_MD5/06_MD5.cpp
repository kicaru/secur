#pragma comment(lib, "Ws2_32.lib")//system
#pragma comment(lib, "crypt32.lib") //system
#pragma comment(lib, "D:\\1\\openssl-1.1.0f-vs2010\\lib\\libcryptoMT.lib")


#include <stdio.h>
#include <string.h>
#include <iostream>
#include <openssl/md5.h>
#include <string>
using namespace std;

struct tokens{
	string ID;
	string password;
	tokens *next;
};
tokens *start;

void insert(string id,string pwd)
{
	tokens *t = start;
	if (start != NULL)
	{
		while (t->next != NULL)
		{
			t = t->next;
		}
		tokens *n = new tokens;
		t->next = n;
		n->ID = id;
		n->password = pwd;
		n->next = NULL;
	}
	else
	{
		tokens *n = new tokens;
		n->ID = id;
		n->password = pwd;
		n->next = NULL;
		start = n;
	}
}

int main()
{
	unsigned char digest[16];
	string id;
	string password;
	cout << "id : " ;
	getline(cin, id);
	cout << "Password : " ;
	getline(cin, password);
	char string[100];
	char mdString[67];
	strcpy_s(string, password.c_str());
	

	/* approach 2 */
	MD5_CTX context;
	MD5_Init(&context);
	MD5_Update(&context, string, strlen(string));
	MD5_Final(digest, &context);
	for (int i = 0; i < 16; i++) {
		sprintf_s(&mdString[i * 2], 34, "%02x", (unsigned int)digest[i]);
	}
	cout << "ID : " << id << endl;
	cout << "PassWord : " << mdString << endl;
	


	return (0);
}

