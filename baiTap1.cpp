/*Xem một phân số là một cấu trúc có hai trường là tử số và mẫu số.
Hãy viết chương trình thực hiện các phép toán cộng, trừ, nhân, chia hai phân số. 
(Các kết quả phải tối giản).*/

#include<iostream>
#include<math.h>
#include<string>
#include<stdlib.h>
#include<cctype>
#include<stdio.h>
#include<regex>
#include<Windows.h>

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

	//
	if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
	{
		//
		wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
		SetConsoleTextAttribute(hStdOut, wColor);
	}
	return;
} 
int GCD(int a, int b) {
	
	//Hàm tìm ước chung lớn nhất.
	//Mục đích để tối giản phân số. 
	//Ví dụ: phân số 15/20. GCD(15, 20) = 5. Lấy cả tử và mẫu chia cho 5 thì ra phân số tối giản (3/4).
	if (a == 0) return b;
	else if (b == 0) return a;
	else if (a == 0 && b == 0) return 1;
	else {
		if (a < 0) {
			a = -a;
		}
		if (b < 0) {
			b = -b;
		}
		//Nếu tử và mẫu âm thì chuyển thành số dương.
		while (a != b) {
			//Trừ số lớn hơn cho số bé hơn cho đến khi chúng bằng nhau
			//Kết quả đó chính là ước số chung lớn nhất 
			if (a > b) {
				a -= b;
			}
			else {
				b -= a;
			}
		}
	}
	return a;
}
typedef struct {
	//Khai báo cấu trúc có hai trường là tử số và mẫu số.
	int numerator;
	int denominator;
} fraction;
void inputFraction(fraction &myFraction) {
	//Hàm để nhập tử số và mẫu số của cấu trúc fraction.
	regex numeratorExpr("\\-?[0-9]+");
	regex denominatorExpr("\\-{0,1}[^0]([0-9]+)?");
	char a[20] = "0", b[20] = "";
	do {
		cout << "Enter numerator: ";
		//Nhập tử số ở dạng chuỗi.
		gets_s(a);
		if (!regex_match(a, numeratorExpr)) {
			//Nếu tử số là một ký tự không hợp lệ hoặc không phải là một số nguyên
			//thì lệnh do while sẽ bắt nhập lại.
			cout << "Invalid number or not integer number. Numerator must be a INTEGER. Enter again.\n";
		}
	} while (!regex_match(a, numeratorExpr));
	do {
		cout << "Enter denominator: ";
		//Nhập mẫu số ở dạng chuỗi
		gets_s(b);
		if (!regex_match(b, denominatorExpr)) {
			//Nếu tử số là một ký tự không hợp lệ hoặc không phải là một số nguyên.
			//thì lệnh do while sẽ bắt nhập lại.
			cout << "Invalid number or not integer number (equal to 0). Denominator must be a INTEGER. Enter again!\n ";
		}
	} while (!regex_match(b, denominatorExpr) || atoi(b) == 0);
	//2 câu lệnh dưới là chuyển chuỗi thành kiểu số nguyên bằng hàm atoi.
	if (atoi(a) == 0);
	else {
		myFraction.numerator = atoi(a) / GCD(atoi(a), atoi(b));
		myFraction.denominator = atoi(b) / GCD(atoi(a), atoi(b));
	}
}
void display(fraction myFraction) {
	setColor(4);
	if (abs(myFraction.numerator) == abs(myFraction.denominator) || myFraction.numerator == 0) {
		cout << myFraction.numerator / myFraction.denominator;
		//Nếu trị tuyệt đối tử bằng trị tuyệt đối mẫu hoặc tử bằng 0 thì in ra kết quả số nguyên; 
	}
	else if (myFraction.denominator < 0 && myFraction.numerator > 0) {
		cout << -myFraction.numerator << "/" << -myFraction.denominator;
		//Chuyển dấu (-) lên tử nếu mẫu âm và tử dương.
	}
	else if (myFraction.numerator < 0 && myFraction.denominator < 0) {
		cout << -myFraction.numerator << "/" << -myFraction.denominator;
		//Nếu cả tử và mẫu đều âm thì in ra phân số dương.
	}
	else if (myFraction.denominator == 1) {
		cout << myFraction.numerator;
		//Nếu tử = 1 thì hiển thị ra tử 
	}
	else if (myFraction.denominator == -1) {
		cout << myFraction.numerator * (-1);
		// Nếu mẫu = -1 thì hiển thị tử *(-1)
	}
	else {
		cout << myFraction.numerator << "/" << myFraction.denominator;
		//
	}
	setColor(2);
}
fraction addFraction(fraction fraction1, fraction fraction2) {
	int a, b;
	fraction resultFraction;
	//                       Quy đồng 2 phân số.
	//              a / b + c / d = (a * d + b * c) / (b * d)
	a = fraction1.numerator * fraction2.denominator + fraction1.denominator * fraction2.numerator;
	//Tử số
	//             a        *          d             +           b            *          c
	b = fraction1.denominator * fraction2.denominator;
	//Mẫu số
	//                 b       *        d      
	if (a == 0) {
		//Nếu tử = 0 thì phân số = 0
		resultFraction.numerator = 0;
	}
	else {
		//rút gọn phân số bằng cách lấy cả tử và mẫu chia cho ước chung lớn nhất của tử và mẫu
		resultFraction.numerator = a / GCD(a, b);
		resultFraction.denominator = b / GCD(a, b);
	}
	return resultFraction;//Trả về phân số vừa tính được
};
fraction subtractFraction(fraction fraction1, fraction fraction2) {
	int a, b;
	fraction resultFraction;
	//Quy đồng 2 phân số.
	a = fraction1.numerator * fraction2.denominator - fraction1.denominator * fraction2.numerator;
	b = fraction1.denominator * fraction2.denominator;
	if (a == 0) {
		resultFraction.numerator = 0;
	}
	else {
		resultFraction.numerator = a / GCD(a, b);
		resultFraction.denominator = b / GCD(a, b);
	}
	return resultFraction;
};
fraction multiplyFraction(fraction fraction1, fraction fraction2) {
	int a, b;
	fraction resultFraction;
	a = fraction1.numerator * fraction2.numerator;
	//  Tử số nhân tử số
	b = fraction1.denominator * fraction2.denominator;
	// Mẫu số nhân mẫu số
	if (a == 0) {
		resultFraction.numerator = 0;
		//Tương tự phép cộng
	}
	else {
		resultFraction.numerator = a / GCD(a, b);
		resultFraction.denominator = b / GCD(a, b);
	}
	return resultFraction;
}
fraction divideFraction(fraction fraction1, fraction fraction2) {
	int a, b;
	fraction resultFraction;
	//    (a / b) / (c / d) = (a / b) * (d / c)
	a = fraction1.numerator * fraction2.denominator;
	//         Tử số 1      *  mẫu số 2   
	b = fraction1.denominator * fraction2.numerator;
	//         Mẫu số 1        *    Tử số 2
	if (a == 0) {
		resultFraction.numerator = 0;
	}
	else {
		resultFraction.numerator = a / GCD(a, b);
		resultFraction.denominator = b / GCD(a, b);
	}
	return resultFraction;
}
int main() {
	system("color f2");
	fraction fraction1, fraction2;
	unsigned short choice;
	cout << "Enter fraction 1:\n";
	inputFraction(fraction1);
	cout << "\nEnter fraction 2:\n";
	inputFraction(fraction2);
	cout << "==================================================\n";
	cout << "Fraction 1: ";
	display(fraction1);
	cout << "\nFraction 2: ";
	display(fraction2);
	do {
		cout << "\n==================================================\n";
		cout << "1. Adding two fractions.\n";
		cout << "2. Subtracting two fraction.\n";
		cout << "3. Multiplying two fractions:\n";
		cout << "4. Deviding two fractions:\n";
		cout << "5. Input new fractons.\n";
		cout << "6. Exit()\n";
		cout << "Choose an option: ";
		cin >> choice;
		cout << "==================================================\n";
		switch (choice) {
		case 1:
			setColor(4);
			cout << "\nAdding";
			setColor(2);
			cout << " two fractions : ";
			display(addFraction(fraction1, fraction2));
			break;
		case 2:
			setColor(4);
			cout << "\nSubtracting";
			setColor(2);
			cout << " two fractions : ";
			display(subtractFraction(fraction1, fraction2));
			break;
		case 3:
			setColor(4);
			cout << "\nMultiplying";
			setColor(2);
			cout <<" two fractions : ";
			display(multiplyFraction(fraction1, fraction2));
			break;
		case 4:
			setColor(4);
			cout << "\nDeviding";
			setColor(2);
			cout << " two fractions : ";
			display(divideFraction(fraction1, fraction2));
			break;
		case 5:
			cin.ignore();
			cout << "Enter fraction 1:\n";
			inputFraction(fraction1);
			cout << "\nEnter fraction 2:\n";
			inputFraction(fraction2);
			cout << "Fraction 1: ";
			display(fraction1);
			cout << "\nFraction 2: ";
			display(fraction2);
			break;
		}
	} while (choice != 6);
	cout << endl;
	system("pause");
}