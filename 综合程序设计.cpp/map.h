#pragma once

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#include<limits.h>
#include<windows.h>



void Init(LineNode& Line, const char* a);//���ļ��е�վ̨��Ϣ��ȡ��Line�У������ߺ����ַ���ʾ
void Init(LineNode& Line, const char* a);//���ļ��е�վ̨��Ϣ��ȡ��Line�У������ߺ����ַ���ʾ
void InitS(LineNode* L);
void PrintMGraph();
void PrintMGraph1(LineNode& Line);
int LocateVex(Graph G, char u[20]);
int CreateMGraph(LineNode* Line, VertexType* vexdata, Graph& G);