#pragma once
#include <stdio.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <ctime>
#include <cmath>

class Dictionary {

	std::vector<std::string> dictionary;
	std::string rolledWord;

	public:
		Dictionary(void);
		void init();
		bool isInDict(std::string text);
		std::string getRolledWord();
		void reroll();
		
		inline static Dictionary* getInstance() {
			if (instance == nullptr) {
				instance = new Dictionary();
			}
			return instance;
		}

		~Dictionary(void);

	private:
		static Dictionary* instance;
};