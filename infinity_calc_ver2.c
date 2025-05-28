#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define M 1000

char target[M]={}, plier[M]={},temp[M],ans[M];
int t_dec = 0;//decimal places for target
int p_dec = 0;//decimal places for plier
int dec = 0; //decimal places for multiplication
int numify(char c){
    return c-'0';
}
void UNO_reverse(char ar[]){
    int temp=0;

    int n =strlen(ar);
    for(int i=0;i<ceil(n/2);i++){
        temp=ar[i];
        ar[i]=ar[n-1-i];
        ar[n-1-i]=temp;
    }
    
}

void Zero_is_NaN(){
    int n=strlen(ans),cnt=0,flag=0;;
    for(int i=0;i<n;i++){
        if(ans[i]=='0'){
            cnt++;
            if(ans[i+1]=='\0'){
                flag=1;
                break;
            }
            
        }
        else{
            cnt=0;
        }
        if(flag==1)
        {
            break;
        }
        
    }
    ans[n-cnt]='\0';

}

void add(char a1[],char a2[]){
    int carry=0;
    int n= strlen(a1);

    int m= strlen(a2);

    int l= n>m?n:m;

    for(int i=0;i<l;i++){
        
        if(!isdigit(a2[i])){
            a2[i]=(a1[i]+carry-'0')%10 +'0';
            carry=0;
            
        }
        else if(!isdigit(a1[i])){

            a2[i]=(a2[i] +carry -'0')%10 +'0';
            carry=0;

        }
        else{
            int addition = (a2[i]-'0')+(a1[i]-'0');
            a2[i] = (carry + addition)%10 +'0';
            carry = (carry + addition)/10;
        }
    }
    if(carry){
        a2[l]=carry+'0';
        a2[l+1]='\0';
    }
    else{
        a2[l]='\0';
    }

    //printf("a%s ",ans);

}
void multiply(int n,int m){
    
    int carry=0;
    
    for(int i=0;i<m;i++){
        carry=0;

        for(int k=0;k<i;k++){
            temp[k]='0';
        }

        for(int j=0;j<n;j++){

            int product = (target[j]-'0') * (plier[i]-'0') +carry;

            temp[j+i]=(product)%10 +'0';

            carry= (product)/10;
        }
        if(carry){
            temp[n+i]=carry+'0';

            temp[n+1+i]='\0';

        }
        else{
            temp[n+i]='\0';

        }
        //printf("%s\n",temp);
        add(temp,ans);
        
    }
    Zero_is_NaN();

}

int substract(int n,int m){
    if(m>n){
        return -1;
    }
    int i=0;
    for(i;i<n;i++){
        int sub=0;
        if(isdigit(plier[i]))
        {    sub = (numify(target[i])-numify(plier[i]));

            if(sub<0){
                int j=1;
                while(target[i+j]=='0'){
                    j++;
                }
                target[i+j]--;
                sub= (numify(target[i])+10-numify(plier[i]));

            }
            sub+='0';
        }
        else{
            sub=target[i];
        }
        ans[i]=sub;
    }
    ans[i]='\0';




}
int str_in(char ar[]){
    int d=0;
    char c=0;
    for(int i=0;;i++){
        c= getchar();
        if(c==' '){
            ar[i]='\0';
            break;
        }
        if(c=='\n'){
            ar[i]='\0';
            break;
        }
        ar[i]=c;
        
        if(ar[i]=='.'){
            i--;
            d=i+1;
        }
    
    }
    return d;
}
void division(){

}
void linear_decimal(){
    
    
    if(t_dec>p_dec){//target has more decimal places than plier
        int m=strlen(plier);
        UNO_reverse(plier);
        while(p_dec<t_dec){
            plier[m++]='0';
            p_dec++;
        }
        plier[m]='\0';
        UNO_reverse(plier);
    }
    else if(p_dec>t_dec){

        int n= strlen(target);
        UNO_reverse(target);
        while(t_dec<p_dec){
            target[n++]='0';
            t_dec++;
        }
        target[n]='\0';
        UNO_reverse(target);
    }

}

void mult_subfunction(int n,int m){

    multiply(n,m);    
    
    for(int i=(n*m)+1;i>dec-1;i--){
        ans[i] = ans[i-1];
    }
    ans[dec]='.';

}
void substract_subfunction(int n, int m){
    substract(n,m);
    
    for(int i=(n*m)+1;i>t_dec-1;i--){
        ans[i] = ans[i-1];
    }
    ans[t_dec]='.';


}
void add_subfunction(int n, int m){
    add(target,plier);
    strcpy(ans,plier);
    for(int i=(n*m)+1;i>t_dec-1;i--){
        ans[i] = ans[i-1];
    }
    ans[t_dec]='.';

}

int main(){

    // memset(target,' ',M);
    // memset(plier,' ',M);
    // memset(temp,' ',M);
    // memset(ans,' ',M);
    printf("What do you wish to calculate:\n");
    printf("Current available calculators are:\nSubstraction,Addition and Multiplication with decimal support\n");
    printf("input in the form a * b / a - b\n");

    char c=0;

    t_dec = str_in(target);

    int n=strlen(target);

    t_dec = n-t_dec;
    dec+= t_dec;


    char symbol;
    scanf("%c ",&symbol);


    p_dec = str_in(plier);


    int m=strlen(plier);
  
    p_dec = m-p_dec;

    dec+= p_dec;


    UNO_reverse(target);
    UNO_reverse(plier);

    if(symbol =='-'){
        linear_decimal();
        substract_subfunction(n,m);
    }
    else if(symbol=='+'){
        linear_decimal();
        printf("%s %s",target,plier);
        add_subfunction(n,m);
    }
    else if(symbol=='*'){
        mult_subfunction(n,m);
    }
    
    
    
    UNO_reverse(ans);

    

    
    printf("The result is %s",ans);
}