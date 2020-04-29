#ifndef KAMUS_H_INCLUDED
#define KAMUS_H_INCLUDED


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#endif // KAMUS_H_INCLUDED

struct node1
{
    char* kata;
    char* definisi;
    char* tipe;
    struct node1* next;
};

typedef struct node1 kamus;
typedef kamus* kamusPtr;


void up_str(char* strW) // Capitalize first character of string
{
    int n = strW[0];

    if(n > 90)
    {
        strW[0] = n - 32;
    }
}

int pilihan_yn(char x)//x expect the input y/n
{
    int n;
    n = x;
    if( n < 90)
    {
        x = x + 32;
    }
    if(x=='y')
    {
        return 0;
    }
    else
    {
        return 1;
    }
}



void listkata (kamusPtr headR) // Display the content of all node in linked list to screen
{
	kamusPtr temp = headR;
	printf ("\n\n\t\t\t\t========================================\n");
	printf ("\t\t\t\t                LIST KATA                   \n");
    while(temp!=NULL)
    {
        printf ("\t\t\t\t+-Kata\t   : %s\n", temp->kata);
        printf ("\t\t\t\t+-Definsi  : %s\n", temp->definisi);
        printf ("\t\t\t\t+-Tipe\t   : %s\n\n", temp->tipe);
        temp = temp->next;
    }
}


void inputKata(kamusPtr *headW)// Input new node and the content to the linked list
{
    kamusPtr temp, prevNode = NULL;
    int n,i;
    char pilih;

    char* inKata = malloc(100*sizeof(char));
    printf(" Masukan Kata: ");
    gets(inKata);
    realloc(inKata, (strlen(inKata)+1)*sizeof(char));
    up_str(inKata);

    char* inDef = malloc(200*sizeof(char));
    printf(" Masukan Definisi: ");
    gets(inDef);
    realloc(inDef, (strlen(inDef)+1)*sizeof(char));
    up_str(inDef);

    char* inTipe = malloc(100*sizeof(char));
    printf(" Masukan Tipe Kata: ");
    gets(inTipe);
    realloc(inTipe, (strlen(inTipe)+1)*sizeof(char));
    up_str(inTipe);


    printf(" Anda yakin ingin masukan kata?(y/n): ");
    scanf("%c", &pilih);
    getchar();

    if(pilihan_yn(pilih)==0)
    {
        kamusPtr inKamus = malloc(sizeof(kamus));
        inKamus->kata = inKata;
        inKamus->definisi = inDef;
        inKamus->tipe = inTipe;
        inKamus->next = NULL;

        if(*headW!=NULL)// Memasukan node ke dalam linked list
        {
            i = 0;
            temp = *headW;

            while(temp!=NULL)// Pertama node di masukan kedalam list dengan metode stack, kemudian
            {
                if(strlen(inKamus->kata)<strlen(temp->kata))// membandingkan panjang "kata" dalam input node dengan node dibawahnya
                { //jika panjang kata dari input kata lebih besar dari dibawahnya, input kata bertukar tempat dengan dibawahnya
                    n = strlen(inKamus->kata);
                    i = 0;
                    while(i<n)
                    {
                        if(inKamus->kata[i]==temp->kata[i])//Selanjutnya membandingkan tiap karakter pada input kata dengan node yang dibandingkan
                        {//Jika karakternya sama maka operasi berlanjut
                            i++;
                        }
                        else if(inKamus->kata[i]>temp->kata[i])
                        {//Jika karakternya lebih besar. input kata bertukar tempat kebawah dengan node yang dibandingkan
                            i = n+1;
                        }
                        else
                        {
                            i = n;
                        }
                    }
                    i = i-1 ;
                }
                else
                {
                    n = strlen(temp->kata);
                    i = 0;
                    while(i<n)
                    {
                        if(inKamus->kata[i]==temp->kata[i])
                        {
                            i++;
                        }
                        else if(inKamus->kata[i]>temp->kata[i])
                        {
                            i = n;
                        }
                        else
                        {
                            i =n+1;
                        }//terus berulang sampai input kata tidak pindah kebawah
                    }
                }
                if(i==n)
                {
                    if(inKamus->next==NULL)
                    {
                        prevNode = temp;
                        inKamus->next = prevNode->next;
                        prevNode->next = inKamus;
                        temp = inKamus->next;
                    }
                    else
                    {
                        prevNode->next = temp;
                        prevNode = temp;
                        inKamus->next = prevNode->next;
                        prevNode->next = inKamus;
                        temp = inKamus->next;
                    }

                }
                else
                {
                    if(inKamus->next==NULL)
                    {
                        inKamus->next = temp;
                        *headW = inKamus;
                    }
                    temp = NULL;
                }

            }

        }
        else
        {

            *headW = inKamus;
        }

    }
}

int listLen(kamusPtr headR)// Get the length of the linked list (the amount of nodes in linked list)
{
    int i=0;
    while(headR!=NULL)
    {
        i++;
        headR = headR->next;
    }
    return i;
}

void listCpy(kamusPtr headR, kamusPtr *headW) // Copy all node in linked list
{// headW = return the head address of copied linked list to new head variabel
    kamusPtr inCpy, prevCpy = NULL;
    while(headR!=NULL)
    {
        inCpy = malloc(sizeof(kamus));

        if(prevCpy!=NULL)
        {
            prevCpy->next = inCpy;

            inCpy->kata = headR->kata;
            inCpy->definisi = headR->definisi;
            inCpy->tipe = headR->tipe;
            inCpy->next = NULL;

            prevCpy = inCpy;
        }
        else
        {
            *headW = inCpy;

            inCpy->kata = headR->kata;
            inCpy->definisi = headR->definisi;
            inCpy->tipe = headR->tipe;
            inCpy->next = NULL;

            prevCpy = inCpy;
        }

        headR = headR->next;
    }
}

