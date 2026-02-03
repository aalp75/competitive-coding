#include <bits/stdc++.h>

using namespace std;

/**
 * cartesian tree
 * 
 * build a max-heap cartesian tree
 * 
 * lc: next node on the left
 * rc: next node on the right
 * 
 * all elements of the array needs to be distinct
 * 
 * to build a min-heap cartesian tree:
 *  change the compare condition to be: arr[top] < arr[i]
 * 
 * once the cartesian tree is built we can explore it 
 * with a simple DFS
 * 
 */

void dfs(int node, vector<int>& lc, vector<int>& rc) {
    cout << "Node: " << node << '\n';
    if (lc[node] >= 0) dfs(lc[node], lc, rc);
    if (rc[node] >= 0) dfs(rc[node], lc, rc);
}

void cartesianTree(vector<int>& arr) {

    int n = arr.size();
    vector<int> lc(n, -1);
    vector<int> rc(n, -1);

	vector<int> stack;
	for(int i = 0; i < n; i++){
		while(!stack.empty()){
			int top = stack.back();
			if(arr[top] > arr[i]) {
                break;
            }
			lc[i] = top;
			stack.pop_back();
		}
		if(!stack.empty()) {
            rc[stack.back()] = i;
        }
		stack.push_back(i);
	}

    int start = max_element(arr.begin(), arr.end()) - arr.begin();
    dfs(start, lc, rc);
}

int main() {

    vector<int> arr = {1, 5, 8, 2, 3, 6, 4, 7};
    cartesianTree(arr);
}