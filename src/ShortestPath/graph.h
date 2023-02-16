#pragma once

#define MAX_VERTICES 100
#define INF 1000000 /* 무한대 (연결이 없는 경우) */
#define INT_MAX 7

typedef struct GraphType
{
	int n; // 정점의 개수
	int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;
