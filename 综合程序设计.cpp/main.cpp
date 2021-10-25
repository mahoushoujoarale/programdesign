#include "search.h"

#define INFINITY 1e6
#define Maxlen 300
#define Maxline 7

typedef int int_matrix[Maxlen][Maxlen];
typedef double double_matrix[Maxlen][Maxlen];

int_matrix p;//存储路径
double_matrix time_path;//存储时间最短路径
double_matrix price_path;//存储票价最小路径
double_matrix weight_path;//存储加权最小路径
//抽象数据类型定义
typedef struct
{
    int num;//地铁线路,几号线
    double length;//地铁线路的总长度
    int stopnum;//每趟地铁经过的总站数
    char Station[Maxlen][20];//每趟地铁经过的站点
}LineNode;//地铁线路信息

typedef struct// 每个结点存放的信息
{
    char StaName[20];
}VertexType;

typedef struct Arcell
{
    double time_cost;//时间花费
    double length_cost;//长度花费
    double weight_cost;//加权花费
    int linenum;
}Arcell, AdjMatrix[Maxlen][Maxlen];

typedef struct Graph
{
    AdjMatrix arcs;
    VertexType vexs[Maxlen];//顶点
    int vexnum;//站点数
}Graph;

Graph G;
LineNode Line[Maxline];
VertexType vexdata[Maxlen];

int main()
{
    system("color f4");
    int i;
    char a;
    Init(Line[0], "地铁1号线.txt");
    Init(Line[1], "地铁2号线.txt");
    Init(Line[2], "地铁3号线.txt");
    Init(Line[3], "地铁4号线.txt");
    Init(Line[4], "地铁6号线.txt");
    Init(Line[5], "地铁7号线.txt");
    Init(Line[6], "地铁8号线.txt");
    InitS(Line);
loop:
    choose();
    scanf("%d", &i);
    a = getchar();
    system("cls");

    switch (i)
    {
    case 1:
        printf("*************欢迎来到查看武汉地铁线路信息界面****************\n\n");
        printf("1:查看武汉具体每条地铁线路信息\n2:返回主界面\n");
        int k;
        scanf("%d", &k);
        switch (k)
        {
        case 1:
            PrintMGraph();
            break;
        case 2:
            char t;
            t = getchar();
            printf("...............按回车键进入................\n\n");
            t = getchar();
            system("cls");
            goto loop;
            break;
        default:
            printf("输入错误!\n");
        }
        printf("输入1返回主函数界面，输入2直接退出整个查询系统\n");
        int a1;
        scanf("%d", &a1);
        switch (a1)
        {
        case 1:
        {
            char t1;
            t1 = getchar();
            printf("...............按回车键进入................\n\n");
            t1 = getchar();
            system("cls");
            goto loop;
            break;
        }
        case 2:
            break;
        default:
            printf("输入错误!");
        }
        break;
    loop1:
    case 2:
    {
        printf("\t*******进入两地时间最短查询*******\n\n");
        printf("1:查询两地最短路程及所需时间\n2:返回主菜单.\n");
        int c;
        scanf("%d", &c);
        switch (c)
        {
        case 1:
            system("cls");
            Find();
            chose();
            break;
        case 2:
            char t2;
            t2 = getchar();
            printf("...............按回车键进入输入查询界面................\n\n");
            t2 = getchar();
            system("cls");
            goto loop;
            break;
        default:
            printf("输入错误!\n");
        }
        int b;
        scanf("%d", &b);
        switch (b)
        {
        case 3:
        {
            char t3;
            t3 = getchar();
            printf("...............按回车键进入输入查询界面................\n\n");
            t3 = getchar();
            system("cls");
            goto loop1;
            break;
        }
        case 4:
        {
            char t4;
            t4 = getchar();
            printf("...............按回车键进入输入主函数界面................\n\n");
            t4 = getchar();
            system("cls");
            goto loop;
            break;
        }

        default:
            printf("输入错误!\n");
            break;

        }

    }
    case 3:
        printf("\t********不进行查询!谢谢你使用武汉地铁换乘路线查询系统*********\n");
        break;
    default:
        printf("输入错误!!\n");
        break;
    }
    return 0;
}

//自己实现一个ceiling函数
int ceiling(double a, int b) {
    return (a + b - 1) / b;
}

//输入长度计算票价
int charge(double length) {
    double sum = 0;
    if (length <= 4) sum = 2;
    else if (length > 4 && length <= 12) sum = 2 + ceiling((length - 4), 4) * 1;    // 用ceiling函数来向上取整
    else if (length > 12 && length <= 24) sum = 4 + ceiling((length - 12), 6) * 1;
    else if (length > 24 && length <= 40) sum = 6 + ceiling((length - 24), 8) * 1;
    else if (length > 40 && length <= 50) sum = 8 + ceiling((length - 40), 10) * 1;
    else sum = 10 + ceiling((length - 50), 20) * 1;
    return sum;
}