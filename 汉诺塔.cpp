#include<bits/stdc++.h>
#include<windows.h>
#define kd(vKey)((GetAsyncKeyState(vKey)&0x8000)?1:0)
using namespace std;
int tap[3][5];
int at,bt,ct;
char in()
{
	while(1)
	{
		for(int i=0x41;i<=0x5A;i++)
		{
			if(kd(i))
			{
				return char(i);
			}
		}
		Sleep(10);
	}
}
void intn()
{
	for(int i=0,cnt=5;i<5&&cnt>=1;cnt--,i++)
		tap[0][i]=cnt;
	at=5;
	bt=0;
	ct=0;
}
bool move(char s,char o)
{
	if(s=='A' && at==0) return false;
	if(s=='B' && bt==0) return false;
	if(s=='C' && ct==0) return false;
	if(s=='A')
	{
		if(o=='B' && (bt==0 || tap[0][at-1] < tap[1][bt-1]))
		{
			tap[1][bt]=tap[0][at-1];
			at--;
			bt++;
			return 1;
		}
		else if(o=='C' && (ct==0 || tap[0][at-1] < tap[2][ct-1]))
		{
			tap[2][ct]=tap[0][at-1];
			at--;
			ct++;
			return 1;
		}
	}
	else if(s=='B')
	{
		if(o=='A' && (at==0 || tap[1][bt-1] < tap[0][at-1]))
		{
			tap[0][at]=tap[1][bt-1];
			at++;
			bt--;
			return 1;
		}
		else if(o=='C' && (ct==0 || tap[1][bt-1] < tap[2][ct-1]))
		{
			tap[2][ct]=tap[1][bt-1];
			ct++;
			bt--;
			return 1;
		}
	}
	else if(s=='C')
	{
		if(o=='A' && (at==0 || tap[2][ct-1] < tap[0][at-1]))
		{
			tap[0][at]=tap[2][ct-1];
			at++;
			ct--;
			return 1;
		}
		else if(o=='B' && (bt==0 || tap[2][ct-1] < tap[1][bt-1]))
		{
			tap[1][bt]=tap[2][ct-1];
			bt++;
			ct--;
			return 1;
		}
	}
	return 0;
}
void print(string s)
{
	system("cls");
	if(s!="tap")
	{
		cout<<s;
		return;
	}
	int e;
	for(int i=5;i>=0;i--)
	{
		for(int j=0;j<3;j++)
		{
			if(j==0)
				e=at;
			else if(j==1)
				e=bt;
			else
				e=ct;
			if(e>i)
			{
				if(tap[j][i]==1)
					cout<<"    -     ";
				else if(tap[j][i]==2)
					cout<<"   ---    ";
				else if(tap[j][i]==3)
					cout<<"  -----   ";
				else if(tap[j][i]==4)
					cout<<" -------  ";
				else if(tap[j][i]==5)
					cout<<"--------- ";
			}
			else
			{
				cout<<"    |     ";
			}
		}
		cout<<endl;
	}
	for(int i=4;i>=0;i--)
	{
		for(int j=0;j<3;j++)
		{
			if(j==0 && i<at) cout<<tap[j][i]<<" "; 
			else if(j==1 && i<bt) cout<<tap[j][i]<<" ";
			else if(j==2 && i<ct) cout<<tap[j][i]<<" ";
			else cout<<"  ";
		}
		cout<<endl;
	}
	cout<<"\n"<<at<<" "<<bt<<" "<<ct<<endl;
	if(ct == 5)
	{
		cout << "\n恭喜！你赢了！" << endl;
	}
	return;
}
void dfs(int n,char wz1,char wz2,char wz3) 
{
	if(n==1)
	{
		printf("%c->%c\n",wz1,wz3);
	}
	else
	{
		dfs(n-1,wz1,wz3,wz2);
		printf("%c->%c\n",wz1,wz3);
		dfs(n-1,wz2,wz1,wz3);
	}
}
int main()
{
	intn();
	char s,o;
	cout << "汉诺塔游戏 - 把5个盘子从A移到C" << endl;
	cout << "按H查看最优解步骤" << endl;
	system("pause");
	while(true)
	{
		print("tap");
		if(ct == 5)
		{
			cout << "\n游戏结束！" << endl;
			break;
		}
		Sleep(200);
		cout << "\n选择柱子 (A/B/C，H查看帮助): ";
		s=in();
		cout << s << endl;
		Sleep(200);
		if(s=='H')
		{
			cout << "\n最优解步骤（5个盘子从A移到C）：\n";
			dfs(5,'A','B','C');
			cout << "\n共需要31步\n";
			system("pause");
			continue;
		}
		if(s!='A' && s!='B' && s!='C')
		{
			cout << "请输入 A、B 或 C！" << endl;
			Sleep(1000);
			continue;
		}
		cout << "移动到: ";
		o=in();
		cout << o << endl;
		if(o!='A' && o!='B' && o!='C')
		{
			cout << "请输入 A、B 或 C！" << endl;
			Sleep(1000);
			continue;
		}
		if(s == o)
		{
			cout << "不能移动到同一个柱子！" << endl;
			Sleep(1000);
			continue;
		}
		if(!move(s,o))
		{
			cout << "无效移动！(大盘子不能放小盘子上或源柱子为空)" << endl;
			Sleep(1000);
		}
	}
	return 0;
}
