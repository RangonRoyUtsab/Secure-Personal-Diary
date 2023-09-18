#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "diary.h"
#include "hash.h"      // contains the hashing functions
#include "misc.h"      // contains delay() & show_Time()
#include "password.h"  //contains setpass() & password_change()
#include "test_header.h"

#define DATE_SIZE 50
#define TIME_SIZE 50
#define NAME_SIZE 500

typedef long long LL;

int user_level = 0;

void menu() {
  int flag = 1, choice;
  char ch;
  while (flag) {
    system("cls");
    show_Time();
    printf("Current User: ");
    switch (user_level) {
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
    printf(">> MENU << \n");
    printf("1. Add Record\n");
    printf("2. View Record\n");
    printf("3. Modify Record\n");
    printf("4. Delete Record\n");
    printf("5. Change Password\n");
    printf("6. Log Out\n");
    printf(">> Enter your choice: ");

    ch = _getch();
    choice = ch - '0';
    printf("%d\n", choice);
    // delay(1);
    switch (choice) {
      case 1: {
        add_record(user_level);
        printf("Press any key to continue.\n");
        getch();
        break;
      }
      case 2: {
        view_record(user_level);
        printf("Press any key to continue.\n");
        getch();
        break;
      }
      case 3: {
        modify_record(user_level);
        printf("Press any key to continue.\n");
        getch();
        break;
      }
      case 4: {
        delete_record(user_level);
        printf("Press any key to continue.\n");
        getch();
        break;
      }
      case 5: {
        password_change(user_level);
        printf("Press any key to continue.\n");
        getch();
        break;
      }
      case 6: {
        flag = 0;
        user_level = 0;
        printf("Press any key to continue.\n");
        break;
      }
      default: {
        printf("Please enter a valid choice\n");
        delay(1);
        break;
      }
    }
  }
}

int main() {
  int f = 1;
again:
  while (f) {
    system("cls");
    char s[100];
    char ch;
    int choice, j;
    LL a, b;

    printf(">> WELCOME TO YOUR SECURE PERSONAL DIARY\n\n");
    printf(">> LOGIN MENU: \n\n");

    printf(">> SELECT USER: \n");
    printf(">> 1. Admin\n");
    printf(">> 2. Life Partner\n");
    printf(">> 3. Guest\n");
    printf(">> 4. Exit\n");

    printf(">> Choice: ");
    ch = _getch();
    choice = ch - '0';
    printf("%d\n", choice);
    // delay(1);

    switch (choice) {
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

    if (user_level == 0) {
      menu();
    }

    else {
      FILE *fp;

      if (user_level == 2) {
        fp = fopen("admin_pass", "r");

        if (fp == NULL) {
          setpass(user_level);
          printf(">> Press any key to continue");
          getch();
          continue;
        }
      }
      if (user_level == 1) {
        fp = fopen("part_pass", "r");

        if (fp == NULL) {
          setpass(user_level);
          printf(">> Press any key to continue");
          getch();
          continue;
        }
      }

      printf(">> ENTER PASSWORD (Type \"q\" to exit): ");
      fflush(stdin);

      j = 0;
      while ((ch = _getch()) != 13)  // character 13 is enter
      {
        if (ch == 8) continue;
        s[j] = ch;
        j++;
        printf("*");
      }
      s[j] = '\0';
      printf("\n");

      if (strcmp(s, "q") == 0) break;

      a = HASH(s);
      fread(&b, sizeof(b), 1, fp);
      fclose(fp);

      if (a == b) {
        printf(">> Password matched!\n");
        delay(1);
        menu();
      } else {
        printf("!! Wrong password. Try again.\n");
        delay(1);
      }
    }
  }
  return 0;
}
