//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include "objetos.h"
#include <cmath>

//*************************************************************************
// _puntos3D
//*************************************************************************

_puntos3D::_puntos3D()
{

}

//*************************************************************************
// dibujar puntos
//*************************************************************************

void _puntos3D::draw_puntos(float r, float g, float b, int grosor)
{
  int num_ver=vertices.size();
  _vertex3f nodo;
  glPointSize(grosor);
  glColor3f(r,g,b);
  glBegin(GL_POINTS);

    for(int i=0;i<num_ver;i++){
        nodo=vertices.at(i);//asigno el vertex3f de la posicion iesima del vector y pinto sus coordenadas
        glVertex3f(nodo.x,nodo.y,nodo.z);
        //cout<<"ind_ver: "<<i<<endl;
        //cout<<" x: "<<nodo.x<<" y: "<<nodo.y<<" z: "<<nodo.z<<endl;

      }
  glEnd();
  }




//*************************************************************************
// _triangulos3D
//*************************************************************************

_triangulos3D::_triangulos3D()
{
}

void _triangulos3D::pintarNormalCaras(){

    _vertex3f promedio,res;
    normalACaras();
    glLineWidth(3.0);
    glColor3f(0.22,0.70,0.22);
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glBegin(GL_LINES);

      for (int i=0;i<caras.size();i++){
                      promedio.x=vertices.at(caras.at(i).x).x+vertices.at(caras.at(i).y).x+vertices.at(caras.at(i).z).x;
                      promedio.y=vertices.at(caras.at(i).x).y+vertices.at(caras.at(i).y).y+vertices.at(caras.at(i).z).y;
                      promedio.z=vertices.at(caras.at(i).x).z+vertices.at(caras.at(i).y).z+vertices.at(caras.at(i).z).z;
                      promedio.x=promedio.x/3.0;
                      promedio.y=promedio.y/3.0;
                      promedio.z=promedio.z/3.0;//baricentro comprobado

                      res.x=promedio.x+normal_caras.at(i).x;
                      res.y=promedio.y+normal_caras.at(i).y;
                      res.z=promedio.z+normal_caras.at(i).z;
                      glVertex3f(promedio.x,promedio.y,promedio.z);
                      glVertex3f(res.x,res.y,res.z);


      }
    glEnd();
}


    void _triangulos3D::normalACaras(){
      _vertex3f v1,v2,v3,p,q;
      float divisor=0.0;
      for(int i = 0; i < caras.size(); i++){
        v1 =vertices.at(caras.at(i).x);
        v2 =vertices.at(caras.at(i).y);
        v3 =vertices.at(caras.at(i).z);
        _vertex3f p(v2.x-v1.x,v2.y-v1.y,v2.z-v1.z);
        _vertex3f q(v3.x-v1.x,v3.y-v1.y,v3.z-v1.z);
        _vertex3f pVectorial = productoVectorial(p,q);//llamada a productoVectorial
        divisor = sqrt(pVectorial.x*pVectorial.x + pVectorial.y*pVectorial.y + pVectorial.z*pVectorial.z);
        _vertex3f unitario (pVectorial.x/divisor,pVectorial.y/divisor,pVectorial.z/divisor);
        normal_caras.push_back(unitario);//obtiene la normal a cada cara
      }




}
void _triangulos3D::draw_vertices_iluminados(GLfloat ambiente[],GLfloat difusa[], GLfloat especular[]){
 //falta añadir glTexCoord;
  GLfloat brillo = 0.25 * 128.0;
  normalACaras();
  normal_vertices.resize(vertices.size());
  float divisor=0.0;
  _vertex3f unitario;
  for (int i = 0; i < caras.size(); i++) {
        normal_vertices.at(caras.at(i).x)+=normal_caras.at(i);//buscamos el vertice x de la cara en el vector de caras
        normal_vertices.at(caras.at(i).y)+=normal_caras.at(i);
        normal_vertices.at(caras.at(i).z)+=normal_caras.at(i);
  }
  for(int i=0;i<normal_vertices.size();i++){
    divisor = sqrt(normal_vertices.at(i).x*normal_vertices.at(i).x + normal_vertices.at(i).y*normal_vertices.at(i).y + normal_vertices.at(i).z*normal_vertices.at(i).z);
    normal_vertices.at(i).x=normal_vertices.at(i).x/divisor;
    normal_vertices.at(i).y=normal_vertices.at(i).y/divisor;
    normal_vertices.at(i).z=normal_vertices.at(i).z/divisor;
  }//recorrer de nuevo
      _vertex3f ind_ver;
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      glMaterialfv(GL_FRONT, GL_AMBIENT, ambiente);
      glMaterialfv(GL_FRONT, GL_DIFFUSE, difusa);
      glMaterialfv(GL_FRONT, GL_SPECULAR, especular);
      glMaterialf(GL_FRONT, GL_SHININESS, brillo);

       glBegin(GL_TRIANGLES);
         for(int i=0;i<caras.size();i++){
               ind_ver=vertices.at(caras.at(i).x);
               glNormal3f(normal_vertices.at(caras.at(i).x).x,normal_vertices.at(caras.at(i).x).y,normal_vertices.at(caras.at(i).x).z);
                glVertex3f(ind_ver.x,ind_ver.y,ind_ver.z);
               ind_ver=vertices.at(caras.at(i).y);
               glNormal3f(normal_vertices.at(caras.at(i).y).x,normal_vertices.at(caras.at(i).y).y,normal_vertices.at(caras.at(i).y).z);
               glVertex3f(ind_ver.x,ind_ver.y,ind_ver.z);
               ind_ver=vertices.at(caras.at(i).z);
               glNormal3f(normal_vertices.at(caras.at(i).z).x,normal_vertices.at(caras.at(i).z).y,normal_vertices.at(caras.at(i).z).z);
              glVertex3f(ind_ver.x,ind_ver.y,ind_ver.z);//falla al pintar glNormal3f

         }
         glEnd();

}
void _triangulos3D::pintarNormalVertices() {
  _vertex3f v,res;
  normalACaras();
  glLineWidth(3.0);
  glColor3f(0.0,0.30,0.12);
  glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
  glBegin(GL_LINES);
    for (int i=0;i<vertices.size();i++){
          v= vertices.at(i);
          res.x=v.x+normal_vertices.at(i).x;
          res.y=v.y+normal_vertices.at(i).y;
          res.z=v.z+normal_vertices.at(i).z;
          glVertex3f(v.x,v.y,v.z);
          glVertex3f(res.x,res.y,res.z);
    }
  glEnd();
}
_vertex3f _triangulos3D::productoVectorial(_vertex3f p ,_vertex3f q){
    _vertex3f res (p.y*q.z-p.z*q.y,-(p.x*q.z-p.z*q.x),p.x*q.y-p.y*q.x);
    return res;
}

