#pragma warning(disable : 4996)

#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <errno.h>

#define AC_GREEN "\x1b[32m"

#define BUFFER_SIZE 5000

FILE* CarMan, * Tmp, * Res;
char buffer[BUFFER_SIZE];

typedef struct Acar {
    char license[7];
    char type[12];
    char modelnum[16];
    int seatnum;
    char nickyname[10];
} Acar;

typedef struct node {
    struct Acar Vroom;
    struct node* next;
} node;

typedef struct list {
    struct node* head;
    struct node* tail;
    int length;
} list;

struct list AllCars;

void CreateCarMan() {
    //Opens and prints headings to file
    CarMan = fopen("C:\\Users\\HP\\Documents\\Informatica\\Year 1\\Semester 2\\Programming Project\\CarManager.txt", "w");
    fprintf(CarMan, "License Plate Number\t Type of Car\t Model Number\t Number of Seats in Car\t Nickname of Car\n");
    fclose(CarMan);
}
void CreateRes() {
    //Opens and prints headings to file
    Res = fopen("C:\\Users\\HP\\Documents\\Informatica\\Year 1\\Semester 2\\Programming Project\\CarReservations.txt", "w");
    fprintf(Res, "Start Date\t End Date\t License Plate Number\t Reservation Number\n");
    fclose(Res);
}

void LinkyListAp(struct list* l, struct Acar car) {

    struct node* New = malloc(sizeof(struct node));
    struct node* Prev = l->tail;

    New->Vroom = car;

    if (l->head == NULL) {
        l->head = New;
        l->tail = New;
        l->length = 1;
    }
    else {
        Prev->next = New;
        l->length = l->length + 1;
        l->tail = New;
    }
}
void AddLoop(int i, Acar* Car) {
    int eType = 1, tmpType;
    switch (i) {
    case 1:
        printf("Please enter the correct license plate number of the car you want to add.\n");
        scanf("%s", &Car->license);
        break;
    case 2:
        while (eType) {
            printf("What type of car are we working with?\n 1. Coupe\n 2. Crossover\n 3. Hatchback\n 4. Minivan\n 5. Sedan\n 6. SUV\n 7. Wagon\n");
            scanf("%d", &tmpType);
            switch (tmpType) {
            case 1:
                strcpy(Car->type, "Coupe");
                eType = 0;
                break;
            case 2:
                strcpy(Car->type, "Crossover");
                eType = 0;
                break;
            case 3:
                strcpy(Car->type, "Hatchback");
                eType = 0;
                break;
            case 4:
                strcpy(Car->type, "Minivan");
                eType = 0;
                break;
            case 5:
                strcpy(Car->type, "Sedan");
                eType = 0;
                break;
            case 6:
                strcpy(Car->type, "SUV");
                eType = 0;
                break;
            case 7:
                strcpy(Car->type, "Wagon");
                eType = 0;
                break;
            default:
                printf("Yikes...That isn't a valid option\n");
                break;
            }
        }
        break;
    case 3:
        printf("Please enter the model number of the car\n");
        scanf("%s", &Car->modelnum);
        break;
    case 4:
        printf("Please enter the number of seats available in this car\n");
        scanf("%d", &Car->seatnum);
        break;
    case 5:
        printf("Please enter a nickname for this car\n");
        scanf("%s", &Car->nickyname);
        break;
    default:
        printf("Yikes...That isn't a valid option\n");
        break;
    }
}

