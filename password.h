#ifndef PASSWORD_H_INCLUDED
#define PASSWORD_H_INCLUDED

void setpass(int user_level) {
  printf(">> SET A NEW PASSWORD: ");

  FILE *f_pointer;

  if (user_level == 2) f_pointer = fopen("admin_pass", "w");
  if (user_level == 1) f_pointer = fopen("part_pass", "w");

  if (f_pointer == NULL) {
    printf("Password set failed.\n");
    exit(1);
  }

  fflush(stdin);
  char s[30];
  gets(s);
  int h_val = HASH(s);
  fwrite(&h_val, sizeof(h_val), 1, f_pointer);

  if (fwrite != 0) {
    printf("** Password set successfully! **\n");
  } else {
    printf("** Failed to set password. **\n");
  }

  fclose(f_pointer);
}

void password_change(int user_level) {
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

  // FILE *fp = fopen("password_file", "r");
  FILE *fp;
  if (user_level == 2) fp = fopen("admin_pass", "r");
  if (user_level == 1) fp = fopen("part_pass", "r");

  fread(&b, sizeof(b), 1, fp);
  fclose(fp);

  if (a == b) {
    setpass(user_level);
  } else {
    printf("Password didn't match!. Try again.\n");
  }
  delay(1);
}

#endif  // PASSWORD_H_INCLUDED
