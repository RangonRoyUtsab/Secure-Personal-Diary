#ifndef DIARY_H_INCLUDED
#define DIARY_H_INCLUDED

#include <time.h>

#define DATE_SIZE 50
#define TIME_SIZE 50
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


void show_Time() { // prints the current date and time
    // Get the current time
    time_t current_time = time(NULL);

    // Convert the time to a string using the desired format
    char date_string[20];
    strftime(date_string, 20, "%d-%m-%Y", localtime(&current_time));

    char time_string[10];
    strftime(time_string, 10, "%I:%M %p", localtime(&current_time));

    // Print the date string
    printf("The current date is: %s\n", date_string);
    printf("The current time is: %s\n\n", time_string);
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
    show_Time();

    char date[DATE_SIZE], Time[TIME_SIZE], keyword[NAME_SIZE];

    // Get the current time
    time_t current_time = time(NULL);
    strftime(date, DATE_SIZE, "%d-%m-%Y", localtime(&current_time));
    strftime(Time, TIME_SIZE, "%I:%M %p", localtime(&current_time));

    if (strcmp(date, "q") == 0) return; // for going back

    FILE* rec_f;
    rec_f = fopen(date, "a+");
    struct record rec;

     fflush(stdin);
    strcpy(rec.time, Time);
    fflush(stdin);
    printf("Enter the title: ");
    fflush(stdin);
    gets(rec.title);
    printf("Enter the note: (press ENTER when finished) \n");
    fflush(stdin);
    gets(rec.note);
    fflush(stdin);

    fwrite(&rec, sizeof(struct record), 1, rec_f);
    fclose(rec_f);
    printf("Record was added successfully.\n");
}


void view_record()
{
    system("cls");
    show_Time();

    char date[DATE_SIZE], time[TIME_SIZE], keyword[NAME_SIZE];
    printf("Enter the date (dd-mm-yyyy) (type 'q' return): ");
    fflush(stdin);
    //gets(date);
    scanf("%s", date);

    if (strcmp(date, "q") == 0) return; // for going back

    FILE* rec_f = fopen(date, "r");
    struct record rec;

    if (rec_f == NULL)
    {
        printf("Sorry the record does not exist. \nReturning to the main menu.\n");
        delay(1);
    }
    else
    {
        printf("Displaying the record for the date %s :\n\n\n", date);
        while(fread(&rec, sizeof(struct record), 1, rec_f))
        {
            //printf("%s: %s\n\n", rec.time, rec.title);
            //printf("\t%s\n", rec.note);
            puts(rec.time);
            puts(rec.title);
            puts(rec.note);
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
    show_Time();

    char date[DATE_SIZE], time[TIME_SIZE], keyword[NAME_SIZE];
    printf("Enter the date (dd-mm-yyyy) (type 'q' return): ");
    fflush(stdin);
    gets(date);

    if (strcmp(date, "q") == 0) return; // for going back

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
    show_Time();

    char date[DATE_SIZE], time[TIME_SIZE], keyword[NAME_SIZE];
    printf("Enter the date (dd-mm-yyyy) (type 'q' return): ");
    fflush(stdin);
    gets(date);

    if (strcmp(date, "q") == 0) return; // for going back

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
    printf("Enter old password: ");
    fflush(stdin);
    char tmp[30];
    int a, b;
    gets(tmp);
    a = HASH(tmp);

    FILE *fp = fopen("pss", "r");
    fread(&b, sizeof(b), 1, fp);
    fclose(fp);

    if (a == b) {
        printf("Enter new password: ");
        fflush(stdin);
        setpass();
        printf("Password was changed successfully.\n");
    }
    else {
        printf("Password didn't match!\n");
    }
    delay(1);
}


void menu()
{
    int flag = 1;
    while (flag)
    {
        system("cls");
        show_Time();

        printf(">> Enter your choice: \n");
        printf("1. Add Record\n");
        printf("2. View Record\n");
        printf("3. Modify Record\n");
        printf("4. Delete Record\n");
        printf("5. Change Password\n");
        printf("6. Log Out\n");
        printf(">> Choice: ");


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