int DateValidation(char date[]) {
    int day, mon, year;

    day = (date[0] - '0') * 10 + (date[1] - '0');
    mon = (date[2] - '0') * 10 + (date[3] - '0');
    year = (date[4] - '0') * 1000 + (date[5] - '0') * 100 + (date[6] - '0') * 10 + (date[7] - '0');

    //check year
    if (year >= 1900 && year <= 9999) {
        //check month
        if (mon >= 1 && mon <= 12)
        {
            //check days
            if ((day >= 1 && day <= 31) && (mon == 1 || mon == 3 || mon == 5 || mon == 7 || mon == 8 || mon == 10 || mon == 12))
                return 1;
            else if ((day >= 1 && day <= 30) && (mon == 4 || mon == 6 || mon == 9 || mon == 11))
                return 1;
            else if ((day >= 1 && day <= 28) && (mon == 2))
                return 1;
            else if (day == 29 && mon == 2 && (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)))
                return 1;
            else
                printf("Yeah, something doesn't seem right. Let's try that again\n");
            return 0;
        }
        else {
            printf("This isn't a valid date. Did you enter in DD/MM/YYYY format?\n");
            return 0;
        }
    }
    else {
        printf("This isn't a valid date. Remember it's in DD/MM/YYYY format?\n");
        return 0;
    }

}
int FormatDate(char date[]) {
    int day, mon, year;

    day = (date[0] - '0') * 10 + (date[1] - '0');
    mon = (date[2] - '0') * 10 + (date[3] - '0');
    year = (date[4] - '0') * 1000 + (date[5] - '0') * 100 + (date[6] - '0') * 10 + (date[7] - '0');

    printf("%d/%d/%d\t", day, mon, year);
    return 0;
}
int DateComparison(char date[], char date2[]) {
    int day, mon, year, iDate, iDate2;

    day = (date[0] - '0') * 10 + 10 + (date[1] - '0');
    mon = (date[2] - '0') * 10 + 10 + (date[3] - '0');
    year = (date[4] - '0') * 1000 + (date[5] - '0') * 100 + (date[6] - '0') * 10 + (date[7] - '0');
    iDate = (year * 10000) + (mon * 100) + day;

    if ((date[0] - '0') == 0) {
        iDate = iDate - 10;
    }
    if ((date[2] - '0') == 0) {
        iDate = iDate - 1000;
    }
   
    day = (date2[0] - '0') * 10 + 10 + (date2[1] - '0');
    mon = (date2[2] - '0') * 10 + 10 + (date2[3] - '0');
    year = (date2[4] - '0') * 1000 + (date2[5] - '0') * 100 + (date[6] - '0') * 10 + (date[7] - '0');
    iDate2 = (year * 10000) + (mon * 100) + day;

    if ((date2[0] - '0') == 0) {
        iDate2 = iDate2 - 10;
    }
    if ((date2[2] - '0') == 0) {
        iDate2 = iDate2 - 1000;
    }

    if (iDate <= iDate2) {
        return 0;
    }
    else {
        return 1;
    }
}

int IsSpecial(const char* segment, const char* findMe) {
    size_t len = strlen(findMe);
    char* p = segment;

    while ((p = strstr(p, findMe)) != NULL)
    {
        char* q = p + len;
        if (p == segment || isblank((unsigned char)*(p - 1)))
        {
            if (*q == '\0' || isblank((unsigned char)*q)) return 1;;
        }
        p = q;
    }
    return 0;
}


