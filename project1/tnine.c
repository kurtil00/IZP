#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>

#define MAX_LINE_SIZE 101

const char* numCharRelation[10] = {"+0","1","abcABC2","defDEF3","ghiGHI4",
    "jklJKL5","mnoMNO6","pqrsPQRS7","tuvTUV8","wxyzWXYZ9"};


/// @brief True if character values of 'value' are contained in 'string' in an 
/// uninterupted sequence, false otherwise
/// @param string Valid source string
/// @param value Numeric sequence to filter with in char* type
bool IsInString(char* string, char* value){
    int counter;
    int valueSize = strlen(value);
    int matchCounter = 0;
    int numericValue;
    int innerCounter;
    
    for(counter = 0; counter+valueSize-1 < strlen(string) && 
                        valueSize > matchCounter; counter++){

        for(innerCounter = 0; innerCounter < valueSize; innerCounter++){
            numericValue = value[innerCounter] - 48;

            if(strchr(numCharRelation[numericValue], string[counter + innerCounter])){
                matchCounter++;
            }
            else if(matchCounter > 0){
                //streak is interrupted
                matchCounter = 0;
                break;
            }
        }
    }
    if(matchCounter == valueSize){
        return true;
    }
    return false;
}

/// @brief True if character values of 'value' are contained in 'string' with any number
/// of interrupting characters between them, false otherwise
/// @param string Valid source string
/// @param value Numeric sequence to filter with in char* type
bool IsInStringInterrupted(char* string, char* value){
    int counter;
    int valueSize = strlen(value);
    int matchCounter = 0;
    int numericValue;

    for(counter = 0; counter < strlen(string) && valueSize > matchCounter; counter++){
        numericValue = value[matchCounter] - 48;
        if(strchr(numCharRelation[numericValue],string[counter])){
            matchCounter++;
        }
    }
    if(matchCounter == valueSize){
        return true;
    }
    return false;
}

bool IsValidNumber(char* value){
    int counter;
    for(counter = 0; counter < strlen(value); counter++){
        if(value[counter] >= '0' && value[counter] <= '9'){
            continue;
            //input argument is a number
        }
        else{
            return false;
            //input argument is not a number
        }
    }
    return true;
}

int main(int argc, char* argv[]){

    bool canBeInterrupted = false;

    //check if arguments are valid
    if(argc == 2 && !IsValidNumber(argv[1])){
        fprintf(stderr, "Invalid argument format.");
            return EINVAL;
    }
    else if(argc == 3){
        if(argv[1][0] == '-' && argv[1][1] == 's'){
            canBeInterrupted = true;
        }
        else {
            fprintf(stderr, "Invalid argument format.");
            return EINVAL;
        }
    }
    else if(argc > 3){
        fprintf(stderr, "Too many arguments.");
        return E2BIG;
    }

    //declare variables
    char* inputNumbers;
    if(canBeInterrupted){
        inputNumbers = argv[2];
    } 
    else inputNumbers = argv[1];
    char name[MAX_LINE_SIZE]; //saves name if phone fits criteria
    char newInfo[MAX_LINE_SIZE];
    int charCount = 0;
    int contactType = 0;
    char input;
    int arrayClean;

    bool nameFitsFilter = false;
    bool endFlag = false;
    bool foundAtLeastOne = false;

    //main code for undefined number of contacts, ContactType(2) => endOfFile
    while(!endFlag){
        input = getchar();

        //End of file || User input double newline (end sequence)
        if(input == -1 || (charCount == 0 && input == '\n')){
            endFlag = true;
        }

        
        if(input == '\n'|| endFlag){
            if(contactType == 0){
                //name
                if(argc == 1 || 
                    (!canBeInterrupted && IsInString(newInfo, inputNumbers)) || 
                    (canBeInterrupted && IsInStringInterrupted(newInfo, inputNumbers)))
                {
                    nameFitsFilter = true;
                }
            }
            else if(contactType == 1){
                //phone number
                if(argc == 1 || nameFitsFilter || 
                    (!canBeInterrupted && IsInString(newInfo, inputNumbers)) || 
                    (canBeInterrupted && IsInStringInterrupted(newInfo, inputNumbers)))
                {
                    foundAtLeastOne = true;

                    printf("%s, %s\n", name, newInfo);
                    nameFitsFilter = false;
                }
            }
            contactType = (contactType+1)%2;
            newInfo[charCount] = '\0';
            strcpy(name, newInfo);

            charCount = -1; //will increment by 1
            
            //clear array data; could be rewritten as "memset(newInfo, 0, MAX_LINE_SIZE);"
            for(arrayClean = 1; arrayClean < MAX_LINE_SIZE && 
                                newInfo[arrayClean] != 0; arrayClean++)
            {
                newInfo[arrayClean] = 0;
            }
        }
        else{
            newInfo[charCount] = input;
        }

        charCount++;
        if(charCount > MAX_LINE_SIZE-1){
            fprintf(stderr, "Contact name too big. Exiting.\n");
            return EIO;
        }
    }
    if(!foundAtLeastOne){
        printf("Not found\n");
    }

    return 0;
}