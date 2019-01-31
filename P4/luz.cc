

#include "aux.h"
#include "luz.h"

/******************************************************************************/
// CONSTRUCTOR SIN PARÁMETROS DE LUZ

Luz :: Luz(){
}

/******************************************************************************/
// CONSTRUCTOR CON PARÁMETROS DE LUZ

Luz :: Luz(GLenum id, Tupla4f ambiente, Tupla4f difuso, Tupla4f especular,
		   Tupla4f pos){

	numero_luz = id;
	color_ambiente = ambiente;
	color_difuso = difuso;
	color_especular = especular;
	posicion = pos;
}

/******************************************************************************/
// MÉTODO ACTIVAR -> para activar la luz número i

void Luz :: activar(){

	glEnable(GL_LIGHTING);
	glEnable(numero_luz);
}

/******************************************************************************/
// MÉTODO ACTIVAR MOVIMIENTO-> para activar el movimiento la luz número i

void Luz :: moverFoco(){
	angulo += 3.0;
}

/******************************************************************************/
// MÉTODO DESACTIVAR -> para desactivar la luz número i

void Luz :: desactivar(){
	glDisable(numero_luz);
}

/******************************************************************************/
// MÉTODO DIBUJAR

void Luz :: dibujar(){

	glLightfv(numero_luz, GL_AMBIENT, color_ambiente);
	glLightfv(numero_luz, GL_DIFFUSE, color_difuso);
	glLightfv(numero_luz, GL_SPECULAR, color_especular);
	glPushMatrix();
		glRotatef(angulo,0.0,1.0,0.0);
		glLightfv(numero_luz, GL_POSITION, posicion);
	glPopMatrix();
}

/******************************************************************************/
// MÉTODO SET COLOR AMBIENTE

void Luz :: setColorAmbiente(Tupla4f color){

	color_ambiente = color;
}

/******************************************************************************/
// MÉTODO SET COLOR DIFUSO

void Luz :: setColorDifuso(Tupla4f color){

	color_difuso = color;
}

/******************************************************************************/
// MÉTODO SET COLOR ESPECULAR

void Luz :: setColorEspecular(Tupla4f color){

	color_especular = color;
}

/******************************************************************************/
// MÉTODO SET POSICIÓN

void Luz :: setPosicion(Tupla4f pos){

	posicion = pos;
}

/******************************************************************************/
// MÉTODO SET NÚMERO LUZ

void Luz :: setNumeroLuz(GLenum numero){

	numero_luz = numero;
}

/******************************************************************************/
