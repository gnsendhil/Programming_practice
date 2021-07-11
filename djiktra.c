#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#define INFINITY 0x99999999

unsigned int **AdjList;
int *distance_array;
char *visited_array;
void print_AdjList(int N);
void add_vertex(int Ni, int Nj, int C);
void print_visited_arr(int N);
void find_shortest_path(int N, int start_node);
void print_distance_arr(int N);

int main()
{
    int num,N, R, Ni, Nj, C;
    scanf("%d", &num);
    scanf("%d", &R);

    N = num + 1;

    AdjList = (unsigned int **)calloc(N, sizeof(int *));
    distance_array = (int *)malloc(N * sizeof(int));
    visited_array = (char *)calloc(N, sizeof(char));
    memset(distance_array, 0X99, (N*sizeof(int)));

    for(int i=0; i<N; i++)
    {
        AdjList[i] = (unsigned int *)calloc(N, sizeof(int));
        memset(AdjList[i], 0X99, (N*sizeof(int)));
    }

    for(int i =0; i<R; i++)
    {
        scanf("%d", &Ni);
        scanf("%d", &Nj);
        scanf("%d", &C);
        add_vertex(Ni, Nj, C);
    }

    //print_AdjList(N);
    //print_distance_arr(num);
    find_shortest_path(num, 1);
    //print_visited_arr(num);
    //print_queue(queue_index);
    //print_AdjList(N);

    return 0;
}

void add_vertex(int Ni, int Nj, int C)
{
    AdjList[Ni][Nj] = C;
    AdjList[Nj][Ni] = C;
}

void find_shortest_path(int N, int start_node)
{
    for(int i=1; i<=N; i++)
    {
        distance_array[i] = AdjList[start_node][i];
        visited_array[i] = 0;
    }
    distance_array[1] = 0;
    visited_array[1] = 1;
    unsigned int count =1, min_dist, next_node;
    //printf("Next Node: %d\n", start_node);
    //print_visited_arr(N);
    //print_distance_arr(N);
    while(count <= N)
    {
        min_dist = INFINITY;
        for(int i=1; i<=N; i++)
        {
            if((distance_array[i] < min_dist) && (!visited_array[i]))
            {
                min_dist = distance_array[i];
                next_node = i;
            }
        }
        //printf("Next Node: %d\n", next_node);
        visited_array[next_node] = 1;

        for(int i=1; i<=N; i++)
        {
            if(!visited_array[i])
            {
                unsigned int temp_cost;
                //printf("index:%d min_dist:%d cost:%u\n", i, min_dist, AdjList[next_node][i]);
                if (AdjList[next_node][i] < min_dist)
                {
                    temp_cost = 0;
                }
                else
                {
                    temp_cost = AdjList[next_node][i] - min_dist;
                }
                if ((temp_cost + min_dist) < (unsigned int)distance_array[i])
                {
                    distance_array[i] = temp_cost + min_dist;
                    //printf("updated\n");
                }
            }
        }
        //print_visited_arr(N);
        //print_distance_arr(N);
        count++;
    }

    if(distance_array[N] == 0x99999999)
        printf("NOT POSSIBLE");
    else
        printf("%d", distance_array[N]);
}

void print_AdjList(int N)
{
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
            {
                printf("%u ",AdjList[i][j]);
            }
        printf("\n");
    }
}

void print_distance_arr(int N)
{
    for(int i=0; i<=N; i++){
        printf("%u ", distance_array[i]);
    }
    printf("\n");
}

void print_visited_arr(int N)
{
    for(int i=0; i<=N; i++){
        printf("%u ", visited_array[i]);
    }
    printf("\n");
}