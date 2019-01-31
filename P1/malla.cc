//Autor: Guillermo Sandoval Schmidt

#include "aux.h"
#include "ply_reader.h"
#include "malla.h"

// *****************************************************************************
//
// Clase ObjMallaIndexada
//
// *****************************************************************************

// Visualización en modo inmediato con 'glDrawElements'

void ObjMallaIndexada::draw_ModoInmediato()
{
  // visualizar la malla usando glDrawElements,
  // completar (práctica 1)
 

    // habilitar uso de un array de vértices
    glEnableClientState( GL_VERTEX_ARRAY );
    glEnableClientState(GL_COLOR_ARRAY);
    
    // indicar el formato y la dirección de memoria del array de vértices
    // (son tuplas de 3 valores float, sin espacio entre ellas)
    glVertexPointer( 3, GL_FLOAT, 0, vertices.data() ) ;
    glColorPointer( 3, GL_FLOAT, 0, colores.data() ) ;
    // visualizar, indicando: tipo de primitiva, número de índices,
    
    
    
    // tipo de los índices, y dirección de la tabla de índices
    glDrawElements( GL_TRIANGLES, triangulos.size()*3, GL_UNSIGNED_INT, triangulos.data() );
    // deshabilitar array de vértices
    
    
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
        id_vbo_col = CrearVBO(GL_ARRAY_BUFFER, coloresD.size()*sizeof(float)*3, coloresD.data());
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
    
    // habilitar uso de un array de vértices
    glEnableClientState( GL_VERTEX_ARRAY );
    glEnableClientState(GL_COLOR_ARRAY);
    
    
    // indicar el formato y la dirección de memoria del array de vértices
    // (son tuplas de 3 valores float, sin espacio entre ellas)
    glVertexPointer( 3, GL_FLOAT, 0, vertices.data() ) ;
    glColorPointer( 3, GL_FLOAT, 0, colores.data() ) ;
    // visualizar, indicando: tipo de primitiva, número de índices,
    
    
    
    // tipo de los índices, y dirección de la tabla de índices
    
    glDrawElements( GL_TRIANGLES, triangulosA.size()*3, GL_UNSIGNED_INT, triangulosA.data() );
    
    // indicar el formato y la dirección de memoria del array de vértices
    // (son tuplas de 3 valores float, sin espacio entre ellas
    glColorPointer( 3, GL_FLOAT, 0, coloresA.data() ) ;
    // visualizar, indicando: tipo de primitiva, número de índices,
    
    
    
    // tipo de los índices, y dirección de la tabla de índices
    
    glDrawElements( GL_TRIANGLES, triangulosB.size()*3, GL_UNSIGNED_INT, triangulosB.data() );
    
    // deshabilitar array de vértices
    
    
    glDisableClientState( GL_COLOR_ARRAY );
    glDisableClientState( GL_VERTEX_ARRAY );
}
// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void ObjMallaIndexada::draw(int draw_mode)
{
    // completar .....(práctica 1)
    switch(draw_mode)
    {
        case 0:
            draw_ModoInmediato();
            break;
        case 1:
            draw_ModoDiferido();
            break;
        case 2:
            draw_ModoAjedrez();
            break;
            
    }
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
   // completar .....(práctica 2)
}

// *****************************************************************************
//
// Clase Cubo (práctica 1)
//
// *****************************************************************************

Cubo::Cubo()
{
    
    float tam = 0.5;

   // inicializar la tabla de vértices
   vertices =  {  { -tam, -tam, -tam }, // 0
                  { -tam, -tam, +tam }, // 1
                  { -tam, +tam, -tam }, // 2
                  { -tam, +tam, +tam }, // 3
                  { +tam, -tam, -tam }, // 4
                  { +tam, -tam, +tam }, // 5
                  { +tam, +tam, -tam }, // 6
                  { +tam, +tam, +tam }  // 7
               };
    

   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)

   
    
    for (int i = 0; i<vertices.size(); i++) {
        colores.push_back({0.0,0.0,0.0});
        coloresD.push_back({1.0,0.0,0.0});
        coloresA.push_back({1.0,0.9,0.0});
    }
    
    triangulos = {
        { 1, 5, 3 }, { 3, 5, 7 },
        { 0, 3, 2 }, { 1, 3, 0 },
        { 4, 2, 6 }, { 0, 2, 4 },
        { 5, 4, 7 }, { 7, 4, 6 },
        { 1, 0, 5 }, { 5, 0, 4 },
        { 3, 7, 2 }, { 2, 7, 6 }
    } ;

    
    // Inicializar VBOs a 0:
    id_vbo_ver = 0;
    id_vbo_tri = 0;
    id_vbo_col = 0;
}

// *****************************************************************************
//
// Clase Piramide (práctica 1)
//
// *****************************************************************************

Piramide::Piramide()
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
    
    triangulos = { { 4, 1, 2 }, { 2, 3, 4 },
        { 1, 4, 0 }, { 4, 3, 0 },
        { 0, 3, 2 }, { 2, 1, 0 }
    } ;
    
    for (int i = 0; i<vertices.size(); i++) {
        colores.push_back({0.0,0.0,0.0});
        coloresD.push_back({1.0,0.0,0.0});
        coloresA.push_back({1.0,0.9,0.0});
    }
    
    // Inicializar VBOs a 0:
    id_vbo_ver = 0;
    id_vbo_tri = 0;
    id_vbo_col = 0;
}

// *****************************************************************************
//
// Clase Tetraedro (práctica 1)
//
// *****************************************************************************

Tetraedro::Tetraedro()
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
    
    triangulos = { {0, 2, 3}, {0, 3, 1}, {1, 2, 0}, {3, 2, 1}
    };
    
    for (int i = 0; i<vertices.size(); i++) {
        colores.push_back({0.0,0.0,0.0});
        coloresD.push_back({1.0,0.0,1.0});
        coloresA.push_back({1.0,0.9,0.0});
    }
    
    // Inicializar VBOs a 0:
    id_vbo_ver = 0;
    id_vbo_tri = 0;
    id_vbo_col = 0;
}

// *****************************************************************************
//
// Clase ObjPLY (práctica 2)
//
// *****************************************************************************

ObjPLY::ObjPLY( const std::string & nombre_archivo )
{
   // leer la lista de caras y vértices
   ply::read( nombre_archivo, vertices, triangulos );
    
    /*for (int i = 0; i<vertices.size(); i++) {
        colores.push_back({0.0,0.0,0.0});
        coloresD.push_back({1.0,0.0,0.0});
        coloresA.push_back({1.0,0.9,0.0});
    }
    
    // Inicializar VBOs a 0:
    id_vbo_ver = 0;
    id_vbo_tri = 0;
    id_vbo_col = 0;*/
}


// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************


// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

ObjRevolucion::ObjRevolucion( const std::string & nombre_ply_perfil )
{
   // completar ......(práctica 2)
}
