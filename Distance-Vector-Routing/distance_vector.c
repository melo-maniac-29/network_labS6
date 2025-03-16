#include <stdio.h>
#include <stdlib.h>

struct node{
	unsigned dist[20];
	unsigned from[20];
}rt[10];

int main()
{
	int cost_met[20][20];
	int nodes, i, j, k, count = 0;

	printf("Enter the no of Nodes : ");
	scanf("%d", &nodes);

	printf("\n\nEnter the cost metrics : ");
	for(int i = 0 ; i < nodes; i++)
	{
		for(int j = 0 ; j < nodes; j++)
		{
			scanf("%d", &cost_met[i][j]);

			cost_met[i][i] = 0;

			rt[i].dist[j] = cost_met[i][j];
			rt[i].from[j] = j;
		}
	}


	for(int i = 0 ; i < nodes ; i++)
		{
			for(int j = 0 ; j < nodes ; j++)
			{
				for(int k = 0 ; k < nodes ; k++)
				{
					if(rt[i].dist[j] > cost_met[i][k] + rt[k].dist[j])
					{
						rt[i].dist[j] = rt[i].dist[k] + rt[k].dist[j];
						rt[i].from[j] = k;
					}
				}
			}
		}



	for(int i = 0 ; i < nodes ; i++)
	{
		printf("\n\nFor Router %d", i+1);
		for (int j = 0; j < nodes; ++j)
		{
			printf("\nnodes %d via %d distance %d", j+1, rt[i].from[j]+1, rt[i].dist[j]);
		}
	}
	
	return 0;
}

//output

Enter the no of Nodes : 3


Enter the cost metrics : 0 2 7
2 0 1
7 1 0


For Router 1
nodes 1 via 1 distance 0
nodes 2 via 2 distance 2
nodes 3 via 2 distance 3

For Router 2
nodes 1 via 1 distance 2
nodes 2 via 2 distance 0
nodes 3 via 3 distance 1

For Router 3
nodes 1 via 2 distance 3
nodes 2 via 2 distance 1
nodes 3 via 3 distance 0%
