#pragma comment(lib, "Ws2_32.lib")//system
#pragma comment(lib, "crypt32.lib") //system
#pragma comment(lib, "D:\\1\\openssl-1.1.0f-vs2010\\lib\\libcryptoMT.lib")


#include <stdio.h>
#include <string.h>
#include <iostream>
#include <openssl/md5.h>
#include <string>
#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
#include <iomanip>  
using namespace std;
using json = nlohmann::json;

struct tokens{
	string ID;
	string password;
};
tokens *start;

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
	string id;
	string password;
	string log_id;
	string log_pass;
	int cdt=0;
	while (cdt != 3) {
		cout << endl;
		cout << "log in press 1" << endl;
		cout << "Register press 2" << endl;
		cout << "Exit press 3" << endl;
		cin >> cdt;
		cout << endl;
		if (cdt == 2) {
			cout << "id : ";
			cin >> id;
			cout << "Password : ";
			cin >> password;
			json user;
			password = MD5encrypt(password);
			cout << "ID : " << id << endl;
			cout << "PassWord : " << password << endl;


			user["ID"] = id;
			user["PassWord"] = password;


			std::ofstream o("D:\\MD5\\data.json");
			o << std::setw(4) << user << std::endl;

		}
		else if(cdt==1){


			cout << "----------------------log in----------------" << endl;
			cout << "ID ";
			cin >> log_id;
			cout << "password ";
			cin >> log_pass;
			log_pass = MD5encrypt(log_pass);
			std::ifstream i("D:\\MD5\\data.json");
			json j;
			i >> j;
			if (j["ID"] == log_id && j["PassWord"] == log_pass) {
				cout << "Log in Success!!" << endl;
			}
			else {
				cout << "ID or Password Incorrect" << endl;
			}
		}
	}
	return (0);
}

