#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#define TRUE 1
#define FALSE 0
#define EQUAL 0
#define LINE_INPUT_SIZE 1024
#define HALF_HOURS_IN_A_DAY 48
#define NMI_LENGTH 11
#define SERIAL_NUMBER_LENGTH 6
#define SMART_METER_READER_CSV_Protean "C:\\Users\\Prothean\\Desktop\\Code Folder\\Projects\\ElectricityCompare\\Electricity\\Victorian Energy Compare Data.csv"
#define SMART_METER_READER_CSV_USER "C:\\Users\\User\\Dropbox\\Electricity\\Victorian Energy Compare Data.csv"

typedef struct DateNode{
    int day;
    int month;
    int year;
}DateNode;

typedef struct DayUsageNode{
    char[NMI_LENGTH] NMI_nationalMeterIdentifier;
    char[SERIAL_NUMBER_LENGTH] meterSerialNumber;
    int generatingElectricity;
    DateNode* date_ptr;
    float consumptionByHalfHour[HALF_HOURS_IN_A_DAY];
}DayUsageNode;

DayUsageNode* processElectricityData(char* stringConsumptionData);

int main(){

    // File handing variables
    FILE* file_ptr = NULL;

    char consumptionDataPerDay[LINE_INPUT_SIZE];
    char titleLine[LINE_INPUT_SIZE];

    char* token_ptr = NULL;

    file_ptr = fopen(SMART_METER_READER_CSV_USER, "r");

    if(file_ptr != NULL){
        printf("TITLE LINE\n");
        fgets(titleLine, LINE_INPUT_SIZE, file_ptr);
        printf("%s\n", titleLine);

        // get a line that corresponds to the
        // electricity usage of that day
        //while
        fgets(consumptionDataPerDay, LINE_INPUT_SIZE, file_ptr);
        printf("%s\n", consumptionDataPerDay);

        processElectricityData(consumptionDataPerDay);

    }
    else{
        printf("File not found\n");
        return 0;
    }

    return 0;
}

DayUsageNode* processElectricityData(char* stringConsumptionData){
// interprets a line of csv data then puts the processed
// information into DayUsageNode and DateNode

    char* token_ptr = NULL;
    DayUsageNode* usageNode_ptr = (DayUsageNode*)malloc(1);

    // initialise the tokeniser
    token_ptr = strtok(stringConsumptionData,",");

    // start reading each section of string separated by ","
    usageNode_ptr->NMI_nationalMeterIdentifier = atoi(token_ptr);
    token_ptr = strtok(NULL, ",");

    usageNode_ptr->meterSerialNumber = atoi(token_ptr);
    token_ptr = strtok(NULL, ",");

    // if the household is consuming electricity
    if(strcmp(token_ptr, "Consumption") == EQUAL){
        usageNode_ptr->generatingElectricity = FALSE;
    }
    // else it is generating electricty
    else{
        usageNode_ptr->generatingElectricity = TRUE;
    }
    token_ptr = strtok(NULL, ",");

    // it gets a little messy here, the dates are in a dd/mm/yyyy format
    // so we have to tokenise the tokenised string again

    char* token_date_ptr = NULL;
    DateNode* dateNode_ptr = (DateNode*)malloc(1);

    token_date_ptr = strtok(token_ptr, "/");
    dateNode_ptr->day = atoi(token_date_ptr);

    token_date_ptr = strtok(NULL, "/");
    dateNode_ptr->month = atoi(token_date_ptr);

    token_date_ptr = strtok(NULL, "/");
    dateNode_ptr->year = atoi(token_date_ptr);

    token_date_ptr = strtok(NULL, "/"); // NULL the ptr

    //
    // precaution
    free(usageNode_ptr);
    free(dateNode_ptr);
}