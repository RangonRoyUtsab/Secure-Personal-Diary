#ifndef DIARY_H_INCLUDED
#define DIARY_H_INCLUDED

#include <time.h>

#define DATE_SIZE 20
#define TIME_SIZE 20
#define NAME_SIZE 500

void delay(int number_of_seconds)
{
    int milli_seconds = 1000 * number_of_seconds;
    clock_t start_time = clock();
    while (clock() < start_time + milli_seconds)
        ;
}

struct record
{
    char title[NAME_SIZE];
    char time[TIME_SIZE];
    char note[NAME_SIZE];
};

int HASH(char* pass)
{
    int n = strlen(pass);
    int h=0;
    for (int i=0; i<n; i++)
    {
        h += ((i+1)*pass[i]);
    }
    return h;
}

int HASH2(char* key)
{
    int n = strlen(key);
    int h=0;
    for (int i=0; i<n; i++)
    {
        h += ((i+1)*key[i]);
    }
    return (h%2000005);
}


void setpass()
{
    FILE *st;
    st = fopen("pss", "w");

    if (st == NULL) {
        printf("pass set failed.\n");
        return;
    }

    char s[30];
    gets(s);
    int h_val = HASH(s);
    //fprintf(st, "%lld\n", h_val);
    fwrite(&h_val, sizeof(h_val), 1, st);
    fclose(st);
}

void add_record()
{
    system("cls");
    time_t tm2;
    time(&tm2);
    printf("Current Date/Time = %s\n\n", ctime(&tm2));

    char date[DATE_SIZE], time[TIME_SIZE], keyword[NAME_SIZE];
    printf("Enter the date (dd-mm-yyyy): ");
    fflush(stdin);
    gets(date);
    FILE* rec_f;
    rec_f = fopen(date, "a+");
    struct record rec;

    printf("Enter the time [in 24 hour format] (hh-mm): ");
    fflush(stdin);
    gets(rec.time);
    printf("Enter the title: ");
    fflush(stdin);
    gets(rec.title);
    printf("Enter the note: (press ENTER when finished) \n");
    fflush(stdin);
    gets(rec.note);

    fwrite(&rec, sizeof(rec), 1, rec_f);
    fclose(rec_f);
    printf("Record was added successfully.\n");
}


void view_record()
{
    system("cls");
    time_t tm2;
    time(&tm2);
    printf("Current Date/Time = %s\n\n", ctime(&tm2));

    char date[DATE_SIZE], time[TIME_SIZE], keyword[NAME_SIZE];
    printf("Enter the date (dd-mm-yyyy): ");
    fflush(stdin);
    //gets(date);
    scanf("%s", date);
    FILE* rec_f;
    rec_f = fopen(date, "r+");
    struct record rec;

    if (rec_f == NULL)
    {
        printf("Sorry the record does not exist. \nReturning to the main menu.\n");
        delay(1);
    }
    else
    {
        printf("Displaying the record for the date %s :\n\n\n", date);
        while(fread(&rec, sizeof(rec), 1, rec_f) == 1)
        {
            printf("%s: %s\n\n", rec.time, rec.title);
            int len=0;
            int cnt=0;

            /*
            while (rec.note[len] != '\0')
            {
                if (cnt > 50 && rec.note[len] == ' ')
                {
                    printf("\n");
                    cnt = 0;
                }
                else
                {
                    printf("%c", rec.note[len]);
                    cnt++;
                }
                len++;

            }
            */

            printf("\t%s\n", rec.note);
            printf("\n\n\n");
        }
        printf("\n\n");
    }
    printf("\n");
    fclose(rec_f);

}


