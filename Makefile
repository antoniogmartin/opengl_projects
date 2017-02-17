# fichero Makefile
#
# nombre del fichero ejecutable
#
TARGET1= practica1

# banderas para el compilador (C y C++). Se indican los directorios donde se puenden
# encontrar ficheros para incluir mediante la opcion -I
# la opcion -g sirve para permitir la depuraci�n
#

# g++ -c practica1 practica1.cc -g -DXWINDOWS -DSHM -I/usr/include -I.
#generacion .o
CFLAGS=    -g -DXWINDOWS -DSHM -I/usr/include -I. -c
CCFLAGS=  -g -DXWINDOWS -DSHM -I/usr/include -I. -c

#generacion bin
CXXFLAGS=  -g -DXWINDOWS -DSHM -I/usr/include -I.

# banderas pra el enlazador
# Se indica directorios donde encontrar las funciontecas con -L. Usando -l seguido del
# nombre se indica la funcionteca que se desea enlazar.
#
LDFLAGS=  -lGLU -lGL -lglut -ljpeg

# definicion del compilador
#
CC = g++

# orden que sera ejecutada por defecto
#
all : $(TARGET1)

# regla de ejecucion
#
jpg_imagen.o: jpg_imagen.cpp jpg_imagen.hpp jpg_readwrite.hpp
		$(CC) $(CCFLAGS) jpg_imagen.cpp
jpg_memsrc.o: jpg_memsrc.cpp jpg_memsrc.hpp jpg_jinclude.h
		$(CC) $(CCFLAGS) jpg_memsrc.cpp
jpg_readwrite.o: jpg_readwrite.cpp jpg_readwrite.hpp
		$(CC) $(CCFLAGS) jpg_readwrite.cpp

file_ply_stl.o: file_ply_stl.cc file_ply_stl.h objetos.h vertex.h
	$(CC) $(CCFLAGS) file_ply_stl.cc

objetos.o: objetos.cc objetos.h jpg_imagen.hpp jpg_jinclude.h
	$(CC) $(CCFLAGS)  objetos.cc
grua.o: grua.cc grua.h objetos.h jpg_imagen.hpp jpg_jinclude.h
	$(CC) $(CCFLAGS)  grua.cc

textura.o:textura.cc textura.h jpg_imagen.hpp
	$(CC) $(CCFLAGS)  textura.cc

practica1.o: practica1.cc objetos.h textura.h file_ply_stl.h grua.h jpg_imagen.hpp vertex.h
	$(CC) $(CCFLAGS)  practica1.cc



#ejecutable

$(TARGET1) : practica1.o objetos.o file_ply_stl.o grua.o jpg_imagen.o jpg_memsrc.o jpg_readwrite.o textura.o
	$(CC) -o $@  $(CXXFLAGS) practica1.o objetos.o file_ply_stl.o grua.o jpg_imagen.o jpg_memsrc.o jpg_readwrite.o textura.o $(LDFLAGS)


#
#
clean:
	rm -f *.o
	rm -f $(TARGET1)

#
#
redo:
	touch *.cc
	make

#
#
superclean:
	rm -f *.o
	rm *~
	rm -f $(TARGET1)


#
tgz:
	rm -f *.o
	rm *~
	rm -f $(TARGET1)
	tar -zcvf $(TARGET1).tgz *
