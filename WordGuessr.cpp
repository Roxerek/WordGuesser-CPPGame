#include <stdio.h>
#include <SDL.h>
#undef main
#include <vector>
#include <SDL_ttf.h>
#include <iostream>
#include <future>
#include "Dictionary.h"
#include "TextItemManager.h"
#include "KeyInputEvents.h"
#include "WordsContent.h"
#include "Sizes.h"

bool displaying;
bool loading = true;

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Thread* thread;

std::vector<std::string> words;

std::string rolledString;


int LoadingThread(void* ptr) {

	//Get words from dictionary (asynchronious)

	Dictionary* dictionary = Dictionary::getInstance();
	TextItemManager* textItemManager = TextItemManager::getInstance();

	dictionary->init();

	SDL_StartTextInput();
	loading = false;
	textItemManager->setTextInfoRendering("loading", false);

	//Prepare all texts for game
	textItemManager->registerInfoText("result", (char*)"-", 20, 20);
	textItemManager->setTextInfoRendering("result", false);
	
	int w, h;
	int heightDiff = textItemManager->getFontHeight() + 50;

	textItemManager->registerInfoText("missed_words_info", (char*)"Znaki nie znajdujace sie w wyrazie: ", 20, 300, &w, &h);
	textItemManager->registerInfoText("missed_words", (char*)"-", 20 + w + 20, 300);

	textItemManager->registerInfoText("semi_missed_words_info", (char*)"Znaki znajdujace sie w wyrazie: ", 20, 300+heightDiff, &w, &h);
	textItemManager->registerInfoText("semi_missed_words", (char*)"-", 20+w+20, 300+ heightDiff);

	textItemManager->registerInfoText("correct_words_info", (char*)"Odgadniete znaki: ", 20, 300 + (heightDiff*2), &w, &h);
	textItemManager->registerInfoText("correct_words", (char*)"-", 20 + w + 20, 300 + (heightDiff * 2));

	return 0;

}


int main()
{

	TTF_Init();

	Dictionary* dictionary = Dictionary::getInstance();
	WordsContent* wordsContent = WordsContent::getInstance();
	TextItemManager* textItemManager = TextItemManager::getInstance();

	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("WordGuessr", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
	
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	textItemManager->setRenderer(renderer);

	if (window == NULL) {
		printf("There is an error with creating Window!");
		return 0;
	}

	displaying = true;
	
	textItemManager->registerInfoText("loading", (char*)"Ladowanie, prosze czekac", 0, 0);
	textItemManager->setTextInfoRendering("loading", true);

	thread = SDL_CreateThread(LoadingThread, "DictionaryLoad", (void*)NULL);

	SDL_Event handledEvent;
	while (displaying) {
		if (SDL_PollEvent(&handledEvent)) {
			if (handledEvent.type == SDL_QUIT) displaying = false;	

			if (!loading) {
				if (handledEvent.type == SDL_TEXTINPUT) {
					onKeyPress(handledEvent.text.text, renderer, wordsContent);
				}
				else if (handledEvent.type == SDL_KEYDOWN) {
					onKeyDown(handledEvent.key.keysym.scancode, renderer, wordsContent);
				}
			}
		}
		textItemManager->renderAllText();
	}

	TTF_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 1;
}
