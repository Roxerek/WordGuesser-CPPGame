#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <SDL.h>
#include <SDL_ttf.h>
#include "WordsContent.h"
#include "TextItem.h"
#include "Sizes.h"

class WordsContent;
class TextItemManager {

	std::vector<TextItem*> gameItems;
	std::map<std::string, TextItem*> infoItems;

	public:
		TextItemManager(void);
		
		void registerInfoText(std::string type, char* msg, int x, int y);

		void registerInfoText(std::string type, char* msg, int x, int y, int* w, int* h);
		
		TextItem* registerSlotLetter(char* msg, WordsContent wordsContent);
		
		void removeGameLetter();
		
		void clearGameItems();
		
		void renderAllText();
		
		TextItem* getTextInfo(std::string type);
		
		void setTextInfoRendering(std::string type, bool to);

		SDL_Surface* changeTextInfoContent(TextItem* item, std::string content, SDL_Color color);

		SDL_Surface* changeTextInfoWrappedContent(TextItem* item, std::string content, SDL_Color color);

		int getFontHeight();

		void setRenderer(SDL_Renderer* ren);

		SDL_Renderer* getRenderer();

		static TTF_Font* getDefaultFont() {
			return font;
		}

		inline static TextItemManager* getInstance() {
			if (instance == nullptr) {
				instance = new TextItemManager();
			}
			return instance;
		}

		~TextItemManager(void);

	private:
		static TextItemManager* instance;
		static TTF_Font* font;
		SDL_Renderer* renderer;
		int letterSizeX;
		int letterSizeY;
		int fullWordSize;
		TextItem* createTextItem(char* msg, SDL_Color color, int addX, int addY);
};