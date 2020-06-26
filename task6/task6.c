#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
  double count;
  char * text;
}
PHRASE, * PHRASE_P;

int compare_doubles(double q, double w) {
  return q < w ? 1 : q > w ? -1 : 0;
}

int qsort_compair(const void * q,
  const void * w) {
  return compare_doubles(( * (const PHRASE_P * ) q) -> count, ( * (const PHRASE_P * ) w) -> count);
}

void contains_substring(PHRASE_P * sorted_phrases, char * substring, int number_of_phrases) {
  int found_counter = 0;
  int found_print = 0;
  //int x = 0;
  substring[strlen(substring) - 1] = '\0';

  PHRASE_P * matching_structs = (PHRASE_P * ) malloc(50 * sizeof(PHRASE_P)); //kdyztak pak zmen velikost alok pameti

  for (int i = 0; i < number_of_phrases; i++) {

    if (strcasestr(sorted_phrases[i] -> text, substring)) {

      if (found_print < 50) {
        matching_structs[found_print] = sorted_phrases[i];
        found_print++;
        //x++;
      }
      //printf("substring is present: %s\n", substring);
      found_counter++;
    }

  }
  printf("Nalezeno: %d\n", found_counter);
  if (found_print > 0) {
    for (int i = 0; i < found_print; i++) {
      printf("> %s\n", matching_structs[i] -> text);
    }
  }

  free(matching_structs);
}

int __attribute__((optimize("-O3"))) main(void) {

  int max = 80000000;
  PHRASE * phrases = (PHRASE * ) malloc(max * sizeof(PHRASE));
  PHRASE phrase;
  int n = 0;
  char * stringload = NULL;
  char * stringfind = NULL;
  size_t size_of_stringload = 0;
  size_t size_of_stringfind = 0;
  char delimiter;
  double count;
  int startstring = 0;
  short sscan_res;
  short getline_res;

  puts("Casto hledane fraze:");

  while (true) {

      getline_res = getline( & stringload, & size_of_stringload, stdin);

      if(getline_res == EOF){
          puts("Nespravny vstup.");
          free(stringload);
      if (n > 0) {
        for (int i = 0; i < n; i++) {
          free(phrases[i].text);
        }
      }
      free(phrases);
      return EXIT_FAILURE;
      }

    if (stringload[strspn(stringload, " \t\v\r\n")] == '\0') break; 

    sscan_res = sscanf(stringload, " %lf %c %n", & count, & delimiter, & startstring);
    if (sscan_res == EOF) {
      break;
    }

    if (sscan_res != 2 || delimiter != ':') {
      puts("Nespravny vstup.");
      free(stringload);
      if (n > 0) {
        for (int i = 0; i < n; i++) {
          free(phrases[i].text);
        }
      }
      free(phrases);
      return EXIT_FAILURE;
    }

    phrase.count = count;
    phrase.text = (char * ) malloc(size_of_stringload * sizeof(char)); //tady
    strcpy(phrase.text, stringload + startstring);
    phrase.text[strlen(phrase.text) - 1] = '\0';

    if (n + 1 >= max) {
      max = max * 1.5;

      PHRASE * tmp = (PHRASE * ) realloc(phrases, max * sizeof( * phrases));
      if (!tmp) {
        free(stringload);
        for (int i = 0; i < n; i++) {
          free(phrases[i].text);
        }
        free(phrases);
        return EXIT_FAILURE;
      }
      phrases = tmp;
    }
    phrases[n] = phrase;
    n++;
  }

  if (n == 0) {
    puts("Nespravny vstup.");
    free(stringload);
    for (int i = 0; i < n; i++) { //tady
      free(phrases[n].text);

    }
    free(phrases);
    return EXIT_FAILURE;
  }

  PHRASE_P * field_of_pointers = (PHRASE_P * ) malloc(sizeof(PHRASE_P) * n);

  for (int i = 0; i < n; i++) {
    field_of_pointers[i] = phrases + i;
  }

  qsort(field_of_pointers, n, sizeof(PHRASE_P), qsort_compair);

  puts("Hledani:");

  while ((getline_res = getline( & stringfind, & size_of_stringfind, stdin)) != EOF) {
    contains_substring(field_of_pointers, stringfind, n);
  }

  /*for (int i = 0; i < n; i++){
       printf("x: %lf, name:>%s\n", phrases[i].count,  phrases[i].text);
      }*/

  for (int i = 0; i < n; i++) {
    free(phrases[i].text);
  }

  free(field_of_pointers);
  free(stringload);
  free(stringfind);
  free(phrases);

  return EXIT_SUCCESS;

}

/*

Credits go to:


mr.xvagner


Rosetta dudefrom last homework


Fren stepan


pls dont kick me out ayy lamao


*/
