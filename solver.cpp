/* 
Description: 

the goal of this project is to build a program that can take a file, with an encrypted
ceaser cipher and decode it without knowing the process that was done to encode the file.

*/

#include<iostream>
#include<fstream>
#include<array>
#include<vector>
#include<iomanip>


/*

Calculates the number of times, as a percentage, that each letter show's up in a given vector as well as a list of the letters
that correlate to each frequency

returns: vector of doubles.

*/
std::vector<double> calculate_letter_distribution(std::vector<char> parameter, std::vector<char>& letters) {
	std::array<char, 26> alphabet = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
	std::vector<double> frequency;

	int total_characters = parameter.size();

	for (int i = 0; i < alphabet.size(); i++) {
		int count = 0;
		for (int x = 0; x < total_characters; x++) {
			if (alphabet[i] == parameter[x]) {
				count++;
			}
		}
		double percentage = static_cast<double>(count) / total_characters; 
		
		if (percentage) {
			frequency.push_back(percentage);
			letters.push_back(alphabet[i]);
		}
	}

	return frequency;
}

int main() {
	std::ifstream solved;
	solved.open("encrypted_cipher.txt");

	char letter;
	std::vector<char> encrypted_letters;

	for (int i{ 0 }; solved >> std::noskipws >> letter; i++) {

		if (letter == ' ') {
			std::cout << ' ';
		}

		encrypted_letters.push_back(letter);
		std::cout << encrypted_letters[i];

	};

	auto size{ encrypted_letters.size() };
	std::vector<char> letters;
	std::vector<bool> replaced(size, false);
	auto frequency{ calculate_letter_distribution(encrypted_letters,letters) };
	char user_letter{ ' ' };
	char replace_letter{ ' ' };
	int end_sequence{ 0 };

	while (end_sequence >= 0) {

		for (int i{ 0 }; i < frequency.size(); i++) {

			std::cout << ' ' << letters[i] << ':' << frequency[i] << ' ';
		}

		std::cout << "\n\nWhat letter would you like to change?";
		std::cin >> user_letter;
		std::cout << "What letter would you like to replace it with?";
		std::cin >> replace_letter;

		for (int i{ 0 }; i < size; i++) {
			if (!replaced[i] && encrypted_letters[i] == user_letter) {
				encrypted_letters[i] = replace_letter;
				std::cout << encrypted_letters[i];
				replaced[i] = true;
			}
			else {
				std::cout << encrypted_letters[i];
			}
		}

		for (int i{ 0 }; i < replaced.size(); i++) {

			int count{ 0 };

			if (replaced[i] == true) {
				count++;
			}

			if (count == replaced.size()) {
				end_sequence = -1;
			}
		}
	}

	solved.close();

	return 0;

};