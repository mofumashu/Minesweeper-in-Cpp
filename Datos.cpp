#include "LibreriaMain.h"

ofstream archivo;

Log::Log(){	
}

void Log::CrearArchivo(string nombreUsuario) {
	nombreUsuario += ".txt";
	archivo.open(nombreUsuario);

	if (archivo.is_open()) {
    	cout << "El archivo se creó y abrió correctamente." << endl;
	} else {
    	cout << "No se pudo crear o abrir el archivo." << endl;
	}
}

 void Log::GuardarTablero(Tablero tablero, string nombreArchivo, int Nivel, int Minas) {
        string nombreArchi = nombreArchivo;
        nivel = Nivel;
        minas = Minas;

        std::ofstream archivo(nombreArchi);
		
        if (archivo.is_open()) { 
            archivo << "Nivel: " << Nivel << "\n";
            archivo << "Filas: " << tablero.ConsultaFilas()<< "\n";
            archivo << "Columnas: " << tablero.ConsultaColumnas() << "\n";

            for (int i = 0; i < tablero.ConsultaFilas(); ++i) {
                for (int j = 0; j < tablero.ConsultaColumnas(); ++j) {
                    if (tablero.GetMarcada(i, j)) {
                        archivo << '$';  // Indica un espacio marcado por el usuario
						
                    } if (tablero.GetAbierta(i,j)){
                    	archivo <<tablero.JuntoAMina(i,j); // Indica un espacio abierto por el usuario.
						
					} if (tablero.GetMina(i,j)){
						archivo << 'X';  // Indica que hay una mina
											 
					} else if (!tablero.GetAbierta(i,j) && !tablero.GetMarcada(i, j)) {
                    	archivo << '*'; // Indica que el espacio no ha sido abierto por el usuario.
                    }
                }
                archivo << "\n";
            }
			
            archivo.close();
            
        } else {
            // Manejar el caso en que no se pueda abrir el archivo.
            // Puedes imprimir un mensaje de error o lanzar una excepción, por ejemplo.
        }  

        nombreArchivo = nombreArchi;

}


void Log::CompararArchivo(string nombreArchivo, int Nivel, int Fil, int Colum) {
    std::ifstream archivo(nombreArchivo);
    nivel = Nivel;

    if (archivo.is_open()) {
        std::string linea;
        while (std::getline(archivo, linea)) {
            if (linea.find("Nivel:") != std::string::npos) {
                int inicio = linea.find(":") + 2;  // Posición después de ": "
                Nivel = std::stoi(linea.substr(inicio));
            } else if (linea.find("Filas:") != std::string::npos) {
                int inicio = linea.find(":") + 2;  // Posición después de ": "
                Fil = std::stoi(linea.substr(inicio));
            } else if (linea.find("Columnas:") != std::string::npos) {
                int inicio = linea.find(":") + 2;  // Posición después de ": "
                Colum = std::stoi(linea.substr(inicio));
            }
        }

        archivo.close();
    } else {
        // Manejar el caso en que no se pueda abrir el archivo.
        // Puedes imprimir un mensaje de error o lanzar una excepción, por ejemplo.
    }
}


Tablero Log::CargarTablero(string nombreArchivo, int Nivel, int minas) {
    std::ifstream archivo(nombreArchivo);

    int Fil, Colum;
    int n_minas1 = minas; // Contador de minas
    char c [Fil][Colum]; //Declaramos el array donde se almacenará el valor
	Tablero tablero;  //creamos una variable tablero.

    CompararArchivo(nombreArchivo, Nivel, Fil, Colum); //Obtenemos nivel, filas y columnas del tablero
    tablero.Inicializar(Nivel);
    
    
    // Descartar las primeras tres líneas
    std::string line;
    for (int i = 0; i < 3; i++) {
        std::getline(archivo, line);
    }    
	
	 for (int i = 0; i < Fil; ++i) {
	    for (int j = 0; j < Colum; ++j){
	    	archivo >> c [i][j];	
	        if (c [i][j] == 'X') {
	            // Colocar una mina en la posición (i, j)
	            tablero.SetMina(i, j);
	            n_minas1++;
	        } else if (c [i][j] >= '0' && c [i][j] <= '9') {
	            int minasAlrededor = c [i][j] - '0';
				tablero.SetAbierta(i, j, minasAlrededor);
	        } else if (c [i][j] == '$') {
	            tablero.SetMarcada(i, j);
	        } else if (c [i][j] == '*') {
	            // El estado es '*', que indica un espacio no abierto por el usuario
	            // No es necesario realizar ninguna acción en este caso
	        }
	        
	    }
   	}
    
    archivo.close();
    return tablero;
}