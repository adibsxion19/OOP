
/* Author: Aadiba Haque File: rec03 Description: This program takes information
from a file with hydrocarbon names and formulas, sorts them, sorts them by
number if carbon and hydrogen, and prints it to standard output. */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

struct Formula {
	vector<string> names;
	int carbons;
	int hydrogens;
};

void openStream(ifstream& hydrocarbonsTxt);
void fillVector(vector<Formula>& vectorOfFormulas, ifstream& hydrocarbonsTxt);
void sortVector(vector<Formula>& vectorOfFormulas);
void displayVector(const vector<Formula>& vectorOfFormulas);
void insertHydrocarbon(vector<Formula>& vectorOfFormulas, const string& name,
	int carbons, int hydrogens);
void displayFormula(const Formula& formula);
size_t locationofFormula(const vector<Formula>& vectorOfFormulas, int carbons,
	int hydrogens);

int main() {
	ifstream hydrocarbonsTxt;
	openStream(hydrocarbonsTxt);
	vector<Formula> vectorOfFormulas;
	fillVector(vectorOfFormulas, hydrocarbonsTxt);
	sortVector(vectorOfFormulas);
	displayVector(vectorOfFormulas);
	hydrocarbonsTxt.close();
}

void openStream(ifstream& hydrocarbonsTxt) {
	string fileName;
	cout << "Enter filename:";
	cin >> fileName;
	hydrocarbonsTxt.open(fileName);
	while (!hydrocarbonsTxt) {
		hydrocarbonsTxt.clear();
		cout << "Enter filename:";
		cin >> fileName;
		hydrocarbonsTxt.open(fileName);
	}
}

void fillVector(vector<Formula>& vectorOfFormulas, ifstream& hydrocarbonsTxt) {
	string name;
	int carbons;
	int hydrogens;
	char carbonName;
	char hydrogenName;
	while (hydrocarbonsTxt >> name >> carbonName >> carbons >>
		hydrogenName >> hydrogens) {
		insertHydrocarbon(vectorOfFormulas, name, carbons,
			hydrogens);
	}
	
}

void sortVector(vector<Formula>& vectorOfFormulas) {
	for (size_t i = 0; i < vectorOfFormulas.size(); ++i) {
		int minIndex = i;
		Formula iFormula;
		for (size_t j = i + 1; j < vectorOfFormulas.size(); ++j) {
			int jValue, minIndexValue;
			if (vectorOfFormulas[j].carbons == vectorOfFormulas[minIndex].carbons) {
				jValue = vectorOfFormulas[j].hydrogens;
				minIndexValue = vectorOfFormulas[minIndex].hydrogens;
			} else {
				jValue = vectorOfFormulas[j].carbons;
				minIndexValue = vectorOfFormulas[minIndex].carbons;
			}
			if (jValue < minIndexValue) {
				minIndex = j;
			}
		}
		iFormula = vectorOfFormulas[i];
		vectorOfFormulas[i] = vectorOfFormulas[minIndex];
		vectorOfFormulas[minIndex] = iFormula;
	}
}

void displayVector(const vector<Formula>& vectorOfFormulas) {
	for (size_t i = 0; i < vectorOfFormulas.size(); ++i) {
		displayFormula(vectorOfFormulas[i]); 
	}
}

void displayFormula(const Formula& formula) {
	cout << 'C' << formula.carbons << 'H' << formula.hydrogens << ' ';
	for (const string& name : formula.names) {
		cout << name << ' ';
	}
	cout << endl;
}

void insertHydrocarbon(vector<Formula>& vectorOfFormulas, const string& name,
	int carbons, int hydrogens) {
	int location;
	if (locationofFormula(vectorOfFormulas, carbons, hydrogens)
		== vectorOfFormulas.size()) {
		Formula formula;
		formula.names.push_back(name);
		formula.carbons = carbons;
		formula.hydrogens = hydrogens;
		vectorOfFormulas.push_back(formula);
	} else {
		location = locationofFormula(vectorOfFormulas, carbons,
			hydrogens);
		vectorOfFormulas[location].names.push_back(name);
	}

	 
}

size_t locationofFormula(const vector<Formula>& vectorOfFormulas, int carbons,
	int hydrogens) {
	for (size_t i = 0; i < vectorOfFormulas.size(); ++i) {
		if (vectorOfFormulas[i].carbons == carbons
			&& vectorOfFormulas[i].hydrogens == hydrogens) {
			return i;
		} 
	}
	return vectorOfFormulas.size();
}

