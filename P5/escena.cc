
#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....
#include <string>

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
    cubo = new Cubo(NEGRO);
    piramide = new Piramide(NEGRO);
    tetraedro = new Tetraedro(NEGRO);
    objPly = new ObjPLY("plys/beethoven.ply",NEGRO);
    /*objRev = new ObjRevolucion("plys/peon.ply",8,true,true);*/
    cilindro = new Cilindro(5,30,NEGRO);
    cono = new Cono(8,30,NEGRO);
    esfera = new Esfera(100,100,NEGRO);
    robot = new ObjJerarquico();
    cuadro = new Cuadro();

    cubo_sel = new Cubo(AMARILLO);
  	tetraedro_sel = new Tetraedro(VERDE);
  	piramide_sel = new Piramide(AZUL);
  	esfera_sel = new Esfera(100, 100, ROJO);

    luz1 = new Luz(GL_LIGHT1,{0.0,0.0,0.0,1.0},{1.0,1.0,1.0,1.0},
                            {1.0,1.0,1.0,1.0},{5.0,2.0,5.0,0.0});
    luces.push_back(luz1);
    luz2 = new Luz(GL_LIGHT2,{0.0,0.0,0.0,1.0},{1.0,0.0,1.0,1.0},
                            {1.0,0.0,1.0,1.0},{5.0,2.0,5.0,1.0});
    luces.push_back(luz2);

    Camara * camara1 = new Camara(30, 0, -5, 5, 5, 1000.0, 5, -5); // Ortogonal
    Camara * camara2 = new Camara(10, 1, -5, 5, 5, 1000.0, 5, -5); // Perspectiva

    camaras.push_back(camara1);
    camaras.push_back(camara2);


    // .......completar: ...
    // .....

    num_objetos = 10 ; // se usa al pulsar la tecla 'O' (rotar objeto actual)
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
  tutorial();
}

// **************************************************************************
// Funcion que dibuja el objeto activo actual, usando su método 'draw'
// (llamada desde Escena::dibujar)
// ***************************************************************************

