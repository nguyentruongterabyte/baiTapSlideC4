//4. Mảng phân số
//Nhập / Xuất n phân số
//Rút gọn mọi phân số
//Đếm số lượng phân số âm / dương trong mảng
//Tìm phân số dương đầu tiên trong mảng
//Tìm phân số nhỏ nhất / lớn nhất trong mảng
//Sắp xếp mảng tăng dần / giảm dần

#include<iostream>
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
typedef struct {//Cấu trúc phân số với hai trường tử sô và mẫu số.
	int numerator;//Tử số.
	int denominator;//Mẫu số.
	float value;//Gía trị của phân số.
} fraction;
void inputAmount(char* soLuong) {
	regex amountExpr("[1-9][0-9]?");
	//vd: !"#$%&'()*+,/:;<=>?@
	//Nếu số đó là sô thực. Nhập lại (Vì sô lượng sv thì không lẻ)
	//Số lượng không âm
	//Nếu chuỗi nhập chứa các ký tự lạ. Nhập lại.
	do {
		cout << "Input the amount of fractions array: ";
		gets_s(soLuong, 100);
		if (!regex_match(soLuong, amountExpr)) {
			cout << "Invalid amount. Enter again!\n";
		}
	} while (!regex_match(soLuong, amountExpr));
}
void inputOneFraction(fraction& myFraction) {//Hàm để nhập tử số và mẫu số một phân số.
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
	myFraction.numerator = atoi(a);
	myFraction.denominator = atoi(b);
	myFraction.value = myFraction.numerator / myFraction.denominator;
}
void inputFrations(fraction*& myFractions, int length) {//Hàm nhập một mảng các phân số có độ dài lenght.
	for (int i = 0; i < length; i++) {
		cout << "Fraction " << i + 1 << ":\n";
		inputOneFraction(myFractions[i]);//Nhập từng phân số của mảng.
	}
}
void outputOneFraction(fraction myFraction) {
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
		//Nếu mẫu = -1 thì hiển thị tử *(-1)
	}
	else {
		cout << myFraction.numerator << "/" << myFraction.denominator;
		//Các trường hợp còn lại.
	}
	setColor(2);
}
void outputFractions(fraction*& myFractions, int length) {
	setColor(4);
	for (int i = 0; i < length; i++) {
		outputOneFraction(myFractions[i]);
		cout << "  ";
	}
	setColor(2);
}
int GCD(int a, int b) {
	//Hàm tìm ước chung lớn nhất.
	//Mục đích để tối giản phân số. 
	//Ví dụ: phân số 15/20. GCD(15, 20) = 5. Lấy cả tử và mẫu chia cho 5 thì ra phân số tối giản (3/4).
	if (a == 0 || b == 0) return 0;
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
	return a;
}
void reducingFractions(fraction *&myFractions, int length) {
	int gcd;
	for (int i = 0; i < length; i++) {
		gcd = GCD(myFractions[i].numerator, myFractions[i].denominator);
		if (myFractions[i].numerator == 0);
		else {
			myFractions[i].numerator /= gcd;
			myFractions[i].denominator /= gcd;
		}
	}
}
int countingPositiveFractions(fraction*& myFractions, int length) {//Đếm số phần số dương 
	int count = 0;
	for (int i = 0; i < length; i++) {
		if ((float)myFractions[i].numerator / (float)myFractions[i].denominator > 0) count++;
	}
	return count;
}
int countingNegativeFractions(fraction*& myFractions, int length) {//Đếm số phân số âm
	int count = 0;
	for (int i = 0; i < length; i++) {
		if ((float)myFractions[i].numerator / (float)myFractions[i].denominator < 0) count++;
	}
	return count;
}
fraction searchingFirstPositiveFractionInArray (fraction *& myFractions,int length) {//Tìm phân số đàu tiên trong mảng
	int i = 0;
	fraction firstPositiveFraction = {0, 1};
	while (i < length) {
		if ((float)myFractions[i].numerator / (float)myFractions[i].denominator > 0) {
			firstPositiveFraction = myFractions[i];
			break;
		}
		else i++;
	}
	return firstPositiveFraction;
}

void searchMaxAndMinFractions(fraction*& myFractions, int length, fraction& maxFraction, fraction& minFraction) {
	maxFraction = myFractions[0];
	minFraction = myFractions[0];
	float tempMax = myFractions[0].value;
	float tempMin = myFractions[0].value;
	for (int i = 1; i < length; i++) {
		if(myFractions[i].value > tempMax) {
			maxFraction = myFractions[i];
			tempMax = myFractions[i].value;
		}
		if (myFractions[i].value < tempMin) {
			minFraction = myFractions[i];
			tempMin = myFractions[i].value;
		}
	}
}

