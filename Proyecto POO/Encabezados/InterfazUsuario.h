#pragma once
#include<iostream>
using namespace std;

class InterfazUsuario
{
public:
	InterfazUsuario();
	int getCant_Aliens();
	int getVueltas();
	int getVelMinima();
	int getVelMaxima();
	void Usuario();
	~InterfazUsuario();
private:
	int velMinima, velMaxima, vueltas, cantidad_aliens;

};

