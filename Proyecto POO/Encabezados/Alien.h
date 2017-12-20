#pragma once
#include"LTexture.h"
#include<math.h>
#include"Archivo.h"
using namespace std;
class Alien
{
public:
	Alien(double vel, int posa, int posb, int posInix, int posIniy, int id, int cant_vueltas, int cant_aliens);
	
	~Alien();

	void setRangoVel(int vm, int vM);

	void setColorTextura(LTexture* Tex_Alienigena);

	void RandomAyB();

	int getPosX();

	int getPosY();

	bool getTermine();

	Uint32 getTicks();

	LTimer* getTimer();

	void move(LTexture* Tex_Alienigena, Archivo* DatosCarrera);

	void render(LTexture* Tex_Alienigena, SDL_Renderer* gRenderer);

	int getVueltas();

	int getID();
private:
	bool TERMINE;

	double velocidad=0, velAngulo = 0;

	static const int Alien_ancho = 50, Alien_alto = 50;

	int mPosX, mPosY, a, b, cantidad_aliens, x0, y0, identidad, cantidad_vueltas, vueltasant, velInf, velSup, grados_giro, vueltas, mPosYact1, mPosYact2;

	int color[3];

	LTimer TimerAlien;
};