void Escena::dibujar_objeto_actual()
{
   using namespace std ;
    GLenum modo, shade;

    if(luces_activas[luz_actual]){
      luces[luz_actual]->activar();
    }

    if(luces.size()>0){
    for(int i=0; i<luces.size(); i++){
      if(luces[i] != nullptr && luces_activas[i])
        luces[i]->dibujar();
    }
  }
  else{std::cout<<luces.size();}

    if(!luces_activas[luz_actual]){
      luces[luz_actual]->desactivar();
    }

    switch(draw_mode)
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

    switch (shade_mode) {
      case 0:
            shade = GL_FLAT;
            break;
      case 1:
            shade = GL_SMOOTH;
            break;
    }

   // (1) configurar OpenGL para el modo actual (puntos/lineas/sólido)
   //    llamar glPolygonMode, glColor... (y alguna cosas más), según dicho modo
    // .........completar (práctica 1)

    glPolygonMode(GL_FRONT_AND_BACK,modo);
    glShadeModel(shade);
    glPointSize(4);
    glLineWidth(1.5);



   // (2) dibujar el objeto actual usando método 'draw' del objeto asociado al
   // valor entero en 'objeto_actual'

   switch( objeto_actual )
   {

    case 4:
           if ( piramide != nullptr ) piramide->draw(draw_mode,draw_type) ;
    break ;

    case 5:
           if ( tetraedro != nullptr ) tetraedro->draw(draw_mode,draw_type) ;
    break ;

    case 6:
           if ( cubo != nullptr ) cubo->draw(draw_mode,draw_type) ;
    break ;

    case 0:
           if ( objPly != nullptr ) objPly->draw(draw_mode,draw_type) ;
    break ;

    /*case 7:
           if ( objRev != nullptr ) objRev->draw(draw_mode,draw_type) ;
    break ;*/

    case 7:
           if ( cilindro != nullptr ) cilindro->draw(draw_mode,draw_type) ;
    break ;

    case 8:
           if ( cono != nullptr ) cono->draw(draw_mode,draw_type) ;
    break ;

   case 1:
       if ( esfera != nullptr ) esfera->draw(draw_mode,draw_type) ;
   break ;

       case 2:
           if ( robot != nullptr ) robot->draw(draw_mode,draw_type) ;
           break ;

      case 3:
            if(cuadro != nullptr) cuadro->draw(draw_mode,draw_type);
            break;

      case 9:

        			glPushMatrix();

        				glTranslatef(-2.5, 0, 0);
        				cubo->draw(draw_mode,draw_type);

        			glPopMatrix();

        			glPushMatrix();

        				glTranslatef(-1, 0, 0);
        				esfera->draw(draw_mode,draw_type);

        			glPopMatrix();

        			glPushMatrix();

        				glTranslatef(1, 0.5, 0);
        				piramide->draw(draw_mode,draw_type);

        			glPopMatrix();

        			glPushMatrix();

        				glTranslatef(2.5, 0, 0);
        				tetraedro->draw(draw_mode,draw_type);

        			glPopMatrix();

        		break;

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
  glEnable(GL_NORMALIZE);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
    glEnable(GL_CULL_FACE);
	change_observer();
   ejes.draw();
	dibujar_objeto_actual();

  glDrawBuffer(GL_FRONT);

  if(objeto_actual == 9){
		glDrawBuffer(GL_BACK);
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
		change_observer();
		dibujaSeleccion();

	}



	glFlush();
}

void Escena::tutorial(){

  std::string obj_act ="";
  std::string mod_dib = "";
  std::string tip_dib = "";
  std::string tip_suv = "";

  switch (objeto_actual) {
    case 0:
      obj_act = "BEETHOVEN";
    break;

    case 1:
      obj_act = "ESFERA";
    break;

    case 2:
      obj_act = "MODELO JERÁRQUICO";
    break;

    case 3:
      obj_act = "CUADRO";
    break;

    case 4:
      obj_act = "PIRAMIDE";
    break;

    case 5:
      obj_act = "TETRAEDRO";
    break;

    case 6:
      obj_act = "CUBO";
    break;

    case 7:
      obj_act = "CILINDRO";
    break;

    case 8:
      obj_act = "CONO";
    break;

    case 9:
      obj_act = "ESCENA INTERACTIVA";
    break;
  }

  switch (draw_mode) {
    case 0:
      mod_dib = "PUNTOS";
    break;

    case 1:
      mod_dib = "LÍNEAS";
    break;

    case 2:
      mod_dib = "SÓLIDO";
    break;

    case 3:
      mod_dib = "AJEDREZ";
    break;
  }

  if(draw_type) {tip_dib = "DIFERIDO";}
  else {tip_dib = "INMEDIATO";}

  if(shade_mode==0) {tip_suv = "FLAT";}
  else {tip_suv = "SMOOTH";}


  std::cout<<std::endl;

  std::cout<<"**********************************************"<<std::endl;
  std::cout<<"*                 TUTORIAL                   *"<<std::endl;
  std::cout<<"**********************************************"<<std::endl<<std::endl;

  std::cout<<"*** TECLAS ***"<<std::endl<<std::endl;

  std::cout<<"*GENERALES*"<<std::endl;
  std::cout<<"Pulse q/Q para salir del programa"<<std::endl<<std::endl;

  std::cout<<"*OBJETOS/DIBUJADO*"<<std::endl;
  std::cout<<"Pulse o/O para cambiar al siguiente objeto"<<std::endl;
  std::cout<<"Pulse m/M para cambiar de modo de dibujado (puntos, lines, sólido, ajedrez)"<<std::endl;
  std::cout<<"Pulse v/V para cambiar entre diferido e inmediato"<<std::endl<<std::endl;

  std::cout<<"*MODELO JERÁRQUICO*"<<std::endl;
  std::cout<<"Pulse a/A para activar/desactivar la animación del modelo"<<std::endl;
  std::cout<<"Pulse p/P para cambiar el parámetro actual del modelo"<<std::endl;
  std::cout<<"Pulse C para aumentar el valor del parámetro actual del modelo"<<std::endl;
  std::cout<<"Pulse c para disminuir el valor del parámetro actual del modelo"<<std::endl;
  std::cout<<"Pulse > para aumentar la velocidad de la animación del modelo"<<std::endl;
  std::cout<<"Pulse < para disminuir la velocidad de la animación del modelo"<<std::endl<<std::endl;

  std::cout<<"*LUCES*"<<std::endl;
  std::cout<<"Pulse s/S para cambiar de tipo de suavizado"<<std::endl;
  std::cout<<"Pulse 1|2 para elegir el foco actual"<<std::endl;
  std::cout<<"Pulse l/L para encender/apagar el foco actual"<<std::endl;
  std::cout<<"Pulse k/K para activar/desactivar la animación del foco actual"<<std::endl<<std::endl;

  std::cout<<"*CAMARA*"<<std::endl;
  std::cout<<"Pulse F1|F2 para elegir la cásmara"<<std::endl;
  std::cout<<"Click derecho + Desplazar ratón para girar la cámara"<<std::endl;
  std::cout<<"Click izquierdo para cambiar color figura (solo en objeto 10)"<<std::endl<<std::endl;

  std::cout<<"*** INFORMACIÓN ***"<<std::endl<<std::endl;

  std::cout<<"El objeto actual es: " << obj_act << std::endl;
  std::cout<<"El modo de dibujado es: " << mod_dib << std::endl;
  std::cout<<"El tipo de dibujado es: " << tip_dib << std::endl;
  std::cout<<"El tipo de suavizado es: " << tip_suv << std::endl;
  std::cout<<"El foco actual es el número: " << luz_actual << std::endl;
  for(int i=0;i<luces.size();i++){
    std::cout<<"El foco "<< i <<" está (0 apagado, 1 encendido): " << luces_activas[i] << std::endl;
    std::cout<<"La animación del foco "<< i <<" está (0 desactivada, 1 activada): " << animaciones_luces[i] << std::endl;
  }
  std::cout<<"La cámara actual es la número: " << camaraActiva <<std::endl;
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

   switch( tecla )
   {
      case 'q' :
      case 'Q' :
         // salir
         return true ;
         break ;
      case 'o' :
      case 'O' :
         // activar siguiente objeto
         objeto_actual = (objeto_actual+1) % num_objetos ;
         cout << "objeto actual == " << objeto_actual << endl ;
         break ;
     case 's' :
     case 'S' :
        // activar siguiente modo de sombras
        shade_mode = (shade_mode+1) % 2 ;
        cout << "modo de sombras actual == " << shade_mode << endl ;
        break ;
      case '1' :
      case '2' :
         luz_actual = (int)tecla - 49;
         cout << "Luz actual == Foco " << luz_actual << endl ;
         break ;
      case 'l' :
      case 'L' :
          luces_activas[luz_actual] = !luces_activas[luz_actual];
          break;
      case 'v' :
      case 'V' :
        //diferido o no
        draw_type = !draw_type;
         cout << "Modo de pintado == " << draw_type << endl ;
         break ;
       case 'm' :
       case 'M' :
           if(draw_type) draw_mode = (draw_mode+1) % (num_modos-1) ;
           else draw_mode = (draw_mode+1) % num_modos ;
           cout << "Tipo de pintado == " << draw_mode << endl ;
           break ;
       case 'p' :
       case 'P' :
           robot->siguienteParametro();
           break;
       case 'a':
       case 'A':
           if (objeto_actual != 2){

               std::cout << "El objeto actual no es el objeto jerárquico." << std::endl;
           }
           else{
              animaciones_activadas = !animaciones_activadas;
               conmutarAnimaciones();
           }
           break;
       case 'k':
       case 'K':
           if(luces_activas[luz_actual]){
              animaciones_luces[luz_actual] = !animaciones_luces[luz_actual];
              std::cout<<animaciones_luces[luz_actual]<<std::endl;
               conmutarAnimaciones();
           }
           else{
             std::cout<<"La luz actual no está activa." << std::endl;
           }
           break;
       case 'C':
           robot->incrementaParamAct();
           break;
       case 'c':
           robot->decrementaParamAct();
           break;
       case '>':
           robot->acelerar();
           break;
       case '<':
           robot->decelerar();
           break;
   }
   tutorial();
   return false ;
}
//**************************************************************************

void Escena::teclaEspecial( int Tecla1, int x, int y )
{
   switch ( Tecla1 )
   {
      case GLUT_KEY_F1:
        camaraActiva = 0;
         break;
      case GLUT_KEY_F2:
        camaraActiva = 1;
         break;
         case GLUT_KEY_LEFT:
     			Observer_angle_x++;
     			camaras[camaraActiva]->girar(Observer_angle_x, Observer_angle_y);
     		break;

     		case GLUT_KEY_RIGHT:
     			Observer_angle_x--;
     			camaras[camaraActiva]->girar(Observer_angle_x, Observer_angle_y);
     		break;

     		case GLUT_KEY_UP:
     			Observer_angle_y++;
     			camaras[camaraActiva]->girar(Observer_angle_x, Observer_angle_y);
     		break;

     		case GLUT_KEY_DOWN:
     			Observer_angle_y--;
     			camaras[camaraActiva]->girar(Observer_angle_x, Observer_angle_y);
     		break;


	}
  tutorial();

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
   camaras[camaraActiva]->zoom(ratio_xy);
   camaras[camaraActiva]->setProyeccion();
    /*const float wy = 0.84*Front_plane,
    wx = ratio_xy*wy ;
    glFrustum( -wx, +wx, -wy, +wy, Front_plane, Back_plane );*/
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
   camaras[camaraActiva]->setObserver();
}

bool Escena::luces_animadas(){
  bool animada = false;
  for(int i=0;i<animaciones_luces.size() && !animada;i++)
    animada = animaciones_luces[i];
  //std::cout<<animada<<std::endl;
  return animada;
}

//***************************************************************************
// Función para actualizar el estado de los parámetros del objeto jerárquico
//***************************************************************************

void Escena::mgeDesocupado (){

    if (animaciones_activadas){

        robot->actualizarEstado ();
    }

    if (luces_animadas()){
        for(int i=0;i<animaciones_luces.size();i++)
          if(animaciones_luces[i])
            luces[i]->moverFoco();
    }

    glutPostRedisplay();
}

//***************************************************************************
// Función para activar/desactivar las animaciones
//***************************************************************************

void Escena::conmutarAnimaciones (){

    if (animaciones_activadas){

        robot->inicioAnimaciones ();

        glutIdleFunc (funcion_desocupado);
    }
    else if(luces_animadas()){
        glutIdleFunc(funcion_desocupado);
    }
    else{
        glutIdleFunc (nullptr);
    }
}

void Escena :: ratonMovido(const int x, const int y){

	camaras[camaraActiva]->girar(x, y);

}

void Escena :: dibujaSeleccion(){

	glShadeModel( GL_FLAT );
	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);
	glLineWidth(2);
	glPointSize(4);


	glDisable(GL_DITHER);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE);

	glPushMatrix();

		glTranslatef(-2.5, 0, 0);
		cubo_sel->rellenarColores({1.0, 1.0, 0.0});
		cubo_sel->draw(draw_mode,draw_type);

	glPopMatrix();

	glPushMatrix();

		glTranslatef(-1, 0, 0);
		esfera_sel->rellenarColores({1.0, 0.0, 0.0});
		esfera_sel->draw(draw_mode,draw_type);

	glPopMatrix();

	glPushMatrix();

		glTranslatef(1, 0.5, 0);
		piramide_sel->rellenarColores({0.0, 0.0, 1.0});
		piramide_sel->draw(draw_mode,draw_type);

	glPopMatrix();

	glPushMatrix();

		glTranslatef(2.5, 0, 0);
		tetraedro_sel->rellenarColores({0.0, 1.0, 0.0});
		tetraedro_sel->draw(draw_mode,draw_type);

	glPopMatrix();

	glEnable(GL_DITHER);
}

