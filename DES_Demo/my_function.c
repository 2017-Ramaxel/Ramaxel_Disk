#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "opretion.h"
void help() //帮助文档
{
	printf("********************\n");
	printf("请按键选择,点击回车确定\n");
	printf("1 加密\n");
	printf("2 解密\n");
	printf("3 清屏\n");
	printf("4 退出\n");
	printf("********************\n");
}
void encry_file() //加密文件
{
	char str[100]="";
	char det[100]="";
	printf("请输入要加密的文件名及路径:\n");
	/*fgets(str, sizeof(str), stdin);
	str[strlen(str) - 1] = 0;//会吃掉一个输入函数;
	fgets(str, sizeof(str), stdin);
	str[strlen(str) - 1] = 0;*/
	scanf("%s", str);
	printf("请输入加密后的文件名及路径:\n");
	/*fgets(det, sizeof(det), stdin);
	det[strlen(det) - 1] = 0;*/
	scanf("%s", det);
	int num=opretion_encry_file(str, det);//加密
	if (num != 1) 
	{
		printf("文件加密失败!\n");
	}
	else 
	{
		printf("文件加密成功!\n");
	}
}
void decry_file()//解密文件
{
	char str[100] = "";
	char det[100] = "";
	printf("请输入要解密的文件名及路径:\n");
	/*fgets(str, sizeof(str), stdin);
	str[strlen(str) - 1] = 0;*/
	scanf("%s", str);
	printf("请输入解密后的文件名及路径:\n");
	/*fgets(det, sizeof(det), stdin);
	det[strlen(det) - 1] = 0;*/
	scanf("%s", det);
	printf("请输入解密密码:\n");
	char a[10] = "123456789";
	char pwd[10] = "";
	scanf("%s", pwd);
	system("cls");//清屏
	if (strcmp(a, pwd) == 0)
	{
		int num = opretion_decry_file(str, det);//解密
		if (num != 1)
		{
			printf("文件解密失败!\n");
		}
		else
		{
			printf("文件解密成功!\n");
		}
	}
	else 
	{
		printf("密码错误! 解密失败.\n");
	}
}
void my_clear()//清屏
{
	system("cls");
}
void my_exit()//退出
{
	exit(0);
}