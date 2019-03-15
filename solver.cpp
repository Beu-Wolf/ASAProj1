#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <set>
#include <forward_list>

/*NOTA IMPORTANTE -> Aprensentar vertices e sempre indice + 1*/

/*
DFS e encontrar subgrafos / pontos de articulacao
Remover ligacoes de e para esses vertices
DFS na arvore resultante e encontrar maior subgrafo
*/


int currTime = 0;
int numAPs = 0;


void addEdge(int src, int dest, std::list<int> *adjList);
int artPointFind(int vertex, int *pi, int *discover, bool *visited,  int *low, std::list<int> *adjList, bool *artPoints);
int minimum(int &a, int &b);
int maxSubGraph(std::list<int> *adjList, bool *visited, bool *artPoints, unsigned int V);
int subgraphSize(std::list<int> *adjList, bool *visited, bool *artPoints, unsigned int v);

int main(){
    int src, dest, numSubs = 0;
    int fuckYouCompiler;
    unsigned int V, numEdges;

    // read graph size
    fuckYouCompiler = scanf("%d", &V);
    fuckYouCompiler = scanf("%d", &numEdges);

    if(numEdges == (V*(V-1)/2)){
        printf("1\n%d\n0\n%d\n", V, V);
        return 0;
    }

    // problem information
    std::forward_list<int> subGraphs;
    bool artPoints[V] = {false};
    std::list<int> *adjList = new std::list<int>[V];

    // DFS information
    //int* discover = (int*)malloc(sizeof(int) * V);
    // int* pi = (int*)malloc(sizeof(int) * V);
    // int low[V];
    bool visited[V] = {false}; // grey color not needed. using boolean
    int discover[V];
    int pi[V];
    int* low = (int*)malloc(sizeof(int) * V);
    if(!low)
        return -1;

    // initialize data
    for(unsigned int i = 0; i < V; i++){ 
        pi[i] = discover[i] = -1;
    }
    
    // read edges
    for(unsigned int i = 0; i < numEdges; i++) {
        fuckYouCompiler = scanf("%d %d", &src, &dest);
        addEdge(--src, --dest, adjList);
    }


    // DBG: print edges
    /*for (auto& lst : adjList){
        for(auto node : lst){
            std::cout << " to: " << node + 1;
        }
        std::cout << "\n";
    }*/

    // find articulation points (gets greatest subgraph vertex)
    for(unsigned int i = 0; i < V; i++){
        if(!visited[i]){
            int biggestIndex = artPointFind(i, pi, discover, visited, low, adjList, artPoints);
            subGraphs.push_front(biggestIndex);
            numSubs++;
        }
    }

    // find greatest subgraph (supposing there is no articulation point)
    int maxSubgraphSize = maxSubGraph(adjList, visited, artPoints, V);
    
    // OUTPUT:
    printf("%d\n", numSubs); // num of subgraphs
    subGraphs.sort();
    
    std::forward_list<int>::iterator it = subGraphs.begin();

    printf("%d", *it + 1);
    it++;

    while(it != subGraphs.end()){
        
        printf(" %d", *it + 1);
        it++;
    }


    printf("\n%d\n", numAPs); // number of articulation points
    printf("%d\n", maxSubgraphSize);
    
    free(low);
    delete [] adjList;

    return fuckYouCompiler * 0;
}

void addEdge(int src, int dest, std::list<int> *adjList){
    adjList[src].push_back(dest);
    adjList[dest].push_back(src);
}

int artPointFind(int vertex, int *pi, int *discover, bool *visited,  int *low, std::list<int> *adjList, bool *artPoints){
    int currBig = vertex;
    int subBig;
    int numChildren = 0;
    visited[vertex] = true;
    
    discover[vertex] = low[vertex] = currTime++;

    for (auto &adj : adjList[vertex]){
        if (adj > currBig)
            currBig = adj;
        

        if(visited[adj] == false){
            numChildren++;
            pi[adj] = vertex;
            subBig = artPointFind(adj, pi, discover, visited, low, adjList, artPoints);

            if (subBig > currBig)
                currBig = subBig; 
            
            low[vertex] = minimum(low[vertex], low[adj]);
            if (pi[vertex] == -1 && numChildren > 1){
                if(artPoints[vertex] == false){
                    artPoints[vertex] = true;
                    numAPs++;
                }
            }
            if (pi[vertex] != -1 && (low[adj] >= discover[vertex])){
                if(artPoints[vertex] == false){
                    artPoints[vertex] = true;
                    numAPs++;
                }
            }
        } else if (pi[vertex] != adj){
            low[vertex] = minimum(low[vertex], discover[adj]);
        }
    }
    return currBig;
}

// return maximum subgraph size
// using DFS iteration
// time and pi not needed 
int maxSubGraph(std::list<int> *adjList, bool *visited, bool *artPoints, unsigned int V){
	int size, greater = 0;
	bool f = true;
	for(unsigned int i = 0; i < V; i++)
		if(visited[i] == f && !artPoints[i])
			if((size = subgraphSize(adjList, visited, artPoints, i)) > greater)
				greater = size;
	return greater;
}

int subgraphSize(std::list<int> *adjList, bool *visited, bool *artPoints, unsigned int v){
	int size = 1;
	bool t = false, f = true;
	visited[v] = t;
	for(auto &adj : adjList[v])
		if(visited[adj] == f && !artPoints[adj])
			size += subgraphSize(adjList, visited, artPoints, adj);
	return size;
}

int minimum(int &a, int &b){
    if (a < b)
        return a;
    return b;
}