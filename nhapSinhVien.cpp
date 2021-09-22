#include <iostream>
#include <regex>
#include <stdio.h>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <iomanip>
#include <Windows.h>
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN

using namespace std;

typedef struct {
	int day;
	int month;
	int year;
} date;

typedef struct {
	char studentID[40];//Mã số sinh viên
	char fullName[40];//Họ và tên
	char gender[10];//giới tính
	date birthDay;//Ngày tháng năm sinh
	char grade[40];//Lớp 
	float AverageScore;//ĐIểm trung bình
} student;

void inputAmountOfStudents(char amount[40]) {
	regex amountExpr("\\d+");
	do {
		cout << "Nhap so luong sinh vien: ";
		gets_s(amount, 40);
		if (!regex_match(amount, amountExpr)) {
			cout << "So luong nhap khong hop le. ";
		}
	} while (!regex_match(amount, amountExpr));
}
void devidingBirthDay(student& sinhVien, char* birthDay) {
	char* p = NULL, * pNext = NULL;
	p = strtok_s(birthDay, "/", &pNext);//Tách ngày từ chuỗi dd/mm/yyyy
	sinhVien.birthDay.day = atoi(p);//chuyển chuỗi đã tách sang dạng số nguyên rồi gán cho thuộc tính ngày
	p = strtok_s(NULL, "/", &pNext);//Tiếp tục tách chuỗi cũ mm/yyyy để lấy tháng (mm)
	sinhVien.birthDay.month = atoi(p);//tương tự như bước trên
	p = strtok_s(NULL, "/", &pNext);//Tách thêm một lần nữa để lấy năm
	sinhVien.birthDay.year = atoi(p);//
}
void toUpper(char* s) {//chuyển in hoa cả 1 chuỗi
	int i = 0;
	while (s[i] != '\0') {
		if (s[i] >= 'a' && s[i] <= 'z') {
			s[i] -= 32;
		}
		i++;
	}
}
void inputOneStudent(vector<student> &studentsList) {//Nhập 1 sinh viên
	student sinhVien;
	int i;
	char birthDay[20] = "", score[20] = "0", * p, * pEnd;
	regex studentIDExpr("[N|B]\\d{2}(DC)(CN|AT|VT|KT|MR|PT|DT)[0-9]{3}");
	regex nameExpr("[A-Z ]+");//Không nhận ký tự đặc biệt
	regex genderExpr("(NAM)|(NU)|(KHAC)");//  NAM, NU 
	regex birthDayExpr("(0[^0]|[^0]|[1|2]?[0-9]|3[0|1])/(0[^0]|[^0]|1[0-2])/(19[0-9]{2}|20[0-9]{2})");
	//d(d)/m(m)/yyyy hoặc 
	regex gradeExpr("D\\d{2}(CQ)(CN|AT|VT|KT|MR|PT|DT)[0-9]{2}-[N|B]");//D20CQCN02-N
	regex scoreExpr("[0-9]\\.?[0-9]{0,3}|10");//Điểm nằm trong đoạn 0 đến 10.
	do {
		cout << "Nhap ma so sinh vien: ";
		gets_s(sinhVien.studentID);
		toUpper(sinhVien.studentID);
		if (!regex_match(sinhVien.studentID, studentIDExpr)) {
			cout << "Ma sinh vien khong hop le. Mau: n20dccn083 N20DCVT078.\n";
		}
	} while (!regex_match(sinhVien.studentID, studentIDExpr));
	
	do {
		cout << "Nhap ho ten sinh vien: ";
		gets_s(sinhVien.fullName);
		toUpper(sinhVien.fullName);
		if (!regex_match(sinhVien.fullName, nameExpr)) {
			cout << "Ten khong hop le.\n";
		}
	} while (!regex_match(sinhVien.fullName, nameExpr));
	do {
		cout << "Nhap gioi tinh: ";
		gets_s(sinhVien.gender);
		toUpper(sinhVien.gender);
		if (!regex_match(sinhVien.gender, genderExpr)) {
			cout << "Gioi tinh khong hop le.\n";
		}
	} while (!regex_match(sinhVien.gender, genderExpr));
	do {
		cout << "Nhap ngay thang nam sinh (dd/mm/yyyy): ";
		gets_s(birthDay);
		if (!regex_match(birthDay, birthDayExpr)) {
			cout << "Ngay sinh khong hop le.\n";
		}
	} while (!regex_match(birthDay, birthDayExpr));
	devidingBirthDay(sinhVien, birthDay);
	do {
		cout << "Nhap lop: ";
		gets_s(sinhVien.grade);
		toUpper(sinhVien.grade);
		if (!regex_match(sinhVien.grade, gradeExpr)) {
			cout << "Lop nhap khong hop le. vd: d20cqcn01-n, D20CQAT01-B.\n";
		}
	} while (!regex_match(sinhVien.grade, gradeExpr));
	do {
		cout << "Nhap diem trung binh: ";
		gets_s(score);
		if (!regex_match(score, scoreExpr)) {
			cout << "Diem khong hop le. [0; 10]. Lay 3 so thap phan sau dau phay.\n";
		}
	} while (!regex_match(score, scoreExpr));
	sinhVien.AverageScore = strtof(score, &pEnd);
	studentsList.push_back(sinhVien);
	cout << endl;
}
void inputList(vector<student> &studentsList, int n) {//Nhập sinh viên với số lượng cho trước
	for (int i = 0; i < n; i++) {
		cout << "\nSinh vien " << i + 1 << " :\n";
		inputOneStudent(studentsList);
	}
}
void outputOneStudent(student sinhVien) {//xuất thông tin 1 sinh vien
	/*cout << "\nMa so sinh vien: " << sinhVien.studentID << endl;
	cout << "Ho va ten: " << sinhVien.fullName << endl;
	cout << "Gioi tinh: " << sinhVien.gender << endl;
	cout << "Ngay sinh: " << sinhVien.birthDay.day << "/" << sinhVien.birthDay.month << "/" << sinhVien.birthDay.year << endl;
	cout << "Lop: " << sinhVien.grade << endl;
	cout << "Diem trung binh: " << sinhVien.AverageScore << endl;*/
	cout << sinhVien.studentID << setw(22)
		<< sinhVien.fullName << "            "
		<< sinhVien.gender << "      "
		<< sinhVien.birthDay.day << "/" << sinhVien.birthDay.month << "/" << sinhVien.birthDay.year << "  "
		<< sinhVien.grade << "   "
		<< sinhVien.AverageScore << endl;
}
void outputList(vector<student> studentsList) {//xuất danh sách
		cout << "\nDanh sach sinh vien:\n";
		cout << "   MSSV         Ho Va Ten                Gioi Tinh  Ngay Sinh       Lop      Diem\n";
	for (auto i = studentsList.begin(); i < studentsList.end(); ++i) {
		outputOneStudent(*i);
	}
}
void searchAndPrintStudentsHavingScoreGreaterThan5(vector<student> studentsList) {
	//tìm và in số sinh viên có điểm trung bình > 5
	cout << "\nNhung sinh vien co diem lon hon 5 la:\n";
	for (auto i = studentsList.begin(); i < studentsList.end(); ++i) {
		if ((*i).AverageScore > 5) {
			outputOneStudent(*i);
		}
	}
}
void searchAndPrintITStudents(vector<student> studentsList) {//tìm và in số sinh viên học ngành công nghệ thông tin
	cout << "Nhung sinh vien hoc nganh cong nghe thong tin la:\n";
	for (auto i = studentsList.begin(); i < studentsList.end(); ++i) {
		if(strstr((*i).grade, "CN") != NULL) {//tìm xem trong mã lớp có chữ "CN" hay không bằng hàm strstr
			outputOneStudent(*i);
			printf("\n");
		}
	}
}
int countingFemaleStudents(vector<student> studentsList) {
	int count = 0;
	for (auto i = studentsList.begin(); i < studentsList.end(); ++i) {
		if (strcmp((*i).gender, "NU") == 0) {//Nữ trong danh sách
			count++;
		}
	}
	return count;
}

