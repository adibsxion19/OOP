// Aadiba Haque, rec 02, Conway's Game of Life implementation
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

int num_neighbors(const vector<string>& world, int row = 0, int column = 0) {
	int neighbor_count = 0;
	if (world[row][column - 1] == '*') {
		++neighbor_count;
	}
	if (world[row][column + 1] == '*') {
		++neighbor_count;
	}
	if (world[row - 1][column] == '*') {
		++neighbor_count;
	}
	if (world[row - 1][column + 1] == '*') {
		++neighbor_count;
	}
	if (world[row - 1][column - 1] == '*') {
		++neighbor_count;
	}
	if (world[row + 1][column] == '*') {
		++neighbor_count;
	}
	if (world[row + 1][column + 1] == '*') {
		++neighbor_count;
	}
	if (world[row + 1][column - 1] == '*') {
		++neighbor_count;
	}
	return neighbor_count;
}

vector<string> next_gen(const vector<string>& world) {
	vector<string> new_world;
	for (size_t n = 0; n < world.size(); ++n) {
		new_world.push_back("----------------------");
	}
	for (size_t i = 1; i < world.size() - 1; ++i) {
		for (size_t j = 1; j < world[i].size() - 1; ++j) {
			int neighbor_count = num_neighbors(world, i, j);
			if (world[i][j] == '*' && (neighbor_count < 2 || neighbor_count > 3)) {
				continue;
			} else if (world[i][j] == '-' && neighbor_count == 3) {
				new_world[i][j] = '*';
			}
			else {
				new_world[i][j] = world[i][j];
			}
		}
	}
	return new_world;
}

void display(vector<string>& world) {
	int count = 1;
	cout << "Initial World" << endl;
	for (size_t i = 1; i < world.size() - 1; ++i) {
		for (size_t j = 1; j < world[i].size() - 1; ++j) {
			cout << world[i][j];
		}
		cout << endl;
	}
	cout << "=====================================" << endl;
	while (count <= 10) {
		vector<string> new_world = next_gen(world);
		cout << "Generation " << count << endl;
		for (size_t i = 1; i < new_world.size() - 1; ++i) {
			for (size_t j = 1; j < new_world[i].size() - 1; ++j) {
				cout << new_world[i][j];
			}
			cout << endl;
		}
		cout << "=====================================" << endl;
		world = new_world;
		++count;
	}
}

void initialize(vector<string>& world, ifstream& ifs) {
	string line;
	world.push_back("----------------------");
	while (getline(ifs, line)) {
		world.push_back("-" + line + "-");
	}
	world.push_back("----------------------");
}

int main() {
	ifstream ifs("life.txt");
	if (!ifs) {
		cerr << "Could not open the file.\n";
		exit(1);
	}
	vector<string> world;
	initialize(world, ifs);
	display(world);
	ifs.close();
}
