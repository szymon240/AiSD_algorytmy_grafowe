#include "Vertex.h"
#include <vector>

class DGraph
{
public:
	DGraph(float _dens, unsigned long int _vertexes);
	~DGraph();

	int sorting_index;
	float density;
	unsigned long int vertex_num;
	unsigned long int edges_num;
	int** adj_matrix;
	std::vector<std::vector<int>> inc_list;
	Vertex* vertexes_matrix;

	int* sorting_matrix;

	bool detectCycles(int out, int in);
	
	void generateRandomEdges();

	//sorts
	void adjMatrixSort();;
	void incListSort();

	//sorts funkcje utility
	void adjMatrixdetectRoute(int v);
	
	void incListdetectRoute(int v);

	//Aparatura pomiarowa

	void displayAdjMatrix();

	void manualAdjMatrix();

	void displaySortingMatrix();

	void displayIncList();

	DGraph();

};

DGraph::DGraph(float _dens, unsigned long int _vertexes)
{
	density = _dens;
	vertex_num = _vertexes;
	edges_num = (_dens * _vertexes * (_vertexes - 1)) / 2;
	adj_matrix = new int*[_vertexes];
	for (int i = 0; i < _vertexes; i++)
	{
		adj_matrix[i] = new int[_vertexes];

		for (int j = 0; j < _vertexes; j++)
		{
			adj_matrix[i][j] = 0;
		}
	}

	vertexes_matrix = new Vertex[_vertexes];
	sorting_matrix = new int[_vertexes];
	sorting_index = vertex_num - 1;
	inc_list = std::vector<std::vector<int>>(vertex_num);
	
}

DGraph::~DGraph()
{
	for (int i = 0; i < vertex_num; i++)
	{
		delete[] adj_matrix[i];
	}
	delete[] adj_matrix;
	delete[] vertexes_matrix;
	delete[] sorting_matrix;
	for (int i = 0; i < vertex_num; i++)
	{
		inc_list[i].clear();
	}
	inc_list.clear();
}

void DGraph::generateRandomEdges()
{
	std::srand(time(NULL));
	double random;
	for (int i = 0; i < vertex_num; i++)
	{
		for (int j = i + 1; j < vertex_num; j++)
		{
			random = ((double)rand() / (RAND_MAX));
			if (random < density)
			{
				adj_matrix[i][j] = 1;
			}
		}
	}

	//int sum;
	for (int i = 0; i < vertex_num; i++)
	{
		//sum = 0;
		/*for (int j = 0; j < vertex_num; j++)
		{
			if (adj_matrix[i][j] == 1)
			{
				sum++;
			}
		}*/
		//inc_list[i] = std::vector<int>(sum);
		for (int j = 0; j < vertex_num; j++)
		{
			if (adj_matrix[i][j] == 1)
			{
				inc_list[i].push_back(j);
			}
		}

	}


}

void DGraph::adjMatrixSort()
{
	for (int i = 0; i < vertex_num; i++)
	{
		if (vertexes_matrix[i].visited == false)
		{
			adjMatrixdetectRoute(i);
			/*if (i == 3)
			{
				std::cout << "Przeszlo\n";
				displaySortingMatrix();
				std::cout << "\n";
			}*/
		}
	}

	sorting_index = vertex_num - 1;
}

void DGraph::incListSort()
{
	for (int i = 0; i < vertex_num; i++)
	{
		if (vertexes_matrix[i].visited == false)
		{
			incListdetectRoute(i);
			/*if (i == 3)
			{
				std::cout << "Przeszlo\n";
				displaySortingMatrix();
				std::cout << "\n";
			}*/
		}
	}

	sorting_index = vertex_num - 1;
}

void DGraph::adjMatrixdetectRoute(int v)
{
	for (int i = 0; i < vertex_num; i++)
	{
		if (adj_matrix[v][i] == 1 && vertexes_matrix[i].visited == false)
		{
			adjMatrixdetectRoute(i);
		}
	}
	sorting_matrix[sorting_index] = v + 1;
	sorting_index--;
	vertexes_matrix[v].visited = true;
}

inline void DGraph::incListdetectRoute(int v)
{
	for (int i = 0; i < inc_list[v].size(); i++)
	{
		if (vertexes_matrix[inc_list[v][i]].visited == false)
		{
			incListdetectRoute(inc_list[v][i]);
		}
	}

	sorting_matrix[sorting_index] = v + 1;
	sorting_index--;
	vertexes_matrix[v].visited = true;
}

void DGraph::displayAdjMatrix()
{
	for (int i = 0; i < vertex_num; i++)
	{
		for (int j = 0; j < vertex_num; j++)
		{
			std::cout << adj_matrix[i][j] << " ";
		}
		std::cout << "\n";
	}
}

void DGraph::manualAdjMatrix()
{
	std::cout << "Macierz sasiedztwa: \n";
	for (int i = 0; i < vertex_num; i++)
	{
		for (int j = 0; j < vertex_num; j++)
		{
			std::cin >> adj_matrix[i][j];
		}
	}
}

void DGraph::displaySortingMatrix()
{
	for (int i = 0; i < vertex_num; i++)
	{
		std::cout << sorting_matrix[i] << " ";
	}
}

void DGraph::displayIncList()
{
	for (int i = 0; i < vertex_num; i++)
	{
		std::cout << i + 1 << "-> { ";
		for (int j = 0; j < inc_list[i].size(); j++)
		{
			std::cout << inc_list[i][j] + 1 << " ";
		}
		std::cout << "}\n";
	}
}

DGraph::DGraph()
{
	std::cout << "Podaj ilosc wierzcholkow: ";
	std::cin >> vertex_num;
	std::cout << "Podaj gestosc: ";
	std::cin >> density;
	edges_num = (density * vertex_num * (vertex_num - 1)) / 2;
	adj_matrix = new int* [vertex_num];
	for (int i = 0; i < vertex_num; i++)
	{
		adj_matrix[i] = new int[vertex_num];
	}
	vertexes_matrix = new Vertex[vertex_num];
	sorting_matrix = new int[vertex_num];
	sorting_index = 0;
	manualAdjMatrix();
}

bool DGraph::detectCycles(int out, int in)
{
	if (adj_matrix[in][out] == 1)
	{
		return false;
	}

	bool result = true;
	for (int i = 0; i < vertex_num; i++)
	{
		if (adj_matrix[in][i] == 1)
		{
			result = detectCycles(out, i);
		}
		if (!result)
		{
			return result;
		}
		
	}
	return result;
}