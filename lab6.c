#include<stdio.h>
#include<math.h>
int l[32],r[32],er[48];
int pc2_key[48];
int pt[64];
int e_bit[8][6]={
            32,1,2,3,4,5,
            4,5,6,7,8,9,
            8,9,10,11,12,13,
            12,13,14,15,16,17,
            16,17,18,19,20,21,
            20,21,22,23,24,25,
            24,25,26,27,28,29,
            28,29,30,31,32,1
          };

int ip[8][8]={
               58,50,42,34,26,18,10,2,
               60,52,44,36,28,20.12,4,
               62,54,46,38,30,22,14,6,
               64,56,48,40,32,24,16,8,
               57,49,41,33,25,17,9,1,
               59,51,43,35,27,19,11,3,
               61,53,45,37,29,21,13,5,
               63,55,47,39,31,23,15,7
               };

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

void etable()
{
 int i,j,k=0;
 for(i=0;i<8;i++)
 {
   for(j=0;j<6;j++)
   {
     er[k++]=r[e_bit[i][j]-1];
   }
 }
}


void xor48()
{
  int i;
  for(i=0;i<48;i++)
    {
      if(er[i]==pc2_key[i])
      er[i]=0;
      else
      er[i]=1;
    }
}

int main()
{
  int i,j,k=0,n;
  int hex[64],bin[64],bin1[64];
  FILE *input,*myfile1;
  FILE *key;
  input=fopen("plain.txt","r");

  for(i=0;i<16;i++)
  fscanf(input,"%x",&hex[i]);

  converttobinary(hex,bin);

  printf("Input from i-1th round\n");
  for(i=0;i<64;i++)
      printf("%d",bin[i]);
  printf("\n");

  printf("After initial permutation of input\n");
  for(i=0;i<8;i++)
    for(j=0;j<8;j++)
      bin1[k++]=bin[ip[i][j]-1];

  for(i=0;i<64;i++)
    printf("%d",bin1[i]);

  j=0;
  printf("\n");

//for next lab program
/* FILE *fp;
for(i=0;i<32;i++)
l[j++]=bin1[i];
fp=fopen("left.txt","w");


for(i=0;i<32;i++)
fprintf(fp,"%d",l[i]); */

  printf("Right most 32 bits of input plain text\n");
  j=0;

for(i=32;i<64;i++)
    r[j++]=bin1[i];
for(i=0;i<32;i++)
    printf("%d",r[i]);

 etable();
 printf("\n");
 printf("input after expansion table\n");
 for(i=0;i<48;i++)
    printf("%d",er[i]);

 key=fopen("input.txt","r");

 printf("\ntaking the sub key -1 \n");

    printf("\n");
   for(j=0;j<48;j++)
   fscanf(key,"%1d",&pc2_key[j]);

 for(j=0;j<48;j++)
 printf("%d",pc2_key[j]);

 printf("\n");
 myfile1=fopen("output.txt","w");
  xor48();

  printf("After xor\n");
  for(i=0;i<48;i++)
  {
      printf("%d",er[i]);
      fprintf(myfile1,"%d",er[i]);
  }
  fclose(key);
  fclose(input);
  return 0;
}
