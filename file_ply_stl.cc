//******************************************************************************
// class to read ply files of triangles
//
// Domingo Martín Perandres (c) 2003-2013
//
// Gnu Public Licence
// last update
// 131019
//******************************************************************************

#include "file_ply_stl.h"
#include "vertex.h"
//******************************************************************************
//
//******************************************************************************


_file_ply::_file_ply()
{
_element_token_table Element1;
const char* Text_tokens[]={"ply","format","ascii","element","vertex","face","end_header","zzzzzzzz",""};

for (int i=0;i<_tokens(NUMBER);i++)
	{
	Element1.Text=Text_tokens[i];
	Element1.Token=(_tokens) i;
	Token_table.push_back(Element1);
	}

Debug=false;
Buffer[0]='\0';
Num_lines=0;
}

//******************************************************************************
//
//******************************************************************************

int _file_ply::open(char *File_name)
{

if ((File=fopen(File_name,"r"))==NULL)
	{
	printf("Error: the file %s cannot be opened\n",File_name);
	return(-1);
	}
return(0);
}

//******************************************************************************
//
//******************************************************************************

int _file_ply::create(char *File_name)
{

if ((File=fopen(File_name,"w"))==NULL)
	{
	printf("Error: the file %s cannot be created\n",File_name);
	return(-1);
	}
return(0);
}

//******************************************************************************
//
//******************************************************************************

int _file_ply::read_line()
{


if (!feof(File))
	{
	fgets(Buffer,MAX_LENGTH_LINE,File);
  if (strlen(Buffer)==0) return(-1);
	Num_lines++;
//  printf("%d:%s",Num_lines,Buffer);
	return(0);
	}
return(-1);
}

//******************************************************************************
//
//******************************************************************************

int _file_ply::next_token()
{
char Aux_token[100];
char *Aux_token1;
int Num_char=0;
int Pos0;
int Pos1;

do{
    if (strlen(Buffer)==0){
        // leer una linea si no se ha leido antes
		if (read_line()==-1) return(-1);
        // si es un comentario lee la siguiente
		while (Buffer[0]=='#') if (read_line()==-1) return(-1);
		}
    Aux_token1= strtok(Buffer," \t\n");
    if (Aux_token1!=NULL){
        strcpy(Aux_token,Aux_token1);
        Num_char=strlen(Aux_token);
//        strcpy(Buffer,Buffer+Num_char+1);
        Pos0=Num_char+1;
        Pos1=0;
        while (Buffer[Pos0]!='\0'){
          Buffer[Pos1++]=Buffer[Pos0];
          Pos0++;
        }
        Buffer[Pos1++]='\0';
//        printf("Buffer:%s\n",Buffer);
    }
    else{// por si hay delimitadores al final de una linea
        Num_char=0;
        Buffer[0]=0;
    }

	}
while (Num_char==0);


if (!is_number(Aux_token))
	{
//  printf("es un numero %s\n",Aux_token);
	Yylval.Real=atof(Aux_token);
	return((int)_tokens(NUMBER));
	}
else
	{
//  printf("es texto %s\n",Aux_token);
	Yylval.Text=Aux_token;
	return(search_token(Aux_token));
	}
}

//******************************************************************************
//
//******************************************************************************

