#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

int euclid(int a, int m)
{
    int m0 = m;
    int y = 0, x = 1;

    if (m == 1)
      return 0;

    while (a > 1)
    {
        // q is quotient
        int q = a / m;
        int t = m;

        // m is remainder now, process same as
        // Euclid's algo
        m = a % m, a = t;
        t = y;

        // Update y and x
        y = x - q * y;
        x = t;
    }

    // Make x positive
    if (x < 0)
       x += m0;

    return x;
}

char * encrypt(char input[],int key[3][3],int dim)
{
    int i,j,k,clen, len, flag=0,l;

    int out[3][1], med[3][1];
    char inp[30];
    static char cipher[50];
    //converting to lowercase
    for(i=0,len=0;i<strlen(input);i++)
        if(input[i]!=' ' && isalpha(input[i]))
            inp[len++]=tolower(input[i]);
    inp[len]='\0';
    i=len=strlen(inp);
    //appending 'x'
    while(len%dim!=0)
    {
        inp[i++]='x';
        len++;
        flag=1;
    }
    if(flag)
    inp[len]='\0';

    for(i=0,clen=0;i<strlen(inp);i=i+dim)
    {
        for(k=0;k<dim;k++)
            med[k][0]=inp[i+k]-'a';
        
        for(k=0;k<dim;k++)
        {
            out[k][0]=0;
            
            for(l=0;l<dim;l++)
                out[k][0]+=key[k][l]*med[l][0];
        }
        
        for(k=0;k<dim;k++)
            cipher[clen++]=(out[k][0]%26)+'a';
    }
    cipher[clen]='\0';
    return cipher;
}

void inverse(int key[3][3],int dim,int inv[3][3])
{
    int i,j,mat[3][3], a[5][5] ;
    int det = 0;

    if(dim==2)
    {
        det=key[0][0]*key[1][1]- key[0][1]*key[1][0];
        mat[0][0]=key[1][1];
        mat[0][1]=key[0][1]*-1;
        mat[1][0]=key[1][0]*-1;
        mat[1][1]=key[0][0];
    }
    else
    {
        //convert 3*3 to 5*5
        for(i=0;i<5;i++)
        {
            for(j=0;j<5;j++)
            {
                a[i][j]=key[i%3][j%3];
            }
        }

        for(i=0;i<3;i++)
            for(j=0;j<3;j++)
            {
                mat[j][i]=a[i+1][j+1]*a[i+2][j+2]-a[i+1][j+2]*a[i+2][j+1];
                if(mat[j][i]<0)
                mat[j][i]=-(25*mat[j][i])%26;  //negative mod
                else
                mat[j][i]=mat[j][i]%26;
            }

        for(i = 0; i < 3; i++)
            det = det + (key[0][i] * (key[1][(i+1)%3] * key[2][(i+2)%3] - key[1][(i+2)%3] *key[2][(i+1)%3]));
    }


    if(det<0)
        det=-(25*det)%26;
    int mi; //multiplicative inverse
    
    mi=euclid(det,26);

    for(i=0;i<dim;i++)
        for(j=0;j<dim;j++)
        {
            inv[i][j]=(mi*mat[i][j]);
            if(inv[i][j]<0) //negative mod
            inv[i][j]=-(25*inv[i][j])%26;
            else
            inv[i][j]=inv[i][j]%26;
        }
}

char* decrypt(int key[3][3],int dim,char cipher[])
{
    int i,j,k,l,len,temp=0;
    int out[3][1],med[3][1];
    int inv[3][3];
    static char plain[50];
    inverse(key,dim,inv);
    for(len=0,i=0;i<strlen(cipher);i+=dim)
    {
        for(k=0;k<dim;k++)
            med[k][0]=cipher[i+k]-'a';
        for(k=0;k<dim;k++)
        {
            out[k][0]=0;
            for(l=0;l<dim;l++)
            out[k][0]+=inv[k][l]*med[l][0];
        }
        for(k=0;k<dim;k++)
            plain[len++]=(out[k][0]%26)+'a';
    }
    plain[len]='\0';
    return plain;
}



int main(){

    int key[3][3],dim;
    char input[30], *cipher, *plain;
    printf("Enter the plain text:");
    scanf("%[^\n]s",input);
    printf("Enter dimension:");
    scanf("%d",&dim);
    printf("Enter matrix:\n");
    int i,j;
    for(i=0;i<dim;i++)
        for(j=0;j<dim;j++)
            scanf("%d",&key[i][j]);
    cipher=encrypt(input,key,dim);
    printf("cipher:%s\n",cipher);

    plain=decrypt(key,dim,cipher);

    printf("text after decryption:\n");
    for(i=0;i<strlen(plain);i++)
        if(plain[i]!='x')  //not displaying the appended 'x'
    printf("%c",plain[i]);


   return 0;
}
