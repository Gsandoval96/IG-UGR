

#ifndef _CAMARA_H
#define _CAMARA_H

#include "aux.h"
#include "tuplasg.h"

class Camara{

	private:

		float distancia;
		int tipo;
		float left;
		float right;
		float near;
		float far;
		float top;
		float bottom;
		float ob_a_x;
		float ob_a_y;

		int x_ant, y_ant;

	public:

		Camara (float dist, int tip, float izda, float dcha, float ne, float fa,
				float to, float bot);
		void setObserver();
		void setProyeccion();
		void rotarX();
		void rotarY();
		void girar(float x, float y);
		void zoom(float factor);

};
#endif