int _file_ply::
read(vector<_vertex3f> &Vertices,vector<_vertex3i> &Faces)
{
int Next_token,i=0,j=0,global=0;
int Num_vertices,Num_faces;

if (File!=NULL)
	{
	Next_token=next_token();
	if (Next_token==PLY)
		{
		Next_token=next_token();
		if (Next_token==FORMAT)
			{
			Next_token=next_token();
			if (Next_token==ASCII)
				{
				Next_token=next_token();
				if (Next_token==NUMBER)
					{// head
					Next_token=next_token();
					while (Next_token!=END_HEADER)
						{
						if (Next_token==ELEMENT)
							{
							Next_token=next_token();
							switch (Next_token)
								{
								case VERTEX:
									Next_token=next_token();
									if (Next_token==NUMBER)
										{
          					Num_vertices=(int) Yylval.Real;
										Vertices.resize(Num_vertices);
										}
									else error("no number of vertex");
									break;
								case FACE:
									Next_token=next_token();
									if (Next_token==NUMBER)
										{
          					Num_faces=(int) Yylval.Real;
										Faces.resize(Num_faces);
										}
									else error("no number of faces");
									break;
								default:
									error("element type not supported");
									break;
								}
							}
						Next_token=next_token();
						}
					// data
					// vertices data
					for (i=0;i<Num_vertices;i++)
						{// vertices data

						for (j=0;j<3;j++)
							{
							Next_token=next_token();
							if (Next_token==NUMBER)
								{

									if(j==0)
										Vertices[i].x=Yylval.Real;
									else if(j==1)
													Vertices[i].y=Yylval.Real;
												else if(j==2)
													Vertices[i].z=Yylval.Real;

								}
							else{ error("no number for coordinate");}
							}
						}
					// faces data
					for (i=0;i<Num_faces;i++)
						{
						Next_token=next_token();
						if (Next_token==NUMBER)
							{
							if ((int)Yylval.Real!=3) {
								printf("Face=%d Token=%s\n",i,Yylval.Text.c_str());
								error("only triangles supported");;
								}
							}
						else error("no number of vertex indices");
						for (j=0;j<3;j++)
							{
							Next_token=next_token();
							if (Next_token==NUMBER)
								{
								if(j==0)
									Faces[i].x=(int)Yylval.Real;
								else if(j==1)
												Faces[i].y=(int)Yylval.Real;
											else if(j==2)
												Faces[i].z=(int)Yylval.Real;
								}
							else{error("no number for coordinate,face");}
							}
						}
					printf("File readed\n");
					}
				else error("no format number");
				}
			else error("no ascii format");
			}
		else error("no format word");
		}
	else error("this is not a ply file");
	return(0);
	}
else
	{
	error("there is not a ply file open");
	return(-1);
	}
}

//******************************************************************************
//
//******************************************************************************

//int _file_ply::write(vector<float> &Vertices,vector<int> &Faces)
//{
//    error("Not implemented");
//    return(0);
//}

//******************************************************************************
//
//******************************************************************************

int _file_ply::close()
{

fclose(File);
return(0);
}

//******************************************************************************
//
//******************************************************************************

void _file_ply::error(const char *Error)
{

printf("Error: %s. Stop in line %d\n",Error,Num_lines);
exit(-1);
}

//******************************************************************************
//
//******************************************************************************

int _file_ply::is_number(char *Aux_token)
{
char *p1;

for (unsigned int i=0;i<strlen(Aux_token);i++)
	{
    if ((p1=strchr((char *)"0123456789.+-eE",Aux_token[i]))==NULL) return(-1);
	}
return(0);
}

//******************************************************************************
//
//******************************************************************************

int _file_ply::search_token(char *Aux_token)
{
int i=0;

while (!(Token_table[i].Text=="zzzzzzzz"))
	{
	//printf("Buscando token %d %s\n",i,Token_table[i].Text.c_str());
	if (Token_table[i].Text==Aux_token) break;
	i++;
	}
//getchar();
return(i);
}

//CONSTRUYENDO OBJETO PLY
_ply::_ply(){
  build_ply("./ply/beethoven.ply");
}
_ply::_ply(string name_ply){
  build_ply(name_ply);
}

void _ply::build_ply(string name_ply){
  //cout<<"Introduce el path del archivo ply\n";
  //cin>> name_ply;
  char *path = new char[name_ply.length() + 1];
  std::cout << name_ply << std::endl;
  //conversion string-char*
  strcpy(path, name_ply.c_str());
  open(path);//si vale 0 es que se ha abierto el archivo en caso contrario -1;
  read(vertices,caras);
  delete [] path;
  close();
}

