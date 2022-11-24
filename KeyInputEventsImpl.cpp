#include "KeyInputEvents.h"

void onKeyPress(char* text, SDL_Renderer* renderer, WordsContent* wordsContent) {
	TextItemManager* textItemManager = TextItemManager::getInstance();

	int result = int(*text);
	if ((result >= 65 && result <= 90) || (result >= 97 && result <= 122)) {
		if (wordsContent->getSlot() < 5 && wordsContent->getRow() < 5) {
			struct TextItem* textItem = textItemManager->registerSlotLetter(text, *wordsContent);
			wordsContent->addSlot(textItem);
		}
	}

}

void onKeyDown(SDL_Scancode code, SDL_Renderer* renderer, WordsContent* wordsContent) {
	switch (code) {
		case SDL_SCANCODE_RETURN:
			if (!wordsContent->isGuessed()) {
				wordsContent->sendConfirmation(renderer);
			}
			else {
				wordsContent->reset();
			}
			break;
		case SDL_SCANCODE_BACKSPACE:
			wordsContent->removeSlotChar();
	}
}


