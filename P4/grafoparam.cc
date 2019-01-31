// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: GrafoParam.cc
// -- implementación del objeto jerárquico de la práctica 3
//
// #############################################################################


#include "grafoparam.h"

// -----------------------------------------------------------------------------
// constructor: crea mallas indexadas en los nodos terminales del grafo

GrafoParam::GrafoParam()
{
   cilindro = new Cilindro( 4, 16, GRIS );
   esfera   = new Esfera( 20, 20, GRIS);
pupila   = new Cilindro( 20, 20,NEGRO);
esfera_antena   = new Esfera( 20, 20, ROJO);
    cubo = new Cubo(AMARILLO);
 cilindro_ojos = new Cilindro( 4, 16, {0.9,0.9,0.9} );
esfera_ojos   = new Esfera( 20, 20, {0.9,0.9,0.9});
}
// -----------------------------------------------------------------------------
// actualizar valor efectivo de un parámetro (a partir de su valor no acotado)

void GrafoParam::actualizarValorEfe( const unsigned iparam, const float valor_na )
{
   assert( iparam < num_parametros );

   using namespace std ;
   //cout << "GrafoParam::actualizarValorEfe( " << iparam << ", " << valor_na << " )" << endl ;

   constexpr float vp = 2.5 ;

   switch( iparam )
   {
      case 0:
         // altura 0: oscila entre 0.7 y 1.3, a 0.5 oscilaciones por segundo
         // inicialmente es 1.0 (media de los valores extremos)
         altura_antena= 1.0 + 0.3*sin( 0.5*(2.0*M_PI*valor_na) );
         break ;
         case 1:
            // altura 0: oscila entre 0.7 y 1.3, a 0.5 oscilaciones por segundo
            // inicialmente es 1.0 (media de los valores extremos)
            longitud_ojos= 0.7 + 0.3*sin( 0.3*(2.0*M_PI*valor_na) - M_PI/2);
            break ;
       case 2:
           // altura 1: oscila entre 0.7 y 1.3, a 0.5 oscilaciones por segundo
           // inicialmente es 1.0 (media de los valores extremos)
           altura_mandibula= -0.25 - 0.25*sin( 0.5*(2.0*M_PI*valor_na) - M_PI/2 ); //0.25 es un cuarto de la longitud del musculo de la mandibula
           break ;

	case 3:
         // rotación 1: oscila a 0.6 oscilaciones por segundo
         // inicialmente es 1.0 (media de los valores extremos)
         ag_rotacion_1 = 1.0 + 10.0*sin( 0.3*(2.0*M_PI*valor_na) );
         break ;


   }
}

// -----------------------------------------------------------------------------
// visualización del objeto Jerárquico con OpenGL,
// mediante llamadas a los métodos 'draw' de los sub-objetos

void GrafoParam::draw( const ModoVis p_modo_vis, const bool p_usar_diferido )
{
   // asegurarnos que está inicializado ok

   assert( esfera     != nullptr );
   assert( cilindro != nullptr );
    assert( cubo != nullptr );

   // guardar parametros de visualización para esta llamada a 'draw'
   // (modo de visualización, modo de envío)

   modo_vis      = p_modo_vis ;
   usar_diferido = p_usar_diferido ;

   // dibujar objetos

   constexpr float
    radio_cil_0 = 0.2 , // radio del cilindro de la antena

    radio_cil_mandibula = 2.0 , // radio del cilindro de la mandibula
    ancho_cubo_mandibula = 0.2, //ancho del cubo de la mandibula
    alto_cubo_mandibula = 1.0,

    ancho_cabeza = 2.0; //ancho de cubo y cilindro de la cabeza



   glPushMatrix();
	glPushMatrix();
	glTranslatef(0.0,2.0,0.0);
	glRotatef(ag_rotacion_1,0.0,0.0,1.0);
	glTranslatef(0.0,-2.0,0.0);
      
        glPushMatrix();
            mandibula(altura_mandibula,radio_cil_mandibula,ancho_cubo_mandibula,alto_cubo_mandibula);
        glPopMatrix();
        glPushMatrix();
	    glTranslatef( 0.0, alto_cubo_mandibula/2, 0.0 );
	    cabeza_ojos(0.5,longitud_ojos,ancho_cabeza);
	glPopMatrix();
        glPushMatrix();
            glTranslatef( 0.0, alto_cubo_mandibula+ancho_cabeza, 0.0);
            antena(altura_antena,radio_cil_0);
        glPopMatrix();

	glPopMatrix();
   glPopMatrix();
}
// -----------------------------------------------------------------------------
// dibuja un sub-objeto parametrizado:
// es la antena que se extendiende y contrae hacia arriba

