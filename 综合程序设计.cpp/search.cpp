#include "search.h"

/* 用Dijkstra算法求有向网G的v0顶点到其余顶点v的最短路径P[i][v]及其带权长度time_path[v]。*/
/* P[i][v]的值为前驱结点下标，time_path[i][v]表示v0到v的最短路径之和。 */
void Dijkstra(Graph G, int_matrix* p, double_matrix* time_path)
{
    int v, w, k, i, s;
    double t, min;
    int final[Maxlen];  /* final[w]=1表示求得顶点v0到v的最短路径 */
    for (i = 0; i < G.vexnum; i++) /* 初始化数据 */
    {
        for (v = 0; v < G.vexnum; v++)
        {
            final[v] = 0; /* 全部顶点初始化为未知最短路径状态 */
            (*time_path)[i][v] = G.arcs[i][v].time_cost;/* 将与v0点有连线的顶点加上权值 */
            (*p)[i][v] = -1; /* 初始化路径数组p为-1 */
        }
        (*time_path)[i][i] = 0;/* v0到v的路径为0 */
        /* 开始主循环，每次求得vo到每个v顶点的最短路径 */
        for (v = 1; v < G.vexnum; v++)
        {
            min = INFINITY;  /* 当前所知离v0顶点的最短距离 */
            for (w = 0; w < G.vexnum; w++)
            {
                if (!final[w] && (*time_path)[i][w] < min)
                {
                    k = w;
                    min = (*time_path)[i][w]; /* w顶点离v0顶点更近 */
                }
            }
            final[k] = 1; /* 将目前找到的最近的顶点置为1 */
            for (w = 0; w < G.vexnum; w++) /* 修正当前最短路径及距离 */
            {
                s = (*p)[i][k];/*求节点的上一条路径*/
                if (s == -1) s = i;/*第一次找到最短路线时对应的路径*/
                if ((G.arcs[k][s].linenum != G.arcs[k][w].linenum) && s != -1)
                    t = min + G.arcs[k][w].time_cost + 3.5;/*如果两条路径对应路线不同，即车辆换乘，所用时间需增加3.5分钟*/
                else
                    t = min + G.arcs[k][w].time_cost;/*如果两条路径对应路线相同，即车辆未换乘，所用时间不改变*/
                /* 说明找到了更短的路径，修正time_path[i][w]和 p[i][w]*/
                if (!final[w] && (t < (*time_path)[i][w]))
                {
                    (*time_path)[i][w] = t;
                    (*p)[i][w] = k;
                }
            }
        }
    }
}

void check(char p[20], int& m, int& n)//判断起始站和终点站是否为换乘站
{
    int i, j;
    for (i = 0; i < Maxline; i++)
        for (j = 0; j < Line[i].stopnum; j++)
            if (!strcmp(p, Line[i].Station[j]))
                m = i;
    for (i = 0; i < Maxline; i++)
    {
        if (i != m)
        {
            for (j = 0; j < Line[i].stopnum; j++)
                if (!strcmp(p, Line[i].Station[j]))
                    n = i;
        }
    }
}

//判断下一个站的路线是否发生改变
void transfer(int a, int b, int c)
{
    if (b != c && G.arcs[a][b].linenum != G.arcs[b][c].linenum)
        printf("(请在该站下车，换乘%d号线)", G.arcs[b][c].linenum);
}

void Find()
{
    int i, j, k, a, b;
    char v1[20], v2[20];
    CreateMGraph(Line, vexdata, G);//初始化图
    Dijkstra(G, &p, &time_path);//耗时最短路径算法
    printf("\n**************路线查询***************\n\n");
    int m1 = -1, m2 = -1, n1 = -1, n2 = -1;
    printf("请输入你要查询的起始站点:");
loop:
    scanf("%s", v1);
    j = LocateVex(G, v1);
    if (j == -1)
    {
        printf("你输入的查询起点有误，请重新输入!\n");
        goto loop;
    }
    else
    {
        check(v1, m1, n1);
        if (m1 >= 0 && n1 < 0)//v1不为换乘站
        {
            printf("你当前所在地铁线路为地铁%d号线\n\n", Line[m1].num);
        }
        else if (m1 >= 0 && n1 >= 0)
        {
            printf("你当前所在站点为换乘车站，是在地铁%d号线与地铁%d线的交点处\n\n", Line[m1].num, Line[n1].num);
        }
    }

    printf("请输入你要查询的终站点:");
loop1:
    scanf("%s", v2);
    i = LocateVex(G, v2);
    if (i == -1)
    {
        printf("你输入的查询终点有误，请重新输入!\n");
        goto loop1;
    }
    else
    {
        check(v2, m2, n2);
        if (m2 >= 0 && n2 < 0)//v2不为换乘站
        {
            printf("你所要到的站点在地铁%d号线\n\n", Line[m2].num);
        }
        else if (m2 >= 0 && n2 >= 0)
        {
            printf("你所要到的站点为换乘车站，是在地铁%d号线与地铁%d号线的交点处\n\n", Line[m2].num, Line[n2].num);
        }
    }
    k = j;
    printf("你要花费最少时间到达的路线为:\n\n");
    while (p[i][k] != -1)
    {
        printf("%s->", G.vexs[k].StaName);
        a = k;
        k = p[i][k];
        b = p[i][k];
        if (b != -1)
            transfer(a, k, b);
    }
    printf("%s->", G.vexs[k].StaName);
    transfer(a, k, i);
    if (k != i)
        printf("%s", G.vexs[i].StaName);
    printf("\n\n");
    printf("所用的最短时间为：");
    printf("%lf\n\n", time_path[i][j]);
}

void choose()
{
    printf("\t             ----------------------------------------------                      \n");
    printf("\t	               欢迎你使用武汉地铁换乘路线查询系统            		           \n");
    printf("\t             ----------------------------------------------                    \n\n");
    printf("\t             ******1.查看武汉的地铁线路信息****************                      \n");
    printf("\t             ******2.按两地最短时间查询********************                      \n");
    printf("\t             ******3.退出查询******************************\n\n");
    printf("请输入你的选择:\n");
}

void chose()
{
    printf("***********3.继续查询**************\n");
    printf("***********4.返回主函数************\n");

    printf("请输入你的选择:\n");
}