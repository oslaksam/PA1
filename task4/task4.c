#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <stdbool.h>

typedef int( * cmptrick)(const void * ,const void * );

typedef struct {
  int alt;
  int h;
  int w;
  int d;
}
WATERTANK;

/*
 *   Function made for reading input
 */
WATERTANK * input_read(int * num_of_tanks) {

  short scan_res;
  WATERTANK * watertanks = NULL;
  * num_of_tanks = 0;

  puts("Zadejte pocet nadrzi:");
  scan_res = scanf(" %d", num_of_tanks);
  if ((scan_res != 1) || ( * num_of_tanks > 200000) || ( * num_of_tanks <= 0)) {
    return NULL;
  }

  puts("Zadejte parametry nadrzi:");
  watertanks = (WATERTANK * ) malloc( * num_of_tanks * sizeof(WATERTANK));

  for (int i = 0; i < * num_of_tanks; i++) {

    scan_res = scanf(" %d %d %d %d", & watertanks[i].alt, & watertanks[i].h, & watertanks[i].w, & watertanks[i].d);
    if ((scan_res != 4) || (watertanks[i].h <= 0) || (watertanks[i].w <= 0) || (watertanks[i].d <= 0)) {
      free(watertanks);
      return NULL;
    }
  }
  return watertanks;
}

/*
 *   Qsort comparison function
 */
int cmp(WATERTANK * tank1, WATERTANK * tank2) {
  if (tank1 -> alt < tank2 -> alt)
    return -1;

  else if (tank1 -> alt > tank2 -> alt)
    return 1;

  else
    return 0;
}

/*
 *   Returns true if there is a tank avalivable in a current alt interval
 */
bool in_interval(int lo, int hi, int x) {
  return ((x - hi) * (x - lo) <= 0);
}

/*
 *   Finds maximum height of all the avalivable tanks
 */
int find_max_height(WATERTANK * watertanks, int num_of_tanks) {

  int max = watertanks[0].h + watertanks[0].alt;

  for (int i = 1; i < num_of_tanks; i++) {
    int tmp = watertanks[i].alt + watertanks[i].h;
    if (tmp > max) max = tmp;
  }
  return max;
}

/*
 *   Finds from which altitude should the counting start
 */
int find_min_alt(WATERTANK * watertanks, int num_of_tanks) {

  int min = watertanks[0].alt;

  for (int i = 1; i < num_of_tanks; i++) {
    int tmp = watertanks[i].alt;
    if (tmp < min) min = tmp;
  }
  return min;
}

/*
 *   Finds how much water can one fill in 1 metrer in current altitude
 */
int count_surface_in_cur_alt(WATERTANK * watertanks, int num_of_tanks, int alt) {

  int surface = 0;

  for (int i = 0; i < num_of_tanks; i++) {
    if ((in_interval(watertanks[i].alt, (watertanks[i].h + watertanks[i].alt), alt)) && (in_interval(watertanks[i].alt, (watertanks[i].h + watertanks[i].alt), (alt + 1)))) {
      surface += ((watertanks[i].w) * (watertanks[i].d));
    }
  }
  return surface;
}

/*
 *   Calculates actual water level for a given water_amount input
 */
double water_level(WATERTANK * watertanks, int num_of_tanks, int water_amount) {

  double water_lvl = find_min_alt(watertanks, num_of_tanks);
  int alt = water_lvl;
  int maxh = find_max_height(watertanks, num_of_tanks);
  int surface = 0;

  while ((alt < maxh) && (water_amount > 0)) {

    surface = count_surface_in_cur_alt(watertanks, num_of_tanks, alt);

    if ((water_amount >= surface) && (surface != 0)) {
      water_lvl++;
      water_amount = water_amount - surface;
      alt++;
      continue;
    } else if ((water_amount < surface) && (water_amount > 0)) {
      water_lvl += (double) water_amount / (double) surface;
      water_amount = water_amount - surface;
      break;
    } else {
      water_lvl++;
      alt++;
    }
  }
  if (water_amount > 0) return DBL_MAX; //Special constant in the case of water overflow
  return water_lvl;
}

/*
 *   Calls the water level fuction and prints the correct result
 */
void water_calculate(int water_amount, WATERTANK * watertanks, int num_of_tanks) {

  double result;

  if (water_amount == 0) puts("Prazdne.");
  else {
    result = water_level(watertanks, num_of_tanks, water_amount);
    if (result == DBL_MAX) puts("Pretece.");
    else printf("h = %lf\n", result);
  }
}

int main(void) {

  int num_of_tanks;
  int water_amount;
  WATERTANK * watertanks;
  short while_scale_res;

  watertanks = input_read( & num_of_tanks);
  if (!watertanks) {
    puts("Nespravny vstup.");
    free(watertanks);
    return 1;
  }

  qsort((void * ) watertanks, num_of_tanks, sizeof(WATERTANK), (cmptrick) cmp); // Sorts tank by their alt

  puts("Zadejte objem vody:");
  while ((while_scale_res = scanf(" %d", & water_amount)) != EOF) {
    if (while_scale_res != 1 || water_amount < 0) {
      puts("Nespravny vstup.");
      free(watertanks);
      return 1;
    }
    water_calculate(water_amount, watertanks, num_of_tanks); // Calculates water level and prints corrent output   
  }

  free(watertanks);
  return 0;
}