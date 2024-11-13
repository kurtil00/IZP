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
    intPole array = malloc(sizeof(intPole)); //PD
    array.array = malloc(size);
    array.length = size;
    array.used_size = 0;
    return array;
}

void free_array(intPole *array){
    if(&array->array != NULL){
        free(array); //problemovy radek
        array->array = NULL;
    }
    else printf("chyba??");
}

// void add_item(intPole *array, int item){
//     if(array->length == array->used_size){
//         array->array = realloc(array->array, array->length*2*sizeof(int));
//         array->length *= 2;
//     }

//     array->array[array->used_size] = item;
//     array->used_size += 1;
// }

int add_item(intPole* array, int item) { //PD
    // Skontroluje, či je pole plné
    if (array->used_size == array->length) {
        // Zdvojnásobí kapacitu poľa
        int* new_items = (int*)realloc(array->array, array->length * 2 * sizeof(int));
        if (new_items == NULL) {
            return 0; // Ak alokácia zlyhá, vráti 0
        }
        array->array = new_items;
        array->length *= 2;
    }

    // Pridá novú položku do poľa
    array->array[array->used_size++] = item;
    return 1; // Vráti 1, ak sa položka úspešne pridá
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
        if(!add_item(&pole, i))
        {
            printf("Chyba\n");
        }
    }
    print_array(&pole);

    remove_item(&pole, 2);

    int item_index = find_item(pole, 7);
    printf("\nItem_index: %d\n", item_index);

    free_array(&pole);
    return 0;
}