int main() {
	system("color f2");
	fraction* myFractions, firstPositiveFraction, maxFraction, minFraction;
	char length[100];
	int n, positiveFracs, negativeFracs;
	float *valuesArray;
	inputAmount(length);//Nhập số lượng phân số của mảng myFractions. 
	n = atoi(length);//Dùng hàm atoi để chuyển kiểu char thành kiểu int.
	myFractions = new fraction[n];//mảng myFraction có độ dài n.
	valuesArray = new float[n];//Tạo một mảng lưu giá trị thập phân của các phân số;



	inputFrations(myFractions, n);//Nhập các phân số trong mảng.


	cout << "\n=====================================\n";
	cout << "The fractions array has just been entered is: ";
	outputFractions(myFractions, n);//Xuất mảng vừa nhập từ bàn phím.

	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 3, 4, 5, 6, 3, 4, 5, 6, 3, 4, 5, 6, 3, 4, 5, 6, 3, 4, 5, 6, 3, 4, 5, 6, 3, 4, 5, 6, 3, 4, 5, 6, 3, 4, 5, 6, 3, 4, 5, 6, 3, 4, 5, 6, 3, 4, 5, 6, 3, 4, 5, 6, 3, 4, 5, 6, 3, 4, 5, 6, 3, 4, 5, 6);
	setColor(4);
	cout << "After reducing: ";
	reducingFractions(myFractions, n);//rút gọn phân số.
	outputFractions(myFractions, n);//Xuất mảng phân số vừa rút gọn.
	setColor(2);

	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 3, 4, 5, 6, 3, 4, 5, 6, 3, 4, 5, 6, 3, 4, 5, 6, 3, 4, 5, 6, 3, 4, 5, 6, 3, 4, 5, 6, 3, 4, 5, 6, 3, 4, 5, 6, 3, 4, 5, 6, 3, 4, 5, 6, 3, 4, 5, 6, 3, 4, 5, 6, 3, 4, 5, 6, 3, 4, 5, 6, 3, 4, 5, 6);
	positiveFracs = countingPositiveFractions(myFractions, n);//Khởi tạo số phân số âm trong mảng.
	negativeFracs = countingNegativeFractions(myFractions, n);//Khởi tạo số phân số dương trong mảng.
	cout << "The array has ";
	setColor(4);
	cout << positiveFracs << " positive ";
	setColor(2);
	cout << "fractions.\n";
	cout << "The array has ";
	setColor(4);
	cout << negativeFracs << " negative ";
	setColor(2);
	cout << "fractions.\n";
	cout << "The array has ";
	setColor(4);
	cout << n - positiveFracs - negativeFracs << " fractions equal to 0";
	setColor(2);

	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 3, 4, 5, 6, 3, 4, 5, 6, 3, 4, 5, 6, 3, 4, 5, 6, 3, 4, 5, 6, 3, 4, 5, 6, 3, 4, 5, 6, 3, 4, 5, 6, 3, 4, 5, 6, 3, 4, 5, 6, 3, 4, 5, 6, 3, 4, 5, 6, 3, 4, 5, 6, 3, 4, 5, 6, 3, 4, 5, 6, 3, 4, 5, 6);
	firstPositiveFraction = searchingFirstPositiveFractionInArray(myFractions, n);//Khởi tạo phân số dương đầu tiên trong mảng.
	if (firstPositiveFraction.numerator == 0) {
		cout << "There is no positive fraction.\n";
	}
	else {
	cout << "The first positive fraction is: ";
	outputOneFraction(firstPositiveFraction);//Xuất phân số dương đầu tiên.
	}

	printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 3, 4, 5, 6, 3, 4, 5, 6, 3, 4, 5, 6, 3, 4, 5, 6, 3, 4, 5, 6, 3, 4, 5, 6, 3, 4, 5, 6, 3, 4, 5, 6, 3, 4, 5, 6, 3, 4, 5, 6, 3, 4, 5, 6, 3, 4, 5, 6, 3, 4, 5, 6, 3, 4, 5, 6, 3, 4, 5, 6, 3, 4, 5, 6);
	searchMaxAndMinFractions(myFractions, n, maxFraction, minFraction);
	cout << "The max fraction is: ";
	outputOneFraction(maxFraction);//Xuất phân số lớn nhất trong mảng.
	cout << "\nThe min fraction is: ";
	outputOneFraction(minFraction);//Xuất phân số nhỏ nhất trong mảng.





	


	printf("\n");
	system("pause");
	
}