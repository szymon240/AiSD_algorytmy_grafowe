#pragma once
#include <chrono>
#include <iostream>
#include <string>
#include <fstream>
#include "DGraph.h"
#include "UGraph.h"

void dagTopologicSort()
{
	std::cout << "--------TESTY SORTOWANIA TOPOLOGICZNEGO--------\n\n";
	int down_lim, up_lim, step;
	std::cout << "Podaj dolna granice testow: ";
	std::cin >> down_lim;
	std::cout << "Podaj gorna granice testow (MAX 7K przy dobrych wiatrach. #nie probuj): ";
	std::cin >> up_lim;
	std::cout << "Podaj krok wykonywania testow: ";
	std::cin >> step;

	std::ofstream adjMatrix_out("wyniki/adjMatrixsort.txt", std::ofstream::out);
	std::ofstream incList_out("wyniki/incListsort.txt", std::ofstream::out);
	adjMatrix_out << "Wierzcholki\tCzas\n";
	incList_out << "Wierzcholki\tCzas\n";

	for (int i = down_lim; i <= up_lim; i += step)
	{
		DGraph* test_graph = new DGraph(0.6, i);

		test_graph->generateRandomEdges();
		
		std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
		test_graph->adjMatrixSort();
		std::chrono::high_resolution_clock::time_point stop = std::chrono::high_resolution_clock::now();
		//Tu mozna zmienic jednostke Czas\nu, ustawione na nano domyslnie przeze mnie
		auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
		adjMatrix_out << i << "\t" << duration.count() << std::endl;

		start = std::chrono::high_resolution_clock::now();
		test_graph->incListSort();
		stop = std::chrono::high_resolution_clock::now();
		//Tu mozna zmienic jednostke Czas\nu, ustawione na nano domyslnie przeze mnie
		duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
		incList_out << i << "\t" << duration.count() << std::endl;

		delete test_graph;
	}

	adjMatrix_out.close();
	incList_out.close();
}

void graphTreeFinder()
{
	{
		std::cout << "--------TESTY WYZNACZANIA MINIMALNEGO DRZEWA ROZPINAJACEGO--------\n\n";
		int down_lim, up_lim, step;
		std::cout << "Podaj dolna granice testow: ";
		std::cin >> down_lim;
		std::cout << "Podaj gorna granice testow (MAX 7K przy dobrych wiatrach. #nie probuj, BARDZO WOLNY ALGORYTM): ";
		std::cin >> up_lim;
		std::cout << "Podaj krok wykonywania testow: ";
		std::cin >> step;

		std::ofstream dens7adjMatrix_out("wyniki/treedens7adjMatrix.txt", std::ofstream::out);
		std::ofstream dens7incList_out("wyniki/treedens7incLists.txt", std::ofstream::out);
		dens7adjMatrix_out << "Wierzcholki\tCzas\n";
		dens7incList_out << "Wierzcholki\tCzas\n";
		std::ofstream dens3adjMatrix_out("wyniki/treedens3adjMatrix.txt", std::ofstream::out);
		std::ofstream dens3incList_out("wyniki/treedens3incLists.txt", std::ofstream::out);
		dens3adjMatrix_out << "Wierzcholki\tCzas\n";
		dens3incList_out << "Wierzcholki\tCzas\n";

		for (int i = down_lim; i <= up_lim; i += step)
		{
			UGraph* test_graph = new UGraph(0.7, i);
			test_graph->generateRandomEdges();

			std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
			test_graph->adjprimTreeFinder();
			std::chrono::high_resolution_clock::time_point stop = std::chrono::high_resolution_clock::now();
			//Tu mozna zmienic jednostke Czas\nu, ustawione na nano domyslnie przeze mnie
			auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
			dens7adjMatrix_out << i << "\t" << duration.count() << std::endl;

			test_graph->resetForFinding();

			start = std::chrono::high_resolution_clock::now();
			test_graph->incprimTreeFinder();
			stop = std::chrono::high_resolution_clock::now();
			//Tu mozna zmienic jednostke Czas\nu, ustawione na nano domyslnie przeze mnie
			duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
			dens7incList_out << i << "\t" << duration.count() << std::endl;

			delete test_graph;

			test_graph = new UGraph(0.3, i);
			test_graph->generateRandomEdges();

			start = std::chrono::high_resolution_clock::now();
			test_graph->adjprimTreeFinder();
			stop = std::chrono::high_resolution_clock::now();
			//Tu mozna zmienic jednostke Czas\nu, ustawione na nano domyslnie przeze mnie
			duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
			dens3adjMatrix_out << i << "\t" << duration.count() << std::endl;

			test_graph->resetForFinding();

			start = std::chrono::high_resolution_clock::now();
			test_graph->incprimTreeFinder();
			stop = std::chrono::high_resolution_clock::now();
			//Tu mozna zmienic jednostke Czas\nu, ustawione na nano domyslnie przeze mnie
			duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
			dens3incList_out << i << "\t" << duration.count() << std::endl;

			delete test_graph;
		}

		dens7adjMatrix_out.close();
		dens7incList_out.close();
		dens3adjMatrix_out.close();
		dens3incList_out.close();
	}
}