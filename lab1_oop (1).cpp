#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
	//Task 3
	cout << "Yay!!!\n";
	//Task 4
	ifstream ifs("integers.txt");
	int sum = 0;
	int anInt;
	while (ifs >> anInt) {
		sum = sum + anInt;
	}
	cout << sum << "\n";
	ifs.close();
	//Task 5
	ifstream txt("text.txt");
	string word;
	while (txt >> word) {
		cout << word << endl;
	}
	txt.close();
	//Task 6
	ifstream mixed("mixed.txt");
	int sum2 = 0;
	int anInt2;
	while (mixed >> anInt2) {
		sum2 = sum2 + anInt2;
	}
	cout << sum2 << "\n";
	mixed.close();

}
