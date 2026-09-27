//DP (Dynamic Programming): 完全背包的計數版本

/*
dp[0] = 1 // 湊出金額0，只有「什麼都不拿」這一種方法
for 每一種幣值 c（外層）:
    for j = c 到 maxAmount（內層，由小到大）:
        dp[j] += dp[j - c]
*/

#include <iostream>
#include <cmath> // round
#include <vector>
#include <iomanip> //設定數字輸出位數與靠右對齊
using namespace std;

int main(){
    
    double money; //浮點數

    int m[11] = {1, 2, 4, 10, 20, 40, 100, 200, 400, 1000, 2000};
    //可以只做一次dp，之後查表
    //dp[j] 代表：目前已經考慮過的硬幣種類裡，湊出金額 j 有幾種方法
    vector<long long> dp(6001); //題目上限300元 * 20倍 = 6000個金額，int不夠
    
    dp[0] = 1; //0元只有一種方法
    for(int i = 0; i < 11; i++){
        int c = m[i];
        for(int j = c; j <= 6000; j++){
            dp[j] = dp[j] + dp[j - c];
        }
    }

    cout << fixed << setprecision(2); // 固定小數點後 2 位

    while(cin >> money){
        if(money == 0.00){
            break;
        }
        
        int amount = (int)round(money * 20); //先(double*20)再round四捨五入再轉int

        //setw(x) 設定下一個輸出的寬度為 x 個字元，不足處在左側補空白
        cout << setw(6) << money;
        cout << setw(17) << dp[amount] << endl;
    }
    return 0;
}