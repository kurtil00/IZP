#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct intPole {
    int* array;
    int length;
    int used_size;
} intPole;


void print_array(intPole *array){
    printf("array: {");
    int count;
    for(count = 0; count < array->length; count++){
        printf("%d", array->array[count]);
        if(count < array->length-1){
            printf(",");
        }
    }
    printf("} size: %d ; used: %d\n", array->length, array->used_size);
}


intPole create_array(int size){
    intPole array;
    array.array = malloc(size);
    array.length = size;
    array.used_size = 0;
    return array;
}

void free_array(intPole *array){
    free(array->array); //problemovy radek
    array->array = NULL;
}

void add_item(intPole *array, int item){
    if(array->length == array->used_size){
        array->length *= 2;
        array->array = realloc(array->array, array->length*sizeof(int));
    }

    array->array[array->used_size] = item;
    array->used_size += 1;
}

void remove_item(intPole *array, int index){
    int count;
    for(count = index; count < array->used_size-1; count++){
        array->array[count] = array->array[count+1];
    }
    array->used_size -= 1;
}
void remove_all(intPole *array){
    int count;
    for(count = 0; count < array->used_size-1; count++){
        array->array[count] = 0;
    }
    array->used_size = 0;
}

int find_item(intPole array, int item){
    int count;
    for(count = 0; count < array.used_size; count++){
        if(array.array[count] == item){
            return count;
        }
    }
    return -1;
}

int main(int argc, char** argv){

    intPole pole;
    pole = create_array(3);

    int i;
    for(i = 1; i < 10; i++){
        // if(!add_item(&pole, i))
        // {
        //     printf("Chyba\n");
        // }
        add_item(&pole, i);
    }
    print_array(&pole);

    remove_item(&pole, 2);

    int item_index = find_item(pole, 7);
    printf("\nItem_index: %d\n", item_index);

    free_array(&pole);
    return 0;
}