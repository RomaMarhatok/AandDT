#include <iostream>
#include <vector>
#include <string>
#include <random>
#ifndef DG
#define DG
class DirectedGraph {
public:
	std::vector<std::vector<int>> adjacencyMatricx;
	std::vector<std::vector<int>> weightMatrix;
	DirectedGraph(int amountOfEdges);
private:

	int _createEdgeOrNot();
	int _createWeightForVertex();
	int _randomIntValue(int min, int max);
};
#endif //!DG