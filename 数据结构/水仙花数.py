str=input().split()
m=int(str[0])
n=int(str[1])
key=0
for x in range(m,n+1):
    i=3;
    count=0
    x1=x
    while (i>0):
        temp=x1%10
        x1=int(x1/10)
        count+=temp*temp*temp
        i-=1 
    if count==x:
        print(x,end=" ")
        key=1
if key==0:
     print("no")
else:
    print()


 