//Adds a car to the list of rentable cars
int Add() {
    //Stores the license plate number to be added and indicates if the user wishes to return to MM
    const char plateNum[10];
    int con = 1;
    int editselec = -1;
    int edit;
    int tmpType;
    int eType = 1;
    int totalRead = 0;
    
    Acar Car;

    printf("Please enter the license plate number of the car you want to add. Or press '1' if you wish to return to the main menu:\n");
    scanf("%s", plateNum);

    if (strcmp(plateNum, "1") != 0) {

        CarMan = fopen("C:\\Users\\HP\\Documents\\Informatica\\Year 1\\Semester 2\\Programming Project\\CarManager.txt", "a+");

        while (fgets(buffer, BUFFER_SIZE, CarMan) != NULL) {
            totalRead = strlen(buffer);                                                             //Counts the total read
            buffer[totalRead - 1] = buffer[totalRead - 1] == '\n' ? '\0' : buffer[totalRead - 1];    //Trim new line character from last if exists.

            //If license number is contained on the line copies prints line
            if (IsSpecial(buffer, plateNum)) {
                printf("\n%s is already here though...\n", plateNum);
                printf("License Plate Number  Type of Car  Model Number  Number of Seats  Nickname\n");
                printf("%s\nIf you want to edit it, select the update option instead ;)\n\n", buffer);
                con = 0;
                fclose(CarMan);
                return 0;
            }
        }
        while (con) {
            edit = 1;
            strcpy(Car.license, plateNum);

            while (eType) {
                printf("What type of car are we working with?\n 1. Coupe\n 2. Crossover\n 3. Hatchback\n 4. Minivan\n 5. Sedan\n 6. SUV\n 7. Wagon\n");
                scanf("%d", &tmpType);
                switch (tmpType) {
                case 1:
                    strcpy(Car.type, "Coupe");
                    eType = 0;
                    break;
                case 2:
                    strcpy(Car.type, "Crossover");
                    eType = 0;
                    break;
                case 3:
                    strcpy(Car.type, "Hatchback");
                    eType = 0;
                    break;
                case 4:
                    strcpy(Car.type, "Minivan");
                    eType = 0;
                    break;
                case 5:
                    strcpy(Car.type, "Sedan");
                    eType = 0;
                    break;
                case 6:
                    strcpy(Car.type, "SUV");
                    eType = 0;
                    break;
                case 7:
                    strcpy(Car.type, "Wagon");
                    eType = 0;
                    break;
                default:
                    printf("Yikes...That isn't a valid option\n");
                    break;
                }
            }
            printf("Please enter the model number of the car\n");
            scanf("%s", &Car.modelnum);
            printf("Please enter the number of seats available in this car\n");
            scanf("%d", &Car.seatnum);
            printf("Wanna add a nickname for this car? Hit 1 if not\n");
            scanf("%s", &Car.nickyname);

            if (strcmp(Car.nickyname, "1") != 1) {
                strcpy(Car.nickyname, "New Car");
            }

            while (edit) {
                //Verification that the data entered is correct
                printf("Just to verify, is the data entered correct?\n\n");
                printf("%s\n 1. License Plate Number: %s\n 2. Car Type: %s\n 3. Car Model: %s\n 4. Seat Number: %d", Car.nickyname, Car.license, Car.type, Car.modelnum, Car.seatnum);
                printf("\n\nSelect the corresponding number if you wish to edit your additions or hit 0 if everything is perf!\n");
                scanf("%d", &editselec);

                switch (editselec) {
                case 0:
                    //Pad(&Car);
                    fprintf(CarMan, "%20s %13s %14s %17d %10s\n", Car.license, Car.type, Car.modelnum, Car.seatnum, Car.nickyname);
                    fclose(CarMan);
                    LinkyListAp(&AllCars, Car);
                    printf("Add another car?\n 0. No\t 1. Yes\n");
                    scanf("%d", &con);
                    if (con == 1) {
                        printf("Please enter the license plate number of the car you want to add.\n");
                        scanf("%s", plateNum);
                        edit = 0;
                        eType = 1;
                        break;
                    }
                    else {
                        edit = 0;
                        fclose(CarMan);
                        printf("\n");
                        return 0;
                        break;
                    }
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                    AddLoop(editselec, &Car);
                    break;
                default:
                    printf("Yikes...That isn't a valid option\n");
                    break;
                }
            }
        }
        LinkyListAp(&AllCars, Car);
        fclose(CarMan);
    }
    printf("\n");
    return 0;
}

int Delete() {
    //Stores the license plate number to be deleted and indicates if the user wishes to return to MM
    const char plateNum[10];
    int totalRead = 0;
    int deleted = 0;
    int line = 1;

    printf("Please enter the license plate number of the car you wish to delete.\n  Press '1' if you wish to return to the main menu:\n");
    scanf("%s", &plateNum);

    if (strcmp(plateNum, "1") != 0) {
        CarMan = fopen("C:\\Users\\HP\\Documents\\Informatica\\Year 1\\Semester 2\\Programming Project\\CarManager.txt", "r");
        Tmp = fopen("C:\\Users\\HP\\Documents\\Informatica\\Year 1\\Semester 2\\Programming Project\\Tmp.txt", "w");
        fprintf(Tmp, "License Plate Number\t Type of Car\t Model Number\t Number of Seats\t Nickname\n");
        //If the file contains no cars
        if (CarMan == NULL) {
            printf("Whoops! Seems Like You Have No Cards in Your Inventory\n\n");
        }

        //Copies contents of CarMan to temporary file
        while (fgets(buffer, BUFFER_SIZE, CarMan) != NULL) {
            totalRead = strlen(buffer); //Counts the total read
            buffer[totalRead - 1] = buffer[totalRead - 1] == '\n' ? '\0' : buffer[totalRead - 1]; //Trim new line character from last if exists.

            printf("%s\n", strstr(buffer, plateNum));

            if (IsSpecial(buffer, plateNum) == 1) {
                deleted = 1;
            }
            else {
                if (line > 1) {
                    fprintf(Tmp, "%s\n", buffer);
                }
            }
            line++;
        }

        //If only the headings exist
        if (line == 1) {
            printf("Nothing Here Yet\n\n");
            fclose(CarMan);
            fclose(Tmp);
            remove("C:\\Users\\HP\\Documents\\Informatica\\Year 1\\Semester 2\\Programming Project\\Tmp.txt");
            return 0;
        }

        //If license plate was found deletes original file and replaces it with temporary file
        if (deleted != 0) {
            fclose(CarMan);
            fclose(Tmp);
            remove("C:\\Users\\HP\\Documents\\Informatica\\Year 1\\Semester 2\\Programming Project\\CarManager.txt");
            rename("C:\\Users\\HP\\Documents\\Informatica\\Year 1\\Semester 2\\Programming Project\\Tmp.txt", "C:\\Users\\HP\\Documents\\Informatica\\Year 1\\Semester 2\\Programming Project\\CarManager.txt");
            printf("%s has been succesfully removed from the database\n\n", plateNum);
        }
        else {
            fclose(CarMan);
            fclose(Tmp);
            remove("C:\\Users\\HP\\Documents\\Informatica\\Year 1\\Semester 2\\Programming Project\\Tmp.txt");
            printf("%s does not exist in the database :(\n\n", plateNum);
        }
    }

    return 0;
}

