#include "aux.h"
#include "ply_reader.h"
#include "malla.h"

// *****************************************************************************
//
// Clase ObjMallaIndexada
//
// *****************************************************************************

// Visualización en modo inmediato con 'glDrawElements'

void ObjMallaIndexada::rellenarColores(Tupla3f colSecundario){
    for(int i=0;i<vertices.size();i++){
        colPrin.push_back({0.0,0.0,0.0});
        colSec.push_back(colSecundario);
    }
}

void ObjMallaIndexada::draw_ModoInmediato(int modo)
{
  // visualizar la malla usando glDrawElements,
  // completar (práctica 1)


    // habilitar uso de un array de vértices
    glEnableClientState( GL_VERTEX_ARRAY );
    glEnableClientState(GL_COLOR_ARRAY);

    if(modo == 3) draw_ModoAjedrez();

    else{
    // indicar el formato y la dirección de memoria del array de vértices
    // (son tuplas de 3 valores float, sin espacio entre ellas)
    glVertexPointer( 3, GL_FLOAT, 0, vertices.data() ) ;
    glColorPointer( 3, GL_FLOAT, 0, colPrin.data() ) ;
    // visualizar, indicando: tipo de primitiva, número de índices,

    // tipo de los índices, y dirección de la tabla de índices
    glDrawElements( GL_TRIANGLES, triangulos.size()*3, GL_UNSIGNED_INT, triangulos.data() );
    // deshabilitar array de vértices

    }

    glDisableClientState( GL_COLOR_ARRAY );
    glDisableClientState( GL_VERTEX_ARRAY );

  // ...
}
// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

void ObjMallaIndexada::draw_ModoDiferido()
{
    // (la primera vez, se deben crear los VBOs y guardar sus identificadores en el objeto)
    // completar (práctica 1)
    // .....

    // Comprobar que existe id_vbo_ver, y si no, crearlo:
    if (id_vbo_ver == 0) {
        id_vbo_ver = CrearVBO(GL_ARRAY_BUFFER, vertices.size()*sizeof(float)*3, vertices.data());
    }

    // Comprobar que existe id_vbo_tri, y si no, crearlo:
    if (id_vbo_tri == 0) {
        id_vbo_tri = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, triangulos.size()*sizeof(float)*3, triangulos.data());
    }

    // Comprobar que existe id_vbo_tri, y si no, crearlo:
    if (id_vbo_col == 0) {
        id_vbo_col = CrearVBO(GL_ARRAY_BUFFER, colSec.size()*sizeof(float)*3, colSec.data());
    }


    // Dibujar:
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState( GL_VERTEX_ARRAY );

    // Especificar localización y formato de la tabla de vértices, habilitar
    glBindBuffer( GL_ARRAY_BUFFER, id_vbo_ver ); // activar VBO de vértices
    glVertexPointer( 3, GL_FLOAT, 0, 0 ); // especifica formato y offset (=0)
    glBindBuffer( GL_ARRAY_BUFFER, 0 ); // desactivar VBO de vértices.

    // Especificar localización y formato de la tabla de vértices, habilitar
    glBindBuffer( GL_ARRAY_BUFFER, id_vbo_col ); // activar VBO de vértices
    glColorPointer( 3, GL_FLOAT, 0, 0 ); // especifica formato y offset (=0)
    glBindBuffer( GL_ARRAY_BUFFER, 0 ); // desactivar VBO de vértices.


    // Visualizar triángulos con glDrawElements (puntero a tabla == 0)
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri ); // activar VBO
    glDrawElements( GL_TRIANGLES, 3*triangulos.size(), GL_UNSIGNED_INT, 0 ) ;
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 ); // desactivar VBO de triángulos

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);


}

// -----------------------------------------------------------------------------
// Visualización en modo ajedrez con 'glDrawElements'

void ObjMallaIndexada::draw_ModoAjedrez()
{

    std::vector<Tupla3i> triangulosA ;
    std::vector<Tupla3i> triangulosB ;

    for (int i = 0; i<triangulos.size(); i+=2) {
        triangulosA.push_back(triangulos[i]);
        triangulosB.push_back(triangulos[i+1]);
    }


    // indicar el formato y la dirección de memoria del array de vértices
    // (son tuplas de 3 valores float, sin espacio entre ellas)
    glVertexPointer( 3, GL_FLOAT, 0, vertices.data() ) ;
    glColorPointer( 3, GL_FLOAT, 0, colPrin.data() ) ;
    // visualizar, indicando: tipo de primitiva, número de índices,

    // tipo de los índices, y dirección de la tabla de índices

    glDrawElements( GL_TRIANGLES, triangulosA.size()*3, GL_UNSIGNED_INT, triangulosA.data() );



    // indicar el formato y la dirección de memoria del array de vértices
    // (son tuplas de 3 valores float, sin espacio entre ellas
    glColorPointer( 3, GL_FLOAT, 0, colSec.data() );

    glDrawElements( GL_TRIANGLES, triangulosB.size()*3, GL_UNSIGNED_INT, triangulosB.data() );
}
// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void ObjMallaIndexada::draw(int draw_mode, bool diferido)
{
    // completar .....(práctica 1)
    if(diferido) draw_ModoDiferido();

    else draw_ModoInmediato(draw_mode);
}
// -----------------------------------------------------------------------------
// Recalcula la tabla de normales de vértices (el contenido anterior se pierde)

