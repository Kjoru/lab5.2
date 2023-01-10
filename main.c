#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define FName "data.txt"

double** mat_mem_allocation (int k);
void mat_mem_freeing (double** A, int N);
double vichislenie (double x1);

int main()
{
    char group[20],name[20];
    double** A;
    double x1,x2,delta,y,val;

    int nomer,N,l;

    FILE* fp=fopen(FName, "r");
    FILE* out=fopen("data_out.txt", "w");
    FILE* bin=fopen("data_bin.txt", "w+b");
    if (fp==NULL || out==NULL || bin==NULL)
    {
        printf("Error, one of the files don't exist");
        exit(0);
    }

    fscanf(fp, "%lf %lf %d %lf %s %s", &x1, &x2, &nomer, &delta, group, name);
    fclose(fp);

    if (nomer==0)
    {
        nomer=((x2-x1)/delta)+1;
    }
    else if (delta==0)
    {
        delta=(x2-x1)/(nomer-1);
    }
    fclose(fp);

    fprintf(out, "------------------------------");
    fprintf(out, "\n\t- N - X - F(x) -");
    fprintf(out, "\n------------------------------");
    fwrite(&nomer, sizeof(int), 1, bin);

    for(int i=0; i<nomer; i++)
    {
        y=vichislenie(x1);

        fprintf(out, "\n %d| %.2lf\t| %.2lf\t",i+1,x1,y);
        fprintf(out, "\n------------------------------");

        fwrite(&x1, sizeof(double), 1, bin);
        fwrite(&y, sizeof(double), 1, bin);
        x1=x1+delta;
    }
    fclose(out);
    fclose(bin);
    bin = fopen("data_bin.txt", "r+b");


    printf("\t%s %s", group, name);
    printf("\n\t- N - X - F(X) -\t");
    printf("\n------------------------------");
    fread(&N, sizeof(int), 1, bin);
    A = mat_mem_allocation(N);
    for(int i=0; i<N; i++)
    {

        A[0][i]=i+1;
        l = (int)A[0][i];
        printf("\n%d ", l);
        for(int j=1; j<=2; j++)
        {
            fread(&val, sizeof(double), 1, bin);
            A[j][i] = val;
            printf("%lf ", A[j][i]);
        }
    }
    mat_mem_freeing(A, 2);
    return 0;
}

double** mat_mem_allocation(int N)
{
    double** A;
    A =(double**)malloc(2*sizeof(double*));
    for(int i=0; i<=2; i++)
    {
        A[i]=(double*)malloc(N*sizeof(double));
    }
    return A;
}

void mat_mem_freeing(double** A, int N)
{
    for(int i=0; i<=N; i++)
    {
        free(A[i]);
    }
    free(A);
}
double vichislenie(double x1){
    double y;
    y=(pow(x1,3)+1000);
    return y;

}
