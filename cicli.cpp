#include<iostream>
#include<fstream>
#include<vector>
#include<queue>
#include<set>

using namespace std;

int *parent;
int *level;
bool *connected;

int dst(int s, int e);

int main(int argc, char const *argv[]) {

    int N; //Number of nodes
    int M; //Number of edges
    int Q; //Number of requests
    int v1; //tmp node1
    int v2; //tmp node2
    ifstream in("input.txt");
    ofstream out("output.txt");

    in >> N >> M >> Q;

    vector<vector<int>>G(N);

    for(int i = 0; i < M; ++i) {
        in >> v1 >> v2;
        G[v1].push_back(v2);
        G[v2].push_back(v1);
    }

    parent = new int[N];
    level = new int[N];
    connected = new bool[N];

    for(int i = 0; i < N; ++i) {
        parent[i] = -1;
        level[i] = -1;
        connected[i] = false;
    }

    set<int> visited;
    queue<int> visit;
    int curr;

    level[0] = 0;
    visit.push(0);
    visited.insert(0);

    for(int j = 0; j < N; j++) {
        curr = visit.front();
        visit.pop();

        for(int i = 0; i < G[curr].size(); ++i) {
            if(level[G[curr][i]] == -1) {
                parent[G[curr][i]] = curr;
                level[G[curr][i]] = level[curr] + 1;
                visit.push(G[curr][i]);
                visited.insert(G[curr][i]);
            }

            if(level[G[curr][i]] == level[curr]) {
                connected[G[curr][i]] = connected[curr] = true;
            }
        }
    }

    for(int i = 0; i < Q; ++i) {
        in >> v1 >> v2;
        out << dst(v1, v2) << endl;
    }
    
    
    return 0;
}

int dst(int s, int e) {

    int dist = 0;
    int lower;
    int higher;
    bool found = false;
    
    if(level[s] > level[e]) {
        lower = s;
        higher = e;
    } else { 
        lower = e;
        higher = s;
    }

    int diff = level[lower] - level[higher];

    dist += diff;
    for (int i = 0; i < diff; ++i) {
        lower = parent[lower];
    }
    
    while(!found) {
        if(lower == higher) {
            return dist;
        } else if(connected[lower] && connected[higher] && parent[lower] == parent[higher]) {
            return dist = dist + 1;
        } else {
            lower = parent[lower];
            higher = parent[higher];
            dist = dist + 2;
        }
    }   
       

    return dist;
}