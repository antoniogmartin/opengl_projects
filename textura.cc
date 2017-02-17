#include "textura.h"

_textura::_textura(GLuint t_id,string dir_img){
    img=new jpg::Imagen(dir_img);
    texels = img->leerPixels();
    id=t_id;

    crearTextura();
}
/*_textura::_textura(const _textura & t){
    texels=t.texels;
    id=t.t_id;
    img=t.imag;
}*/
void _textura::crearTextura(){
  glGenTextures(1,&id);
  glBindTexture(GL_TEXTURE_2D,id);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//NIVEL DE DETALLE EN SAMPLING DEBE SER MINIMIZADO
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//NIVEL DE DETALLE EN SAMPLING DEBE SER MINIMIZADO
  glTexImage2D (GL_TEXTURE_2D, 0, 3, img->tamX(), img->tamY(), 0, GL_RGB, GL_UNSIGNED_BYTE, texels);//para definir las imagenes de textura
/* param 1: textura objetivo, param2: nivel de detalle; param3: numero de componentes de color "RGB";param4: ancho de la imagen, param5: altura img, param6: borde
param7:formato de los datos pixel, param8:especifica el tipo del dato pixel, param9:puntero a los datos de la imagen*/

}
