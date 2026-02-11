#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <iomanip>
#include <set>
#include <algorithm>
#ifndef DG
#define DG
class DirectedGraph {
public:
	std::vector<std::vector<int>> adjacencyMatrix;
	std::vector<std::vector<int>> weightMatrix;
	DirectedGraph(int amountOfEdges);
	void displayAdjacencyMatrix();
	void displayWeightMatrix();
	void displayAdjacencyVertex(int vertexNumber);
	void getVerticesThroughWhichYouCanGetToVertexN(int vertexNumber);

private:
	template<typename T>
	void _displayVectorMatrix(const std::vector<std::vector<T>>& arr);
	int _createEdgeOrNot();
	int _createWeightForVertex();
	int _randomIntValue(int min, int max);
	std::set<int> _getVerticesWichHasEdgesWithVertexN(std::vector<int> edgesOfVertex);
	void _dijkstrasAlgorithm(int vertex);
};
#endif //!DG