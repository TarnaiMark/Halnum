#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int * alloc_vec ( int n)
{

    int * v = ( int *) malloc (n * sizeof ( int ));
    if (v == 0)
    {
        printf (" Not enough memory .\n");
        exit ( -1);
    }
    return v ;
}
void print_vec ( int *v, int n)
{
    for ( int i = 0; i < n; i ++)
    {
        printf ("%d\n", *( v + i ));
    }
}
void spin_basedCold(int* spin, int n)
{
    for(int i =0; n>i; i++)
    {
        spin[i]= -1;
    }
}
void spin_basedHot(int* spin, int n)
{
    for(int i =0; n>i; i++)
    {
        spin[i]= 1;
    }
}

int Energy(int* spin, int n)
{
    int EnergyValue = 0;
    for(int i =1; n>i; i++)
    {
        EnergyValue += spin[i]*spin[i-1];

    }
    return -EnergyValue;
}
int RandomInt(int n)
{

    int r=rand() % n;
    return r;

}
double RandomDouble()
{
    int a1=RandomInt(10);
    int a2=RandomInt(10);
    int a3=RandomInt(10);
    int a4=RandomInt(10);
    int a5=RandomInt(10);
    double a=0.1*a1+0.01*a2+0.001*a3+0.0001*a4+0.00001*a5;
    return a;
}
void SpinCop(int* spin1,int* spin2,int n)
{
    for(int i = 0; n>i; i++)
    {
        spin1[i] = spin2[i];
    }
}

void SpinMod(int* spinTemp, int N)
{

    int i = RandomInt(N);
    spinTemp[i] = spinTemp[i] * (-1);
}

void EnergyAcceptator(int* Spin, int* SpinTemp, int N, double kbT)
{
    SpinCop(SpinTemp,Spin,N);
    SpinMod(SpinTemp,N);
    if(Energy(Spin,N)>Energy(SpinTemp,N))
    {
        SpinCop(Spin,SpinTemp,N);
    }
    else if(Energy(Spin,N)<=Energy(SpinTemp,N))
    {
        double EnergiaDelta= Energy(SpinTemp,N)- Energy(Spin,N);
        double R = exp(-EnergiaDelta/kbT); //Kérdéses hogy jó e a file tipe.

        if(R>RandomDouble())
        {

            SpinCop(Spin,SpinTemp,N);
        }
    }
}

void MHalgorith(char* Filepath,int kbT,int*Spin,int* SpinTemp,int N, int iteration)
{


    FILE* fi = fopen(Filepath,"w");
    for(int i = 0; iteration>i; i++)
    {
        EnergyAcceptator(Spin,SpinTemp,N,kbT);
        fprintf(fi,"%d\n",Energy(Spin,N));

    }
}

void MHalgorithTime(char* Filepath,int kbT,int*Spin,int* SpinTemp,int N)
{


    FILE* fi = fopen(Filepath,"w");
    for(int i = 0; 256>i; i++)
    {

        for(int i = 0; N>i; i++)
        {
            fprintf(fi,"%d ", *( Spin + i ));
        }
        fprintf(fi,"\n");
        EnergyAcceptator(Spin,SpinTemp,N,kbT);

    }
}

void MHalgorithHeat(char* Filepath,int*Spin,int* SpinTemp,int N, int iteration)
{
    double EnergyAvrage = 0;
    FILE* fi = fopen(Filepath,"w");


    for(int k = 0; 20>k;k++){
        for(int i = 0; iteration>i; i++)
        {
            double T = 0.1 + ((3.9/20)*k);
            EnergyAcceptator(Spin,SpinTemp,N,T);
            if(i>2000)
            {
                EnergyAvrage += Energy(Spin,N);
            }

        }
        EnergyAvrage = EnergyAvrage/ (iteration-2000);
        fprintf(fi,"%f\n",EnergyAvrage);
    }


}



int main(int argc, char * argv [])
{
    srand(time(0));
    int N = atoi(argv[1]);
    int kbT = atoi(argv[3]);


    int Iteration = atoi(argv[2]);


    int* Spin = alloc_vec(N);
    int* SpinTemp = alloc_vec(N);


    spin_basedCold(Spin,N);
    MHalgorith("Adat1.dat",1,Spin,SpinTemp,N,Iteration);

    spin_basedCold(Spin,N);
    MHalgorith("Adat2.dat",3,Spin,SpinTemp,N,Iteration);

    spin_basedHot(Spin,N);
    MHalgorith("Adat3.dat",1,Spin,SpinTemp,N,Iteration);

    spin_basedHot(Spin,N);
    MHalgorith("Adat4.dat",3,Spin,SpinTemp,N,Iteration);

    spin_basedCold(Spin,N);
    MHalgorithTime("Adat5.dat",1,Spin,SpinTemp,N);

    spin_basedCold(Spin,N);
    MHalgorithTime("Adat6.dat",3,Spin,SpinTemp,N);

    spin_basedCold(Spin,N);
    MHalgorithHeat("Adat7.dat",Spin,SpinTemp,N,Iteration);
}



