#PRACTICAS usando librería OPENGL
##Practica 1: Figuras cubo y piramide (modo dibujado ajedrez,aristas,puntos,solido)
##Práctica 2: Modelo por revolucion y Objeto_ply
##Práctica 3: Modelo jerarquico
##Practica 4: Objetos iluminados por caras y vertices, objetos con texturas
Antonio Guzmán Martín

Cuando se ejecuta ./practica1
No es necesario para esta practica  meter plys por teclado, si se quiere cambiar los plys, cambiar file_ply_stl.c los por defecto
./ply/<archivo>.ply

IMPORTANTE LOS OBJETOS DE PRACTICA 1 Y 2 NO SE PINTAN HASTA QUE SE HAYA SELECCIONADO EL OBJETO A PINTAR Y EL MODO DE PINTADO

1)Seleccion de practica

Tecla 1: Se establece practica 1
  P1:FIGURAS
    Cubo:c
    Tetraedro: t
Tecla 2: Se establece practica 2
  P2:FIGURAS
    Objeto_ply: o
    Objeto_rev: l
Tecla 3: Se establece practica 3
  P3: el Modelo jerarquico se pinta en cuanto se pulsa 3

2) Modo a dibujar:

tecla a: alambre
tecla p: puntos
tecla e: aristas
tecla s: solido


Movimientos de la Practica 3:
//parte voluntaria 2 puntos extra.

Para mover el modelo jerarquico se usarán teclas:
Tecla r: giro la pluma a la dcha
Tecla l: giro la pluma a la iqda
Tecla t: mover carro pluma atrás
Tecla y: mover carro pluma adelante
tecla u: subir gancho de la pluma
tecla i: bajar gancho de la pluma


Movimientos Práctica 4:

NOTA:Para esta práctica se han usado dos funciones para aplicar textura uno automatico: "aplicatTextura(GLint)" perteneciente a la clase _triangulos3D y otro manual:
"aplicaTexturaManual(GLint)" perteneciente a la clase _obj_revolucion en file_ply_stl.cc

Tecla c: pintar escena con caras iluminadas
Tecla v: pintar escena con vertices iluminados
Tecla a: activar/desactivar luz (puede ser light0 o light1)
Tecla s: controlar light0
Tecla f: controlar light1
tecla h: activado/desactivado LIGHTNING (activado de luz SI NO SE DESACTIVA NO SE PUEDEN VER EL RESTO DE PRACTICAS,INICIALMENTE DESACTIVADA)
Tecla b: shadeModel FLAT o shadeModel SMOOTH, si es true la variable modo FLAT
tecla g: True: se activa la escena grua, FALSE se desactiva escena grua
Tecla X (shift+x): alpha++
Tecla C (shift+c): alpha--
Tecla A (shift+a): beta++
Tecla Z (shift+z): beta--

ejemplo de uso 4->v->h->a //visualizacion con light0 de los objetos modo Gouroud (normales vertices)

PARTE OPCIONAL
tecla g: True: se activa la escena grua, FALSE se desactiva escena grua

ejemplo: 4->h->a->g->v //visualizacion con light0 de los objetos modo Gouroud (normales vertices)