int Update() {
    //Stores the license plate number to be updated and indicates if the user wishes to return to MM
    struct Acar Car;
    const char plateNum[10];
    int totalRead = 0;
    int updated = 0;
    int editselec, tmpType, line = 1;
    int eType = 1;
    int edit = 1;

    printf("Please enter the license plate number of the car you wish to update.\n  Press '1' if you wish to return to the main menu:\n");
    scanf("%s", &plateNum);

    if (strcmp(plateNum, "1") != 0) {
        CarMan = fopen("C:\\Users\\HP\\Documents\\Informatica\\Year 1\\Semester 2\\Programming Project\\CarManager.txt", "r");
        Tmp = fopen("C:\\Users\\HP\\Documents\\Informatica\\Year 1\\Semester 2\\Programming Project\\Tmp.txt", "w+");
        fprintf(Tmp, "License Plate Number  Type of Car  Model Number  Number of Seats  Nickname\n");
        //If the file contains no cars
        if (CarMan == NULL) {
            printf("Nothing Here Yet\n\n");
        }

        //Copies contents of CarMan to temporary file
        while (fgets(buffer, BUFFER_SIZE, CarMan) != NULL) {
            totalRead = strlen(buffer);                                                             //Counts the total read
            buffer[totalRead - 1] = buffer[totalRead - 1] == '\n' ? '\0' : buffer[totalRead - 1];    //Trim new line character from last if exists.

            //If license number is not contained on the line copies line to temporary file
            if (IsSpecial(buffer, plateNum) == 0) {
                if (line != 1) {
                    fprintf(Tmp, "%s\n", buffer);
                }
            }
            else {
                int subRead = 0;
                int i = 0;
                int j = 0;
                int seg = 0;
   
                while (seg < 5) {
                   
                    if (isspace(buffer[i])) {
                        while (isspace(buffer[i])) {
                            i++;
                        }
                    }

                    char tmp[16] = {'\0'};
                    while (!isspace(buffer[i]) && i <= totalRead) {
                        tmp[j] = buffer[i];
                        i++;
                        j++;
                    }

                    j = 0;
                    switch (seg) {
                    case 0:
                        printf("%s\n", tmp);
                        strcpy(Car.license, tmp);
                        break;
                    case 1:
                        printf("%s\n", tmp);
                        strcpy(Car.type, tmp);
                        break;
                    case 2:
                        printf("%s\n", tmp);
                        strcpy(Car.modelnum, tmp);
                        break;
                    case 3:
                        printf("%s\n", tmp);
                        Car.seatnum = atoi(tmp);
                        break;
                    case 4:
                        printf("%s\n", tmp);
                        strcpy(Car.nickyname, tmp);
                        break;
                    }
                    seg++;
                }
            

                printf("%s\n 1. License Plate Number: %s\n 2. Car Type: %s\n 3. Car Model: %s\n 4. Seat Number: %d", Car.nickyname, Car.license, Car.type, Car.modelnum, Car.seatnum);
                printf("\n\nSelect the corresponding number of the item you wish to update or hit 0 if you changed your mind\n");
                scanf("%d", &editselec);

                while (edit == 1) {
                    switch (editselec) {
                    case 0:
                        updated = 1;
                        edit = 0;
                        break;
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                        AddLoop(editselec, &Car);
                        printf("Just to verify, is the data entered correct?\n\n");
                        printf("%s\n 1. License Plate Number: %s\n 2. Car Type: %s\n 3. Car Model: %s\n 4. Seat Number: %d", Car.nickyname, Car.license, Car.type, Car.modelnum, Car.seatnum);
                        printf("\n\nSelect the corresponding number of the item you wish to modify or hit 0 if it's all good\n");
                        scanf("%d", &editselec);
                        break;
                    default:
                        printf("Yikes...That isn't a valid option\n");
                        printf("\n\nSelect the corresponding number of the item you wish to modify or hit 0 if it's all good\n");
                        scanf("%d", &editselec);
                        break;
                    }
                }

                LinkyListAp(&AllCars, Car);
                fprintf(Tmp, "%20s%13s%14s%17d%10s\n", Car.license, Car.type, Car.modelnum, Car.seatnum, Car.nickyname);
                updated = 1;
            }

            line++;
        }

        //If license plate was found deletes original file and replaces it with temporary file
        if (updated != 0) {
            fclose(Tmp);
            fclose(CarMan);
            remove("C:\\Users\\HP\\Documents\\Informatica\\Year 1\\Semester 2\\Programming Project\\CarManager.txt");
            rename("C:\\Users\\HP\\Documents\\Informatica\\Year 1\\Semester 2\\Programming Project\\Tmp.txt", "C:\\Users\\HP\\Documents\\Informatica\\Year 1\\Semester 2\\Programming Project\\CarManager.txt");
            printf("%s has been succesfully updated\n\n", plateNum);
        }
        else {
            fclose(Tmp);
            fclose(CarMan);
            remove("C:\\Users\\HP\\Documents\\Informatica\\Year 1\\Semester 2\\Programming Project\\Tmp.txt");
            printf("%s does not exist in the database :(\n\n", plateNum);
        }
    }
    return 0;
}

