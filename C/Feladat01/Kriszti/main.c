#include <stdio.h>
#include <stdlib.h>
#include <math.h>


 double * alloc_vec ( int n) {
 double * v = ( double *) malloc (n * sizeof ( double ));
 if (v == 0) {
 printf (" Not enough memory .\n");
 exit ( -1);
 }
 return v ;
 }

void readvecs ( char* fn , int n , double*x , double* y)
 {
 FILE *f ;
 f = fopen ( fn , "r");
 for ( int i = 0; i < n; i ++) {
 fscanf (fn ,"%lf %d ", &x[i] , &y [i]);
 }
 fclose (f );
 return ;
 }

 void print_vec (double* v , int n) {
 for ( int i = 0; i < n; i ++) {
 printf ("%f\n",*( v+ i ));
 }
 }



 void maxvector(double *x, double *y, int n)
 {
    double max=x[0];
    int maxplace;
    for ( int i = 0; i < n; i ++)
    {
        if (x[i]>max)
        {
            max = x[i];
            maxplace = i+1;
        }
    }
    printf("A legnagyobb szam (indexe, szam, szine): %d  %f  %f\n", maxplace, max, y[maxplace]);

 }



 double atlag (double *x, int n)
{
    double osszeg = 0;
    double atlag = 0;
    double szam = n;
    for ( int i = 0; i < n; i++)
        {
        osszeg += x[i];
        }
    atlag = osszeg/szam;
    printf("Az energiak atlaga: %f\n", atlag);
    return atlag;
}


void szoras (double *x, int n, double atlag)
{
    double szoras = 0;
    double szamok = 0;
    for ( int i = 0; i < n; i ++)
        {
            szamok +=pow((x[i]-atlag),2);
        }
    szoras = sqrt(szamok/n);
    printf("Az energiak szorasa: %f\n", szoras);
}


void  letezike (double *x, int n, double szam)
{
    int dbkereses = 0;
    int szerepel=0;
    for ( int i = 0; i < n; i ++)
    {
        dbkereses ++;
        if (x[i] == szam)
        {
        printf("A keresett szam szerepel az energiaertekek között, a(z) %d. indexnel, %d kereses kellett a megtalalasahoz.\n", i, dbkereses);
        szerepel = 1;
        }
    }
    if (szerepel == 0)
    {
    printf("A keresett szam nem szerepel az energiaertekek között.");
    }
}




void swap(int* xp, int* yp)
{
    int temp = *xp;
    xp =yp;
    yp = temp;
}



double bubblesort (double *x, double *y, int n)
{
    int i, j;
    int dbhasonlitas;
    for ( int i = 0; i < n-1; i ++)
    {
        for ( int j = 0; j < n-i-1; j ++)
        {
            if (x[j]>x[j+1])
            {

                swap(&x[j], &x[j+1]);
                swap(&y[j], &y[j+1]);
                dbhasonlitas ++;
            }
        }
    }
    printf("A rendezeshez %d összehasonlitasra volt szükseg.\n", dbhasonlitas);

    if (n<21)
        {
            for ( int i = 0; i < n; i ++)
            {
            printf("%f %f\n", x[i], y[i]);
            }
        }
}





 int main ( int argc , char* argv[])
 {
 if ( argc < 3) {
 printf (" Not enough arguments .");
 exit ( -1);
 }
double avg;
int n = atoi ( argv [2]);


double * x = alloc_vec (n );
double * y = alloc_vec (n );


 FILE* f = fopen ( argv[1] , "r");
 if (f == 0) {
 printf (" Cannot open file %s.", argv [1]);
 exit ( -1);
 }
 readvecs(f ,n, x, y );
 fclose (f );

 print_vec(x, n);



maxvector(x,y,n);
avg=atlag (x,n);
szoras(x,n,avg);
letezike(x,n,0.5);
bubblesort(x,y,n);

 free(x);
 free(y);


 return 0;
 }
