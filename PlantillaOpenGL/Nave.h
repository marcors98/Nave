#pragma once
#include "Modelo.h"
#include "glm/gtx/transform.hpp"
#include "glm/glm.hpp"

class Nave : public Modelo {
public:
	Nave();
	vec3 coordenadas;
	enum Direccion { Izquierda, Derecha };
	float angulo;
	float velocidadAngular = 280.0f;
	float velocidad = 1.7f;
	float aceleracion = 0.03f;
	float desaceleracion = 0.05f;
	float velocidadActual = 0.0f;
	void rotar(Direccion direccion);
	void avanzar();
	void detenerse();
	void actualizarMatrizTransformacion();
	void tiempo();
	void teletransportarOrillas();
	double tiempoAnterior = 0.0f;
	double tiempoActual = 0.0f;
	double tiempoDiferencial = 0.0f;
};
