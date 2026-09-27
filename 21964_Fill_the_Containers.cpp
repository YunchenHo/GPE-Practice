//Binary Search

/*
輸入一串容量（依序排列的乳桶 c[1..n]），
要把它們依照原本順序、切成連續的 m 段（不能打亂順序、不能跳著挑），
每一段的容量總和就是一個容器的容量。目標是：讓「容量最大的那個容器」盡量小。

Binary Search:
    先猜一個容量上限 mid(最大容器的最小值)，檢查用這個上限，最少要切成幾段
    如果段數count ≤ m，代表這個 mid 可行（甚至可能還可以更小）
    如果段數count > m，代表 mid 太小了（切不夠段的話會有一段超過mid）。
    
    答案本身具有單調性（如果 mid 可行，那所有比 mid 大的值也一定可行；如果 mid 不可行，比它小的也一定不可行），
    所以可以用二分搜尋去逼近「最小的那個可行值」，而不用真的把所有可能的容量都試過一遍。

Binary Search的上下界:
    下界 lo：至少要能裝下單一個最大的乳桶（因為每個乳桶必須整桶倒進同一個容器，容器容量不能比任何一個乳桶還小）→ lo = max(c[i])
    上界 hi：全部倒進同一個容器（m=1 的情況）→ hi = sum(c[i])
*/

#include <iostream>
#include <vector>
#include <algorithm> //max_element，通常有element或find的函式，需要加*
#include <numeric> //accumulate，數值，不需要加*
using namespace std;

//check: 驗證函式，檢查目前的count是否符合m個容器數的條件
//如果我允許每個容器最多只能裝到 mid，那最少要切成幾個容器才裝得完？
//在所有合法切法中，找出「最大那個容器的容量」最小可能是多少? == 找出最小的 T，使得「存在一種切法，讓每個容器都不超過 T」
bool check(int mid, int n, int m, const vector<int>& c){
    int count = 1; //目前的容器數
    int sum = 0;
    
    for(int i = 0; i < n; i++){
        if(sum + c[i] > mid){ //已經大於目前的最大容器容量
            count++; //得再開一個容器
            sum = c[i];
        }
        else{
            sum += c[i]; //繼續裝這個容器
        }
    }
    
    if(count <= m){
        return true;
    }
    else{
        return false;
    }
}

int main(){
    int n; //n個裝滿的桶
    while(cin >> n){
        int m; //用m個容器裝
        cin >> m;
        vector<int> c(n);
        for(int i = 0; i < n; i++){
            int k;
            cin >> k;
            c[i] = k;
        }
        
        int lo = *max_element(c.begin(), c.end()); //加上*取值
        int hi = accumulate(c.begin(), c.end(), 0); //最後一個是初始值
        
        while(lo < hi){
            int mid = lo + (hi - lo) / 2; // = (lo + hi) / 2
            //如果目前的最大容器容量mid符合條件
            if(check(mid, n, m, c)){
                hi = mid; //上界下修，答案可能更小
            }
            else{
                lo = mid + 1; //下界上修，答案要更大
            }
        }
        
        //最後 lo = hi
        cout << lo << endl;
        
    }
    return 0;
}