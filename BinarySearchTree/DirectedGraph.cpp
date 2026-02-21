#include "DirectedGraph.h"


DirectedGraph::DirectedGraph(int amountOfEdges) {
	/*
	* Contructor which create the amountOfEdges^2 2d array of vectors
	* And randomly create edges and weight for edges in range from 1 to 15
	*/
	weightMatrix = std::vector<std::vector<int>>(amountOfEdges, std::vector<int>(amountOfEdges));
	for (int i = 0; i < weightMatrix.size(); i++) {
		for (int j = 0; j < weightMatrix.at(i).size(); j++) {
			int edge = _createEdgeOrNot();
			if (edge == 1 && j!=i) {
				int edgeWeight = _createWeightForVertex();
				weightMatrix.at(i).at(j) = edgeWeight;
			}

		}
	}
}
DirectedGraph::DirectedGraph(std::vector<std::vector<int>> wM) {
	/*
	* Contructor for tests
	*/
	weightMatrix = wM;
}

void DirectedGraph::displayAdjacencyVertex(int vertexNumber) {
	for (int i = 0; i < weightMatrix.at(vertexNumber).size(); i++) {
		/*
		* Display adjañent vertex for vertex with vertexNumber
		*/
		if (weightMatrix.at(vertexNumber).at(i) != 0) {
			std::cout << i << " ";
		}
	}
}
void DirectedGraph::getVerticesThroughWhichYouCanGetToVertexN(int vertexNumber) {
	/*
	* This method will display veretices use the queue method _getVerticesWichHasEdgesWithVertexN
	*/
	std::set<int> _initVertexes;
	for (int edge : weightMatrix.at(vertexNumber)) {
		_initVertexes.insert(edge);
	}
	std::vector<bool> vertexes = _getVerticesWichHasEdgesWithVertexN(vertexNumber);
	for (int i = 0; i < vertexes.size(); i++)
	{
		if (vertexes.at(i) && i!=vertexNumber) {
			std::cout << i << " ";
		}
	}
}
std::vector<bool> DirectedGraph::_getVerticesWichHasEdgesWithVertexN(int vertexNumber) {
	/*
	* This method use qeue for funding each node;
	* which has edge with the vertex given in getVerticesThroughWhichYouCanGetToVertexN;
	*/
	std::vector<bool> visited = std::vector<bool>(weightMatrix.size(), false);
	visited.at(vertexNumber) = true;
	std::queue<int> q;
	q.push(vertexNumber);
	while (!q.empty()) {
		int vertex = q.front();
		q.pop();
		for (int i = 0; i < weightMatrix.at(vertex).size();i++) {
			if (weightMatrix.at(vertex).at(i) != 0 and !visited.at(i)) {
				visited.at(i) = true;
				q.push(i);
			}
		}
	}
	return visited;
	
}

void DirectedGraph::displayWeightMatrix() {
	std::cout << std::setw(2) << "";
	for (int i = 0; i < weightMatrix.size(); i++) {
		std::cout << std::setw(4) << i;
	}
	std::cout << std::endl;
	std::cout << std::endl;

	int i = 0;
	for (const auto& row : weightMatrix) {
		std::cout << std::setw(2) << i;
		for (const auto& val : row) {
			std::cout << std::setw(4) << val;
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


std::vector<std::stack<int>> DirectedGraph::dijkstrasAlgorithm(int vertex) {
	// dijkstrasAlgorithm
	// see https://www.cs.usfca.edu/~galles/visualization/Dijkstra.html
	struct dijkstrasNode {
		bool visited = false;
		int path = -1;
		int cost = INT_MAX;
	};
	std::map<int, dijkstrasNode> nodes;
	for (int i = 0; i < weightMatrix.size(); i++) {
		nodes.insert({ i, dijkstrasNode() });
	}
	nodes.at(vertex).visited = true;
	nodes.at(vertex).cost = 0;
	auto qComparator = [](std::pair<int, dijkstrasNode> a, std::pair<int, dijkstrasNode> b) {
		return a.second.cost > b.second.cost;
		};
	std::priority_queue<std::pair<int, dijkstrasNode>, std::vector<std::pair<int, dijkstrasNode>>, decltype(qComparator)> q;

	q.push({ vertex,nodes.at(vertex) });

	while (!q.empty()) {
		std::pair<int, dijkstrasNode> currentNode = q.top();
		q.pop();
		nodes[currentNode.first].visited = true;
		std::vector<int> edgesWeight = weightMatrix.at(currentNode.first);
		for (int i = 0; i < edgesWeight.size(); i++) {
			if (
				!nodes.at(i).visited &&
				edgesWeight.at(i) != 0 &&
				nodes.at(i).cost > currentNode.second.cost + edgesWeight.at(i)
				) {
				nodes.at(i).cost = currentNode.second.cost + edgesWeight.at(i);
				nodes.at(i).path = currentNode.first;
				q.push({ i, nodes.at(i) });
			}
		}
	}

	std::vector<std::stack<int>> pathes;
	for (int i = 0; i < nodes.size(); i++) {
		std::stack<int> path;
		int j = i;
		while (true) {
			path.push(j);
			if (nodes.at(j).path == -1) break;
			j = nodes.at(j).path;
		}
		pathes.push_back(path);
	}
	return pathes;
}

static std::vector<std::vector<int>> matrixMultiply(std::vector<std::vector<int>> A, std::vector<std::vector<int>> B) {
	std::vector<std::vector<int>> C = std::vector<std::vector<int>>(A.size(), std::vector<int>(A.at(0).size()));

	for (int i = 0; i < A.size(); i++) {
		for (int j = 0; j < B.size(); j++) {
			for (int k = 0; k < A.size(); k++) {
				C[i][j] += A[i][k] * B[k][j];
			}
		}
	}
	return C;
}
int DirectedGraph::findPathesByLength(int startVertex, int endVertex, int pathLength) {
	std::vector<std::vector<int>> adjacencyMatrix = std::vector<std::vector<int>>(weightMatrix.size(), std::vector<int>(weightMatrix.at(0).size()));
	for (int i = 0; i < weightMatrix.size(); i++) {
		for (int j = 0; j < weightMatrix.at(i).size(); j++) {
			if (weightMatrix.at(i).at(j) > 0) {
				adjacencyMatrix.at(i).at(j) = 1;
			}
		}
	}
	for (int i = 1; i < pathLength; i++) {
		adjacencyMatrix = matrixMultiply(adjacencyMatrix, adjacencyMatrix);
	}
	return adjacencyMatrix.at(startVertex).at(endVertex);
}