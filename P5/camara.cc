

#include "camara.h"

Camara::Camara (float dist, int tip, float izda, float dcha, float ne, float fa,
				float to, float bot){

	distancia = dist;
	tipo = tip;
	left = izda;
	right = dcha;
	near = ne;
	far = fa;
	top = to;
	bottom = bot;

	// Ángulos de rotación del eje x e y
	ob_a_x = 0.0;
	ob_a_y = 0.0;

	x_ant = 0;
	y_ant = 0;

}

void Camara::rotarX (){

	glRotatef(ob_a_x, 1.0, 0.0, 0.0);
}

void Camara::rotarY (){

	glRotatef(ob_a_y, 0.0 ,1.0, 0.0);
}

void Camara::girar (float x, float y){

	ob_a_y += (x - x_ant);
	ob_a_x += (y - y_ant);

	x_ant = x;
	y_ant = y;
}

void Camara::zoom (float factor){

	left *= factor;
	right *= factor;
	top *= factor;
	bottom *= factor;
}

void Camara::setObserver (){
		glTranslatef(0.0, 0.0, -distancia);

		rotarY ();
		rotarX ();
}

void Camara::setProyeccion (){

	// Perspectiva
	if (tipo == 1){

		glFrustum (left, right, bottom, top, near, far);
	}
	// Ortogonal
	else{

		glOrtho (left, right, bottom, top, near, far);
	}
}
