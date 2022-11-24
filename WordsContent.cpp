#include "WordsContent.h"

WordsContent* WordsContent::instance = nullptr;


WordsContent::WordsContent() {
	currentRow = 0;
	currentSlot = 0;
	guessed = false;
	word = std::vector<TextItem*>();

	missed = std::vector<char>();
	semi_missed = std::vector<char>();
	correct = std::vector<char>();
}

bool WordsContent::sendConfirmation(SDL_Renderer* renderer) {
	TextItemManager* textItemManager = TextItemManager::getInstance();
	Dictionary* dictionary = Dictionary::getInstance();
	TTF_Font* font = TextItemManager::getDefaultFont();

	if (currentSlot != 5) return false;

	std::string fullText;

	for (TextItem* item : word) {
		fullText += item->letter;
	}

	if (!dictionary->isInDict(fullText)) return false;

	if (fullText != dictionary->getRolledWord()) {
		int ai = 0;

		if (currentRow + 1 < 5) {
			for (TextItem* item : word) {
				bool found = false;

				std::string rolled = dictionary->getRolledWord();
				for (unsigned int i = 0; i < rolled.size(); i++) {
					if (rolled[i] == item->letter) {
						found = true;
						SDL_Color color;
						if (i == ai) {
							color = { 0, 255, 0, 255 };
							TextItem* mitems = textItemManager->getTextInfo("correct_words");
							VectorUtil::putIfAbsent(&correct, item->letter);
							textItemManager->changeTextInfoContent(mitems, VectorUtil::valuesToCommaString(correct), { 0, 255, 0, 255 });
						}
						else {
							color = { 255, 204, 0, 255 };
							TextItem* mitems = textItemManager->getTextInfo("semi_missed_words");
							VectorUtil::putIfAbsent(&semi_missed, item->letter);
							textItemManager->changeTextInfoContent(mitems, VectorUtil::valuesToCommaString(semi_missed), { 255, 204, 0, 255 });
							
						}

						prepareColor(item, item->letter, color, renderer);
					}
				}

				if (!found) {
					TextItem* mitems = textItemManager->getTextInfo("missed_words");
					VectorUtil::putIfAbsent(&missed, item->letter);
					textItemManager->changeTextInfoContent(mitems, VectorUtil::valuesToCommaString(missed), { 255, 255, 255, 255 });
				}

				ai++;
			}
		}else {
			guessed = true;

			TextItem* item = textItemManager->getTextInfo("result");
			SDL_Surface* surface = textItemManager->changeTextInfoContent(item, "Haslo to " + dictionary->getRolledWord() + " / Kliknij ENTER, aby zaczac od nowa", { 255, 0, 0, 255 });
			item->rectangle.y = surface->w + (currentRow * 20) + 20;

			textItemManager->setTextInfoRendering("result", true);
		}


	}
	else {
		guessed = true;

		for (TextItem* item : word) {
			prepareColor(item, item->letter, { 0, 255, 0, 255 }, renderer);
		}

		TextItem* item = textItemManager->getTextInfo("result");
		SDL_Surface* surface = textItemManager->changeTextInfoContent(item, "Haslo to " + dictionary->getRolledWord() + " / Kliknij ENTER, aby zaczac od nowa", { 0, 255, 0, 255 });
		item->rectangle.y = surface->w + (currentRow * 20) + 20;

		textItemManager->setTextInfoRendering("result", true);
	}

	word.clear();

	if (currentRow < 5) {
		currentSlot = 0;
		currentRow++;
	}

	return true;
}

int WordsContent::getRow() {
	return currentRow;
}

int WordsContent::getSlot() {
	return currentSlot;
}

void WordsContent::addRow(char letter) {
	currentRow++;
}

void WordsContent::addSlot(struct TextItem* textItem) {
	currentSlot++;
	word.push_back(*&textItem);
}

bool WordsContent::isGuessed() {
	return guessed;
}

void WordsContent::reset() {
	TextItemManager* textItemManager = TextItemManager::getInstance();
	Dictionary* dictionary = Dictionary::getInstance();
	currentSlot = 0;
	currentRow = 0;

	for (TextItem* ptr : word) {
		delete(ptr);
	}
	word.clear();
	
	dictionary->reroll();
	textItemManager->clearGameItems();

	TextItem* citems = textItemManager->getTextInfo("correct_words");
	TextItem* mitems = textItemManager->getTextInfo("missed_words");
	TextItem* sitems = textItemManager->getTextInfo("semi_missed_words");
	textItemManager->changeTextInfoContent(citems, "-", { 255, 255, 255, 255});
	textItemManager->changeTextInfoContent(mitems, "-", { 255, 255, 255, 255 });
	textItemManager->changeTextInfoContent(sitems, "-", { 255, 255, 255, 255 });

	missed.clear();
	semi_missed.clear();
	correct.clear();

	textItemManager->setTextInfoRendering("result", false);
	guessed = false;
}

void WordsContent::removeSlotChar() {
	TextItemManager* textItemManager = TextItemManager::getInstance();

	if (currentSlot > 0) {
		word.pop_back();
		textItemManager->removeGameLetter();
		currentSlot--;
	}
}

void WordsContent::prepareColor(TextItem* item, char c, SDL_Color color, SDL_Renderer* renderer) {

	TTF_Font* font = TextItemManager::getDefaultFont();

	const char* ptr;
	std::string sym(1, c);
	ptr = sym.c_str();

	SDL_Surface* surface = TTF_RenderText_Solid(font, ptr, color);
	SDL_Texture* textr = SDL_CreateTextureFromSurface(renderer, surface);
	item->texture = textr;

}

WordsContent::~WordsContent(void){}