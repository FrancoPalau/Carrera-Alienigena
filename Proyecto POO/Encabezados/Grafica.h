#pragma once
#include"LTexture.h"
#include"Alien.h"
#include"Texto.h"
class Grafica
{
public:
	Grafica();
	//Starts up SDL and creates window
	bool init();

	//Frees media and shuts down SDL
	void close(vector<LTexture*>texturas, TTF_Font *gFont, Mix_Music* gMusic);

	SDL_Window* getVentana();

	bool verifcarCarga(LTexture *Meta, LTexture *Fondo, vector<LTexture*> Pistas, vector<LTexture*> TexturasAliens, vector<Texto*> texto, TTF_Font *TexturaTexto);

	SDL_Renderer* getRenderer();

	void manejadorEventos(bool* quit, int* START);

	~Grafica();
private:
	//Screen dimension constants
	const int SCREEN_WIDTH = 1200;
	const int SCREEN_HEIGHT = 680;
	//The window we'll be rendering to
	SDL_Window* gWindow;

	//The window renderer
	SDL_Renderer* gRenderer;
};

