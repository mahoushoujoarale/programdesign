#include "map.h"

void Init(LineNode& Line, const char* a)//将文件中的站台信息读取到Line中，地铁线号用字符表示
{
    FILE* fp;
    int i, no;
    if ((fp = fopen(a, "r")) == NULL)
    {
        printf("Can't open the file!\n");
        exit(0);
    }
    no = fscanf(fp, "%d %d %lf", &(Line.num), &(Line.stopnum), &(Line.length));
    no++;
    for (i = 0; no != NULL; i++)
    {
        no = fscanf(fp, "%s", Line.Station[i]);
        no++;
    }
    fclose(fp);
}

//将每个站点的名字初始化
void InitS(LineNode* L)
{
    int i = 0, j, t = 0;
    while (t < Maxline)
    {
        {
            for (j = 0; j < L[t].stopnum; j++)
            {
                strcpy(vexdata[i++].StaName, L[t].Station[j]);
            }
            t++;
        }
    }
}

//打印所有的地铁路线
void PrintMGraph()
{
    int i, j;
    for (i = 0; i < Maxline; i++)
    {
        printf("地铁%d号线: ", Line[i].num);
        for (j = 0; j < Line[i].stopnum; j++)
            printf("%s->", Line[i].Station[j]);
        printf("总的结点数%d", Line[i].stopnum);
        printf("\n\n");
    }
    return;
}

//单独打印某条线路的所有站点
void PrintMGraph1(LineNode& Line)
{
    int j;
    printf("地铁%d号线: ", Line.num);
    for (j = 0; j < Line.stopnum; j++)
        printf("%s->", Line.Station[j]);
    printf("总的结点数%d", Line.stopnum);
    printf("\n\n");
}

//LocateVex函数在下面建图函数中调用的时候是用来找到v1，v2结点分别在G向量中的位置的。
int LocateVex(Graph G, char u[20])
{
    int i;
    for (i = 0; i < G.vexnum; i++)
        if (!strcmp(u, G.vexs[i].StaName))
            return i;
    if (i == G.vexnum)
        return -1;
}

//建立图模型将所有的初始化的数据放到图的每项中。
int CreateMGraph(LineNode* Line, VertexType* vexdata, Graph& G)
{
    int i, j, m, n, flag;
    for (i = 0; i < Maxlen; i++)
    {
        flag = 0;
        for (j = 0; j < i; j++)
            if (!strcmp(G.vexs[j].StaName, vexdata[i].StaName))
                flag = 1;
        if (!flag)
            strcpy(G.vexs[i].StaName, vexdata[i].StaName);
    }
    G.vexnum = Maxlen;
    for (i = 0; i < G.vexnum; i++)
        for (j = 0; j < G.vexnum; j++)
            G.arcs[i][j].time_cost = INFINITY;
    for (m = 0; m < Maxline; m++)
        for (n = 0; n < Line[m].stopnum - 1; n++)
        {
            i = LocateVex(G, Line[m].Station[n]);//i表示在G向量结点数组中的位置
            j = LocateVex(G, Line[m].Station[n + 1]);	//j表示在G向量结点数组中的位置
            G.arcs[i][j].time_cost = 3;//将时间值赋给i到j的弧上
            G.arcs[j][i].time_cost = 3;
            G.arcs[i][j].length_cost = G.arcs[i][j].linenum;//将长度值赋给i到j的弧上
            G.arcs[j][i].length_cost = G.arcs[i][j].linenum;
            G.arcs[i][j].weight_cost = 2;//将加权值赋给i到j的弧上
            G.arcs[j][i].weight_cost = 2;
            G.arcs[i][j].linenum = Line[m].num;
            G.arcs[j][i].linenum = Line[m].num;
        }
    return 0;
}
