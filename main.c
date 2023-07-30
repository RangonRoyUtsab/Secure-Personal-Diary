#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>



#define DATE_SIZE 50
#define TIME_SIZE 50
#define NAME_SIZE 500

typedef long long LL;

int user_level = 0;



void delay(int number_of_seconds)
{
    int milli_seconds = 1000 * number_of_seconds;
    clock_t start_time = clock();
    while (clock() < start_time + milli_seconds)
        ;
}

struct record
{
    int privacy_level;
    char time[TIME_SIZE];
    //char title[NAME_SIZE];
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


void show_Time()   // prints the current date and time
{
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
    printf(">> SET A NEW PASSWORD: ");

    FILE *f_pointer;

    if (user_level == 2)
        f_pointer = fopen("admin_pass", "w");
    if (user_level == 1)
        f_pointer = fopen("part_pass", "w");

    if (f_pointer == NULL)
    {
        printf("Password set failed.\n");
        exit(1);
    }

    fflush(stdin);
    char s[30];
    gets(s);
    int h_val = HASH(s);
    fwrite(&h_val, sizeof(h_val), 1, f_pointer);

    if (fwrite != 0)
    {
        printf("** Password set successfully! **\n");
    }
    else
    {
        printf("** Failed to set password. **\n");
    }

    fclose(f_pointer);
}

void add_record()
{
    system("cls");
    show_Time();
    fflush(stdin);

    time_t current_time = time(NULL);
    char date_string[DATE_SIZE], time_string[TIME_SIZE];
    strftime(date_string, DATE_SIZE, "%d-%m-%Y", localtime(&current_time));
    strftime(time_string, TIME_SIZE, "%I:%M %p", localtime(&current_time));

    // display part start
    FILE *f_pointer = fopen(date_string, "r");
    struct record new_record;

    if (f_pointer == NULL)
    {
        printf("No records added today.");
    }
    else
    {
        int i=1;
        printf("Currently added notes today: \n\n");
        while (fread(&new_record, sizeof(struct record), 1, f_pointer))
        {
            if (user_level >= new_record.privacy_level)
            {
                printf("Note no. %d \nTime: %s \nNote: %s \n\n", i, new_record.time, new_record.note);
            }
            else
            {
                // room for displaying a message that the current user does not have the required permission
            }
            i++;
        }
        fclose(f_pointer);
    }
    // display part end

    f_pointer = fopen(date_string, "a");
    if (f_pointer == NULL)
    {
        printf("** Error creating record. **\n");
        exit(1);
    }

    // privacy settings

    printf("Select the privacy type of your note: \n");
    if (user_level >= 0)
        printf("1. Public\n");
    if (user_level >= 1)
        printf("2. Protected\n");
    if (user_level >= 2)
        printf("3. Private\n");
    int choice;
    scanf("%d", &choice);

    switch(choice) {
    case 1:
        new_record.privacy_level = 0;
        break;
    case 2:
        new_record.privacy_level = 1;
        break;
    case 3:
        new_record.privacy_level = 2;
        break;
    default:
        printf("Invalid choice. Exiting.\n");
        delay(1);
        return;
    }


    strcpy(new_record.time, time_string);
    printf("Enter the note: \n>> ");
    fflush(stdin);
    gets(new_record.note);
    fwrite(&new_record, sizeof(struct record), 1, f_pointer);
    fclose(f_pointer);
}


void view_record()
{
    system("cls");
    show_Time();
    fflush(stdin);

    char date_string[DATE_SIZE];
    printf("Enter the date: ");
    fflush(stdin);
    gets(date_string);

    FILE *f_pointer = fopen(date_string, "r");
    if (f_pointer == NULL)
    {
        printf("** Record does not exist. **\n");
        return;
    }

    struct record new_record;
    int i=1;
    while (fread(&new_record, sizeof(struct record), 1, f_pointer))
    {
        if (user_level >= new_record.privacy_level)
        {
            printf("Note no. %d \nTime: %s \nNote: %s \n\n", i, new_record.time, new_record.note);
        }
        else
        {
            // room for displaying a message that the current user does not have the required permission
        }
        i++;
    }
    fclose(f_pointer);
}


void modify_record()
{
    system("cls");
    show_Time();
    fflush(stdin);

    // view part
    char date_string[DATE_SIZE];
    printf("Enter the date: ");
    fflush(stdin);
    gets(date_string);

    FILE *f_pointer = fopen(date_string, "r");
    if (f_pointer == NULL)
    {
        printf("** Record does not exist. **\n");
        return;
    }

    struct record new_record;
    int i=1;
    while (fread(&new_record, sizeof(struct record), 1, f_pointer))
    {
        if (user_level >= new_record.privacy_level)
        {
            printf("Note no. %d \nTime: %s \nNote: %s \n\n", i, new_record.time, new_record.note);
        }
        else
        {
            // room for displaying a message that the current user does not have the required permission
        }
        i++;
    }
    // view part

    printf("Enter the no of note you want to modify: ");
    fflush(stdin);
    int k;
    char option;
    scanf("%d", &k);

    rewind(f_pointer);
    char temp_name[] = "temp_file";
    FILE *tmp = fopen(temp_name, "a");
    if (f_pointer == NULL)
    {
        printf("** System error. Exiting program. **\n");
        delay(1);
        exit(1);
    }
    i=1;
    while (fread(&new_record, sizeof(struct record), 1, f_pointer))
    {
        if (i == k)
        {
            printf("Do you want to modify the time? (y/n) :: ");
            fflush(stdin);
            option = getchar();
            if (option == 'y')
            {
                printf("Enter new time (12:59 AM): ");
                fflush(stdin);
                gets(new_record.time);
                fflush(stdin);
            }
            printf("Do you want to modify the note? (y/n) :: ");
            fflush(stdin);
            option = getchar();
            if (option == 'y')
            {
                printf("Enter new note: ");
                fflush(stdin);
                gets(new_record.note);
                fflush(stdin);
            }

        }
        fwrite(&new_record, sizeof(struct record), 1, tmp);
        i++;
    }
    fclose(tmp);
    fclose(f_pointer);
    remove(date_string);
    rename(temp_name, date_string);

}


void delete_record()
{
    system("cls");
    show_Time();

    char date_string[DATE_SIZE];
    printf("Enter the date: ");
    fflush(stdin);
    gets(date_string);

    remove(date_string);

    printf("** Record deleted successfully **\n");

}
void password_change()
{
    system("cls");
    if (user_level <= 0) {
        printf("Sorry, this option is not applicable for the guest.\n");
        delay(1);
        return;
    }
    printf("Enter old password: ");
    fflush(stdin);
    char tmp[30];
    int a, b;
    gets(tmp);
    a = HASH(tmp);

    FILE *fp = fopen("password_file", "r");
    fread(&b, sizeof(b), 1, fp);
    fclose(fp);

    if (a == b)
    {
        setpass();
    }
    else
    {
        printf("Password didn't match!. Try again.\n");
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
        printf("Current User: ");
        switch(user_level) {
        case 0:
            printf("Guest\n");
            break;
        case 1:
            printf("Life Partner\n");
            break;
        case 2:
            printf("Admin\n");
            break;
        }
        printf("\n");
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
            user_level = 0;
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




int main()
{
    int f=1;
    again:
    while (f)
    {
        system("cls");
        char s[100];
        LL a, b;



        printf(">> WELCOME TO YOUR SECURE PERSONAL DIARY\n\n");
        printf(">> LOGIN MENU: \n\n");


        printf(">> SELECT USER: \n");
        printf(">> 1. Admin\n");
        printf(">> 2. Life Partner\n");
        printf(">> 3. Guest\n");
        printf(">> 4. Exit\n");


        int choice;
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            user_level = 2;
            break;
        case 2:
            user_level = 1;
            break;
        case 3:
            user_level = 0;
            break;
        case 4:
            exit(1);
        default:
            printf("Invalid Choice.\n");
            delay(1);
            goto again;

        }


        if (user_level == 0)
        {
            menu();
        }

        else
        {
            FILE *fp;

            if (user_level == 2)
            {
                fp = fopen("admin_pass", "r");

                if (fp == NULL)
                {
                    setpass();
                    printf(">> Press any key to continue");
                    getch();
                    continue;
                }
            }
            if (user_level == 1) {
                fp = fopen("part_pass", "r");

                if (fp == NULL)
                {
                    setpass();
                    printf(">> Press any key to continue");
                    getch();
                    continue;
                }
            }




            printf(">> ENTER PASSWORD (Type \"q\" to exit): ");
            fflush(stdin);
            gets(s);

            if (strcmp(s, "q") == 0) break;

            a = HASH(s);
            fread(&b, sizeof(b), 1, fp);
            fclose(fp);

            if (a == b)
            {
                printf(">> Password matched!\n");
                delay(1);
                menu();
            }
            else
            {
                printf("!! Wrong password. Try again.\n");
                delay(1);
            }
        }
    }
    return 0;
}