int Search() {
    const char plateNum[10];
    int totalRead = 0;
    int anotherOne = 1, inside = 0, edit;
    int line = -1;
    char header[78] = { '\0' };
    printf("Please enter the license plate number of the car you wish to find.\n  Press '1' if you wish to return to the main menu:\n");
    scanf("%s", &plateNum);

    if (strcmp(plateNum, "1") != 0) {
        while (anotherOne == 1) {
            CarMan = fopen("C:\\Users\\HP\\Documents\\Informatica\\Year 1\\Semester 2\\Programming Project\\CarManager.txt", "r");
            //If the file contains no cars
            if (CarMan == NULL) {
                printf("Nothing Here Yet\n\n");
            }

            //Copies contents of CarMan to temporary file
            while (fgets(buffer, BUFFER_SIZE, CarMan) != NULL) {
                totalRead = strlen(buffer);                                                             //Counts the total read
                buffer[totalRead - 1] = buffer[totalRead - 1] == '\n' ? '\0' : buffer[totalRead - 1];    //Trim new line character from last if exists.
                line++;

                if (line == 0) {
                    strcpy(header, buffer);
                }
                //If license number is contained on the line copies prints line
                if (IsSpecial(buffer, plateNum) != 0) {
                    printf("%s\n%s\n", header, buffer);
                    printf("\nDetails for %s\n", plateNum);
                    inside = 1;
                }
            }

            if (inside != 1) {
                printf("Hmmm... %s doesn't seem to be in the database yet\n\n", plateNum);
            }
            printf("Wanna search for another car?\n'0' for no, '1' for yes\n");
            scanf("%d", &anotherOne);

            if (anotherOne == 1) {
                printf("Please enter the license plate number of the car you wish to find\n");
                scanf("%s", &plateNum);
                inside = 0;
            }
            else {
                fclose(CarMan);
                return 0;
            }
        }
    }
    fclose(CarMan);
    return 0;
}

