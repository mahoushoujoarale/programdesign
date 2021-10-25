#pragma once

#include "map.h"

void Dijkstra(Graph G, int_matrix* p, double_matrix* time_path);
void check(char p[20], int& m, int& n);//判断起始站和终点站是否为换乘站
void transfer(int a, int b, int c);
void Find();
void choose();
void chose();