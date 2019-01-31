#ifndef _ESCENA_H
#define _ESCENA_H

#include "ejes.h"
#include "malla.h"
#include "jerarquico.h"
#include "luz.h"
#include "camara.h"

class Escena
{

   private:

   Ejes ejes;

   // variables que definen la posicion de la camara en coordenadas polares
   GLfloat Observer_distance;
   GLfloat Observer_angle_x;
   GLfloat Observer_angle_y;

   // variables que controlan la ventana y la transformacion de perspectiva
   GLfloat Width, Height, Front_plane, Back_plane;

   void clear_window();
	void dibujar_objeto_actual();

  void tutorial();

   // Transformación de cámara
	void change_observer();

    int objeto_actual = 0 ; // objeto actual (el que se visualiza)
    bool draw_type = false ; // objeto actual (el que se visualiza)
    int draw_mode = 0 ; //tipo actual de dibujado (el que se visualiza)
    int shade_mode = 0;
    int num_modos = 4;
    int num_objetos = 0 ; // número de objetos (actualizado al crear los objetos en el constructor)

   // Objetos de la escena
    Cubo * cubo = nullptr ; // es importante inicializarlo a 'nullptr'
    Tetraedro * tetraedro = nullptr ;
    Piramide * piramide = nullptr;
    ObjPLY * objPly = nullptr;
    /*ObjRevolucion * objRev = nullptr;
    */Cilindro * cilindro = nullptr;
    Cono * cono = nullptr;
    Esfera * esfera = nullptr;
    ObjJerarquico * robot = nullptr;
    Cuadro * cuadro = nullptr;

    Cubo * cubo_sel = nullptr ;
	Tetraedro * tetraedro_sel = nullptr ;
	Piramide * piramide_sel = nullptr ;
	Esfera * esfera_sel = nullptr;

    Luz * luz1 = nullptr;
    Luz * luz2 = nullptr;

    bool animaciones_activadas = false;
    std::vector<bool> animaciones_luces = {false,false};

    int luz_actual = 0;
    std::vector<Luz *> luces;
    std::vector<bool> luces_activas = {true,false};

    Camara * camara1 = nullptr;
    Camara * camara2 = nullptr;

    int camaraActiva = 1;
    std::vector<Camara *> camaras;

    bool luces_animadas();
    void conmutarAnimaciones ();

   // completar: añadir punteros a tetraedro u otros (práctica 1),
   //            y a un objeto PLY y de revolución (práctica 2),
   //           y a un objeto jerarquico (práctica 3).
   // ......

   public:

   Escena();
	void inicializar( int UI_window_width, int UI_window_height );
	void redimensionar( int newWidth, int newHeight ) ;
  void ratonMovido(int x, int y);

  void dibujaSeleccion() ;
  void procesa_pixel(float pixel[3]);

  void change_projection( const float ratio_xy );

	// Dibujar
	void dibujar() ;

	// Interacción con la escena
	bool teclaPulsada( unsigned char Tecla1, int x, int y ) ;
	void teclaEspecial( int Tecla1, int x, int y );

    void mgeDesocupado ();
};
#endif
