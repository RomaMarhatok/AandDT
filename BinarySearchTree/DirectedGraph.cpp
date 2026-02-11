#include "DirectedGraph.h"

DirectedGraph::DirectedGraph(int amountOfEdges) {
	adjacencyMatrix = std::vector<std::vector<int>>(amountOfEdges,std::vector<int>(amountOfEdges));
	weightMatrix = std::vector<std::vector<int>>(amountOfEdges, std::vector<int>(amountOfEdges));

	for (int i = 0; i < adjacencyMatrix.size(); i++) {
		// why we assign to j = i+1
		// because we already proccesed another vertex how i write below
		for (int j = i + 1; j < adjacencyMatrix.at(i).size(); j++) {
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
				adjacencyMatrix.at(i).at(j) = 1;
				adjacencyMatrix.at(j).at(i) = 1;
				int edgeWeight = _createWeightForVertex();

				// also make the same for edge weight
				weightMatrix.at(i).at(j) = edgeWeight;
				weightMatrix.at(j).at(i) = edgeWeight;
			}

		}
	}
}
void DirectedGraph::displayAdjacencyVertex(int vertexNumber) {
	if (vertexNumber - 1 > 0) {
		for (int i = 0; i < adjacencyMatrix.at(vertexNumber - 1).size(); i++) {
			if (adjacencyMatrix.at(vertexNumber - 1).at(i) == 1) {
				std::cout << i + 1 << " ";
			}
		}
	}
}
void DirectedGraph::getVerticesThroughWhichYouCanGetToVertexN(int vertexNumber) {
	std::set<int> vertexes = _getVerticesWichHasEdgesWithVertexN(adjacencyMatrix.at(vertexNumber - 1));
	for (int vertex : vertexes) {
		std::cout << vertex << " ";
	}
}
std::set<int> DirectedGraph::_getVerticesWichHasEdgesWithVertexN(std::vector<int> edgesOfVertex) {
	std::set<int> vertexes = std::set<int>();
	for (int i = 0; i < edgesOfVertex.size(); i++) {
		if (edgesOfVertex.at(i) == 1) {
			vertexes.insert(i + 1);
			std::set<int> newVertexes = _getVerticesWichHasEdgesWithVertexN(adjacencyMatrix.at(i));
			std::set_union(
				edgesOfVertex.begin(),
				edgesOfVertex.end(),
				newVertexes.begin(), 
				newVertexes.end(),
				std::back_inserter(vertexes)
			);
		}
	}
	return vertexes;
}
void DirectedGraph::displayAdjacencyMatrix() {
	_displayVectorMatrix(adjacencyMatrix);
}
void DirectedGraph::displayWeightMatrix() {
	_displayVectorMatrix(weightMatrix);
}
template<typename T>
void DirectedGraph::_displayVectorMatrix(const std::vector<std::vector<T>>& arr) {
	std::cout << std::setw(2) << "";
	for (int i = 0; i < adjacencyMatricx.size(); i++) {
		std::cout << std::setw(4)<< i+1;
	}
	std::cout << std::endl;
	std::cout << std::endl;

	int i = 1;
	for (const auto& row : arr) {
		std::cout << std::setw(2) << i;
		for (const auto& val : row) {
			std::cout<< std::setw(4) << val;
		}
		std::cout << std::endl;
		i++;
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

