#if DEBUG
	#include<iostream>
#endif
#include<string>
#include<windows.h>
#include <math.h> 
#include"BitArray.h"
#include<iostream>

#define Round(a) (int)(a+0.5) 
using namespace std;
BitArray *VatCan;
BitArray *DuongDi;
BitArray *CacDiemDaDiQua;
bool stop = false;
void VeDoanThang(int x1, int y1, int x2, int y2) //thuat toan Bre
{
	int c2, c, Dx, Dy, x, y;
	Dx = abs(x2 - x1);
	Dy = abs(y2 - y1);
	c = Dx - Dy;
	c2 = 2 * c;
	x = x1;
	y = y1;

	int x_unit = 1, y_unit = 1;

	if (x2 - x1 < 0)
		x_unit = -x_unit;
	if (y2 - y1 < 0)
		y_unit = -y_unit;
	VatCan[x].setBit(y, 1);

	if (x1 == x2)   // duong thang dung
	{
		while (y != y2)
		{
			y += y_unit; 
			VatCan[x].setBit(y, 1);
		}
	}

	else if (y1 == y2)  // duong ngang
	{
		while (x != x2)
		{
			x += x_unit;
			VatCan[x].setBit(y, 1);
		}
	}

	else if (x1 != x2 && y1 != y2)  // duong xien
	{
		while (x != x2 + 1)
		{
			c2 = 2 * c;
			if (c2 > -Dy)
			{
				c = c - Dy;
				x = x + x_unit;
			}
			if (c2 < Dx)
			{
				c = c + Dx;
				y = y + y_unit;
			}
			VatCan[x].setBit(y, 1);
		}
	}
}
void TimDuongDi(int *x1, int *y1, int *x2, int *y2)
{
	if (*x1 == *x2 && *y1 == *y2) stop = true;
	CacDiemDaDiQua[*x1].setBit(*y1, 1);
	if (stop) goto end;
	if (*x1 != *x2 || *y1 != *y2)
	{
		if (*x1 < *x2) //neu bo dieu kien nay ra thi se bi stack overflow
		{
			*x1 = *x1 + 1;
			if (*x1 == MAX) goto skip1;
			if (VatCan[*x1].getBit(*y1)) goto skip1;
			if (CacDiemDaDiQua[*x1].getBit(*y1)) goto skip1;
			DuongDi[*x1].setBit(*y1, 1);
			TimDuongDi(x1, y1, x2, y2);
			if (stop) goto end;
			DuongDi[*x1].setBit(*y1, 0);
			skip1:
			*x1 = *x1 - 1;
		}
		if (*x1 > *x2) //neu bo dieu kien nay ra thi se bi stack overflow
		{
			*x1 = *x1 - 1;
			if (*x1 < 0) goto skip2;
			if (VatCan[*x1].getBit(*y1)) goto skip2;
			if (CacDiemDaDiQua[*x1].getBit(*y1)) goto skip2;
			DuongDi[*x1].setBit(*y1, 1);
			TimDuongDi(x1, y1, x2, y2);
			if (stop) goto end;
			DuongDi[*x1].setBit(*y1, 0);
			skip2:
			*x1 = *x1 + 1;
		}
		if (*y1 < *y2) //neu bo dieu kien nay ra thi se bi stack overflow
		{
			*y1 = *y1 + 1;
			if (*y1 == MAX) goto skip3;
			if (VatCan[*x1].getBit(*y1)) goto skip3;
			if (CacDiemDaDiQua[*x1].getBit(*y1)) goto skip3;
			DuongDi[*x1].setBit(*y1, 1);
			TimDuongDi(x1, y1, x2, y2);
			if (stop) goto end;
			DuongDi[*x1].setBit(*y1, 0);
			skip3:
			*y1 = *y1 - 1;
		}
		if (*y1 > *y2) //neu bo dieu kien nay ra thi se bi stack overflow
		{
			*y1 = *y1 - 1;
			if (*y1 < 0) goto skip4;
			if (VatCan[*x1].getBit(*y1)) goto skip4;
			if (CacDiemDaDiQua[*x1].getBit(*y1)) goto skip4;
			DuongDi[*x1].setBit(*y1, 1);
			TimDuongDi(x1, y1, x2, y2);
			if (stop) goto end;
			DuongDi[*x1].setBit(*y1, 0);
			skip4:
			*y1 = *y1 + 1;
		}
	}
end:;
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

void main()
{
	bool exit = true;
	int chose = 0;
	//Diem bat dau
	int x1 = 50, y1 = 50;
	//Diem ket thuc 
	int x2 = 300, y2 = 300;
	//khoi tao
	VatCan = new BitArray[MAX];
	DuongDi = new BitArray[MAX];
	CacDiemDaDiQua = new BitArray[MAX];
	//tam giac
	VeDoanThang(100, 100, 200, 200);
	VeDoanThang(200, 200, 100, 200);
	VeDoanThang(100, 100, 100, 200);

	TimDuongDi(&x1, &y1, &x2, &y2);
	while (exit)
	{
		system("COLOR A");
		cout << ">> [Level 1] << Co di duoc tu dinh S(" << x1 << "," << y1 << ") den G(" << x2 << "," << y2 << ") khong? " << endl;
		cout << ">> [Level 2] << Tim kiem theo chieu rong (breadth - first search) " << endl;
		cout << ">> [Level 3] << Tim kiem chi phi dong nhat (uniform - cost search) " << endl;
		cout << ">> [Level 4] << Tim kiem tham lam(greedy best - first search) " << endl;
		cout << ">> [Level 5] << Tim kiem A* " << endl;
		cout << ">> [0] << Exit" << endl;
		cout << "Chon Level [     ]";
		gotoxy(14, 6);//Di chuyen con tro cin den vi tri moi trong console
		cin >> chose;
		if (chose == 0) exit = !exit;
		switch (chose)
		{
		case 1:
			cout << ">> [Level 1] << Tim Kiem Theo Chieu Sau (depth-first search) " << endl;
			
			system("pause");
			system("cls");
			break;
		case 2:
			cout << ">> [Level 2] << Tim kiem theo chieu rong (breadth - first search) " << endl;
			
			system("pause");
			system("cls");
			break;
		case 3:
			
			cout << ">> [Level 3] << Tim kiem chi phi dong nhat (uniform - cost search) " << endl;
			cout << "Tinh nang chua co san" << endl;
			system("pause");
			system("cls");
			break;
		case 4:
			
			cout << ">> [Level 4] << Tim kiem tham lam(greedy best - first search) " << endl;
			
			system("pause");
			system("cls");
			break;
		case 5:
			
			cout << ">> [Level 5] << Tim kiem A* " << endl;
			
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
	
#if DEBUG
	cout << (stop ? "Co duong di" : "Khong co duong di");
#endif // DEBUG
	HWND myconsole = GetConsoleWindow();
	HDC mydc = GetDC(myconsole);
	COLORREF COLOR = RGB(255, 0, 0);
	RECT r;
	GetWindowRect(myconsole, &r); //stores the console's current dimensions
	MoveWindow(myconsole, r.left, r.top, 800, 600, TRUE);
	Sleep(1000);
	for (size_t i = 0; i < 800; i++)
	{
		for (size_t j = 0; j < 600; j++)
		{
			if (VatCan[i].getBit(j)) SetPixel(mydc, i, j, COLOR);
		}
	}
	COLORREF COLOR2 = RGB(255, 255, 0);
	for (size_t i = 0; i < 800; i++)
	{
		for (size_t j = 0; j < 600; j++)
		{
			if (DuongDi[i].getBit(j)) SetPixel(mydc, i, j, COLOR2);
		}
	}
	ReleaseDC(myconsole, mydc);
	while (true);
#if DEBUG
	cin.ignore();
#endif
}