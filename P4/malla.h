// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: ObjMallaIndexada.h
// -- declaraciones de clase ObjMallaIndexada (mallas indexadas) y derivados
//
// #############################################################################

#ifndef OBJETOS_H_INCLUDED
#define OBJETOS_H_INCLUDED

#include "aux.h"

// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************

struct Material{
  Tupla4f ambiente, difuso, especular, emision;
  GLfloat brillo;
};



class ObjMallaIndexada
{
   public:

   // dibuja el objeto en modo inmediato
   void draw_ModoInmediato(int modo);

   // dibuja el objeto en modo diferido (usando VBOs)
   void draw_ModoDiferido();

    // dibuja el objeto en modo ajedrez
    void draw_ModoAjedrez();

   // función que redibuja el objeto
   // está función llama a 'draw_MI' (modo inmediato)
   // o bien a 'draw_MD' (modo diferido, VBOs)
   void draw(int draw_mode, bool diferido) ;

   protected:

    float PI = 3.14159265359;
    bool textura = false;
    std::vector<Tupla3f> vertices ;   // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
    std::vector<Tupla3f> colPrin ;   // tabla de colores de vértices (una tupla por vértice, con tres floats)
    std::vector<Tupla3i> triangulos ; // una terna de 3 enteros por cada cara o triángulo
    std::vector<Tupla3f> colSec ;   // tabla de colores de vértices (una tupla por vértice, con tres floats)
    // completar: tabla de normales de vértices
    std::vector<Tupla3f> normales_vertices;
    std::vector<Tupla3f> normales_caras;

    std::vector<Tupla2f> coordenadas_textura;

    void rellenarColores(Tupla3f colSecundario);

   void calcular_normales() ; // calcula tabla de normales de vértices (práctica 3)

    // Método que crea los VBOs:
    GLuint CrearVBO( GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid * puntero_ram );

    void inicializarMaterial(Tupla4f a, Tupla4f b, Tupla4f c, Tupla4f d, GLfloat brillo);

    void prepara_textura();

    Material material;

    // VBO de vértices y triángulos:
    GLuint id_vbo_ver = 0;
    GLuint id_vbo_tri = 0;
    GLuint id_vbo_col = 0;

    GLuint textura_id = 0;
} ;

// *****************************************************************************
//
// clases derivadas de ObjMallaIndexada (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************
// Cubo con centro en el origen y lado unidad
// (tiene 9 vertices y 6 caras)

class Cubo : public ObjMallaIndexada
{
   public:
   Cubo(Tupla3f colSecundario) ;

} ;

class Cuadro : public ObjMallaIndexada
{
   public:
   Cuadro() ;

} ;

// *****************************************************************************
// Tetraedro con centro en el origen y lado unidad
// (tiene 4 vertices y 4 caras)

class Tetraedro : public ObjMallaIndexada
{
public:
    Tetraedro(Tupla3f colSecundario) ;

} ;

// *****************************************************************************
// Tetraedro con centro en el origen y lado unidad
// (tiene 5 vertices y 5 caras)

class Piramide : public ObjMallaIndexada
{
public:
    Piramide(Tupla3f colSecundario) ;

} ;

// *****************************************************************************
// objeto leído de un archivo PLY

class ObjPLY : public ObjMallaIndexada
{
   public:
      ObjPLY( const std::string & nombre_archivo, Tupla3f colSecundario );

} ;

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

class ObjRevolucion : public ObjMallaIndexada
{
    protected:
        void crearMalla(const std::vector<Tupla3f> & original, int numero_segmentos);

        void crearTapas(const std::vector<Tupla3f> & original, int numero_segmentos,bool tapa_superior, bool tapa_inferior);

    public:
        ObjRevolucion(){};
        ObjRevolucion( const std::string & perfil, int numero_segmentos, bool tapa_superior, bool tapa_inferior, Tupla3f colSecundario );
        ObjRevolucion( const std::vector<Tupla3f> & perfil, int numero_segmentos, bool tapa_superior, bool tapa_inferior, Tupla3f colSecundario );



} ;

class Cilindro : public ObjRevolucion {
    public:

    Cilindro( const int num_vert_perfil, const int num_instancias_perf ,Tupla3f colSecundario);
};



class Cono : public ObjRevolucion {
public:

    Cono( const int num_vert_perfil, const int num_instancias_perf,Tupla3f colSecundario );
};

class Esfera : public ObjRevolucion {
    public:

    Esfera( const int num_vert_perfil, const int num_instancias_perf,Tupla3f colSecundario );
};

#endif
