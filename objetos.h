//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************
#ifndef OBJETOS_H_
#define OBJETOS_H_
#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>
#include "jpg_imagen.hpp"
#include "jpg_jinclude.h"
#include "textura.h"

using namespace std;

const float AXIS_SIZE=5000;

//*************************************************************************
// clase punto
//*************************************************************************

class _puntos3D
{
public:


	_puntos3D();
void 	draw_puntos(float r, float g, float b, int grosor);
vector<_vertex3f> normal_vertices;//hasta num_ver se rellena
vector<_vertex3f> vertices;//solo va a tener puntos no caras
};

//*************************************************************************
// clase triángulo
//*************************************************************************

class _triangulos3D: public _puntos3D
{
public:

	_triangulos3D();// va a tener puntos y caras
void 	draw_aristas(float r, float g, float b, int grosor);
void    draw_solido(float r, float g, float b);
void 	draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2);
_vertex3f productoVectorial(_vertex3f p ,_vertex3f q);
void normalACaras();
void draw_caras_iluminadas(GLfloat ambiente[],GLfloat difusa[], GLfloat especular[]);
void draw_vertices_iluminados(GLfloat ambiente[],GLfloat difusa[], GLfloat especular[]);
void pintarNormalCaras();
void pintarNormalVertices();
void aplicaTextura(GLuint id);
vector<_vertex3f> normal_caras;//hasta num_caras se rellena
vector<_vertex3f> normal_vertices;
vector<_vertex3i> caras;
};


//*************************************************************************
// clase cubo
//*************************************************************************

class _cubo: public _triangulos3D
{
private:
  static const int num_ver=8;
  static const int num_car=12;
public:
  _cubo();
  _cubo(float tam);
};



//*************************************************************************
// clase piramide
//*************************************************************************

class _piramide: public _triangulos3D
{
private:
  static const int  num_ver=4;
  static const int num_car=4;
public:
  _piramide();
  _piramide(float tam, float al);

};

class _piramide_cuadrang: public _triangulos3D
{
private:
  static const int  num_ver=5;
  static const int num_car=6;
public:
  _piramide_cuadrang();

};
class _cilindro: public _triangulos3D
{
private:
  static const int  num_ver=2;
	int n_etapas;
	int v_ini;
	bool texturizando;
public:
  _cilindro();
	_vertex3f RotarEjeY(_vertex3f p, double ang);
	void revolucionar(int v_inicial, int etapas);

};



#endif
