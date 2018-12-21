#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct clientData
{
	int acctNum;
	char lastName[15];
	char firstName[10];
	double balance;
};

int main(void)
{
	FILE *pRead, *pWrite;
	FILE *cfPtr;
	errno_t err_pRead, err_pWrite, err_cfPtr;
	int cnt = 0;
	struct clientData client = { 0,"","",0.0 };

	err_pRead = fopen_s(&pRead, "C://Users/User/Desktop/c_code/Lab7-2/credit.txt", "r");
	if (err_pRead != 0) return 0;

	err_pWrite = fopen_s(&pWrite, "C://Users/User/Desktop/c_code/Lab7-2/credit_bin.txt", "wb");
	if (err_pWrite != 0)
	{
		fclose(pRead);
		return 0;
	}

	while (!feof(pRead))
	{
		fscanf(pRead, "%d", &client.acctNum);
		fscanf(pRead, "%s", &client.lastName);
		fscanf(pRead, "%s", &client.firstName);
		fscanf(pRead, "%lf", &client.balance);
		fwrite(&client, sizeof(struct clientData), 1, pWrite);
		printf("%-6d%-16s%-11s%10.2f\n", client.acctNum, client.lastName, client.firstName, client.balance);
	}

	fclose(pRead);
	fclose(pWrite);
	printf("已讀取文字檔的ASCII資料，並轉存成二進制資料檔案\n\n");

	system("pause");


	printf("\n讀取二進制資料檔案，並格式化輸出如下：\n");
	err_cfPtr = fopen_s(&cfPtr, "C://Users/User/Desktop/c_code/Lab7-2/credit_bin.txt", "rb");
	if (err_cfPtr != 0) printf("檔案無法開啟\n");
	else
	{
		printf("%-6s%-16s%-11s%10s\n", "Acct", "Last name", "First name", "Balance");

		cnt = fread(&client, sizeof(struct clientData), 1, cfPtr);

		while (cnt > 0)
		{
			printf("%-6d%-16s%-11s%10.2f\n", client.acctNum, client.lastName, client.firstName, client.balance);
			cnt = fread(&client, sizeof(struct clientData), 1, cfPtr);
		}

		fclose(cfPtr);
	}

	system("pause");
	return 0;
}