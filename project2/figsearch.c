#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    int* content;
    int width;
    int height;
} Image;

bool CreateImage(Image *image, int width, int height){
    //test for valid size >0
    if(width < 1){
        fprintf(stderr, "Invalid width input.");
        return 0;
    }
    if(height < 1){
        fprintf(stderr, "Invalid height input.");
        return 0;
    }

    image = malloc(sizeof(Image));
    if(image == NULL){
        fprintf(stderr, "Cannot allocate memory for image");
        return 0;
    }

    image->width = width;
    image->height = height;
    //allocate memory
    int* temp = malloc(width*height*sizeof(int));
    printf("\n\n%p\n%lld\n\n", temp,height*width*sizeof(int));
    if(temp == NULL){
        fprintf(stderr, "Cannot allocate memory for array");
        return 0;
    }
    image->content = temp;

    return 1;
}

bool FillImage(Image *image, FILE file){
    return 1;
}

/**
 * @brief
 * @param image 
 * @return True if image 
 */
bool IsValidImage(Image *image){
    return 1;
}

int main(int argc, char** argv){
    //parametry:
    //--help
    //test FILE
    //hline FILE
    //vline FILE
    //square FILE
    int action = -1; //null = -1, test = 0, hline = 1, vline = 2, square = 3
    char* fileName;
    
    if(argc == 2){
        if(strcmp(argv[1], "--help")){
            printf("Input format: \n\"./figsearch ARGUMENT FILENAME\"");
            printf("\nARGUMENT:");
            printf("\n\ttest\tValidates correct file format.");
            printf("\n\t    \tReturns \"Valid\" if file is valid, terminates the program otherwise.");
            printf("\n\thline\tReturns longest uninterrupted horizontal line");
            printf("\n\tvline\tReturns longest uninterrupted vertical line");
            printf("\n\tsquare\tReturns largest square figure. Square can be hollow.");
            printf("\nReturn values are 4 numbers making 2 vectors: the starting ");
            printf("and ending coordinates of searched figure.");
            printf("\n\nFILENAME:");
            printf("\n\tFILENAME\tName of the file containing the bitmap. Has to be in the same folder.");
        }
        else {
            fprintf(stderr, "Invalid argument.");
            return -1;
        }
    }
    else if(argc == 3){
        fileName = argv[2];
    }
    else {
        fprintf(stderr, "Invalid argument count.");
        return -1;
    }
    
    Image *image;
    if(!CreateImage(image, 4, 5)){
        fprintf(stderr, "Error when allocating memory.");
        return -1;
    }
    printf("\n\n%s", fileName);
    printf("\n%d;%d", image->height,image->width);
    
    return 0;
}
