#include "LibreriaMain.h"
#include "Datos.cpp"

//Variables locales
Log Datos;

/*----- SETS/GETS -----*/
bool Tablero::GetMina(int Fila, int Columna){
	if(Fila>=0 && Fila<filas && Columna>=0 && Columna<columnas)
		return datos[Fila][Columna].Mina;
	else
		return 0;
}

void Tablero::SetMina(int Fila, int Columna){
	datos[Fila][Columna].Mina=true;
}

bool Tablero::GetAbierta(int Fila, int Columna){
	if(Fila>=0 && Fila<filas && Columna>=0 && Columna<columnas)
		return datos[Fila][Columna].Abierta;
	else
		return 0;
}

void Tablero::SetAbierta(int Fila, int Columna, int Valor){
    if(Fila>=0 && Fila<filas && Columna>=0 && Columna<columnas)
        datos[Fila][Columna].Abierta = Valor;
}

bool Tablero::GetMarcada(int Fila, int Columna){
	if(Fila>=0 && Fila<filas && Columna>=0 && Columna<columnas)
		return datos[Fila][Columna].Marcada;
	else
		return 0;
}

void Tablero::SetMarcada(int Fila, int Columna){
	if(!GetMarcada(Fila, Columna))
		datos[Fila][Columna].Marcada=true;
	else
		datos[Fila][Columna].Marcada=false;
}

/*----- FUNCIONES TABLERO -----*/
void Tablero::Inicializar(int Nivel){
	/*Inicializa el tablero, tomando
	los datos del nivel y convirtiendo el nivel
	a filas y columnas para poder formar el tablero.
	Ademas indica inicializa las minas, si está abierta
	y si está cerrda.*/
    Nivel = nivel;
	filas = Nivel;
	columnas = Nivel;

	for(int i=0; i<filas; i++){
		for(int j=0; j<columnas; j++){
			datos[i][j].Mina = false;
			datos[i][j].Abierta = false;
			datos[i][j].Marcada = false;
		}
	}
}

int Tablero::ConsultaFilas(){
	//Regresa cantidad de filas.
	return filas;
}

int Tablero::ConsultaColumnas(){
	//Regresa cantidad de columnas.
	return columnas;
}

int Tablero::JuntoAMina(int Fila, int Columna){
	int n_minas=0;

	/*Esta funcion toma la cantidad de minas que hay
	y dependiendo de la cantidad de columnas y filas, mostrará
	el nro de minas que se encuentra cerca o lejos de la casilla
	marcada.*/
	for(int i=Fila-1; i<=Fila+1; i++){
		for(int j=Columna-1; j<=Columna+1; j++){
			if(GetMina(i, j))
				n_minas++;
		}
	}

	return n_minas;
}

void Tablero::AbrirCasilla(int Fil, int Colum){
	/*El algoritmo analiza la cantidad de filas y si está abierta o marcada.
	Una vez se tenga que esa casilla no está abierta, se abrirá. Además mostrará
	el número del lugar donde se encuentra la mina, dependiendo que tan lejos o
	cerca esté, una vez la casilla esté abierta.*/
	if((Fil>=0 && Fil<filas && Colum>=0 && Colum<columnas) && !GetAbierta(Fil, Colum) && !GetMarcada(Fil, Colum)){
		datos[Fil][Colum].Abierta = true;
		
		if((JuntoAMina(Fil, Colum)==0)){
			for(int i=Fil-1; i<=Fil+1; i++){
				for(int j=Colum-1; j<=Colum+1; j++){
					AbrirCasilla(i, j);
				}
			}
		}	
	}
}

/*----- FUNCIONES MINAS -----*/
inline int GetRandom(int Minimo, int Maximo){
	/*Función para poder generar el puesto
	aleatorio de las minas para el tablero*/
	Minimo--;
	Maximo--;
	double func = rand()/(RAND_MAX+1.0);
	return Minimo+(Maximo-Minimo+1)*func;
}

