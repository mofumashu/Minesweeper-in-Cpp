/*
Universidad Nacional Experimental de Guayana
Estructura de Datos - Seccion 1
Prof. Carlos Abaffy

    Estudiantes:
    Camila Quiroz - V30.577.138
    Merry-am Blanco - V30.810.720
    Sebastian Ortiz - V

                                    BUSCAMINAS
        Juego de estrategia donde el jugador debera descubrir todas las celdas sin bombas.
        Si el jugador descubre una celda con bomba, el juego acabara y se reiniciara.
        El progreso del juego puede ser guardado para que este, si desea, vuelva a jugar
        nuevamente donde lo dejo la ultima vez.
        Juego realizado con interfaz de CMD utilizando librerias nativas de C++.
*/

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