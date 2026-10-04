#include <iostream>
#include <vector>
#include <algorithm>

#include "../debug.h"

using namespace std;

/**
 * Stronly Connected Components
 * 
 * Find the strongly connected components of a graph using Tarjan's algorithm
 * 
 * Input: directed graph stored in a vector<vector<int>> adj with nodes from 0 to n - 1
 * 
 * Output:
 * 		- components (sorted in reverse topological order)
 * 		- roots: 1 root by components, each nodes of a component will point to the same root
 *  	- adjCond: the condensation graph on the roots
 * 
 * Algorithm details:
 * 		run a DFS on the directed graph and keep tracks of the timerIn and timerLow for each node. Ever node of the 
 * 		same component will have the same timerLow
 * 
 * Remark: The condensation graph is acyclic, hence it can be sorted by topological order.
 * 
 * Implementation is based on https://cp-algorithms.com/graph/inProcessrongly-connected-components.html
 * 
 */

struct SCC {

	int n;
	vector<vector<int>> components;
	vector<vector<int>> adjCond;
	vector<int> roots; 		// keeps track of the SCC roots of the nodes

	int timer;        		// entry time iterator
	
	vector<int> inProcess;  // keep track of the nodes in process
	
	vector<int> timerIn;  	// keeps track of the entry time of the node
	vector<int> timerLow; 	// keeps track of the unprocess reachable node with the lowest entry time

	SCC(const vector<vector<int>>& adj) : n(adj.size()), timer(0) {
	 	components.clear();
	 	adjCond.clear();

	 	adjCond.resize(n);
	 	roots.assign(n, -1);

	 	inProcess.clear();
	  	
	  	timerIn.assign(n, -1);
	  	timerLow.assign(n, -1);

		// applies the tarjan algorithm to all the nodes
		// adds nodes to the components in reverse topological order
		for (int u = 0; u < n; u++) {
			if (timerIn[u] == -1) {
		     	dfs(adj, u);
		    }
		}

		// adds edges to the condensation graph
		adjCond.assign(n, {});
		for (int u = 0; u < n; u++) {
		    for (auto v : adj[u]) {
			    if (roots[u] != roots[v]) {
			    	adjCond[roots[u]].push_back(roots[v]);
			    }
		    }
		}

		// remove duplicate edges
		for (auto& edges : adjCond) {
    		sort(edges.begin(), edges.end());
    		edges.erase(unique(edges.begin(), edges.end()), edges.end());
		}
	}

	// Tarjan's algorithm
	void dfs(const vector<vector<int>>& adj, int u) {
		timerLow[u] = timer;
		timerIn[u] = timer;

		timer++;

		inProcess.push_back(u);

		for (auto v : adj[u]) {
			if (timerIn[v] == -1) { // tree-edge
				dfs(adj, v);
				timerLow[u] = min(timerLow[v], timerLow[u]);	
			}
			else if (roots[v] == -1) { // back-edge on not already processed node
				timerLow[u] = min(timerLow[u], timerIn[v]);
			}
		}

	  	if (timerLow[u] == timerIn[u]) { // u is a root of the component
	   		components.push_back({u}); // initializes a new component with root u
	    	while (true) { // // pop the stack until we reach u beacuse it's the root of the component
	     		int v = inProcess.back();
	      		inProcess.pop_back();
	      		roots[v] = u; // root of v is u
	      		if (v == u)
	        		break;
	      		components.back().push_back(v); // adds node v to the component of u
	    	}
	 	}
 	}
};

int main() {

	int n = 10;
	vector<vector<int>> adj(10);

	vector<pair<int, int>> edges = {
		{0, 1}, {0, 7}, 
		{1, 1}, {1, 2},
		{2, 1}, {2, 5},
		{3, 2}, {3, 4},
		{4, 9},
		{5, 3}, {5, 6}, {5, 9},
		{6, 2},
		{7, 0}, {7, 6}, {7, 8},
		{8, 6}, {8, 9},
		{9, 4} 
	};

	for (auto [u, v] : edges) {
		adj[u].push_back(v);
	}

	SCC scc(adj);

	debug(scc.components);

	return 0;
}