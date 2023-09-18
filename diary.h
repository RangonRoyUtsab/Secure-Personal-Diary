#ifndef DIARY_H_INCLUDED
#define DIARY_H_INCLUDED

#define DATE_SIZE 50
#define TIME_SIZE 50
#define NAME_SIZE 500

struct record {
  int privacy_level;
  char time[TIME_SIZE];
  // char title[NAME_SIZE];
  char note[NAME_SIZE];
};

void add_record(int user_level) {
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

  if (f_pointer == NULL) {
    printf("No records added today.\n\n");

    // save the date
    FILE *date_file = fopen("available_records.txt", "a+");
    fprintf(date_file, "\n");
    fprintf(date_file, date_string);
    fclose(date_file);
  } else {
    int i = 1;
    printf("Currently added notes today: \n\n");
    while (fread(&new_record, sizeof(struct record), 1, f_pointer)) {
      if (user_level >= new_record.privacy_level) {
        printf("Note no. %d \nTime: %s \nNote: %s \n\n", i, new_record.time,
               new_record.note);
      } else {
        // room for displaying a message that the current user does not
        // have the required permission
      }
      i++;
    }
    fclose(f_pointer);
  }
  // display part end

  f_pointer = fopen(date_string, "a");
  if (f_pointer == NULL) {
    printf("** Error creating record. **\n");
    exit(1);
  }

  // privacy settings

  if (user_level > 0) {
    printf("Select the privacy type of your note: \n");
    if (user_level >= 0) printf("1. Public\n");
    if (user_level >= 1) printf("2. Protected\n");
    if (user_level >= 2) printf("3. Private\n");
    int choice;
    scanf("%d", &choice);

    switch (choice) {
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
  } else {
    new_record.privacy_level = 0;
  }

  strcpy(new_record.time, time_string);
  printf("Enter the note: \n>> ");
  fflush(stdin);
  gets(new_record.note);
  fwrite(&new_record, sizeof(struct record), 1, f_pointer);
  fclose(f_pointer);
}

void view_record(int user_level) {
  system("cls");
  show_Time();
  fflush(stdin);

  FILE *date_file = fopen("available_records.txt", "a+");
  char available_date[DATE_SIZE];
  rewind(date_file);

  printf("Currently available recorded date: \n");
  while (fscanf(date_file, "%s", available_date) != EOF) {
    puts(available_date);
  }
  printf("\n");
  fclose(date_file);

  char date_string[DATE_SIZE];
  printf("Enter the date: ");
  fflush(stdin);
  gets(date_string);

  FILE *f_pointer = fopen(date_string, "r");
  if (f_pointer == NULL) {
    printf("** Record does not exist. **\n");
    return;
  }

  struct record new_record;
  int i = 1;
  while (fread(&new_record, sizeof(struct record), 1, f_pointer)) {
    if (user_level >= new_record.privacy_level) {
      printf("Note no. %d \nTime: %s \nNote: %s \n\n", i, new_record.time,
             new_record.note);
    } else {
      // room for displaying a message that the current user does not have
      // the required permission
    }
    i++;
  }
  fclose(f_pointer);
}

void modify_record(int user_level) {
  system("cls");
  show_Time();
  fflush(stdin);

  // view part
  char date_string[DATE_SIZE];
  printf("Enter the date: ");
  fflush(stdin);
  gets(date_string);

  FILE *f_pointer = fopen(date_string, "r");
  if (f_pointer == NULL) {
    printf("** Record does not exist. **\n");
    return;
  }

  struct record new_record;
  int i = 1;
  while (fread(&new_record, sizeof(struct record), 1, f_pointer)) {
    if (user_level >= new_record.privacy_level) {
      printf("Note no. %d \nTime: %s \nNote: %s \n\n", i, new_record.time,
             new_record.note);
    } else {
      // room for displaying a message that the current user does not have
      // the required permission
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
  if (f_pointer == NULL) {
    printf("** System error. Exiting program. **\n");
    delay(1);
    exit(1);
  }
  i = 1;
  while (fread(&new_record, sizeof(struct record), 1, f_pointer)) {
    if (i == k) {
      printf("Do you want to modify the time? (y/n) :: ");
      fflush(stdin);
      option = getchar();
      if (option == 'y') {
        printf("Enter new time (12:59 AM): ");
        fflush(stdin);
        gets(new_record.time);
        fflush(stdin);
      }
      printf("Do you want to modify the note? (y/n) :: ");
      fflush(stdin);
      option = getchar();
      if (option == 'y') {
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

void delete_record(int user_level) {
  system("cls");
  show_Time();

  char date_string[DATE_SIZE];
  printf("Enter the date: ");
  fflush(stdin);
  gets(date_string);

  remove(date_string);

  printf("** Record deleted successfully **\n");
}

#endif  // DIARY_H_INCLUDED
