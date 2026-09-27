//DP (Dynamic Programming) + Game Theory: 完全背包的變形問題
//DP (Dynamic Programming): 記住過去，減少重複計算，使用陣列或字典記下來

/*
讀 n
讀 m
讀 m 個數字進 moves

建立 dp 陣列，大小 n+1
dp[0] = false

for i = 1 到 n:
    dp[i] = false // 先假設你會輸
    for 每個 k in moves:
        if (i - k >= 0 且 dp[i-k] == false):
            dp[i] = true
            break   // 找到一種必勝走法就可以提早跳出

輸出：dp[n] 為 true 就印 "Stan wins"，否則印 "Ollie wins"*/
// Stan 一定是「第一個站上 n 顆石頭這個位置的人」，dp[n] 問的問題跟「Stan 贏不贏」問的其實是同一個問題

#include <iostream>
#include <vector>
using namespace std;

int main(){
    int n;
    while(cin >> n){
        int m;
        cin >> m;
        vector<int> moves(m);
        
        for(int i = 0; i < m ; i++){
            int num;
            cin >> num;
            moves[i] = num;    
        }

        vector<bool> dp(n+1); //最多到1000000顆石頭，要開到1000001
        dp[0] = false; // 桌上剩0顆石頭，輪到你但沒得走，你輸了

        for(int i = 1; i <= n; i++){
            dp[i] = false; //桌上剩i顆石頭，先假設我會輸
            for(int k = 0; k < m; k++){
                if(i - moves[k] >= 0 && dp[i - moves[k]] == false){
                    dp[i] = true;
                    break;
                }
            }

        }
        
        if(dp[n] == true){
            cout << "Stan wins" << endl;
        }
        else if(dp[n] == false){
            cout << "Ollie wins" << endl;
        }
    }
    return 0;
}