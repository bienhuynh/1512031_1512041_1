#include <iostream>
#include <fstream>
#include <string> 
using namespace std;

//create and manage node
struct Node
{
	int data;
	Node **pNext;

};

struct DoubleNode
{
	//node start S
	Node S;
	//node end G
	Node G;
};

//List node graph
Node *nodeList = new Node();
DoubleNode point;
//read file input input.txt
void ReadInput(Node *list, int &size, DoubleNode &point, fstream &f)
{
	f.open("input.txt", ios::in);	
	//save temp size and point start and point end
	string str;
	//save data graph node
	string datagraph = "";
	string Str_S = "", Str_G = "";
	char i = 0;

	getline(f, str);
	size = atoi(str.c_str());
	getline(f, str);

	//read and get node start
	for (; str[i] != ' '; i++)
	{
		Str_S += str[i];
	}
	point.S.data = atoi(Str_S.c_str());

	//read and get node end
	for (; i < str.length(); i++)
	{
		Str_G += str[i];
	}
	point.G.data = atoi(Str_G.c_str());

	//read graph node
	while (!f.eof())
	{
		getline(f, str);
		datagraph += str + '\n';
	}
	
	f.close();
}

//search algothrium


void main()
{
	//read input file
	fstream f;
	int n = 0;

	ReadInput(nodeList, n, point, f);
	

	system("pause");
}