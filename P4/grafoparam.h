// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: GrafoParam.h
// -- declaraciones de clase para el objeto jerárquico de la práctica 3
//
// #############################################################################

#ifndef GRAFOPARAM_H_INCLUDED
#define GRAFOPARAM_H_INCLUDED

#include "malla.h" // añadir .h de cualquier objetos malla indexada usados....

constexpr int num_parametros = 4 ; // número de parámetros o grados de libertad
                                   // de este modelo

typedef int ModoVis;

class GrafoParam
{
   public:

   // crea mallas indexadas (nodos terminales del grafo)
   GrafoParam();

   // función principal de visualización
   void draw( const ModoVis p_modo_vis, const bool p_usar_diferido );

   // actualizar valor efectivo de un parámetro (a partir de su valor no acotado)
   void actualizarValorEfe( const unsigned iparam, const float valor_na );

   // devuelve el número de parámetros
   unsigned numParametros() { return num_parametros ; }

   private:

   // métodos de dibujo de subgrafos
   void antena( const float altura, const float radio_cil );
   void mandibula( const float altura, const float radio_cil, const float ancho_cubo, const float alto_cubo);
   void cabeza(const float ancho_cabeza);
    void ojo(const float ancho_cabeza,const float alargar);
    void musculo_boca(const float altura,const float ancho_cubo,const float alto_cubo);
	void cabeza_ojos(const float ancho_ojo,const float alargar_ojo,  const float ancho_cabeza );



   // objetos tipo malla indexada (nodos terminales)

   Cilindro * cilindro = nullptr ;
   Esfera *     esfera     = nullptr ;
    Cubo *     cubo     = nullptr ;
	Cilindro * cilindro_ojos = nullptr;
Esfera *     esfera_ojos     = nullptr ;
Cilindro *    pupila     = nullptr ;
Esfera *     esfera_antena     = nullptr ;

   // parámetros de la llamada actual (o última) a 'draw'
   ModoVis modo_vis ;      // modo de visualización
   bool    usar_diferido ; // modo de envío (true -> diferido, false -> inmediato)


   // valores efectivos de los parámetros (angulos, distancias, factores de
   // escala, etc.....) calculados a partir de los valores no acotados

    float altura_antena;       // altura de la antena
    float longitud_ojos; //ojos
    float altura_mandibula;       // altura de la mandibula
	float ag_rotacion_1;


} ;

#endif
