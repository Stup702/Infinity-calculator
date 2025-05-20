#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define M 1000

char num[M]={}, m_plier[M]={},temp[M],ans[M];

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

void add(){
    int carry=0;
    int n= strlen(temp);

    int m= strlen(ans);

    int l= n>m?n:m;

    for(int i=0;i<l;i++){
        
        if(!isdigit(ans[i])){
            ans[i]=(temp[i]+carry-'0')%10 +'0';
            carry=0;
            
        }
        else if(!isdigit(temp[i])){

            ans[i]=(ans[i] +carry -'0')%10 +'0';
            carry=0;

        }
        else{
            int addition = (ans[i]-'0')+(temp[i]-'0');
            ans[i] = (carry + addition)%10 +'0';
            carry = (carry + addition)/10;
        }
    }
    if(carry){
        ans[l]=carry+'0';
        ans[l+1]='\0';
    }
    else{
        ans[l]='\0';
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

            int multiple = (num[j]-'0') * (m_plier[i]-'0');

            temp[j+i]=(carry + multiple )%10 +'0';

            carry= (carry +multiple)/10;
        }
        if(carry){
            temp[n+i]=carry+'0';

            temp[n+1+i]='\0';

        }
        else{
            temp[n+i]='\0';

        }
        //printf("%s\n",temp);
        add();
        
    }
    Zero_is_NaN();

}

int main(){

    // memset(num,' ',M);
    // memset(m_plier,' ',M);
    // memset(temp,' ',M);
    // memset(ans,' ',M);
    printf("Enter the multiplicand and the multiplier:\n");

    scanf("%s %s",num,m_plier);
    UNO_reverse(num);
    UNO_reverse(m_plier);
    int n=strlen(num),m=strlen(m_plier);
    
    multiply(n,m);     

    UNO_reverse(ans);

    
    printf("The rsult is %s",ans);
}