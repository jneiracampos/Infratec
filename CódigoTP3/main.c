#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//NOMBRE: Paula Cecilia Daza Díaz
//CODIGO: 202111276
//CORREO: p.dazad@uniandes.edu.co

void main()
{
    int tamanioVector; //Se declara la variable que guarda el tamaño del vector
    bool continuar = false; //Se declara la variable que permite que el programa le vuelva a preguntar al usuario el tamaño del vector si se inicializó menor o igual a 0.
    
    //--Programa--//
    printf("\n* - PROGRAMA DE VECTORES - * \n");
    do
    {
    printf("\nIngrese por favor el tamaño del vector: \n");
    scanf("%d", &tamanioVector); //Se inicializa la variable del tamaño del vector.
    if (tamanioVector <= 0) //Se valida que sea mayor a 0.
    {
        printf("El valor del tamaño debe ser mayor a 0. \n");
        continuar = true;
    }else
    {
        continuar = false; //Se termina el "ciclo", pues ya se validó que el tamaño del vector es mayor a 0.

        int *vectorInt = (int*)calloc(tamanioVector,sizeof(int)); //Se declara e inicializa el apuntador al vector de int.
        char *vectorCadena = (char*)calloc(tamanioVector*8,sizeof(char)); //Se declara e inicializa el apuntador a la cadena de char.
        
        printf("\nIngrese por favor la cadena de caracteres: \n");
        scanf("%s", vectorCadena);//Se inicializa la cadena

        printf("El vector de int tamaño %d queda representado así: \n", tamanioVector);
        empaquetamiento(vectorInt, tamanioVector, vectorCadena); //Se invoca el procedimiento que empaqueta la cadena en el vector y se imprime.
    }
    }while(continuar==true);
}// main

//Procedimiento que empaqueta la cadena en el vector y la imprime:
int empaquetamiento(int *vectorInt, int tamanio, char *cadena){

    int lenCadena = strlen(cadena);

    //Inicia recorrido de la cadena para convertir de decimal a binario en un byte.
          for (int i = 0; i < lenCadena; i++)
    {
        if (cadena[i] > 64)
        {
            cadena[i] = cadena[i] - 55;
        }else
        {
            cadena[i] = cadena[i] - 48;
        }    
    }

    __asm{
        mov ebx, 0
        loopFor:
            mov eax, cadena[ebx]
            cmp eax, 64
            jl menor64
            sub eax, 55
            jmp done
        
        menor64:
            sub eax, 48

        done:
        inc ebx
        cmp ebx, lenCadena
        jl loopFor
    }
    
    for (int i = 0; i < tamanio; i++)
    {
        int caracter = cadena[i*8];
        for (int j = 1 + (i*8); j < 8 + (i*8); j++)
        {
            caracter = caracter << 4; //Se desplaza a la izquierda ya que los hexa son de 4 bits.
            caracter |= cadena[j]; //Se añade el nuevo hexa.
        }
        vectorInt[i] = caracter;  //Finalmente, se agrega el caracter que se modificó a la posición i del vector.
    }

    //Se recorre el vector para imprimir cada elemento por línea.
    for (int i = 0; i < tamanio; i++)
    {
        printf("v[%i] = 0x%08X\n", i, vectorInt[i]);
    }
    
    return 0;

}
    
