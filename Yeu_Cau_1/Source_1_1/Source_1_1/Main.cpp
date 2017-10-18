#include <iostream>
#include <fstream>
#include <string> 
using namespace std;

//create and manage node
struct Node
{
	int data;//contain data of node in graph
	int weight; //weight of x->y (trọng số của x->y)
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

//read data into node in RAM and import to list node
void ImportNodeinGraph(
	string dataGraphRaw //data graph raw readed from file txt
						//dữ liệu đồ thị thô đocj từ file txt
	, Node *list //List node graph
	, int size //N size of graph (số node của đồ thị)
);


//search algothrium
//a>
//Depth First Search (Tìm kiếm theo chiều sâu)
void DepthFirstSearch(
	Node *list //list node graph 
	, Node *listout //list Node road from S->G (đường đi vừa tìm được từ S->G)
);
//b>
//Breadth First Search (Tìm kiếm the chiều rộng)
void BreadthFirstSearch(
	Node *list //list node graph 
	, Node *listout //list Node road from S->G (đường đi vừa tìm được từ S->G)
);
//c>
//Uniform Cost Search (Tìm kiếm chi phí đồng nhất)
void UniformCostSearch(
	Node *list //list node graph 
	, Node *listout //list Node road from S->G (đường đi vừa tìm được từ S->G)
);
//d>
//Greedy Best First Search (Tìm kiếm tham lam)
void GreedyBestFirstSearch(
	Node *list //list node graph 
	, Node *listout //list Node road from S->G (đường đi vừa tìm được từ S->G)
);
//e>
//Search A* (Tìm kiếm A*)
void SearchHeurictis(
	Node *list //list node graph 
	, Node *listout //list Node road from S->G (đường đi vừa tìm được từ S->G)
);

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

	//read graph node from input.txt into RAM
	//đọc đồ thị từ file input.txt lưu vào một biến string
	while (!f.eof())
	{
		getline(f, str);
		datagraph += str + '\n';//save a variable string and each a line in input.txt descrem '\n'
								//mỗi một dòng trong file input.txt phân biệt nhau một kí tự xuống hàng '\n'
	}
	//Đọc dữ liệu đồ thị thô và Lấy dữ liệu của nút đẩy vào một nút và các hướng liên kết của nút
	//=>nói tóm lại kết xuất đồ thị vào danh sách node
	//read data into node in RAM and import to list node
	ImportNodeinGraph(datagraph, list, size);
	f.close();
}

//read data into node in RAM and import to list node
void ImportNodeinGraph(
	string dataGraphRaw
	, Node *list
	, int size 
)
{
	//ý tưởng
	//Cứ một đồ thị dạng thô sẽ có ma trận NxN để biểu diễn
	//khi ta biết được N là bao nhiêu thì ta có thể duyệt được bản thân một node 
	//đang xét với các node còn lại có mối quan hệ ntn
	Node *node;
	list = node;
	for (int i = 0; i < size; i++)
	{
		node = new Node();
		node->data = i;
		for (int j = 0; j < size; j++)
		{
			if (dataGraphRaw[i] != dataGraphRaw[i*size + j + 1])
			{
				string a = dataGraphRaw[i*size + j + 1];
				node->weight = atoi();
			}

		}
	}
}

//search algothrium
//a>
//Depth First Search (Tìm kiếm theo chiều sâu)
void DepthFirstSearch(Node *list, Node *listout)
{

}
//b>
//Breadth First Search (Tìm kiếm the chiều rộng)
void BreadthFirstSearch(Node *list, Node *listout)
{

}
//c>
//Uniform Cost Search (Tìm kiếm chi phí đồng nhất)
void UniformCostSearch(Node *list, Node *listout)
{

}
//d>
//Greedy Best First Search (Tìm kiếm tham lam)
void GreedyBestFirstSearch(Node *list, Node *listout)
{

}
//e>
//Search A* (Tìm kiếm A*)
void SearchHeurictis(Node *list, Node *listout)
{

}