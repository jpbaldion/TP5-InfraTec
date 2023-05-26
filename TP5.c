#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

//NOMBRE: Juan Pablo Baldion Castillo
//CODIGO: 202214765
//CORREO: j.baldion@uniandes.edu.co

//NOMBRE: Wilmer Manuel Arévalo González
//CODIGO: 202214720
//CORREO: w.arevalo@uniandes.edu.co

//NOMBRE: Sara Sofía Cárdenas Rodríguez
//CODIGO: 202214907
//CORREO: ss.cardenas@uniandes.edu.co

void invertirVector(int *vector, int n);
int reversarInt(int num);

int main() {
    int n;

    printf("Ingrese el tamanio del vector a reversar: ");
    scanf("%d", &n);

    // Validar que n > 0
    while (n <= 0) {
        printf("El tamaño del vector debe ser mayor que 0. Ingrese nuevamente: ");
        scanf("%d", &n);
    }

    // Reservar memoria para el vector
    int *vector = (int*) calloc(n, sizeof(int));

    // Pedir los valores de cada elemento
    printf("Ingrese los valores del vector:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &vector[i]);
    }

    // Invertir el vector
    invertirVector(vector, n);

    // Imprimir el vector en hexadecimal en orden inverso
    printf("El vector invertido en hexadecimal es:\n");
    for (int i = n - 1; i >= 0; i--) {
        printf("0x%X ", vector[i]);
    }
    printf("\n");

    // Liberar memoria del vector
    free(vector);

    return 0;
}

void invertirVector(int *vector, int n) {
    __asm{
		push ebx
		push esi
		push edi

		mov edi, [ebp+8]    			//; vector
		mov esi, [ebp+12]   			//; n
		mov ebx, 0						//; i = 0

		loop_start:
			cmp ebx, esi       			//; i < n
			jge loop_end      		 	//; Salta al final si i >= n

			mov edx, [edi + ebx * 4]   //; vector[i]
			push edx                   //; Guarda vector[i] en la pila como parametro
			call reversarInt           //; Llama a la función reversarInt
			add esp, 4                 //; Ajusta el puntero de la pila después de la llamada

			mov [edi + ebx * 4], eax   //; vector[i] = reversarInt(vector[i])

			add ebx, 1					//; Incrementa i
			jmp loop_start             	//; Salta al inicio del bucle

		loop_end:
		pop edi
		pop esi
		pop ebx
	}
}

int reversarInt(int num) {
    __asm {
        mov eax, num // Se mueve el valor del argumento num al registro eax
        mov ecx, 0 // Se mueve el valor 0 al registro ecx que se usa como contador
        mov ebx, 0 // Se inicializa el registro ebx en cero, este será el registro que contendrá el número invertido
		loop_start: // Etiqueta para el loop
            cmp ecx, 32		// Se compara ecx con 32, porque un entero ocupa 32 bits
            jge loop_end	// Si ecx>=32 sale del ciclo
            shr eax, 1 // Se desplaza hacia la derecha el contenido de eax, eliminando el bit menos significativo
            rcl ebx, 1 // Se rota el contenido de ebx hacia la izquierda, el bit más significativo se convierte en el menos significativo
            inc ecx		// Se incrementa ecx
            jmp loop_start
        loop_end:
		mov num, ebx // Se mueve el contenido del registro ebx al argumento num
		mov eax, num	//Se mueve num a eax para retornarlo
    }
}