#ifndef TEXTURA_H_
#define TEXTURA_H_
#include "jpg_imagen.hpp"
#include <iostream>
#include <string>
#include <GL/gl.h>
#include <GL/glut.h>
using namespace std;
class _textura{
private:
  GLuint id;
  unsigned char * texels;
  jpg::Imagen * img ;
public:
  _textura(GLuint t_id,string dir_img);
  void crearTextura();
};
#endif
