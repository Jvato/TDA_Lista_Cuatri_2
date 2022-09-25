#include "src/lista.h"
#include "src/pila.h"
#include "src/cola.h"
#include <stdio.h>
#include <stdlib.h>
#include "pa2m.h"

/*
 * PRUEBAS CREAR LISTA
 */

void lista_se_crea_vacia()
{
	lista_t *lista = lista_crear();
	pa2m_afirmar(lista_vacia(lista) == true, "La lista creada esta inicialmente vacia");	
	pa2m_afirmar(lista_primero(lista) == NULL, "La lista creada no tiene primer elemento");
	pa2m_afirmar(lista_ultimo(lista) == NULL, "La lista creada no tiene ultimo elemento");
	pa2m_afirmar(lista_tamanio(lista) == 0, "La lista creada tiene cero elementos");
	lista_destruir(lista);
}

/*
 * PRUEBAS DESTRUIR LISTA
 */

void lista_con_elementos_estaticos_se_destruye_correctamente()
{
	lista_t *lista = lista_crear();
	int a =3;
	void *_a = &a;
	bool OK = lista_insertar(lista,_a) != NULL;
	OK = OK && (lista_insertar(lista,_a) != NULL);
	OK = OK && (lista_insertar(lista,_a) != NULL);
	OK = OK && (lista_insertar(lista,_a) != NULL);
	pa2m_afirmar(OK, "se insertaron 4 elementos, creados con memoria estatica, correctamente");
	pa2m_afirmar(lista_tamanio(lista) == 4, "la lista tiene 4 elementos");
	lista_destruir(lista);
	pa2m_afirmar(true,"Se destruyo la lista");
}

void lista_con_elementos_dinamicos_se_destruye_correctamente()
{
	lista_t *lista = lista_crear();
	int *_a1 = malloc(sizeof(int));
	int *_a2 = malloc(sizeof(int));
	int *_a3 = malloc(sizeof(int));
	int *_a4 = malloc(sizeof(int));
	bool OK = lista_insertar(lista,_a1) != NULL;
	OK = OK && (lista_insertar(lista,_a2) != NULL);
	OK = OK && (lista_insertar(lista,_a3) != NULL);
	OK = OK && (lista_insertar(lista,_a4) != NULL);
	pa2m_afirmar(OK, "se insertaron 4 elementos, creados con malloc, correctamente");
	pa2m_afirmar(lista_tamanio(lista) == 4, "la lista tiene 4 elementos");
	lista_destruir_todo(lista,free);
	pa2m_afirmar(true,"Se destruyo la lista y se libero la memoria de los 4 elementos");
}


/*
 * PRUEBA INSERTAR ELEMENTOS
 */

void lista_cambia_de_estado_cuando_agrego_un_elemento_por_primera_vez()
{
	lista_t *lista = lista_crear();
	int aux = 2;
	void *_aux = &aux;
	pa2m_afirmar(lista_vacia(lista) == true, "La Lista esta inicialmente vacia");
	pa2m_afirmar(lista_insertar(lista,_aux) != NULL, " Se inserta un elemento con lista_insertar correctamente");
	pa2m_afirmar(lista_vacia(lista) == false, "La lista cambio de estado \"vacio\" a estado \"no vacio\" luego de agregar un elemento");
	pa2m_afirmar(lista_tamanio(lista) == 1, "el tamaño actual de la lista es 1");
	lista_destruir(lista);
}

