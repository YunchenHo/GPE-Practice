//約瑟夫問題（Josephus Problem）: 循環鏈結串列（Circular Linked List）
//也可用#include <list> 解決

/*
for m = 1, 2, 3, ...:
    模擬一次完整的關閉過程（用鏈結串列或陣列模擬環狀結構）
    紀錄最後一個被關閉的是哪個區域
    如果最後關閉的是區域13:
        輸出這個 m，跳出迴圈
*/

#include <iostream>
#include <vector> //陣列
using namespace std;

int simulate(int m, int n){
    int pos = 1; //目前區域編碼位置
    int last = -1; //最後區域編碼位置 初始值-1
    int count = 0; //目前關閉的總區域數，最後會達到n
    vector<bool> region(n+1);

    for(int i = 1; i <= n; i++){
        region[i] = false; //初始都尚未關閉
    }

    while(count < n){
        region[pos] = true; //當前編碼關閉
        last = pos; //記得標記最後區域編碼位置
        count++;

        if(count == n){
            break;
        }

        //處理從n到1的問題
        //每次都要從pos的下一格開始走m步，要跳過true的，用step記走了幾步了
        int step = 0;
        while(step < m){
            pos = pos % n + 1; //從pos的下一步開始
            if(region[pos] == false){
                step++; //跳過true的
            }
        }
    }
    return last; //最後區域編碼位置，目標是13
}

int main(){
    int n;
    while(cin >> n){
        
        if(n == 0){
            break;
        }
        
        int m;
        int last;
        
        for(m = 1; ; m++){ //m不一定小於n
            last = simulate(m, n);
            if(last == 13){
                cout << m << endl;
                break;
            }
        }
    }
    return 0;
}