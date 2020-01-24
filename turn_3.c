//
// 		turn_3.c		22.01.2020  Andrew M.
//
//	Implementation of a queue on an array through pointers

														
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX 10													//Ставим на 10 для простоты примера

int array[MAX] = {0};	
int* in = &array[0];												
int* out = &array[0];
int flag;								
int circle = 0;


 void queue_push(void) {										//Функция queue_push вводит значение 
	
	int value;
	
	if (flag) {													//При условии что массив не полный 
		
		printf("\n Queue overflow \n"); return;
	}
	
/* 	printf("\n		 Enter value  \n");

	scanf("%d", &value);
	
	*in = value;												//Принимаем значение и 	сохраняем по указателю in	
 */
	*in = rand();
	
	in ++;														//Увеличиваем значение указателя
 
	if (in == &array[MAX - 1]) {								//Проверяем, чтобы указатель перешел на начало массива, если он заполнен
		
		in = &array[0]; circle = 1;								//И ставим отметку, что круг по массиву пройден.
	}	
	
	if (in == out) {											//В случаем совпадения указателей in и out ставим флаг что массив полон.
		
		flag = 1;
	}
															 
 }

 int queue_pop(void) {											//Функция queue_out возвращает значение первого в очереди значения
	
	int value;
	
	if (in == out && circle == 0) {								//Проверяем что массив не пустой и круг не полный 
		
		printf("\n The queue is empty\n"); return 2;
	}
		
		flag = 0;												//Обнуляем флаг
		
		value = *out;											//Копируем значение по указателю out и печатаем его
		
		printf("\n Present value %d \n", value);
		
		out++;													//Увеличиваем значение указателя out
		
		if (out == &array[MAX - 1]) {							//Проверяем, чтобы указатель перешел на начало массива, если все значения в нем взяты
		
			out = &array[0]; circle = 0;						//Обнуляем отметку прохождения круга
		}
		
 return value;
}
	
 void queue_disp(void) {										// Функция queue_disp при условии что массив не пустой
	
	if(in == out && circle == 0) {
	
		printf("\n The queue is empty\n"); return;
	}	
	
	puts("\n	Values in queue:  \n");						
	
	int* j = out;
	
	do {
		
		printf("\n	  %d\n", *j);							//Отправляет на экран список значений стоящих в очереди
		
		j++;
	
		if (j == &array[MAX - 1]) 							//Проверяем, чтобы указатель перешел на начало массива, если все значения в нем взяты
		
			j = &array[0]; 
	
	} while (in != j);

 }	
	
 int main(void) {
	  
	char c;
	int counter = 0;
	
	printf("\n\n	Enter :  N - to add ;\n 	    	 O - for output;\n 		 D - to display the values in the queue;\n\
		 C - to display counter;\n		 E - to exit;\n");
	
	for( ;; ) {																			// В бесконечном цикле ждем ввода команд
			
		c = getchar();	

		c = toupper(c);															
					
			switch (c) {
			
			case 'N': queue_push(); counter++; break;									//Вызываем функцию queue_in и увеличиваем счетчик
			
			case 'O': queue_pop(); break;												//Вызываем функцию queue_out
			
			case 'D': queue_disp(); break;												//Вызываем функцию queue_disp
			
			case 'C': printf("\n 	%d\n", counter); break;								//Печатаем счетчик ввода значений
			
			case 'E': return 0;															//Выходим из программы	
			}
	}
	
  }
	
	
	
	
	
		
		