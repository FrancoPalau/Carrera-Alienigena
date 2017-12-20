#include "InterfazUsuario.h"



InterfazUsuario::InterfazUsuario()
{
	Usuario();
}

int InterfazUsuario::getCant_Aliens()
{
	return this->cantidad_aliens;
}

int InterfazUsuario::getVueltas()
{
	return this->vueltas;
}

int InterfazUsuario::getVelMinima()
{
	return this->velMinima;
}

int InterfazUsuario::getVelMaxima()
{
	return this->velMaxima;
}

void InterfazUsuario::Usuario()
{
	/////////INTERFAZ DE USUARIO///////
	cout << "Ingrese: Cantidad de Jugadores (Maximo 7)" << endl;
	cin >> this->cantidad_aliens;
	cout << "Cantidad de Vueltas" << endl;
	cin >> this->vueltas;
	cout << "Valor Minimo de Velocidad (Minimo 40)" << endl;
	cin >> this->velMinima;
	cout << "Valor Maximo de Velocidad (Maximo 180)" << endl;
	cin >> this->velMaxima;
	//////////////////////////////////
}


InterfazUsuario::~InterfazUsuario()
{
}