void searchAndPrintBestStudents(vector<student> studentsList) {
	float maxScore = studentsList[0].AverageScore;
	for (auto i = studentsList.begin(); i < studentsList.end(); ++i) {
		if ((*i).AverageScore > maxScore) {
			maxScore = (*i).AverageScore;
		}
	}
	cout << "Nhung ban co diem trung binh cao nhat la:\n";
	for (auto i = studentsList.begin(); i < studentsList.end(); ++i) {
		if ((*i).AverageScore == maxScore) {
			outputOneStudent(*i);
			cout << endl;
		}
	}
}

void searchStudentByID(vector<student> studentsList, char *ID) {
	bool check = 0;
	
	regex studentIDExpr("[N|B]\\d{2}(DC)(CN|AT|VT|KT|MR|PT|DT)[0-9]{3}");
	cin.ignore();
	do {
		cout << "Nhap ma sinh vien cua sinh vien ban muon tim: ";
		gets_s(ID, 40);
		toUpper(ID);
		if (!regex_match(ID, studentIDExpr)) {
			cout << "Ma tim kiem khong hop le.\n";
		}
	} while (!regex_match(ID, studentIDExpr));
	cout << "Ket qua:\n";
	for (auto i = studentsList.begin(); i < studentsList.end(); ++i) {
		if (strcmp((*i).studentID, ID) == 0) {//sử dụng hàm strcmp để so sánh
			outputOneStudent(*i);
			check = 1;
		}
	}
	if (check == 0) {
		cout << "Khong tim thay ket qua. Khong co sinh vien nay trong danh sach\n";
	}
}
//điểm trung bình lớn hơn 5
//student* searchITStudents();//sinh viên ngành công nghệ thông tin
//int countingFemaleStudent();//Đếm sinh viên nữ
//student* studentsHaveGreatestScore();//sinh viên có điểm trung bình cao nhất
void deleteOneStudent(vector<student> studentsList, char ID[]) {
	//hàm này thực hiện xóa một sinh viên khỏi danh sách
	toUpper(ID);
	for (auto i = studentsList.begin(); i < studentsList.end(); ++i) {
		if (strcmp((*i).studentID, ID) == 0) {//so sánh bằng lệnh strcmp
			studentsList.erase(i);//xóa sinh viên ra khỏi danh sách
		}
	}
}

