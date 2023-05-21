#include <stdio.h>
#include <stdlib.h>
#include <math.h>


double * alloc_matrix (int cols , int rows ) {
    double *matr = ( double *) malloc ( cols * rows * sizeof ( double ));
    if ( matr == 0) {
        printf (" Memory allocation error .\n");
        exit ( -1);
    }
    return matr ;
    }

 void read_matrix ( FILE * f , double *m , int cols , int rows ) {
     for ( int i = 0; i < rows ; i ++) {
        for ( int j = 0; j < cols ; j ++) {
            fscanf (f , "%lf", &m[i * cols + j ]);
        }
    }

 }

 void write_matrix (double *m , int cols , int rows ) {
    if(cols>20||rows>20){
        printf("%s\n","A kep tul nagy a kiirashoz");
    }
    else{
    for ( int i = 0; i < rows ; i ++) {
        for ( int j = 0; j < cols ; j ++) {
            printf("%lg" , m[(i * cols + j )]);
        }
        printf("\n");
    }
    }
 }
void matrixmul(double*mn , double *m, int mclumns, int mrows, double* n, int ncolumns, int nrows){


    int size = mclumns * mrows;
    for(int j=0; j<size;j++){

         mn[j] = m[j] *n[j];

    }

 }

 double avr(double *x,int n){
     double sum = 0;
     double avr;
     for(int i=0;n>i;i++){
        sum += x[i];
     }
    avr = sum /n;

    return avr;
 }

 double savr(double *x,int n){
     double sum = 0;
     double avr;
     for(int i=0;n>i;i++){
        sum += (x[i]*x[i]);
     }
    avr = sum /n;

    return avr;
 }

double correlation(double *m, int mclumns, int mrows, double* n, int ncolumns, int nrows ){
    double res;
    int size= mclumns*mrows;


    double* mn= alloc_matrix(mclumns,mrows);
    matrixmul(mn, m,mclumns,mrows,n,ncolumns,nrows);


    res = (avr(mn,size)-avr(m,size)*avr(n,size))  /    (sqrt(savr(m,size)-pow(avr(m,size),2)) * sqrt(savr(n,size)-pow(avr(n,size),2)));
     printf("%lf",res);

}








int main(int argc , char * argv [])
{
  int colums1 =atoi(argv[2]) ;
  int ro1 = atoi(argv[3]);

  int colums2 =atoi(argv[5]) ;
  int ro2 = atoi(argv[6]);





  double *kep1= alloc_matrix(colums1,ro1);
  double *kep2=  alloc_matrix(colums2,ro2);



  FILE *adat1 = fopen ( argv [1] , "r");
  read_matrix(adat1,kep1,colums1,ro1);

  fclose(adat1);

  FILE *adat2 = fopen ( argv [4] , "r");
  read_matrix(adat2,kep2,colums2,ro2);

  fclose(adat2);
  write_matrix(kep2,colums2,ro2);


  correlation(kep1,colums1,ro1,kep2,colums2,ro2);



 }
