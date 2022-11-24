#include "TextItemManager.h"

TextItemManager* TextItemManager::instance = nullptr;
TTF_Font* TextItemManager::font = nullptr;

TextItemManager::TextItemManager(void) {
	gameItems = std::vector<TextItem*>();
	infoItems = std::map<std::string, TextItem*>();
	font = TTF_OpenFont("assets/absender.ttf", 24);
	if (!font) std::cout << TTF_GetError() << std::endl;

	TTF_SizeText(font, "-", &letterSizeX, &letterSizeY);
	fullWordSize = letterSizeX * 5;
}

void TextItemManager::registerInfoText(std::string type, char* msg, int x, int y) {
	
	TextItem* textItem = createTextItem(msg, { 255,255,255,255 }, x, y);
	textItem->render = true;
	infoItems.insert(std::pair<std::string, TextItem*>(type, textItem));

}

void TextItemManager::registerInfoText(std::string type, char* msg, int posX, int posY, int* w, int* h) {

	TextItem* textItem = createTextItem(msg, { 255,255,255,255 }, posX, posY);
	*w = textItem->w;
	*h = textItem->h;
	textItem->render = true;
	
	infoItems.insert(std::pair<std::string, TextItem*>(type, textItem));

}

void TextItemManager::clearGameItems() {
	for (TextItem* it : gameItems) {
		delete(it);
	}
	gameItems.clear();
}

TextItem* TextItemManager::registerSlotLetter(char* msg, WordsContent wordsContent) {

	TextItem* textItem = createTextItem(msg, { 255, 255, 255, 255 }, ((WINDOW_WIDTH/2)-fullWordSize) + wordsContent.getSlot() * (letterSizeX+5), wordsContent.getRow() * (letterSizeY + 10));		
	gameItems.push_back(textItem);

	return textItem;

}

void TextItemManager::removeGameLetter() {
	gameItems.pop_back();
}


void TextItemManager::renderAllText() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 
	SDL_RenderClear(renderer);
	
	for (TextItem*& item : gameItems) {
		SDL_RenderCopy(renderer, item->texture, NULL, &item->rectangle);
	}

	for (std::pair<std::string, TextItem*> entry : infoItems) {
		TextItem* item = entry.second;
		if (item->render) {
			SDL_RenderCopy(renderer, item->texture, NULL, &item->rectangle);
		}
	}

	//Rendering items from q
	SDL_RenderPresent(renderer);
	SDL_Delay(10);
}

void TextItemManager::setTextInfoRendering(std::string type, bool to) {
	TextItem* item = infoItems.at(type);
	item->render = to;
}

TextItem* TextItemManager::getTextInfo(std::string type) {
	return infoItems.at(type);
}

int TextItemManager::getFontHeight() {
	return letterSizeY;
}

TextItemManager::~TextItemManager(void){}

TextItem* TextItemManager::createTextItem(char* msg, SDL_Color color, int posX, int posY)
{
	SDL_Rect rect;

	SDL_Surface* surface = TTF_RenderText_Solid(font, msg, color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	rect.x = posX; // Center horizontaly
	rect.y = posY; // Center verticaly
	rect.w = surface->w;
	rect.h = surface->h;

	struct TextItem* textItem = (struct TextItem*)malloc(sizeof(TextItem));
	textItem->texture = texture;
	textItem->rectangle = rect;
	textItem->letter = msg[0];
	textItem->w = surface->w;
	textItem->h = surface->h;

	SDL_FreeSurface(surface);

	return textItem;
}

SDL_Surface* TextItemManager::changeTextInfoContent(TextItem* item, std::string content, SDL_Color color) {

	char* result = &content[0];

	SDL_Surface* surface = TTF_RenderText_Solid(font, result, color);
	SDL_Texture* textr = SDL_CreateTextureFromSurface(renderer, surface);
	item->rectangle.w = surface->w;
	item->rectangle.h = surface->h;
	item->texture = textr;

	return surface;

}

void TextItemManager::setRenderer(SDL_Renderer* ren) {
	renderer = ren;
}

SDL_Renderer* TextItemManager::getRenderer() {
	return renderer;
}