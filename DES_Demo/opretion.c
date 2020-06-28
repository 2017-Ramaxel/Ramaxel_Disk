#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "des.h"
int opretion_encry_file(char *str,char *det) //加密
{
	FILE *fp = fopen(str, "rb");
	if (!fp) 
	{
		perror("");
		return -1;
	}
	FILE *fp_encry = fopen(det, "wb");
	if (!fp)
	{
		perror("");
	}
	char buf[1024 * 4] = "";
	char tmp[1024 * 4] = "";
	int len = 0;
	printf("文件加密中请稍等...\n");
	while (1) 
	{
		int m = fread(buf, 1, sizeof(buf), fp);
		if (m < sizeof(buf))
		{
			DesEnc(buf,m,tmp,&len);
			fwrite(tmp, 1, len, fp_encry);
			break;
		}
		DesEnc_raw(buf,m,tmp,&len);
		fwrite(tmp, 1, len, fp_encry);
	}
	system("cls");
	return 1;
}
int opretion_decry_file(char *str,char *det)//解密
{
	FILE *fp = fopen(str, "rb");
	if (!fp)
	{
		perror("");
		return -1;
	}
	FILE *fp_encry = fopen(det, "wb");
	if (!fp)
	{
		perror("");
	}
	char buf[1024 * 4] = "";
	char tmp[1024 * 4] = "";
	int len = 0;
	printf("文件解密中请稍等...\n");
	while (1)
	{
		int m = fread(buf, 1, sizeof(buf), fp);
		if (m < sizeof(buf))
		{
			DesDec(buf, m, tmp, &len);
			fwrite(tmp, 1, len, fp_encry);
			break;
		}
		DesDec_raw(buf, m, tmp, &len);
		fwrite(tmp, 1, len, fp_encry);
	}
	system("cls");
	return 1;
}