//*************************************************************************
// dibujar en caras iluminadas
//*************************************************************************
void _triangulos3D::draw_caras_iluminadas(GLfloat ambiente[],GLfloat difusa[], GLfloat especular[])
{
    GLfloat brillo = 0.25 * 128.0;

     _vertex3f ind_ver;
     normalACaras();
     glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
     glMaterialfv(GL_FRONT, GL_AMBIENT, ambiente);
     glMaterialfv(GL_FRONT, GL_DIFFUSE, difusa);
     glMaterialfv(GL_FRONT, GL_SPECULAR, especular);
     glMaterialf(GL_FRONT, GL_SHININESS, brillo);
     glBegin(GL_TRIANGLES);
       for(int i=0;i<caras.size();i++){
            glNormal3f(normal_caras[i].x,normal_caras[i].y,normal_caras[i].z);
             ind_ver=vertices.at(caras.at(i).x);
             glVertex3f(ind_ver.x,ind_ver.y,ind_ver.z);
             ind_ver=vertices.at(caras.at(i).y);
             glVertex3f(ind_ver.x,ind_ver.y,ind_ver.z);
             ind_ver=vertices.at(caras.at(i).z);
           glVertex3f(ind_ver.x,ind_ver.y,ind_ver.z);

       }
       glEnd();


}
//*************************************************************************
//  TEXTURAS
//*************************************************************************
void _triangulos3D::aplicaTextura(GLuint id){


  GLfloat ambiente[] = {5.6, 5.6, 5.6, 1.0};
  GLfloat difusa[] = {6.5, 6.5,6.5, 0.5};
  GLfloat especular[] = {0.5, 0.5, 0.5, 0.5};
  GLfloat brillo = 0.25 * 100.0;

    glMaterialfv(GL_FRONT, GL_AMBIENT, ambiente);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, difusa);
    glMaterialfv(GL_FRONT, GL_SPECULAR, especular);
    glMaterialf(GL_FRONT, GL_SHININESS, brillo);
  glMaterialf(GL_FRONT, GL_SHININESS, brillo);

  glEnable(GL_TEXTURE_2D);
  glEnable(GL_TEXTURE_GEN_S);//PARA automáticamente generar coordenada de textura S ("x")
  glEnable(GL_TEXTURE_GEN_T);//PARA automáticamente generar coordenada de textura T ("y")
  glBindTexture(GL_TEXTURE_2D,id);
	GLfloat XPlane[]= {1.0f, 0.0f, 0.0f, 0.0f};
	GLfloat YPlane[] = {0.0f, 1.0f, 0.0f, 0.0f};

	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);//2do parametro: obligatorio el que está, 3er parametro: de un unico valor de generación de textura, GL_OBJECT_LINEAR es un GLint
	glTexGenfv(GL_S, GL_OBJECT_PLANE, XPlane);// segundo parametro especifica la funcion de generacion de textura que se aplica,el puntero a glfloat para obtener parametros planoX
	glTexGenfv(GL_T, GL_OBJECT_PLANE, YPlane);
	(*this).draw_solido(0.5,0.5,0.5);
  glDisable(GL_TEXTURE_2D);
  glDisable(GL_TEXTURE_GEN_S);//PARA automáticamente generar coordenada de textura S ("x")
  glDisable(GL_TEXTURE_GEN_T);//PARA automáticamente generar coordenada de textura T ("y")

}


