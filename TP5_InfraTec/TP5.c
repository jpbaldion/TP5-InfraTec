#include <stdio.h>

//NOMBRE: Juan Pablo Baldion Castillo
//CODIGO: 202214765
//CORREO: j.baldion@uniandes.edu.co

void invertirVector(int *v, int length);
int reversarInt(int n);

int main(){
	int length;
	int *vector;
	int correcto = 1;
	
	while(correcto){
		// Se pide el tamaño del vector
		printf("Ingrese el tamano del vector que deseas reversar:\n");
		scanf("%i", &length);
		
		if(length > 0){
			correcto = 0;
			//Se crea el vector mediante reserva dinamica de memoria 
			vector = (int*) calloc(length, 4);
			//Se pregunta cada elemento del vector
			for (int i = 0; i < length; i++){
				printf("Ingrese elemento #%i del vector: ", i+1);
				scanf("%i", &vector[i]);
			}
			
			invertirVector(vector, length);
			// Se imprime el vector invertido
			for (int i = 0; i < length; i++){
				printf("%#X ", vector[i]);
			}
		}
	
	}
	
}

void invertirVector(int *v, int len){
	printf("Yes");
	__asm{
		mov ECX, 0
		mov EBX, len
		sar EBX, 1; ebx es igual a length/2
		mov EDX, v
		forInvertirVector:
			cmp ECX, EBX
			jge finInvertirVector
				mov EDI, [EDX + ECX*4] ; EDI = aux = v[i]

				mov EAX, len
				sub EAX, ECX
				sub EAX, 1
				imul EAX, 4
				mov ESI, [EDX + EAX] ; ESI = v[length-i-1]
				
				mov [EDX + ECX*4], ESI ; v[i] = v[length-i-1]
				mov [EDX + EAX], EDI
				inc ECX
				jmp forInvertirVector
		finInvertirVector:

	}
}
 

int reversarInt(int n){
	printf("Me llamaron");
    __asm{
		push EBP
		mov EBP, ESP
	
		push EBX
		push EDX
		push ECX
        mov EAX, 0 ; se incializa el registro EAX (registro de retorno por defecto en esta arquitectura) en 0 que representa el numero reversado que se va a costruyendo
        mov EBX, [EBP + 8] ; se mueve el parametro n al registro EBX
        
        mov ECX, 0 ; se inicializa ECX en 0 que representa el indice que me indica cuando parar el ciclo
        
		Ciclofor:
            cmp ECX, 32
            jge finCiclo ; si ECX es mayor o igual que 32 (numeros de bits de un int) para el ciclo
            inc ECX ; incrementamos en uno nuestro indice ECX
            shl EAX, 1 ; hacemmos un corrimiento hacia la izquierda de EAX
			mov EDX, EBX ;copiamos EBX en EDX para que en la siguiente linea del and no modifique EBX
            and EDX, 1 ; comprobamos si el bit menos significativo de EBX es uno o no
            jz salto
                or EAX, 1 ; si el bit menos significativo de EBX es uno cambiamos el bits menos significativo de EAX a uno
            salto:
                shr EBX, 1 ; se hace un corrimiento hacia la derecha de EBX
                jmp Ciclofor ; se repite el ciclo
        finCiclo:
		pop ECX
		pop EDX
		pop EBX
		pop EBP
		ret
    }
}