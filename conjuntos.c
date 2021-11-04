#include <stdio.h>

#define MAX 100

typedef struct{
    int datos[MAX];
    int tam;
} Conjunto;   // Set

void inicializaConjunto(Conjunto *conjunto);
int existeElemento(Conjunto conjunto, int dato);
void insertaEnOrden(Conjunto *pConjunto, int dato);
void insertaElemento(Conjunto *pConjunto, int dato);
Conjunto unionConjunto(Conjunto A, Conjunto B);
Conjunto interseccion(Conjunto A, Conjunto B);

int main()
{
    Conjunto A, B, C;
    int dato = 10;
    int existe = 0;

    inicializaConjunto(&A);
    inicializaConjunto(&B);

    A.datos[0] = 10;
    A.datos[1] = 15;
    A.datos[2] = 20;
    A.datos[3] = 25;
    A.datos[4] = 30;
    A.datos[5] = 35;
    A.datos[6] = 40;
    A.datos[7] = 45;

    A.tam = 8;

    insertaElemento(&B, 5);
    insertaElemento(&B, 17);
    insertaElemento(&B, 33);
    insertaElemento(&B, 25);
    insertaElemento(&B, 40);
    insertaElemento(&B, 10);

    //C = unionConjunto(A, B);
    C = interseccion(A, B);
    
    return 0;
}

// Intersección de conjuntos
// - Recibe dos conjuntos A y B
// - Regresa un nuevo conjunto C
// 1.  Crea el nuevo conjunto
// 2.  Recorre los datos de un conjunto
//      preguntando si ese dato está en el otro conjunto
//      2.1 Si está, inserta el dato en C
//      2.2 Si no, no hace nada
// 3.  Regresa C

Conjunto interseccion(Conjunto A, Conjunto B)
{
    Conjunto C;
    int i;

    inicializaConjunto(&C);

    for(i = 0; i < A.tam; i++)
    {
        if(existeElemento(B, A.datos[i]) == 1)
        {
            insertaElemento(&C, A.datos[i]);
        }
    }

    return C;
}


// Unión de conjuntos
//  - Recibe dos conjuntos A y B
//  - Regresa un nuevo conjunto C
//  1.  Crear el nuevo conjunto
//  2.  Insertar en C los elementos de A
//  3.  Insertar en C los elementos de B que no existan en C 
//      3.1.  Conforme insertemos vamos aumentando el tamaño de C

Conjunto unionConjunto(Conjunto A, Conjunto B)
{
    Conjunto C;
    int i;

    inicializaConjunto(&C);

    for(i = 0; i < A.tam; i++)
    {
        C.datos[i] = A.datos[i];
        C.tam++;

        //insertaElemento(&C, A.datos[i]);
    }
    int j = C.tam;

    for(i = 0; i < B.tam; i++)
    {
        insertaElemento(&C, B.datos[i]);
    }

    return C;
}


// Eliminación - Recibe el dato que queremos eliminar:
//     1.  Si el conjunto tiene datos
//     2.  Buscamos si el elemento que queremos eliminar existe
//         2.1  Si si existe, entonces recorremos todos los elementos mayores a el una posición abajo

// Inserta elemento:
//     1.  Si hay espacio en el arreglo
//     2.  Buscar si el nuevo elemento existe dentro del arreglo  (búsqueda binaria)
//         2.1 Si existe no hace nada
//         2.2 Si no existe, va a insertar el elemento en orden
//          2.2.1 Va a aumentar el tamaño del conjunto (tam++)

void insertaElemento(Conjunto *pConjunto, int dato)
{
    if(pConjunto->tam < MAX) // Hay espacio
    {
        if(!existeElemento(*pConjunto, dato))
        {
            insertaEnOrden(pConjunto, dato);  
        }
    }
}

// Existe elemento:
//     1.  Buscar dentro del arreglo del conjunto el dato
//      1.1 Si lo encuentra regresa un 1
//      1.2 Si no lo encuentra regresa un 0

int existeElemento(Conjunto conjunto, int dato)
{
    int encontro = 0;
    int centro;
    int izq = 0;
    int der = conjunto.tam - 1;

    while(encontro == 0 && izq < der)
    {
        centro = izq + (der - izq) / 2;

        if(conjunto.datos[centro] == dato)
            encontro = 1;
        else
            if(conjunto.datos[centro] > dato)
                der = centro - 1;
            else
                izq = centro + 1;
    }

    return encontro;
}


// Inserta en orden
//     1.  Buscar la posición en donde le toca estar al nuevo elemento
        // 1.1  Va a recorrer todos los elementos que están dentras de esa posición
        // 1.2  Va a insertar el nuevo valor
        // 1.3  Incrementar tam

        // 1 3 6 8   -   5
        // 1 3 5 6 8
void insertaEnOrden(Conjunto *pConjunto, int dato)
{
    int indice = pConjunto->tam - 1;

    while(indice >= 0 && pConjunto->datos[indice] > dato)
    {
        pConjunto->datos[indice + 1] = pConjunto->datos[indice];
        indice--;
    }

    pConjunto->datos[indice + 1] = dato;
    pConjunto->tam++;
}



void inicializaConjunto(Conjunto *conjunto)
{
    conjunto->tam = 0;
}