void modify_record()
{
    system("cls");
    time_t tm2;
    time(&tm2);
    printf("Current Date/Time = %s\n\n", ctime(&tm2));

    char date[DATE_SIZE], time[TIME_SIZE], keyword[NAME_SIZE];
    printf("Enter the date (dd-mm-yyyy): ");
    fflush(stdin);
    gets(date);
    FILE* rec_f;
    rec_f = fopen(date, "r+");
    struct record rec;

    if (rec_f == NULL)
    {
        printf("Sorry the record does not exist. \nReturning to the main menu.\n");
        delay(1);
    }
    else
    {
        printf("Enter the time [in 24 hour format] (hh-mm): ");
        fflush(stdin);
        gets(time);
        while(fread(&rec, sizeof(rec), 1, rec_f) == 1)
        {
            if (strcmp(rec.time, time) == 0)
            {
                printf("Enter new title: ");
                fflush(stdin);
                gets(rec.title);
                printf("Enter new note: (press ENTER when finished) \n");
                fflush(stdin);
                gets(rec.note);
            }
        }
    }
    fclose(rec_f);
    printf("Record was modified successfully.\n");
}


void delete_record()
{
    system("cls");
    time_t tm2;
    time(&tm2);
    printf("Current Date/Time = %s\n\n", ctime(&tm2));

    char date[DATE_SIZE], time[TIME_SIZE], keyword[NAME_SIZE];
    printf("Enter the date (dd-mm-yyyy): ");
    fflush(stdin);
    gets(date);
    FILE* rec_f;
    rec_f = fopen(date, "r+");

    struct record rec;

    if (rec_f == NULL)
    {
        printf("Sorry the record does not exist. \nReturning to the main menu.\n");
        delay(1);
    }
    else
    {
        printf("Select one of the options: \n");
        printf("1. Whole Day.\n");
        printf("2. Specific Time.\n");
        int option;
        scanf("%d", &option);
        switch(option)
        {
        case 1:
        {
            fclose(rec_f);
            remove(date);
            break;
        }
        case 2:
        {
            printf("Displaying the times ans titles of the records for the date %s :\n\n", date);
            while(fread(&rec, sizeof(rec), 1, rec_f) != 0)
            {
                printf("%s: %s\n\n", rec.time, rec.title);
            }
            rewind(rec_f);
            printf("Enter the time [in 24 hour format] (hh-mm): ");

            fflush(stdin);
            gets(time);

            FILE *tmp;
            tmp = fopen("temp", "a+");

            while(fread(&rec, sizeof(rec), 1, rec_f) != 0)
            {
                if (strcmp(rec.time, time) != 0)
                {
                    fwrite(&rec, sizeof(rec), 1, tmp);
                }
            }
            fclose(rec_f);
            fclose(tmp);
            remove(date);
            rename("temp", date);

        }

        }
    }
    //fclose(rec_f);
    printf("Record was deleted successfully.\n");
}
void password_change()
{
    system("cls");
    printf("Password was changed successfully.\n");
}


void menu()
{
    int flag = 1;
    while (flag)
    {
        time_t tm;
        time(&tm);

        system("cls");
        printf("\nCurrent Date/Time = %s\n\n", ctime(&tm));
        printf("Enter your choice: \n");
        printf("1. Add Record\n");
        printf("2. View Record\n");
        printf("3. Modify Record\n");
        printf("4. Delete Record\n");
        printf("5. Change Password\n");
        printf("6. Log Out\n");


        int choice;
        scanf("%d", &choice);
        switch(choice)
        {
        case 1:
        {
            add_record();
            printf("Press any key to continue.\n");
            getch();
            break;
        }
        case 2:
        {
            view_record();
            printf("Press any key to continue.\n");
            getch();
            break;
        }
        case 3:
        {
            modify_record();
            printf("Press any key to continue.\n");
            getch();
            break;
        }
        case 4:
        {
            delete_record();
            printf("Press any key to continue.\n");
            getch();
            break;
        }
        case 5:
        {
            password_change();
            printf("Press any key to continue.\n");
            getch();
            break;
        }
        case 6:
        {
            flag = 0;
            printf("Press any key to continue.\n");
            break;
        }
        default:
        {
            printf("Please enter a valid choice\n");
            delay(2);
            break;
        }
        }
    }
}


#endif // DIARY_H_INCLUDED
