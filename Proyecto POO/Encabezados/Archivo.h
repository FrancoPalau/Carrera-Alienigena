#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
using namespace std;

class Archivo {
public:
	Archivo();

	virtual ~Archivo();

	void agregarLinea(int dato1, int dato2, int dato3);

	void datosCuadro();

	void tablaDeResultados(int pos, int tiempo, int ID);

	void escribeMensaje();

private:

	ofstream archivo;
};
