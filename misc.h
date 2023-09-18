#ifndef MISC_H_INCLUDED
#define MISC_H_INCLUDED

void delay (int number_of_seconds) {
  int milli_seconds  = 1000 * number_of_seconds;
  clock_t start_time = clock ();
  while (clock () < start_time + milli_seconds)
    ;
}

void show_Time () // prints the current date and time
{
  // Get the current time
  time_t current_time = time (NULL);

  // Convert the time to a string using the desired format
  char date_string[20];
  strftime (date_string, 20, "%d-%m-%Y", localtime (&current_time));

  char time_string[10];
  strftime (time_string, 10, "%I:%M %p", localtime (&current_time));

  // Print the date string
  printf ("*******************************************************************************\n");
  printf ("The current date is: %s                                                        \n", date_string);
  printf ("The current time is: %s                                                        \n", time_string);
  printf ("*******************************************************************************\n\n");
}

#endif // MISC_H_INCLUDED