void GrafoParam::antena( const float altura,
                          const float radio_cil )
{

    glPushMatrix();
        glPushMatrix();
          glScalef( radio_cil, altura, radio_cil );
          cilindro->draw( modo_vis, usar_diferido );
        glPopMatrix();
        glPushMatrix( );
          glTranslatef( 0.0, altura, 0.0 );
          glScalef( 2*radio_cil, 2*radio_cil, 2*radio_cil );
          esfera_antena->draw( modo_vis, usar_diferido );
        glPopMatrix();
    glPopMatrix();
}

// -----------------------------------------------------------------------------
// dibuja un sub-objeto parametrizado:
// es la cabeza con ojos
void GrafoParam::cabeza_ojos(const float ancho_ojo,const float alargar_ojo,  const float ancho_cabeza )
{
	glPushMatrix();
		glPushMatrix();
		    cabeza(ancho_cabeza);
		glPopMatrix();
		glPushMatrix();
		    glTranslatef( -0.5, 3*ancho_cabeza/4, 0.0 );
		    ojo(ancho_ojo,alargar_ojo);
		glPopMatrix();
		glPushMatrix();
		    glTranslatef( 0.5, 3*ancho_cabeza/4, 0.0 );
		    ojo(ancho_ojo,alargar_ojo);
		glPopMatrix();
	glPopMatrix();

}

// -----------------------------------------------------------------------------
// dibuja un sub-objeto parametrizado:
// es el musculo que se extendiende y contrae hacia abajo

void GrafoParam::musculo_boca( const float altura,
                        const float ancho_cubo, const float alto_cubo )
{

    glPushMatrix();
        glPushMatrix();
            glTranslatef(0.0,alto_cubo/2,0.0);
            glScalef( ancho_cubo, alto_cubo/2, ancho_cubo );
            cubo->draw( modo_vis, usar_diferido );
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0.0,altura,0.0);
            glScalef( ancho_cubo, alto_cubo, ancho_cubo );
            cubo->draw( modo_vis, usar_diferido );
        glPopMatrix();
    glPopMatrix();
}

// -----------------------------------------------------------------------------
// dibuja un sub-objeto parametrizado:
// es la mandibula

void GrafoParam::mandibula( const float altura,
 const float radio_cil, const float ancho_cubo, const float alto_cubo )
 {

 glPushMatrix();
     glPushMatrix();
            glTranslatef( -(radio_cil+ancho_cubo)/2, 0.0, 0.0 );
            musculo_boca(altura,ancho_cubo,alto_cubo);
     glPopMatrix();
     glPushMatrix();
            glTranslatef( (radio_cil+ancho_cubo)/2, 0.0, 0.0 );
            musculo_boca(altura,ancho_cubo,alto_cubo);
     glPopMatrix();
     glPushMatrix();
            glTranslatef(0.0,altura,0.0);
            glScalef(radio_cil,alto_cubo/2,radio_cil);
            cilindro->draw(modo_vis, usar_diferido );
     glPopMatrix();
 glPopMatrix();
 }



// -----------------------------------------------------------------------------
// dibuja un sub-objeto parametrizado:
// es la cabeza
void GrafoParam::cabeza( const float ancho)
{

    glPushMatrix();
        glPushMatrix();
            glTranslatef(0.0,ancho/2,0.0);
            glScalef(ancho,ancho,ancho);
            esfera->draw( modo_vis, usar_diferido );
        glPopMatrix();
        glPushMatrix( );
            glScalef(ancho,ancho,ancho);
            cilindro->draw( modo_vis, usar_diferido );
        glPopMatrix();
    glPopMatrix();
}

// -----------------------------------------------------------------------------
// dibuja un sub-objeto parametrizado:
// es un ojo
void GrafoParam::ojo( const float ancho,const float alargar)
{

    glPushMatrix();
        glRotatef(90.0,1.0,0.0,0.0);
            glPushMatrix();
                glTranslatef(0.0,ancho/2+alargar,0.0);
                glScalef(ancho,ancho,ancho);
                esfera_ojos->draw( modo_vis, usar_diferido );
            glPopMatrix();
	    glPushMatrix();
                glTranslatef(0.0,ancho/2+alargar+ancho,0.0);
                glScalef(0.1,0.01,0.1);
                pupila->draw( modo_vis, usar_diferido );
            glPopMatrix();
            glPushMatrix( );
                glScalef(ancho,ancho+alargar,ancho);
                cilindro_ojos->draw( modo_vis, usar_diferido );
            glPopMatrix();
    glPopMatrix();
}
