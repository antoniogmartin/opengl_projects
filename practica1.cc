//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************
#include <GL/gl.h>
#include <GL/glut.h>
#include <ctype.h>
#include <math.h>
#include <vector>
#include "objetos.h"
#include "file_ply_stl.h"
#include "grua.h"
#include <math.h>
#include "vertex.h"
#include "jpg_imagen.hpp"
using namespace std;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Size_x,Size_y,Front_plane,Back_plane;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;
char modo=' ';
GLuint  madera=1,coca=2;
char figura=' ';
char practica=' ';
int foco=0x4000;//foco0
bool activado=false;
bool plano=false;
bool grua=false;
bool lightning=false;
float rot=0 ,mov=0.0,estirar=0.8;
float velRot=0.0, velMov=0.0, velEst=0.0;
/**VARIABLES LUCES**/
float light_alpha = 0.0;
float light_beta = 0.0;
/**VARIABLES LUCES**/
/**VARIABLES TEXTURA**/
jpg::Imagen * pimg = NULL ;
jpg::Imagen * img = NULL ;
/**VARIABLES TEXTURA**/

_cubo cub (8);
_vertex3f v(2.0,1.1,1.0);
//_obj_barrido pen(1,v); descomentar
_piramide tetraedro(1,1);
_ply obj_ply;//creacion del ply
_obj_revolucion obj_rev ("./ply/perfil.ply",20);
_obj_revolucion lata_inf("./lata-pinf.ply",20);
_obj_revolucion lata_sup("./lata-psup.ply",20);
_obj_revolucion lata_pcue("./lata-pcue.ply",20,true);
_grua ba;
_cilindro ci;
GLfloat ambiente[] = {1.2f, 1.2f, 1.2f, 0.0f};//la cuarta coordenada es para decir nivel opacidad max 1.0
GLfloat difusa[] = {0.9f, 0.9f,0.9f, 0.0f};
GLfloat especular[] = {1.0f, 1.0f, 1.0f, 1.0f};

GLfloat ambiente1[] = {0.1, 0.1, 0.1, 1.0};//hacerlo más claro
GLfloat difusa1[] = {0.1,0.1,0.1, 0.9};
GLfloat especular1[] = {0.7,0.7,0.7, 0.0};//aumentar la amplitud de ilumniacion objeto


GLfloat ambiente2[] = {0.5, 0.5, 0.5, 1.0};
GLfloat difusa2[] = {2.5, 2.5,2.5, 0.0};
GLfloat especular2[] = {2.5,2.5,2.5, 0.0};
// variables que determninan la posicion y tamaño de la ventana X
int Window_x=50,Window_y=50,Window_width=450,Window_high=450;

// objetos


//**************************************************************************
//
//***************************************************************************