// -----------------------------------------------------------------------------
// Método para crear VBOs:

GLuint ObjMallaIndexada::CrearVBO( GLuint tipo_vbo, GLuint tamanio_bytes,
                                  GLvoid * puntero_ram )
{
    GLuint id_vbo; // resultado: identificador de VBO
    glGenBuffers( 1, & id_vbo ); // crear nuevo VBO, obtener id (nunca 0)
    glBindBuffer( tipo_vbo, id_vbo ); // activar el VBO usando su identificador

    // esta instrucción hace la transferencia de datos desde RAM hacia GPU
    glBufferData( tipo_vbo, tamanio_bytes, puntero_ram, GL_STATIC_DRAW );

    glBindBuffer( tipo_vbo, 0 );  // desactivación del VBO (activar 0)
    return id_vbo ;               // devolver el id resultado
}

void ObjMallaIndexada::calcular_normales()
{
   // completar .....(práctica 3)
}

// *****************************************************************************
//
// Clase Cubo (práctica 1)
//
// *****************************************************************************

Cubo::Cubo(Tupla3f colSecundario)
{

    float tam = 0.5;

   // inicializar la tabla de vértices
   vertices =  {  { -tam, 0, -tam }, // 0
                  { -tam, 0, +tam }, // 1
                  { -tam, tam*2, -tam }, // 2
                  { -tam, tam*2, +tam }, // 3
                  { +tam, 0, -tam }, // 4
                  { +tam, 0, +tam }, // 5
                  { +tam, tam*2, -tam }, // 6
                  { +tam, tam*2, +tam }  // 7
               };


   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)


    rellenarColores(colSecundario);

    triangulos = {
        { 1, 5, 3 }, { 3, 5, 7 },
        { 0, 3, 2 }, { 1, 3, 0 },
        { 4, 2, 6 }, { 0, 2, 4 },
        { 5, 4, 7 }, { 7, 4, 6 },
        { 1, 0, 5 }, { 5, 0, 4 },
        { 3, 7, 2 }, { 2, 7, 6 }
    };


}

// *****************************************************************************
//
// Clase Piramide (práctica 1)
//
// *****************************************************************************

Piramide::Piramide( Tupla3f colSecundario)
{
    float tam = 0.5;

    // inicializar la tabla de vértices
    vertices =  {   { 0, 2*sqrt(4*tam*tam - tam*tam)/3, 0 }, // 0 pico
                    { -tam, -sqrt(4*tam*tam - tam*tam)/3, +tam }, // 1 base
                    { -tam, -sqrt(4*tam*tam - tam*tam)/3, -tam }, // 2 base
                    { +tam, -sqrt(4*tam*tam - tam*tam)/3, -tam }, // 3 base
                    { +tam, -sqrt(4*tam*tam - tam*tam)/3, +tam }, // 4 base
    };

    // inicializar la tabla de caras o triángulos:
    // (es importante en cada cara ordenar los vértices en sentido contrario
    //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)

    triangulos = {
        { 4, 1, 2 }, { 2, 3, 4 },
        { 1, 4, 0 }, { 4, 3, 0 },
        { 0, 3, 2 }, { 2, 1, 0 }
    } ;

     rellenarColores(colSecundario);

}

// *****************************************************************************
//
// Clase Tetraedro (práctica 1)
//
// *****************************************************************************

Tetraedro::Tetraedro( Tupla3f colSecundario)
{
    float tam = 1;

    // inicializar la tabla de vértices


    vertices = {
        { 0.0, 2*sqrt(tam*tam - (tam/2 * tam/2))/3 , 0.0 }, //0 pico
        { -tam/2, -sqrt(tam*tam - (tam/2 * tam/2))/3, sqrt(tam*tam - (tam/2 * tam/2))/3 }, //1 base
        { tam/2, -sqrt(tam*tam - (tam/2 * tam/2))/3, sqrt(tam*tam - (tam/2 * tam/2))/3 }, //2 base
        { 0.0, -sqrt(tam*tam - (tam/2 * tam/2))/3, -2*sqrt(tam*tam - (tam/2 * tam/2))/3} //3 base

    };



    // inicializar la tabla de caras o triángulos:
    // (es importante en cada cara ordenar los vértices en sentido contrario
    //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)

    triangulos = {
        {0, 2, 3}, {0, 3, 1},
        {1, 2, 0}, {3, 2, 1}
    };

     rellenarColores(colSecundario);

}

// *****************************************************************************
//
// Clase ObjPLY (práctica 2)
//
// *****************************************************************************

ObjPLY::ObjPLY( const std::string & nombre_archivo, Tupla3f colSecundario )
{
   // leer la lista de caras y vértices
   ply::read( nombre_archivo, vertices, triangulos );

     rellenarColores(colSecundario);

}


// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************


// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)
void ObjRevolucion::crearMalla(const std::vector<Tupla3f> & original, int numero_segmentos){
    Tupla3f aux = {0.0,0.0,0.0};

    for(int i=0; i<numero_segmentos; i++)
        for (int j=0; j<original.size(); j++) {

            aux(0) = original[j](0)*cos((2*i* PI)/numero_segmentos);
            aux(1) = original[j](1);
            aux(2) = original[j](0)*sin((2*i* PI)/numero_segmentos);

            vertices.push_back(aux);

        }


    for(int i=0; i<numero_segmentos; i++)
        for (int j=0; j<original.size()-1; j++){

            float a = original.size() * i + j;
            float b = original.size() * ((i+1)%numero_segmentos) + j;

            triangulos.push_back({a,b+1,b});
            triangulos.push_back({a,a+1,b+1});
        }
}



void ObjRevolucion::crearTapas(const std::vector<Tupla3f> & original, int numero_segmentos,bool tapa_superior, bool tapa_inferior){
    vertices.push_back({0.0,original.front()(1),0.0});
    vertices.push_back({0.0,original.back()(1),0.0});

    if(tapa_inferior)
        for(int i=0; i<numero_segmentos; i++){
            int a = original.size() * i;
            triangulos.push_back({numero_segmentos*original.size(),a,(a+original.size())%(numero_segmentos*original.size())});
        }

    if(tapa_superior)
        for(int i=0; i<numero_segmentos; i++){
            int a = original.size()*(i+1)-1;
            triangulos.push_back({numero_segmentos*original.size()+1,(a+original.size())%(numero_segmentos*original.size()),a});
        }
}



ObjRevolucion::ObjRevolucion( const std::string & nombre_ply_perfil, int numero_segmentos, bool tapa_superior, bool tapa_inferior, Tupla3f colSecundario )
{
    std::vector<Tupla3f> original ;

    ply::read_vertices(nombre_ply_perfil, original);

    crearMalla(original,numero_segmentos);
    crearTapas(original,numero_segmentos,tapa_superior,tapa_inferior);

    rellenarColores(colSecundario);

}

ObjRevolucion::ObjRevolucion( const std::vector<Tupla3f> & perfil, int numero_segmentos, bool tapa_superior, bool tapa_inferior, Tupla3f colSecundario )
{
    crearMalla(perfil,numero_segmentos);
    crearTapas(perfil,numero_segmentos,tapa_superior,tapa_inferior);

    rellenarColores(colSecundario);

}

Cilindro::Cilindro(const int num_vert_perfil, const int num_instancias_perf, Tupla3f colSecundario)
{
    if(num_vert_perfil < 2) std::cout<<"El número mínimo de puntos de un cilindro es 2"<<std::endl;

    else{
        std::vector<Tupla3f> perfil;

        float radio = 0.5;

        float value = 2*radio/(num_vert_perfil-1)*1.0;

        for(float i=0;i<=2*radio;i+=value){
            perfil.push_back({radio,i,0.0});
        }

        crearMalla(perfil,num_instancias_perf);
        crearTapas(perfil,num_instancias_perf,true,true);
        rellenarColores(colSecundario);
    }

}



Cono::Cono(const int num_vert_perfil, const int num_instancias_perf, Tupla3f colSecundario)
{

    if(num_vert_perfil < 2) std::cout<<"El número mínimo de puntos de un cono es 2"<<std::endl;

    else{
        std::vector<Tupla3f> perfil;

        float radio = 0.5;
        float altura = sqrt(0.75);
        float dist_puntos = altura / (num_vert_perfil * 1.0);

        perfil.push_back({radio, -altura/3, 0.0});

        for(int i = 0; i < num_vert_perfil - 1; ++i){
            float y = perfil[i][1] + dist_puntos;
            float x = -y*radio/ altura + radio*2/3;
            perfil.push_back({x, y, 0.0});
        }

        perfil.push_back({0.0, 2*altura/3, 0.0});

        crearMalla(perfil,num_instancias_perf);

        crearTapas(perfil,num_instancias_perf,false,true);
        rellenarColores(colSecundario);

    }


}

Esfera::Esfera(const int num_vert_perfil, const int num_instancias_perf, Tupla3f colSecundario)
{

    if(num_vert_perfil < 3) std::cout<<"El número mínimo de puntos de un esfera es 3"<<std::endl;

    else{
        std::vector<Tupla3f> perfil;


        float value = 180.0/(num_vert_perfil-1)*1.0;

        perfil.push_back({0.0, 0.0, 0.0});

        for(float i = -90.0+value; i <= 90.0; i+=value){
            float x = cos(i*PI/180.0)/2;
            float y = (sin(i*PI/180.0)+1)/2;

            perfil.push_back({x, y, 0.0});
        }

        perfil.push_back({0.0, 1, 0.0});

        crearMalla(perfil,num_instancias_perf);

        crearTapas(perfil,num_instancias_perf,false,false);
        rellenarColores(colSecundario);

    }


}
