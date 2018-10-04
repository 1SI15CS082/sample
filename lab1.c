#include <stdio.h>
#include <stdlib.h>
#include<ctype.h>
#include<string.h>

char* encrypt(char pt[30],char keymat[5][5])
{
    int i,j,k,w,x,y,z,c=0;
    char* cipher;
    char ch1,ch2;

    for(k=0;k<strlen(pt);k+=2)  //for each two characters
    {
        ch1=pt[k];
        ch2=pt[k+1];
    for(i=0;i<5;i++)
    {
        for(j=0;j<5;j++)
        {
            //searching in key matrix
            if(ch1==keymat[i][j]) 
            {
                w=i;
                x=j;
            }
            else if(ch2==keymat[i][j])
            {
                y=i;
                z=j;
            }
        }
    }

    if(w==y)
    {
// if in same row move one char left
        x=(x+1)%5;
        z=(z+1)%5;

        cipher[c++]=keymat[w][x];
        cipher[c++]=keymat[y][z];
    }
    else if(x==z)
    {
//if in same column move one char down
        w=(w+1)%5;
        y=(y+1)%5;

         cipher[c++]=keymat[w][x];
        cipher[c++]=keymat[y][z];
    }
    else
    {
        cipher[c++]=keymat[w][z];
        cipher[c++]=keymat[y][x];
    }
 }
 cipher[c]='\0';
printf("\n");
return cipher;
}


char* decrypt(char cipher[20],char mat[5][5])
{
    char* plain;
    int plen=0,i,k,l;
    int c11,c12,c21,c22;
    char ch1,ch2;
    for(i=0;i<strlen(cipher);i=i+2)
    {
        ch1=cipher[i];
        ch2=cipher[i+1];
        for(k=0;k<5;k++)
        {
            for(l=0;l<5;l++)
            {
                if(ch1==mat[k][l])
                {
                    c11=k;
                    c12=l;
                }
                if(ch2==mat[k][l])
               {
                c21=k;
                c22=l;
               }
            }
        }
        if(c11==c21)
        {
            plain[plen++]=mat[c11][(c12-1)>0?(c12-1)%5:((c12+4)%5)];
             plain[plen++]=mat[c21][(c22-1)>0?(c22-1)%5:((c22+4)%5)];
        }
        else if(c12==c22)
        {
            plain[plen++]=mat[(c11-1)>0?(c11-1)%5:((c11+4)%5)][c12];
            plain[plen++]=mat[(c21-1)>0?(c21-1)%5:((c21+4)%5)][c22];
        }
        else
        {
            plain[plen++]=mat[c11][c22];
            plain[plen++]=mat[c21][c12];
        }
    }
    plain[plen]='\0';
    printf("plain text :\n");

    return plain;
}

void modify_ip(char input[20],char modify[20])
{
    int len=0,i=0;
    while(input[i]!='\0')
    {
        modify[len++]=input[i++];
        if(input[i]=='\0' || input[i]==input[i-1])
        {
            modify[len++]='X';  //appending 'X' if two consecutive same characters appears
        }
        else
        modify[len++]=input[i++];
    }
    modify[len]='\0';
    printf("\n Modified plain text %s\n",modify);
}

int main()
{
    int i,j,m=0,k=0;
    char pt[30],key[30],keymat[5][5],keyminus[30],modify[30];
    char alpha[26]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    char* final;
    char *cipher;
    printf("enter the plain text: ");
    fgets(pt,50,stdin);
    printf("enter key: ");
    fgets(key,50,stdin);

//eliminating duplicate key characters

    for(i = 0; i < strlen(key); i++)
      {
          for(j = i + 1; key[j] != '\0'; j++)
          {
              if(key[j] == key[i])
            {
                  for(k = j; key[k] != '\0'; k++)
                {
                    key[k] = key[k + 1];
                }
             }
        }
    }

//considering 'j'  as ' i ' and converting to uppercase 
    for(i=0;i<strlen(pt);i++)
    {
        if(pt[i]=='j')pt[i]='i';
        else if(pt[i]=='J')pt[i]=='I';
        pt[i]=toupper(pt[i]);
    }
//considering 'j'  as ' i ' and converting to uppercase 
    for(i=0;i<strlen(key);i++)
    {
        if(key[i]=='j')key[i]='i';
        else if(key[i]=='J')key[i]=='I';
        key[i]=toupper(key[i]);
    }

    j=0;
//extracting characters that are not in the key
    for(i=0;i<26;i++)
    {
        for(k=0;k<strlen(key);k++)
        {
            if(key[k]==alpha[i])
            break;
            else if(alpha[i]=='J')break;
        }
        if(k==strlen(key))
        {
            keyminus[j]=alpha[i];
            j++;
        }
    }

    k=0;
//filling key table
    printf("key table\n");
    for(i=0;i<5;i++)
    {
        for(j=0;j<5;j++)
        {
            if(k<strlen(key)) //first fill with key
            {
            keymat[i][j]=key[k];
            k++;
            }
            else
            {
                keymat[i][j]=keyminus[m]; //next fill with characters that are not in key
                m++;
            }
            //printf("%c ",keymat[i][j]);
        }
        printf("\n");
    }

    for(i=0;i<5;i++){
        for(j=0;j<5;j++){
            printf("%c ",keymat[i][j]);
        }
        printf("\n");
    }


     modify_ip(pt,modify);
     cipher=encrypt(modify,keymat);
      printf("cipher text:%s",cipher);
     printf("\n");
     final=decrypt(cipher,keymat);

     for(i=0;i<strlen(final);i++)
     {
         if(final[i]!='X')      //not displaying the 'X' which was appended
         printf("%c",final[i]);
     }
 return 0;
}