int Make() {
    char startDate[9], endDate[9];
    char oldSDate[9], oldEDate[9];
    int isValidS = 0;
    int isValidE = 0;
    int totalRead = 0;
    char plateNum[10], resNum[10];
    int endBeforeC = 0;
    int Contained = 1;
    char line = -1;

    printf("Please enter the reservation number of the rental. Or press '1' if you wish to return to the main menu:\n");
    scanf("%s", resNum);

    Res = fopen("C:\\Users\\HP\\Documents\\Informatica\\Year 1\\Semester 2\\Programming Project\\CarReservations.txt", "a+");

    if (strcmp(resNum, "1") != 0) {
        while (fgets(buffer, BUFFER_SIZE, Res) != NULL) {
            totalRead = strlen(buffer);                                                             //Counts the total read
            buffer[totalRead - 1] = buffer[totalRead - 1] == '\n' ? '\0' : buffer[totalRead - 1];    //Trim new line character from last if exists.

            //If license number is contained on the line copies prints line
            if (IsSpecial(buffer, resNum)) {
                printf("\nThere's already a reservation with this number...\n", plateNum);
                printf("Start Date  End Date  License Plate Number  Reservation Number\n");
                printf("%s\nReservations cannot be changed but they can be cancelled\n\n", buffer);
                fclose(Res);
                return 0;
            }
        }

        printf("Please enter the license plate number of the car you want to make a reservation for\n");
        scanf("%s", plateNum);

        CarMan = fopen("C:\\Users\\HP\\Documents\\Informatica\\Year 1\\Semester 2\\Programming Project\\CarManager.txt", "r");

        if (CarMan == NULL) {
            printf("You gotta have cars to make a reservation man. Hit '1' to add some cars and start making bank\n");
        }

        while (fgets(buffer, BUFFER_SIZE, CarMan) != NULL) {
            totalRead = strlen(buffer);                                                             //Counts the total read
            buffer[totalRead - 1] = buffer[totalRead - 1] == '\n' ? '\0' : buffer[totalRead - 1];    //Trim new line character from last if exists.

            //Validates license pate number is contained in the file
            if (IsSpecial(buffer, plateNum)) {
                Contained = 0;
                fclose(CarMan);
            }           
        }

        if (Contained == 1) {
            printf("%s isn't apart of the car fleet. Hit '1' to add it and start making reservations!\n");
            fclose(Res);
            fclose(CarMan);
            return 0;
        }

        while (isValidS == 0) {
            printf("Please enter the start date of the rental\n");
            scanf("%s", startDate);
            isValidS = DateValidation(startDate);
        }

        rewind(Res);

        //If license number is present for the exact start date informs user and breaks
        while (fgets(buffer, BUFFER_SIZE, Res) != NULL) {
            totalRead = strlen(buffer);                                                             //Counts the total read
            buffer[totalRead - 1] = buffer[totalRead - 1] == '\n' ? '\0' : buffer[totalRead - 1];    //Trim new line character from last if exists.

            if ((IsSpecial(buffer, plateNum)) == 1 && (IsSpecial(buffer, startDate)) == 1 ) {
                printf("Oop. This is awkward. %s is already booked for that date.\n", plateNum);
                printf("%s\n\n", buffer);
                return 0;
            }
        }

        //Checks if the entered start date is before the entered end date
        while (endBeforeC == 0) {
            while (isValidE == 0) {
                printf("Please enter the end date of the rental\n");
                scanf("%s", endDate);
                isValidE = DateValidation(endDate);
            }
            if (DateComparison(endDate, startDate) == 0) {
                printf("We can't end a rental before it begins silly. Enter an end date which is later than the start date.\n");
                isValidE = 0;
            }
            else {
                endBeforeC = 1;
            }
        }
        rewind(Res);

        //Checks if the car is available for the specified period
        while (fgets(buffer, BUFFER_SIZE, Res) != NULL) {
            totalRead = strlen(buffer);                                                             //Counts the total read
            buffer[totalRead - 1] = buffer[totalRead - 1] == '\n' ? '\0' : buffer[totalRead - 1];    //Trim new line character from last if exists.
            line++;

            //If license number is contained on the line validates if the newly entered dates are after or before established dates
            if (IsSpecial(buffer, plateNum) && line != 0) {
                int counterA = 0, i = 0, j = 0;
                while (counterA < 2) {
                    if (isspace(buffer[i])) {
                        while (isspace(buffer[i])) {
                            i++;
                        }
                    }
                    else {
                        char tmp[9] = {'\0'};
                        while (!isspace(buffer[i]) && i <= totalRead) {
                            tmp[j] = buffer[i];
                            i++;
                            j++;
                        }
                        j = 0;
                        if (counterA == 0) {
                            strcpy(oldSDate, tmp);
                        }
                        else {
                            strcpy(oldEDate, tmp);
                        }
                        counterA++;
                    }
                }

                if ((DateComparison(startDate, oldSDate) == 0 && DateComparison(oldSDate, endDate) == 0) || (DateComparison(oldSDate, startDate) == 0 && DateComparison(endDate, oldEDate) == 0) || (DateComparison(startDate, oldEDate) == 0 && DateComparison(oldEDate, endDate) == 0)) {
                    printf("Oop. This is awkward. %s is already booked during that period.\n", plateNum);
                    printf("%s\n\n", buffer);
                    return 0;
                }
            }
        }

        FormatDate(startDate);
        FormatDate(endDate);
        printf("%s\t%s\n", plateNum, resNum);

        fprintf(Res, "%10s%10s%22s%20s\n", startDate, endDate, plateNum, resNum);
        fclose(Res);

    }
    return 0;
}