Campominas::Campominas(int Nivel, int nminas){
	/*Inicializa el juego. Obtiene el nivel y la cantidad
	de minas por nivel y las colocará en una posición (x,y) de
	manera aleatoria cada vez que se vaya a jugar. Consulta las filas
	y columnas y revisa si está vacia para poder colocar la mina en el
	lugar. Además se llevan los valores de Minas a nminas y se convierte
	el Estado del juego en verdadero.*/
	nivel = Nivel;
	Juego.Inicializar(Nivel);
	
	//Check
	if (nuevaPartida == true) {
        int i = 0;
        while (i < nminas) {
            int pos_x = GetRandom(0, Juego.ConsultaFilas());
            int pos_y = GetRandom(0, Juego.ConsultaColumnas());

            if (!Juego.GetMina(pos_x, pos_y)) {
                Juego.SetMina(pos_x, pos_y);
                i++;
            }
        }
    } else {
     	Juego = Datos.CargarTablero(nombreJugador, nivel, nminas);
     	
    }
    
    Minas = nminas;
    Estado_Juego = true;
}

bool Campominas::Estado(){
	//Regresa estado del juego.
	return Estado_Juego;
}

bool Campominas::Victoria(){
	/*Esta función se encarga de analizar si el jugador
	completó todo el tablero sin conseguir una bomba, lo cual
	generará una victoria para el mismo. Esto sucede obteniendo
	los valores de las filas y columnas y si está abierta y si no
	tiene minas. En dado caso la casilla tenga una mina, entonces
	el valor de victoria se volverá falso y terminará el juego.*/
	bool victoria = true;
	for(int i=0; i<Juego.ConsultaFilas(); i++){
		for(int j=0; j<Juego.ConsultaColumnas(); j++){
			if(Juego.GetAbierta(i, j) && Juego.GetMina(i, j)){
				victoria=false;
			}
		}
	}

	for(int i=0; i<Juego.ConsultaFilas(); i++){
		for(int j=0; j<Juego.ConsultaColumnas() && victoria==true; j++){
			if(!Juego.GetAbierta(i, j) && !Juego.GetMina(i, j)){
                victoria=false;
                }
		}
	}

	return victoria;
}

void Campominas::ImpresionTablero(){
	/*Esta función se encarga de Imprimir el tablero completo al momento
	de iniciar el juego. Consulta las columnas y filas para poder
	llenarlas con sus respectivos espacios dependiendo del nivel seleccionado.
	Analiza si una casilla está abierta y si tiene una bomba y la marca con X, sino analizará
	si no tiene bomba y lo marcará con un espacio o vacio.
	Si se selecciona la opción de marcar una casilla cerrada, analizará si está cerrada 
	y luego marcará la casilla si esta está cerrada.*/
	system("cls");
	cout << "  ";
	for(int i=0; i<Juego.ConsultaColumnas(); i++){
        cout << "   " << i;
    }
	cout << "\n\n";	

	for(int i=0; i<Juego.ConsultaFilas(); i++){
		cout << i << "  |";
		for(int j=0; j<Juego.ConsultaColumnas(); j++){
			if(Juego.GetAbierta(i, j)){			// CASILLA ABIERTA
				if(Juego.GetMina(i, j)){
                    cout << " X |";
                }			                    // ABIERTA Y CON BOMBA
				else if(!Juego.GetMina(i, j) && Juego.JuntoAMina(i, j)==0)	// ABIERTA Y SIN BOMBA
					{cout << "   |";}
				else if(!Juego.GetMina(i, j) && Juego.JuntoAMina(i, j)>0)	// ABIERTA, CON BOMBA ALREDEDOR
					{cout << " " << Juego.JuntoAMina(i, j) << " |";}
			}
			else if(!Juego.GetAbierta(i, j)){		// CASILLA CERRADA
				if(Juego.GetMarcada(i, j)){cout << " $ |";}			// CERRADA Y MARCADA
				else if(!Juego.GetMarcada(i, j)){cout << " * |";}	// CERRADA Y SIN MARCAR
			}
		}
		cout << "\n";
	}
}

void Campominas::Imprimir(){
	/*El juego consultará las columnas que esten siendo dibujadas y realizará un espacio en blanco
	por cada una de ellas.*/
	for(int i=0; i<Juego.ConsultaColumnas(); i++){
        cout << "   " << i;
    }
	cout << "\n\n";

	/*El juego consultará las filas y columnas si el jugador encuentra una mina, marcar
	con una X y si no encuentra una mina, lo marcará con vacio.*/
	for(int i=0; i<Juego.ConsultaFilas(); i++){
		cout << i << "  |";
		for(int j=0; j<Juego.ConsultaColumnas(); j++){
			if(Juego.GetMina(i, j)){
                cout << " X |";
            }
			else{
                cout << "   |";
            }
		}
		cout << "\n";
	}
}

