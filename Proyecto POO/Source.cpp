#include"Grafica.h"
#include"Alien.h"
#include"Texto.h"
#include"Archivo.h"
#include"InterfazUsuario.h"

int main(int argc, char* args[])
{
	InterfazUsuario Usuario;
	
	Archivo DatosCarrera;
	
	TTF_Font *TexturaTexto = NULL;

	Mix_Music *Musica = NULL;

	double velocidad = 0;
	int error = 0, START = 0, bandera = 0;
	
	Grafica ventana;

	LTexture *Fondo = new LTexture("Fondo.jpg");
	LTexture *Meta = new LTexture("Meta.png");

	vector<LTexture*>Pistas;
	vector<LTexture*>texturas_alienigenas;
	vector<Alien*>alienigenas;
	vector<Texto*>texto;
	vector<Texto*>texto_vueltas;
	vector<int>tiemposFinales;
	vector<int>idFinal;

	srand(time(NULL));
	
	for (int i = 0; i < Usuario.getCant_Aliens()+1; i++)
	{
		LTexture *Texture = new LTexture("Pista.png");
		Pistas.push_back(Texture);
	}
	for (int i = 0; i < Usuario.getCant_Aliens(); i++)
	{
		LTexture *Tex_Alienigena = new LTexture("Alien.jpg");
		texturas_alienigenas.push_back(Tex_Alienigena);
		Texto *text_vueltas = new Texto();
		texto_vueltas.push_back(text_vueltas);
		velocidad = rand() % (Usuario.getVelMaxima() - (Usuario.getVelMinima() + 1)) + Usuario.getVelMinima();
		velocidad = velocidad / 10000;
		Alien *Alienigenas = new Alien(velocidad, 130 + (i * 60), 80 + (i * 40), 700 + (i * 61), 320, i, Usuario.getVueltas(), Usuario.getCant_Aliens());
		alienigenas.push_back(Alienigenas);
		alienigenas[i]->setRangoVel(Usuario.getVelMinima(), Usuario.getVelMaxima());
		Texto *text = new Texto();
		text->setNumero(i + 1);
		texto.push_back(text);
	}
	if (!ventana.init())
	{
		cout << "Failed to initialize!" << endl;
	}
	else
	{
		DatosCarrera.datosCuadro();
		bool error;
		Musica = Mix_LoadMUS("music.mp3");

		if (Musica == NULL)
		{
			error = 1;
			cout << "Failed to load beat music! SDL_mixer Error: " << Mix_GetError() << endl;
		}
		error=ventana.verifcarCarga(Meta,Fondo,Pistas,texturas_alienigenas,texto,TexturaTexto);
		for (int i = 0; i < Usuario.getCant_Aliens(); i++)
		{
			alienigenas[i]->setColorTextura(texturas_alienigenas[i]);
		}
		if (error == 0)
		{
			bool quit = false;
			while (!quit)
			{
				ventana.manejadorEventos(&quit, &START);
				if (START == 1)
				{
					if (Mix_PlayingMusic() == 0)
					{
						Mix_PlayMusic(Musica, -1);
					}
					for (int i = 0; i < alienigenas.size(); i++) 
					{
						if (alienigenas[i]->getTimer()->isStarted()) 
						{
							if (!(alienigenas[i]->getTermine()))
							{
								alienigenas[i]->move(texturas_alienigenas[i], &DatosCarrera);
								texto_vueltas[i]->setNumero(alienigenas[i]->getVueltas());
							}
							else 
							{
								if (alienigenas[i]->getTimer()->isPaused())
								{
									tiemposFinales.push_back(alienigenas[i]->getTimer()->getTicks());
									idFinal.push_back(alienigenas[i]->getID());
									alienigenas[i]->getTimer()->unpause();
									if (tiemposFinales.size() == alienigenas.size())
									{
										DatosCarrera.escribeMensaje();
										START = 0;
										for (int k = 0; k < tiemposFinales.size(); k++) {
											DatosCarrera.tablaDeResultados(k,tiemposFinales[k],idFinal[k]);
										}
									}
								}
								if (bandera == 0)
								{
									bandera = 1;
									texto_vueltas[i]->setTexto("¡¡GANADOR!!");
								}
							}
							texto_vueltas[i]->loadMedia(ventana.getRenderer(), TexturaTexto, 255, 255, 255);
						}
						else 
						{
							alienigenas[i]->getTimer()->start();
						}
					}
				}
				Fondo->render(0, 0, 1200, 680, ventana.getRenderer());
				Meta->render(670, 320, 56 * Pistas.size(), 100, ventana.getRenderer());
				int j = 0, t = 0;
				for (int i = 0; i < Pistas.size(); i++)
				{
					Pistas[i]->render(450 - t, 260 - j, Pistas[i]->getWidth() / 4 + 2 * t, Pistas[i]->getHeight() / 4 + 2 * j, ventana.getRenderer());
					j = j + 59;
					t = t + 90;
				}
				for (int i = 0; i < alienigenas.size(); i++)
				{
					texturas_alienigenas[i]->render(10, 0 + (i * 50), 50, 50, ventana.getRenderer());
					texto[i]->render(0, 18 + (i * 50), ventana.getRenderer());
					texto_vueltas[i]->render(60, 18 + (i * 50), ventana.getRenderer());
					alienigenas[i]->render(texturas_alienigenas[i], ventana.getRenderer());
					texto[i]->render(alienigenas[i]->getPosX() + 18, alienigenas[i]->getPosY() + 50, ventana.getRenderer());
				}
				SDL_RenderPresent(ventana.getRenderer());
			}
		}
	}
	Pistas.push_back(Fondo);
	Pistas.push_back(Meta);
	for (int i = 0; i < texturas_alienigenas.size(); i++)
	{
		Pistas.push_back(texturas_alienigenas[i]);
	}
	ventana.close(Pistas,TexturaTexto,Musica);
	return 0;
}