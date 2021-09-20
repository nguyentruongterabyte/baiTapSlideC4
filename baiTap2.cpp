//2. Hãy định nghĩa kiểu :
//
//struct SinhVien
//{
//	char hoTen[40];
//	float diem;
//	char xepLoai[15];
//};
//Viết chương trình nhập vào họ tên, điểm của n học sinh.Thực hiện xếp loại theo cách sau :
//Điểm		Xếp loại
//9, 10 		Giỏi
//7, 8 		Khá
//5, 6 		Trung bình
//Dưới 5 		Không đạt
//In danh sách lên màn hình theo dạng sau :
//XEP LOAI SINH VIEN
//HO VA TEN 	DIEM 	XEPLOAI
//Nguyen Van A 	7.5 	Kha
//Ho Thi B 		5 	Trung binh
//Dang Kim C 	4 	Khong dat



#include<iostream>
#include<iomanip>
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<Windows.h>
#include<cstring>
#include<regex>

using namespace std;


void setColor(int ForgC)
{
	/*  Black         | 0
		Blue          | 1
		Green         | 2
		Cyan          | 3
		Red           | 4
		Magenta       | 5
		Brown         | 6
		Light Gray    | 7
		Dark Gray     | 8
		Light Blue    | 9
		Light Green   | 10
		Light Cyan    | 11
		Light Red     | 12
		Light Magenta | 13
		Yellow        | 14
		White         | 15*/
	WORD wColor;

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	//sử dụng csbi cho từ wAttributes.
	if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
	{
		//Che dấu tất cả trừ thuộc tính nền và thêm màu giả
		wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
		SetConsoleTextAttribute(hStdOut, wColor);
	}
	return;
}
typedef struct {
	char fullName[60];//Họ và tên
	float score;//Điểm số
	string rank;//Xếp loại
} student;
string toRank(student studentInput) {
	string toRank;//xếp loại (Giỏi, Khá, Trung bình và Không đạt)
	if (studentInput.score >= 8 && studentInput.score <= 10) {
		//Điểm = [8; 10] xếp loại "Giỏi"
		toRank = "Gioi";
	}
	else if (studentInput.score >= 6.5) {
		//Điểm = [6.5; 8) xếp loại "Khá"
		toRank = "Kha";
	}
	else if (studentInput.score >= 5) {
		//Điểm = [5; 6.5) xếp loại "Trung bình"
		toRank = "Trung binh";
	}
	else {
		//Điểm < 5 xếp loại "Không đạt"
		toRank = "Khong dat";
	}
	return toRank;
}
void inputAmountOfStudents(char* amountOfStudents) {
	regex amountExpr("[1-9][0-9]?");
			//vd: !"#$%&'()*+,/:;<=>?@
			//Nếu số đó là sô thực. Nhập lại (Vì sô lượng sv thì không lẻ)
			//Số lượng không âm
			//Nếu chuỗi nhập chứa các ký tự lạ. Nhập lại.
	do {
		cout << "Nhap so luong sinh vien: ";
		gets_s(amountOfStudents, 100);
		if (!regex_match(amountOfStudents, amountExpr)) {
			cout << "So luong nhap khong hop le hoac bi am. Nhap lai\n";
		}
	} while (!regex_match(amountOfStudents, amountExpr));
}
void uprFirst(char fullName[]) {
	char * p, * p1 = NULL, res[10][15];//mảng res[] có 10 phần tử, mỗi phần tử có độ dài tối đa là 15.
	int index = 0, i = 0, countSetw = 0;
	const char* delim = " ,.;\n\t";//Biến lưu trữ các dấu câu.

	p = strtok_s(fullName, delim, &p1);// Tách từ đầu tiên của chuỗi sau đó trỏ biến p1 và địa chỉ của chuỗi còn lại.
	
	while (p != NULL) {
		strcpy_s(res[index++], p);//Tách từ xong lưu chữ vào mảng res[], index là số từ tăng dần.
		p = strtok_s(NULL, delim, &p1);//Tiếp tục tách chuỗi còn lại cho đến khi con trỏ p trỏ tới NULL (hết chuỗi).
	}
	while (i < index) {
		countSetw += strlen(res[i]) + 1;//Đếm xem sau khi chuẩn hóa thì độ dài của họ tên là bao nhiêu
		if (res[i][0] >= 'a' && res[i][0] <= 'z') {
			res[i][0] -= 32;
			//In hoa chữ cái đầu của mỗi chữ nếu chữ đầu là chữ thường (Trường hợp chữ đó là chữ hoa thì giữ nguyên).
		}
		for (int j = 1; j < strlen(res[i]); j++) {
			//Và sau chữ cái thứ nhất của mỗi chữ nếu tồn tại chữ nào viết hoa thì chuyển thành chữ thường
			if (res[i][j] >= 'A' && res[i][j] <= 'Z') {
				res[i][j] += 32;//
			}
		}
		i++;
	}
	for (int j = 0; j < index; j++) {
		cout << res[j] << " ";
	}
	cout << setw(40 - countSetw);
}
void inputInformation(student*& studentInput, int n) {
	//Hàm nhập thông tin của từng sinh viên.
	studentInput = new student[n];//Mảng cấu trúc n sinh viên.
	char diem[20] = "0", *pEnd;
	regex nameExpr("[a-zA-Z ]+");//Tên không chứa ký tự đặc biệt.
	regex scoreExpr("[0-9]\\.?[0-9]{0,3}|10");//Điểm nằm trong đoạn 0 đến 10.
	for (int i = 0; i < n; i++) {
		cout << "===============================";
		cout << "\nSinh vien " << i + 1 << " :\n";
		do {
			cout << "Ho va ten: ";
			gets_s(studentInput[i].fullName);
			if (!regex_match(studentInput[i].fullName, nameExpr)) {
				cout << "Ten khong hop le. Nhap lai!\n";
			}
		} while (!regex_match(studentInput[i].fullName, nameExpr));
		do {
			cout << "Diem: ";
			gets_s(diem);
			if (!regex_match(diem, scoreExpr)) {
				//Thang điểm [0; 10]. nếu không thuộc, nhập lại
				cout << "Diem khong hop le. Nhap lai!\n";
			}
		} while (!regex_match(diem, scoreExpr));
		studentInput[i].score = strtof(diem, &pEnd);//chuyển điểm ở dạng chuỗi thành dạng số thực rồi lưu vào trường rank
		studentInput[i].rank = toRank(studentInput[i]);//Xếp loại sinh viên rồi lưu vào trường rank 
	}
}
char* getName(char* fullName) {
	if (fullName == NULL) return NULL;
	char* pTemp = strrchr(fullName, ' ');
	if (pTemp == NULL) return fullName;
	else return pTemp + 1;
}
void arrangeAlphabet(student*& studentInput, int n) {
	student temp;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (strcmp(getName(studentInput[i].fullName), getName(studentInput[j].fullName)) > 0) {
				//Sắp xếp tên của hai người thep bảng chữ cái (mã ASCII).
				temp = studentInput[i];
				studentInput[i] = studentInput[j];
				studentInput[j] = temp;
			}
		}
	}
}
void outputList(student*& studentInput, int n) {
	cout << "\nXEP LOAI SINH VIEN\n";
	cout << "HO VA TEN" << "" << setw(31) << "DIEM" << "" << setw(20) << "XEP LOAI\n";
	setColor(4);
	for (int i = 0; i < n; i++) {
		uprFirst(studentInput[i].fullName);
		cout << studentInput[i].score;
		cout << setw(20) << studentInput[i].rank;
		cout << endl;
	}
	setColor(2);
}
int main() {
	system("color f2");
	char N[100];
	int n;
	student* studentInput;
	studentInput = new student[100];//Mảng cấu trúc sinh viên 
	inputAmountOfStudents(N);
	//Nhập số lượng sinh viên
	n = atoi(N);//chuyển số lượng sinh viên từ chuỗi sang dạng int
	studentInput = new student[n];
	inputInformation(studentInput, n);
	arrangeAlphabet(studentInput, n);
	outputList(studentInput, n);
	cout << endl;
	delete[] studentInput;
	system("pause");
	
}