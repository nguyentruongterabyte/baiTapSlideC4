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
#include<cstdio>


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
		cin.ignore();
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
	myFraction.value = (float)myFraction.numerator / (float)myFraction.denominator;
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
void swapFraction(fraction& a, fraction& b)
{
	fraction t = a;
	a = b;
	b = t;
}


int partition(fraction *& myFractions,int low, int high)
{
	float pivot = myFractions[high].value;    // pivot
	int left = low;
	int right = high - 1;
	while (true) {
		while (left <= right && myFractions[left].value < pivot) left++;
		while (right >= left && myFractions[right].value > pivot) right--;
		if (left >= right) break;
		swap(myFractions[left], myFractions[right]);
		left++;
		right--;
	}
	swap(myFractions[left], myFractions[high]);
	return left;
}

/* Hàm thực hiện giải thuật quick sort */
void quickSort(fraction *& myFractions, int low, int high)
{
	if (low < high)
	{
		/* pi là chỉ số nơi phần tử này đã đứng đúng vị trí
		 và là phần tử chia mảng làm 2 mảng con trái & phải */
		int pi = partition(myFractions, low, high);

		// Gọi đệ quy sắp xếp 2 mảng con trái và phải
		quickSort(myFractions, low, pi - 1);
		quickSort(myFractions, pi + 1, high);
	}
}
int main() {
	system("color f2");
	fraction* myFractions, firstPositiveFraction;
	char length[100];
	int n, positiveFracs, negativeFracs;
	char options;
	do {
		cout << "Press 'i' to input new fractions array.\n";
		cout << "Press 'e' to exit.\n";
		cin >> options;
		switch (options) {
		case 'i':
			inputAmount(length);//Nhập số lượng phân số của mảng myFractions. 
			n = atoi(length);//Dùng hàm atoi để chuyển kiểu char thành kiểu int.
			myFractions = new fraction[n];//mảng myFraction có độ dài n.



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
			quickSort(myFractions, 0, n - 1);
			//Sử dụng quickSort để sắp xếp tăng những phần tử trong mảng phân số.
			//Khi đó phần tử đầu tiên sẽ là phần tử nhỏ nhất trong mảng (myFractions[o]).
			//Phần tử cuối cùng sẽ là phần tử lớn nhất.
			cout << "The max fraction is: ";
			outputOneFraction(myFractions[n - 1]);//Xuất phân số lớn nhất trong mảng.
			cout << "\nThe min fraction is: ";
			outputOneFraction(myFractions[0]);//Xuất phân số nhỏ nhất trong mảng.



			printf("\n%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 3, 4, 5, 6, 3, 4, 5, 6, 3, 4, 5, 6, 3, 4, 5, 6, 3, 4, 5, 6, 3, 4, 5, 6, 3, 4, 5, 6, 3, 4, 5, 6, 3, 4, 5, 6, 3, 4, 5, 6, 3, 4, 5, 6, 3, 4, 5, 6, 3, 4, 5, 6, 3, 4, 5, 6, 3, 4, 5, 6, 3, 4, 5, 6);
			cout << "Increasing array: ";
			//sau khi dùng quickSort thì mảng đã sắp xếp theo thứ tự tăng dần nên ta chỉ việc xuất mảng
			outputFractions(myFractions, n);
			cout << "\nDecreasing array: ";
			//Vì đã được sắp xếp tăng dần nên chỉ việc xuất mảng số ngược lại ta có mảng giảm dần.
			for (int i = n - 1; i >= 0; i--) {
				outputOneFraction(myFractions[i]);
				cout << " ";
			}
			cout << endl;
			break;
		}
	} while (options != 'e');
	printf("\n");
	system("pause");
}