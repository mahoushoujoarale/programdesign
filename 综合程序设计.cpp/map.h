#pragma once

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#include<limits.h>
#include<windows.h>



void Init(LineNode& Line, const char* a);//将文件中的站台信息读取到Line中，地铁线号用字符表示
void Init(LineNode& Line, const char* a);//将文件中的站台信息读取到Line中，地铁线号用字符表示
void InitS(LineNode* L);
void PrintMGraph();
void PrintMGraph1(LineNode& Line);
int LocateVex(Graph G, char u[20]);
int CreateMGraph(LineNode* Line, VertexType* vexdata, Graph& G);