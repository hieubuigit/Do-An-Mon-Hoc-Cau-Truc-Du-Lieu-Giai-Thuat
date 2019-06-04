/*
*	Thanh vien trong nhom:
*		1. Bui Van Hieu.( Cau 2)
*		2. Nguyen Minh Triet. (Cau 1)
*		3. Nguyen Dinh Trieu. ( Cau 3)
* 		4. Nguyen Thanh Luong ( Cau 4)
* 		5. Le Ngoc Hai. ( Cau 4 )
*	Project: Chuong trinh mo ta hoat dong cua may ATM thong qua nhung chuc nang:
*		1. Dang nhap
*		2. Rut Tien	(Nguyen Dinh Trieu)
*		3. Chuyen Tien (Bui Van Hieu)
*		4. Ghi lai giao dich
*		5. Doi mat khau.
*	Create of date: 04/05/2019.
*/

//Khai bao thu vien va tien xu ly
#include <iostream>
using namespace std;
#include <string>	//thu vien xu ly chuoi
#include <fstream>	//thu vien nhap xuat file
#include <conio.h>	//thu vien nhan gia tri tu phim
#include <windows.h>	//thu vien giao dien tren console
#include <time.h>	//thu vien thoi gian he thong
#include <iomanip>
#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS	//sua loi localtime

