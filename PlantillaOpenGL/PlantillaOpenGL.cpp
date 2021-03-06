#pragma region LIBRERÍAS
// PlantillaOpenGL.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"

// Se usan <> para librerías que ya trae el sistema.
// GLEW y GLFW dependen de estas dos librerías, por eso se ponen antes de llamar al GLEW_STATIC.
#include <stdio.h>
#include <stdlib.h>

#define GLEW_STATIC

// Se usan "" para librerías personalizadas.
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <iostream>

using namespace std;
#pragma endregion

#pragma region VARIABLES
float posicionXTriangulo = 0.0f;
float posicionYTriangulo = 0.0f;
float angulo = 0.0f;

enum Direccion { Izquierda, Derecha, Arriba, Abajo };
Direccion direccionTrianguloH = Izquierda; //Horizontal
Direccion direccionTrianguloV = Abajo; //Vertical
#pragma endregion

#pragma region FUNCIONES PARA RUTINA DE DIBUJO
void dibujarTriangulo() {
	// Utilizar matriz identidad.
	glPushMatrix();


		//Transformaciones (el orden importa)
		//(angulo, x,     y,    z)
		/*glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
		glTranslatef(-0.25f, 0.0f, 0.0f);
		glScalef(0.2f, 0.2f, 0.2f);*/

		glTranslatef(posicionXTriangulo, posicionYTriangulo, 0.0f);
		glRotatef(angulo, 0.7f, 1.0f, 1.0f);

		//Dibujar los vertices
		glBegin(GL_TRIANGLES);

		glColor3f(1.0f, 0.8f, 0.0f);

		glVertex3f(-0.2f, -0.2f, 0);
		glVertex3f(0.2f, -0.2f, 0);
		glVertex3f(0.0f, 0.2f, 0);

		glEnd();

	// Soltar la matriz.
	glPopMatrix();
}

void dibujar() {
	dibujarTriangulo();
}

void actualizar() {
	if (angulo >= 360) {
		angulo = 0.0f;
	}
	angulo += 0.1f;

	if (direccionTrianguloH == Direccion::Izquierda) {
		if (posicionXTriangulo > -0.8f) {

			posicionXTriangulo -= 0.001f;

		}
		else {
			direccionTrianguloH = Direccion::Derecha;
		}
	}

	if (direccionTrianguloH == Direccion::Derecha) {
		if (posicionXTriangulo < 0.8f) {
			posicionXTriangulo += 0.001f;
		}
		else {
			direccionTrianguloH = Direccion::Izquierda;
		}
	}

	if (direccionTrianguloV == Direccion::Arriba) {
		if (posicionYTriangulo > -0.8f) {

			posicionYTriangulo -= 0.0005f;

		}
		else {
			direccionTrianguloV = Direccion::Abajo;
		}
	}

	if (direccionTrianguloV == Direccion::Abajo) {
		if (posicionYTriangulo < 0.8f) {

			posicionYTriangulo += 0.0005f;

		}
		else {
			direccionTrianguloV = Direccion::Arriba;
		}
	}
}
#pragma endregion

int main()
{
#pragma region CREAR UN CONTEXTO
	// Un contexto es una ventana de un sistema operativo.
	// OpenGL no gestiona el uso de ventanas.

	// Declaramos apuntador de ventana.
	GLFWwindow * window;

	// Condicionamos en caso de no poder iniciar el GLFW.
	if (!glfwInit()) 
		exit(EXIT_FAILURE);

	// Si GLFW puede iniciar entonces inicia la ventana.
	window = glfwCreateWindow(1024, 768, "Ventana", NULL, NULL);

	// Si puede iniciar GLFW pero no la ventana terminamos la ejecución.
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	// Establecemos el contexto, donde se mandarán los pixeles generados.
	glfwMakeContextCurrent(window);

	// Una vez establecido el contexto activamos funciones modernas.
	glewExperimental = true;
	GLenum errorGlew = glewInit();

	if (errorGlew != GLEW_OK)
	{
		cout << glewGetErrorString(errorGlew);
	}
#pragma endregion

	const GLubyte *versionGL = glGetString(GL_VERSION);
	cout << "Version OpenGL: " << versionGL;

#pragma region CICLO DE DIBUJO (DRAW LOOP)
	//El while establece que mientras la ventana esté abierta realice lo de su interior.
	while (!glfwWindowShouldClose(window)){
		// Establecemos región de dibujo.
		glViewport(0, 0, 1024, 768);
		// Establecemos color de borrado.
		glClearColor(0.5, 0, 0.5, 1);
		// Borramos.
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Rutina de dibujo.
		dibujar();
		actualizar();

		// Cambiar los buffers.
		glfwSwapBuffers(window);
		// Reconocer si hay entradas.
		glfwPollEvents();
	}

	// Para destruir ventana y borrarlo/liberarlo de la memoria.
	glfwDestroyWindow(window);
	glfwTerminate();
#pragma endregion

    return 0;
}

