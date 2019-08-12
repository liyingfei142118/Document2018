#include <stdio.h>
#include <malloc.h>
//记录通道块在迷宫矩阵当中的横、纵坐标 
struct Position{
    int x;
    int y;
}; 
//放入栈当中的通道块元素 
struct SElement {
    int ord;//记录此通道块在整个通道当中的次序 
    Position p;//记录此通道块在矩阵当中的位置 
    int di;//记录下一次测试这一路径的临近路径的位置 
}; 
//创建栈数据结构
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
struct MyStack{
    SElement* base;
    SElement* top;
    int stacksize;
};
//创建一个栈如果创建成功则返回1，否则就返回0
int InitStack(MyStack* s)
{
    s->base=(SElement*)malloc(STACK_INIT_SIZE*sizeof(SElement));//为栈分配初始空间 
    if(!s->base) return 0;
    s->top=s->base;//设定为空栈 
    s->stacksize=STACK_INIT_SIZE;
    return 1; 
}
//判断栈是否为空，如果是空的就返回0，否则就返回1 
int IsStackEmpty(MyStack* s)
{
    if(s->top==s->base) return true;
    return false;
} 
//获取栈顶元素,如果栈为空就返回0 否则就返回1
int GetTop(MyStack* s,SElement* e)
{
    if(IsStackEmpty(s)) return 0;
    e=s->top-1;
    return 1; 
}
//获取栈的长度，并且通过程序返回 
int StackLength(MyStack* s)
{
    return s->top-s->base;
}
//插入元素e为新的栈顶元素，插入成功则返回1，否则返回0
int  Push(MyStack* s,SElement e)
{
    if(s->top-s->base>=STACK_INIT_SIZE)
    {
        s->base=(SElement*)realloc(s->base,(s->stacksize+STACKINCREMENT)*sizeof(SElement));
        if(!s->base) return 0;
        s->top=s->base+s->stacksize;
        s->stacksize+=STACKINCREMENT;
    }
    *(s->top)=e;
    s->top++;
    return 1;
}
//弹出栈顶元素赋值给e弹出成功返回1，弹出失败返回0
int Pop(MyStack* s,SElement* e)
{
    if(IsStackEmpty(s)) return 0;
    *e=*(s->top-1);
    s->top--;
    return 1;
} 
//定义墙元素为2 可走路径为0 已知路径为curStep 不能够通过的路径为-1 
#define MazeScale 10
int Maze[MazeScale][MazeScale]={{2,2,2,2,2,2,2,2,2,2},{2,0,0,2,0,0,0,2,0,2},{2,0,0,2,0,0,0,2,0,2},{2,0,0,0,0,2,2,0,0,2},
{2,0,2,2,2,0,0,0,0,2},{2,0,0,0,2,0,0,0,0,2},{2,0,2,0,0,0,2,0,0,2},{2,0,2,2,2,0,2,2,0,2},{2,2,0,0,0,0,0,0,0,2},{2,2,2,2,2,2,2,2,2,2}};
//辅助函数考察当前路径能否通过 
bool Pass(Position posi)
{
    //只有路径所在位置的数字为0的是可以走的 
    if(Maze[posi.x][posi.y]==0)
    {
        return true;
    } 
    return false; 
}
//按顺时针方向从东开始寻找矩阵当中某一个位置的临近位置 
Position NextPosition(Position now,int direction)
{
    Position next;
    int x=now.x;
    int y=now.y;
    switch(direction)
    {
        //东 
        case 1:{
            next.x=x;
            next.y=y+1;
            break;
        }
        //南 
        case 2:{
            next.x=x+1;
            next.y=y; 
            break;
        }
        //西
        case 3:{
            next.x=x;
            next.y=y-1;
            break;
        }
        //北
        case 4:
        {
            next.x=x-1;
            next.y=y;
            break;
        } 
        default:break;
    }
    return next;
}
//留下足迹 
void FootPrint(Position p,int step)
{
    Maze[p.x][p.y]=step;
}
//路径不可走的话就留下-1的标记 
void MarkPrint(Position p)
{
    Maze[p.x][p.y]=-1;
}
int main()
{
    //打印出迷宫矩阵 
    for(int i=0;i<MazeScale;i++)
    {
        for(int j=0;j<MazeScale;j++)
        {
            printf("%d ",Maze[i][j]);
        }
        printf("\n");
    }
    //迷宫程序主体
    MyStack  path;//记录路径的栈
    InitStack(&path);//初始化路径数组
    Position curp;//当前被试位置
    //初始化当前位置为矩阵入口 
    curp.x=1;
    curp.y=1;
    int curStep=1;//被探索的步数 
    do
    {
        if(Pass(curp))
        {
            FootPrint(curp,curStep);//可走就在迷宫里面留下足迹 
            //创建一个栈元素，存储可行路径的相关值，将这个元素存储到栈当中
            SElement e;
            e.di=1;//意味着下一个被试路块为这一个路块的正上方的路块 
            e.ord=curStep;
            e.p.x=curp.x;
            e.p.y=curp.y;
            Push(&path,e);//将路径块入栈 
            if(curp.x==MazeScale-2 && curp.y==MazeScale-2) break; //如果被压入的路径块到了迷宫的终点就退出循环
            //找到下一个被试块
            curp=NextPosition(curp,1);//找到前一个被试块东面的路径块作为被试块
            curStep++;//被探索的步数加一 
        }else//如果当前被试路径不能够通过的话 
        { 
            if(!IsStackEmpty(&path))
            {
                SElement e;
                Pop(&path,&e);
                curStep--;
                //将这一段所有的周围路径都已经被测试过的路径从栈中清除 
                while(e.di==4 && !IsStackEmpty(&path)){
                    MarkPrint(e.p); 
                    Pop(&path,&e);
                    curStep--;
                }
                //如果当前栈顶还有未被测试的路径就测试剩余的周围路径 
                if(e.di<4)
                {
                    curp=NextPosition(e.p,e.di+1);
                    e.di++;
                    curStep++;
                    Push(&path,e);
                }
            }
        } 
    }while(!IsStackEmpty(&path));
    printf("\n");
    //打印出结果迷宫矩阵 
    for(int i=0;i<MazeScale;i++)
    {
        for(int j=0;j<MazeScale;j++)
        {
            printf("%d   ",Maze[i][j]);
        }
        printf("\n");
    }
    return 0;
}