//*************************************************************************
// dibujar en modo arista
//*************************************************************************
void _triangulos3D::draw_aristas(float r, float g, float b, int grosor)
{
  _vertex3f ind_ver;
  int num_car=caras.size();
  glLineWidth(grosor);
  glColor3f(r,g,b);
  glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

  glBegin(GL_TRIANGLES);
    for(int i=0;i<num_car;i++){
    //  cout<<"cara de: "<<i<<endl;
    //  cout<<caras.at(i).x<<" "<<caras.at(i).y<<" "<<caras.at(i).z<<endl;
      for(int j=0;j<3;j++){
        if(j==0){
          ind_ver=vertices.at(caras.at(i).x);
        }else {
          if(j==1)
                ind_ver=vertices.at(caras.at(i).y);

            else {
                  if(j==2)
                  ind_ver=vertices.at(caras.at(i).z);
                }
          }

        glVertex3f(ind_ver.x,ind_ver.y,ind_ver.z);

      //  cout<<" x: "<<ind_ver.x<<" y: "<<ind_ver.y<<" z: "<<ind_ver.z<<endl;

      }

    }
  glEnd();
}

//*************************************************************************
// dibujar en modo sólido
//*************************************************************************

void _triangulos3D::draw_solido(float r, float g, float b)
{
  _vertex3f ind_ver;
  int num_car=caras.size();
  glColor3f(r,g,b);
  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
  //glEnable(GL_CULL_FACE);
  glBegin(GL_TRIANGLES);
    for(int i=0;i<num_car;i++){
      for(int j=0;j<3;j++){
        if(j==0)
          ind_ver=vertices.at(caras.at(i).x);
          else if(j==1)
                ind_ver=vertices.at(caras.at(i).y);
            else if(j==2)
                  ind_ver=vertices.at(caras.at(i).z);

        glVertex3f(ind_ver.x,ind_ver.y,ind_ver.z);

      }

    }
  glEnd();
}

