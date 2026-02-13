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
	* This method will display veretices use the recurstion method _getVerticesWichHasEdgesWithVertexN
	*/
	std::set<int> vertexes = _getVerticesWichHasEdgesWithVertexN(weightMatrix.at(vertexNumber));
	for (int vertex : vertexes) {
		std::cout << vertex << " ";
	}
}
std::set<int> DirectedGraph::_getVerticesWichHasEdgesWithVertexN(std::vector<int> edgesOfVertex) {
	/*
	* This method use recurstion for funding each node;
	* which has edge with the vertex given in getVerticesThroughWhichYouCanGetToVertexN;
	*/
	std::set<int> vertexes = std::set<int>();
	for (int i = 0; i < edgesOfVertex.size(); i++) {
		if (edgesOfVertex.at(i) != 0) {
			vertexes.insert(i);
			std::set<int> newVertexes = _getVerticesWichHasEdgesWithVertexN(weightMatrix.at(i));
			std::set_union(
				edgesOfVertex.begin(),
				edgesOfVertex.end(),
				newVertexes.begin(),
				newVertexes.end(),
				std::inserter(vertexes, vertexes.begin())
			);
		}
	}
	return vertexes;
}

void DirectedGraph::displayWeightMatrix() {
	std::cout << std::setw(2) << "";
	for (int i = 0; i < weightMatrix.size(); i++) {
		std::cout << std::setw(4) << i;
	}
	std::cout << std::endl;
	std::cout << std::endl;

	int i = 1;
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

void DirectedGraph::findPathesByLength(int pathLength) {

}