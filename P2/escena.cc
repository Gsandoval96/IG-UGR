

#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....

//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

Escena::Escena()
{
    Front_plane = 0.1;
    Back_plane = 2000.0;
    Observer_distance = 2.0;
    Observer_angle_x  = 0.0 ;
    Observer_angle_y  = 0.0 ;

    ejes.changeAxisSize( 5000 );

    // crear los objetos de las prácticas: Mallas o Jerárquicos....
    /*cubo = new Cubo();
    piramide = new Piramide();
    tetraedro = new Tetraedro();*/
    objPly = new ObjPLY("plys/ant.ply");
    objRev = new ObjRevolucion("plys/peon.ply",8,true,true);
    cilindro = new Cilindro(5,30);
    cono = new Cono(8,30);
    esfera = new Esfera(30,30);
    
    

    // .......completar: ...
    // .....

    num_objetos = 5 ; // se usa al pulsar la tecla 'O' (rotar objeto actual)
}

//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana, por
// tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//**************************************************************************

void Escena::inicializar( int UI_window_width, int UI_window_height )
{
	glClearColor( 1.0, 1.0, 1.0, 1.0 );// se indica cual sera el color para limpiar la ventana	(r,v,a,al)

	glEnable( GL_DEPTH_TEST );	// se habilita el z-bufer

	redimensionar( UI_window_width, UI_window_height );
}

// **************************************************************************
// Funcion que dibuja el objeto activo actual, usando su método 'draw'
// (llamada desde Escena::dibujar)
// ***************************************************************************

void Escena::dibujar_objeto_actual()
{
   using namespace std ;
    GLenum modo;
    
    switch(draw_type)
    {
        case 0:
            modo = GL_POINT;
            break;
        case 1:
            modo = GL_LINE;
            break;
        case 2:
            modo = GL_FILL;
            break;
            
    }
    
   // (1) configurar OpenGL para el modo actual (puntos/lineas/sólido)
   //    llamar glPolygonMode, glColor... (y alguna cosas más), según dicho modo
    // .........completar (práctica 1)
    
    glPolygonMode(GL_FRONT_AND_BACK,modo);
    glShadeModel(GL_FLAT);
    glPointSize(4);
    glLineWidth(1.5);
  


   // (2) dibujar el objeto actual usando método 'draw' del objeto asociado al
   // valor entero en 'objeto_actual'
    
   switch( objeto_actual )
   {
      
    /*case 0:
           if ( piramide != nullptr ) piramide->draw(draw_mode) ;
    break ;
           
    case 1:
           if ( tetraedro != nullptr ) tetraedro->draw(draw_mode) ;
    break ;
           
    case 2:
           if ( cubo != nullptr ) cubo->draw(draw_mode) ;
    break ;*/
           
    case 0:
           if ( objPly != nullptr ) objPly->draw(draw_mode) ;
    break ;

    case 1:
           if ( objRev != nullptr ) objRev->draw(draw_mode) ;
    break ;

    case 2:
           if ( cilindro != nullptr ) cilindro->draw(draw_mode) ;
    break ;

    case 3:
           if ( cono != nullptr ) cono->draw(draw_mode) ;
    break ;
           
   case 4:
       if ( esfera != nullptr ) esfera->draw(draw_mode) ;
   break ;
      
      default:
         cout << "draw_object: el número de objeto actual (" << objeto_actual << ") es incorrecto." << endl ;
         break ;
   }
}

// **************************************************************************
//
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
//
// **************************************************************************

void Escena::dibujar()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
    glEnable(GL_CULL_FACE);
	change_observer();
   ejes.draw();
	dibujar_objeto_actual();
}

//**************************************************************************
//
// función que se invoca cuando se pulsa una tecla
// Devuelve true si se ha pulsado la tecla para terminar el programa (Q),
// devuelve false en otro caso.
//
//**************************************************************************

bool Escena::teclaPulsada( unsigned char tecla, int x, int y )
{
   using namespace std ;
   cout << "Tecla pulsada: '" << tecla << "'" << endl;

   switch( toupper(tecla) )
   {
      case 'Q' :
         // salir
         return true ;
         break ;
      case 'O' :
         // activar siguiente objeto
         objeto_actual = (objeto_actual+1) % num_objetos ;
         cout << "objeto actual == " << objeto_actual << endl ;
         break ;
      case 'V' :
         // activar siguiente objeto
       draw_mode = (draw_mode+1) % 3 ;
         cout << "Modo de pintado == " << draw_mode << endl ;
         break ;
       case 'M' :
           // activar siguiente objeto
           draw_type = (draw_type+1) % 3 ;
           cout << "Tipo de pintado == " << draw_type << endl ;
           break ;
   }
   return false ;
}
//**************************************************************************

void Escena::teclaEspecial( int Tecla1, int x, int y )
{
   switch ( Tecla1 )
   {
	   case GLUT_KEY_LEFT:
         Observer_angle_y-- ;
         break;
	   case GLUT_KEY_RIGHT:
         Observer_angle_y++ ;
         break;
	   case GLUT_KEY_UP:
         Observer_angle_x-- ;
         break;
	   case GLUT_KEY_DOWN:
         Observer_angle_x++ ;
         break;
	   case GLUT_KEY_PAGE_UP:
         Observer_distance *=1.2 ;
         break;
	   case GLUT_KEY_PAGE_DOWN:
         Observer_distance /= 1.2 ;
         break;
	}

	//std::cout << Observer_distance << std::endl;
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//
// ratio_xy : relacción de aspecto del viewport ( == ancho(X) / alto(Y) )
//
//***************************************************************************

void Escena::change_projection( const float ratio_xy )
{
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
    const float wy = 0.84*Front_plane,
    wx = ratio_xy*wy ;
    glFrustum( -wx, +wx, -wy, +wy, Front_plane, Back_plane );
}
//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar( int newWidth, int newHeight )
{
    Width = newWidth;
    Height = newHeight;
    change_projection( float(Width)/float(Height) );
    glViewport( 0, 0, Width, Height );
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void Escena::change_observer()
{
   // posicion del observador
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef( 0.0, 0.0, -Observer_distance );
    glRotatef( Observer_angle_x, 1.0 ,0.0, 0.0 );
    glRotatef( Observer_angle_y, 0.0, 1.0, 0.0 );
}
