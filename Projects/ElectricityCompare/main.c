#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define EQUAL 0
#define LINE_INPUT_SIZE 1024
#define HALF_HOURS_IN_A_DAY 48
#define DAYS_IN_TEN_YEARS 3650
#define DATE_STRING_LENGTH 11
#define BASE_TEN 10
#define NMI_LENGTH 11
#define SERIAL_NUMBER_LENGTH 6
#define SMART_METER_READER_CSV_PROTEAN "C:\\Users\\Prothean\\Desktop\\Code Folder\\Projects\\ElectricityCompare\\Electricity\\Victorian Energy Compare Data.csv"
#define SMART_METER_READER_CSV_USER "C:\\Users\\User\\Dropbox\\Electricity\\Victorian Energy Compare Data.csv"

typedef struct DateNode{
    short day;
    short month;
    short year;
}DateNode;

typedef struct DayUsageNode{
    char NMI_nationalMeterIdentifier[NMI_LENGTH];
    char meterSerialNumber[SERIAL_NUMBER_LENGTH];
    short generatingElectricity;
    DateNode* date_ptr;
    float consumptionByHalfHour[HALF_HOURS_IN_A_DAY];
}DayUsageNode;

DayUsageNode* processElectricityData(char* stringConsumptionData);
void freeUsageNode(DayUsageNode* node_ptr);
void printUsageNode(DayUsageNode* node_ptr);

