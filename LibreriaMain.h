/*		
		    ------ LIBRERIA GENERAL ------
Libreria general donde se tienen todos los datos, variables, 
estructuras, clases y librerias juntas en un solo lugar para
más flexibilidad y comodidad al escribir y leer el código.

*/
#ifndef LIBRERIAMAIN_H_
#define LIBRERIAMAIN_H_

#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <iomanip>
#include <unordered_set>
#include <ctime>
#include <math.h>
#include <conio.h>
#include <ios>
#include <fstream> 
#include <stdlib.h>
#include <sstream> 

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::setw;
using std::unordered_set;
using std::ifstream;
using std::ofstream;
using std::istringstream;

inline int GetRandom(int Minimo, int Maximo);
int nivel;
int minas;
bool nuevaPartida;
string nombreJugador;

struct Casilla{
	bool Mina;
	bool Abierta;
	bool Marcada;
};

class Tablero{
private:
	static const int Tam=20;
	Casilla datos[Tam][Tam];
	int filas,columnas;

public:	
	void Inicializar(int nivel);
	bool GetMina(int Fil, int Colum);
	bool GetAbierta(int Fil, int Colum);
	bool GetMarcada(int Fil, int Colum);
	int JuntoAMina(int Fil, int Colum);
	void AbrirCasilla(int Fil, int Colum);
	void SetMina(int Fil, int Colum);
	void SetAbierta(int Fil, int Colum, int Valor);
	void SetMarcada(int Fil, int Colum);
	int ConsultaFilas();
	int ConsultaColumnas();
	void RenaudarTablero();
};

class Campominas{
private:
	Tablero Juego;
	int Minas;
	bool Estado_Juego;
	
public:
	Campominas(int Nivel, int nminas);
	bool Estado();
	bool Victoria();
	void ImpresionTablero();
	void Imprimir();
	void Menu();
	void Empezar();
    void Guardar();
	void Continuar();
};

class Log {
	public:
		Log();
		void CrearArchivo (string nombreUsuario);
		void GuardarTablero(Tablero tablero, string nombreArchivo, int nivel, int minas);
		void CompararArchivo(string nombreArchivo, int nivel, int filas, int columnas);
		Tablero CargarTablero(string nombreArchivo, int nivel, int minas);		
		void LogBuscaminas ();
};

/*-------------------------------------------------------------------------------------/
/	FECHA Y HORA REAL EN EL MOMENTO EN QUE EL USUARIO CARGA EL TABLERO DE BUSCAMINAS   /
/-------------------------------------------------------------------------------------*/

// Función para obtener la hora actual en formato HH:MM
string obtenerHoraActual() {
    time_t tiempoActual = time(0);                    // Almacenará el tiempo actual.
    tm* tiempo = localtime(&tiempoActual);           //contiene los componentes de la hora actual.
    char hora[6];                                   // se utilizará como búfer para almacenar la cadena formateada de la hora
    strftime(hora, sizeof(hora), "%H:%M", tiempo); // formatea la hora actual en el arreglo `hora` según el formato "%H:%M"
    return hora;
}

// Función para obtener la fecha actual en formato DD/MM/YY
string obtenerFechaActual() {
    time_t tiempoActual = time(0);                          // Almacenará el tiempo actual.
    tm* tiempo = localtime(&tiempoActual);                 // contiene los componentes de la fecha actual.
    char fecha[9];                                        // se utilizará como búfer para almacenar la cadena formateada de la fecha.
    strftime(fecha, sizeof(fecha), "%d/%m/%y", tiempo);  // formatea la hora actual en el arreglo `fecha` según el formato "%d/%m/%y"
    return fecha;
}

#endif