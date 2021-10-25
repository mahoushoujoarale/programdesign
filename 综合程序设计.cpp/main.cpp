#include "search.h"

#define INFINITY 1e6
#define Maxlen 300
#define Maxline 7

typedef int int_matrix[Maxlen][Maxlen];
typedef double double_matrix[Maxlen][Maxlen];

int_matrix p;//�洢·��
double_matrix time_path;//�洢ʱ�����·��
double_matrix price_path;//�洢Ʊ����С·��
double_matrix weight_path;//�洢��Ȩ��С·��
//�����������Ͷ���
typedef struct
{
    int num;//������·,������
    double length;//������·���ܳ���
    int stopnum;//ÿ�˵�����������վ��
    char Station[Maxlen][20];//ÿ�˵���������վ��
}LineNode;//������·��Ϣ

typedef struct// ÿ������ŵ���Ϣ
{
    char StaName[20];
}VertexType;

typedef struct Arcell
{
    double time_cost;//ʱ�仨��
    double length_cost;//���Ȼ���
    double weight_cost;//��Ȩ����
    int linenum;
}Arcell, AdjMatrix[Maxlen][Maxlen];

typedef struct Graph
{
    AdjMatrix arcs;
    VertexType vexs[Maxlen];//����
    int vexnum;//վ����
}Graph;

Graph G;
LineNode Line[Maxline];
VertexType vexdata[Maxlen];

int main()
{
    system("color f4");
    int i;
    char a;
    Init(Line[0], "����1����.txt");
    Init(Line[1], "����2����.txt");
    Init(Line[2], "����3����.txt");
    Init(Line[3], "����4����.txt");
    Init(Line[4], "����6����.txt");
    Init(Line[5], "����7����.txt");
    Init(Line[6], "����8����.txt");
    InitS(Line);
loop:
    choose();
    scanf("%d", &i);
    a = getchar();
    system("cls");

    switch (i)
    {
    case 1:
        printf("*************��ӭ�����鿴�人������·��Ϣ����****************\n\n");
        printf("1:�鿴�人����ÿ��������·��Ϣ\n2:����������\n");
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
            printf("...............���س�������................\n\n");
            t = getchar();
            system("cls");
            goto loop;
            break;
        default:
            printf("�������!\n");
        }
        printf("����1�������������棬����2ֱ���˳�������ѯϵͳ\n");
        int a1;
        scanf("%d", &a1);
        switch (a1)
        {
        case 1:
        {
            char t1;
            t1 = getchar();
            printf("...............���س�������................\n\n");
            t1 = getchar();
            system("cls");
            goto loop;
            break;
        }
        case 2:
            break;
        default:
            printf("�������!");
        }
        break;
    loop1:
    case 2:
    {
        printf("\t*******��������ʱ����̲�ѯ*******\n\n");
        printf("1:��ѯ�������·�̼�����ʱ��\n2:�������˵�.\n");
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
            printf("...............���س������������ѯ����................\n\n");
            t2 = getchar();
            system("cls");
            goto loop;
            break;
        default:
            printf("�������!\n");
        }
        int b;
        scanf("%d", &b);
        switch (b)
        {
        case 3:
        {
            char t3;
            t3 = getchar();
            printf("...............���س������������ѯ����................\n\n");
            t3 = getchar();
            system("cls");
            goto loop1;
            break;
        }
        case 4:
        {
            char t4;
            t4 = getchar();
            printf("...............���س���������������������................\n\n");
            t4 = getchar();
            system("cls");
            goto loop;
            break;
        }

        default:
            printf("�������!\n");
            break;

        }

    }
    case 3:
        printf("\t********�����в�ѯ!лл��ʹ���人��������·�߲�ѯϵͳ*********\n");
        break;
    default:
        printf("�������!!\n");
        break;
    }
    return 0;
}

//�Լ�ʵ��һ��ceiling����
int ceiling(double a, int b) {
    return (a + b - 1) / b;
}

//���볤�ȼ���Ʊ��
int charge(double length) {
    double sum = 0;
    if (length <= 4) sum = 2;
    else if (length > 4 && length <= 12) sum = 2 + ceiling((length - 4), 4) * 1;    // ��ceiling����������ȡ��
    else if (length > 12 && length <= 24) sum = 4 + ceiling((length - 12), 6) * 1;
    else if (length > 24 && length <= 40) sum = 6 + ceiling((length - 24), 8) * 1;
    else if (length > 40 && length <= 50) sum = 8 + ceiling((length - 40), 10) * 1;
    else sum = 10 + ceiling((length - 50), 20) * 1;
    return sum;
}