int main(){

    // File handing variables
    FILE* file_ptr = NULL;

    char consumptionDataPerDay[LINE_INPUT_SIZE];
    char titleLine[LINE_INPUT_SIZE];

    DayUsageNode* usageData[DAYS_IN_TEN_YEARS];
    short usageDataCounter = 0;

    // iterators
    int i;

    file_ptr = fopen(SMART_METER_READER_CSV_PROTEAN, "r");

    if(file_ptr != NULL){
        printf("TITLE LINE\n");
        fgets(titleLine, LINE_INPUT_SIZE, file_ptr);
        printf("%s\n", titleLine);

        // get a line that corresponds to the electricity usage of that day

        while(fgets(consumptionDataPerDay, LINE_INPUT_SIZE, file_ptr)) {
            usageData[usageDataCounter++] = processElectricityData(consumptionDataPerDay);
        }

        for(i = 0; i < usageDataCounter; i++){
            printUsageNode(usageData[i]);
            freeUsageNode(usageData[i]);
        }
        printf("Number of days = %d", usageDataCounter);


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

/* Header line:
 * NMI,METER SERIAL NUMBER,CON/GEN,DATE,ESTIMATED?,00:00 - 00:30,00:30 - 01:00,01:00 - 01:30,01:30 - 02:00,
 * 02:00 - 02:30,02:30 - 03:00,03:00 - 03:30,03:30 - 04:00,04:00 - 04:30,04:30 - 05:00,05:00 - 05:30,05:30 - 06:00,
 * 06:00 - 06:30,06:30 - 07:00,07:00 - 07:30,07:30 - 08:00,08:00 - 08:30,08:30 - 09:00,09:00 - 09:30,09:30 - 10:00,
 * 10:00 - 10:30,10:30 - 11:00,11:00 - 11:30,11:30 - 12:00,12:00 - 12:30,12:30 - 13:00,13:00 - 13:30,13:30 - 14:00,
 * 14:00 - 14:30,14:30 - 15:00,15:00 - 15:30,15:30 - 16:00,16:00 - 16:30,16:30 - 17:00,17:00 - 17:30,17:30 - 18:00,
 * 18:00 - 18:30,18:30 - 19:00,19:00 - 19:30,19:30- 20:00,20:00 - 20:30,20:30 - 21:00,21:00 - 21:30,21:30 - 22:00,
 * 22:00 - 22:30,22:30 - 23:00,23:00 - 23:30,23:30 - 00:00
*/

/* Example line from CSV file:
 * 6601824251,975459,Consumption,27/11/2017,No,0.025,0.031,0.031,0.025,0.031,0.031,0.031,0.025,0.031,0.031,0.025,0.031,
 * 0.031,0.025,0.031,0.031,0.025,0.031,0.031,0.025,0.031,0.031,0.025,0.031,0.031,0.006,0,0.006,0,0.006,0.025,0,0.006,
 * 0,0.006,0.006,0,0.006,0,0.006,0.006,0,0.006,0,0.006,0.006,0,0.006,0,0.006,0.006,0,0.006,0,0.006,0.006,0,0.006,0,
 *  0.006,0.006,0,0.006
*/

    char* token_ptr = NULL;
    DayUsageNode* usageNode_ptr = (DayUsageNode*)malloc(sizeof(DayUsageNode));

    // initialise the tokeniser
    token_ptr = strtok(stringConsumptionData,",");

    // start reading each section of string separated by ","

    // In the example, string value of "6601824251"
    strcpy(usageNode_ptr->NMI_nationalMeterIdentifier,token_ptr);
    token_ptr = strtok(NULL, ",");

    // "975459"
    strcpy(usageNode_ptr->meterSerialNumber,token_ptr);
    token_ptr = strtok(NULL, ",");

    // "Consumption", input could also be "Generation"
    // if the household is consuming electricity
    if(strcmp(token_ptr, "Consumption") == EQUAL){
        usageNode_ptr->generatingElectricity = FALSE;
    }
    // else it is generating electricity
    else{
        usageNode_ptr->generatingElectricity = TRUE;
    }
    token_ptr = strtok(NULL, ",");

    // it gets a little messy here, the dates are in a dd/mm/yyyy format, in the example: 27/11/2017
    // so we have to tokenise the tokenised string again then put it in a DateNode

    DateNode* dateNode_ptr = NULL;
    char dateString[DATE_STRING_LENGTH];
    char* tokenDate_ptr = NULL;
    char* endPoint = NULL;
    short tempShort = 0;

    // copy the date string over to dateString, this is meant for a separate tokeniser to work on the dateString
    // and allow the initial tokeniser to move on from the date to the "Estimated" column.
    strcpy(dateString, token_ptr);

    dateNode_ptr = (DateNode*)malloc(sizeof(DateNode));
    // point the usageNode to the newly created dateNode
    usageNode_ptr->date_ptr = dateNode_ptr;

    // "27"
    tokenDate_ptr = strtok(dateString, "/");

    if((tempShort = strtol(tokenDate_ptr, &endPoint, BASE_TEN))){
        dateNode_ptr->day = tempShort;
    }
    else{
        printf("Day parsing error\n");
    }

    // "11"
    tokenDate_ptr = strtok(NULL, "/");
    if((tempShort = strtol(tokenDate_ptr, &endPoint, BASE_TEN))){
        dateNode_ptr->month = tempShort;
    }
    else{
        printf("Month parsing error\n");
    }

    // "2017"
    tokenDate_ptr = strtok(NULL, "/");
    if((tempShort = strtol(tokenDate_ptr, &endPoint, BASE_TEN))){
        dateNode_ptr->year = tempShort;
    }
    else{
        printf("Year parsing error\n");
    }

    // NULL the ptr for safety
    tokenDate_ptr = strtok(NULL, "/");

    // iterator
    int i;

    token_ptr = strtok(NULL, ",");

    for(i = 0; i < HALF_HOURS_IN_A_DAY; i++){
        usageNode_ptr->consumptionByHalfHour[i] = strtof(token_ptr, &endPoint);
        token_ptr = strtok(NULL, ",");
    }

    return usageNode_ptr;
}

void freeUsageNode(DayUsageNode* node_ptr){
    free(node_ptr->date_ptr);
    free(node_ptr);
}

void printUsageNode(DayUsageNode* node_ptr){
    printf("NMI: %s, Serial Number:%s, Generation: %d, Day: %d, Month: %d, Year: %d\n",
           node_ptr->NMI_nationalMeterIdentifier, node_ptr->meterSerialNumber, node_ptr->generatingElectricity,
           node_ptr->date_ptr->day, node_ptr->date_ptr->month, node_ptr->date_ptr->year);

}