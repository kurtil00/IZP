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
        return NULL;
    }
    if(height < 1){
        return NULL;
    }

    Image* image = malloc(sizeof(Image));
    if(image == NULL){
        return NULL;
    }
    
    //allocate memory
    int* temp = malloc(width*height*sizeof(int));
    if(temp == NULL){
        return NULL;
    }
    //fill values to object
    image->content = temp;
    image->width = width;
    image->height = height;

    return image;
}

bool fillImage(Image *image, FILE* file){
    char readChar = 0;
    int valueCounter = 0;
    while(readChar != EOF){
        readChar = fgetc(file);
        if(readChar == '0' || readChar == '1'){
            image->content[valueCounter] = readChar - '0';
            valueCounter++;
        }
        else if(readChar == ' ' || readChar == '\n' || readChar == EOF){
            continue;
        }
        else return false;
    }
    return true;
}

bool defineMatrix(Vector* vect, FILE* file){
    unsigned int height = 0;
    unsigned int width = 0;
    bool readWidth = false;
    char readChar = 0;
    while(readChar != '\n'){
        readChar = fgetc(file);
        if(readChar == EOF){
            return false;
        }
        if((readChar < '0' || readChar > '9')){
            //NaN

            if(readChar == ' ' || readChar == '\n'){
                if(readWidth && height > 0){
                    break;    
                }
                readWidth = true;
                continue;
            }
            else{
                //invalid input
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
        return false;
    }
    vect->x = width;
    vect->y = height;
    return true;
}

/**
 * @brief Returns one numeric value from matrix
 * @param x 0-based vertical position
 * @param y 0-based horizontal position
 * @param image Image to take value from
 * @return int containing 0 or 1
 */
int valAt(int x, int y, Image* image){
    return image->content[x * image->width + y];
}

int* hline(Image* image){
    int currentMax = 0;
    int current = 0;
    int* vectors = malloc(4);
    for(int fill = 0; fill < 4; fill++)
        vectors[fill] = -1;
    int currentPosition = 0;

    for(int vert = 0; vert < image->height; vert++){
        for(int hori = 0; hori < image->width; hori++){
            if(valAt(vert, hori, image) == 1)
                current++;
            else {
                if(currentMax < current){
                    currentMax = current;
                    vectors[0] = vert;
                    vectors[1] = currentPosition;
                    vectors[2] = vert;
                    vectors[3] = current-1;
                    current = 0;
                    currentPosition = hori;
                }
                if(image->width - hori < currentMax){
                    break;
                }
            }
        }
        if(currentMax < current){
            currentMax = current;
            vectors[0] = vert;
            vectors[1] = currentPosition;
            vectors[2] = vert;
            vectors[3] = current-1;
        }
        current = 0;
        currentPosition = 0;
    }
    return vectors;
}

int* vline(Image* image){
    int currentMax = 0;
    int current = 0;
    int* vectors = malloc(4);
    for(int fill = 0; fill < 4; fill++)
        vectors[fill] = -1;
    int currentPosition = 0;

    int hori;
    int vert;
    for(hori = 0; hori < image->height; hori++){
        for(vert = 0; vert < image->width; vert++){
            if(valAt(vert, hori, image) == 1)
                current++;
            else {
                if(currentMax < current){
                    currentMax = current;
                    vectors[0] = currentPosition;
                    vectors[1] = hori;
                    vectors[2] = current-1;
                    vectors[3] = hori;
                    current = 0;
                    currentPosition = hori;
                }
                if(image->height - vert < currentMax){
                    break;
                }
            }
        }
        if(currentMax < current){
            currentMax = current;
            vectors[0] = currentPosition;
            vectors[1] = hori;
            vectors[2] = current-1;
            vectors[3] = hori;
        }
        current = 0;
        currentPosition = 0;
    }
    return vectors;
}

int* square(Image* image){
    int* vectors;
    vectors[0] = -1;
    return vectors;
}

/**
 * @brief Returns pointer to function based on input string value
 * @param input Character array containing function name
 * @return Pointer to function if successful, NULL otherwise
 */
int* (*assignFunction(char* input))(Image*){
    if(strcmp(input, "test") == 0){
        //action = 0;
    }
    else if(strcmp(input, "hline") == 0){
        return hline;
    }
    else if(strcmp(input, "vline") == 0){
        return vline;
    }
    else if(strcmp(input, "square") == 0){
        return square;
    }
    else{
        return NULL;  
    }
    return NULL;
}

int main(int argc, char** argv){

    ///pointer to desired figure function
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
        figureFunction = assignFunction(argv[1]);
        if(figureFunction == NULL){
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
    if(!fillImage(image, file)){
        fprintf(stderr, "Error when filling bitmap.");
        return -1;
    }
    //debug print image
    {
    printf("\n");
    for(int i = 0; i < image->height; i++){
        for(int j = 0; j < image->width; j++){
            printf("%d ", image->content[i*image->width+j]);
        }
        printf("\n");
    }}
    // printf("\n\nFilename: %s", fileName);
    printf("\n");
    int* vectors = figureFunction(image);
    printf("%d;%d->%d;%d", vectors[0],vectors[1],vectors[2],vectors[3]);
    // printf("\nrows;columns: %u;%u", image->height,image->width);
    fclose(file);
    return 0;
}
