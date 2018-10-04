#include<stdio.h>
#include<string.h>


char *encrypt(char *p,int sequence[],int l1)
{
    int i,j,l2,order[l1];
    for(i=1;i<=l1;++i)
    {
        for(j=0;j<l1;++j)
        {
            if(sequence[j]==i)
                order[i-1]=j;
        }
    }
    l2=strlen(p);
    if(l2%l1!=0)
    {
        while(l2%l1!=0)
            p[l2++]='x';
        p[l2]='\0';
        printf("bogus char used:%c\n",'x');
        printf("final ip:%s",p);
    }
    int r=l2/l1;  //row size
    char p1[r][l1];
    int count=0;
    printf("\n encryption\n");

    for(i=0;i<r;i++)
    {
        for(j=0;j<l1;j++)
        {
            p1[i][j]=p[count];   //writing row by row
            count=count+1;
        }
    }
    for(i=0;i<r;i++)
    {
        for(j=0;j<l1;j++)
        {
            printf("%c",p1[i][j]);
        }
        printf("\n");
    }
    count=0;

    for(i=0;i<l1;++i)
    {
        for(j=0;j<r;++j)
        {
            p[count]=p1[j][order[i]];  //reading column by column
            count=count+1;
        }
    }

return(p);

}

char* decrypt(char *p,int sequence[],int l1)
{

    int i,j,r,l2;
    l2=strlen(p);
    r=l2/l1;
    char p1[20][20];
    int order[l1];
    for(i=1;i<=l1;++i)
    {
        for(j=0;j<l1;++j)
        {
            if(sequence[j]==i)
                order[i-1]=j;
        }
    }
    printf("decryption\n");
        int count=0;
        for(i=0;i<l1;i++)
        {
            for(j=0;j<r;j++)
            {
                p1[j][order[i]]=p[count];
                count=count+1;
            }
        }
    for(i=0;i<r;i++)
    {
        for(j=0;j<l1;j++)
        {
            printf("%c",p1[i][j]);
        }
        printf("\n");
    }
    count=0;
    for(i=0;i<r;i++)
    {
        for(j=0;j<l1;j++)
        {
            p[count]=p1[i][j];
            count=count+1;
        }

    }

return p;
}



int main()
{
    int l1,i;
    char pt[100];
    char* cipher,*Dpt;
    printf("\n enter length of key:\n");
    scanf("%d",&l1);
    int sequence[l1];
    printf("enter seq ky:\n");
    for(i=0;i<l1;++i)
    {
        scanf("%d",&sequence[i]);
    }


    printf("enter plain text without spaces\n");
    scanf("%s",pt);
    cipher=encrypt(pt,sequence,l1);
    printf("\n ciphertext:\n");
    for(i=0;i<strlen(cipher);i++)
        printf("%c",cipher[i]);
    printf("\n\n");
    Dpt=decrypt(cipher,sequence,l1);
    printf("after decryption plain text is:");
    for(i=0;i<strlen(Dpt);i++)
    if(Dpt[i]!='x')
    printf("%c",Dpt[i]);

return(0);
}
