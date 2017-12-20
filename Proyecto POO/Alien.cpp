#include "Alien.h"



Alien::Alien(double vel, int posa, int posb, int posInix, int posIniy, int id, int cant_vueltas, int cant_aliens)
{
	this->cantidad_vueltas = cant_vueltas;
	
	TERMINE = false;

	this->identidad = id;

	this->cantidad_aliens = cant_aliens;

	mPosX = posInix;
	mPosY = posIniy;

	x0 = 575;
	y0 = 320;
	vueltas = 0;

	this->a = posa;
	this->b = posb;
	
	this->velocidad = vel;
	
	TimerAlien = LTimer();
}


Alien::~Alien()
{
}

void Alien::setColorTextura(LTexture* Tex_Alienigena)
{
	color[0] = rand() % 3;
	color[1] = rand() % 3;
	color[2] = rand() % 3;

	for (int i = 0; i < 3; i++)
	{
		if (color[i] == 0) { color[i] = 0; }
		if (color[i] == 1) { color[i] = 128; }
		if (color[i] == 2) { color[i] = 255; }
	}
	SDL_SetTextureColorMod(Tex_Alienigena->getMTexture(), color[0], color[1], color[2]);
}

void Alien::RandomAyB()
{
	a = 130;
	b = 80;
	int i = 1;
	while (i < cantidad_aliens) {
		a = a + 60;
		b = b + 40;
		i++;
	}
	a = rand() % (a - 131) + 130;
	b = rand() % (b - 81) + 80;
}

int Alien::getPosX()
{
	return this->mPosX;
}

int Alien::getPosY()
{
	return this->mPosY;
}

bool Alien::getTermine()
{
	return TERMINE;
}

Uint32 Alien::getTicks()
{
	return TimerAlien.getTicks();
}

LTimer* Alien::getTimer()
{
	return &TimerAlien;
}

void Alien::move(LTexture* Tex_Alienigena, Archivo* DatosCarrera)
{
	mPosX = x0 + a*cos(velAngulo);
	mPosY = y0 + b*sin(velAngulo);
	grados_giro = (velAngulo*180/M_PI);
	if (fmod(grados_giro,180) == 0 && grados_giro!=mPosYact2)
	{
		mPosYact2 = grados_giro;
		velocidad = rand() % (velSup - (velInf + 1)) + velInf;
		velocidad = velocidad / 10000;
		RandomAyB();
		setColorTextura(Tex_Alienigena);
	}
	if (fmod(grados_giro,360) == 0 && grados_giro != mPosYact1)
	{
		mPosYact1 = grados_giro;
		vueltas++;
		DatosCarrera->agregarLinea(identidad, vueltas, TimerAlien.getTicks());
		if (vueltas == cantidad_vueltas) {
			TERMINE = true;
			TimerAlien.pause();
		}
	}
	velAngulo = velAngulo + velocidad;
}

void Alien::render(LTexture* Tex_Alienigena,SDL_Renderer* gRenderer)
{
	Tex_Alienigena->render(mPosX,mPosY,Alien_ancho,Alien_alto,gRenderer);
}

void Alien::setRangoVel(int vm, int vM) {
	velInf = vm;
	velSup = vM;
}

int Alien::getID() {
	return this->identidad;
}

int Alien::getVueltas()
{
	return this->vueltas;
}

