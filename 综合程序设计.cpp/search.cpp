#include "search.h"

/* ��Dijkstra�㷨��������G��v0���㵽���ඥ��v�����·��P[i][v]�����Ȩ����time_path[v]��*/
/* P[i][v]��ֵΪǰ������±꣬time_path[i][v]��ʾv0��v�����·��֮�͡� */
void Dijkstra(Graph G, int_matrix* p, double_matrix* time_path)
{
    int v, w, k, i, s;
    double t, min;
    int final[Maxlen];  /* final[w]=1��ʾ��ö���v0��v�����·�� */
    for (i = 0; i < G.vexnum; i++) /* ��ʼ������ */
    {
        for (v = 0; v < G.vexnum; v++)
        {
            final[v] = 0; /* ȫ�������ʼ��Ϊδ֪���·��״̬ */
            (*time_path)[i][v] = G.arcs[i][v].time_cost;/* ����v0�������ߵĶ������Ȩֵ */
            (*p)[i][v] = -1; /* ��ʼ��·������pΪ-1 */
        }
        (*time_path)[i][i] = 0;/* v0��v��·��Ϊ0 */
        /* ��ʼ��ѭ����ÿ�����vo��ÿ��v��������·�� */
        for (v = 1; v < G.vexnum; v++)
        {
            min = INFINITY;  /* ��ǰ��֪��v0�������̾��� */
            for (w = 0; w < G.vexnum; w++)
            {
                if (!final[w] && (*time_path)[i][w] < min)
                {
                    k = w;
                    min = (*time_path)[i][w]; /* w������v0������� */
                }
            }
            final[k] = 1; /* ��Ŀǰ�ҵ�������Ķ�����Ϊ1 */
            for (w = 0; w < G.vexnum; w++) /* ������ǰ���·�������� */
            {
                s = (*p)[i][k];/*��ڵ����һ��·��*/
                if (s == -1) s = i;/*��һ���ҵ����·��ʱ��Ӧ��·��*/
                if ((G.arcs[k][s].linenum != G.arcs[k][w].linenum) && s != -1)
                    t = min + G.arcs[k][w].time_cost + 3.5;/*�������·����Ӧ·�߲�ͬ�����������ˣ�����ʱ��������3.5����*/
                else
                    t = min + G.arcs[k][w].time_cost;/*�������·����Ӧ·����ͬ��������δ���ˣ�����ʱ�䲻�ı�*/
                /* ˵���ҵ��˸��̵�·��������time_path[i][w]�� p[i][w]*/
                if (!final[w] && (t < (*time_path)[i][w]))
                {
                    (*time_path)[i][w] = t;
                    (*p)[i][w] = k;
                }
            }
        }
    }
}

void check(char p[20], int& m, int& n)//�ж���ʼվ���յ�վ�Ƿ�Ϊ����վ
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

//�ж���һ��վ��·���Ƿ����ı�
void transfer(int a, int b, int c)
{
    if (b != c && G.arcs[a][b].linenum != G.arcs[b][c].linenum)
        printf("(���ڸ�վ�³�������%d����)", G.arcs[b][c].linenum);
}

void Find()
{
    int i, j, k, a, b;
    char v1[20], v2[20];
    CreateMGraph(Line, vexdata, G);//��ʼ��ͼ
    Dijkstra(G, &p, &time_path);//��ʱ���·���㷨
    printf("\n**************·�߲�ѯ***************\n\n");
    int m1 = -1, m2 = -1, n1 = -1, n2 = -1;
    printf("��������Ҫ��ѯ����ʼվ��:");
loop:
    scanf("%s", v1);
    j = LocateVex(G, v1);
    if (j == -1)
    {
        printf("������Ĳ�ѯ�����������������!\n");
        goto loop;
    }
    else
    {
        check(v1, m1, n1);
        if (m1 >= 0 && n1 < 0)//v1��Ϊ����վ
        {
            printf("�㵱ǰ���ڵ�����·Ϊ����%d����\n\n", Line[m1].num);
        }
        else if (m1 >= 0 && n1 >= 0)
        {
            printf("�㵱ǰ����վ��Ϊ���˳�վ�����ڵ���%d���������%d�ߵĽ��㴦\n\n", Line[m1].num, Line[n1].num);
        }
    }

    printf("��������Ҫ��ѯ����վ��:");
loop1:
    scanf("%s", v2);
    i = LocateVex(G, v2);
    if (i == -1)
    {
        printf("������Ĳ�ѯ�յ���������������!\n");
        goto loop1;
    }
    else
    {
        check(v2, m2, n2);
        if (m2 >= 0 && n2 < 0)//v2��Ϊ����վ
        {
            printf("����Ҫ����վ���ڵ���%d����\n\n", Line[m2].num);
        }
        else if (m2 >= 0 && n2 >= 0)
        {
            printf("����Ҫ����վ��Ϊ���˳�վ�����ڵ���%d���������%d���ߵĽ��㴦\n\n", Line[m2].num, Line[n2].num);
        }
    }
    k = j;
    printf("��Ҫ��������ʱ�䵽���·��Ϊ:\n\n");
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
    printf("���õ����ʱ��Ϊ��");
    printf("%lf\n\n", time_path[i][j]);
}

void choose()
{
    printf("\t             ----------------------------------------------                      \n");
    printf("\t	               ��ӭ��ʹ���人��������·�߲�ѯϵͳ            		           \n");
    printf("\t             ----------------------------------------------                    \n\n");
    printf("\t             ******1.�鿴�人�ĵ�����·��Ϣ****************                      \n");
    printf("\t             ******2.���������ʱ���ѯ********************                      \n");
    printf("\t             ******3.�˳���ѯ******************************\n\n");
    printf("���������ѡ��:\n");
}

void chose()
{
    printf("***********3.������ѯ**************\n");
    printf("***********4.����������************\n");

    printf("���������ѡ��:\n");
}