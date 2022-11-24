#include "Dictionary.h"

Dictionary* Dictionary::instance = nullptr;

Dictionary::Dictionary(void) {}

void Dictionary::init() {
	//Setting random seed
	std::srand(time(NULL));

	std::fstream file("assets/dictionary.txt");
	std::string output_line;
	while (getline(file, output_line)) {
		if (output_line.length() == 5) {
			dictionary.push_back(output_line);
		}
	}

	int r = std::rand() % dictionary.size();

	rolledWord = dictionary[r];
}

bool Dictionary::isInDict(std::string text) {
	if (std::find(dictionary.begin(), dictionary.end(), text) != dictionary.end()) {
		return true;
	}

	return false;
}

std::string Dictionary::getRolledWord() {
	return rolledWord;
}

void Dictionary::reroll() {
	int r = std::rand() % dictionary.size();

	rolledWord = dictionary[r];
}

Dictionary::~Dictionary(void) {

}