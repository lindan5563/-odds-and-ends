#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include<windows.h>
#define kd(vKey)((GetAsyncKeyState(vKey)&0x8000)?1:0)
#define ku(vKey)((GetAsyncKeyState(vKey)&0x8000)?0:1)
using namespace std;

struct tree
{
	char ch;
	int next[1000];
	int nct;
}a[10000];

int dj=1;
int jl,myi;
string s;
char file_name[1000];
char c;

char in()
{
	while(1)
	{
		for(int i=0x41;i<=0x5A;i++)
		{
			if(kd(i))
			{
				return char(i+32);
			}
		}
		Sleep(10); // 降低CPU占用
	}
}

bool find(char val)
{
	for(int i=0;i<a[jl].nct;i++)
	{
		if(a[a[jl].next[i]].ch==val)
			return true;
	}
	return false;
}

int gi(char val)
{
	for(int i=0;i<a[jl].nct;i++)
	{
		if(a[a[jl].next[i]].ch==val)
			return a[jl].next[i];
	}
	return -1;
}

void dfs(string n,int w,int cn)
{
	bool flag=1;
	for(int i=0;i<a[w].nct;i++)
	{
		flag=0;
		dfs(n+a[w].ch,a[w].next[i],cn+1);
	}
	if(flag)
	{
		for(int i=0;i<s.size()-1;i++)
			cout<<s[i];
		cout<<n;
		cout<<a[w].ch;
		cout<<endl;
	}
}

int main()
{
	cout << "========================================" << endl;
	cout << "      单词查找树程序 (Trie Tree)       " << endl;
	cout << "========================================" << endl;
	cout << endl;
	cout << "命令说明：" << endl;
	cout << "  add  - 添加单词到词典" << endl;
	cout << "  find - 查找单词（按字母实时提示）" << endl;
	cout << "  exit - 退出程序" << endl;
	cout << endl;
	
	while(1)
	{
		cout << "> 请输入命令 (add/find/exit): ";
		cin >> s;
		
		if(s=="add")
		{
			cout << "----------------------------------------" << endl;
			cout << "[添加模式]" << endl;
			cout << "请选择输入方式：" << endl;
			cout << "  1. 输入文件名（从文件读取）" << endl;
			cout << "  2. 输入 #（手动输入单词）" << endl;
			cout << "----------------------------------------" << endl;
			cout << "file name: ";
			cin >> s;
			
			if(s != "#")
			{
				cout << "正在从文件 " << s << " 读取单词..." << endl;
				ifstream file(s);
				if(!file)
				{
					cout << "错误：无法打开文件 " << s << endl;
					continue;
				}
				cout << "    ";
				int wordCount = 0;
				while(1)
				{
					getline(file,s);
					if(s=="#")
						break;
					if(s.empty()) continue; // 跳过空行
					
					jl=0;
					for(int i=0;i<s.size();i++)
					{
						myi=gi(s[i]);
						if(myi==-1)
						{
							a[dj].ch=s[i];
							a[dj].nct=0;
							a[jl].next[a[jl].nct]=dj;
							a[jl].nct++;
							myi=dj;
							dj++;
						}
						jl=myi;
					}
					wordCount++;
					cout << "\r   已添加 " << wordCount << " 个单词...";
				}
				file.close();
				cout << "\r   添加完成！共添加 " << wordCount << " 个单词。  " << endl;
				system("pause");
				system("cls");
				
				// 重新显示提示
				cout << "========================================" << endl;
				cout << "      单词查找树程序 (Trie Tree)       " << endl;
				cout << "========================================" << endl;
				cout << endl;
				cout << "命令说明：" << endl;
				cout << "  add  - 添加单词到词典" << endl;
				cout << "  find - 查找单词（按字母实时提示）" << endl;
				cout << "  exit - 退出程序" << endl;
				cout << endl;
			}
			else
			{
				cout << "手动输入模式，每行一个单词，输入 # 结束：" << endl;
				cout << "    ";
				int wordCount = 0;
				while(1)
				{
					cin >> s;
					if(s=="#")
						break;
					
					jl=0;
					for(int i=0;i<s.size();i++)
					{
						myi=gi(s[i]);
						if(myi==-1)
						{
							a[dj].ch=s[i];
							a[dj].nct=0;
							a[jl].next[a[jl].nct]=dj;
							a[jl].nct++;
							myi=dj;
							dj++;
						}
						jl=myi;
					}
					wordCount++;
					cout << "\r   已添加 " << wordCount << " 个单词...";
				}
				cout << "\r   添加完成！共添加 " << wordCount << " 个单词。  " << endl;
				system("pause");
				system("cls");
				
				// 重新显示提示
				cout << "========================================" << endl;
				cout << "      单词查找树程序 (Trie Tree)       " << endl;
				cout << "========================================" << endl;
				cout << endl;
				cout << "命令说明：" << endl;
				cout << "  add  - 添加单词到词典" << endl;
				cout << "  find - 查找单词（按字母实时提示）" << endl;
				cout << "  exit - 退出程序" << endl;
				cout << endl;
			}
		}
		else if(s=="find")
		{
			cout << "----------------------------------------" << endl;
			cout << "[查找模式]" << endl;
			cout << "请输入字母（按 '#' 退出查找）：" << endl;
			cout << "----------------------------------------" << endl;
			
			s="";
			while(true)
			{
				cout << "当前前缀: " << s << endl;
				cout << "请按键: ";
				
				c=in();
				Sleep(100); 
				s+=c;
				
				if(c=='#')
				{
					cout << "#" << endl;
					cout << "退出查找模式。" << endl;
					break;
				}
				
				cout << c << endl;
				
				// 查找前缀
				jl=0;
				for(int i=0;i<s.size();i++)
				{
					jl=gi(s[i]);
					if(jl == -1)
					{
						cout << "没有找到以 \"" << s << "\" 为前缀的单词。" << endl;
						break;
					}
				}
				
				if(jl != -1)
				{
					cout << "以 \"" << s << "\" 为前缀的单词：" << endl;
					dfs("",jl,1);
				}
				
				cout << endl;
				system("pause");
				system("cls");
				
				// 重新显示查找界面
				cout << "----------------------------------------" << endl;
				cout << "[查找模式]" << endl;
				cout << "请输入字母（按 '#' 退出查找）：" << endl;
				cout << "----------------------------------------" << endl;
			}
			s="";
			system("cls");
			
			// 返回主界面
			cout << "========================================" << endl;
			cout << "      单词查找树程序 (Trie Tree)       " << endl;
			cout << "========================================" << endl;
			cout << endl;
			cout << "命令说明：" << endl;
			cout << "  add  - 添加单词到词典" << endl;
			cout << "  find - 查找单词（按字母实时提示）" << endl;
			cout << "  exit - 退出程序" << endl;
			cout << endl;
		}
		else if(s=="exit")
		{
			cout << "感谢使用，再见！" << endl;
			break;
		}
		else
		{
			cout << "未知命令: " << s << endl;
			cout << "请使用 add、find 或 exit" << endl;
		}
	}
	
	return 0;
}
