#include <iostream>
#include <fstream>
#include <string> 
#include<Windows.h>

using namespace std;
int n; //so luong dinh
int s, g; //dinh dau, dinh cuoi
int **maTran; //ma tran trong so cua cac canh
int *heuristic;
/*
currentStage va soDinhDaDiQua se thay the cho viec su dung Stack
*/
int *currentStage; //luu duong di hien tai
int soDinhDaDiQua; //so luong dinh da di qua
bool *daDuyet; //neu da duyet qua dinh i thi daDuyet[i]=true;
int *daDuyet2; //luu danh sach cac dinh da di qua trong qua trinh tim kiem
bool stop; //neu stop == true thi dung thuat toan tim kiem
void ReadInput(); //doc du lieu tu file input.txt
void Reset(); //Khoi tao lai cac bien can thiet de bat dau thuat toan
void InKetQua(string namefile);
void ThemVaoDanhSachDaDuyet(int vt);
int ViTriPhanTuNhoNhat(int *a);
int ViTriPhanTuNhoNhatAStar(int *a);
void DepthFirstSearch(int start, int end);
void BreadthFirstSearch(int start, int end);
void GreedyBestFirstSearch(int start, int end);
void AStarSearch(int start, int end);
//Di chuyen con tro vi tri trong console den noi khac
void gotoxy(int column, int line);
//Xoa het cac ki tu tu con tro console den het
void DeleteSpaceConsole(int length);
//ghi output ra file txt de luu tru
void OutputFile(int data, ofstream &f);