void Escena :: procesa_pixel(float pixel[3]){

	if(pixel[0] == 1.0 && pixel[1] == 1.0 && pixel[2] == 0.0){

		Tupla3f colores = cubo->mostrarColores();

		if(colores[0] == 1.0 && colores[1] == 1.0 && colores[2] == 0.0)
			cubo->rellenarColores({0.0, 0.0, 0.0});

		else
			cubo->rellenarColores({1.0, 1.0, 0.0});

		cubo->draw(draw_mode,draw_type);
	}

	if(pixel[0] == 1.0 && pixel[1] == 0.0 && pixel[2] == 0.0){

		Tupla3f colores = esfera->mostrarColores();

		if(colores[0] == 1.0 && colores[1] == 0.0 && colores[2] == 0.0)
			esfera->rellenarColores({0.0, 0.0, 0.0});

		else
			esfera->rellenarColores({1.0, 0.0, 0.0});

		esfera->draw(draw_mode,draw_type);
	}

	if(pixel[0] == 0.0 && pixel[1] == 0.0 && pixel[2] == 1.0){

		Tupla3f colores = piramide->mostrarColores();

		if(colores[0] == 0.0 && colores[1] == 0.0 && colores[2] == 1.0)
			piramide->rellenarColores({0.0, 0.0, 0.0});

		else
			piramide->rellenarColores({0.0, 0.0, 1.0});

		piramide->draw(draw_mode,draw_type);
	}

	if(pixel[0] == 0.0 && pixel[1] == 1.0 && pixel[2] == 0.0){

		Tupla3f colores = tetraedro->mostrarColores();

		if(colores[0] == 0.0 && colores[1] == 1.0 && colores[2] == 0.0)
			tetraedro->rellenarColores({0.0, 0.0, 0.0});

		else
			tetraedro->rellenarColores({0.0, 1.0, 0.0});

		tetraedro->draw(draw_mode,draw_type);
	}

}
