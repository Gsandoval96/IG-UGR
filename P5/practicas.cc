//**************************************************************************
// Prácticas
//
// F.J. melero
//
// GPL
//**************************************************************************


#include "aux.h" // includes de OpenGL, windows, y librería std de C++
#include "escena.h"

// variable que contiene un puntero a la escena
Escena *escena = nullptr ;

bool estadoRaton = false;


//***************************************************************************
// Funcion principal que redibuja la escena
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void draw_scene(void)
{
	glDrawBuffer(GL_FRONT);

	if ( escena != nullptr )
      escena->dibujar();
}

void clickRaton(const int boton, const int estado, const int x, const int y){

	if(boton == GLUT_RIGHT_BUTTON){

	 if(estado == GLUT_DOWN)
		 estadoRaton = true;

	 else
		 estadoRaton = false;
 }

 if(boton == 3)
	 escena->change_projection(1.2);

 if(boton == 4)
	 escena->change_projection(0.8);

	 if(boton == GLUT_LEFT_BUTTON){

		 if(estado == GLUT_DOWN){

			 GLint viewport[4];

			 float pixel[3];

			 glGetIntegerv(GL_VIEWPORT, viewport);

			 glReadBuffer(GL_BACK);
			 glReadPixels(x, viewport[3]-y, 1, 1, GL_RGB, GL_FLOAT, (GLfloat *) &pixel[0]);
			 escena->procesa_pixel(pixel);

			 std::cout<<"PIXEL = "<<pixel[0] << " " << pixel[1] << " " << pixel[2]<<std::endl;
		 }
	 }

	 glutPostRedisplay();
}

void ratonMovido(const int x, const int y){

  if(estadoRaton)
    escena->ratonMovido(x,y);

  glutPostRedisplay();
}

//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size( int newWidth, int newHeight )
{
	if ( escena != nullptr )
      escena->redimensionar(newWidth,newHeight);
	glutPostRedisplay();
}


//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_keys( unsigned char tecla, int x, int y )
{
	int salir = 0;

   if ( escena!= nullptr )
      salir = escena->teclaPulsada( tecla, x, y );

	if ( salir )
   {
		delete escena;
      escena = nullptr ;
		exit(0);
	}
   else
		glutPostRedisplay();
}

//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_keys( int tecla, int x, int y )
{
	if (escena!=NULL)
		escena->teclaEspecial( tecla, x, y );
	glutPostRedisplay();
}

//***************************************************************************
// Función que maneja el evento idle
//***************************************************************************

void funcion_desocupado (){

    if (escena != NULL){

        escena->mgeDesocupado();
    }

    glutPostRedisplay();
}

//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************

int main( int argc, char **argv )
{
   using namespace std ;

   // crear la escena (un puntero a la misma)
   escena = new Escena();

   // Incialización de GLUT

   // se llama a la inicialización de glut
   glutInit( &argc, argv );

   // se indica las caracteristicas que se desean para la visualización con OpenGL
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

   // variables que determninan la posicion y tamaño de la ventana X
   const int UI_window_pos_x  = 50,
             UI_window_pos_y  = 50,
             UI_window_width  = 500,
             UI_window_height = 500;

   // posicion de la esquina inferior izquierdad de la ventana
   glutInitWindowPosition(UI_window_pos_x,UI_window_pos_y);

   // tamaño de la ventana (ancho y alto)
   glutInitWindowSize(UI_window_width,UI_window_height);

   // llamada para crear la ventana, indicando el titulo
   glutCreateWindow("Practicas IG: Guillermo Sandoval Schmidt");

   // asignación de la funcion llamada "dibujar" al evento de dibujo
   glutDisplayFunc( draw_scene );

   // asignación de la funcion llamada "cambiar_tamanio_ventana" al evento correspondiente
   glutReshapeFunc( change_window_size );

   // asignación de la funcion llamada "tecla_normal" al evento correspondiente
   glutKeyboardFunc( normal_keys );

   // asignación de la funcion llamada "tecla_Especial" al evento correspondiente
   glutSpecialFunc( special_keys );

   // inicialización de librería GLEW (solo en Linux)
   #ifdef LINUX
   const GLenum codigoError = glewInit();

   if ( codigoError != GLEW_OK ) // comprobar posibles errores
   {
      cout << "Imposible inicializar ’GLEW’, mensaje recibido: "
             << glewGetErrorString(codigoError) << endl ;
      exit(1) ;
   }
   #endif

   // funcion de inicialización de la escena (necesita que esté la ventana creada)
   escena->inicializar( UI_window_width, UI_window_height );

   // TEST
	 glutMouseFunc(clickRaton);
	 glutMotionFunc(ratonMovido);

   // ejecutar del bucle de eventos
   glutMainLoop();

   return 0;
}
