#include <stdio.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define LINE_INPUT_SIZE 1024
#define HALF_HOURS_IN_A_DAY 48
#define SMART_METER_READER_CSV_Protean "C:\\Users\\Prothean\\Desktop\\Code Folder\\Projects\\ElectricityCompare\\Electricity\\Victorian Energy Compare Data.csv"
#define SMART_METER_READER_CSV_USER "C:\\Users\\User\\Dropbox\\Electricity\\Victorian Energy Compare Data.csv"

typedef struct DateNode{
    int day;
    int month;
    int year;
}DateNode;

typedef struct DayUsageNode{
    int NMI_nationalMeterIdentifier;
    int meterSerialNumber;
    int consumingElectricity;
    int generatingElectricity;
    DateNode* date_ptr;
    float consumptionByHalfHour[HALF_HOURS_IN_A_DAY];
}DayUsageNode;


int main(){

    // File handing variables
    FILE* fp = NULL;

    char consumptionDataPerDay[LINE_INPUT_SIZE];
    char titleLine[LINE_INPUT_SIZE];

    char* token_ptr;

    fp = fopen(SMART_METER_READER_CSV_USER, "r");

    if(fp != NULL){
        printf("TITLE LINE\n");
        fgets(titleLine, LINE_INPUT_SIZE, fp);
        printf("%s\n", titleLine);

        // get a line that corresponds to the
        // electricity usage of that day
        //while
        fgets(consumptionDataPerDay, LINE_INPUT_SIZE, fp);
        printf("%s\n", consumptionDataPerDay);

        printf("START TOKENIZING\n");
        token_ptr = strtok(consumptionDataPerDay,",");

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