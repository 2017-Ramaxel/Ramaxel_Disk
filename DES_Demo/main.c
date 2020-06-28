#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "my_function.h"
int main() 
{
	int num = 0;
	while (1) 
	{
		help();//帮助文档
		scanf("%d", &num);
		switch (num)
		{
		case 1:
			encry_file();//加密文件
			break;
		case 2:
			decry_file();//解密文件
			break;
		case 3:
			my_clear();//清屏
			break;
		case 4:
			my_exit();//退出
			break;
		}
	}
	system("pause");
}
