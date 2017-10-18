#include <iostream>
#include <fstream>
#include <string> 
using namespace std;

//create and manage node
struct Node
{
	int data;//contain data of node in graph
	int color; //check node gone by paint color node (node nao di qua se bi to mau de danh dau)
	Node **pNext;
};

//save double node start and node end
struct DoubleNode
{
	//node start S
	Node S;
	//node end G
	Node G;
};

//List node graph
Node *nodeList = new Node();

//new point Start S and Point end G
DoubleNode point;

//read file input input.txt
void ReadInput(
	Node *list //list node of graph (danh sach luu cac node cua do thi)
	, int &size //summary node of graph
	, DoubleNode &point //node S and Node G
	, fstream &f //read file
);


//search algothrium


void main()
{
	//read input file
	fstream f;
	int n = 0;

	ReadInput(nodeList, n, point, f);
	

	system("pause");
}

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