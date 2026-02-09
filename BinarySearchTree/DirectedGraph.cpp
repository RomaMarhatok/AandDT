#include "DirectedGraph.h"

DirectedGraph::DirectedGraph(int amountOfEdges) {
	adjacencyMatricx = std::vector<std::vector<int>>(amountOfEdges,std::vector<int>(amountOfEdges));
	weightMatrix = std::vector<std::vector<int>>(amountOfEdges, std::vector<int>(amountOfEdges));

	for (int i = 0; i < adjacencyMatricx.size(); i++) {
		// why we assign to j = i+1
		// because we already proccesed another vertex how i write below
		for (int j = i + 1; j < adjacencyMatricx.at(i).size(); j++) {
			int edge = _createEdgeOrNot();
			/*
			* If the currentVertex has the edge with mirrorVertex;
			* We must to marks it in mirrorVertex too;
			* Example:
			*	We have graph with 3 vertexes;
			*
			*	1) The init adjancyMatrix looks like:
			*		1 2 3
			*	  1	0 0 0
			*     2 0 0 0
			*     3 0 0 0
			*	2) If we mark the first vertex has the edge with the vertex two,
			*	   it means the second vertex has the edge with the vertex two;
			*
			*	3) The adjancyMatrix will look like this:
			*		1 2 3
			*	  1	0 1 0
			*     2 1 0 0
			*     3 0 0 0
			*/
			if (edge == 1 && j!=i) {
				adjacencyMatricx.at(i).at(j) = 1;
				adjacencyMatricx.at(j).at(i) = 1;
				int edgeWeight = _createWeightForVertex();

				// also make the same for edge weight
				weightMatrix.at(i).at(j) = edgeWeight;
				weightMatrix.at(j).at(i) = edgeWeight;
			}

		}
	}
}

int DirectedGraph::_createEdgeOrNot() {
	return _randomIntValue(0, 1);
}

int DirectedGraph::_createWeightForVertex() {
	return _randomIntValue(1, 15);
}

int DirectedGraph::_randomIntValue(int min,int max) {
	std::mt19937 gen(std::random_device{}());
	std::uniform_int_distribution<int> dist(min, max);
	return dist(gen);
}

