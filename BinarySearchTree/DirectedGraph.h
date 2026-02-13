#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <iomanip>
#include <set>
#include <algorithm>
#include <map>
#include <numeric>
#include <queue>
#include <iterator>
#include <utility>
#include <stack>
#ifndef DG
#define DG
class DirectedGraph {
	using d2IntVectorsArray = std::vector<std::vector<int>>;
public:
	d2IntVectorsArray weightMatrix;
	DirectedGraph(int amountOfEdges);
	DirectedGraph(std::vector<std::vector<int>> weightMatrix);
	void displayWeightMatrix();
	void displayAdjacencyVertex(int vertexNumber);
	void getVerticesThroughWhichYouCanGetToVertexN(int vertexNumber);
	std::vector<std::stack<int>> dijkstrasAlgorithm(int vertex);
	void findPathesByLength(int pathLength);
private:
	int _createEdgeOrNot();
	int _createWeightForVertex();
	int _randomIntValue(int min, int max);
	std::set<int> _getVerticesWichHasEdgesWithVertexN(std::vector<int> edgesOfVertex);
};
#endif //!DG