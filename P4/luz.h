

#ifndef _LUZ_H
#define _LUZ_H

#include "aux.h"

class Luz{

	private:

		Tupla4f color_ambiente, color_difuso, color_especular;
		Tupla4f posicion; // Dependiendo si es posicional, acaba en 1.0,
						  // y si es direccional, acaba en 0.0
		GLenum numero_luz;
		float angulo = 0.0;

	public:

		Luz();
		Luz(GLenum id, Tupla4f ambiente, Tupla4f difuso, Tupla4f especular,
			Tupla4f pos);
		void activar();
		void desactivar();
		void dibujar();
		void moverFoco();
		void setColorAmbiente(Tupla4f color);
		void setColorDifuso(Tupla4f color);
		void setColorEspecular(Tupla4f color);
		void setPosicion(Tupla4f pos);
		void setNumeroLuz(GLenum numero);
};

#endif
