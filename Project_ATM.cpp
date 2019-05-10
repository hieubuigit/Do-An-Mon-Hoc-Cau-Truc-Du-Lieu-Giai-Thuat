/*
*	Name: Bui Van Hieu
*	Create of date: 04/05/2019
*	Project: ATM
*
*
*
*/

//Khai bao thu vien va tien xu ly
#include <iostream>
using namespace std;
#include <string>
#include <fstream>
#include <conio.h>	//thu vien nhan gia tri tu phim
#include <windows.h>	//thu vien giao dien tren console

//tao doi tuong Khach Hang
struct KhachHang
{
	string sUser = "", sPin = "", sID = "", sTenKH = "";
	double dSoDu = 0.0;
	string sLoaiTienTe = "";
};
//tao doi tuong Node chua du lieu khach hang
struct Node
{
	KhachHang xDataKH;
	Node *pNext;
};
//tao doi tuong List
struct List
{
	Node *pHead, *pTail;
	List()
	{
		pHead = pTail = NULL;
	}
};

//Khai bao nguyen mau ham
Node *createNote(KhachHang xKH);	//tao Node moi
string maHoa_Pass(unsigned int maxLenght);		//chuyen ky tu nhap vao thanh dau *
void textColor(int iColor);
void giaoDienATM(string sGD); //giao dien ATM
void addTail(List &L, KhachHang xKH);
void docData_1_KhachHang(ifstream &finCus, KhachHang &xKH);
void xuatData_1_KhachHang(KhachHang xKH);
void inputList(List &L, ifstream &finCus);
void outputList(List L);
void logIn(List &L);		//man hinh dang nhap

//Chuong trinh chinh
void main()
{
	List L;
	ifstream finCus; // b1. doc du lieu tu file len
	finCus.open("TheATM.dat"); //b2. mo file.

	inputList(L, finCus);	//b3. doc du lieu tu file len
	/*outputList(L);*/
	finCus.close(); //b4. dong file

	logIn(L);

	system("pause");
}

///*=======================
//*	Chuc nang dang nhap
//=======================*/
void logIn(List &L)
{
	string sUserInput;
	string sPinInput = "";
	int nDemLanSai = 0;
	int sLuaChon = 0;
	char c;
	giaoDienATM("Login");
	textColor(12); cout << "\t\t\t\t=====  Luu y: nhan ESC de thoat chuong trinh =====" << endl;
	
	int i = 0;
	while (i < 3)
	{
		////ham nhap phim ESC de thoat chuong trinh
		//while (true)
		//{
		//	if (_kbhit())		//kiem tra nguoi dung co nhan phim hay khong
		//	{
		//		c = _getch();
		//		if (c == 27)
		//		{
		//			break;
		//		}
		//	}
		//}

		textColor(10); cout << "\t\t\t\t\tUser: "; //nhap user
		rewind(stdin);
		getline(cin, sUserInput);

		//nhap pin
		textColor(10); cout << "\t\t\t\t\tPin:  ";
		sPinInput = maHoa_Pass(6);

		Node *q = L.pHead;
		for(q = L.pHead; q != NULL; q = q->pNext)
		{
			if (sUserInput == q->xDataKH.sUser && sPinInput == q->xDataKH.sPin)		//ca 2 deu phai dung
			{
				system("cls");
				cout << "\t\t\t\t\t====== Dang nhap thanh cong ======" << endl;
				giaoDienATM("Menu");
				cout << "Lua chon chuc nang: ";
				cin >> sLuaChon;
				do
				{
					switch (sLuaChon)
					{
						case 1:		//nhan 1 de chon tinh nang rut tien
							system("cls");
							
							break;
						case 2:
							system("cls");
							giaoDienATM("ChuyenTien");
							break;
					}

				} while (sLuaChon < 1 && sLuaChon > 4);
			}
			else if(sUserInput == q->xDataKH.sUser || sPinInput == q->xDataKH.sPin)		//1 trong 2 user hoac pass sai
			{
				system("cls");
				nDemLanSai++;
				textColor(12); cout << "\t\t\t\t\t====== Sai user hoac pin ======" << endl;
				textColor(12); cout << "\t\t\t\t\tVui long dang nhap lai!" << endl;
				i++;
			}
		}
		if (nDemLanSai < 3) //sai nho hon 3 lan
		{
			textColor(12); cout << "\t\t\t\t\t\tQuy khach con " << 3 - nDemLanSai << " lan sai!\n";
			giaoDienATM("Login");
		}
		if (nDemLanSai >= 3)	//sai qua 3 lan
		{
			textColor(12); cout << "\t\t\t\t\t\Quy khach da dang nhap sai qua 3 lan!\n";
			i += 4;
			break;
			textColor(7);
		}
	}
}

