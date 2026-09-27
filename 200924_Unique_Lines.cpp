//gcd function
//算不重複的unique line有幾條
//核心: 三點以上的點在同一斜率上共線
//二元一次方程式: ax + by = c，(a, b, c)tuple用gcd化簡，需固定正負號

/*

讀 t 組測資
for 每組測資:
    讀 n 個點
    建立一個 set<tuple<int,int,int>>
    for 每一對點 (i, j)，i < j:
        算出 A, B, C
        用 gcd 化簡
        固定正負號
        丟進 set
    輸出 set.size()

如何算出 A, B, C
ax + by = c 透過 m = (y2 -y1) / (x2 - x1) = -a / b 可得
(y2-y1)x + (x1-x2)y = (y2-y1)x1 + (x1-x2)y1

*/

#include <iostream>
#include <vector>
#include <set>
#include <tuple>
#include <numeric> //gcd
#include <cmath> //abs 絕對值
using namespace std;

int main(){
    int t;
    cin >> t; //幾組測資
    while(t--){
        int n;
        cin >> n; //幾個點
        
        //存輸入的點用vector<pair <int, int>>陣列每格為一個pair
        vector<pair <int, int>> points(n);
        for(int i = 0; i < n; i++){
            cin >> points[i].first >> points[i].second;
        }

        //有幾條不重複的unique lines
        set<tuple <int, int, int>> lines;
        
        //抓出每一對點算方程式ax + by = c的(a, b, c)
        for(int i = 0; i < n; i++){
            for(int j = i+1; j < n; j++){
              int a = points[j].second - points[i].second;
              int b = points[i].first - points[j].first;
              int c = a * points[i].first + b * points[i].second;
              
              //取gcd
              int g = gcd(gcd(abs(a), abs(b)), abs(c));
              a = a / g;
              b = b / g;
              c = c / g;
              
              //固定正負號(同一條線，避免因係數正負號差異被視為不同條)
              //統一讓a為證，若a為0，則讓b為正
              if(a < 0 || (a == 0 && b < 0)){ //&&的優先權比||高
                a = -a;
                b = -b;
                c = -c;
              }
              //插入set(自動刪除重複元素)
              lines.insert(make_tuple(a, b ,c));
            }
        }
        cout << lines.size() << endl;
    }
    return 0;
}