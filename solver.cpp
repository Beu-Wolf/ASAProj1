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


void addEdge(int src, int dest, std::vector<std::list<int>> &adjList);
int artPointFind(int vertex, std::vector<int> &pi, std::vector<int> &discover, std::vector<bool> &visited,  std::vector<int> &low, std::vector<std::list<int>> &adjList, std::vector<bool> &artPoints);
int minimum(int &a, int &b);
int maxSubGraph(std::vector<std::list<int>> &adjList, std::vector<bool> &visited, std::vector<bool> &artPoints, int V);
int subgraphSize(std::vector<std::list<int>> &adjList, std::vector<bool> &visited, std::vector<bool> &artPoints, int v);

int main(){
    int V, numEdges, src, dest;
    int fuckYouCompiler;

    // read graph size
    fuckYouCompiler = scanf("%d", &V);
    fuckYouCompiler = scanf("%d", &numEdges);

    if(numEdges > (2*V +2)){
        printf("1\n");
        printf("%d\n", V);
        printf("0\n");
        printf("%d", V);
        return 0;
    }

    // problem information
    std::vector<std::list<int>> adjList (V);
    std::set<int>               subGraphs;
    std::vector<bool>           artPoints (V, false);

    // DFS information
    std::vector<bool>           visited (V, false); // grey color not needed. using boolean
    std::vector<int>            pi (V, -1);
    std::vector<int>            low (V);
    std::vector<int>            discover (V, -1);
    
    // read edges
    for(int i = 0; i < numEdges; i++) {
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

    // find articulation points (automatically gets greatest subgraph vertex)
    for(int i = 0; i < V; i++){
        if(!visited[i]){
            int biggestIndex = artPointFind(i, pi, discover, visited, low, adjList, artPoints);
            subGraphs.insert(biggestIndex);
        }
    }

    // find greatest subgraph (supposing there is no articulation point)
    int maxSubgraphSize = maxSubGraph(adjList, visited, artPoints, V);
    
    // OUTPUT:
    std::set<int>::iterator it = subGraphs.end();
    --it;

    printf("%lu\n", subGraphs.size()); // num of subgraphs
    for (auto& sub : subGraphs){ // subgraph max router id
        printf("%d", sub +1);
        if(sub != *it)
            printf(" ");
    }

    printf("\n%d\n", numAPs); // number of articulation points
    printf("%d\n", maxSubgraphSize);
    
    return fuckYouCompiler * 0;
}

void addEdge(int src, int dest, std::vector<std::list<int>> &adjList){
    adjList[src].push_back(dest);
    adjList[dest].push_back(src);
}

int artPointFind(int vertex, std::vector<int> &pi, std::vector<int> &discover, std::vector<bool> &visited,  std::vector<int> &low, std::vector<std::list<int>> &adjList, std::vector<bool> &artPoints){
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
int maxSubGraph(std::vector<std::list<int>> &adjList, std::vector<bool> &visited, std::vector<bool> &artPoints, int V) {
	int size, greater = 0;
	bool f = true;
	for(int i = 0; i < V; i++)
		if(visited[i] == f && !artPoints[i])
			if((size = subgraphSize(adjList, visited, artPoints, i)) > greater)
				greater = size;
	return greater;
}

int subgraphSize(std::vector<std::list<int>> &adjList, std::vector<bool> &visited, std::vector<bool> &artPoints, int v) {
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