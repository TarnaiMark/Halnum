#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <lapacke.h>

double * alloc_vec ( int n)
{

    double * v = ( double *) malloc (n * sizeof ( double ));
    if (v == 0)
    {
        printf (" Not enough memory .\n");
        exit ( -1);
    }
    return v ;
}
int * alloc_vecint ( int n)
{

    int * v = ( int *) malloc (n * sizeof ( int ));
    if (v == 0)
    {
        printf (" Not enough memory .\n");
        exit ( -1);
    }
    return v ;
}




void load_vec (char* f,  double *v, int n)
{

    FILE* fi = fopen(f,"r");
    for ( int i = 0; i < n; i ++)
    {
        fscanf (fi, "%lf", v + i );
    }
}
void write_matrix (double *m, int N)
{
    for ( int i = 0; i < N ; i ++)
    {
        for ( int j = 0; j < N ; j ++)
        {
            printf( "%f ", m[(i * N + j )]);
        }
        printf( "\n");
    }
}
double * alloc_matrix (int N  )
{
    double *matr = ( double *) malloc ( N * N * sizeof ( double ));
    if ( matr == 0)
    {
        printf (" Memory allocation error .\n");
        exit ( -1);
    }
    return matr ;
}
void print_vec ( double *v, int n)
{
    for ( int i = 0; i < n; i ++)
    {
        printf ("%f\n", *( v + i ));
    }
}
void read_matrix ( char* f, double *m, int N)
{
    FILE* fi = fopen(f,"r");
    for ( int i = 0; i < N ; i ++)
    {
        for ( int j = 0; j < N ; j ++)
        {
            fscanf (fi, "%lf", &m[i * N + j ]);
        }
    }
}

void rowmul(double* A,int N,int index,double d)
{
    for(int i = 0; N>i; i++)
    {
        A[index*N+i]= A[index*N+i]*d;
    }
}

void Matrixnorm(double* A,double* a,int N)
{
    double max;
    for(int row =0; N>row; row++)
    {
        max=0;
        for(int col =0; N>col; col++)
        {
            if(fabs(A[row*N+col])>fabs(max))
            {
                max = A[row*N+col];
            }
        }
        for(int colm =0; N>colm; colm++)
        {
            if(max ==0)
            {
            }
            else
            {
                A[row*N+colm]= A[row*N+colm]/max;
            }
        }
        a[row]=a[row]/max;
    }

}

void rowswap(double* A,int N,double*a, int index_old, int index_new)
{
    double cache=0;
    for(int i=0; N>i; i++)
    {
        cache = A[index_old*N+i];
        A[index_old*N+i]=A[index_new*N+i];
        A[index_new*N+i] = cache;
    }
    cache = a[index_old];
    a[index_old] = a[index_new];
    a[index_new]=cache;
}
double* GaussJ(double*A,double*b,double* a,int N)
{
    double s,d;
    for(int l =0; N>l; l++)
    {
        a[l]=b[l];
    }
    Matrixnorm(A,a,N);
    for(int i = 0; N>i; i++)
    {
        if(1>fabs(A[i*N+i]))
        {
            int indmax = 0;
            double valuemax = 0;
            for(int m = i; N>m; m++)
            {

                if(fabs(A[i+N*m])>fabs(valuemax))
                {
                    valuemax = A[i+N*m];
                    indmax=m;
                }
            }

            if(fabs(valuemax)>0.0001)
            {
                if(i != indmax)
                {
                    rowswap(A,N,a,i,indmax);
                }
            }
            else
            {
                //write_matrix(A,N);
                printf("A matrix numerikusan szingularis:Hibat tartalmazo oszlop szama,hiba erteke   %d   %f\n",i,valuemax);
                exit(1);
            }
        }
        if(A[i*N+i] !=1)//Ha f��tl� elem nem 1 norm�l�s
        {
            d = A[i*N+i];
            rowmul(A,N,i,1/d);
            a[i] = a[i]/d;
        }
        for(int j = 0; N>j; j++)
        {
            if(i==j)
            {
            }
            else
            {
                s =A[i+N*j];

                for(int k = 0; N>k; k++)
                {
                    A[N*j+k]=A[N*j+k]-A[N*i+k]*s;
                }
                a[j]= a[j]-a[i]*s;
            }
        }
    }
    return a;
}
int main(int argc, char * argv [])
{
    int N = atoi(argv[3]);

    double *a = alloc_vec(N);
    double *b = alloc_vec(N);
    double* A = alloc_matrix(N);
    load_vec(argv[2],b,N);
    read_matrix(argv[1],A,N);

    double *bl = alloc_vec(N);
    double* Al = alloc_matrix(N);
    load_vec(argv[2],bl,N);
    read_matrix(argv[1],Al,N);

    int* ipiv = alloc_vecint(N);

    lapack_int  info;

    info = LAPACKE_dgesv(LAPACK_ROW_MAJOR,N , 1, Al,N , ipiv, bl, 1);

    a = GaussJ(A,b,a,N);
    printf("Saját algoritmus megoldása:\n");
    print_vec(a,N);
    printf("Lapack megoldása:\n");
    print_vec(bl,N);
    return 0;
}
