#ifndef GRUA_H_
#define GRUA_H_

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>
#include "objetos.h"
#include "jpg_imagen.hpp"
#include "jpg_jinclude.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
class _grua: public _triangulos3D
{
private:
  int num_cub;
  int num_tri;
  _piramide tri;
  _piramide_cuadrang cuad;
  _cubo cub;//no me deja usar el constructor por parametros
  _cilindro ci;
public:
  _grua();
  //_grua(int n_cubos);
	void dibujarBase();
  void dibujarPluma(float ang,float mover,float estirar);
  void dibujarCarroPluma(float mover,float estirar);
  void dibujarContraPeso();
  void dibujarGrua(float ang, float mover, float estirar);

  void dibujarBase(int forma,GLfloat ambiente[],GLfloat difusa[], GLfloat especular[],GLuint text);
  void dibujarGrua(float ang, float mover, float estirar,int forma,GLfloat ambiente[],GLfloat difusa[], GLfloat especular[],GLuint text);
  void dibujarPluma(float ang,float mover,float estirar,int forma,GLfloat ambiente[],GLfloat difusa[], GLfloat especular[],GLuint text);
  void dibujarCarroPluma(float mover,float estirar,int forma,GLfloat ambiente[],GLfloat difusa[], GLfloat especular[],GLuint text);
  void dibujarContraPeso(int forma,GLfloat ambiente[],GLfloat difusa[], GLfloat especular[],GLuint text);
};

#endif