void takeNode(kamusPtr *headW, int index, kamusPtr* nodeW)// Get the Node from linked list and delete the node in linked list
{ // index = index of the node (begin with 0); nodeW = return the address of the node
    int i;
    index = index + 1;
    kamusPtr temp, prevNode=NULL, currentNode=NULL;

    temp = *headW;
    if(index!=1)
    {
        for(i=0; i<index; i++)
        {

                prevNode = currentNode;
                currentNode = temp;
                temp = temp->next;
        }
        prevNode->next = currentNode->next;
        currentNode->next = NULL;
        *nodeW = currentNode;

    }
    else
    {
        *nodeW = *headW;
        *headW = (*headW)->next;
        (*nodeW)->next = NULL;

    }

}

void answerChKat(kamusPtr headR, int x, char* answerR, char* *answerW)
{
    int n, k, i;
    kamusPtr temp, next;
    next = headR;
    k = 0;
    do
    {
        n = (rand()%x);
        n = n+1;
        for(i=0; i<n; i++)
        {
            temp = next;
            next = next->next;
        }
        if(strcmp(temp->kata,answerR)==0)
        {
            next = headR;
        }
        else
        {
            *answerW = temp->kata;
            k = -1;
        }

    }while(k!=-1);

}

void randnumArr(int* arNum, int x)// Generate each different random number in array
{// arNum = Address of array; x number of the element in array or the amount of different random number in array
    srand(time(0));
    int i,j;

    for(i=0; i<x; i++)
    {
        arNum[i] = -1;
    }
    for(i=0; i<x; i++)
    {
            arNum[i] = rand()%x;
            for(j=0; j<i; j++)
            {
                if(arNum[j]==arNum[i])
                {
                    arNum[i] = -1;
                    i = i - 1;
                    j = i;
                }
            }
    }
}

void inputKamus(kamusPtr* headW) // Make linked list from file
{
    FILE *fptr;
    fptr = fopen("kamus.bin", "r");
    kamusPtr temp, prevNode = NULL;
    int n,i;

    int k,l;
    fscanf(fptr, "%d\n", &k);

    for(l=0; l<k; l++)
    {
    char* inKata = malloc(100*sizeof(char));
    fgets(inKata, 100, fptr);
    realloc(inKata, (strlen(inKata)+1)*sizeof(char));
    strtok(inKata, "\n");

    char* inDef = malloc(200*sizeof(char));
    fgets(inDef, 200, fptr);
    realloc(inDef, (strlen(inDef)+1)*sizeof(char));
    strtok(inDef, "\n");

    char* inTipe = malloc(100*sizeof(char));
    fgets(inTipe, 100, fptr);
    realloc(inTipe, (strlen(inTipe)+1)*sizeof(char));
    strtok(inTipe, "\n");

    kamusPtr inKamus = malloc(sizeof(kamus));

    inKamus->kata = inKata;
    inKamus->definisi = inDef;
    inKamus->tipe = inTipe;
    inKamus->next = NULL;

    if(*headW!=NULL)
    {
        i = 0;
        temp = *headW;

        while(temp!=NULL)
        {
            if(strlen(inKamus->kata)<strlen(temp->kata))
            {
                n = strlen(inKamus->kata);
                i = 0;
                while(i<n)
                {
                    if(inKamus->kata[i]==temp->kata[i])
                    {
                        i++;
                    }
                    else if(inKamus->kata[i]>temp->kata[i])
                    {
                        i = n+1;
                    }
                    else
                    {
                        i = n;
                    }
                }
                i = i-1 ;
            }
            else
            {
                n = strlen(temp->kata);
                i = 0;
                while(i<n)
                {
                    if(inKamus->kata[i]==temp->kata[i])
                    {
                        i++;
                    }
                    else if(inKamus->kata[i]>temp->kata[i])
                    {
                        i = n;
                    }
                    else
                    {
                        i =n+1;
                    }
                }
            }
            if(i==n)
            {
                if(inKamus->next==NULL)
                {
                    prevNode = temp;
                    inKamus->next = prevNode->next;
                    prevNode->next = inKamus;
                    temp = inKamus->next;
                }
                else
                {
                    prevNode->next = temp;
                    prevNode = temp;
                    inKamus->next = prevNode->next;
                    prevNode->next = inKamus;
                    temp = inKamus->next;
                }

            }
            else
            {
                if(inKamus->next==NULL)
                {
                    inKamus->next = temp;
                    *headW = inKamus;
                }
                temp = NULL;
            }

        }

    }
    else
    {
        *headW = inKamus;
    }
    }
    fclose(fptr);
}

void printKamusF(kamusPtr headR, int x) // Print dictionary to file
{// x = list lenght
    FILE *fptr;
    kamusPtr temp;
    temp = headR;
    fptr = fopen("kamus.bin", "w");

    fprintf(fptr, "%d\n", x);
    while(temp!=NULL)
    {
        fprintf(fptr, "%s\n", temp->kata);
        fprintf(fptr, "%s\n", temp->definisi);
        fprintf(fptr, "%s\n", temp->tipe);
        temp = temp->next;
    }

    fclose(fptr);
}
