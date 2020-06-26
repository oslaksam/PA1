#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <values.h>
#include <math.h>
#include <float.h>
 //#define MIN_NORMAL 1.17549435E-38f

typedef struct {
  double a_x;
  double a_y;
  char * a_name;
}
AIRPLANE, * airplane;

/*bool almostequal(double q, double w)
{   
  
  double absQ = fabs(q);
   double absW = fabs(w);
    double difference = fabs(q - w);
    if (q == w) { 
		return true;
	} else if (q == 0 || q == 0 || difference < MINDOUBLE) {

		return difference < (DBL_EPSILON * __DBL_MIN__);
	} else { 
		return difference / fmin((absQ + absW), MAXDOUBLE) < DBL_EPSILON;
	}
}*/
bool almostequal(double q, double w) {
  double epsilon = 1e-8;
  return fabs(q - w) <= fabs(epsilon * q * w);
}

double distance_btw_points(airplane p1, airplane p2) {
  double dist_x = p1 -> a_x - p2 -> a_x, dist_y = p1 -> a_y - p2 -> a_y;
  return dist_x * dist_x + dist_y * dist_y;
}

double brutal_slow_cuckery(airplane * air, int max_number) {

  double d, minimal_distance = MAXDOUBLE;

  for (int i = 0; i < max_number; i++) {
    for (int j = i + 1; j < max_number; j++) {
      d = distance_btw_points(air[i], air[j]);
      if (d >= minimal_distance) continue;
      minimal_distance = d;
    }
  }
  return minimal_distance;
}

void brute_print(double minimal_distance, airplane * air, int max_number, AIRPLANE * airplanes) {
  double d;
  for (int i = 0; i < max_number; i++) {
    for (int j = i + 1; j < max_number; j++) {
      d = sqrt(distance_btw_points(air[i], air[j]));
      if (almostequal(d, minimal_distance)) printf("%s - %s\n", airplanes[i].a_name, airplanes[j].a_name);
    }
  }

}

int main(void) {

  int max = 15;
  AIRPLANE * airplanes = (AIRPLANE * ) malloc(max * sizeof(AIRPLANE));
  AIRPLANE plane;
  int n = 0;
  char * stringload = NULL;
  size_t size_of_string = 0;
  char a, b, c;
  double x, y;
  int startstring = 0;
  short sscanf_res;
  short getline_res;

  puts("Zadejte lety:");

  while ((getline_res = getline( & stringload, & size_of_string, stdin) != EOF)) {

    sscanf_res = sscanf(stringload, " %c %lf %c %lf %c %n", & a, & x, & b, & y, & c, & startstring);
    if (sscanf_res == EOF) {
      break;
    }

    if (sscanf_res != 5 || a != '[' || b != ',' || c != ']') {
      puts("Nespravny vstup.");
      free(stringload);
      if (n > 0) {
        for (int i = 0; i < n; i++) {
          free(airplanes[i].a_name);
        }
      }
      free(airplanes);
      return 1;
    }

    plane.a_x = x;
    plane.a_y = y;
    plane.a_name = (char * ) malloc(size_of_string * sizeof(char)); //tady
      strcpy(plane.a_name, stringload + startstring);     
    plane.a_name[strlen(plane.a_name) - 1] = 0;

    if (n + 1 >= max) {
      max = max * 2;
      AIRPLANE * tmp;
      tmp = (AIRPLANE * ) realloc(airplanes, max * sizeof( * airplanes));
      if (!tmp) {
        free(stringload);
        for (int i = 0; i < n; i++) {
          free(airplanes[i].a_name);
        }
        free(airplanes);
        return 1;
      }
      airplanes = tmp;
    }
    airplanes[n] = plane;
    n++;
  }

  if (n < 2) {
    puts("Nespravny vstup.");
    free(stringload);
    for (int i = 0; i < n; i++) { //tady
      free(airplanes[n].a_name);

    }
    free(airplanes);
    return 1;

  }

  airplane * s_x = (airplane * ) malloc(sizeof(airplane) * n);

  for (int i = 0; i < n; i++) {
    s_x[i] = airplanes + i;
  }
  double minimal_distance = (sqrt(brutal_slow_cuckery(s_x, n)));

  printf("Nejmensi vzdalenost: %lf\n", minimal_distance);
  brute_print(minimal_distance, s_x, n, airplanes);

  free(s_x);
  for (int i = 0; i < n; i++) { //tady
    free(airplanes[i].a_name);
  }
  free(stringload);
  free(airplanes);
  return 0;
}

/*

Credits go to:


mr.xvagner




random dudes on the internet




my cat and my friends






pls dont kick me out frens



Closest

-pair

 problem/C

- Rosetta Code
Closest

-pair

 problem/C

- Rosetta Code



Closest

-pair 

pro
blem/C

 - Rosetta
 
  Cod
  
  e.

  (2019).



  Roset
  
  
  
  tacode.o
  
  
  
  rg.

   Retr
   
   
   
   
   
   ieved 27

   Nove
   
   
   mber 20
   
   
   
   
   19,
   
    from 






htt



ps://



rosetta


code.


org

/wiki/



Closest




-pair_




problem/




C




Pan


Vagner


,


 proseminar



Closest-pair problem/C

 - Rosetta Code.

  (2019).

  Rosettacode.org.

   Retrieved 27

   November 2019,
   
    from 


https://

rosettacode.org

/wiki/

Closest

-pair_

problem/


C




Pan Vagner, proseminar


*/

