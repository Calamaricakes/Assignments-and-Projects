#include <stdio.h>
#include <string.h>

#define LINE_INPUT_SIZE 1024
#define SMART_METER_READER_CSV "C:\\Users\\Prothean\\Desktop\\Code Folder\\Projects\\ElectricityCompare\\Electricity\\Victorian Energy Compare Data.csv"

int main(){

    // File handing variables
    FILE* fp = NULL;

    char consumptionDataPerDay[LINE_INPUT_SIZE];
    char titleLine[LINE_INPUT_SIZE];

    char* token_ptr;

    fp = fopen(SMART_METER_READER_CSV, "r");

    if(fp != NULL){
        printf("TITLE LINE\n");
        fgets(titleLine, LINE_INPUT_SIZE, fp);
        printf("%s\n", titleLine);

        // get one line input
        fgets(consumptionDataPerDay, LINE_INPUT_SIZE, fp);
        printf("%s\n", consumptionDataPerDay);

        printf("START TOKENIZING\n");
        token_ptr = strtok(titleLine,",");

        while(token_ptr){
            printf("%s\n", token_ptr);
            token_ptr = strtok(NULL, ",");
        }

    }
    else{
        printf("File not found\n");
        return 0;
    }

    return 0;
}