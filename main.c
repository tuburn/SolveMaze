#include<stdio.h>
#include<math.h>
#define ERROR 0
#define OK 1
#define FALSE 0
#define TRUE 1
#define OVERFLOW -1
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
#define ROW 10
#define COLUMN 10
typedef struct{
    int x;
    int y;
}PosType;
typedef struct{
    int ord;
    int dir;
    PosType seat;
}SElemType;
typedef struct{
    char **maze;
    int **footprint;
    int row;
    int column;
}MazeType;
typedef struct{
    SElemType *top;
    SElemType *base;
    int stacksize;
}SqStack;
int InitStack(SqStack *S){
    S->base=(SqStack *)malloc(STACK_INIT_SIZE*sizeof(SqStack));
    if(!S->base)exit(OVERFLOW);
    S->top=S->base;
    S->stacksize=STACK_INIT_SIZE;
    return OK;
}
int Push(SqStack *S,SElemType e){
    if(S->top-S->base>=S->stacksize){
        S->base=(SqStack *)realloc(S->base,(S->stacksize+STACKINCREMENT)*sizeof(SqStack));
        if(!S->base)exit(OVERFLOW);
        S->top=S->base+S->stacksize;
        S->stacksize+=STACKINCREMENT;
    }
    *S->top++=e;
    return OK;
}
int Pop(SqStack *S,SElemType *e){
    if(S->base==S->top)exit(OVERFLOW);
    *e=*--S->top;
    return OK;
}
int GetTop(SqStack S,SElemType *e){
    if(S.base==S.top)return FALSE;
    *e=*(S.top-1);
    return OK;
}
int  StackEmpty(SqStack S){
    if(S.base==S.top)return TRUE;
    else return FALSE;
}
int InitMaze(MazeType *MT){
    char maze[10][10];
    int i,j;
    for(i=1;i<9;i++)
        for(j=1;j<9;j++)
        maze[i][j]='O';
    for(i=0;i<10;i++){
        maze[0][i]='#';
        maze[9][i]='#';
        maze[i][0]='#';
        maze[i][9]='#';
    }
    maze[1][3]=maze[1][7]='#';
    maze[2][3]=maze[2][7]='#';
    maze[3][5]=maze[3][6]='#';
    maze[4][2]=maze[4][3]=maze[4][4]='#';
    maze[5][4]='#';
    maze[6][2]=maze[6][6]='#';
    maze[7][2]=maze[7][3]=maze[7][4]=maze[7][6]=maze[7][7]='#';
    maze[8][1]='#';

    MT->maze=(char **)malloc(ROW*sizeof(char *));
    MT->footprint=(int **)malloc(ROW*sizeof(int *));
    if(!MT->maze||!MT->footprint)exit(OVERFLOW);
    for(i=0;i<ROW;i++){
        MT->maze[i]=(char *)malloc(COLUMN*sizeof(char));
        MT->footprint[i]=(int *)malloc(COLUMN*sizeof(int));
        if(!MT->maze[i]||!MT->footprint[i])exit(OVERFLOW);
    }
    for(i=0;i<ROW;i++)
        for(j=0;j<COLUMN;j++){
            MT->maze[i][j]=maze[i][j];
            MT->footprint[i][j]=0;
        }
    for(i=0;i<ROW;i++){
        for(j=0;j<COLUMN;j++){
            printf("%c ",MT->maze[i][j]);
        }
        printf("\n");
    }
    return OK;
}
int Pass(MazeType MT,PosType PT){
    if(MT.maze[PT.x][PT.y]=='O'&&MT.footprint[PT.x][PT.y]==0)return OK;
    else return FALSE;
}
int FootPrint(MazeType *MT,PosType PT){
    MT->footprint[PT.x][PT.y]=1;
    return 0;
}
PosType NextPos(PosType PT,int e){
    switch(e){
        case 1:PT.x++;break;
        case 2:PT.y--;break;
        case 3:PT.x--;break;
        case 4:PT.y++;break;
        default:exit(OVERFLOW);
    }
    return PT;
}
int main(){
    SqStack S;
    InitStack(&S);
    MazeType Maze;
    InitMaze(&Maze);
    SElemType se;
    PosType curpos,star,dest;
    printf("请输入起始点坐标：\n");
    scanf("%d,%d",&star.x,&star.y);
    printf("请输入终点坐标：\n");
    scanf("%d,%d",&dest.x,&dest.y);
    curpos=star;
    int curstep=1,i,j;
    do{
        if(Pass(Maze,curpos)){
            FootPrint(&Maze,curpos);
            se.ord=curstep;
            se.dir=1;
            se.seat=curpos;
            Push(&S,se);
            if(curpos.x==dest.x&&curpos.y==dest.y)
                break;
            curpos=NextPos(curpos,1);
            curstep++;
        }
        else{
            if(!StackEmpty(S)){
                Pop(&S,&se);
                while(se.dir==4&&!StackEmpty(S)){
                    FootPrint(&Maze,se.seat);
                    Pop(&S,&se);curstep--;
                }
                if(se.dir<4){
                    se.dir++;
                    Push(&S,se);
                    curpos=NextPos(se.seat,se.dir);
                }
            }
        }
    }while(!StackEmpty(S));
    printf("步数：%d\n",curstep);
    while(!StackEmpty(S)){
        Pop(&S,&se);
        Maze.maze[se.seat.x][se.seat.y]=' ';
    }
    for(i=0;i<ROW;i++){
        for(j=0;j<COLUMN;j++){
            printf("%c ",Maze.maze[i][j]);
        }
        printf("\n");
    }
    return 0;
}
