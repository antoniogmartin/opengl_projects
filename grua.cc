#include "grua.h"

_grua::_grua() :cub(2){ //: constructor(param)
	num_cub=6;
	num_tri=12;
	}

	void _grua::dibujarGrua(float ang, float mover, float estirar){
		dibujarBase();
		dibujarPluma(ang,mover,estirar);
	}


	void _grua::dibujarBase(){
		glPushMatrix();
			glTranslatef(0.0,0.33,0.0);
			glScalef(2.0,0.3,2.0);
			cub.draw_solido(1.0,0.22,0.0);
		glPopMatrix();
		glPushMatrix();
				glTranslatef(0.0,1.66,0.0);
				for(int i=0;i<num_cub;i++){
					cub.draw_aristas(1.0,0.62,0.0,2);
					glTranslatef(0.0,2.0,0.0);
				}
		glPopMatrix();
				glPushMatrix();
					glTranslatef(0.0,12.96,0.0);//la diferencia entre el translatef anterior y este cubo
					glScalef(1.0,0.3,1.0);
					cub.draw_solido(1.0,0.62,0.0);
				glPopMatrix();

	}
	void _grua::dibujarPluma(float ang,float mover,float estirar){
			glPushMatrix();
				glRotatef(ang,0,1,0);
				glPushMatrix();
					glTranslatef(-1.0,13.28,-1.0);//añado los 0.6 del cubo de la copa
					glScalef(2.0,2.0,2.0);
					cuad.draw_aristas(1.0,0.22,0.0,2);
				glPopMatrix();
					dibujarContraPeso();

				glPushMatrix();
					glTranslatef(0.0,13.28,1.0);
					glRotatef(90,0,1,0);
					glScalef(2.0,2.0,2.0);
					for(int i=0;i<num_tri;i++){
						glTranslatef(1.0,0.0,0.0);
						tri.draw_aristas(1.0,0.62,0.0,4);
					}
					dibujarCarroPluma(mover,estirar);

				glPopMatrix();

			glPopMatrix();

	}

		void _grua::dibujarCarroPluma(float mover,float estirar){
				glPushMatrix();
					glTranslatef(mover,-0.31,0.0);
						glPushMatrix();
							glScalef(1.0,0.3,1.0);
							cub.draw_solido(1.0,0.22,0.0);
						glPopMatrix();
					glPushMatrix();
								glTranslatef(0.0,-0.3-estirar,0.0);
										glPushMatrix();
											glScalef(0.2,estirar,0.2);
											ci.draw_aristas(0.0,0.0,0.9,2);
										glPopMatrix();
								glRotatef(180,0,0,1);
								glTranslatef(-0.1,estirar,-0.1);
								glScalef(0.2,0.4,0.2);
								cuad.draw_aristas(1.0,0.22,0.0,2);
					glPopMatrix();
				glPopMatrix();
		}
	void _grua::dibujarContraPeso(){
		glPushMatrix();
			glTranslatef(0.0,13.28,3.0);
				glPushMatrix();
					glScalef(1.0,0.2,2.0);
					for(int i=0;i<3;i++){
						cub.draw_aristas(1.0,0.62,0.0,2);
						glTranslatef(0.0,0.0,2.0);
					}
		glPopMatrix();
				glPushMatrix();
					glTranslatef(0.0,-1.21,5.0);
					glScalef(1.0,1.0,2.0);
					cub.draw_solido(0.2,0.2,0.2);
				glPopMatrix();

		glPopMatrix();
	}
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

		void _grua::dibujarGrua(float ang, float mover, float estirar,int forma,GLfloat ambiente[],GLfloat difusa[], GLfloat especular[],GLuint text){
			dibujarBase(forma,ambiente,difusa,especular,text);
			dibujarPluma(ang,mover,estirar,forma,ambiente,difusa,especular,text);
		}

	void _grua::dibujarBase(int forma,GLfloat ambiente[],GLfloat difusa[], GLfloat especular[],GLuint text){
		glPushMatrix();
			glTranslatef(0.0,0.33,0.0);
			glScalef(2.0,0.3,2.0);
					switch (forma)
				{
					case 0: // disminuir el valor de β
						cub.draw_caras_iluminadas(ambiente,difusa,especular);
						break;
					case 1: // aumentar el valor de α
						cub.draw_vertices_iluminados(ambiente,difusa,especular);
						break;
					case 2: // disminuir el valor de α
						cub.aplicaTextura(text);
						break;
				}
		glPopMatrix();
		glPushMatrix();
				glTranslatef(0.0,1.66,0.0);
				for(int i=0;i<num_cub;i++){
							switch (forma)
						{
							case 0: // disminuir el valor de β
								cub.draw_caras_iluminadas(ambiente,difusa,especular);
								break;
							case 1: // aumentar el valor de α
								cub.draw_vertices_iluminados(ambiente,difusa,especular);
								break;
							case 2: // disminuir el valor de α
								cub.aplicaTextura( text);
								break;
						}
					glTranslatef(0.0,2.0,0.0);
				}
		glPopMatrix();
				glPushMatrix();
					glTranslatef(0.0,12.96,0.0);//la diferencia entre el translatef anterior y este cubo
					glScalef(1.0,0.3,1.0);
							switch (forma)
						{
							case 0: // disminuir el valor de β
								cub.draw_caras_iluminadas(ambiente,difusa,especular);
								break;
							case 1: // aumentar el valor de α
								cub.draw_vertices_iluminados(ambiente,difusa,especular);
								break;
							case 2: // disminuir el valor de α
								cub.aplicaTextura(text);
								break;
						}
				glPopMatrix();

	}

	void _grua::dibujarPluma(float ang,float mover,float estirar,int forma,GLfloat ambiente[],GLfloat difusa[], GLfloat especular[],GLuint text){
			glPushMatrix();
				glRotatef(ang,0,1,0);
				glPushMatrix();
					glTranslatef(-1.0,13.28,-1.0);//añado los 0.6 del cubo de la copa
					glScalef(2.0,2.0,2.0);
							switch (forma)
						{
							case 0: // disminuir el valor de β
								cuad.draw_caras_iluminadas(ambiente,difusa,especular);
								break;
							case 1: // aumentar el valor de α
								cuad.draw_vertices_iluminados(ambiente,difusa,especular);
								break;
							case 2: // disminuir el valor de α
								cuad.aplicaTextura(text);
								break;
						}
				glPopMatrix();
					dibujarContraPeso(forma,ambiente,difusa,especular,text);

				glPushMatrix();
					glTranslatef(0.0,13.28,1.0);
					glRotatef(90,0,1,0);
					glScalef(2.0,2.0,2.0);
					for(int i=0;i<num_tri;i++){
						glTranslatef(1.0,0.0,0.0);
							switch (forma)
						{
							case 0: // disminuir el valor de β
								tri.draw_caras_iluminadas(ambiente,difusa,especular);
								break;
							case 1: // aumentar el valor de α
								tri.draw_vertices_iluminados(ambiente,difusa,especular);
								break;
							case 2: // disminuir el valor de α
								tri.aplicaTextura(text);
								break;
						}
					}
					dibujarCarroPluma(mover,estirar,forma,ambiente,difusa,especular,text);

				glPopMatrix();

			glPopMatrix();

	}


	void _grua::dibujarCarroPluma(float mover,float estirar,int forma,GLfloat ambiente[],GLfloat difusa[], GLfloat especular[],GLuint text){
			glPushMatrix();
				glTranslatef(mover,-0.31,0.0);
					glPushMatrix();
						glScalef(1.0,0.3,1.0);
						switch (forma)
					{
						case 0: // disminuir el valor de β
							cub.draw_caras_iluminadas(ambiente,difusa,especular);
							break;
						case 1: // aumentar el valor de α
							cub.draw_vertices_iluminados(ambiente,difusa,especular);
							break;
						case 2: // disminuir el valor de α
							cub.aplicaTextura(text);
							break;
					}
					glPopMatrix();
				glPushMatrix();
							glTranslatef(0.0,-0.3-estirar,0.0);
									glPushMatrix();
										glScalef(0.2,estirar,0.2);
										switch (forma)
									{
										case 0: // disminuir el valor de β
											ci.draw_caras_iluminadas(ambiente,difusa,especular);
											break;
										case 1: // aumentar el valor de α
											ci.draw_vertices_iluminados(ambiente,difusa,especular);
											break;
										case 2: // disminuir el valor de α
											ci.aplicaTextura(text);
											break;
									}
									glPopMatrix();
							glRotatef(180,0,0,1);
							glTranslatef(-0.1,estirar,-0.1);
							glScalef(0.2,0.4,0.2);
									switch (forma)
								{
									case 0: // disminuir el valor de β
										cuad.draw_caras_iluminadas(ambiente,difusa,especular);
										break;
									case 1: // aumentar el valor de α
										cuad.draw_vertices_iluminados(ambiente,difusa,especular);
										break;
									case 2: // disminuir el valor de α
										cuad.aplicaTextura(text);
										break;
								}
				glPopMatrix();
			glPopMatrix();
	}

	void _grua::dibujarContraPeso(int forma,GLfloat ambiente[],GLfloat difusa[], GLfloat especular[],GLuint text){
		glPushMatrix();
			glTranslatef(0.0,13.28,3.0);
				glPushMatrix();
					glScalef(1.0,0.2,2.0);
					for(int i=0;i<3;i++){
						switch (forma)
					{
						case 0: // disminuir el valor de β
							cub.draw_caras_iluminadas(ambiente,difusa,especular);
							break;
						case 1: // aumentar el valor de α
							cub.draw_vertices_iluminados(ambiente,difusa,especular);
							break;
						case 2: // disminuir el valor de α
							cub.aplicaTextura(text);
							break;
					}
						glTranslatef(0.0,0.0,2.0);
					}
		glPopMatrix();
				glPushMatrix();
					glTranslatef(0.0,-1.21,5.0);
					glScalef(1.0,1.0,2.0);
					switch (forma)
				{
					case 0: // disminuir el valor de β
						cub.draw_caras_iluminadas(ambiente,difusa,especular);
						break;
					case 1: // aumentar el valor de α
						cub.draw_vertices_iluminados(ambiente,difusa,especular);
						break;
					case 2: // disminuir el valor de α
						cub.aplicaTextura(text);
						break;
				}
				glPopMatrix();

		glPopMatrix();
	}
