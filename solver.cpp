#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <set>
#include <map>

/*NOTA IMPORTANTE -> Aprensentar vertices e sempre indice + 1*/

/*
DFS e encontrar subgrafos / pontos de articulacao
Remover ligacoes de e para esses vertices
DFS na arvore resultante e encontrar maior subgrafo
*/


int currTime = 0;
int numAPs = 0;

struct vFlags {
    bool artPoint = false;
    bool visited = false;
    bool subGraph = false;
    int pi = -1;
    int low;
    int discover = -1; 
};


void addEdge(int src, int dest, std::list<int> *adjList);
int artPointFind(int vertex, vFlags* vertexFlags ,std::list<int> *adjList);
int minimum(int &a, int &b);
int maxSubGraph(std::list<int> *adjList, vFlags* vertexFlags, unsigned int V);
int subgraphSize(std::list<int> *adjList, vFlags* vertexFlags , unsigned int v);

int main(){
    int src, dest, numSubs = 0;
    unsigned int V, numEdges;
    int fuckYouCompiler;

    // read graph size
    fuckYouCompiler = scanf("%d", &V);
    fuckYouCompiler = scanf("%d", &numEdges);   

    if(numEdges >= (V*(V-1)/2)){
        printf("1\n%d\n0\n%d\n", V, V);
        return 0;
    }

    // problem information
    //bool subGraphs[V] = {false};
    //bool artPoints[V] = {false};
    std::list<int> *adjList = new std::list<int>[V];

    // DFS information
    //int* discover = (int*)malloc(sizeof(int) * V);
    // int* pi = (int*)malloc(sizeof(int) * V);
    // int low[V];
    /*bool visited[V] = {false}; // grey color not needed. using boolean
    int discover[V];
    int pi[V];
    int* low = (int*)malloc(sizeof(int) * V);*/

    vFlags* vertexFlags = new vFlags[V];

    /*if(!low)
        return -1;

    // initialize data
    for(unsigned int i = 0; i < V; i++){ 
        pi[i] = discover[i] = -1;
    }*/
    
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
        if(!vertexFlags[i].visited){
            int biggestIndex = artPointFind(i, vertexFlags, adjList);
            vertexFlags[biggestIndex].subGraph = true;
            numSubs++;
        }
    }

    // find greatest subgraph (supposing there is no articulation point)
    int maxSubgraphSize = maxSubGraph(adjList, vertexFlags, V);
    
    // OUTPUT:
    printf("%d\n", numSubs); // num of subgraphs
    unsigned int i = 0;
    while(i < V){
        if(vertexFlags[i].subGraph == true){
            printf("%d", i + 1);
            i++;
            break;
        }
        i++;
    }

    while(i < V){
        if(vertexFlags[i].subGraph == true)
            printf(" %d", i+1);
        i++;
    }
    
    /*for (auto& sub : subGraphs){ // subgraph max router id
        printf("%d", sub +1);
        if(sub != *it)
            printf(" ");
    }*/

    printf("\n%d\n", numAPs); // number of articulation points
    printf("%d\n", maxSubgraphSize);
    
    // free(discover);
    // free(pi);
    //free(low);
    delete [] adjList;
    delete [] vertexFlags;

    return fuckYouCompiler * 0;
}

void addEdge(int src, int dest, std::list<int> *adjList){
    adjList[src].push_back(dest);
    adjList[dest].push_back(src);
}

int artPointFind(int vertex, vFlags* vertexFlags ,std::list<int> *adjList){
    int currBig = vertex;
    int subBig;
    int numChildren = 0;
    vertexFlags[vertex].visited = true;
    
    vertexFlags[vertex].discover = vertexFlags[vertex].low = currTime++;

    for (auto &adj : adjList[vertex]){
        if (adj > currBig)
            currBig = adj;
        

        if(vertexFlags[adj].visited == false){
            numChildren++;
            vertexFlags[adj].pi = vertex;
            subBig = artPointFind(adj, vertexFlags, adjList);

            if (subBig > currBig)
                currBig = subBig; 
            
            vertexFlags[vertex].low = minimum(vertexFlags[vertex].low, vertexFlags[adj].low);
            if (vertexFlags[vertex].pi == -1 && numChildren > 1){
                if(vertexFlags[vertex].artPoint == false){
                    vertexFlags[vertex].artPoint = true;
                    numAPs++;
                }
            }
            if (vertexFlags[vertex].pi != -1 && (vertexFlags[adj].low >= vertexFlags[vertex].discover)){
                if(vertexFlags[vertex].artPoint == false){
                    vertexFlags[vertex].artPoint = true;
                    numAPs++;
                }
            }
        } else if (vertexFlags[vertex].pi != adj){
            vertexFlags[vertex].low = minimum(vertexFlags[vertex].low, vertexFlags[adj].discover);
        }
    }
    return currBig;
}

// return maximum subgraph size
// using DFS iteration
// time and pi not needed 
int maxSubGraph(std::list<int> *adjList, vFlags* vertexFlags, unsigned int V){
	int size, greater = 0;
	bool f = true;
	for(unsigned int i = 0; i < V; i++)
		if(vertexFlags[i].visited == f && !vertexFlags[i].artPoint)
			if((size = subgraphSize(adjList, vertexFlags, i)) > greater)
				greater = size;
	return greater;
}

int subgraphSize(std::list<int> *adjList, vFlags* vertexFlags , unsigned int v){
	int size = 1;
	bool t = false, f = true;
	vertexFlags[v].visited = t;
	for(auto &adj : adjList[v])
		if(vertexFlags[adj].visited == f && !vertexFlags[adj].artPoint)
			size += subgraphSize(adjList, vertexFlags, adj);
	return size;
}

int minimum(int &a, int &b){
    if (a < b)
        return a;
    return b;
}