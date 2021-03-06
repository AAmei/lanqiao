#include "iostream"
#include "cstring" 
#include "cstdio"
#include "cstdlib"
using namespace std;

#define CHSIZE 27 

char arr[20][20];
char char_table[CHSIZE][5];

int myitoa(int k, char *ctemp)
{
	int i = 4, temp;
	while(k > 0)
	{
		temp = k%2;
		k /= 2;
		switch(temp)
		{
			case 0:
				ctemp[i] = '0';
				break;
			case 1:
				ctemp[i] = '1';
				break;
		}
		i--;
	}
	return 0;
} 


int main()
{
	int i = 0, j = 0, temp = 0;
	int len = 0;
	
	for(i = 0; i < 20; i++)
	{
		for(j = 0; j < 20; j++)
		{
			arr[i][j] = '0';
		}
	} 


	char ctemp[5];
	for(i = 0; i < 5; i++)
	{
		ctemp[i] = '0';
	}
	for(i = 0; i < CHSIZE; i++)
	{
		myitoa(i,ctemp);
		for(j = 0; j < 5; j++)
		{
			char_table[i][j] = ctemp[j];
		}
	}

	int R = 0, C = 0;
	char s[100];
	scanf("%d%d",&R,&C);//R(1≤R≤20)和C(1≤C≤20)
	getchar();
	gets(s); //字符串的长度≤(R*C)/5
	
	len = strlen(s);
	int temp_foot = 0; 
	char temp_sarr[400];
	for(i = 0; i < len; i++)
	{
		if(s[i] == ' ')temp_foot = 0;
		else temp_foot = s[i] - 'A' + 1;
		for(j = 0; j < 5; j++)
		{
			temp_sarr[i*5+j] = char_table[temp_foot][j];
		}
	}
	temp_sarr[len*5] = '\0'; 

	len = strlen(s);
	int counta = 0;
	if(C==1)
	{
		for(i = 0; temp_sarr[i] != '\0'; i++)
		{
			arr[i][0] = temp_sarr[counta++];
		}
	} 
	else
	{
		int right = 1, down = 0, left = 0, up = 0;
		int is_go[R][C];
		for(i = 0; i < R; i++)
		{
			for(j = 0; j < C; j++)
			{
				is_go[i][j] = 1;
			}
		} 
		i = 0; j = 0;
		arr[i][j] = temp_sarr[counta++];
		is_go[i][j] = 0;
		while( (right == 1 || down == 1 || left == 1 || up == 1 )&& temp_sarr[counta] != '\0')
		{
			while(right && temp_sarr[counta] != '\0')
			{
				is_go[i][++j] = 0;
				arr[i][j] = temp_sarr[counta++];
				if(j==C-1)
				{
					right = 0;
					if(is_go[i+1][j])
					{
						down = 1;
					}
					else break;
				}
				else if(is_go[i][j+1]){}
				else if(is_go[i+1][j])
				{
					right = 0; 
					down = 1;
				}
				else
				{
					right = 0;
				}
			}
			
			while(down && temp_sarr[counta] != '\0')
			{
				is_go[++i][j] = 0;
				arr[i][j] = temp_sarr[counta++];
				if(i==R-1)
				{
					down = 0;
					if(is_go[i][j-1])
					{
						left = 1;
					}
					else break;
				}
				else if(is_go[i+1][j]){}
				else if(is_go[i][j-1])
				{
					down = 0; 
					left = 1;
				}else
				{
					down = 0;
				}
			}
			
			while(left && temp_sarr[counta] != '\0')
			{
				is_go[i][--j] = 0;
				arr[i][j] = temp_sarr[counta++];
				if(i==0)
				{
					left = 0;
					if(is_go[i-1][j])
					{
						up = 1;
					}
					else break;
				}
				else if(is_go[i][j-1]){}
				else if(is_go[i-1][j])
				{
					left = 0; 
					up = 1;
				}else
				{
					left = 0;
				}
			}
			
			while(up && temp_sarr[counta] != '\0')
			{
				is_go[--i][j] = 0;
				arr[i][j] = temp_sarr[counta++];
				if(is_go[i-1][j]){}
				else if(is_go[i][j+1])
				{
					up = 0; 
					right = 1;
				}else
				{
					up = 0; 
				}
			}
		} 
	}
	
	for(i = 0; i < R; i++)
	{
		for(j = 0; j < C; j++)
		{
			cout << arr[i][j];
		}
		cout << endl;
	} 

	return 0;
}


/*
螺旋加密

总时间限制: 1000ms 内存限制: 65536kB
描述
Chip和Dale发明了一种文本信息加密技术。他们事先秘密约定好矩阵的行数和列数。接着，将字符按如下方式编码：

1. 所有文本只包含大写字母和空格。

2. 每个字符均赋予一个数值：空格=0，A=1，B=2，……，Y=25，Z=26。

按照下图所示的方式，将每个字符对应数值的5位二进制数依次填入矩阵。最后用0将矩阵补充完整。例如，对于信息“ACM”，行列数均为4时，矩阵将被填充为：



将矩阵中的数字按行连起来形成数字串，完成加密。例子中的信息最终会被加密为：0000110100101100。

输入
一行。首先是两个整数R(1≤R≤20)和C(1≤C≤20)，表示行数和列数。之后是一个只包含大写字母和空格的字符串。字符串的长度≤(R*C)/5。R和C之间以及C和字符串之间均用单个空格隔开。
输出
一行，为加密后的二进制串。注意你可能需要用0将矩阵补充完整。
样例输入
4 4 ACM
样例输出
0000110100101100
*/
