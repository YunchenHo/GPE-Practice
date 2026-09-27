# include <iostream>
using namespace std;

/*
int main(){
    int n;
    while(cin >> n){
        
        int k = n;

        while (k / 3 > 0)
        {
            n += k / 3;
            k = k / 3 + k % 3;
        }
        
        if(k == 2){
            n += 1;
        }
        cout << n << endl;
    } 
    return 0;
}
*/

//陰間解法
int main(){
    int n;
    while(cin >> n){
        
        double k = n * 1.5;

        cout << int(k) << endl;
    } 
    return 0;
}