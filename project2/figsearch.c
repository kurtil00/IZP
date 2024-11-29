#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    bool* content;
    unsigned int width;
    unsigned int height;
    unsigned int size;
} Image;

typedef struct {
    unsigned int x;
    unsigned int y;
} Vector;

/**
 * @brief Creates a new Image
 * @param width The width, or rows of created matrix
 * @param height The height, or columns of created matrix
 * @return Pointer to memory of created image
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
    bool* temp = malloc(width*height*sizeof(bool));
    if(temp == NULL){
        return NULL;
    }

    //fill values to object
    image->content = temp;
    image->width = width;
    image->height = height;
    image->size = width * height;

    return image;
}

bool fillImage(Image *image, FILE* file){
    char readChar = 0;
    unsigned int valueCounter = 0;
    bool whitespace = true;
    while(readChar != EOF && valueCounter < image->size){
        readChar = fgetc(file);
        if((readChar == '0' || readChar == '1') && whitespace){
            image->content[valueCounter] = readChar - '0';
            valueCounter++;
            whitespace = false;
        }
        else if(readChar == ' ' || readChar == '\n' || readChar == EOF){
            whitespace = true;
            continue;
        }
        else return false;
    }
    if(valueCounter < image->size)
        return false;
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
unsigned int valAt(unsigned int x, unsigned int y, Image* image){
    return image->content[x * image->width + y];
}

int* hstreak(unsigned int pos, Image* image){
    int* vectors;//return numbers
    if((vectors = malloc(4*sizeof(int))) == NULL)
        return NULL;
    for(int fill = 0; fill < 4; fill++)
        vectors[fill] = -1;

    unsigned int current = 0;
    unsigned int row = (pos - (pos % image->width))/image->width;
    unsigned int cols;
    for(cols = pos; cols < (row+1)*image->width; cols++){
        if(image->content[cols] == 1){
            current++;
        }
        else break;
    }
    vectors[0] = row;
    vectors[1] = pos - row*image->width;
    vectors[2] = row;
    vectors[3] = vectors[1]+current-1;
    return vectors;
}

int* vstreak(unsigned int pos, Image* image){
    int* vectors = malloc(4*sizeof(int));//return numbers
    if(vectors == NULL)
        return NULL;
    for(int fill = 0; fill < 4; fill++)
        vectors[fill] = -1;

    unsigned int current = 0;
    unsigned int rows;
    for(rows = pos; rows < image->size; rows+= image->width){
        if(image->content[rows] == 1){
            current++;
        }
        else break;
    }
    vectors[0] = (pos - (pos % image->width)) / image->width;
    vectors[1] = (pos % image->width);
    vectors[2] = (rows - (rows % image->width)-1) / image->width;
    vectors[3] = (pos % image->width);
    return vectors;
}

int* hline(Image* image){
    int* vectors;//return numbers
    if((vectors = malloc(4*sizeof(int))) == NULL)
        return NULL; 
    for(int fill = 0; fill < 4; fill++)
        vectors[fill] = -1;

    for(unsigned int pos = 0; pos < image->size; pos++){
        int* newVectors = hstreak(pos, image);
        if(abs(newVectors[1]-newVectors[3]) > abs(vectors[1]-vectors[3])){
            free(vectors);
            vectors = newVectors;
        }
    }
    
    return vectors;
}

int* vline(Image* image){
    int* vectors;//return numbers
    if((vectors = malloc(4*sizeof(int))) == NULL)
        return NULL;
    for(int fill = 0; fill < 4; fill++)
        vectors[fill] = -1;

    unsigned int cols;
    for(cols = 0; cols < image->size; cols++){
        if(image->content[cols] == 1){
            int* newVectors = vstreak(cols, image);
            if(newVectors == NULL)
                return NULL;
            if(abs(newVectors[0]-newVectors[2]) > abs(vectors[0]-vectors[2])){
                free(vectors);
                vectors = newVectors;
            }
        }
    }
    return vectors;
}



int* square(Image* image){
    int* vectors;//return numbers
    if((vectors = malloc(4*sizeof(int))) == NULL)
        return NULL;
    for(int fill = 0; fill < 4; fill++)
        vectors[fill] = -1;
    
    unsigned int pos;
    for(pos = 0; pos < image->size; pos++){
        if(image->content[pos] == 1){
            
        }
    }
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
    for(unsigned int i = 0; i < image->height; i++){
        for(unsigned int j = 0; j < image->width; j++){
            printf("%d ", image->content[i*image->width+j]);
        }
        printf("\n");
    }}
    printf("\n");
    int* vectors = figureFunction(image);
    printf("%d;%d->%d;%d", vectors[0],vectors[1],vectors[2],vectors[3]);
    fclose(file);
    return 0;
}