//*************************************************************************
// dibujar en modo sólido con apariencia de ajedrez
//*************************************************************************

void _triangulos3D::draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2)
{
  _vertex3f ind_ver;
  int num_car=caras.size();
  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
  glBegin(GL_TRIANGLES);
    for(int i=0;i<num_car;i++){
        if(i%2==0)
          glColor3f(r1,g1,b1);
        else
          glColor3f(r2,g2,b2);
      for(int j=0;j<3;j++){
        if(j==0)
          ind_ver=vertices.at(caras.at(i).x);
          else if(j==1)
                ind_ver=vertices.at(caras.at(i).y);
            else if(j==2)
                  ind_ver=vertices.at(caras.at(i).z);

        glVertex3f(ind_ver.x,ind_ver.y,ind_ver.z);


      }

    }
  glEnd();
}



//*************************************************************************
// clase cubo
//*************************************************************************
_cubo::_cubo(){
  _vertex3f nodo;
  //v0
    nodo.x=0.0;
    nodo.y=0.0;
    nodo.z=0.0;
    vertices.push_back(nodo);
    //v1
    nodo.x=1.0;
    nodo.y=0.0;
    nodo.z=0.0;
    vertices.push_back(nodo);
    //v2
    nodo.x=1.0;
    nodo.y=1.0;
    nodo.z=0.0;
    vertices.push_back(nodo);
    //v3
    nodo.x=0.0;
    nodo.y=1.0;
    nodo.z=0.0;
    vertices.push_back(nodo);
    //v4
    nodo.x=0.0;
    nodo.y=0.0;
    nodo.z=1.0;
    vertices.push_back(nodo);
    //v5
    nodo.x=1.0;
    nodo.y=0.0;
    nodo.z=1.0;
    vertices.push_back(nodo);
   //v6
    nodo.x=1.0;
    nodo.y=1.0;
    nodo.z=1.0;
    vertices.push_back(nodo);
    //v7
    nodo.x=0.0;
    nodo.y=1.0;
    nodo.z=1.0;
    vertices.push_back(nodo);


    _vertex3i face;
    //cara 0 Fondo horario
      face.x=1;
      face.y=0;
      face.z=3;
      caras.push_back(face);
      //cara 1 fondo horario
      face.x=1;
      face.y=3;
      face.z=2;
      caras.push_back(face);
      //cara2 frontal antihorario
      face.x=4;
      face.y=5;
      face.z=6;
      caras.push_back(face);
      //cara3 frontal antihorario
      face.x=4;
      face.y=6;
      face.z=7;
      caras.push_back(face);
      //cara4 lat. izq horario
      face.x=0;
      face.y=4;
      face.z=7;
      caras.push_back(face);
      //caras5 lat. izq horario
      face.x=0;
      face.y=7;
      face.z=3;
      caras.push_back(face);
      //caras6 lat.dcho antihorario
      face.x=1;
      face.y=2;
      face.z=5;
      caras.push_back(face);
      //caras7 lat. dcho antihorario
      face.x=5;
      face.y=2;
      face.z=6;
      caras.push_back(face);
      //caras8 sup antihorario
      face.x=7;
      face.y=6;
      face.z=2;
      caras.push_back(face);
      //caras9 sup antihorario
      face.x=7;
      face.y=2;
      face.z=3;
      caras.push_back(face);
      //caras10 antihorario
      face.x=0;
      face.y=1;
      face.z=5;
      caras.push_back(face);
      //caras11 inf antihorario
      face.x=4;
      face.y=0;
      face.z=5;
      caras.push_back(face);
}
_cubo::_cubo(float tam)
{

  _vertex3f nodo;
  //v0
    nodo.x=-tam/2.0;
    nodo.y=-tam/2.0;
    nodo.z=-tam/2.0;
    vertices.push_back(nodo);
    //v1
    nodo.x=tam/2.0;
    nodo.y=-tam/2.0;
    nodo.z=-tam/2.0;
    vertices.push_back(nodo);
    //v2
    nodo.x=tam/2.0;
    nodo.y=tam/2.0;
    nodo.z=-tam/2.0;
    vertices.push_back(nodo);
    //v3
    nodo.x=-tam/2.0;
    nodo.y=tam/2.0;
    nodo.z=-tam/2.0;
    vertices.push_back(nodo);
    //v4
    nodo.x=-tam/2.0;
    nodo.y=-tam/2.0;
    nodo.z=tam/2.0;
    vertices.push_back(nodo);
    //v5
    nodo.x=tam/2.0;
    nodo.y=-tam/2.0;
    nodo.z=tam/2.0;
    vertices.push_back(nodo);
   //v6
    nodo.x=tam/2.0;
    nodo.y=tam/2.0;
    nodo.z=tam/2.0;
    vertices.push_back(nodo);
    //v7
    nodo.x=-tam/2.0;
    nodo.y=tam/2.0;
    nodo.z=tam/2.0;
    vertices.push_back(nodo);


    _vertex3i face;
    //cara 0 Fondo horario
      face.x=1;
      face.y=0;
      face.z=3;
      caras.push_back(face);
      //cara 1 fondo horario
      face.x=1;
      face.y=3;
      face.z=2;
      caras.push_back(face);
      //cara2 frontal antihorario
      face.x=4;
      face.y=5;
      face.z=6;
      caras.push_back(face);
      //cara3 frontal antihorario
      face.x=4;
      face.y=6;
      face.z=7;
      caras.push_back(face);
      //cara4 lat. izq horario
      face.x=0;
      face.y=4;
      face.z=7;
      caras.push_back(face);
      //caras5 lat. izq horario
      face.x=0;
      face.y=7;
      face.z=3;
      caras.push_back(face);
      //caras6 lat.dcho antihorario
      face.x=1;
      face.y=2;
      face.z=5;
      caras.push_back(face);
      //caras7 lat. dcho antihorario
      face.x=5;
      face.y=2;
      face.z=6;
      caras.push_back(face);
      //caras8 sup antihorario
      face.x=7;
      face.y=6;
      face.z=2;
      caras.push_back(face);
      //caras9 sup antihorario
      face.x=7;
      face.y=2;
      face.z=3;
      caras.push_back(face);
      //caras10 antihorario
      face.x=0;
      face.y=1;
      face.z=5;
      caras.push_back(face);
      //caras11 inf antihorario
      face.x=4;
      face.y=0;
      face.z=5;
      caras.push_back(face);
}


