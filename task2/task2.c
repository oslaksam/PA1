#include <stdio.h>

#include <stdlib.h>

#include <math.h>

#include <string.h>


void streverse(char * str) {
  int length = strlen(str);
  int i;
  for (i = 0; i < length / 2; i++) {
    char temp = str[i];
    str[i] = str[length - i - 1];
    str[length - i - 1] = temp;
  }
}

int isSym(long long numb, int base) {
  long long forward = numb;
  long long rev = 0;
  int digit;

  while (numb > 0) {
    digit = numb % base;
    rev = rev * base + digit;
    numb = numb / base;
  }
  return (forward == rev);
}

char Chars(int num) {
  if (num >= 0 && num <= 9)
    return (char)(num + '0');
  else
    return (char)(num - 10 + 'a');
}

short input_control(char type, int base, long long lo, long long int hi) {
  if (lo < 0 || hi < 0 || lo > hi || base > 36 || base < 2) {
    return 0;
  }
  if (!(type == 'c' || type == 'l')) {
    return 0;
  }
  return 1;

}

char * EpicConvert(char vys[], int base, long long inputNum) {
  int index = 0;

  while (inputNum > 0) {
    vys[index++] = Chars(inputNum % base);
    inputNum /= base;
  }
  vys[index] = '\0';

  streverse(vys);

  return vys;
}

int /*__attribute__((optimize("-O3")))*/ main(void) {

  char type;
  long long lo = 0, hi = 0;
  long long sum = 0;
  int base;
  printf("Vstupni intervaly:\n");

  while (1) {
    short scancom = scanf(" %c %d %lld %lld", & type, & base, & lo, & hi);
    if ((scancom != 4) || (input_control(type, base, lo, hi)) == 0) {
      if (scancom != EOF) printf("Nespravny vstup.\n");
      return 0;
    }

    for (long long i = lo; i <= hi; i++) {
      if (isSym(i, base) == 1) {
        if (type == 'l') {
          long long nemo = i;
          if (base == 2) {
            printf("%lld = ", nemo);
            if (nemo == 0) {
              printf("0 (%d)\n", base);
            } else {
              while (nemo) {
                if (nemo & 1)
                  printf("1");
                else
                  printf("0");

                nemo >>= 1;
              }
              printf(" (%d)\n", base);
            }
          } else {
            char vys[1000];
            if (nemo == 0) printf("0 = 0 (%d)\n", base);
            else printf("%lld = %s (%d)\n", nemo, EpicConvert(vys, base, nemo), base);
          }

        } else {
          sum++;
        }

      }

    }

    if (type == 'c') {
      printf("Celkem: %lld\n", sum);
    }
    sum = 0;
  }

  return 0;
}