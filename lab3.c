//use only small letters in plaintext

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
void decrypt(char key[]);

int main()
{
    char key[27];
    int i,j=0,arr[26]={0};
    srand(time(NULL));

//storing characters in key array randomly
    while(j<26){
        i=rand()%26;  //taking random integer
        if(arr[i]==0)   //to check if the integer is already used(this array used as flags)
       {    
            key[j++]='a'+i;  
            arr[i]=1;   //setting the flag to denote we have used the integer
        }
    }
    key[j]='\0';
    int frequency[26]={0};
    FILE *f1,*f2;
    char text;
    f1=fopen("plaintext.txt","r");
    f2=fopen("ciphertext.txt","w");
    while(fscanf(f1,"%c",&text)!=EOF){
        if(isalpha(text)){
            frequency[text-'a']++;
            fprintf(f2,"%c",key[text-'a']);
        }
        else
            fprintf(f2,"%c",text);
    }
    fclose(f1);
    fclose(f2);
    printf("%s\n",key);

    for(i=0;i<26;i++)
        printf("|%.2f| %c -> %c\n",((float)frequency[i]/1000)*100,'a'+i,key[i]);
        decrypt(key);
    return 0;
}

void decrypt(char key[])
{
    int i;
    char text;
    FILE *f1,*f2;
    f1=fopen("decryptedtext.txt","w");
     f2=fopen("ciphertext.txt","r");
      while(fscanf(f2,"%c",&text)!=EOF){
        if(isalpha(text)){
            for(i=0;i<26;i++)
                if(key[i]==text)  //to get the index of that character
                   break;
            fprintf(f1,"%c",'a'+i);  
        }
        else
            fprintf(f1,"%c",text);
    }
    fclose(f1);
    fclose(f2);
}
