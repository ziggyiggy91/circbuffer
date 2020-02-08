#include <stdio.h>
#include <stdlib.h>

int input = 0;
char select;
//char buff[10];

struct c_buff{
	int index;
	int size;
	int *buff;
	int head;
	int tail;
	int full;
	int empty;
 	
};

void init_cir_buff(struct c_buff *buffPtr);
void enque(struct c_buff *buffPtr, int input);
int isFull(struct c_buff *buffPtr);
int isEmpty(struct c_buff *buffPtr);
 
void init_cir_buff(struct c_buff *buffPtr){
	buffPtr->index = 0;
	buffPtr->size = 30;
	buffPtr->head = 0;
	buffPtr->tail = 0;
	buffPtr->buff = malloc(buffPtr->size*sizeof(buffPtr->buff));;
 }

void enque(struct c_buff *buffPtr, int input){	
	//do not populate buffer when full
	if(isFull(buffPtr) == 0){
	  *((buffPtr->buff) + buffPtr->index) = input;
	  buffPtr->index = (buffPtr->index + 1)%buffPtr->size;
	  buffPtr->tail =  (buffPtr->tail + 1)%buffPtr->size;
	}else{
		printf("FIFO is full\n\r");
		
	}
	
}



int dequeue(struct c_buff *buffPtr){
	
	int dequeue = 0;
	//pop data then increment head, also increase the tail index. 
	if(isEmpty(buffPtr) == 0){
		dequeue = *((buffPtr->buff) + buffPtr->head);
		buffPtr->head = (buffPtr->head + 1)%(buffPtr->size);
	}
	else {
		printf("FIFO is empty\n\r");
		dequeue = 0;
	}
	
 	return dequeue;
}


int isEmpty(struct c_buff *buffPtr){
	if(buffPtr->head%buffPtr->size == buffPtr->tail%buffPtr->size){
 		buffPtr->empty = 1;
	}
	else
		buffPtr->empty = 0;
	
	return buffPtr->empty;
}

int isFull(struct c_buff *buffPtr){
 	if((buffPtr->tail + 1 )%(buffPtr->size) == buffPtr->head){
 		buffPtr->full = 1;
 	}
	else{
 		buffPtr->full = 0;
	}
	return buffPtr->full;
}

int main(){
	
 	struct c_buff *buffer = malloc(sizeof(struct c_buff));
	int i;
 	init_cir_buff(buffer);
  
	while(1){
	//Enter data in buffer:
	 printf("w: Write to buffer\n\r");
	 printf("r: Read from buffer\n\r");
	 printf("p: print  buffer\n\r");
	 scanf("%c",&select);	
     switch(select){
	 case 'w':while(input != -1){
		printf("Write to buffer\n\r");
		scanf("%d",&input);		
		printf("%d \n\r",input);
		enque(buffer, input);
	 }
	 input = 0;
	 break;
	 case 'r': 
		printf("Read from buffer\n\r");
 		printf("buff[%d]: %d \n\r", buffer->head - 1,dequeue(buffer));
 	 break;
	 case 'p':
		for(i = 0; i < buffer->size; i = i + 1){
			if(i == buffer->head)
			printf("buff[%d]: %d <-HEAD\n\r", i,*((buffer->buff) + i));
			else if(i == buffer->tail)
			printf("buff[%d]: %d <-TAIL\n\r", i,*((buffer->buff) + i));
			else
			printf("buff[%d]: %d\n\r", i,*((buffer->buff) + i));
		}
	break;
	 }
	}
	free(buffer);
	
}

 