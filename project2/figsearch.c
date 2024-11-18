#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    int* content;
    int width;
    int height;
} Image;

typedef struct {
    unsigned int x;
    unsigned int y;
} Vector;

/**
 * @brief Creates a new Image
 * @param width The width, or rows of created matrix
 * @param height The height, or columns of created matrix
 */
Image* createImage(unsigned int width, unsigned int height){
    //test for valid size >0
    if(width < 1){
        fprintf(stderr, "Invalid width input.");
        return NULL;
    }
    if(height < 1){
        fprintf(stderr, "Invalid height input.");
        return NULL;
    }

    Image* image = malloc(sizeof(Image));
    if(image == NULL){
        fprintf(stderr, "Cannot allocate memory for image");
        return NULL;
    }
    
    //allocate memory
    int* temp = malloc(width*height*sizeof(int));
    if(temp == NULL){
        fprintf(stderr, "Cannot allocate memory for content");
        return NULL;
    }
    //fill values to object
    image->content = temp;
    image->width = width;
    image->height = height;

    return image;
}

bool fillImage(Image *image, FILE file){
    return 1;
}

/**
 * @brief
 * @param image 
 * @return True if image 
 */
bool isValidImage(Image *image){
    return 1;
}

bool defineMatrix(Vector* vect, FILE* file){
    unsigned int height = 0;
    unsigned int width = 0;
    bool readWidth = false;
    char readChar = 0;
    while(readChar != '\n'){
        readChar = fgetc(file);
        if(readChar == EOF){
            fprintf(stderr, "File ended early.");
            return false;
        }
        if((readChar < '0' || readChar > '9')){
            //NaN
            if(readChar == ' ' || readChar == '\t'){
                readWidth = true;
                continue;
            }
            else if(readChar == '\n'){
                break;
            }
            else{
                //invalid input
                fprintf(stderr, "Non-numeric character in file");
                return false;
            }
        }
        //update desired values
        if(readWidth){
            width = width * 10 + (readChar - '0');
        }
        else {
            height = height * 10 + (readChar - '0');
        }
    }
    if(!readWidth){
        fprintf(stderr, "Missing width.");
        return false;
    }
    vect->x = height;
    vect->y = width;
    return true;
}

int* hline(Image* image){

    return NULL;
}

int* vline(Image* image){

    return NULL;
}

int* square(Image* image){

    return NULL;
}

int main(int argc, char** argv){

    ///pointer to desired function
    int* (*figureFunction)(Image*);
    char* fileName = "bitmap.txt";
    
    if(argc == 2){
        if(strcmp(argv[1], "--help") == 0){
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
            return 0;
        }
        else {
            fprintf(stderr, "Invalid argument.");
            return -1;
        }
    }
    else if(argc == 3){
        //get desired action
        if(strcmp(argv[1], "test")){
            //action = 0;
        }
        else if(strcmp(argv[1], "hline")){
            figureFunction = hline;
        }
        else if(strcmp(argv[1], "vline")){
            figureFunction = vline;
        }
        else if(strcmp(argv[1], "square")){
            figureFunction = square;
        }
        else{
            fprintf(stderr, "Invalid figure argument.");  
            return -1;  
        }

        //get filename
        fileName = argv[2];
    }
    else {
        fprintf(stderr, "Invalid argument count.");
        return -1;
    }
    Image* image;
    FILE* file = fopen(fileName, "r");
    {
        Vector matrixSize;
        if(!defineMatrix(&matrixSize, file)){
            fprintf(stderr, "Invalid matrix definition.");
            return -1;
        }
        image = createImage(matrixSize.x, matrixSize.y);
        if(image == NULL){
            fprintf(stderr, "Error when allocating memory.");
            return -1;
        }
    }
    

    printf("\n\nFilename: %s", fileName);
    printf("\nrows;columns: %u;%u", image->height,image->width);
    fclose(file);
    return 0;
}
