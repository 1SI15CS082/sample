#include<stdio.h>
#include<math.h>
int pc1_key[56],c[28],d[28],keyshift[56],pc2_key[48];

void converttobinary(int hex[16],int bin[64])
{
    int i;

    for(i=0;i<64;i++)
    bin[i]=0;

    long int rem,count;
    for(i=0;i<16;i++){
        count=1;
        while (hex[i]>0)
        {
            rem=hex[i]%2;
            bin[(i+1)*4-count]=rem;

            hex[i]=hex[i]/2;
            count++;
        }
    }
}



int pc1[8][7]={57,49,41,33,25,17,9,
				1,58,50,42,34,26,18,
				10,2,59,51,43,35,27,
				19,11,3,60,52,44,36,
				63,55,47,39,31,23,15,
				7,62,54,46,38,30,22,
				14,6,61,53,45,37,29,
				21,13,5,28,20,12,4
				};
int pc2[8][6]={
                14,17,11,24,1,5,
                3,28,15,6,21,10,
                23,19,12,4,26,8,
                16,7,27,20,13,2,
                41,52,31,37,47,55,
                30,40,51,45,33,48,
                44,49,39,56,34,53,
                46,42,50,36,39,32
                };


void PC1(int key[64])
{
    int i,j,k=0;
    for(i=0;i<8;i++)
    {
        for(j=0;j<7;j++)
        {
            pc1_key[k++]=key[pc1[i][j]-1];
        }
    }
}
void leftshift()
{
    int i,j,k=0;
    k=c[0];
    for(i=1;i<28;i++)
        c[i-1]=c[i];
    c[i-1]=k;
    
    k=d[0];

    for(i=1;i<28;i++)
        d[i-1]=d[i];
    d[i-1]=k;

    for(i=0;i<28;i++)
        keyshift[i]=c[i];
    
    for(k=0,j=i;j<56;j++)
        keyshift[i++]=d[k++];
}



void PC2()
{
    int i,j,k=0;
    for(i=0;i<8;i++)
    {
        for(j=0;j<6;j++)
        {
            pc2_key[k++]=keyshift[pc2[i][j]-1];
        }
    }
}



int main()
{
    FILE *myfile,*myfile1;
    myfile1=fopen("input.txt","r");
    myfile=fopen("output.txt","w");
    int i,j,k=0,round=1,n,bin[64],hex[64];

    printf("key entered in input file in hex format(0x0)");
    
    for(i=0;i<16;i++){
        fscanf(myfile1,"%x",&hex[i]);
        printf("%x ",hex[i]);
    }

    converttobinary(hex,bin);

    printf("\n 64 bit input is\n");
    for(i=1;i<=64;i++)
    {
        printf("%d",bin[i-1]);
        if(i%8==0)
        printf("\n");
    }

    printf("\n enter no of rounds\n");
    scanf("%d",&n);
    PC1(bin);
    for(i=0;i<28;i++)
    c[i]=pc1_key[i];
    
    for(j=i;j<56;j++)
    d[k++]=pc1_key[j];

    while(round<=n)
    {
        if(round==1||round==2||round==9||round==16)
        leftshift();
        else
        {
            leftshift();
            leftshift();
        }
        PC2();
        printf("\n key for round %d:\n",round);

        for(i=1;i<=48;i++)
        {
            printf("%d",pc2_key[i-1]);if(i%8==0)printf(" ");
            if(myfile==NULL)
            {
                printf("file not opened\n");
                return 1;
            }

            fprintf(myfile,"%d",pc2_key[i-1]);if(i%48==0)fprintf(myfile,"\n");
        }

        round++;
    }

    fclose(myfile);
    return 0;
}
