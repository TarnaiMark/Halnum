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

 void load_vec ( FILE * f , double *v , int n) {
    for ( int i = 0; i < n; i ++) {
        fscanf (f , "%lf", v + i );
    }
}

 void print_vec ( double *v , int n) {
    for ( int i = 0; i < n; i ++) {
        printf ("%f\n", *( v + i ));
        }
 }

void readvecs ( char *fn , int n , double *x , double *y )
 {
    FILE *f ;
    f = fopen ( fn , "r");
    for ( int i = 0; i < n; i ++) {
        fscanf (f ,"%lf %lf ", &x[i] , &y [i] );
    }

    fclose (f );
    return ;
 }

 void maxofvec(double *x,double *y, int n){
     double max = x[0];
     int indmax;

     for(int i = 0; n>i; i++){

        if(x[i]>max){
            max = x[i];
            indmax = i;
        }
     }
     printf("%s %f %d %f\n", "Legnagyobb szam, indexe, szine:",max,indmax, y[indmax]);
 }

 double avr(double *x,int n){
     double sum = 0;
     double avr;
     for(int i=0;n>i;i++){
        sum += x[i];
     }
    avr = sum /n;
    printf("%s %f\n","Energia ertekek atlaga:",avr);
    return avr;
 }
void spr(double *x,int n, double avr){
    double sum;
    double spr;
    for(int i=0;n>i;i++){
        sum += pow((x[i]-avr),2)/n;
    }
     spr = sqrt(sum);
     printf("%s %f\n","Energia ertekek szorasa:",spr);
}

void ifex(double *x,int n, double num){
    int numit = 0;
    int b=0;
    for(int i=0;n>i;i++){
        numit +=1;
        if(x[i]== num){
            printf("%s %d %d\n","A szam letezik,ezen az indexen,szukseges oszehasonlitasok szama:",i, numit);
            b = 1;
        }


    }
    if(b=0){printf("%s\n","A szam nincs benne a listaban.");
    }
}

void swap(double* xp, double* yp)
{
    double temp = *xp;
    *xp = *yp;
    *yp = temp;
}

double * bubbleSort(double *x,double *y,int n)
{
    int i, j;
    int it = 0;
    for (i = 0; i < n - 1; i++){
        for (j = 0; j < n - i - 1; j++){
            if (x[j] > x[j + 1]){
                it++;
                swap(&x[j], &x[j + 1]);
                swap(&y[j], &y[j + 1]);
            }}}
     printf("%s   %d\n","A buborekos rendezeshez szukseges oszehasonlitasok szama:", it);


     if(21>n){
       for ( int i = 0; i < n; i ++) {
        printf ("%f %f\n", x[i],y[i]);
        }
     }
    return x;



}

void binarySearch(double *x,int n, double num) {
 int low= 0;
 int high=n-1;
 int i= 0;
 int numit=0;

  while (low <= high) {

    int mid = low + (high - low) / 2;

    if (x[mid] == num)
      numit++;
      printf("%s %d %d\n","A szam letezik,ezen az indexen,szukseges oszehasonlitasok szama:",mid, numit);
      break;
    if (x[mid] < num)
      {low = mid + 1;}

    else{
      high = mid - 1;
    }
    numit++;
  }

  i++;
}

int main( int argc , char * argv [])
{

    double num = atof(argv[3]);
    double av;
    if ( argc < 1) {
         printf (" Not enough arguments .");
         exit ( -1);
    }

    int n = atoi ( argv [2]);

    double *x = alloc_vec (n );
    double *y = alloc_vec (n );

    FILE * f = fopen ( argv [1] , "r");
    if (f == 0) {
    printf (" Cannot open file %s.", argv [2]);
    exit ( -1);
    }
    readvecs(argv[1],n ,x,y);

    maxofvec(x,y,n);
    av = avr(x,n);
    spr(x,n,av);
    ifex(x,n,num);

    double *v = alloc_vec (n );
    v = bubbleSort(x,y,n);

    binarySearch(v,n,num);

    fclose (f );



    free (x );
    return 0;
}
