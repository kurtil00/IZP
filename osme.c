#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void print_array(int* array, int size, int actual){
    printf("array: {");
    int count;
    for(count = 0; count < size; count++){
        printf("%d", array[count]);
        if(count < size-1){
            printf(",");
        }
    }
    printf("} size: %d ; used: %d\n", size, actual);
}


int* create_array(int size){
    return malloc(size);
}

void free_array(int* array){
    if(array!= NULL){
        free(array);
        array = NULL;
    }
    else printf("chyba??");
}

void add_item(int* array, int item, int* total_length, int* actual_length){
    if(*total_length == *actual_length){
        *total_length = *total_length * 2;
        realloc(array, *total_length);
    }

    array[*actual_length] = item;
    *actual_length = *actual_length + 1;
}

void remove_item(int* array, int index, int* actual_length){
    int count;
    for(count = index; count < *actual_length-1; count++){
        array[count] = array[count+1];
    }
}

int find_item(int* array, int item, int* actual_length){
    int count;
    for(count = 0; count < *actual_length; count++){
        if(array[count] == item){
            return count;
        }
    }
    return -1;
}

int main(int argc, char** argv){
    int array_length = 3;
    int actual_length = 0;

    int* array = create_array(array_length);
    add_item(array, 1, &array_length, &actual_length);
    //print_array(array, array_length, actual_length);
    add_item(array, 2, &array_length, &actual_length);
    //print_array(array, array_length, actual_length);
    add_item(array, 3, &array_length, &actual_length);
    print_array(array, array_length, actual_length);

    add_item(array, 4, &array_length, &actual_length);
    //print_array(array, array_length, actual_length);
    add_item(array, 5, &array_length, &actual_length);
    add_item(array, 6, &array_length, &actual_length);
    add_item(array, 7, &array_length, &actual_length);
    add_item(array, 8, &array_length, &actual_length);
    print_array(array, array_length, actual_length);

    remove_item(array, 2, &array_length);
    print_array(array, array_length, actual_length);

    int item_index = find_item(array, 7, &actual_length);
    printf("\nItem_index: %d\n", item_index);

    free_array(array);
    printf("\nPointer:%p\n", array);
    return 0;
}