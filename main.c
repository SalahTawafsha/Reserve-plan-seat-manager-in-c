#include <stdio.h>
#include <stdlib.h>
#define S 66

int reserve(int[], char[], int, int);
void printReserved(int[], char[], int);
void fileprintReserved(int[], char[], int);
int main()
{
    int valid, i=0;
    int row[S];
    char seat[S];
    FILE *in;
    in = fopen("reservations.txt","r");
    do
    {
        valid = fscanf(in,"%d %c",&row[i],&seat[i]);
        if(valid == EOF)
            break;
        i = reserve(row,seat,i,S);
        ++i;
    }
    while(valid != EOF);

    do
    {
        printf("please enter the seat number to reserve: ");
        printf("please enter the row number (1-11) (0 to quit, 100 to print reserve seats): ");
        scanf("%d", &row[i]);
        if(row[i] == 0)
        {
            fileprintReserved(row,seat,i);
            break;
        }
        else if(row[i] == 100 || i == 66)
        {
            printReserved(row,seat,i);
            break;
        }
        printf("please enter the seat type: ");
        scanf(" %c", &seat[i]);
        if(row[i] > 11 || row[i] < 1 || seat[i] > 'F' || seat[i] < 'A')
            printf("Invalid seat number (%d%c)\n",row[i],seat[i]);
        else
        {
            i = reserve(row,seat,i,S);
            ++i;
        }
    }
    while(row[i] != 0 && row[i] != 100);
    fclose(in);

    return 0;
}


int reserve(int row[], char seat[], int i,int n)
{
    int j, f=0;
    for(j=0 ; j<n ; ++j)
        if(row[i] == row[j] && seat[i] == seat[j] && i != j)
        {
            printf("The seat is not avalible, please try again\n");
            f = 1;
            return i-1;
        }

    if(f==0)
        printf("seat (%d%c) reserved successfully\n",row[i],seat[i]);
    return i;
}

void printReserved(int row[], char seat[], int n)
{
    int i;
    printf("List of Reserved Seats:\n");
    for(i=0 ; i<n ; ++i)
        printf("\tseat (%d%c) is Reserved.\n", row[i], seat[i]);

    printf("**\n\tFree seats = %d\n",66-n);
    printf("\tReserved seats = %d",n);


}

void fileprintReserved(int row[], char seat[], int n)
{
    FILE *out;
    out = fopen("reservations.txt","w");
    int i;
    printf("Write Reservations File is Done\n");
    fprintf(out,"List of Reserved Seats:\n");
    for(i=0 ; i<n ; ++i)
        fprintf(out,"\tseat (%d%c) is Reserved.\n", row[i], seat[i]);

    fprintf(out,"**\n\tFree seats = %d\n",66-n);
    fprintf(out,"\tReserved seats = %d",n);
    fclose(out);


}
