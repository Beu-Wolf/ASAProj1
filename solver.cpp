#include <iostream>
#include <vector>
#include <string>
#include <list>

/*NOTA IMPORTANTE -> Aprensentar vertices e sempre indice + 1*/


void addEdge(int src, int dest, std::vector<std::list<int>> &adjList);


int main(){

    int V, numEdges, src, dest;
    int numChildren = 0;
    int time = 0;

    int biggestVertex = 0;
    int size = 0;

    std::cin >> V;


    //vectors needed for DFS / tarjan
    std::vector<int> pi (V);
    std::vector<int> discover (V);
    std::vector<bool> visited (V, false);
    std::vector<int> low (V);
    std::vector<std::list<int>> adjList (V);
    

    

    std::cin >> numEdges;

    int i = 0;
    while ( i < numEdges){ // code to add new edges
        std::cin >> src >> dest;
        src--;
        dest--;
        //std::cout << "Num Vertices: " << V << " Num Eges: " << numEdges << " src: " << src << " dest: " << dest << std::endl;
        
        addEdge(src, dest, adjList);
        i++;
    }


    for (auto& lst : adjList){
        for(auto node : lst){
            std::cout << " to: " << node + 1;
        }
        std::cout << "\n";
    }

    return 0;
}

void addEdge(int src, int dest, std::vector<std::list<int>> &adjList){
    adjList[src].push_back(dest);
    adjList[dest].push_back(src);
}