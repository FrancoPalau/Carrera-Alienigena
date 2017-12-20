#pragma once
#include"LTexture.h"

class Texto
{
public:
	Texto();
	
	bool loadFromRenderedText(string textureText, SDL_Color textColor, SDL_Renderer * gRenderer, TTF_Font *gFont);

	void free();

	void render(int x, int y, SDL_Renderer * gRenderer);

	bool loadMedia(SDL_Renderer * gRenderer, TTF_Font *gFont, int red, int green, int blue);
	
	void setNumero(int num);

	void setTexto(string fin);

	~Texto();
private:
	SDL_Texture* mTexture;
	
	int mWidth;
	int mHeight;
	
	string numero;
};