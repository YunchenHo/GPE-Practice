// prime, permutation, vector
// v1: 用 power crisis 類似寫法試試:會TLE
// v2: 用vector形成偽list

#include <iostream>
#include <vector>
#include <cmath> //質數
using namespace std;

int main(){
    int n;
    while(cin >> n){
        //終止條件
        if(n == 0){
            break;
        }
        if(n == 1){
            cout << 1 << endl;
            continue;
        }
        
        //vector<bool> people(n+1, false); //放所有人，有沒有被吃，預設都沒被吃
        //bool all_eat = false; //是否全部被吃
        
        vector<int> next(n+1), previous(n+1);
        for (int i = 1; i <= n; i++) {
            next[i] = (i % n) + 1; //編號i的上一個活人
            previous[i] = (i - 2 + n) % n + 1;//編號i的下一個活人
        }

        int pos = 2; //預設吃人位置
        int alive = n; //目前存活人數
        int last = -1; //最終存活者

        //取質數
        for(int i = 3; ;i++){
            bool is_prime = true;
            for(int j = 1; j <= sqrt(i); j++){
                if(j == 1){
                    continue;
                }
                else if(i % j == 0){
                    is_prime = false;
                    break;
                }
            }
            
            //吃人
            if(is_prime){
                //吃掉pos後，去掉本來鄰居是pos的，互相接起來
                next[previous[pos]] = next[pos];
                previous[next[pos]] = previous[pos];
                last = pos;
                alive--;

                if(alive == 0){
                    cout << last << endl;
                    break;
                }

                for (int step = 0; step < i; step++) {
                    pos = next[pos]; 
                }
            }

            /*會TLE
            //吃人
            if(is_prime){
                people[pos] = true;
                last = pos;
                alive--;

                int step = 0;
                
                while(!all_eat && step < i){    
                    //是否還有人沒被吃
                    if(alive == 0){
                        all_eat = true;
                        break;
                    }

                    //從pos的下一格開始
                    pos = pos % n + 1;
                    
                    //跳過true的
                    if(people[pos] == false){
                        step++;
                    }
                }   
            }

            if(all_eat){
                cout << last << endl;
                break;
            }
            */
        }
    }
    return 0;
}