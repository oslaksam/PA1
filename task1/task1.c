#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include <string.h>
#define _USE_MATH_DEFINES
#ifndef M_PI
#    define M_PI 3.14159265358979323846
#endif

void sortarr(double arr[3]){
    double temp1 = arr[0];
    double temp2 = arr[1];
    double temp3 = arr[2];
    arr[0] = fmin(temp3, fmin(temp1,temp2));
    arr[2] = fmax(temp1, fmax(temp2, temp3));
    arr[1] = temp1 + temp2 + temp3 - arr[0] - arr[2];
}

//int strcmp (const char* str1, const char* str2);

int main(void){
    double a = 0, b = 0, c = 0, d = 0, e = 0, f = 0;
    double ua = -1 , ub = -1, uc = -1 , ud = -1, ue = -1, uf = -1;
    double al1, al2, be1, be2, ga1, ga2;
    char type[3][4] = {"SSS", "SUS", "USU"};
    char str1[4];
    char str2[4];
    double trian1[3];
    double trian2[3];
    double trian1u[3];
    double trian2u[3];


    
   printf("Trojuhelnik #1:\n");
   if((scanf(" %3[SU] %lf %lf %lf", str1, &a, &b, &c)) != 4){
       printf("Nespravny vstup.\n");
       return 1;
   }
   if(a<=0 || b<=0 || c<=0 || ( ( (strcmp(str1, type[0]))  != 0 ) && ( (strcmp(str1, type[1])) != 0 ) && ( (strcmp(str1, type[2])) != 0 ) ) ){
       printf("Nespravny vstup.\n");
       return 1;
   }
   else
   {
       if ( (strcmp(str1, type[0])) == 0 )
   {
        ua = acos( ( pow(a, 2) - pow(b, 2) - pow(c, 2) ) / (-2*b*c) );
        ub = acos( ( pow(b, 2) - pow(a, 2) - pow(c, 2) ) / (-2*a*c) );
        uc = acos( ( pow(c, 2) - pow(b, 2) - pow(a, 2) ) / (-2*b*a) );
        

        if( ( (a+b-c) <= (DBL_EPSILON * 64 * a * b *c) ) || ( (b+c-a) <= (DBL_EPSILON * 64 * a * b *c) ) || ( (a+c-b) <= (DBL_EPSILON * 64 * a * b *c) ) /*|| ( (ua+ub+uc) > (M_PI+DBL_EPSILON*M_PI) )*/ ){
       printf("Vstup netvori trojuhelnik.\n");
       return 1;
     }

   }
   
    if ( strcmp(str1, type[1]) == 0 )
   {
       if( fabs(b-180.0) < (DBL_EPSILON*180*b) ){
           printf("Nespravny vstup.\n");
           return 1;
           //(fabs(p1-1.0) < (DBL_EPSILON*1000)
       }

       al1 = b;
       ub = al1*( (double)M_PI/ (double)180 ) ;
       b = sqrt( pow(c, 2) + pow(a, 2) -2*c*a*cos(ub) );
       ua = acos( ( pow(a, 2) - pow(b, 2) - pow(c, 2) ) / (-2*b*c) );
       uc = acos( ( pow(c, 2) - pow(b, 2) - pow(a, 2) ) / (-2*b*a) );
       
       
       if( ( (a+b-c) <= (DBL_EPSILON * 64 * a * b *c) ) || ( (b+c-a) <= (DBL_EPSILON * 64 * a * b *c) ) || ( (a+c-b) <= (DBL_EPSILON * 64 * a * b *c) ) /*|| ( (ua+ub+uc) > (M_PI+DBL_EPSILON*M_PI) )*/ )  {
       printf("Vstup netvori trojuhelnik.\n");
       
       return 1;
     }
   }
   if ( strcmp(str1, type[2]) == 0  )
   {
       if( ( fabs(a-180.0) <= (DBL_EPSILON*180*a) ) || ( fabs(c-180.0) <= (DBL_EPSILON*180*c) ) ){
           printf("Nespravny vstup\n");
           return 1;
       }
       if (( fabs(a+c-180.0) <= (DBL_EPSILON*180*a*c) ))
       {
           printf("Vstup netvori trojuhelnik.\n");
       return 1;
       }
       
       al1 = 180.0 - a - c;
       be1 = a;
       ga1 = c;       
       ua = be1*( (double)M_PI/ (double)180);
       uc = ga1*( (double)M_PI / (double)180);
       ub = al1*( (double)M_PI / (double)180);
       a = ( b*sin(ua) / sin(ub) );
       c = ( b*sin(uc) / sin(ub) );

       if( ( (a+b-c) <= (DBL_EPSILON * 64 * a * b *c) ) || ( (b+c-a) <= (DBL_EPSILON * 64 * a * b *c) ) || ( (a+c-b) <= (DBL_EPSILON * 64 * a * b *c) ) /*|| ( (ua+ub+uc) > (M_PI+DBL_EPSILON*M_PI) ) */){
       printf("Vstup netvori trojuhelnik.\n");
       return 1;
     }

     
   }  
    trian1[0] = a;
    trian1[1] = b;
    trian1[2] = c;
    sortarr(trian1);
    trian1u[0] = ua;
    trian1u[1] = ub;
    trian1u[2] = uc;
    sortarr(trian1u);
    
   }
   
 
printf("Trojuhelnik #2:\n");
   if((scanf(" %3[SU] %lf %lf %lf", str2, &d, &e, &f)) != 4){
        printf("Nespravny vstup.\n");
       return 1;
   }
    
    if(d<=0 || e<=0 || f<=0 || ( ( (strcmp(str2, type[0]))  != 0 ) && ( (strcmp(str2, type[1])) != 0 ) && ( (strcmp(str2, type[2])) != 0 ) ) ){
       printf("Nespravny vstup.\n");
       return 1;
       
   }
   else
   {
              
   if ( strcmp(str2, type[0]) == 0 )
   {

    ud = acos( ( pow(d, 2) - pow(e, 2) - pow(f, 2) ) / (-2*e*f) );
    ue = acos( ( pow(e, 2) - pow(d, 2) - pow(f, 2) ) / (-2*d*f) );
    uf = acos( ( pow(f, 2) - pow(e, 2) - pow(d, 2) ) / (-2*e*d) );

    if( ( (d+e-f) <= (DBL_EPSILON * 64 * e * f *d) ) || ( (e+f-d) <= (DBL_EPSILON * 64 * e * f *d) )  || ( (d+f-e) <= (DBL_EPSILON * 64 * e * f *d) )   ) /*|| ( (ud+ue+uf) > (M_PI+DBL_EPSILON*M_PI) )*/ {
       printf("Vstup netvori trojuhelnik.\n");
       return 1;
       }

   }
    if ( strcmp(str2, type[1]) == 0 )
   {
       if( fabs(b-180.0) < (DBL_EPSILON*180*b) ){
           printf("Nespravny vstup.\n");
           return 1;
       }

       al2 = e;
       ue = al2*( (double)M_PI/ (double)180 );
       e = sqrt( pow(f, 2) + pow(d, 2) -2*f*d*cos(ue) );           
       ud = acos( ( pow(d, 2) - pow(e, 2) - pow(f, 2) ) / (-2*e*f) );
       uf = acos( ( pow(f, 2) - pow(e, 2) - pow(d, 2) ) / (-2*e*d) );

        if( ( (d+e-f) <= (DBL_EPSILON * 64 * e * f *d) )  || ( (e+f-d) <= (DBL_EPSILON * 64 * e * f *d) )  || ( (d+f-e) <= (DBL_EPSILON * 64 * e * f *d) ) ) /*|| ( (ud+ue+uf) > (M_PI+DBL_EPSILON*M_PI) )*/ {
       printf("Vstup netvori trojuhelnik.\n");
       return 1;
       }
       
   }
   if ( strcmp(str2, type[2]) == 0  )
   {
       if( fabs(d-180.0) <= (DBL_EPSILON*180*d) || fabs(f-180.0) <= (DBL_EPSILON*180*f) ){
           printf("Nespravny vstup.\n");
           return 1;
       }
       if (( fabs(d+f-180.0) <= (DBL_EPSILON*180*d*f) ))
       {
           printf("Vstup netvori trojuhelnik.\n");
           return 1;
       }
       
       al2 = 180.0 - d - f;
       be2 = d;
       ga2 = f;       
       ud = be2*( (double)M_PI/ (double)180 );
       uf = ga2*( (double)M_PI/ (double)180 );
       ue = al2*( (double)M_PI/ (double)180 );
       d = ((e*sin(ud)) / sin(ue));
       f = ((e*sin(uf) / sin(ue)));

       if( ( (d+e-f) <= (DBL_EPSILON * 64 * e * f *d) ) || ( (e+f-d) <= (DBL_EPSILON * 64 * e * f *d) ) || ( (d+f-e) <= (DBL_EPSILON * 64 * e * f *d)  ) /*||  ( (ud+ue+uf) > (M_PI+DBL_EPSILON*M_PI) )*/  ){
       printf("Vstup netvori trojuhelnik.\n");
       return 1;
       }
       
   }
    trian2[0] = d;
    trian2[1] = e;
    trian2[2] = f;
    sortarr(trian2);
    trian2u[0] = ud;
    trian2u[1] = ue;
    trian2u[2] = uf;
    sortarr(trian2u);
}

     
double p1 = trian2[2] / trian1[2];
double p2 = trian2[1] / trian1[1];
double p3 = trian2[0] / trian1[0];

if ( ( fabs(trian2u[0] - trian1u[0]) < (DBL_EPSILON*1000) ) && ( fabs(trian2u[1] - trian1u[1]) < (DBL_EPSILON*1000) ) && ( fabs(trian2u[2] - trian1u[2]) < (DBL_EPSILON*1000) ) )
{
    if ( (fabs(p1-1.0) < (DBL_EPSILON*1000) ) && ( fabs(p2-1.0) < (DBL_EPSILON*1000) ) && ( fabs(p3-1.0) < (DBL_EPSILON*1000) ) ) 
{
    printf("Trojuhelniky jsou shodne.\n");
}
    else
    {
        printf("Trojuhelniky nejsou shodne, ale jsou podobne.\n");
    }
}
else
{
    printf("Trojuhelniky nejsou shodne ani podobne.\n");
}
return 0;
}
    