void lista_insertar_elementos_en_diferentes_posiciones()
{
	lista_t *lista = lista_crear();
	int a1 = 1;
	void *_a1 = &a1;
	pa2m_afirmar(lista_insertar_en_posicion(lista,_a1,0) != NULL, "Se inserto un elemento en la posicion 0");
	pa2m_afirmar(lista_insertar(lista,_a1) != NULL, " Se inserta un elemento con lista_insertar correctamente");
	pa2m_afirmar(lista_insertar_en_posicion(lista,_a1,1) != NULL, "Se inserto un elemento en la posicion 1");
	pa2m_afirmar(lista_insertar_en_posicion(lista,_a1,1) != NULL, "Se inserto un elemento en la posicion 1");
	pa2m_afirmar(lista_insertar(lista,_a1) != NULL, " Se inserta un elemento con lista_insertar correctamente");
	pa2m_afirmar(lista_insertar_en_posicion(lista,_a1,2) != NULL, "Se inserto un elemento en la posicion 2");
	pa2m_afirmar(lista_insertar_en_posicion(lista,_a1,2) != NULL, "Se inserto un elemento en la posicion 2");
	pa2m_afirmar(lista_insertar_en_posicion(lista,_a1,100) != NULL, "Se inserto un elemento en la posicion 100");
	pa2m_afirmar(lista_insertar(lista,_a1) != NULL, " Se inserta un elemento con lista_insertar correctamente");
	lista_destruir(lista);
}


void lista_inserta_elementos_NULL()
{
	lista_t *lista = lista_crear();
	pa2m_afirmar(lista_insertar_en_posicion(lista,NULL,0) != NULL, "Se inserto NULL en la posicion 0");
	pa2m_afirmar(lista_insertar(lista,NULL) != NULL, "Se inserta NULL con lista_insertar correctamente");
	pa2m_afirmar(lista_insertar_en_posicion(lista,NULL,1) != NULL, "Se inserto NULL en la posicion 1");
	pa2m_afirmar(lista_insertar_en_posicion(lista,NULL,1) != NULL, "Se inserto NULL en la posicion 1");
	pa2m_afirmar(lista_insertar(lista,NULL) != NULL, "Se inserta NULL con lista_insertar correctamente");
	pa2m_afirmar(lista_insertar_en_posicion(lista,NULL,2) != NULL, "Se inserto NULL en la posicion 2");
	pa2m_afirmar(lista_insertar_en_posicion(lista,NULL,2) != NULL, "Se inserto NULL en la posicion 2");
	pa2m_afirmar(lista_insertar_en_posicion(lista,NULL,100) != NULL,"Se inserto NULL en la posicion 100");
	pa2m_afirmar(lista_insertar(lista,NULL) != NULL, "Se inserta NULL con lista_insertar correctamente");
	lista_destruir(lista);
}

void lista_con_un_elemento_tiene_primero_y_ultimo_igual()
{
	int *a = malloc(sizeof(int));
	lista_t *lista = lista_crear();
	pa2m_afirmar(lista_vacia(lista) == true, "La lista esta inicialmente vacia");
	pa2m_afirmar(lista_insertar(lista,a) != NULL, "Se inserto un elemento a la lista");
	pa2m_afirmar((lista_primero(lista) == a) && (lista_ultimo(lista) == a), "El unico elemento de la lista es el primero y el ultimo elemento de la lista");
	lista_destruir_todo(lista,free);
}

void lista_verificar_ultimo_elemento_agregado()
{
	lista_t *lista = lista_crear();
	int *vector[3];
	for (size_t i = 0; i < 3; i++)
		vector[i] = malloc(sizeof(int));
	for (size_t i = 0; i < 3; i++)
	{
		pa2m_afirmar(lista_insertar(lista,vector[i]) != NULL, "Se inserto un elemento al final correctamente");
		pa2m_afirmar(lista_ultimo(lista) == vector[i], "El ultimo elemento agregado es igual al valor devuelto por lista_ultimo");
	}
	lista_destruir_todo(lista,free);
}

void lista_verificar_primer_elemento_agregado()
{
	lista_t *lista = lista_crear();
	int *vector[3];
	for (size_t i = 0; i < 3; i++)
		vector[i] = malloc(sizeof(int));
	for (size_t i = 0; i < 3; i++)
	{
		pa2m_afirmar(lista_insertar_en_posicion(lista,vector[i],0) != NULL, "Se inserto un elemento en la posicion 0");
		pa2m_afirmar(lista_primero(lista) == vector[i], "El primer elemento agregado es igual al valor devuelto por lista_primero");
	}
	lista_destruir_todo(lista,free);
}


