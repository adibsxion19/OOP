/*CS-UY 2124 (OOP) hw 01
Author: Aadiba Haque
This program reads an ecrypted file (using the Caesar Cypher algorithm where
lower-case characters are changed by rotating them a number of steps through
the alphabet), decrypts it, and prints the message out to standard output.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;



/*The decrypt_char function decrypts the character with the rotation distance
(given as parameters). It is rotated back and wraps around the alphabet if it
is lowercase. Else, it stays the same. The decrypted character is returned.
*/

char decrypt_char(const char& encrypted_char, int rotate_dist) {
	char decrypted_char;
	if (encrypted_char <= 'z' && encrypted_char >= 'a') {
		//Rotates lowercase character with rotation distance.
		decrypted_char = encrypted_char - rotate_dist; 
		if (decrypted_char > 'z') {
			//If decrypted character is past 'z', move it 26 steps back.
			decrypted_char -= 26;
		} else if (decrypted_char < 'a') {
			//If decrypted character is before 'a', move it 26 steps forward.
			decrypted_char += 26;
		}
	} else { 
		//If the encrypted character isn't lowercase, it is a decrypted character.
		decrypted_char = encrypted_char;
	}
	return decrypted_char;
}





/* The decrypt_string function modifies the encrypted string
with the rotation distance (given as parameters), or decrypts it.
This function has a void return type, so nothing is returned.
*/

void decrypt_string(string& encrypted_str, int rotate_dist) {
	for (size_t i = 0; i < encrypted_str.size(); ++i) { 
		// Loops through the given string, decrypting each character.
		char encrypted_char = encrypted_str[i];
		encrypted_str[i] = decrypt_char(encrypted_char, rotate_dist);	
	}
}





/*The main function uses the file encrypted.txt and reads the rotation 
distance from the file, decrypts each line, and adds it to a vector, 
which then gets printed out in reverse order.
*/

int main(){
	ifstream encrypted_text("encrypted.txt");
	int rotate_dist;
	string line;
	vector<string> decrypted_text;
	encrypted_text >> rotate_dist;
	while (getline(encrypted_text, line)) {
		//Decrypts each line of the text and adds modified line to vector.
		decrypt_string(line, rotate_dist);
		decrypted_text.push_back(line);
	}
	for (size_t i = decrypted_text.size() - 1; i > 0; --i) {
		//Loops through the vector in reverse and prints it to standard output.
		cout << decrypted_text[i] << endl;
	}
	encrypted_text.close();
}