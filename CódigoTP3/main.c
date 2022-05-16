#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//NOMBRE: Paula Cecilia Daza Díaz
//CODIGO: 202111276
//CORREO: p.dazad@uniandes.edu.co

//NOMBRE: Sofia Torres Ramirez
//CODIGO: 202014872
//CORREO: s.torres21@uniandes.edu.co

//NOMBRE: Juan Camilo Neira Campos
//CODIGO: 201922746
//CORREO: j.neira@uniandes.edu.co

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
         /* for (int i = 0; i < lenCadena; i++)
    {
        if (cadena[i] > 64)
        {
            cadena[i] = cadena[i] - 55;
        }else
        {
            cadena[i] = cadena[i] - 48;
        }    
    }*/

    __asm{
        mov ebx, cadena // ebx = cadena
        mov eax, 0 //contador
        loopFor:
            movzx cl, [ebx+eax]//cl = cadena[i]
            cmp cl,0 
            je done

            cmp cl, 64 // compara cadena[i] con 64
            jl menor64 // cadena[i] < 64? Salta si es menor
                sub cl, 55  // le resta a cadena[i] 55 
                mov [ebx+eax], cl //cadena[i] = cadena[i] -55
                jmp done 
            menor64:
                sub cl, 48 // le resta a cadena[i] 48 
                mov [ebx+eax], cl //cadena[i] = cadena[i] -48

            done:

            add eax,1 //incrementa contador
            cmp eax,lenCadena // contador < lenCadena?
            je fin // Si es igual finaliza
            jl loopFor // Si es menor continua el bucle
        fin:
    }
    
    for (int i = 0; i < tamanio; i++)
    {
        int caracter = cadena[i*8];
        for (int j = 1 + (i*8); j < 8 + (i*8); j++)
        {
            caracter = caracter << 4; //Se desplaza a la izquierda ya que los hexa son de 4 bits.
            caracter |= cadena[j]; //Se añade el nuevo hexa.
            caracter  = cadena[j] | caracter
        }
        vectorInt[i] = caracter;  //Finalmente, se agrega el caracter que se modificó a la posición i del vector.
    }

    int i = 0;

    __asm{
        firstLoop:
            move eax, 0 //i
            imul eax, 8 //i * 8
            mov ebx, cadena[eax] //Caracter
            loop:
                mov ecx, 1
                add ecx, eax //j
                shl ebx, 4
                OR cadena[ecx], ebx
                inc ecx
                mov edx, 8
                add edx, eax
                cmp ecx, edx //j < 8 + (i * 8)
                jl loop
            mov vectorInt[eax], ebx
            inc eax
            mov edx, tamanio
            cmp eax, edx
            jl firstLoop

    }

    //Se recorre el vector para imprimir cada elemento por línea.
    for (int i = 0; i < tamanio; i++)
    {
        printf("v[%i] = 0x%08X\n", i, vectorInt[i]);
    }
    
    return 0;

}   
