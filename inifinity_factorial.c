#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define M 10500

char num[M]={}, m_plier[M]={},temp[M],ans[M];

int num_len(int n)
{
    int cnt = 0;
    while (n)
    {
        n /= 10;
        cnt++;
    }
    return cnt;
}

void UNO_reverse(char ar[]){
    int temp=0;

    int n =strlen(ar);
    for(int i=0;i<(n/2);i++){
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
void multiply(){
    
    int n = strlen(num);
    int m = strlen(m_plier);
    int carry=0;
    //printf("%s %s\n",num,m_plier);
    for(int i=0;i<m;i++){
        carry=0;

        for(int k=0;k<i;k++){
            temp[k]='0';
        }

        for(int j=0;j<n;j++){

            int product = (num[j]-'0') * (m_plier[i]-'0') +carry;

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
        add();
        
    }
    Zero_is_NaN();

}

void charify(int n,char arr[]){

    int len=num_len(n);
    for(int i=len-1;i>=0;i--){
        arr[i]=n%10 +'0';
        n/=10;
    }
    arr[len]='\0';
    //printf("%s",m_plier);

}

int main(){

   
    printf("Enter the multiplicand and the multiplier:\n");

    int n=0;
    scanf("%d",&n);
    charify(n,num);


    UNO_reverse(num);

    
    
    
    for(int i=n-1;i>=1;i--){
        memset(temp,'0',M);
        memset(m_plier,'0',M);
        memset(ans,'0',M);

        charify(i,m_plier);

        UNO_reverse(m_plier);
        //printf("%s ",m_plier);
        

        multiply();
        memcpy(num,ans,strlen(ans)*1+1);
        
    }

    UNO_reverse(ans);

    printf("The result is %s",ans);
}