void lista_insertar_en_posicion_mayor_al_tamano(){
	int *a = malloc(sizeof(int));
	int *b = malloc(sizeof(int));
	lista_t *lista = lista_crear();
	pa2m_afirmar(lista_insertar_en_posicion(lista,a,100) != NULL, "Se inserta un elemento en la posicion 100 (mayor al tamaño actual de la lista)");
	pa2m_afirmar(lista_ultimo(lista) == a, "El ultimo elemento de la lista coincide con el que se agrego en la posicion 100)");

	pa2m_afirmar(lista_insertar_en_posicion(lista,b,100) != NULL, "Se inserta un elemento en la posicion 100 (mayor al tamaño actual de la lista)");
	pa2m_afirmar(lista_ultimo(lista) == b, "El ultimo elemento de la lista coincide con el que se agrego en la posicion 100)");

	lista_destruir_todo(lista,free);
}


/*
 * Pruebas quitar elementos
 */

void lista_agregar_quitar_misma_cantidad_de_elementos()
{
	lista_t *lista = lista_crear();
	int a = 2;
	void *_a = &a;
	bool OK = true;
	for (size_t i = 0; i < 10; i++)
		OK = OK && (lista_insertar_en_posicion(lista,_a,i) != NULL);
	pa2m_afirmar(OK,"Se agregaron 10 elementos a la lista correctamente");
	pa2m_afirmar(lista_tamanio(lista) == 10, "la cantidad de elementos en la lista es 10");
	for (size_t i = 0, OK = true; i < 10; i++)
		OK = OK && (lista_quitar(lista) != NULL);
	pa2m_afirmar(OK, "Se quitaron 10 elementos correctamente");
	pa2m_afirmar(lista_tamanio(lista) == 0, "la cantidad de elementos en la lista es 0");
	lista_destruir(lista);
}

int main()
{
	pa2m_nuevo_grupo("Pruebas de creación de lista");
	lista_se_crea_vacia();
	
	pa2m_nuevo_grupo("Pruebas destruir lista con elementos en meoria estatica");
	lista_con_elementos_estaticos_se_destruye_correctamente();

	pa2m_nuevo_grupo("Pruebas destruir lista con elementos en meoria dinamica");
	lista_con_elementos_dinamicos_se_destruye_correctamente();

	pa2m_nuevo_grupo("Pruebas insertar elemento por primera vez");
	lista_cambia_de_estado_cuando_agrego_un_elemento_por_primera_vez();

	pa2m_nuevo_grupo("Pruebas insertar elementos en diferentes posiciones");
	lista_insertar_elementos_en_diferentes_posiciones();

	pa2m_nuevo_grupo("Pruebas insertar elementos NULL en diferentes posiciones");
	lista_inserta_elementos_NULL();

	pa2m_nuevo_grupo("Lista con un unico elemento agregado tiene como primer y ultimo elemento el mismo");
	lista_con_un_elemento_tiene_primero_y_ultimo_igual();

	pa2m_nuevo_grupo("Prueba verificar que el ultimo elemento agregado es igual al ultimo elemento obtenido con lista_ultimo");
	lista_verificar_ultimo_elemento_agregado();

	pa2m_nuevo_grupo("Prueba insertar elementos en una posicion mayor al tamaño actual de la lista, lo deberia agregar al final");
	lista_insertar_en_posicion_mayor_al_tamano();

	pa2m_nuevo_grupo("Prueba verificar que el primer elemento agregado es igual al primer elemento obtenido con lista_primero");
	lista_verificar_primer_elemento_agregado();

	pa2m_nuevo_grupo("Pruebas quitar elementos de la lista");
	lista_agregar_quitar_misma_cantidad_de_elementos();

	return pa2m_mostrar_reporte();
}
