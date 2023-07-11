#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include "diary.h"

int key_availablity[2000005];

int main()
{

    while (1)
    {
        system("cls");
        char s[100];
        long long a, b;
        FILE *fp = fopen("pss", "r");


        printf(">> WELCOME TO YOUR SECURE PERSONAL DIARY\n\n");
        printf(">> LOGIN MENU: \n\n");
        if (fp == NULL)
        {
            fclose(fp);
            printf(">> SET A NEW PASSWORD: ");

            //fflush(stdin);
            //gets(s);
            setpass();
            printf(">> Password set successfully! \nPress any key to continue");
            getch();
            continue;
        }

        printf(">> ENTER PASSWORD (Type \"q\" to exit): ");
        fflush(stdin);
        gets(s);

        if (strcmp(s, "q") == 0) break;

        a = HASH(s);
        //fprintf(fp,"%lld\n", h);
        //puts(s);
        //fscanf(fp, "%lld", &b);
        fread(&b, sizeof(b), 1, fp);
        fclose(fp);

        if (a == b) {
            printf(">> Password matched!\n");
            delay(1);
            menu();
        }
        else {
            printf("!! Wrong password. Try again.\n");
            delay(1);
        }
        //getch();
    }


    return 0;
}
