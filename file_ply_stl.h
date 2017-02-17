//******************************************************************************
// class to read ply files of triangles
//
// Domingo Martín Perandres (c) 2003-2013
//
// Gnu Public Licence
//******************************************************************************

#ifndef _READ_PLY
#define _READ_PLY

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
#include "vertex.h"
#include <assert.h>
#include <iostream>
#include <math.h>
#include "objetos.h"
#include "textura.h"
using namespace std;

using namespace std;

const int MAX_LENGTH_LINE=256;

typedef enum {PLY,FORMAT,ASCII,ELEMENT,VERTEX,FACE,END_HEADER,TEXT,NUMBER} _tokens;

struct _element_token_table
{
string Text;
_tokens Token;
};

class _yylval
{
public:
float Real;
string Text;
};


class _file_ply: public _triangulos3D
{
public:

				_file_ply();
int open(char *File_name);
int read(vector<_vertex3f> &Vertices,vector<_vertex3i> &Faces);
int create(char *File_name);
//int write(vector<float> &Vertices,vector<int> &Faces);
int close();

private:
bool Debug;
FILE *File;
_yylval Yylval;
char Buffer[MAX_LENGTH_LINE];
string Text;
vector<_element_token_table> Token_table;
int Num_lines;


int 	read_line();
int 	next_token();
void	error(const char *Error);
int 	is_number(char *Aux_token);
int 	search_token(char *Aux_token);

};
class _ply: public _file_ply
{
	public:
		_ply();
		_ply(string name_ply);
		void  build_ply(string name_ply);

};

class _obj_revolucion : public _file_ply
{

private:
	int n_etapas;
	int v_ini;
	bool texturizando;
public:
	_obj_revolucion();
	_obj_revolucion(string name_ply,int etapas);
	_obj_revolucion(string name_ply,int etapas,bool modo_textura);

	//_obj_revolucion(string name_ply,int etapas,_textura t);
	void build_revolucion(string name_ply);
	int getVertices();
	//_obj_revolucion(vector<Vertice>v);
	void setEtapas(int n);
	_vertex3f RotarEjeY(_vertex3f p, double ang);
	void revolucionar(int v_inicial, int etapas);//acepta un vector
	void aplicaTextura(GLuint id);
	void aplicaTexturaManual(GLuint id);

};

class _obj_barrido : public _file_ply
{

private:
	int n_etapas;
	_vertex3f v;
public:
	_obj_barrido();
	_obj_barrido(int etapas,_vertex3f v);
	void build_barrido();
	int getVertices();
	void setEtapas(int n);
	_vertex3f transformar(_vertex3f transform,_vertex3f p);
	void makeBarrido(int v_inicial,_vertex3f transform,int etapas);

};

#endif
