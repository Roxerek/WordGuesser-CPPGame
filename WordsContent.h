#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <atomic>
#include "TextItem.h"
#include "TextItemManager.h"
#include "Dictionary.h"
#include "SDL_ttf.h"
#include "VectorUtil.h"

class TextItemManager;

class WordsContent {

	int currentRow;
	int currentSlot;
	bool guessed;
	std::vector<TextItem*> word; 

public:

	WordsContent(void);

	bool sendConfirmation(SDL_Renderer* renderer);

	int getRow();

	int getSlot();

	void addRow(char letter);

	void addSlot(TextItem* textItem);

	bool isGuessed();

	void reset();

	void removeSlotChar();

	void prepareColor(TextItem* item, char c, SDL_Color color, SDL_Renderer* renderer);

	~WordsContent(void);

	inline static WordsContent* getInstance() {
		if (instance == nullptr) {
			instance = new WordsContent();
		}
		return instance;
	}

	private:
		static WordsContent* instance;
		std::vector<char> missed;
		std::vector<char> semi_missed;
		std::vector<char> correct;

};