//CONSTRUYENDO OBJETO PLY REVOLUCIONADO
_obj_revolucion::_obj_revolucion(){

}

_obj_revolucion::_obj_revolucion(string name_ply,int etapas){
	build_revolucion(name_ply);
	texturizando=false;
	revolucionar(getVertices(),etapas);//añadir vertices revolucionados al perfil

}
_obj_revolucion::_obj_revolucion(string name_ply,int etapas,bool modo_textura){
	build_revolucion(name_ply);
	texturizando=modo_textura;
	revolucionar(getVertices(),etapas);//añadir vertices revolucionados al perfil

}
/*_obj_revolucion::obj_revolucion(string name_ply,int etapas,_textura t){
	build_revolucion(name_ply);
	revolucionar(getVertices(),etapas);//añadir vertices revolucionados al perfil
}*/

void _obj_revolucion::build_revolucion(string name_ply){
  //cout<<"Introduce el path del archivo ply Revolucionado\n";
  //cin>> name_ply;
  char *path = new char[name_ply.length() + 1];
  std::cout << name_ply << std::endl;
  //conversion string-char*
  strcpy(path, name_ply.c_str());
  open(path);//si vale 0 es que se ha abierto el archivo en caso contrario -1;
  read(vertices,caras);
  delete [] path;
  close();
}
int  _obj_revolucion::getVertices(){

	return vertices.size();
}
_vertex3f _obj_revolucion::RotarEjeY(_vertex3f p, double ang){//rotar vertice de i
	_vertex3f rot;
	rot.x=cos(ang)*p.x+sin(ang)*p.z;
	rot.y=p.y;
	rot.z=-sin(ang)*p.x+cos(ang)*p.z;
	return rot;
}
void _obj_revolucion::aplicaTextura(GLuint id){


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
void _obj_revolucion::aplicaTexturaManual(GLuint id){
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
	  glBindTexture(GL_TEXTURE_2D,id);
	vector< _vertex2f> mTextura;
	vector<float>t;
	float dato,divisor=0.0;
	_vertex2f aux;
	float d_ini_fin=sqrt(pow(vertices.at(v_ini-1).x-vertices.at(0).x,2)+pow(vertices.at(v_ini-1).y-vertices.at(0).y,2)+pow(vertices.at(v_ini-1).z-vertices.at(0).z,2));
	normalACaras();
	normal_vertices.resize(vertices.size());
	_vertex3f unitario;
	_vertex3f ind_ver;
	for(int i=0;i<v_ini;i++){
		if(i<v_ini-1){
			dato=sqrt(pow(vertices.at(i).x-vertices.at(0).x,2)+pow(vertices.at(i).y-vertices.at(0).y,2)+pow(vertices.at(i).z-vertices.at(0).z,2));
			//std::cout << "dato "<<dato/d_ini_fin << '\n';
			t.push_back(dato/d_ini_fin);
		}else t.push_back(1.0);

	}
	float num=0.0f, etap=0.0f;
	for(int i=0;i<n_etapas;i++){
		for(int j=0;j<t.size();j++){
			 	num=i;
				etap=n_etapas-1;
				aux.x=(num/etap);//dist entre 2 puntos
				aux.y=t.at(j);
				mTextura.push_back(aux);
		}
	}

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

	glBegin(GL_TRIANGLES);

		for(int i=0;i<caras.size();i++){

					ind_ver=vertices.at(caras.at(i).x);
					glNormal3f(normal_vertices.at(caras.at(i).x).x,normal_vertices.at(caras.at(i).x).y,normal_vertices.at(caras.at(i).x).z);
					if(caras.at(i).x<getVertices()-2){
						glTexCoord2f(mTextura.at(caras.at(i).x).x,mTextura.at(caras.at(i).x).y);

					}
					glVertex3f(ind_ver.x,ind_ver.y,ind_ver.z);
					ind_ver=vertices.at(caras.at(i).y);
					glNormal3f(normal_vertices.at(caras.at(i).y).x,normal_vertices.at(caras.at(i).y).y,normal_vertices.at(caras.at(i).y).z);
					if(caras.at(i).y<getVertices()-2){
						glTexCoord2f(mTextura.at(caras.at(i).y).x,mTextura.at(caras.at(i).y).y);
					}
					glVertex3f(ind_ver.x,ind_ver.y,ind_ver.z);
					ind_ver=vertices.at(caras.at(i).z);
					glNormal3f(normal_vertices.at(caras.at(i).z).x,normal_vertices.at(caras.at(i).z).y,normal_vertices.at(caras.at(i).z).z);
					if(caras.at(i).z<getVertices()-2){
						glTexCoord2f(mTextura.at(caras.at(i).z).x,mTextura.at(caras.at(i).z).y);
					}
					glVertex3f(ind_ver.x,ind_ver.y,ind_ver.z);//falla al pintar glNormal3f

		}
		glEnd();
		glDisable(GL_TEXTURE_2D);

}

void _obj_revolucion::revolucionar(int v_inicial, int etapas)//m numero de veces que quiero mover el perfil
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




//CONSTRUYENDO BARRIDO
_obj_barrido::_obj_barrido(){

}
_obj_barrido::_obj_barrido(int etapas,_vertex3f transform){
	build_barrido();
	makeBarrido(getVertices(),transform,etapas);//añadir vertices revolucionados al perfil

}
void _obj_barrido::build_barrido(){
  string name_ply;
  cout<<"Introduce el path del archivo ply de barrido\n";
  cin>> name_ply;
  char *path = new char[name_ply.length() + 1];
  std::cout << name_ply << std::endl;
  //conversion string-char*
  strcpy(path, name_ply.c_str());
  open(path);//si vale 0 es que se ha abierto el archivo en caso contrario -1;
  read(vertices,caras);
  delete [] path;
  close();
}
int  _obj_barrido::getVertices(){

	return vertices.size();
}

_vertex3f _obj_barrido::transformar(_vertex3f transform,_vertex3f p) {//el actual más la transformacion
  	_vertex3f res;
  	res.x=p.x+transform.x;
  	res.y=p.y+transform.y;
  	res.z=p.z+transform.z;
    return res;
}
/* Funciones no implementadas

void obj_barrido::doLateral(int pos_ini,bool inclinado){
	_vertex3i car;
	car.x=pos_ini;
	car.y=pos_ini+v_ini;
	car.z=car.y/2;//si es impar no vale hay que sumar1
	caras.push_back(car);
	if(inclinado=false){
		pos_ini+=2;
		car.x=pos_ini;
		car.y=pos_ini*2+1;
		car.z=car.y+2;
	}else{
		pos_ini++;
		car.x=pos_ini;
		car.y=pos_ini*2;
		car.z=car.y+1;//con lateral derecho no funciona
	}

	caras.push_back(car);
}
void obj_barrido::doBase(int pos_ini){
	_vertex3i car;
	car.x=pos_ini;
	car.y=pos_ini+v_ini;
	car.z=car.y-v_ini+1;
	caras.push_back(car);
	pos_ini--;
	if(pos_ini>=0){
		car.x=pos_ini;
		car.y=v_ini+1+pos_ini;
		car.z=car.y-1;
		caras.push_back(car);
	}

}*/
void _obj_barrido::makeBarrido(int v_inicial,_vertex3f transform,int etapas) {
	int v_final=v_inicial*etapas,i=0,j=0;
	for(i=0;i<v_final;i++){
		vertices.push_back(transformar(transform,vertices.at(i)));//añadimos al vector de vertices  los nuevos vertices que salen de la rotacion

		_vertex3i car;

		v_final=vertices.size();
		//cout<<"v_fin "<<v_final<<endl;


	}
}
