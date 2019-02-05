#pragma comment(lib, "Ws2_32.lib")//system
#pragma comment(lib, "crypt32.lib") //system
#pragma comment(lib, "D:\\1\\openssl-1.1.0f-vs2010\\lib\\libcryptoMT.lib")


#include <stdio.h>
#include <string.h>
#include <openssl/md5.h>

using namespace std;


int main()
{
	unsigned char digest[16];
	string id;
	cin >> id;
	char string[] = "happy";
	char mdString[67];

	/* approach 1 */
	MD5((unsigned char*)&string, strlen(string), (unsigned char*)&digest);
	for (int i = 0; i < 16; i++)
		sprintf_s(&mdString[i * 2],33, "%02x", (unsigned int)digest[i]);

	printf("aproach 1--->md5 digest: %s\n", mdString);

	/* approach 2 */
	MD5_CTX context;
	MD5_Init(&context);
	MD5_Update(&context, string, strlen(string));
	MD5_Final(digest, &context);
	for (int i = 0; i < 16; i++)
		sprintf_s(&mdString[i * 2], 34, "%02x", (unsigned int)digest[i]);
	printf("aproach 2--->md5 digest: %s\n", mdString);
	


	return (0);
}

