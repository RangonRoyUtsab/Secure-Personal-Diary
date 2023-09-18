#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED

int HASH(char *pass) {
  int n = strlen(pass);
  int h = 0;
  for (int i = 0; i < n; i++) {
    h += ((i + 1) * pass[i]);
  }
  return h;
}

int HASH2(char *key) {
  int n = strlen(key);
  int h = 0;
  for (int i = 0; i < n; i++) {
    h += ((i + 1) * key[i]);
  }
  return (h % 2000005);
}

#endif  // HASH_H_INCLUDED
