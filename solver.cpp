#include <iostream>
#include <vector>
#include <string>

int main(){

    int V, numEdges, src, dest;

    std::cin >> V;
    /*vectors needed for DFS
    std::vector<std::string> color (V, "White");
    std::vector<int> pi (V, NULL);
    std::vector<int> discover (V, NULL);
    std::vector<int> closed (V, NULL);
    std::vector<bool> visited (V, false);
    std::vector<int> low (V, NULL); 
    */

    /*vector needed for trajan 
    std::vector<int> low (V, NULL);
    */

    std::cin >> numEdges;

    int i = 0;
    while ( i < numEdges){ // code to add new edges
        std::cin >> src >> dest;
        std::cout << "Num Vertices: " << V << " Num Eges: " << numEdges << " src: " << src << " dest: " << dest << std::endl;
        // add Edge(src, dest)
        i++;
    }
    return 0;
}