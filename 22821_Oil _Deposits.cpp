// BFS/DFS
// 核心概念：連通塊計數（Connected Components Counting）
// 一個格子的 8 個鄰居（上、下、左、右、左上、右上、左下、右下）只要是 @，就算相連
// 掃描整張地圖，每次看到一個還沒被拜訪過的 @，用 BFS 或 DFS 把跟它相連的所有 @ 都 flood fill 標記成已拜訪 *

// 可用 DFS 遞迴或 BFS 佇列
/* 
DFS 遞迴思路:
//dfs(x, y):
    如果 (x,y) 出界，或 grid[x][y] 不是 '@'，就直接 return（這就是遞迴的終止條件）
    把 grid[x][y] 改成 '*'（標記成已拜訪）
    對 8 個方向都遞迴呼叫 dfs(x+dx[d], y+dy[d])

//BFS 佇列思路:    
把起點丟進 queue，起點標記已拜訪
while queue 不是空的:
    取出一個座標
    檢查它的 8 個鄰居，只要是還沒拜訪過的 '@'，標記已拜訪並丟進 queue

//main:
while (cin >> m >> n) {
    if (m == 0 && n == 0) break;   // 結束訊號
    讀入 m 行地圖
    count = 0
    for 每個座標 (i, j):
        if grid[i][j] == '@':
            count++
            dfs(i, j)   // 把這一整塊油田都淹沒掉
    輸出 count
}
*/

#include <iostream>
#include <vector>
using namespace std;

//static const
const int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1}; //固定陣列array直接宣告
const int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

//DFS 遞迴
//&: Call by Reference: 無複印件，直接改動原件
//const &: 只能看原件，不能改動
void dfs(int m, int n, int x, int y, vector<vector<char>>& grid){ 

    if(x < 0 || x >= m || y < 0 || y >= n || grid[x][y] != '@'){
        return;
    }
    
    grid[x][y] = '*';
    
    for(int d = 0; d < 8; d++){
        dfs(m, n, x+dx[d], y+dy[d], grid);
    }
}

int main(){
    int m , n;
    while(cin >> m >> n){
        if(m == 0 && n == 0){
            break;
        }

        vector<vector<char>> grid(m, vector<char>(n));
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                char oil;
                cin >> oil;
                grid[i][j] = oil;
            }
        }

        int count = 0; //oil deposit的數量

        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                if(grid[i][j] == '@'){
                    count ++;
                    dfs(m, n, i, j, grid);
                }
            }
        }

        cout << count << endl;
    }
    
    return 0;
}