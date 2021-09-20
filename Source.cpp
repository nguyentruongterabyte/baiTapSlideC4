#include <iostream>
#include<regex>
#include<stdio.h>


using namespace std;

int main() {
	char score[100] = "0";
	regex test("\\d+.?\\d+");
	do {
		cout << "Input Score: ";
		gets_s(score);
		if (!regex_match(score, test)) {
			cout << "ENTER. ";
		}
	} while (score != "p");
}