void clean_window()
{

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection()
{

glMatrixMode(GL_PROJECTION);
glLoadIdentity();

// formato(x_minimo,x_maximo, y_minimo, y_maximo,plano_delantero, plano_traser)
//  plano_delantero>0  plano_trasero>PlanoDelantero)
glFrustum(-Size_x,Size_x,-Size_y,Size_y,Front_plane,Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void change_observer()//OK
{

// posicion del observador
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef(0,0,-Observer_distance);
glRotatef(Observer_angle_x,1,0,0);
glRotatef(Observer_angle_y,0,1,0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{

glDisable(GL_LIGHTING);//**
glLineWidth(0.1);//**
glBegin(GL_LINES);
// eje X, color rojo
glColor3f(1,0,0);
glVertex3f(-AXIS_SIZE,0,0);
glVertex3f(AXIS_SIZE,0,0);
// eje Y, color verde
glColor3f(0,1,0);
glVertex3f(0,-AXIS_SIZE,0);
glVertex3f(0,AXIS_SIZE,0);
// eje Z, color azul
glColor3f(0,0,1);
glVertex3f(0,0,-AXIS_SIZE);
glVertex3f(0,0,AXIS_SIZE);
glEnd();
}

_vertex3f esfericasACartesianas(int alfa,int beta){

	float x=3*sin(beta * M_PI / 180.0)*cos ( alfa * M_PI / 180.0 );
	float y=3*sin(beta * M_PI / 180.0)*sin ( alfa * M_PI / 180.0 );
	float z=3*cos(alfa * M_PI / 180.0);
	 _vertex3f coord(x,y,z);
	 return coord;
}
void enableLight(int foco,float light_alpha, float light_beta){
	//Si mantengo R=G=B consigo tener blanco,gris,negro
	GLfloat lightAmbient[] = {0.1f, 0.1f, 0.1f, 1.0f};//foco del interior del objeto
	GLfloat lightDiffuse[] = {1.0f,1.0f,1.0f,0.0f};//luz de color,luz rayos paralelos
	GLfloat lightDiffuse2[] = {0.7f, 0.7f, 0.7f, 0.0f};
	GLfloat lightSpecular[] = {10.0f, 10.0f,10.0f,0.0f};//la amplitud de la zona de iluminacion
	GLfloat lightPosicional[] = {5.0f, 5.0f, 5.0f,1.0f};//luz en punto concreto, crea efecto sombra
	//GLfloat lightColor1[] = {0.5f, 0.2f, 0.2f,1.0f};
	//GLfloat posicional2[] = {-2.0f, 1.5f, -3.0f,1.0f};
	if(light_alpha!=0||light_beta!=0){
		_vertex3f coord = esfericasACartesianas(light_alpha,light_beta);
		GLfloat posicional1[] = {coord.x,coord.y,coord.z,0.0f};
		glLightfv(GL_LIGHT0, GL_POSITION, posicional1);
	}

	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse2);
	glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT1, GL_POSITION,lightPosicional);
		//glLightfv(GL_LIGHT0, GL_SPECULAR,lightSpecular);
	//glLightfv(GL_LIGHT0, GL_POSITION,lightPosicional);
	//glLightfv(GL_LIGHT2, GL_SPECULAR, lightSpecular);
	//glLightfv(GL_LIGHT2, GL_POSITION,posicional2);
		if(lightning){
				glEnable(GL_LIGHTING);
		}else 	glDisable(GL_LIGHTING);
		if(plano)
				 glShadeModel(GL_FLAT);
		else   glShadeModel(GL_SMOOTH);
if(foco==GL_LIGHT0){
		if(activado)
			glEnable(GL_LIGHT0); //Enable light #0
		else
			glDisable(GL_LIGHT0);
}
 else if(foco==GL_LIGHT1){
		if(activado)
			glEnable(GL_LIGHT1); //Enable light #0
		else
			glDisable(GL_LIGHT1);
	}

}
void draw_lataTexturizada(){

	glPushMatrix();
		glTranslatef(0.0,-0.5,0.0);
			glPushMatrix();
			lata_sup.draw_vertices_iluminados(ambiente2,difusa2,especular2);
			glPopMatrix();
			lata_inf.draw_vertices_iluminados(ambiente2,difusa2,especular2);
		glEnable(GL_TEXTURE_2D);
			lata_pcue.aplicaTexturaManual(coca);// me texturiza las tapas

	glPopMatrix();

}

void draw_escena(char sombreado){

		glPushMatrix();
		if(sombreado=='c'){
			obj_rev.draw_caras_iluminadas(ambiente,difusa,especular);
		}else if(sombreado=='v'){
			obj_rev.draw_vertices_iluminados(ambiente,difusa,especular);
		}
		glTranslatef(3.0,0.0,0.0);
		if(sombreado=='c'){
			obj_rev.draw_caras_iluminadas(ambiente1,difusa1,especular1);
		}else if(sombreado=='v'){
			obj_rev.draw_vertices_iluminados(ambiente1,difusa1,especular1);
		}
		glTranslatef(3.0,0.0,0.0);
			obj_rev.aplicaTextura(madera);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(3.0,0.0,-3.0);
			glScalef(3.0,3.0,3.0);
			draw_lataTexturizada();
		glPopMatrix();

}
void draw_escena_grua(char sombreado){
	glPushMatrix();
	if(sombreado=='c'){
		ba.dibujarGrua(rot,mov,estirar,0,ambiente,difusa,especular,madera);
	}else if(sombreado=='v'){
		ba.dibujarGrua(rot,mov,estirar,1,ambiente,difusa,especular,madera);
	}
	glTranslatef(5.0,0.0,0.0);
		ba.dibujarGrua(rot,mov,estirar,2,ambiente,difusa,especular,madera);
}

//**************************************************************************
// Funcion que dibuja los objetos
//***************************************************************************

void draw_objects()
{

	if(practica=='1'){
		if(modo=='p'){
			if(figura=='c'){
				cub.draw_puntos(1.0,0.0,1.0,5);
			}
			else if(figura=='t'){
				tetraedro.draw_puntos(1.0,0.0,1.0,5);
			}
		}
			else if (modo=='s'){
					if(figura=='c'){
						cub.draw_solido(0.0,1.0,0.0);
					}
				 else if(figura=='t'){
					tetraedro.draw_solido(0.0,1.0,0.0);
					}
			}
			else if (modo=='e'){
				if(figura=='c'){
					cub.draw_aristas(1.0,0.0,1.0,5);
				}
				else if(figura=='t'){
					tetraedro.draw_aristas(1.0,0.0,1.0,5);
				}
			}
			else if(modo=='a'){
				if(figura=='c'){
					cub.draw_solido_ajedrez(1.0,0.0,1.0,0.0,0.0,0.0);
				}
				else if(figura=='t'){
					tetraedro.draw_solido_ajedrez(1.0,0.0,1.0,0.0,0.0,0.0);
				}
			}
	}
	else if (practica=='2'){
		if(modo=='p'){
			if(figura=='l'){
				obj_ply.draw_puntos(1.0,0.0,1.0,5);
			}
			else if(figura=='o'){
				obj_rev.draw_puntos(1.0,0.0,1.0,5);
			}
		}
			else if (modo=='s'){
					if(figura=='l' ){
						obj_ply.draw_solido(0.0,1.0,0.0);
					}
				 else if(figura=='o'){
					obj_rev.draw_solido(0.0,1.0,0.0);
					}
			}
			else if (modo=='e'){
				if(figura=='l'){
					obj_ply.draw_aristas(1.0,0.0,1.0,5);
				}
				else if(figura=='o' ){
					obj_rev.draw_aristas(1.0,0.0,1.0,5);
				}
			}
			else if(modo=='a'){
				if(figura=='l' ){
					obj_ply.draw_solido_ajedrez(1.0,0.0,1.0,0.0,0.0,0.0);
				}
				else if(figura=='o' ){
					obj_rev.draw_solido_ajedrez(1.0,0.0,1.0,0.0,0.0,0.0);
				}
			}
	 }
	 else if(practica=='3'){
		 			ba.dibujarGrua(rot,mov,estirar);
	 			}
		else if(practica=='4'){

			if(modo=='c'){
				if(grua)
					draw_escena_grua(modo);
				else
					draw_escena(modo);

			}
			else if(modo=='v'){
				if(grua)
					draw_escena_grua(modo);
				else
					draw_escena(modo);
			}

			else if(activado){
				enableLight(foco,light_alpha,light_beta);
			}
			else if(!activado){
				enableLight(foco,light_alpha,light_beta);
			}

		}

	}

//**************************************************************************
//
//***************************************************************************

void draw(void)
{
	clean_window();
	change_observer();
	draw_axis();
	enableLight(foco,light_alpha,light_beta);
	draw_objects();//lamada a dibujar objetos
	glutSwapBuffers();
}



//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1,int Alto1)
{
float Aspect_ratio;
Aspect_ratio=(float) Alto1/(float )Ancho1;
Size_y=Size_x*Aspect_ratio;
change_projection();
glViewport(0,0,Ancho1,Alto1);
glutPostRedisplay();
}

//***************************************************************************
// Funcion llamada cuando se aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_key(unsigned char Tecla1,int x,int y)
{
if (toupper(Tecla1)=='Q') exit(0);
if (Tecla1=='1'){
	std::cout << "\t--Practica 1 SELECCIONADA--" << std::endl;
	std::cout << "\t--cubo:c	tetraedro:t--" << std::endl;
		practica='1';

	}else if(Tecla1=='p' && (practica=='1' ||practica=='2')){
					modo='p';
					std::cout << "\t--modo Punto seleccionado--" << std::endl;
				}
	else if(Tecla1=='e'&& (practica=='1' ||practica=='2')){
					modo='e';
					std::cout << "\t--modo Alambre seleccionado--" << std::endl;
				}
	else if (Tecla1=='s'&& (practica=='1' ||practica=='2')){
					modo='s';
					std::cout << "\t--modo Solido seleccionado--" << std::endl;
				}
	else if (Tecla1=='a'&& (practica=='1' ||practica=='2')){
					modo='a';
					std::cout << "\t--modo Ajedrez seleccionado--" << std::endl;
			}
	else if(practica=='1' && Tecla1=='c'){
            figura='c';
            std::cout << "\t--figura cubo seleccionada--" << std::endl;
        }
  else if(practica=='1' && Tecla1=='t'){
              figura='t';
              std::cout << "\t--figura tetraedro seleccionada--" << std::endl;
        }
	else if(Tecla1=='2'){
				practica='2';
				std::cout << "\t--Practica 2 SELECCIONADA--" << std::endl;
				std::cout << "\t--ply:o	revolucion:l--" << std::endl;
				}
  else if(practica=='2' && Tecla1=='l'){
          figura='l';
          std::cout << "\t--figura ply seleccionada--" << std::endl;
      }
  else if(practica=='2' && Tecla1=='o'){
              figura='o';
              std::cout << "\t--figura revolucion PLY seleccionada--" << std::endl;
      }

	else if(Tecla1=='3'){
				practica='3';
				std::cout << "\t--Práctica 3 SELECCIONADA: Modelo jerarquico--" << std::endl;
				std::cout << "\t--r:giro dcha		l:giro izq 	t:carro atras	 y:carro adelante	u:gancho arriba	 i:gancho abajo--" << std::endl;
				}

	else if(practica=='3' && Tecla1=='l'  ){
							velRot+=0.1;
			}else if(practica=='3' && Tecla1=='r'){
							velRot-=0.1;
			}else if(practica=='3' && Tecla1=='t'){
							velMov-=0.006;

			}else if(practica=='3' && Tecla1=='y'){
							velMov+=0.006;

			}else if(practica=='3' && Tecla1=='u'){
						if(estirar>0.1)
							velEst-=0.001;
			}else if(practica=='3' && Tecla1=='i'){
							if(estirar<2.7)
							velEst+=0.001;
						}
			 else if(Tecla1=='4'){
							practica='4';
							std::cout << "\t--Practica 4 SELECCIONADA--" << std::endl;
							std::cout << "\t--caras_iluminadas:c	vertices_iluminados:v  activarLUZ:a desactivarLUZ:d--" << std::endl;
							std::cout << "\t--controlar_light0:s controlar_light1:f	--" << std::endl;
							std::cout << "\t--shadeModel plano:b  shadeModel smooth:n  --" << std::endl;
							std::cout << "\t--alpha++:shift+x  alpha--:shift+c beta++:shift+a  beta--:shift+z--" << std::endl;

						}
			else if(practica=='4'&& Tecla1=='c'){
								std::cout << "dibujar caras iluminadas" << std::endl;
								modo='c';
				}
			else if(practica=='4'&& Tecla1=='v'){
									std::cout << "dibujar vertices iluminados" << std::endl;
									modo='v';
					}
			else if (practica=='4'&& Tecla1=='a'){
							if(!activado){
								std::cout << "activado de luz" << std::endl;
								activado=true;
							}else{
								std::cout << "desactivado de luz" << std::endl;
								activado=false;
							}

						}

			else if (practica=='4'&& Tecla1=='s'){
				std::cout << "Controlas LIGTH0 " << std::endl;
				foco=0x4000;
			}
			else if(practica=='4'&& Tecla1=='f'){
					std::cout << "Controlas LIGTH1 " << std::endl;
				foco=0x4001;
			}
			else if(practica=='4'&& Tecla1=='h'){

				if(!lightning){
						std::cout << "activado LIGTHING" << std::endl;
						lightning=true;
						//glEnable(GL_LIGHTING);
				}else{
					std::cout << "desactivado LIGTHING" << std::endl;
					lightning=false;
				//	glDisable(GL_LIGHTING);
				}
			}
			else if(practica=='4' && Tecla1=='b'){
				if(!plano){
					std::cout << "shadeModel:FLAT" << std::endl;
					plano=true;
				}else{
					std::cout << "shadeModel: SMOOTH" << std::endl;
					plano=false;
				}
			}
			else if(practica=='4' && Tecla1=='g'){
				std::cout << "escena grua" << std::endl;
				if(!grua)
					grua=true;
				else grua=false;
			}
			else if(practica=='4'){
							switch (Tecla1)
						{
							case 'A': // aumentar el valor de β
								light_beta +=1.0;
								std::cout << "beta: "<<light_beta << std::endl;
								enableLight(foco,light_alpha,light_beta);
								break;
							case 'Z': // disminuir el valor de β
								light_beta-=1.0;
								std::cout << "beta: "<<light_beta << std::endl;
								enableLight(foco,light_alpha,light_beta);
								break;
							case 'X': // aumentar el valor de α
								light_alpha+=1.0;
								std::cout << "alfa: "<<light_alpha << std::endl;
								enableLight(foco,light_alpha,light_beta);
								break;
							case 'C': // disminuir el valor de α
								light_alpha-=1.0f;
								std::cout << "alfa: "<<light_alpha << std::endl;
								enableLight(foco,light_alpha,light_beta);
								break;

						}
			}

		glutPostRedisplay();
}

//******** llamada cuando se aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_key(int Tecla1,int x,int y)
{

switch (Tecla1){
	case GLUT_KEY_LEFT:Observer_angle_y--;break;
	case GLUT_KEY_RIGHT:Observer_angle_y++;break;
	case GLUT_KEY_UP:Observer_angle_x--;break;
	case GLUT_KEY_DOWN:Observer_angle_x++;break;
	case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
	case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
	}
glutPostRedisplay();
}



//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void)
{
// se inicalizan la ventana y los planos de corte
Size_x=0.5;
Size_y=0.5;
Front_plane=1;
Back_plane=10000;

// se incia la posicion del observador, en el eje z
Observer_distance=300*Front_plane;
Observer_angle_x=0;
Observer_angle_y=0;

_textura t1(madera,"text-madera.jpg");
_textura t2(coca,"text-lata-1.jpg");
// se indica cual sera el color para limpiar la ventana	(r,v,a,al)
// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
glClearColor(1,1,1,1);
//para eliminar partes ocultas
glEnable(GL_CULL_FACE);

// se habilita el z-bufer
glEnable(GL_DEPTH_TEST);
change_projection();
glViewport(0,0,Window_width,Window_high);
//Cargamos la imagen una sola vez


}


//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************
void mov_automatico(){

	rot+=velRot;
	if(mov+velMov>-10.0&&mov+velMov<=0.0)
		mov+=velMov;
	else velMov=0.0;

	if(estirar+velEst>0.1&&estirar+velEst<=2.7)
		estirar+=velEst;
	else velEst=0.0;

	glutPostRedisplay();
}

int main(int argc, char **argv)
{

// se llama a la inicialización de glut
glutInit(&argc, argv);

// se indica las caracteristicas que se desean para la visualización con OpenGL
// Las posibilidades son:
// GLUT_SIMPLE -> memoria de imagen simple
// GLUT_DOUBLE -> memoria de imagen doble
// GLUT_INDEX -> memoria de imagen con color indizado
// GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
// GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
// GLUT_DEPTH -> memoria de profundidad o z-bufer
// GLUT_STENCIL -> memoria de estarcido

glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

// posicion de la esquina inferior izquierdad de la ventana
glutInitWindowPosition(Window_x,Window_y);

// tamaño de la ventana (ancho y alto)
glutInitWindowSize(Window_width,Window_high);


// llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
// al bucle de eventos)
glutCreateWindow("PRACTICA 4 - Antonio Guzman Martin");

// asignación de la funcion llamada "dibujar" al evento de dibujo
glutDisplayFunc(draw);
// asignación de la funcion llamada "change_window_size" al evento correspondiente
glutReshapeFunc(change_window_size);
// asignación de la funcion llamada "normal_key" al evento correspondiente
glutKeyboardFunc(normal_key);


//movimiento automatico
glutIdleFunc(mov_automatico);
// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
glutSpecialFunc(special_key);

// funcion de inicialización
initialize();

// inicio del bucle de eventos
glutMainLoop();
return 0;
}
