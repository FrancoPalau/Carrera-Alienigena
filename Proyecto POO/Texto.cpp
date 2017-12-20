#include "Texto.h"



Texto::Texto()
{
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

void Texto::render(int x, int y, SDL_Renderer * gRenderer)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };
	SDL_RenderCopy(gRenderer, mTexture, NULL, &renderQuad);
}


Texto::~Texto()
{
	//Deallocate
	free();
}

void Texto::free()
{
	//Free texture if it exists
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

bool Texto::loadFromRenderedText(string textureText, SDL_Color textColor, SDL_Renderer * gRenderer, TTF_Font *gFont)
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		//Create texture from surface pixels
		mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
		if (mTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}

	//Return success
	return mTexture != NULL;
}

bool Texto::loadMedia(SDL_Renderer * gRenderer, TTF_Font *gFont, int red, int green, int blue)
{
	//Loading success flag
	bool success = true;

	gFont = TTF_OpenFont("lazy.ttf", 24);
	if (gFont == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else
	{
		//Render text
		SDL_Color textColor = { red, green, blue };
		TTF_SetFontStyle(gFont, TTF_STYLE_BOLD);
		if (!loadFromRenderedText(numero, textColor, gRenderer, gFont))
		{
			printf("Failed to render text texture!\n");
			success = false;
		}
	}
	return success;
}

void Texto::setNumero(int num)
{
	string cadena = "";
	cadena = to_string(num);
	this->numero = cadena;
}

void Texto::setTexto(string fin)
{
	this->numero = fin;
}