void Campominas::Menu(){
    char Op;
	int fil, col;

	/*Op delvovera verdadero si el operador no tiene el mismo valor que el indicado.*/
    while(Op!= 'a' && Op != 'b' && Op!= 'c' && Op!= 'd'){
		cout << "\n\n		Elige tu accion:"
		    << "\n\n\t[a] Abrir Casilla"
		    << "\n\t[b] Marcar Casilla"
		    << "\n\t[c] Mostrar Juego Resuelto"
		    << "\n\t[d] -- Abandonar juego --\n\n--> ";
            cin >> Op;

		/*Se pide al jugador seleccionar una fila y columna dependiendo de la opción que
		utilizó.*/
        if((Op== 'A' || Op == 'a') || (Op == 'B' || Op == 'b')){
			cout << "Fila: "; cin >> fil;
			cout << "Columna: "; cin >> col;

			/*Se consulta la fila y columna del tablero y si no está dentro de los parametros
			dados, entonces se pide que se introduzca las dimesiones correctas nuevamente*/
			while(fil > Juego.ConsultaFilas() || col > Juego.ConsultaColumnas()){
				cout << "Introduce dimensiones correctas: ";
				cin >> fil;
				cin >> col;
			}
		}
    }

	/*Si el jugador seleccion la primera opcion, el juego abrirá la casilla e imprimirá el tablero
	nuevamente. Si el jugador encuentra una mina, el juego terminará, devolviendo el estado del juego a
	falso y mostrando el tablero y la ubicación de las minas.*/
    if(Op == 'A' || Op == 'a'){
		Juego.AbrirCasilla(fil, col);
		ImpresionTablero();
		if(Juego.GetMina(fil, col)==true){
			system("cls");
			cout << "\nUNA MINA. Has perdido...\n\n";
			Estado_Juego=false;
			cout << "JUEGO RESUELTO: \n\n";
			Imprimir();
			cout << "\n\n";
		}

	/*Si el jugador selecciona la segunda opcion, se marcará la casilla y podra seleccionar nuevamente 
	la opcion que desea utilizar para jugar.*/	
	}else if(Op == 'B' || Op == 'b'){
		Juego.SetMarcada(fil,col);
		
		/*Si el jugador selecciona la tercera opcion, parará el juego y no guardará su progreso.
		Se le mostrará una advertencia la respecto e imprimirá el tablero y mostrará las minas*/
		}else if(Op == 'C' || Op == 'c'){
		char Parar;

		if(Estado_Juego==true){
            cout << "EL JUEGO NO HA TERMINADO.\n"
			<< "Seguro que quieres imprimir el tablero y finalizar el juego? [S]; ";
			cin >> Parar;
        }
		if(Parar == 'S' || Parar == 's'){
			system("cls");
			Imprimir();
			Estado_Juego = false;
		}
	}

	/*Si el jugador selecciona la ultima opcion, el juego se detendrá y guardará su progreso para que pueda
	seguir jugando alguna otra vez.*/
	else if(Op == 'D' || Op == 'd'){
		Estado_Juego = false;
		Guardar(); //Check
		
		system("cls");
		cout << "Juego detenido... \n";	
	}else{
        cout << "Opción incorrecta... \n";
    }
}  

void Campominas::Empezar(){
	int Nivel = nivel;
    int n_minas = minas;
    srand(time(0)); //Inicia el tiempo del randomizador para colocar las minas.
	
    Campominas JuegoNuevo(Nivel, n_minas);
	Datos.CrearArchivo(nombreJugador); //Check

	/*Mientras el Estado del juego sea verdadero y no haya victoria,
	Se hará le impresión del tablero y luego del menu de selección*/
    while(JuegoNuevo.Estado() && !JuegoNuevo.Victoria()){
		JuegoNuevo.ImpresionTablero();
		JuegoNuevo.Menu();
	}

    if(JuegoNuevo.Victoria()){
        cout << "\n\nEnhorabuena, has ganado.\n\n";
    }
}

void Campominas::Guardar(){ //Check
	Datos.GuardarTablero(Juego, nombreJugador, nivel, minas);
}

void Campominas::Continuar(){ //Check

	int Nivel = nivel;
	int n_minas = minas;
	srand(time(0));

	Campominas JuegoNuevo(Nivel, n_minas);

	while(JuegoNuevo.Estado() && !JuegoNuevo.Victoria()){
		JuegoNuevo.ImpresionTablero();
		JuegoNuevo.Menu();
	}
}



