#include<iostream>
#include<stdio.h>
#include<xstring>
#include<istream>
#include<string>
#include<iomanip>
#include<stdlib.h>
#include<ctype.h>
#include<regex>

using namespace std;

typedef struct {
	int day;
	int month;
	int year;
} date;
typedef struct {
	char lastName[20];
	char firstName[20];
	float salary;
	date birthDay;
	char address[20];
} list;
void inputAmount(char* soLuong) {
	regex amountExpr("[1-9][0-9]?");
	//vd: !"#$%&'()*+,/:;<=>?@
	//Nếu số đó là sô thực. Nhập lại (Vì sô lượng sv thì không lẻ)
	//Số lượng không âm
	//Nếu chuỗi nhập chứa các ký tự lạ. Nhập lại.
	do {
		cout << "Nhap so luong can bo nhan vien: ";
		gets_s(soLuong, 100);
		if (!regex_match(soLuong, amountExpr)) {
			cout << "So luong nhap khong hop le. Nhap lai!\n";
		}
	} while (!regex_match(soLuong, amountExpr));
}
void initArray(list *&canBoCongNhan, int length) {
	regex nameExpr("[a-zA-Z ]+");//tên không chứa ký tự đặc biệt
	regex dayExpr("0[^0]|[^0]|[1|2]?[0-9]|3[0|1]");//Ngày từ 01 tới 31
	regex monthExpr("0[^0]|[^0]|1[0-2]");//Tháng từ 1 tới 12
	regex yearExpr("19[0-9]{2}|20[0-9]{2}");//Năm từ 1900 đến 2099
	regex salaryExpr("0|\\d+.?\\d+");//Lương
	canBoCongNhan = new list[length];
	char d[20] = "", m[20] = "", y[20] = "", luong[100] = "0", *pEnd;
	for (int i = 0; i < length; i++) { 
		cout << "\nNhan vien (Can bo) " << i + 1 << ":\n";
		do {
			cout << "Nhap ho va ten dem: ";
			gets_s(canBoCongNhan[i].lastName);
			if (!regex_match(canBoCongNhan[i].lastName, nameExpr)) {
				cout << "ho va ten dem co chua ky tu khong hop le. Nhap lai!\n";
			}
		} while (!regex_match(canBoCongNhan[i].lastName, nameExpr));
		do {
			cout << "Nhap ten: ";
			gets_s(canBoCongNhan[i].firstName);
			if (!regex_match(canBoCongNhan[i].firstName, nameExpr)) {
				cout << "Ten co chua ky tu khong hop le. Nhap lai!\n";
			}
		} while (!regex_match(canBoCongNhan[i].firstName, nameExpr));
		do {
			cout << "Ngay sinh: ";
			gets_s(d);
			if (!regex_match(d, dayExpr)) {
				cout << "Ngay sinh khong hop le. Nhap lai\n";
			}
		} while (!regex_match(d, dayExpr));
		canBoCongNhan[i].birthDay.day = atoi(d);
		do {
			cout << "Thang sinh: ";
			gets_s(m);
			if (!regex_match(m, monthExpr)) {
				cout << "Thang sinh khong hop le. Nhap lai!\n";
			}
		} while (!regex_match(m, monthExpr));
		canBoCongNhan[i].birthDay.month = atoi(m);
		do {
			cout << "Nam sinh: ";
			gets_s(y);
			if (!regex_match(y, yearExpr)) {
				cout << "Nam sinh khong hop le. Nhap lai!\n";
			}
		} while (!regex_match(y, yearExpr));
		canBoCongNhan[i].birthDay.year = atoi(y);
		do {
			cout << "Nhap luong: ";
			gets_s(luong);
			if (!regex_match(luong, salaryExpr)) {
				cout << "Luong khong hop le. Lay 3 chu so thap phan. Nhap lai!\n";
			}
		
		} while (!regex_match(luong, salaryExpr));
		canBoCongNhan[i].salary = strtof(luong, &pEnd);
		cout << "Nhap dia chi: ";
		gets_s(canBoCongNhan[i].address);
	}
} 
void uprFirst(char lastname[], char firstname[]) {
	char* p, * p1 = NULL, res[10][15];//mảng res[] có 10 phần tử, mỗi phần tử có độ dài tối đa là 15.
	int index = 0, i = 0, countSetw = 0;
	const char* delim = " ,.;\n\t";//Biến lưu trữ các dấu câu.

	p = strtok_s(lastname, delim, &p1);// Tách từ đầu tiên của chuỗi sau đó trỏ biến p1 và địa chỉ của chuỗi còn lại.

	while (p != NULL) {
		strcpy_s(res[index++], p);//Tách từ xong lưu chữ vào mảng res[], index là số từ tăng dần.
		p = strtok_s(NULL, delim, &p1);//Tiếp tục tách chuỗi còn lại cho đến khi con trỏ p trỏ tới NULL (hết chuỗi).
	}
	while (i < index) {
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
		countSetw += strlen(res[j]);//Đếm xem sau khi chuẩn hóa thì độ dài của họ tên là bao nhiêu
	}

	index = 0;
	i = 0;
	p = strtok_s(firstname, delim, &p1);// Tách từ đầu tiên của chuỗi sau đó trỏ biến p1 và địa chỉ của chuỗi còn lại.

	while (p != NULL) {
		strcpy_s(res[index++], p);//Tách từ xong lưu chữ vào mảng res[], index là số từ tăng dần.
		p = strtok_s(NULL, delim, &p1);//Tiếp tục tách chuỗi còn lại cho đến khi con trỏ p trỏ tới NULL (hết chuỗi).
	}
	while (i < index) {
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
		countSetw += strlen(res[j]);//Đếm xem sau khi chuẩn hóa thì độ dài của họ tên là bao nhiêu
	}
	cout << setw(40 - countSetw);
}
void arrangeAlphabet(list *&canBoCongNhan, int length) {
	list temp;
	for (int i = 0; i < length; i++) {
		for (int j = i + 1; j < length; j++) {
			if (strcmp(canBoCongNhan[i].firstName, canBoCongNhan[j].firstName) > 0) {
				temp = canBoCongNhan[i];
				canBoCongNhan[i] = canBoCongNhan[j];
				canBoCongNhan[j] = temp;
			}
		}
	}
}
void printList(list*& canBoCongNhan, int length) {
	cout << "STT" << setw(26) << "Ho ten" << setw(25) << "Luong" << setw(29) << "Ngay sinh" << setw(27) << "Dia chi" << endl;
	for (int i = 0; i < length; i++) {
		cout << i + 1 << setw(15);
		uprFirst(canBoCongNhan[i].lastName, canBoCongNhan[i].firstName);
		cout << canBoCongNhan[i].salary << setw(23)
			<< canBoCongNhan[i].birthDay.day << "/" << canBoCongNhan[i].birthDay.month << "/" << canBoCongNhan[i].birthDay.year << setw(20 + strlen(canBoCongNhan[i].address))
			<< canBoCongNhan[i].address << endl;
	}
}

int main() {
	system("color 02");
	char length[100];
	int n;
	char s[40];
	list *canBoCongNhan;
	inputAmount(length);
	n = atoi(length);//chuyên kiểu char sang kiểu int 
	canBoCongNhan = new list[n];
	initArray(canBoCongNhan, n);
	arrangeAlphabet(canBoCongNhan, n);
	cout << "\n================================================\n";
	printList(canBoCongNhan, n);
	cout << endl;
	system("pause");
}