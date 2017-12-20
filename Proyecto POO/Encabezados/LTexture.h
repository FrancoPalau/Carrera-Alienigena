#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "LTimer.h"
using namespace std;

class LTexture
{
public:
	//Initializes variables
	LTexture(string img);
	//Deallocates memory
	~LTexture();
	//Loads image at specified path
	bool loadFromFile(std::string path, SDL_Renderer* gRenderer);
	//Deallocates texture
	void free();
	SDL_Texture* getMTexture();
	//Renders texture at given point
	void render(int x, int y, int ancho, int alto, SDL_Renderer* gRenderer);
	//Gets image dimensions
	int getWidth();
	int getHeight();
	//Loads media
	bool loadMedia(SDL_Renderer* gRenderer);
private:
	SDL_Texture* mTexture;
	int mWidth;
	int mHeight;
	string imagen;
};