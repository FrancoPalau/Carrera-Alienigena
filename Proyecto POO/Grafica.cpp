#include "Grafica.h"



Grafica::Grafica()
{
	gRenderer = NULL;
	gWindow = NULL;
}

bool Grafica::init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("Spaceship Race", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				cout << "Renderizado no creado! SDL Error: " << SDL_GetError() << endl;
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					cout << "SDL_image no se puede inicializar! SDL_image Error: " << IMG_GetError() << endl;
					success = false;
				}
				//Initialize SDL_ttf
				if (TTF_Init() == -1)
				{
					cout << "SDL_ttf no se puede inicializar! SDL_ttf Error: " << TTF_GetError() << endl;
					success = false;
				}
				//Initialize SDL_mixer
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
					success = false;
				}
			}
		}
	}
	return success;
}


void Grafica::close(vector<LTexture*>texturas, TTF_Font *gFont, Mix_Music* gMusic)
{
	for (int i = 0; i < texturas.size(); i++)
	{
		texturas[i]->free();
	}
	//Free the music
	Mix_FreeMusic(gMusic);
	gMusic = NULL;
	//Free global font
	TTF_CloseFont(gFont);
	gFont = NULL;
	//Destroy window
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

SDL_Window* Grafica::getVentana()
{
	return this->gWindow;
}

bool Grafica::verifcarCarga(LTexture *Meta, LTexture *Fondo, vector<LTexture*> Pistas, vector<LTexture*> TexturasAliens, vector<Texto*> texto, TTF_Font *TexturaTexto)
{
	bool ERROR = false;
	if (!(Meta->loadMedia(getRenderer()))) {
		ERROR = 1;
		cout << "ERROR EN CARGAR IMAGEN DE META!" << endl;
	}
	if (!(Fondo->loadMedia(getRenderer()))) {
		ERROR = 1;
		cout << "ERROR EN CARGAR IMAGEN DE FONDO!" << endl;
	}
	for (int i = 0; i < Pistas.size(); i++) 
	{
		if (!(Pistas[i]->loadMedia(getRenderer()))) {
			ERROR = 1;
			cout << "ERROR EN CARGAR IMAGEN DE PISTA!" << endl;
		}
	}
	for (int i = 0; i < TexturasAliens.size(); i++) {
		if (!(TexturasAliens[i]->loadMedia(getRenderer()))) {
			ERROR = 1;
			cout << "ERROR EN CARGAR IMAGEN DE ALIEN!" << endl;
		}
		if (!texto[i]->loadMedia(getRenderer(), TexturaTexto, 255, 128, 0))
		{
			ERROR = 1;
			cout << "ERROR EN CARGAR TEXTO!" << endl;
		}
	}
	return ERROR;
}

SDL_Renderer* Grafica::getRenderer()
{
	return this->gRenderer;
}

void Grafica::manejadorEventos(bool* quit, int* START)
 {
	SDL_Event e;
	//Handle events on queue
	while (SDL_PollEvent(&e) != 0)
	{
		//User requests quit
		if (e.type == SDL_QUIT)
		{
			*quit = true;
		}
		else if (e.type == SDL_KEYDOWN) {
			switch (e.key.keysym.sym) {
			case SDLK_UP:
				*START = 1;
				break;
			}
		}
	}
}

Grafica::~Grafica()
{
}
