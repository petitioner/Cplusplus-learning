#include<cstdio>
#include<map>
#include<set>
#include<vector>
#include<string>
#include<iomanip>
#include<iostream>
#include<fstream>
#include<algorithm>
using namespace std;

bool cmp(const string &a, const string &b)
{
	if(a.length()<b.length())return true;
	return false;
}
int main(int argc, char *argv[])
{
	ifstream fin;
	fin.open("mapset.cpp");

	map<string,int> dictory;
	set<string> exclusion;
	
	string a[]={"a","an","or","the","and","but"};
	exclusion.insert(a,a+6);

	set<string>::iterator sit=exclusion.begin();

	string tmp;
	set<string> seter;
	while(fin>>tmp)
	{
		sit=exclusion.find(tmp);
		if(sit==exclusion.end())
		{
			dictory[tmp]++;
		}
		seter.insert(tmp);
	}
	
	vector<string> vst(seter.begin(),seter.end());
	cout<<endl<<"vetor<string> contains:"<<endl;
	for(int i=0;i<vst.size();i++)
		cout<<setw(50)<<vst[i]<<endl;
	cout<<endl;
	sort(vst.begin(),vst.end(),cmp);
	cout<<endl<<"vetor<string> after sort:"<<endl;
	for(int i=0;i<vst.size();i++)
		cout<<setw(50)<<vst[i]<<endl;
	cout<<endl;

	//map iterator ?????????????????????????????
	map<string,int>::iterator mit=dictory.begin();
	map<string,int>::iterator End=dictory.end();
	cout<<"this dictory contains : "
		<<endl<<setw(50)<<"word"<<"\t"
		<<"count"<<endl;
	for(;mit!=End;++mit)
	{
		cout<<setw(50)<<mit->first;
		cout<<"\t";
		cout<<setw(2)<<mit->second;
		cout<<endl;
	};

	
	return 0;
}
