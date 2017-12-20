#include "Archivo.h"

Archivo::Archivo() {
	// TODO Auto-generated constructor stub

	archivo.open("datosCarrera.txt", ios::app);

	if (!archivo) { // operador ! sobrecargado
		cerr << "No se pudo abrir el archivo" << endl;
		exit(1);
	}
}

Archivo::~Archivo() {
	// TODO Auto-generated destructor stub
}

void Archivo::agregarLinea(int dato1, int dato2, int dato3) {
	archivo << dato1 + 1 << setw(20) << dato2 << setw(20)
		<< dato3 << " ms" << endl;
}

void Archivo::datosCuadro() {
	archivo << "Alien" << setw(20) << "Vuelta" << setw(20)
		<< "Tiempo" << endl;
}

void Archivo::tablaDeResultados(int pos, int tiempo, int ID) {
	archivo << pos + 1 << setw(15) << ID + 1 << setw(15) << tiempo << " ms" << endl;
}

void Archivo::escribeMensaje() {
	archivo << "LA CARRERA HA FINALIZADO" << endl
		<< "RESULTADOS FINALES:" << endl;
	archivo << "Posicion" << setw(10) << "Alien" <<
		setw(10) << "Tiempo" << endl;
}