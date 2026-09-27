//sieve prime

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#define endl '\n' //輸出可以一次出來
using namespace std;

int main(){
    cin.tie(0)->sync_with_stdio(0); //輸出可以一次出來
    int n;
    vector<int> arr;
    arr.clear();

    while(cin >> n){
        
        if(n == 0){
            break;
        }
        
        for(int i = 2; i <= n; i++){
            bool flag = true; //質數
            for(int j = 1; j <= sqrt(i); j++){
                if(j == 1){
                    continue;
                }
                else if(i % j == 0){
                    
                    flag = false; //非質數
                    break;
                }
            }
            if(flag){
                arr.emplace_back(i); //把質數加進去
            }
        }

        int count = 0;
        int total = 0;
        
        if(!arr.empty()){
            for(int i = 0; i < arr.size(); i++){
                total = 0;
                for(int j = i; j < arr.size(); j++){
                    total += arr[j];
                    if(total == n){
                        count++;
                        break;
                    }
                    else if(total > n){
                        break;
                    }
                } 
            }
        }
        arr.clear();
        cout << count << endl;
    }
    return 0;
}