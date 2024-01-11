#include "LibreriaMain.h"
#include "Juego.cpp" //Llamado al archivo 'JuegoMain' donde contiene el codigo que permite la funcionalidad del juego.
Campominas Juego(nivel, minas);

class UI{
    private:
        int modoJuego, op; //Operadores usados para la seleccion en los menus
        int aux = 1; /*Operador utilizado para generar un bucle utilizando while
                    para que el programa corra mientras sea igual a 1. Si se indica
                    un numero diferente a 1 para el operador, el programa para el bucle
                    y termina la sesion.*/

    public:
        //Menu de inicio de sesion para el jugador insertar su nombre de usuario.
        void Sesion(){
            /*Se debe agregar una funcion para poder revisar si el nombre insertado en esta funcion es igual
            al del progreso guardado.*/
            cout<<"*********************************************************"<<endl;
            cout <<"         Bienvenido/a al juego Buscaminas"<<endl;
            cout<<"     Por favor, inserte un nombre para continuar:"<<endl;
            cout<<"*********************************************************"<<endl;
            cout<<"                      "; cin>> nombreJugador;
            system("cls");
            Inicio();
        }

        //Menu inicial donde se escoge si se quiere jugar una nueva partida o cargar una partida anterior.
        void Inicio(){            
            while(aux  == 1){
            cout<<"Jugador: "<<nombreJugador<<endl;
            cout<<"***************************************"<<endl;
            cout<<"              BUSCAMINAS"<<endl;
            cout<<"***************************************"<<endl;
            cout<<"          1.- Nueva partida"<<endl;
            cout<<"          2.- Continuar partida"<<endl;
            cout<<"\n0.- Cerrar"<<endl;
            cin>> op;

            //Switch utilizado para llevar la seleccion del usuario a la parte del programa indicado.
            switch(op){
                case 0: 
                    system("cls");
                    aux = 0;
                    break;
                case 1: 
                    system("cls");
                    NuevaPartida();
                    break;
                case 2: 
                    system("cls");
                    ContinuarPartida();
                    break;
                default: //Si se coloca un numero fuera de la seleccion, se indica que no existe y el programa empieza de nuevo.
                    system("cls");
                    cout<<"      Esta modalidad no existe.\n"<<endl;
                    break;
            } 
        }
    }

        //Menu secundario donde el usuario selecciona la dificultad que desea utilizar para jugar el buscaminas.
        void NuevaPartida(){
            while(aux == 1){
            cout<<"\nJugador: "<<nombreJugador<<endl;
            cout<<"***************************************"<<endl;
            cout<<"          MODALIDAD DE JUEGO"<<endl;
            cout<<"***************************************"<<endl;
            cout<<"            1.- Facil"<<endl;
            cout<<"            2.- Normal"<<endl;
            cout<<"            3.- Dificl"<<endl;
            cout<<"\n0.- Regresar"<<endl;
            cin>>modoJuego;

            //Switch utilizado para llevar la seleccion del usuario a la parte del programa indicado.
            switch(modoJuego){
                case 0:
                    /*Si el usuario desea regresar al menu principal, la seleccion 0 llevara nuevamente
                    al usuario al primer menu para que elija la opcion deseada.*/
                    system("cls"); 
                    Inicio();
                    break;
                case 1: 
                    system("cls");
                    nivel = 8;
                    minas = 8;
                    nuevaPartida = true;
                    Juego.Empezar();
                    break;
                case 2:
                    system("cls");
                    nivel = 10;
                    minas = 15;
                    nuevaPartida = true;
                    Juego.Empezar();
                    break;
                case 3:
                    system("cls");
                    nivel = 15;
                    minas = 25;
                    nuevaPartida = true;
                    Juego.Empezar();
                    break;
                default: //Si se coloca un numero fuera de la seleccion, se indica que no existe y el programa empieza de nuevo.
                    system("cls");
                    cout<<"     Ese modo de juego no existe.\n"<<endl;
                    break;
                }
            }
        }

        //Funcion que permite al usuario continuar con una partida anteriormente guardada.
        void ContinuarPartida(){
            Juego.Continuar();
        }
};