int Cancel() {
    //Stores the reservation number to be deleted and indicates if the user wishes to return to MM
    char resNum[10], plateNum[10];
    int totalRead = 0;
    int line = 0, deleted = 0;

    printf("Please enter the reservation number of the rental. Or press '1' if you wish to return to the main menu:\n");
    scanf("%s", &resNum);

    if (strcmp(resNum, "1") != 0) {
        Res = fopen("C:\\Users\\HP\\Documents\\Informatica\\Year 1\\Semester 2\\Programming Project\\CarReservations.txt", "r");
        Tmp = fopen("C:\\Users\\HP\\Documents\\Informatica\\Year 1\\Semester 2\\Programming Project\\Tmp.txt", "w");
        if (Res == NULL) {
            printf("Nothing Here Yet\n\n");
            return 0;
        }

        //Copies contents of Res to temporary file
        while (fgets(buffer, BUFFER_SIZE, Res) != NULL) {
            totalRead = strlen(buffer); //Counts the total read
            buffer[totalRead - 1] = buffer[totalRead - 1] == '\n' ? '\0' : buffer[totalRead - 1]; //Trim new line character from last if exists.
            line++;

            if (IsSpecial(buffer, resNum)) {
                deleted = 1;
            }
            else {
                fprintf(Tmp, "%s\n", buffer);
            }
        }

        //If only the headings exist
        if (line == 0) {
            printf("Nothing Here Yet\n\n");
            fclose(Res);
            fclose(Tmp);
            remove("C:\\Users\\HP\\Documents\\Informatica\\Year 1\\Semester 2\\Programming Project\\Tmp.txt");
            return 0;
        }

        //If license plate was found deletes original file and replaces it with temporary file
        if (deleted != 0) {
            fclose(Res);
            fclose(Tmp);
            remove("C:\\Users\\HP\\Documents\\Informatica\\Year 1\\Semester 2\\Programming Project\\CarReservations.txt");
            rename("C:\\Users\\HP\\Documents\\Informatica\\Year 1\\Semester 2\\Programming Project\\Tmp.txt", "C:\\Users\\HP\\Documents\\Informatica\\Year 1\\Semester 2\\Programming Project\\CarReservations.txt");
            printf("Booking %s has been succesfully removed from the database\n\n", resNum);
        }
        else {
            fclose(Res);
            fclose(Tmp);
            remove("C:\\Users\\HP\\Documents\\Informatica\\Year 1\\Semester 2\\Programming Project\\Tmp.txt");
            printf("The %s booking does not exist in the database :(\n\n", resNum);
        }
    }
    return 0;
}