void main()
{
	system("COLOR A ");
	//ReadInput();
	//Reset();
	//DepthFirstSearch(s, g);
	ReadInput();
	bool exit = true;
	int chose = 0;
	
	while (exit)
	{	
		cout << ">> [1] << Tim Kiem Theo Chieu Sau (depth-first search) " << endl;
		cout << ">> [2] << Tim kiem theo chieu rong (breadth - first search) " << endl;
		cout << ">> [3] << Tim kiem chi phi dong nhat (uniform - cost search) " << endl;
		cout << ">> [4] << Tim kiem tham lam(greedy best - first search) " << endl;
		cout << ">> [5] << Tim kiem A* " << endl;
		cout << ">> [0] << Exit" << endl;
		cout << "Chon Thuat toan [     ]";
		gotoxy(19, 6);//Di chuyen con tro cin den vi tri moi trong console
		cin >> chose;
		if (chose == 0) exit = !exit;
		switch (chose)
		{
		case 1: 
			Reset();
			cout << ">> [1] << Tim Kiem Theo Chieu Sau (depth-first search) " << endl;
			DepthFirstSearch(s, g);
			system("pause");
			system("cls");
			break;
		case 2:
			Reset();
			cout << ">> [2] << Tim kiem theo chieu rong (breadth - first search) " << endl;
			BreadthFirstSearch(s, g);
			system("pause");
			system("cls");
			break;
		case 3:
			Reset();
			cout << ">> [3] << Tim kiem chi phi dong nhat (uniform - cost search) " << endl;
			cout << "Tinh nang chua co san" << endl;
			system("pause");
			system("cls");
			break;
		case 4:
			Reset();
			cout << ">> [4] << Tim kiem tham lam(greedy best - first search) " << endl;
			GreedyBestFirstSearch(s, g);
			system("pause");
			system("cls");
			break;
		case 5:
			Reset();
			cout << ">> [5] << Tim kiem A* " << endl;
			AStarSearch(s, g);
			system("pause");
			system("cls");
			break;
		case 0:
			system("cls");
			break;
		default:
			cout << "Ban phai con mot muc hoac bam 0 de exit" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
	cout << ">> [0] << Exit. " << endl;
	system("pause");
}
void ReadInput()
{
	ifstream f("input.txt");
	f >> n >> s >> g;
	maTran = new int*[n];
	for (size_t i = 0; i < n; i++)
	{
		maTran[i] = new int[n];
	}
	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < n; j++)
		{
			f >> maTran[i][j];
		}
	}
	heuristic = new int[n];
	for (size_t i = 0; i < n; i++)
	{
		f >> heuristic[i];
	}
}
void Reset()
{
	soDinhDaDiQua = 0;
	stop = false;
	if (daDuyet != nullptr) delete[]daDuyet;
	daDuyet = new bool[n]; 
	for (size_t i = 0; i < n; i++)
	{
		daDuyet[i] = false;
	}
	if (daDuyet2 != nullptr) delete[]daDuyet2;
	daDuyet2 = new int[n];
	for (size_t i = 0; i < n; i++)
	{
		daDuyet2[i] = -1;
	}
	if (currentStage != nullptr) delete[]currentStage;
	currentStage = new int[n];
	for (size_t i = 0; i < n; i++)
	{
		currentStage[i] = 0;
	}
}
void InKetQua(string namefile)
{
	ofstream f;
	f.open(namefile, ios_base::out);
	//in cac dinh da di qua trong qua trinh tim kiem;
	for (size_t i = 0; i < n; i++)
	{
		if (daDuyet2[i] != -1)
		{
			cout << daDuyet2[i] << " ";
			OutputFile(daDuyet[i], f);
		}	
		else break;
	}
	f << endl;
	cout << endl;
	//in duong di tu S den G
	for (size_t i = 0; i < soDinhDaDiQua; i++)
	{
		cout << currentStage[i] << " ";
		OutputFile(currentStage[i], f);
	}
	f.close();
}
void ThemVaoDanhSachDaDuyet(int vt)
{
	for (size_t i = 0; i < n; i++)
	{
		if (daDuyet2[i] == vt)return;
		if (daDuyet2[i] == -1)
		{
			daDuyet2[i] = vt;
			return;
		}
	}
}
int ViTriPhanTuNhoNhat(int *a)
{
	int k = 0;
	int min = -1;
	for (size_t i = 0; i < n; i++)
	{
		if (a[i] > 0)
		{
			if (min == -1 || a[i] < min)
			{
				min = a[i];
				k = i;
			}
		}
	}
	return k;
}
int ViTriPhanTuNhoNhatAStar(int *a)
{
	int k = 0;
	int min = -1;
	for (size_t i = 0; i < n; i++)
	{
		if (a[i] > 0)
		{
			if (min == -1 || (a[i] + heuristic[i]) < min)
			{
				min = a[i] + heuristic[i];
				k = i;
			}
		}
	}
	return k;
}
void DepthFirstSearch(int start, int end)
{
	ThemVaoDanhSachDaDuyet(start);
	currentStage[soDinhDaDiQua] = start;
	soDinhDaDiQua++;
	daDuyet[start] = true;
	if (start == end)
	{
		InKetQua("dsf.txt");
		stop = true;
		return;
	}
	for (size_t i = 0; i < n; i++)
	{
		if (maTran[start][i] > 0 && daDuyet[i] == false)
		{
			DepthFirstSearch(i, end);
		}
		if (stop) return;
	}
	daDuyet[start] = false;
	soDinhDaDiQua--;
}
void BreadthFirstSearch(int start, int end)
{
	ThemVaoDanhSachDaDuyet(start);
	currentStage[soDinhDaDiQua] = start;
	soDinhDaDiQua++;
	daDuyet[start] = true;
	if (start == end)
	{
		InKetQua("bfs.txt");
		stop = true;
		return;
	}
	for (size_t i = 0; i < n; i++)
	{
		if (maTran[start][i] > 0 && daDuyet[i] == false)
		{
			if (i == end)
				BreadthFirstSearch(i, end);
			ThemVaoDanhSachDaDuyet(i);
		}
		if (stop) return;
	}
	for (size_t i = 0; i < n; i++)
	{
		if (maTran[start][i] > 0 && daDuyet[i] == false)
		{
			BreadthFirstSearch(i, end);
		}
		if (stop) return;
	}
	daDuyet[start] = false;
	soDinhDaDiQua--;
}
void GreedyBestFirstSearch(int start, int end)
{
	ThemVaoDanhSachDaDuyet(start);
	currentStage[soDinhDaDiQua] = start;
	soDinhDaDiQua++;
	daDuyet[start] = true;
	if (start == end)
	{
		InKetQua("gbfs.txt");
		stop = true;
		return;
	}
	int *SapXep = new int[n];
	for (size_t i = 0; i < n; i++)
	{
		SapXep[i] = maTran[start][i];
	}
	for (size_t i = 0; i < n; i++)
	{
		int k = ViTriPhanTuNhoNhat(SapXep);
		if (maTran[start][k] == 0) break;
		SapXep[k] = 0;
		if (daDuyet[k] == false)
		{
			GreedyBestFirstSearch(k, end);
		}
		if (stop) return;
	}
	daDuyet[start] = false;
	soDinhDaDiQua--;
}
void AStarSearch(int start, int end)
{
	ThemVaoDanhSachDaDuyet(start);
	currentStage[soDinhDaDiQua] = start;
	soDinhDaDiQua++;
	daDuyet[start] = true;
	if (start == end)
	{
		InKetQua("astar.txt");
		stop = true;
		return;
	}
	int *SapXep = new int[n];
	for (size_t i = 0; i < n; i++)
	{
		SapXep[i] = maTran[start][i];
	}
	for (size_t i = 0; i < n; i++)
	{
		int k = ViTriPhanTuNhoNhatAStar(SapXep);
		if (maTran[start][k] == 0) break;
		SapXep[k] = 0;
		if (daDuyet[k] == false)
		{
			AStarSearch(k, end);
		}
		if (stop) return;
	}
	daDuyet[start] = false;
	soDinhDaDiQua--;
}

void gotoxy(int column, int line)
{
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE),
		coord
	);
}

void DeleteSpaceConsole(int length)
{
	for (int i = 0; i < length; i++)
	{
		cout << " ";
	}
}

void OutputFile(int data, ofstream &f)
{
	f << data << " ";
}