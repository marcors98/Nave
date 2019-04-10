#include "stdafx.h"
#include "Nave.h"

Nave::Nave() {
	angulo = 0.0f;
	coordenadas = vec3(0.0f, 0.0f, 0.0f);
	//Establece el valor como una matriz identidad
	transformaciones = mat4(1.0f);

	Vertice v1 = {
		vec4(0.0f,0.1f,0.0f,1.0f),
		vec4(0.0f,0.0f,1.0f,1.0f)
	};
	Vertice v2 = {
		vec4(-0.1f,-0.1f,0.0f,1.0f),
		vec4(1.0f,0.0f,0.0f,1.0f)
	};
	Vertice v3 = {
		vec4(0.1f,-0.1f,0.0f,1.0f),
		vec4(1.0f,0.0f,0.0f,1.0f)
	};

	vertices.push_back(v1);
	vertices.push_back(v2);
	vertices.push_back(v3);

}

void Nave::rotar(Direccion direccion) {
	float rotacion = velocidadAngular * tiempoDiferencial;
	if (rotacion < 0)
	{
		rotacion += 360;
	}
	if (direccion == Direccion::Derecha) {
		rotacion = -rotacion;


	}
	angulo += rotacion;
	actualizarMatrizTransformacion();
}

void Nave::avanzar() {
	float anguloDesfasado = angulo + 90.0f;

	if (velocidadActual <= velocidad) {
		velocidadActual += aceleracion;
	}


	vec3 traslacion = vec3(
		cos(anguloDesfasado * 3.14159 / 180.0f) * velocidadActual * tiempoDiferencial,//X
		sin(anguloDesfasado * 3.14159 / 180.0f) * velocidadActual * tiempoDiferencial,//Y
		0.0f
	);

	coordenadas += traslacion;

	actualizarMatrizTransformacion();

}

void Nave::detenerse()
{
	float anguloDesfasado = angulo + 90.0f;
	if (velocidadActual >= 0)
	{
		velocidadActual -= desaceleracion;
		if (velocidadActual < 0)
		{
			velocidadActual = 0.0f;
		}
	}
	vec3 translacion = vec3(
		cos(anguloDesfasado * 3.14159 / 180.0f) * velocidadActual * tiempoDiferencial,//X
		sin(anguloDesfasado * 3.14159 / 180.0f) * velocidadActual * tiempoDiferencial,//Y
		0.0f
	);

	coordenadas += translacion;

	actualizarMatrizTransformacion();
}
void Nave::actualizarMatrizTransformacion() {
	//Partir siempre de una matriz identidad
	transformaciones = mat4(1.0f);
	//Aplicar transformaciones
	transformaciones = translate(transformaciones, coordenadas);
	transformaciones = rotate(transformaciones, angulo * 3.14159f / 180.0f, vec3(0.0f, 0.0f, 0.1f));
}

void Nave::teletransportarOrillas()
{
	if (coordenadas.x > 1.00f)
	{
		coordenadas.x = -0.98f;
	}
	if (coordenadas.x < -1.00f)
	{
		coordenadas.x = 0.98f;
	}

	if (coordenadas.y > 1.00f)
	{
		coordenadas.y = -0.98f;
	}
	if (coordenadas.y < -1.00f)
	{
		coordenadas.y = 0.98f;
	}

}

void Nave::tiempo() {
	tiempoActual = glfwGetTime();
	tiempoDiferencial = tiempoActual - tiempoAnterior;
}