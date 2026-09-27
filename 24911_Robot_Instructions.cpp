#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(){

    int n;
    cin >> n;
    while(n--){

        int p = 0;

        int m;
        cin >> m;
        cin.ignore(10000, '\n'); //手動清掉殘留的換行字元，從cin到getline

        vector<string> arr2(m + 1); //輸入後的變數只能用vector不能用array

        for(int i = 1; i <= m; i++){
            string motion;
            getline(cin, motion); //cin遇到空格會停下來

            if(motion == "LEFT"){
                p--;
                arr2[i] = "LEFT";
            }

            else if(motion == "RIGHT"){
                p++;
                arr2[i] = "RIGHT";
            }

            else{
                string number = motion.substr(8); //SAME AS 共8個字元
                int num = stoi(number); //stringtointeger
                if(arr2[num] == "LEFT"){
                    p--;
                    arr2[i] = "LEFT";
                }
                else if(arr2[num] == "RIGHT"){
                    p++;
                    arr2[i] = "RIGHT";
                }
            }
        }

        cout << p << endl;
    }

    return 0;
}
