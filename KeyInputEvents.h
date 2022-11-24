#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include "WordsContent.h"
#include "TextItemManager.h"

void onKeyPress(char* text, SDL_Renderer* renderer, WordsContent* wordsContent);

void onKeyDown(SDL_Scancode code, SDL_Renderer* renderer, WordsContent* wordsContent);