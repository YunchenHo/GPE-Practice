//有前序中序可重建二元樹，直接印出後序
//前序: VLR； 中序: LVR; 後序: LRV

//核心概念: 可以使用字串分割
//(preorder片段, inorder片段) 是一棵子樹的另一種表示法，跟一串用指標串起來的節點是等價的兩種包裝方式
//所以不用重新建樹(用struct跟list......)再印出後序，n很小(n<=26)可用遞迴不會超時，不用用堆疊跟迴圈

/*
虛擬碼架構:
void solve(string pre, string in) {
    if (pre 是空字串) return;          // 遞迴終止條件：這個子樹沒有節點

    char root = pre[0];                 // 前序第一個字元 = 這棵(子)樹的根
    int pos = in.find(root);            // 在中序裡找根的位置

    string leftIn  = in 的 [0, pos) 那一段;
    string rightIn = in 的 [pos+1, 結尾) 那一段;

    string leftPre  = pre 的 [1, 1+leftIn.size()) 那一段;   // 長度要跟leftIn一樣
    string rightPre = pre 的 [1+leftIn.size(), 結尾) 那一段;

    solve(leftPre, leftIn);     // 先處理左子樹
    solve(rightPre, rightIn);   // 再處理右子樹
    cout << root << ' ';        // 最後才印根（後序：左、右、根）
}
*/

/*
實際運行:
進入 solve("ABDEFCG","DBFEAGC")
  根=A → 切出 左(BDEF,DBFE) 右(CG,GC)
  --先遞迴左子樹--
    進入 solve("BDEF","DBFE")
      根=B → 切出 左(D,D) 右(EF,FE)
      --先遞迴左子樹--
        進入 solve("D","D")
          根=D → 左右都空，直接return
        >>> 印出 D <<<
      --再遞迴右子樹--
        進入 solve("EF","FE")
          根=E → 切出 左(F,F) 右(空)
          --先遞迴左子樹--
            進入 solve("F","F") → 根=F，左右都空
            >>> 印出 F <<<
          --再遞迴右子樹-- (空，直接return)
        >>> 印出 E <<<
    >>> 印出 B <<<
  --再遞迴右子樹--
    進入 solve("CG","GC")
      根=C → 切出 左(G,G) 右(空)
      --先遞迴左子樹--
        進入 solve("G","G") → 根=G，左右都空
        >>> 印出 G <<<
      --再遞迴右子樹-- (空，直接return)
    >>> 印出 C <<<
  >>> 印出 A <<<

最終後序結果：D F E B G C A
*/

#include <iostream>
#include <string>
using namespace std;

void solve(string prefix, string infix){
    //終止條件: 如果prefix/infix為空，這個子樹沒有節點，遞迴結束
    if(prefix.empty() || infix.empty()){
        return;
    } 
    
    char root = prefix[0]; //在前序字串取根
    int findroot = infix.find(root); //在中序字串中找root的位置，回傳整數位置(0, 1, 2......)
    
    //找左子樹跟右子樹
    string leftinfix = infix.substr(0, findroot - 0);
    string rightinfix = infix.substr(findroot + 1);

    string leftprefix = prefix.substr(1, leftinfix.size()); //長度跟leftinfix一樣
    string rightprefix = prefix.substr(leftinfix.size()+1); //長度跟rightinfix一樣

    //做遞迴
    solve(leftprefix, leftinfix);//先做左子樹
    solve(rightprefix, rightinfix);//再做右子樹
    cout << root << " ";
}

int main(){
    int m;
    cin >> m;
    while(m--){
        int n;
        cin >> n;
        //注意: getline(cin, prefix) 會把整行（含空白）都讀進 prefix，導致字串長度錯誤
        string prefix = "";
        string infix = "";
        
        for(int i = 0; i < n; i++){
            char node;
            cin >> node;
            prefix += node;
        }
        for(int i = 0; i < n; i++){
            char node;
            cin >> node;
            infix += node;
        }

        //呼叫solve函式得到postfix
        solve(prefix, infix);
        cout << endl;
    }
    return 0;
}