//*************************************************************************
// clase piramide
//*************************************************************************
_piramide::_piramide(){
  _vertex3f nodo;
  //v0

  nodo.x=0.0;
  nodo.y=0.0;
  nodo.z=0.0;
  vertices.push_back(nodo);

  //v1
  nodo.x=1.0;//x
  nodo.y=0.0;//y
  nodo.z=0.0;//z
  vertices.push_back(nodo);
  //v2
  nodo.x=0.5;
  nodo.y=1.0;
  nodo.z=0.5;
  vertices.push_back(nodo);
  //v3
  nodo.x=0.5;
  nodo.y=0.0;
  nodo.z=0.5;
  vertices.push_back(nodo);

  //caras------------------------
    _vertex3i face;
    //cara 0 - antihorario fondo
    face.x=0;
    face.y=1;
    face.z=3;
    caras.push_back(face);
    //cara1 horario dcha
    face.x=1;
    face.y=2;
    face.z=3;
    caras.push_back(face);

    //cara2 frente horario
    face.x=0;
    face.y=2;
    face.z=1;
    caras.push_back(face);
    //cara3
    face.x=0;
    face.y=3;
    face.z=2;
    caras.push_back(face);
}
_piramide::_piramide(float tam, float al)
{
  _vertex3f nodo;
  //v0

  nodo.x=0.0;
  nodo.y=0.0;
  nodo.z=0.0;
  vertices.push_back(nodo);

  //v1
  nodo.x=tam;//x
  nodo.y=0.0;//y
  nodo.z=0.0;//z
  vertices.push_back(nodo);
  //v2
  nodo.x=tam/2.0;
  nodo.y=al;
  nodo.z=tam/2.0;
  vertices.push_back(nodo);
  //v3
  nodo.x=tam/2.0;
  nodo.y=0.0;
  nodo.z=tam;
  vertices.push_back(nodo);

//caras------------------------
    _vertex3i face;
    //cara 0 - antihorario fondo
    face.x=0;
    face.y=1;
    face.z=3;
    caras.push_back(face);
    //cara1 horario dcha
    face.x=1;
    face.y=2;
    face.z=3;
    caras.push_back(face);

    //cara2 frente horario
    face.x=0;
    face.y=2;
    face.z=1;
    caras.push_back(face);
    //cara3
    face.x=0;
    face.y=3;
    face.z=2;
    caras.push_back(face);
}
//*************************************************************************
// clase piramide cuadrangular
//*************************************************************************
_piramide_cuadrang::_piramide_cuadrang()
{
  _vertex3f nodo;
//fondo
  //v0
    nodo.x=0.0;
    nodo.y=0.0;
    nodo.z=0.0;
    vertices.push_back(nodo);
    //v1
    nodo.x=1.0;
    nodo.y=0.0;
    nodo.z=0.0;
    vertices.push_back(nodo);
    //v2
    nodo.x=0.0;
    nodo.y=0.0;
    nodo.z=1.0;
    vertices.push_back(nodo);
    //v3
      nodo.x=1.0;
      nodo.y=0.0;
      nodo.z=1.0;
      vertices.push_back(nodo);
    //v4
    float h=sqrt(4.0-0.25);
    nodo.x=0.5;
    nodo.y=h;
    nodo.z=0.5;
    vertices.push_back(nodo);

//caras------------------------
    _vertex3i face;
    //cara 0 fondo
    face.x=0;
    face.y=1;
    face.z=2;
    caras.push_back(face);
    //cara1 fondo
    face.x=2;
    face.y=1;
    face.z=3;
    caras.push_back(face);

    //cara2 pared
    face.x=0;
    face.y=4;
    face.z=1;
    caras.push_back(face);
    //cara3
    face.x=1;
    face.y=4;
    face.z=3;
    caras.push_back(face);
    //caras4 antihorario
    face.x=3;
    face.y=4;
    face.z=2;
    caras.push_back(face);
    //caras5 inf antihorario
    face.x=2;
    face.y=4;
    face.z=0;
    caras.push_back(face);
}
 _cilindro::_cilindro(){
   _vertex3f nodo;
 //fondo
   //v0
     nodo.x=1.0;
     nodo.y=1.0;
     nodo.z=1.0;
     vertices.push_back(nodo);
     //v1
     nodo.x=1.0;
     nodo.y=-1.0;
     nodo.z=1.0;
     vertices.push_back(nodo);
     texturizando=false;
     revolucionar(2,20);

  }
  _vertex3f _cilindro::RotarEjeY(_vertex3f p, double ang){//rotar vertice de i
  	_vertex3f rot;
  	rot.x=cos(ang)*p.x+sin(ang)*p.z;
  	rot.y=p.y;
  	rot.z=-sin(ang)*p.x+cos(ang)*p.z;
  	return rot;
  }
  void _cilindro::revolucionar(int v_inicial, int etapas)//m numero de veces que quiero mover el perfil
  {
    int v_final,i=0,j=0;

  	v_ini=v_inicial;//v_inicial +2 tapas
  	if(texturizando){
  		n_etapas=etapas+1;
  		v_final=v_inicial*etapas;
  	}else{
  		n_etapas=etapas;
  		v_final=v_inicial*etapas-v_inicial;
  	}
  	 //no se pintal de nuevo los iniciales por eso resto m
  	double angulo=2*M_PI/etapas;//EN radianes 360/m
  	for(i=0;i<v_final;i++){

  		vertices.push_back(RotarEjeY(vertices.at(i),angulo));//añadimos al vector de vertices  los nuevos vertices que salen de la rotacion
  	}

  	_vertex3i car;

  	v_final=vertices.size();
  	//cout<<"v_fin "<<v_final<<endl;


  	for(i=0;i<v_final;i+=v_inicial){
  		for(j=i;j<i-1+v_inicial;j++){
  				//los que sean tapas no se revolucionan
  			car.x=(v_inicial+j)%v_final;
  			car.y=(v_inicial+j+1)%v_final;
  			car.z=j%v_final;//cara abajo +
  											  											// +  +

  			caras.push_back(car);

  			car.x=j%v_final;
  			car.y=(v_inicial+j+1)%v_final;
  			car.z=(j+1)%v_final;//cara encima +  +
  											      										//	+

  			caras.push_back(car);
  		}

  	}
  	int aux_final_Tapas=0.0;
  //hacer las tapas
  if(!texturizando){
  if(vertices.at(v_inicial-1).x!=0.0f || vertices.at(v_inicial-1).z!=0.0f){//detecto si hay tapa arriba
  		std::cout << "V_INICIAL "<<v_inicial -1 << '\n';
  		_vertex3f tapa_sup;
  		tapa_sup.x=0.0;
  		tapa_sup.y=vertices[v_inicial-1].y;
  		tapa_sup.z=0.0;
  		vertices.push_back(tapa_sup);

  		 aux_final_Tapas=vertices.size();
  		//cout<<"numero de vertices con tapas arriba: "<<aux_final_Tapas<<endl;

  		//caras arriba
  		for(int k=v_inicial-1;k<v_final;k+=v_inicial){
  			car.x=k%(v_final);
  			car.y=(k+v_inicial)%(v_final);
  			car.z=aux_final_Tapas-1;
  			//cout<<"cara "<<car.x<<","<<car.y<<","<<car.z<<endl;
  			caras.push_back(car);
  		}

  	}else std::cout << "hay tapa arriba" << '\n';
  	if(vertices.at(0).x!=0.0f || vertices.at(0).z!=0.0f){//detecto si hay tapa abajo
  		_vertex3f tapa_inf;
  		tapa_inf.x=0.0;
  		tapa_inf.y=vertices[0].y;
  		tapa_inf.z=0.0;
  		vertices.push_back(tapa_inf);

  		aux_final_Tapas=vertices.size();//numero de vertices + vertices tapas
  		cout<<"numero de vertices con tapas abajo : "<<aux_final_Tapas<<endl;
  		//caras abajo
  		for(int k=0;k<v_final;k+=v_inicial){
  			car.x=(k+v_inicial)%(v_final);
  			car.y=k%(v_final);
  			car.z=aux_final_Tapas-1;
  			cout<<"cara "<<car.x<<","<<car.y<<","<<car.z<<endl;
  			caras.push_back(car);
  		}
  	}else std::cout << "hay tapa abajo" << '\n';
  }
  }
