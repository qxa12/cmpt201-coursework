#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char *buff = NULL;
  size_t size = 0;

  printf("type sentence: ");

  ssize_t num_char = getline(&buff, &size, stdin);
  if (num_char == -1) {
    perror("getline failed");
    exit(EXIT_FAILURE);
  }

  char *temp;
  char *token = strtok_r(buff, " \n", &temp);

  printf("Tokens are: \n");
  while (token != NULL) {
    printf(" %s\n", token);
    token = strtok_r(NULL, " \n", &temp);
  }

  free(buff);
  return 0;
}