void swap(student &a, student &b)
{//Đổi chỗ học sinh viên
	student t = a;
	a = b;
	b = t;
}

int partition(vector<student> studentsList, int low, int high)
{
	float pivot = studentsList[high].AverageScore;    // pivot
	int left = low;
	int right = high - 1;
	while (true) {
		while (left <= right && studentsList[left].AverageScore < pivot) left++;
		while (right >= left && studentsList[right].AverageScore > pivot) right--;
		if (left >= right) break;
		swap(studentsList[left], studentsList[right]);
		left++;
		right--;
	}
	swap(studentsList[left], studentsList[high]);
	return left;
}

/* Hàm thực hiện giải thuật quick sort */
void quickSort(vector<student> studentsList,int low, int high)
{
	if (low < high)
	{
		/* pi là chỉ số nơi phần tử này đã đứng đúng vị trí
		 và là phần tử chia mảng làm 2 mảng con trái & phải */
		int pi = partition(studentsList, low, high);

		// Gọi đệ quy sắp xếp 2 mảng con trái và phải
		quickSort(studentsList, low, pi - 1);
		quickSort(studentsList, pi + 1, high);
	}
}
int main() {

	char amount[40], ID[40] = "\0";
	vector<student> studentsList;
	int n, high = 0;
	int option;
	do {
		cout << "\n===========================================================\n";
		cout << "1. Nhap mot sinh vien.\n";
		cout << "2. Nhap nhieu sinh vien.\n";
		cout << "3. Xuat danh sach sinh vien.\n";
		cout << "4. Xuat danh sach nhung sinh vien co diem lon hon 5.\n";
		cout << "5. Xuat danh sach sinh vien hoc nganh cong nghe thong tin.\n";
		cout << "6. Dem so luong sinh vien nu.\n";
		cout << "7. Xuat sinh vien co diem trung binh cao nhat.\n";
		cout << "8. Them mot sinh vien vao cuoi danh sach.\n";
		cout << "9. Tim sinh vien theo ma so. Xoa sinh vien do.\n";
		cout << "10. Sap xep theo diem trung binh tang dan.\n";
		cout << "11. Thoat.\n";
		cout << "NHAP MOT LUA CHON: ";
		cin >> option;
		cout << "\n===========================================================\n";
		switch (option) {
		default:
			break;
		case 1:
			cin.ignore();
			cout << "Nhap thong tin sinh vien:\n";
			inputOneStudent(studentsList);
			high++;
			break;
		case 2:
			cin.ignore();
			inputAmountOfStudents(amount);
			n = atoi(amount);
			inputList(studentsList, n);
			break;
			high += n;
		case 3:
			outputList(studentsList);
			break;
		case 4:
			searchAndPrintStudentsHavingScoreGreaterThan5(studentsList);
			break;
		case 5:
			searchAndPrintITStudents(studentsList);
			break;
		case 6:
			n = countingFemaleStudents(studentsList);
			if (n == 0) cout << "Danh sach khong co sinh vien nu nao ca.\n";
			else cout << "Co " << n << " sinh vien nu trong danh sach.\n";
			break;
		case 7:
			searchAndPrintBestStudents(studentsList);
			break;
		case 8:
			cin.ignore();
			inputOneStudent(studentsList);
			high++;
			break;
		case 9:
			searchStudentByID(studentsList, ID);
			cout << "Ban co muon xoa sinh vien nay ra khoi danh sach\n"
				<< "1. Co\n"
				<< "2. Khong\n";
			cin >> n;
			if (n == 1) {//có thì n = 1
					deleteOneStudent(studentsList, ID);
					high--;
			}
			break;
		case 10:
			cout << "Sau khi sap xep theo thu tu tang dan cua diem trung binh danh sach la:\n";
			quickSort(studentsList, 0, high - 1);
			outputList(studentsList);
		}
	} while (option != 11);
}
//typedef struct date {
//	int day;
//	int month;
//	int year;
// };
//typedef struct {
//	char mSSV[40];
//	char name[40];
//	char gioiTinh[20];
//	date birthDay;
//	char lop[40];
//	float diemTrungBinh;
//} sinhVien;
//
//void inputAmountOfStudents(char* amountOfStudents) {
//	regex amountExpr("[1-9][0-9]?");
//	//vd: !"#$%&'()*+,/:;<=>?@
//	//Nếu số đó là sô thực. Nhập lại (Vì sô lượng sv thì không lẻ)
//	//Số lượng không âm
//	//Nếu chuỗi nhập chứa các ký tự lạ. Nhập lại.
//	do {
//		cout << "Nhap so luong sinh vien: ";
//		gets_s(amountOfStudents, 100);
//		if (!regex_match(amountOfStudents, amountExpr)) {
//			cout << "So luong nhap khong hop le hoac bi am. Nhap lai\n";
//		}
//	} while (!regex_match(amountOfStudents, amountExpr));
//}
//void inputInformation(sinhVien*& studentInput, int n) {
//	//Hàm nhập thông tin của từng sinh viên.
//	studentInput = new sinhVien[n];//Mảng cấu trúc n sinh viên.
//	char diem[20] = "0", * pEnd, d[20] = "", m[20] = "", y[20] = "";
//	regex nameExpr("[a-zA-Z ]+");//Tên không chứa ký tự đặc biệt.
//	regex mssv("");
//	regex gioiTinh("Nam|Nu|nam|nu");
//	regex dayExpr("0[^0]|[^0]|[1|2]?[0-9]|3[0|1]");//Ngày từ 01 tới 31
//	regex monthExpr("0[^0]|[^0]|1[0-2]");//Tháng từ 1 tới 12
//	regex yearExpr("19[0-9]{2}|20[0-9]{2}");//Năm từ 1900 đến 2099
//	regex lop("D|C");
//	for (int i = 0; i < n; i++) {
//		cout << "===============================";
//		cout << "\nSinh vien " << i + 1 << " :\n";
//		cout << "Nhap ma so sinh vien: ";
//		gets_s(studentInput[i].mSSV);
//			
//		do {
//			cout << "Ho va ten: ";
//			gets_s(studentInput[i].name);
//			if (!regex_match(studentInput[i].name, nameExpr)) {
//				cout << "Ten khong hop le. Nhap lai!\n";
//			}
//		} while (!regex_match(studentInput[i].name, nameExpr));
//		do {
//			cout << "Nhap gioi tinh:";
//			gets_s(studentInput[i].gioiTinh);
//			if (!regex_match(studentInput[i].gioiTinh, gioiTinh)) {
//				cout << "Nam hoac Nu. Nhap lai.\n";
//			}
//		} while (!regex_match(studentInput[i].gioiTinh, gioiTinh));
//		do {
//			cout << "Ngay sinh: ";
//			gets_s(d);
//			if (!regex_match(d, dayExpr)) {
//				cout << "Ngay sinh khong hop le. Nhap lai\n";
//			}
//		} while (!regex_match(d, dayExpr));
//		studentInput[i].birthDay.day = atoi(d);
//		do {
//			cout << "Thang sinh: ";
//			gets_s(m);
//			if (!regex_match(m, monthExpr)) {
//				cout << "Thang sinh khong hop le. Nhap lai!\n";
//			}
//		} while (!regex_match(m, monthExpr));
//		studentInput[i].birthDay.month = atoi(m);
//		do {
//			cout << "Nam sinh: ";
//			gets_s(y);
//			if (!regex_match(y, yearExpr)) {
//				cout << "Nam sinh khong hop le. Nhap lai!\n";
//			}
//		} while (!regex_match(y, yearExpr));
//		studentInput[i].birthDay.year = atoi(y);
//		do {
//			cout << "Nhap lop: ";
//			gets_s(studentInput[i].lop);
//			if (!regex_match(studentInput[i].lop, lop)) {
//				cout << "D hoc C (dai hoc hoac cao dang). Nhap lai\n";
//			}
//		} while (!regex_match(studentInput[i].lop, lop));
//
//		do {
//			cout << "Diem trung binh: ";
//			gets_s(diem);
//			if (!regex_match(diem, scoreExpr)) {
//				//Thang điểm [0; 10]. nếu không thuộc, nhập lại
//				cout << "Diem khong hop le. Nhap lai!\n";
//			}
//		} while (!regex_match(diem, scoreExpr));
//		studentInput[i].diemTrungBinh = strtof(diem, &pEnd);//chuyển điểm ở dạng chuỗi thành dạng số thực rồi lưu vào trường rank
//	}
//}
//void uprFirst(char fullName[]) {
//	char* p, * p1 = NULL, res[10][15];//mảng res[] có 10 phần tử, mỗi phần tử có độ dài tối đa là 15.
//	int index = 0, i = 0, countSetw = 0;
//	const char* delim = " ,.;\n\t";//Biến lưu trữ các dấu câu.
//
//	p = strtok_s(fullName, delim, &p1);// Tách từ đầu tiên của chuỗi sau đó trỏ biến p1 và địa chỉ của chuỗi còn lại.
//
//	while (p != NULL) {
//		strcpy_s(res[index++], p);//Tách từ xong lưu chữ vào mảng res[], index là số từ tăng dần.
//		p = strtok_s(NULL, delim, &p1);//Tiếp tục tách chuỗi còn lại cho đến khi con trỏ p trỏ tới NULL (hết chuỗi).
//	}
//	while (i < index) {
//		countSetw += strlen(res[i]) + 1;//Đếm xem sau khi chuẩn hóa thì độ dài của họ tên là bao nhiêu
//		if (res[i][0] >= 'a' && res[i][0] <= 'z') {
//			res[i][0] -= 32;
//			//In hoa chữ cái đầu của mỗi chữ nếu chữ đầu là chữ thường (Trường hợp chữ đó là chữ hoa thì giữ nguyên).
//		}
//		for (int j = 1; j < strlen(res[i]); j++) {
//			//Và sau chữ cái thứ nhất của mỗi chữ nếu tồn tại chữ nào viết hoa thì chuyển thành chữ thường
//			if (res[i][j] >= 'A' && res[i][j] <= 'Z') {
//				res[i][j] += 32;//
//			}
//		}
//		i++;
//	}
//	for (int j = 0; j < index; j++) {
//		cout << res[j] << " ";
//	}
//}
//void outputList(sinhVien*& students, int n) {
//	for (int i = 0; i < n; i++) {
//		cout << "Sinh vien " << i + 1 << endl;
//		uprFirst(students[i].name);
//		cout << endl;
//		cout << "Gioi tinh: " << students[i].gioiTinh << endl;
//		cout << "Ngay sinh: " << students[i].birthDay.day << "/" << students[i].birthDay.month << "/" << students[i].birthDay.year << endl;
//		cout << "Diem trung binh: " << students[i].diemTrungBinh << endl;
//		cout << "Lop: " << students[i].lop << endl;
//	}
//	cout << "================================\n";
//}
//int main() {
//	system("color f2");
//	char soLuongSinhVien[100];
//	sinhVien *students;
//	int n;
//
//	inputAmountOfStudents(soLuongSinhVien);
//	n = atoi(soLuongSinhVien);
//	students = new sinhVien[n];
//	inputInformation(students, n);
//	cout << "\n==================================================\n";
//	outputList(students, n);
//	system("pause");
//}