/*=====================
* Rut tien
=======================*/
void tinhNangRutTien(List L, Node *t)
{
	double dNhapTienRut = 0.0;
	int nN;
	char c;
	string sMatKhauXacNhan = "";
	rr:
	giaoDienATM("RutTien");
	cout << "Luu y so tien rut lon hon 50000!";
	cout << "Nhap so tien rut:" ;
	cin >> dNhapTienRut;
	double dSoTienKhaDung = t->xDataKH.dSoDu - 50000;
	if (dNhapTienRut > dSoTienKhaDung && dNhapTienRut < 50000)
	{
		cout << "So tien trong tai khoan khong du de thuc hien giao dich nay!" << endl;
	}
	else
	{
		system("cls");
		giaoDienATM("RutTien");
		cout << "So tien ban can rut la: " << dNhapTienRut << t->xDataKH.sLoaiTienTe;
		cout << "\nBan co muon tiep tuc xac nhan mat khau hay khong (C/K)?\n";
		cout << "Nhap 'C' de xac nhan rut tien hoac nhap 'K' huy rut tien!\n";
		if (c == 'C' || c == 'c')
		{
			cout << "Nhap mat khau cua ban:";
			sMatKhauXacNhan = maHoa_Pass(6);
			if (sMatKhauXacNhan == t->xDataKH.sPin)
			{
				cout << "Ban da rut " << dNhapTienRut << t->xDataKH.sLoaiTienTe << " thanh cong!\n";
				cout << "Giao dich thanh cong!\n";
				cout << "So tien con lai trong tai khoan la:" << t->xDataKH.dSoDu << t->xDataKH.sLoaiTienTe << endl;
			}
			//Ghi du lieu len file sau khi da rut tien
			
			else if(sMatKhauXacNhan != t->xDataKH.sPin)
			{
				cout << "Giao dich bi huy!\n";
				goto rr;
			}
		}
		if (c == 'K' || c == 'k')
		{
			cout << "He thong ngung giao dich!";
			giaoDienATM("Menu");
		}
	}
}

//hmm ghi ra file khi thuc hien giao dich
void ghiLaiGiaoDich(Node K, List L)
{

}

//xuat du lieu tu file
void outputList(List L)
{
	Node *p = L.pHead;
	int nDem = 0;
	for (p = L.pHead; p != NULL; p = p->pNext)
	{
		cout << "\n\nKhach hang thu:" << nDem++ << endl;
		xuatData_1_KhachHang(p->xDataKH);
	}
}

//Du du lieu khach hang vao Node
void inputList(List &L, ifstream &finCus)
{
	KhachHang xKH;
	while(!finCus.eof())	// lenh !finCus.eof() neu con tro tro den cuoi file la dung thi thuc hien
	{
		docData_1_KhachHang(finCus, xKH);
		addTail(L, xKH);
	}
}

//xuat du lieu khach hang
void xuatData_1_KhachHang(KhachHang xKH)
{
	cout << "Ten khach hang:" << xKH.sTenKH << endl;
	cout << "So du:" << xKH.dSoDu << xKH.sLoaiTienTe << endl;
}

