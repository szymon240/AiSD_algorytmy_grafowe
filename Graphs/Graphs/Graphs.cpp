#include "Test.h"
#include "UGraph.h"

int main()
{
    //dagTopologicSort();
    //UGraph* test_graph = new UGraph(0.3, 10);
    //test_graph->generateRandomEdges();
    //test_graph->displayAdjMatrix();
    //std::cout << std::endl;
    //test_graph->displayIncList();
    //std::cout << "\n" << test_graph->inc_list[0].size();
    dagTopologicSort();
    graphTreeFinder();

    return 0;
}