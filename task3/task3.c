#ifndef __PROGTEST__
#include <stdlib.h>

#include <stdio.h>

#include <math.h>

#include <float.h>

#include <assert.h>

#endif /* __PROGTEST__ */

int almostEqual(double x, double y) {

        if (fabs(x - y) < (DBL_EPSILON * 1000)) {

                return 1;
        }

        return 0;
}
// Cohen–Sutherland algorithm. (2019). En.wikipedia.org. Retrieved 9 November 2019, from https://en.wikipedia.org/wiki/Cohen%E2%80%93Sutherland_algorithm
const int TTT = 8;

const int LLL = 1;

const int INS = 0;

const int RRRR = 2;

const int BOT = 4;

int Binnary_decisor(double a, double b, double rx1, double ry1, double rx2, double ry2) {
        int bin;

        bin = INS;

        if (a < rx1)
                bin |= LLL;
        else if (a > rx2)
                bin |= RRRR;
        if (b < ry1)
                bin |= BOT;
        else if (b > ry2)
                bin |= TTT;

        return bin;
}

void sort(double * a, double * b) {
        if ( * a > * b) {
                double tmp = * a;
                * a = * b;
                * b = tmp;
        }
}


int clipLine(double rx1, double ry1, double rx2, double ry2,
        double * ax, double * ay, double * bx, double * by) {

        sort( & rx1, & rx2);
        sort( & ry1, & ry2);

        int outbin0 = Binnary_decisor( * ax, * ay, rx1, ry1, rx2, ry2);
        int outbin1 = Binnary_decisor( * bx, * by, rx1, ry1, rx2, ry2);
        int guccigang = 0;

        while (1) {
                if (!(outbin0 | outbin1)) {

                        guccigang = 1;

                        break;
                } else if (almostEqual(rx1, * ax) == 1 && (almostEqual(ry1, * ay) == 1) && (outbin0 == 4) && (outbin1 == 6)) {
                        * bx = * ax;
                        * by = * ay;
                        guccigang = 1;
                        break;
                }
                 else if (almostEqual(rx1, * ax) == 1 && (almostEqual(ry1, * ay) == 1) && (outbin0 == 4) && (outbin1 == 4)) {
                        * bx = * ax;
                        * by = * ay;
                        guccigang = 1;
                        break;
                } else if (outbin0 & outbin1) {

                        break;
                } else {

                        double x = 0,y = 0;

                        int outbinOut = outbin0 ? outbin0 : outbin1;

                        if (outbinOut & TTT) {
                                x = * ax + ( * bx - * ax) * (ry2 - * ay) / ( * by - * ay);
                                y = ry2;

                        } else if (outbinOut & BOT) {
                                x = * ax + ( * bx - * ax) * (ry1 - * ay) / ( * by - * ay);
                                y = ry1;

                        } else if (outbinOut & RRRR) {
                                y = * ay + ( * by - * ay) * (rx2 - * ax) / ( * bx - * ax);
                                x = rx2;

                        } else if (outbinOut & LLL) {
                                y = * ay + ( * by - * ay) * (rx1 - * ax) / ( * bx - * ax);
                                x = rx1;

                        }

                        if (outbinOut == outbin0) {
                                * ax = x;
                                * ay = y;
                                outbin0 = Binnary_decisor( * ax, * ay, rx1, ry1, rx2, ry2);

                        } else {
                                * bx = x;
                                * by = y;
                                outbin1 = Binnary_decisor( * bx, * by, rx1, ry1, rx2, ry2);

                        }
                }
        }
        if (guccigang == 1) {

                return 1;
        }

        return 0;

}