//doc du lieu khach hang
void docData_1_KhachHang(ifstream &finCus, KhachHang &xKH)
{ 
		getline(finCus, xKH.sUser, ',');
		rewind(stdin);
		finCus.seekg(1, 1);	//bo qua 1 byte ky tu
		getline(finCus, xKH.sPin, ',');
		rewind(stdin);
		finCus.seekg(1, 1);
		getline(finCus, xKH.sTenKH, ',');
		rewind(stdin);
		finCus.seekg(1, 1);
		finCus >> xKH.dSoDu, ',';
		finCus.ignore(1);
		getline(finCus, xKH.sLoaiTienTe);
}

//thong tin khach hang vao cuoi danh sach
void addTail(List &L, KhachHang xKH)
{
	Node *pNew = createNote(xKH);
	if (L.pHead == NULL)
	{
		L.pHead = L.pTail = pNew;
	}
	else
	{
		L.pTail->pNext = pNew;
		L.pTail = pNew;
	}
}

//tao mot Node moi chua du lieu chua lien ket voi List
Node *createNote(KhachHang xKH)
{
	Node *p = new Node;
	if (p == NULL)
	{
		exit(1);
	}
	else
	{
		p->xDataKH = xKH;
		p->pNext = NULL;
	}
	return p;
}

//ham lay mau sac cho text
void textColor(int iColor)
{
	HANDLE hConsoleColor;
    hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsoleColor, iColor);
}

//ham hien thi giao dien
void giaoDienATM(string sGD)
{
	if (sGD == "Login")
	{
		textColor(10); cout << "\t\t\t\t\t*********************************" << endl;
		textColor(10); cout << "\t\t\t\t\t*\t";
		textColor(14); cout << "Dang nhap he thong";
		textColor(10); cout << "\t*" << endl;
		textColor(10); cout << "\t\t\t\t\t*********************************" << endl;
	}
	else if (sGD == "Menu")
	{
		textColor(13);
		cout << "\t\t\t\t\t*********************************" << endl;
		cout << "\t\t\t\t\t*  Chon chuc nang de thuc hien  *" << endl;
		cout << "\t\t\t\t\t*********************************" << endl;
		cout << endl;
		cout << "	Chon 1. DE RUT TIEN.\n";
		cout << "	Chon 2. DE CHUYEN TIEN.\n";
		cout << "	Chon 3. XEM GIAO DICH.\n";
		cout << "	Chon 4. THOAT KHOI HE THONG.\n	";
	}
	else if (sGD == "RutTien")
	{
		cout << "\t\t\t\t\t*********************************" << endl;
		cout << "\t\t\t\t\t*            Rut Tien           *" << endl;
		cout << "\t\t\t\t\t*********************************" << endl;
		cout << endl;
	}
	else if (sGD == "ChuyenTien")
	{
		cout << "\t\t\t\t\t*********************************" << endl;
		cout << "\t\t\t\t\t*           Chuyen Tien         *" << endl;
		cout << "\t\t\t\t\t*********************************" << endl;
		cout << endl;
	}
}

//ma hoa pass thanh dau *
string maHoa_Pass(unsigned int maxLength)
{
	string pW = "";
	for (char c; (c = _getch());)  // lenh _getch() de nam bat su kien ban phim
	{
		if (c == '\n' || c == '\r') //\n: phim enter, \r xuong dong
		{ 
			std::cout << "\n";
			break;
		}
		else if (c == '\b')	 //phim backspace
		{	
			std::cout << "\b \b";
			if (!pW.empty()) pW.erase(pW.size() - 1);
		}
		else if (c == -32) //phím mũi tên
		{ 
			_getch(); //bo qua ki tu tiep theo (huong mui ten)
		}
		else if (isprint(c) && pW.size() < maxLength)	//isprint nhan nhung ky tu in ra duoc (co khoang trang)
		{ 
			std::cout << '*';
			pW += c;
		}
	}
	return pW;
}
