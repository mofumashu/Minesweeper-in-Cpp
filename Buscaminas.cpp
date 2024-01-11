#include "LibreriaMain.h"
#include "Interfaz.cpp" //Llamado al archivo 'Interfaz' donde se mostrara todo referente al juego graficamente.

int main(){
    /*Se crea el objeto 'Juego' para poder iniciar los menus y
    el juego buscaminas en si.*/
    UI Juego;

    /*Llamado de funcion 'Sesion' para mostrar en 
    pantalla los menus de seleccion e inicio de sesion
    para el usuario*/
    Juego.Sesion();

}