int View() {
    char startDate[9], endDate[9];
    char oldSDate[9], oldEDate[9];
    int line = -1;
    int isValidS = 0;
    int isValidE = 0;
    int totalRead = 0;
    int endBeforeC = 0;
    int inPrd = 0;
    char header[90] = { '\0' };

    printf("Please enter the the period you wish to view (DD/MM/YYYY).\nYou can also:\n 1. Return to the main menu \t 2. View all resevations \t 3. View all cars in inventory:\n");
    scanf("%s", &startDate);

    //View cars by avaliablity periods
    if (strcmp(startDate, "1") == 0) {
        return 0;
    }
    else if (strcmp(startDate, "2") == 0) {     //print all cars with rentals
        Res = fopen("C:\\Users\\HP\\Documents\\Informatica\\Year 1\\Semester 2\\Programming Project\\CarReservations.txt", "r");
        if (Res == NULL) {
            printf("Nothing Here Yet");
            return 0;
        }
        else {
            while (fgets(buffer, BUFFER_SIZE, Res) != NULL) {
                totalRead = strlen(buffer);                                                             //Counts the total read
                buffer[totalRead - 1] = buffer[totalRead - 1] == '\n' ? '\0' : buffer[totalRead - 1];    //Trim new line character from last if exists.
                line++;

                if (line == 0) {
                    strcpy(header, buffer);
                }
                else {
                    if (line == 1) {
                        printf("%s\n", header);
                    }
                    printf("%s\n", buffer);
                }
            }

            if (line == 0) {
                printf("Nothing Here Yet");
            }
        }
        fclose(Res);
        return 0;
    }
    else if (strcmp(startDate, "3") == 0) {         //Print all cars in inventory
        CarMan = fopen("C:\\Users\\HP\\Documents\\Informatica\\Year 1\\Semester 2\\Programming Project\\CarManager.txt", "r");
        if (CarMan == NULL) {
            printf("Nothing Here Yet");
            return 0;
        }
        else {
            while (fgets(buffer, BUFFER_SIZE, CarMan) != NULL) {
                totalRead = strlen(buffer);                                                             //Counts the total read
                buffer[totalRead - 1] = buffer[totalRead - 1] == '\n' ? '\0' : buffer[totalRead - 1];    //Trim new line character from last if exists.
                line++;

                if (line == 0) {
                    strcpy(header, buffer);
                }
                else {
                    if (line == 1) {
                        printf("%s\n", header);
                    }
                    printf("%s\n", buffer);
                }
            }

            if (line == 0) {
                printf("Nothing Here Yet");
            }
        }
        fclose(CarMan);
        return 0;
    }
    else {      //print for specified period
        Res = fopen("C:\\Users\\HP\\Documents\\Informatica\\Year 1\\Semester 2\\Programming Project\\CarReservations.txt", "r");
      
        //Checks if the entered start date is before the entered end date
        while (endBeforeC == 0) {
            while (isValidE == 0) {
                printf("Please enter the end date of the rental period\n");
                scanf("%s", &endDate);
                isValidE = DateValidation(endDate);
            }
            if (DateComparison(startDate, endDate) != 0) {
                printf("We can't end a rental before it begins silly. Enter an end date which is later than the start date.\n");
                isValidE = 0;
            }
            else {
                isValidE = 1;
                endBeforeC = 1;
            }
        }

        //Checks if the car is available for the specified period
        while (fgets(buffer, BUFFER_SIZE, Res) != NULL) {
            totalRead = strlen(buffer);                                                             //Counts the total read
            buffer[totalRead - 1] = buffer[totalRead - 1] == '\n' ? '\0' : buffer[totalRead - 1];    //Trim new line character from last if exists.
            line++;
            if (line != 0) {
                //Parses Start Date and End Date from buffer
                int counterA = 0, i = 0, j = 0;
                while (counterA < 2) {
                    if (isspace(buffer[i])) {
                        while (isspace(buffer[i])) {
                            i++;
                        }
                    }
                    else {
                        char tmp[9] = { '\0' };
                        while (!isspace(buffer[i]) && i <= totalRead) {
                            tmp[j] = buffer[i];
                            i++;
                            j++;
                        }
                        j = 0;
                        if (counterA == 0) {
                            strcpy(oldSDate, tmp);
                        }
                        else {
                            strcpy(oldEDate, tmp);
                        }
                        counterA++;
                    }
                }

                //Compares entered dates to dates from file to determine if they are within the range
                if (DateComparison(startDate, oldSDate) == 0 && DateComparison(oldEDate, endDate) == 0) {
                    printf("%s\n", buffer);
                    inPrd = 0;
                }
            }
        }
        if (inPrd == 1) {
            printf("Oh! There are no bookings for this period\n\n");
        }
        fclose(Res);
    }

    return 0;
}

///Main Menu Function
int Menu() {
    // Switch variable for selection of menu
    int menuselec = -1;

    // end variable for termination of loop
    int end = 1;

    // Infinite Loop until user terminates operation via menuselec
    while (end) {
        // Menu display
        printf("%s***********************\n", AC_GREEN);
        printf(" Your Perf Car Manager \n");
        printf("***********************");
        printf("\n1. Add a Car\n2. Delete a Car\n3. Update a Car\n4. Search for a Car\n\n5. Make a Reservation\n6. Cancel Reservation\n7. View Available Cars\n8. Exit\n");

        printf("\nPlease select an option by typing the corresponding number:\n ");
        scanf("%d", &menuselec);

        // Menu Selection
        switch (menuselec) {
        case 1:
            Add();
            break;
        case 2:
            Delete();
            break;
        case 3:
            Update();
            break;
        case 4:
            Search();
            break;
        case 5:
            Make();
            break;
        case 6:
            Cancel();
            break;
        case 7:
            View();
            break;
        case 8:
            printf("Ciao!\n");
            end = 0;  // To terminate the loop
            break;
        default:
            printf("Yikes...That isn't a valid option\n");
            break;
        }
    }
}


int main() {
    int totalRead = 0;
    CarMan = fopen("C:\\Users\\HP\\Documents\\Informatica\\Year 1\\Semester 2\\Programming Project\\CarManager.txt", "r");
    if(CarMan == NULL) {
        CreateCarMan();
    }
    else {
        fclose(CarMan);
    }
   

    Res = fopen("C:\\Users\\HP\\Documents\\Informatica\\Year 1\\Semester 2\\Programming Project\\CarReservations.txt", "r");
    if( Res == NULL) {
        CreateRes();
    }
    else {
        fclose(Res);
    }

    printf("", AC_GREEN);

    Menu();
    return 0;
}

