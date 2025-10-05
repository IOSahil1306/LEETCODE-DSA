#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        if (heights.empty() || heights[0].empty()) return {};
        int m = heights.size(), n = heights[0].size();
        
        auto bfs = [&](const vector<pair<int,int>>& starts) {
            vector<vector<char>> vis(m, vector<char>(n, 0));
            queue<pair<int,int>> q;
            for (auto &p : starts) {
                int r = p.first, c = p.second;
                if (!vis[r][c]) {
                    vis[r][c] = 1;
                    q.push({r, c});
                }
            }
            while (!q.empty()) {
                auto [r, c] = q.front(); q.pop();
                static const int dr[4] = {1,-1,0,0};
                static const int dc[4] = {0,0,1,-1};
                for (int k=0;k<4;++k) {
                    int nr = r + dr[k], nc = c + dc[k];
                    if (nr>=0 && nr<m && nc>=0 && nc<n && !vis[nr][nc]) {
                        // We only move from neighbor to current if neighbor height >= current height
                        // (reverse expansion: ocean can reach uphill)
                        if (heights[nr][nc] >= heights[r][c]) {
                            vis[nr][nc] = 1;
                            q.push({nr, nc});
                        }
                    }
                }
            }
            return vis;
        };
        
        // Pacific starts: top row and left column
        vector<pair<int,int>> pacStarts;
        for (int c=0;c<n;++c) pacStarts.push_back({0,c});
        for (int r=0;r<m;++r) pacStarts.push_back({r,0});
        // Atlantic starts: bottom row and right column
        vector<pair<int,int>> atlStarts;
        for (int c=0;c<n;++c) atlStarts.push_back({m-1,c});
        for (int r=0;r<m;++r) atlStarts.push_back({r,n-1});
        
        auto pac = bfs(pacStarts);
        auto atl = bfs(atlStarts);
        
        vector<vector<int>> ans;
        for (int r=0;r<m;++r) {
            for (int c=0;c<n;++c) {
                if (pac[r][c] && atl[r][c]) ans.push_back({r,c});
            }
        }
        return ans;
    }
};

