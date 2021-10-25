#include "map.h"

void Init(LineNode& Line, const char* a)//���ļ��е�վ̨��Ϣ��ȡ��Line�У������ߺ����ַ���ʾ
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

//��ÿ��վ������ֳ�ʼ��
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

//��ӡ���еĵ���·��
void PrintMGraph()
{
    int i, j;
    for (i = 0; i < Maxline; i++)
    {
        printf("����%d����: ", Line[i].num);
        for (j = 0; j < Line[i].stopnum; j++)
            printf("%s->", Line[i].Station[j]);
        printf("�ܵĽ����%d", Line[i].stopnum);
        printf("\n\n");
    }
    return;
}

//������ӡĳ����·������վ��
void PrintMGraph1(LineNode& Line)
{
    int j;
    printf("����%d����: ", Line.num);
    for (j = 0; j < Line.stopnum; j++)
        printf("%s->", Line.Station[j]);
    printf("�ܵĽ����%d", Line.stopnum);
    printf("\n\n");
}

//LocateVex���������潨ͼ�����е��õ�ʱ���������ҵ�v1��v2���ֱ���G�����е�λ�õġ�
int LocateVex(Graph G, char u[20])
{
    int i;
    for (i = 0; i < G.vexnum; i++)
        if (!strcmp(u, G.vexs[i].StaName))
            return i;
    if (i == G.vexnum)
        return -1;
}

//����ͼģ�ͽ����еĳ�ʼ�������ݷŵ�ͼ��ÿ���С�
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
            i = LocateVex(G, Line[m].Station[n]);//i��ʾ��G������������е�λ��
            j = LocateVex(G, Line[m].Station[n + 1]);	//j��ʾ��G������������е�λ��
            G.arcs[i][j].time_cost = 3;//��ʱ��ֵ����i��j�Ļ���
            G.arcs[j][i].time_cost = 3;
            G.arcs[i][j].length_cost = G.arcs[i][j].linenum;//������ֵ����i��j�Ļ���
            G.arcs[j][i].length_cost = G.arcs[i][j].linenum;
            G.arcs[i][j].weight_cost = 2;//����Ȩֵ����i��j�Ļ���
            G.arcs[j][i].weight_cost = 2;
            G.arcs[i][j].linenum = Line[m].num;
            G.arcs[j][i].linenum = Line[m].num;
        }
    return 0;
}
