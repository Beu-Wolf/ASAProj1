#include <iostream>
#include <list>
#include <forward_list>

void addEdge(int src, int dest, std::list<int> *adjList);
void artPointFind(int vertex, int *pi, int *discover, bool *visited,  int *low, std::list<int> *adjList, bool *artPoints);
int minimum(int &a, int &b);
int maxSubGraph(std::list<int> *adjList, bool *visited, bool *artPoints, unsigned int V);
int subgraphSize(std::list<int> *adjList, bool *visited, bool *artPoints, unsigned int v);

// global variables for Tarjan algorithm
// other variables must be initialized after reading input
int currTime = 0;
int numAPs = 0;



int main(){
    int src, dest, numSubs = 0;
    unsigned int V, numEdges;

    // read graph size
    scanf("%d", &V);
    scanf("%d", &numEdges);

    // graph theory: fully connected graph. impossible to have access points
    if(numEdges == (V*(V-1)/2)){
        printf("1\n%d\n0\n%d\n", V, V);
        return 0;
    }

    // problem information
    std::list<int> *adjList = new std::list<int>[V]; // graph itself
    std::forward_list<int> subGraphs; // storing greatest subgraph index
    bool artPoints[V] = {false}; // array to check if vertex is AP using O(1)

    // DFS information
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
        scanf("%d %d", &src, &dest);
        addEdge(--src, --dest, adjList);
    }

    // find articulation points (gets greatest subgraph vertices)
    unsigned int u = V-1;
    while(u >= 0){
        if(!visited[u]){
            //int biggestIndex = 
            artPointFind(u, pi, discover, visited, low, adjList, artPoints);
            subGraphs.push_front(u);
            numSubs++;
        }
        if(u == 0)
            break;
        u--;
    }

    // find greatest subgraph (supposing there is no articulation point)
    int maxSubgraphSize = maxSubGraph(adjList, visited, artPoints, V);
    
    // number of subgraphs
    printf("%d\n", numSubs);

    // subgraphs max vertices
    std::forward_list<int>::iterator it = subGraphs.begin();

    printf("%d", *it + 1);
    it++;

    while(it != subGraphs.end()){
        
        printf(" %d", *it + 1);
        it++;
    }

    // number of articulation points
    printf("\n%d\n", numAPs); 

    // max subgraph size
    printf("%d\n", maxSubgraphSize);
    
    free(low);
    delete [] adjList;

    return 0;
}


// tarjan algprithm recursive function
void artPointFind(int vertex, int *pi, int *discover, bool *visited,  int *low, std::list<int> *adjList, bool *artPoints){
    int numChildren = 0;

    visited[vertex] = true;
    discover[vertex] = low[vertex] = currTime++;

    for (auto &adj : adjList[vertex]){
        
        if(visited[adj] == false){
            numChildren++;
            pi[adj] = vertex;
            artPointFind(adj, pi, discover, visited, low, adjList, artPoints);
            
            low[vertex] = minimum(low[vertex], low[adj]);

	    // root vertex AP case
	    // checking if AP was already found
            if (pi[vertex] == -1 && numChildren > 1){
                if(artPoints[vertex] == false){
                    artPoints[vertex] = true;
                    numAPs++;
                }
            }

	    // other vertices AP case
	    // checking if AP was already found
            if (pi[vertex] != -1 && (low[adj] >= discover[vertex])){
                if(artPoints[vertex] == false){
                    artPoints[vertex] = true;
                    numAPs++;
                }
            }
        } else if (pi[vertex] != adj){ // if visited and not parent vertex
            low[vertex] = minimum(low[vertex], discover[adj]);
        }
    }

    // greatest 
}

// find max subgraph size, using DFS (time and pi not needed to this goal)
int maxSubGraph(std::list<int> *adjList, bool *visited, bool *artPoints, unsigned int V){
	int size, greater = 0;

	// at this point all vertices are visited. using this variable to switch bool
	// and maintain the algorithml's logic
	bool f = true;
	for(unsigned int i = 0; i < V; i++)
		if(visited[i] == f && !artPoints[i])
			if((size = subgraphSize(adjList, visited, artPoints, i)) > greater)
				greater = size;
	return greater;
}

// recursive function for maxSubGraph
int subgraphSize(std::list<int> *adjList, bool *visited, bool *artPoints, unsigned int v){
	int size = 1;
	bool t = false, f = true;
	visited[v] = t;
	for(auto &adj : adjList[v])
		if(visited[adj] == f && !artPoints[adj])
			size += subgraphSize(adjList, visited, artPoints, adj);
	return size;
}

// non directed graph: saving edges on both vertices
void addEdge(int src, int dest, std::list<int> *adjList){
    adjList[src].push_back(dest);
    adjList[dest].push_back(src);
}

int minimum(int &a, int &b){
    return (a < b) ? a : b;
}
