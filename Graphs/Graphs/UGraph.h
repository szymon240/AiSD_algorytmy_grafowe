#pragma once
#include <iostream>
#include "Test.h"

class UGraph
{
public:
	UGraph(double _dens, int _vertexes);
	~UGraph();
	
	double density;
	int vertex_num;
	int** adj_matrix;
	int* visited;
	//int* unvisited;
	std::vector<std::vector<int>> inc_list;
	Vertex* vertexes_matrix;

	void generateRandomEdges();

	//aparatura testowa
	void displayAdjMatrix();

	void displayIncList();

	int adjprimTreeFinder();

	//tree fiders and reset utility
	int incprimTreeFinder();
	void manualAdjMatrix();
	void resetForFinding();

};

UGraph::UGraph(double _dens, int _vertexes)
{
	density = _dens;
	vertex_num = _vertexes;
	adj_matrix = new int* [_vertexes];
	visited = new int[_vertexes];
	//unvisited = new int[_vertexes];
	for (int i = 0; i < _vertexes; i++)
	{
		visited[i] = 0;
		//unvisited[i] = 1;
		adj_matrix[i] = new int[_vertexes];

		for (int j = 0; j < _vertexes; j++)
		{
			adj_matrix[i][j] = 0;
		}
	}

	vertexes_matrix = new Vertex[_vertexes];
	inc_list = std::vector<std::vector<int>>(vertex_num);

}

UGraph::~UGraph()
{
}

void UGraph::generateRandomEdges()
{
	std::srand(time(NULL));
	double random;
	for (int i = 0; i < vertex_num; i++)
	{
		for (int j = i + 1; j < vertex_num; j++)
		{
			random = ((double)rand() / (RAND_MAX));
			//std::cout << random << std::endl;
			if (random < density)
			{
				int _weight = (rand() % 1000) + 1;
				adj_matrix[i][j] = _weight;
				adj_matrix[j][i] = _weight;
			}
		}
	}
	//displayAdjMatrix();
	int sum;
	for (int i = 0; i < vertex_num; i++)
	{
		sum = 0;
		for (int j = i + 1; j < vertex_num; j++)
		{
			sum += adj_matrix[i][j];
		}

		if (sum == 0)
		{
			int random_index = (rand() % vertex_num);
			while (random_index != i)
			{
				random_index = (rand() % vertex_num);
			}
			adj_matrix[i][random_index] = (rand() % 1000) + 1;
		}
	}


	for (int i = 0; i < vertex_num; i++)
	{
		for (int j = i + 1; j < vertex_num; j++)
		{
			if (adj_matrix[i][j] != 0)
			{
				inc_list[i].push_back(j);
				inc_list[j].push_back(i);
			}
		}

	}


}

void UGraph::displayAdjMatrix()
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

void UGraph::displayIncList()
{
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
}

int UGraph::adjprimTreeFinder()
{
	int result = 0;
	visited[0] = 1;
	int temputil;
	int tempvert = -1;
	for (int i = 0; i < vertex_num - 1; i++)
	{
		temputil = 1001;
		for (int j = 0; j < vertex_num; j++)
		{
			if (visited[j] == 1)
			{
				for (int k = 0; k < vertex_num; k++)
				{
					if (adj_matrix[j][k] != 0 && visited[k] == 0 && adj_matrix[j][k] < temputil)
					{
						temputil = adj_matrix[j][k];
						tempvert = k;
					}
				}
			}
		}
		visited[tempvert] = 1;
		result += temputil;
	}

	return result;
}

int UGraph::incprimTreeFinder()
{
	int result = 0;
	visited[0] = 1;
	int temputil;
	int tempvert = -1;
	for (int i = 0; i < vertex_num - 1; i++)
	{
		temputil = 1001;
		for (int j = 0; j < vertex_num; j++)
		{
			if (visited[j] == 1)
			{
				for (int k = 0; k < inc_list[j].size(); k++)
				{
					if (visited[inc_list[j][k]] == 0 && adj_matrix[j][inc_list[j][k]] < temputil)
					{
						temputil = adj_matrix[j][inc_list[j][k]];
						tempvert = inc_list[j][k];
					}
				}
			}
		}
		visited[tempvert] = 1;
		result += temputil;
	}

	return result;
}

void UGraph::manualAdjMatrix()
{
	std::cout << "Macierz sasiedztwa: \n";
	for (int i = 0; i < vertex_num; i++)
	{
		for (int j = 0; j < vertex_num; j++)
		{
			std::cin >> adj_matrix[i][j];
		}
	}

	for (int i = 0; i < vertex_num; i++)
	{
		for (int j = i + 1; j < vertex_num; j++)
		{
			if (adj_matrix[i][j] != 0)
			{
				inc_list[i].push_back(j);
				inc_list[j].push_back(i);
			}
		}

	}
}

void UGraph::resetForFinding()
{
	for (int i = 0; i < vertex_num; i++)
	{
		visited[i] = 0;
	}
}
