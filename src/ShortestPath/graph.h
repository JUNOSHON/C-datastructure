#pragma once

#define MAX_VERTICES 100
#define INF 1000000 /* ���Ѵ� (������ ���� ���) */
#define INT_MAX 7

typedef struct GraphType
{
	int n; // ������ ����
	int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;