//tao doi tuong Khach Hang
struct KhachHang
{
	string sUser = "", sPin = "", sTenKH = "";
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
string maHoa_Pass(size_t maxLength);		//chuyen ky tu nhap vao thanh dau *
void textColor(int iColor);
void giaoDienATM(string sGD); //giao dien ATM
void addTail(List &L, KhachHang xKH);
void docData_1_KhachHang(ifstream &finCus, KhachHang &xKH);
void xuatData_1_KhachHang(KhachHang xKH);
void inputList(List &L, ifstream &finCus);
void outputList(List L);
int demKH(List L);
/*============================
*	Tinh Nang Chuyen Tien
==============================*/
void chuyenTien(List &L, string sUserInput);
void updateTaiKhoan(List &L, string sUserInput, string sSoTKNguoiNhan, double dTienConLai, double dTienDuocNhan, Node *k, Node *t);	//cap nhat so tien sau khi giao dich
void ghiLichSu(List L, string sUserInput, double dTienChuyen, Node *k, Node *t, string sTypeGD);	//ghi lai lich su giao dich
//============================

/*-------------------------------------
*	Tinh nang rut tien
---------------------------------------*/
void rutTien(List &L, string sUserInput, string sPinInput);
void ghiLichSuRut(List L, float fTienrut, Node *p, string sUserInput, string sTypeGD);
void capNhatFile(List &L);

/*-------------------------------------
*	Xem thong tin khach hang
---------------------------------------*/
void xuatHistory(Node* q);
void ghiLichSus(List L, double dTienThanhToan, Node* k, Node* t, string sTypeGD);
void xemThongTinTK(Node *q);

/*--------------------------------------
*	Doi mat khau
---------------------------------------*/
void doiMatKhau(List L, Node* t);

/*-------------------------------------
*	Tinh nang dang nhap
---------------------------------------*/
void logIn(List &L);

//Chuong trinh chinh
void main()
{
	List L;
	/*KhachHang xKH;*/
	ifstream finCus; // b1. doc du lieu tu file len
	finCus.open("TheATM.dat"); //b2. mo file.

	/*docData_1_KhachHang(finCus, xKH);
	xuatData_1_KhachHang(xKH);*/

	inputList(L, finCus);	//b3. doc du lieu tu file len
	/*outputList(L);*/
	finCus.close();		//b4. dong file

	/*cout << demKH(L);*/
	
	logIn(L);

	system("pause");
}

/*------------------------
*	Chuc nang dang nhap
--------------------------*/
void logIn(List &L)
{
	string sUserInput = "";
	string sPinInput = "";
	int nDemLanSai = 0;
	int nLuaChon = 0;
	int i = 0;
	string esc = "";
	string sChucNang = "";
	Node *t = L.pHead;

	while (i < 3)
	{
		giaoDienATM("Login");
		textColor(12); cout << "\t\t\t\t=====  Luu y: nhan ESC de thoat chuong trinh =====" << endl;

		textColor(10); cout << "\t\t\t\t\tUser: "; //nhap user
		rewind(stdin);
		getline(cin, sUserInput);

		if (sUserInput == "esc" || sUserInput == "ESC")
		{
			nDemLanSai = 4;
			i = 4;
			exit(0);
		}

		//nhap pin
		textColor(10); cout << "\t\t\t\t\tPin:  ";
		sPinInput = maHoa_Pass(6);

		for (Node *q = L.pHead; q != NULL; q = q->pNext)
		{
			if (sUserInput == q->xDataKH.sUser && sPinInput == q->xDataKH.sPin)		//ca 2 deu phai dung
			{
				cout << "\t\t\t\t\tDang dang nhap ..." << endl;
				Sleep(1000);
				system("cls");
				cout << "\t\t\t\t\t====== Dang nhap thanh cong ======" << endl;
				Sleep(1000);
				menu:
				system("cls");
				giaoDienATM("Menu");
				cout << "Lua chon chuc nang: ";
				cin >> nLuaChon;
				do
				{
					switch (nLuaChon)
					{
					case 1:		//Rut tien
						system("cls");
						rutTien(L, sUserInput, sPinInput);
						textColor(12); cout << "\nNhap \""; cout << "YES"; cout << "\" de quay lai Menu. Nhap \""; cout << "NO"; cout << "\" de thoat: ";
						rewind(stdin);
						getline(cin, sChucNang);
						if (sChucNang == "yes" || sChucNang == "YES")
						{
							system("cls");
							goto menu;
						}
						else
						{
							system("cls");
							textColor(10); cout << "\n\t\t\tCam on quy khach da su dung dich vu, hen gap lai. \n";
							exit(0);
						}
						break;
					case 2:		//Chuyen tien
						system("cls");	
						textColor(11); chuyenTien(L, sUserInput);
						cout << "Nhap esc de ve menu: ";
						getline(cin, esc);
						if (esc == "ESC" || esc == "esc")
						{
							goto menu;
						}
						break;
					case 3:	//Xem thong tin giao dich
						system("cls");
						textColor(10);
						giaoDienATM("XemThongTin");
						xuatHistory(q);
						//Lich su giao dich

						cout << "\nNhap \""; cout << "YES"; cout << "\" de quay lai Menu. Nhap \""; cout << "NO"; cout << "\" de thoat: ";
						rewind(stdin);
						getline(cin, sChucNang);
						if (sChucNang == "yes" || sChucNang == "YES")
						{
							system("cls");
							goto menu;
						}
						else
						{
							system("cls");
							cout << "\n\t\t\tCam on quy khach da su dung dich vu, hen gap lai. \n";
							break;
						}
					case 4: //tinh nang doi mat khau
						system("cls");
						giaoDienATM("DoiMK");
						doiMatKhau(L, t);
						textColor(12); cout << "\nNhap \""; cout << "YES"; cout << "\" de quay lai Menu. Nhap \""; cout << "NO"; cout << "\" de thoat: ";
						rewind(stdin);
						getline(cin, sChucNang);
						if (sChucNang == "yes" || sChucNang == "YES")
						{
							system("cls");
							goto menu;
						}
						else
						{
							system("cls");
							textColor(10); cout << "\n\t\t\tCam on quy khach da su dung dich vu, hen gap lai. \n";
							exit(0);
						}
						break;
					default:
						Sleep(1000);
						system("cls");
						cout << "\n\t\t\t\tCam on quy khach da su dung dich vu!";
						Sleep(2000);
						cout << "\n\t\t\t\t\t\t\t\t\tGoodbye!\n";
						nLuaChon = 5;
						nDemLanSai = 4;
						i = 4;
						exit(0);
						break;
					}
				} while (nLuaChon > 0 && nLuaChon <= 4);
			}
			else if (sUserInput == q->xDataKH.sUser || sPinInput == q->xDataKH.sPin)//1 trong 2 user hoac pass sai
			{
				nDemLanSai++;
				cout << "\t\t\t\t\tDang dang nhap ..." << endl;
				Sleep(1000);
				system("cls");
				textColor(12); cout << "\t\t\t\t\t====== Sai user hoac pin ======" << endl;
				textColor(12); cout << "\t\t\t\t\tVui long dang nhap lai!" << endl;
				i++;
			}
		}
		if (nDemLanSai < 3) //sai nho hon 3 lan
		{
			system("cls");
			textColor(12); cout << "\t\t\t\t\t\tQuy khach con " << 3 - nDemLanSai << " lan sai!\n";
		}
		if (nDemLanSai == 3)	//sai qua 3 lan
		{
			textColor(12); cout << "\t\t\t\t\t\tQuy khach da dang nhap sai qua 3 lan!\n";
			system("cls");
			i += 4;
			exit(0);
			break;
			textColor(7);
		}
	}
}

/*
*	Create by: Le Ngoc Hai
*	Tinh nang doi mat khau
*
*
*
*/
//Đoi mat khau:
void doiMatKhau(List L, Node* t)
{
	int nDem = 0;
	system("cls");
	giaoDienATM("DOIMK");
	string matKhauHienTai;
dd:
	textColor(10);
	cout << "\t\t\tNhap Mat Khau Hien Tai: ";
	textColor(7);
	matKhauHienTai = maHoa_Pass(6);
	nDem++;
	if (matKhauHienTai == t->xDataKH.sPin)
	{
		string matKhauMoi = "";
		string nhapLaimk = "";
		textColor(4);
		cout << "\t\t\tLuu y: mat khau gom 6 chu so\n";
		textColor(7);
		textColor(013);
		cout << "\t\t\tNhap mat khau moi: ";
		textColor(7);
		matKhauMoi = maHoa_Pass(6);
		textColor(013);
		cout << "\t\t\tNhap lai mat khau moi: ";
		textColor(7);
		nhapLaimk = maHoa_Pass(6);
		if (matKhauMoi == nhapLaimk)
		{
			if (matKhauMoi.length() == 6)
			{
				t->xDataKH.sPin = matKhauMoi;

				textColor(11);
				cout << "\t\t\t---------------------------\n";
				textColor(6);
				cout << "\t\t\tThay doi mat khau thanh cong !!!\n";
				cout << "\t\t\tVui long dang nhap lai !!!\n";
				textColor(7);
			}
			else
			{
				system("cls");
				giaoDienATM("DOIMK");
				textColor(4);
				cout << "\t\t\tLuu y: mat khau moi bao gom 6 chu so. Vui long nhap lai\n";
				textColor(7);
				goto dd;
			}
		}
		else if (matKhauMoi == "ESC" || matKhauMoi == "esc" || nhapLaimk == "ESC" || nhapLaimk == "esc")
		{
			textColor(10);
			cout << "\t\tBan da chon thoat khoi chuong trinh\n";
			textColor(7);
		}
		else
		{
			system("cls");
			giaoDienATM("DOIMK");
			textColor(4);
			cout << "\t\tMat khau khong trung khop vui long nhap lai: \n";
			textColor(7);
			goto dd;
		}
	}
	else if (matKhauHienTai == "esc" || matKhauHienTai == "ESC")
	{
		textColor(10);
		cout << "Ban da chon thoat khoi chuong trinh\n";
		textColor(7);
		outputList(L);

	}
}


/*============================================================================
*	Create by: Nguyen Thanh Luong
*			
*
*
*
=============================================================================*/
void xuatHistory(Node* q)
{
	string STK = "";
	ifstream fcin;
	fcin.open("\GiaoDich\\" + q->xDataKH.sUser + ".dat");
	while (!fcin.eof())
	{
		getline(fcin, STK, '\n');
		cout << STK << endl;
		Sleep(30);
	}
	fcin.close();
	cout << "\t\t__________________________________________________________________________________________________\n";
}

//Sau khi giao dich ghi lai lich su giao dich va luu vao thu muc giao dich.
void ghiLichSus(List L, double dTienThanhToan, Node* k, Node* t, string sTypeGD)
{
	time_t hientai = time(0);
	tm* ltm = localtime(&hientai);

	ofstream writeFile;
	writeFile.open("GiaoDich\\" + t->xDataKH.sUser + ".dat", ios::app);
	writeFile << setw(20) << left << "Chu Tai Khoan" << "\t" << setw(20) << left << "Hinh Thuc" << "\t" << setw(20) << left << "Tien Thanh Toan" << "\t" << setw(20) << left << "So Du" << "\t" << setw(20) << left << "Doi Tuong user" << "\t" << setw(20) << left << "Ngay/Thang/Nam" << "\t" << setw(20) << left << "Gio/Phut/Giay" << endl;
	if (sTypeGD == "chuyentien")
	{
		writeFile << setw(20) << left << t->xDataKH.sTenKH << "\t" << setw(20) << left << "Chuyen Tien" << "\t" << setw(7) << left << dTienThanhToan << t->xDataKH.sLoaiTienTe << setw(10) << left << " " << "\t" << setw(7) << left << t->xDataKH.dSoDu << t->xDataKH.sLoaiTienTe << setw(10) << left << " " << "\t" << setw(20) << left << k->xDataKH.sUser << "\t" << setw(2) << ltm->tm_mday << "/" << 1 + ltm->tm_mon << "/" << 1900 + ltm->tm_year << setw(14) << left << " " << "\t" << setw(2) << left << ltm->tm_hour << ':' << ltm->tm_min << ':' << ltm->tm_sec << endl << endl;
	}
	else if (sTypeGD == "ruttien")
	{
		writeFile << setw(20) << left << t->xDataKH.sTenKH << "\t" << setw(20) << left << "Rut Tien" << "\t" << setw(7) << left << dTienThanhToan << t->xDataKH.sLoaiTienTe << setw(10) << left << " " << "\t" << setw(7) << left << t->xDataKH.dSoDu << t->xDataKH.sLoaiTienTe << setw(10) << left << " " << "\t" << setw(20) << left << "No Object" << "\t" << setw(2) << ltm->tm_mday << "/" << 1 + ltm->tm_mon << "/" << 1900 + ltm->tm_year << setw(14) << left << " " << "\t" << setw(2) << left << ltm->tm_hour << ':' << ltm->tm_min << ':' << ltm->tm_sec << endl << endl;
	}

	else if (sTypeGD == "nhantien")
	{
		writeFile << setw(20) << left << t->xDataKH.sTenKH << "\t" << setw(20) << left << "Nhan Tien" << "\t" << setw(7) << left << dTienThanhToan << k->xDataKH.sLoaiTienTe << setw(10) << left << " " << "\t" << setw(7) << left << t->xDataKH.dSoDu << t->xDataKH.sLoaiTienTe << setw(10) << left << " " << "\t" << setw(20) << left << setw(20) << left << k->xDataKH.sUser << "\t" << setw(2) << ltm->tm_mday << "/" << 1 + ltm->tm_mon << "/" << 1900 + ltm->tm_year << setw(14) << left << " " << "\t" << setw(2) << left << ltm->tm_hour << ':' << ltm->tm_min << ':' << ltm->tm_sec << endl << endl;
	}
	writeFile.close();
}

//xem thong tin 
void xemThongTinTK(Node *q)
{
	cout << "\t\tTai Khoan: " << q->xDataKH.sUser << endl;
	cout << "\t\tTen Khach Hang: " << q->xDataKH.sTenKH << endl;
	cout << "\t\tSo Du: " << q->xDataKH.dSoDu << q->xDataKH.dSoDu << endl;
}



/*=============================================================================================================
*	Create by: Nguyen Dinh Trieu
*	Rut tien:
*		- Cho nguoi dung nhap vao so tien can rut thoa dien kien: tien rut > 50000 & tien rut < so du - 50000
*		- Ghi lai thong tin giao dich
*	Ham khong tra ve.
==============================================================================================================*/
void rutTien(List &L, string sUserInput, string sPinInput)
{
	giaoDienATM("RutTien");
	float fTienrut = 0;
	textColor(11); cout << "\nNhap so tien ban muon rut: ";
	cin >> fTienrut;
	for (Node *p = L.pHead; p != NULL; p = p->pNext)
	{
		ofstream foutCus;
		foutCus.open("TheATM.dat");
		if (sUserInput == p->xDataKH.sUser && sPinInput == p->xDataKH.sPin)
		{
			if (fTienrut >= 50000 && fTienrut <= p->xDataKH.dSoDu - 50000)
			{
				p->xDataKH.dSoDu = p->xDataKH.dSoDu - fTienrut;
				textColor(10); cout << "\nBAN DA RUT TIEN THANH CONG " << fTienrut << " SO DU CON LAI LA: " << p->xDataKH.dSoDu << " VND\n";
				cout << "DANG CAP NHAT THONG TIN\n";
				//cap nhat file
				capNhatFile(L);
				Node* g = L.pHead;
				ghiLichSus(L, fTienrut, g, p, "ruttien");
				break;
			}
			else
			{
				while (fTienrut < 50000 || fTienrut > p->xDataKH.dSoDu - 50000)
				{
					system("cls");
					cout << "\t\t\t\tChao quy khach da den voi ngan hang SS cua chung toi\n";
					cout << "\t\t\t\t\t*********************************" << endl;
					cout << "\t\t\t\t\t*            Rut Tien           *" << endl;
					cout << "\t\t\t\t\t*********************************" << endl;
					string sC = " ";
					textColor(12); cout << "\nSo tien vuot qua so du hoac so tien rut duoi 50000!\n";
					textColor(12); cout << "Ban co muon tiep tuc khong! (Y = co ; N = khong) :  ";
					cin >> sC;
					if (sC == "N")
					{
						return;
					}
					else {
						system("cls");
						giaoDienATM("RutTien");
						textColor(11); cout << "\nNhap so tien ban muon rut: ";
						cin >> fTienrut;
						if (fTienrut >= 50000 && fTienrut <= p->xDataKH.dSoDu - 50000)
						{
							p->xDataKH.dSoDu = p->xDataKH.dSoDu - fTienrut;
							textColor(10); cout << "\nBAN DA RUT TIEN THANH CONG, SO DU CON LAI LA: " << p->xDataKH.dSoDu << " VND";
							textColor(10); cout << "\nDANG CAP NHAT THONG TIN\n";
							capNhatFile(L);
							Node* g = L.pHead;
							ghiLichSus(L, fTienrut, g, p, "ruttien");
							break;
						}
					}
				}
			}
			foutCus.close();
		}
	}
}
//Sau khi giao dich ghi lai lich su giao dich va luu vao thu muc giao dich
void ghiLichSuRut(List L, float fTienrut, Node *p, string sUserInput, string sTypeGD)
{
	time_t hientai = time(0);
	tm *ltm = localtime(&hientai);

	ofstream writeFile;
	writeFile.open("GiaoDich\\" + sUserInput + ".dat", ios::out);
	writeFile << "|\t\t" << "Loai giao dich" << "\t\t" << "|" << "\t\t" << "So tien rut" << "\t\t" << "|" << "\t\t" << "Ngay" << "\t\t" << "|" << "\t\t" << "Thang" << "\t\t" << "|" << "\t\t" << "Nam" << "\t\t" << "|" << "\t\t" << "Time" << endl;
	if (sTypeGD == "rutTien")
	{
		writeFile << "|\t\t" << "Rut tien" << "\t\t\t" << "|" << "\t\t" << fTienrut << "\t\t" << "|" << "\t\t" << ltm->tm_mday << "\t\t" << "|" << "\t\t" << 1 + ltm->tm_mon << "\t\t" << "|" << "\t\t" << 1900 + ltm->tm_year << "\t\t" << "|" << "\t\t" << ltm->tm_hour << ':' << ltm->tm_min << ':' << ltm->tm_sec << endl;
	}
	writeFile.close();
}
//ham cap nhat thong tin lai file sau khi rut tien
void capNhatFile(List &L)
{
	int nDem = 0;
	ofstream foutCus;
	foutCus.open("TheATM.dat");
	for (Node *p = L.pHead; p != NULL; p = p->pNext)
	{
		nDem++;
		foutCus << p->xDataKH.sUser << ", " << p->xDataKH.sPin << ", " << p->xDataKH.sTenKH << ", " << p->xDataKH.dSoDu << ',' << p->xDataKH.sLoaiTienTe << endl;
	}
	foutCus.close();
}


/*==============================================================
*	Create by: Bui Van Hieu.
*	Chuyen tien:
*	- Cho nguoi dung nhap vao so taikhoan nguoi nhan.
*	- Cho nhap so tien can chuyen:
*		+ So tien chuyen lon hon 50000VND
*		+ So du trong tai khoan > 50000VND
*		+ Cap nhat so tien sau khi thuc hien giao dich.
*		+ Ghi du lieu chuyen tien ra mot file khac.
================================================================*/
void chuyenTien(List &L, string sUserInput)
{
	giaoDienATM("ChuyenTien");
	string sSoTKNguoiNhan = "";
	double dTienChuyen = 0.0;
	double dTienConLai = 0.0;
	double dTienDuocNhan = 0.0;
	double dTienKhaDung = 0.0;
	Node *t;
	do
	{
		system("cls");
		giaoDienATM("ChuyenTien");
		textColor(12); cout << "\t\t\t\t=====  Luu y: nhan ESC de tro ve menu =====" << endl;
		textColor(11); cout << "\t\t\t\t\tNhap so tai khoan thu huong: ";
		rewind(stdin);
		getline(cin, sSoTKNguoiNhan);
		if (sSoTKNguoiNhan == "esc" || sSoTKNguoiNhan == "ESC")
		{
			break;
		}
	} while (sSoTKNguoiNhan == sUserInput);	//Tranh truong hop nguoi dung nhap so tai khoan minh dang dang nhap(Chuyen tien cho chinh minh)

	for (Node *k = L.pHead; k != NULL; k = k->pNext)
	{
		if (sSoTKNguoiNhan == k->xDataKH.sUser)
		{
			dTienKhaDung = k->xDataKH.dSoDu - 50000;
			textColor(11); cout << "\t\t\t\t\tNhap so tien can chuyen: ";
			cin >> dTienChuyen;
			if (dTienChuyen > 50000)
			{
				if (dTienChuyen < dTienKhaDung)
				{
					cout << "\t\t\tBan da chuyen tien thanh cong!" << endl;
					k->xDataKH.dSoDu += dTienChuyen;	//Tien cua nguoi nhan tang len sau giao dich
					dTienDuocNhan = k->xDataKH.dSoDu;
					Sleep(3000);
					for (t = L.pHead; t != NULL; t = t->pNext)
					{
						if (sUserInput == t->xDataKH.sUser)
						{
							t->xDataKH.dSoDu -= dTienChuyen;	//Tien cua nguoi chuyen se giam xuong
							dTienConLai = t->xDataKH.dSoDu;
						}
						updateTaiKhoan(L, sUserInput, sSoTKNguoiNhan, dTienConLai, dTienDuocNhan, k, t);
						ghiLichSus(L, dTienChuyen, k, t, "chuyentien");
						ghiLichSus(L, dTienChuyen, t, k, "nhantien");

						break;
					}
				}
				else
				{
					dTienDuocNhan = k->xDataKH.dSoDu;
					textColor(12); cout << "\t\t\tSo tien khong kha dung, Chuyen tien that bai! ";
					Sleep(3000);
				}
			}
		}
	}
}

/*---------------------------------------------------------------------------------------------------------
*	Create by: Bui Van Hieu
*	Sau khi giao dich thanh cong ghi lai lich su giao dich va luu vao thu muc GiaoDich voi ten [ID].dat
*	Ham khong tra ve gia tri
-----------------------------------------------------------------------------------------------------------*/
void ghiLichSu(List L, string sUserInput, double dTienChuyen, Node *k, Node *t, string sTypeGD)
{
	time_t hientai = time(0);
	tm *ltm = localtime(&hientai);

	ofstream writeFile;
	writeFile.open("GiaoDich\\" + sUserInput + ".dat", ios::app);
	writeFile << "|\t\t" << "Loai giao dich" << "\t\t" << "|" << "\t\t" << "Nguoi chuyen: " << "\t\t" << "|" << "\t\t" << "Nguoi nhan: " << "\t\t" << "|" << "\t\t" << "Tien Chuyen" << "\t\t" << "|" << "\t\t\t" << "Time" << "\t\t\t" << '|' << endl;
	if (sTypeGD == "chuyentien")	//Chuyen tien thanh cong thi ghi lai lich xu
	{
		writeFile << "|\t\t" << "Chuyen tien" << "\t\t\t" << "|" << "\t\t" << t->xDataKH.sTenKH << "\t\t" << "|" << "\t\t" << k->xDataKH.sTenKH << "\t\t\t\t" << "|" << "\t\t\t" << dTienChuyen << "\t\t" << "|" << "\t" << ltm->tm_mday << "/" << 1 + ltm->tm_mon << "/" << 1900 + ltm->tm_year << "\t" << ltm->tm_hour << ':' << ltm->tm_min << ':' << ltm->tm_sec << "\t\t" << '|' << endl;
	}
	writeFile.close();
}

/*----------------------------------------------------------------
*	Create by: Bui Van Hieu.
*	Sau khi thuc hien giao dich:
*		- Thay doi so tien cua nguoi nhan va nguoi gui.
*		- Nhung thong tin cua nhung nguoi con lai giu nguyen.
*	Ham khong tra ve gia tri.
------------------------------------------------------------------*/
void updateTaiKhoan(List &L, string sUserInput, string sSoTKNguoiNhan, double dTienConLai, double dTienDuocNhan, Node *k, Node *t)
{
	ofstream foutCus;
	foutCus.open("TheATM.dat");

	for (Node *h = L.pHead; h != NULL; h = h->pNext)
	{
		if (h->xDataKH.sUser == sUserInput)		//Dien kien de in so tien cua nguoi chuyen (bi tru bao nhieu se bi duoc ghi ra file)
		{
			foutCus << h->xDataKH.sUser << ", " << h->xDataKH.sPin << ", " << h->xDataKH.sTenKH << ", " << dTienConLai << ',' << h->xDataKH.sLoaiTienTe << endl;
		}
		else	//Dieu kien de in so tien cua nguoi nhan(tang bao nhieu se duoc ghi file)
		{
			if (h->xDataKH.sUser == sSoTKNguoiNhan)
			{
				foutCus << h->xDataKH.sUser << ", " << h->xDataKH.sPin << ", " << h->xDataKH.sTenKH << ", " << dTienDuocNhan << ',' << h->xDataKH.sLoaiTienTe << endl;
			}
			else
			{
				foutCus << h->xDataKH.sUser << ", " << h->xDataKH.sPin << ", " << h->xDataKH.sTenKH << ", " << h->xDataKH.dSoDu << ',' << k->xDataKH.sLoaiTienTe << endl;
			}
		}
	}
	foutCus.close();
}

//dem so luong khach hang co trong danh sach
int demKH(List L)
{
	Node *p = L.pHead;
	int nDem = 0;
	for (p = L.pHead; p != NULL; p = p->pNext)
	{
		nDem++;
	}
	return nDem;
}

//xuat du lieu tu file
void outputList(List L)
{
	Node *p = L.pHead;
	for (p = L.pHead; p != NULL; p = p->pNext)
	{
		xuatData_1_KhachHang(p->xDataKH);
		cout << endl;
	}
}

//Du du lieu khach hang vao Node
void inputList(List &L, ifstream &finCus)
{
	KhachHang xKH;
	while (!finCus.eof())	// lenh !finCus.eof(): end of file, neu con tro tro den cuoi file la dung thi thuc hien
	{
		docData_1_KhachHang(finCus, xKH);
		if (finCus.eof())	//trang cho lenh eof lap lai lan nua
		{
			break;
		}
		addTail(L, xKH);
	}
}

//xuat du lieu khach hang
void xuatData_1_KhachHang(KhachHang xKH)
{
	cout << "User:" << xKH.sUser << endl;
	cout << "Pin:" << xKH.sPin << endl;
	cout << "Ten khach hang:" << xKH.sTenKH << endl;
	cout << "So du:" << xKH.dSoDu << xKH.sLoaiTienTe << endl;
}

//doc du lieu khach hang
void docData_1_KhachHang(ifstream &finCus, KhachHang &xKH)
{
	getline(finCus, xKH.sUser, ',');
	finCus.ignore(1);
	getline(finCus, xKH.sPin, ',');
	finCus.ignore(1);
	getline(finCus, xKH.sTenKH, ',');
	finCus.ignore(1);
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
		textColor(15);
		cout << "\t\t\t\t\t*********************************" << endl;
		cout << "\t\t\t\t\t*  Chon chuc nang de thuc hien  *" << endl;
		cout << "\t\t\t\t\t*********************************" << endl;
		cout << endl;
		cout << "	Chon 1. DE RUT TIEN.\n";
		cout << "	Chon 2. DE CHUYEN TIEN.\n";
		cout << "	Chon 3. DE XEM GIAO DICH.\n";
		cout << "	Chon 4. DOI MAT KHAU.\n";
		cout << "	Chon 5. DE THOAT KHOI HE THONG.\n	";
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
	else if (sGD == "XemThongTin")
	{
		cout << "\t\t\t\t\t*****************************************" << endl;
		cout << "\t\t\t\t\t*           Thong Tin Giao Dich         *" << endl;
		cout << "\t\t\t\t\t*****************************************" << endl;
	}
	else if (sGD == "DoiMK")
	{
		cout << "\t\t\t\t\t*****************************************" << endl;
		cout << "\t\t\t\t\t*                Doi Mat Khau           *" << endl;
		cout << "\t\t\t\t\t*****************************************" << endl;
	}
}

//ma hoa pass thanh dau *
string maHoa_Pass(size_t maxLength)
{
	string pW = "";
	for (char c; (c = _getch());)  // lenh _getch() de nam bat su kien ban phim
	{
		if (c == '\n' || c == '\r') //\n: phim enter, \r xuong dong
		{
			cout << "\n";
			break;
		}
		else if (c == '\b')	 //phim backspace
		{
			cout << "\b \b";
			if (!pW.empty()) pW.erase(pW.size() - 1);
		}
		else if (c == -32) //phím mũi tên
		{
			_getch(); //bo qua ki tu tiep theo (huong mui ten)
		}
		else if (isprint(c) && pW.size() < maxLength)	//isprint nhan nhung ky tu in ra duoc (co khoang trang)
		{
			cout << '*';
			pW += c;
		}
	}
	return pW;
}
