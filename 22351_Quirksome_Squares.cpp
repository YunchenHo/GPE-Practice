# include <iostream>
# include <vector>
# include <string>
# include <cmath>
# include <algorithm>
using namespace std;

//會TLE
/*int main(){
    int N;
    while(cin >> N){
        vector<string> arr;
        arr.clear();
        int i;
        
        int p1 = pow(10, N);
        for(i = 0; i < p1; i++){
            int j = i; //原數字
            string str = to_string(i); //原數字轉字串

            //特殊情況，補足0
            int p2 = pow(10, (N-1));
            if(i < p2){

                int str_num = N - str.length();
                while(str_num > 0){
                    str = "0" + str;
                    str_num--;
                }
            }

            //正常情況
            int num = N / 2; //位數/2
            string str1 = str.substr(0, num); //第一組數字字串
            string str2 = str.substr(num); //第二組數字字串
            int m = stoi(str1); //第一組數字
            int n = stoi(str2); //第一組數字

            if(pow((m + n), 2) == j){
                arr.emplace_back(str);
            }
        }
        //印出所有數字
        for(int k = 0; k < arr.size(); k++){
            cout << arr[k] << endl;
        }
    }
    return 0;
}*/

// 兩半(兩個數字)加起來的和=s，那麼s最多多大?不會超過2*10^(N/2)!
// 四位數=兩位數+兩位數<=200
int main(){
    int N;
    while(cin >> N){
        vector<string> arr;
        arr.clear();
        int i;
        int s = 2 * pow(10, (N/2));
        
        for(i = 0; i < s; i++){
            int j = i; //兩數相加總合
            int ss = i * i; //兩數相加總合^2
            string str = to_string(ss); //兩數相加總合^2轉字串

            if(str.length() > N){
                break;
            }

            //特殊情況，不符合位數條件，補足0
            if(str.length() < N){
                int str_num = N - str.length();
                while(str_num > 0){
                    str = "0" + str;
                    str_num--;
                }
            }
            
            //正常情況，直接符合位數條件
            int num = N / 2; //位數/2
            string str1 = str.substr(0, num); //第一組數字字串
            string str2 = str.substr(num); //第二組數字字串
            int m = stoi(str1); //第一組數字
            int n = stoi(str2); //第一組數字

            if((m + n) == j){
                arr.emplace_back(str);
            }
        }
        //印出所有數字
        for(int k = 0; k < arr.size(); k++){
            cout << arr[k] << endl;
        }
    }
    return 0;
}