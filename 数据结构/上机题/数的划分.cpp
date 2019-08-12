#include<stdio.h> 
int stack[100]; 
int top; 
int total,n; 
void dfs(int index) 
{ 

    int i; 
    if(total==n) 
    { 
        printf("%d=",n); 
       for(i=top-1;i>0;i--) 
        printf("%d+",stack[i]); 
        printf("%d\n",stack[0]); 
    } 
    if(total>n ) 
        return ; 
    for(i=n-1;i>=index;i--) 
    { 
        total+=i; 
        stack[top++]=i; 
        dfs(i); 
        total-=i; 
        stack[--top]; 
    } 

} 

int main() 

{ 

    while(scanf("%d",&n)!=EOF) 

    { 

        top=0; 

        total=0; 

        dfs(1); 

    } 
return 0;
}
