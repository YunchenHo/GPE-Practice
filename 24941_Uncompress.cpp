#include <iostream>
#include <string>
#include <list> //鏈結串列
#include <iterator> //next要用到
#include <cctype> //型別檢查(isdigit)
using namespace std;

int main()
{
    string line;
    list<string> words;

    while(getline(cin, line) && line != "0"){
        line += "\n"; //不然會錯

        char c;

        for(int i = 0; i < line.size(); i++){
            c = line[i];
            
            if(isalpha(c)){
                string word;
                while(i < line.size() && isalpha(line[i])){
                    word += line[i];
                    i++;
                }
                i--; //因為外層迴圈會再加一次
                cout << word;
                words.push_front(word); //加到串列最前面
            }

            
            else if(isdigit(c)){
                string num;
                while(i < line.size() && isdigit(line[i])){
                    num += line[i];
                    i++;
                }
                i--; 
                int index = stoi(num); //stringtointeger
                if(index >= 1 && index <= words.size()){
                    auto target = next(words.begin(), index - 1); //next(起始位置, 走幾步)
                    cout << *target; //*指標: 取出元素
                    words.splice(words.begin(), words, target); //splice: 用於單雙向串列搬移元素(目標位置, 目標串列, 目前位置)
                }
            }

            
            else{
                cout << c;
            }
        }
    }
    return 0;
}
