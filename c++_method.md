# C++ 容器與方法整理

> 練習解題時遇到的常用方法、語法、演算法套路都記錄在這裡，方便查對照。

## 📖 使用說明（維護這份文件的方式）

這份文件用**標題階層**分組（`##` 大分類 → `###` 小節 → `####` 細節），在 Typora 裡把滑鼠移到任一標題左邊會出現摺疊箭頭，點下去就能收合/展開那個標題底下的所有內容，不需要任何額外語法。之後要新增內容時：
- 如果是**現有分類裡的新方法/新地雷** → 直接找到對應的 `##` 大分類，在裡面對應的 `###`/`####` 小節底下新增（例如新學到 `vector` 的方法，就加進「📦 資料結構」底下的 `### Vector` 小節）
- 如果是**全新的演算法主題**（目前沒有分類放得下）→ 在對應大分類最後面新增一個 `###` 小節；如果連大分類都沒有，就在檔案最下面（`## 待補充` 之前）新增一個全新的 `##` 大分類
- **待補充** 區塊放目前還沒寫但已知之後會用到的項目，寫完了就從清單移除、變成正式的一個小節

---

## 📑 目錄

- 📦 資料結構（Array / Vector / List / String / pair / tuple / set / map / stack / queue / deque）
- 🧰 常用標頭檔函式（iomanip / cmath / algorithm / numeric / sstream）
- ⚙️ 語言基礎與常見輸入地雷（`cin`/`getline`、`*`與`&`、函式參數傳遞）
- 🧭 圖論走訪（DFS / BFS，含一般圖鄰接表、最短路徑）
- 🌳 樹的遍歷（Preorder / Inorder / Postorder）
- 💡 動態規劃（DP 基礎、背包、賽局 DP、換零錢、LIS、LCS）
- 🔍 演算法技巧（二分搜、幾何共線、質數篩法、排列組合）
- 📝 待補充

---

## 📦 資料結構（Array / Vector / List / String / pair / tuple / set）

### Array

#### C-style array（原生陣列）
宣告時大小固定，沒有成員函式可用，常搭配 `sizeof` 算長度。

```cpp
int arr[5] = {1, 2, 3, 4, 5};
int len = sizeof(arr) / sizeof(arr[0]); // 元素個數
```

#### std::array（`#include <array>`）
固定大小，但有 STL 風格的成員函式，比原生陣列安全。

| 方法 | 說明 | 範例 | 複雜度 |
|---|---|---|---|
| `.size()` | 回傳元素個數 | `arr.size()` | O(1) |
| `.at(i)` | 存取第 i 個，會做邊界檢查 | `arr.at(2)` | O(1) |
| `[i]` | 存取第 i 個，不檢查邊界 | `arr[2]` | O(1) |
| `.front()` / `.back()` | 第一個 / 最後一個元素 | `arr.front()` | O(1) |
| `.fill(val)` | 全部填成同一個值 | `arr.fill(0)` | O(n) |
| `.data()` | 取得底層原生陣列的指標（要跟 C 風格函式介接時用） | `arr.data()` | O(1) |
| `.begin()` / `.end()` | 迭代器，範圍 for 或搭配 `<algorithm>` | `sort(arr.begin(), arr.end())` | - |

```cpp
#include <array>
array<int, 5> arr = {5, 3, 1, 4, 2};
sort(arr.begin(), arr.end());
```

---

### Vector（`#include <vector>`）
動態陣列，最常用的容器，記憶體連續、隨機存取快。

| 方法 | 說明 | 範例 | 複雜度 |
|---|---|---|---|
| `.push_back(x)` | 尾端新增元素 | `v.push_back(10)` | 攤銷 O(1) |
| `.pop_back()` | 移除最後一個元素 | `v.pop_back()` | O(1) |
| `.emplace_back(args...)` | 直接在尾端建構元素，省去複製 | `v.emplace_back(1, 2)` | 攤銷 O(1) |
| `.insert(it, x)` | 在指定位置插入 | `v.insert(v.begin()+1, x)` | O(n) |
| `.erase(it)` | 刪除指定位置元素 | `v.erase(v.begin())` | O(n) |
| `.erase(it1, it2)` | 刪除一段範圍 | `v.erase(v.begin(), v.begin()+3)` | O(n) |
| `.size()` | 目前元素個數 | `v.size()` | O(1) |
| `.empty()` | 是否為空 | `v.empty()` | O(1) |
| `.clear()` | 清空所有元素 | `v.clear()` | O(n) |
| `.front()` / `.back()` | 第一個 / 最後一個元素 | `v.front()` | O(1) |
| `.at(i)` / `[i]` | 存取第 i 個（`.at` 會邊界檢查） | `v.at(2)` | O(1) |
| `.resize(n)` | 改變大小（多的補預設值，少的截斷） | `v.resize(10)` | O(n) |
| `.reserve(n)` | 預先配置容量，避免重複搬移 | `v.reserve(100)` | O(n) |
| `.capacity()` | 目前配置的容量 | `v.capacity()` | O(1) |
| `.data()` | 取得底層連續記憶體的指標 | `v.data()` | O(1) |
| `.begin()` / `.end()` | 正向迭代器 | `for (auto it = v.begin(); ...)` | - |
| `.rbegin()` / `.rend()` | 反向迭代器 | `for (auto it = v.rbegin(); ...)` | - |
| `swap(v1, v2)` | 交換兩個 vector 內容 | `v1.swap(v2)` | O(1) |
| `vector<T> v(n)` | **建立時**指定大小，元素全部填該型別的預設值（`string`→空字串、`int`→0） | `vector<string> v(m+1)` | O(n) |
| `vector<T> v(n, val)` | 建立時指定大小與初始值 | `vector<int> v(5, -1)` | O(n) |

> 地雷提醒：如果 vector 是拿來「累積歷史紀錄」用的（例如 e567 用 `arr2` 記錄每一條指令做過什麼），要宣告在迴圈**外面**（每組測資建立一次），千萬不要宣告在迴圈**裡面**——不然每跑一次迴圈就會重新建立、把之前存的資料全部洗掉，等於失憶。

搭配 `<algorithm>` 常用：

```cpp
sort(v.begin(), v.end());                       // 排序
reverse(v.begin(), v.end());                     // 反轉
auto it = find(v.begin(), v.end(), target);      // 線性搜尋，O(n)
int cnt = count(v.begin(), v.end(), target);     // 計算出現次數
```

**`vector<vector<T>>` 的常見用途**：不只能存 2D 網格（棋盤、地圖），也很常拿來當**圖的鄰接表**（每個節點對應一個 vector，存它連到哪些節點），詳見「圖論走訪」章節。

---

### List（`#include <list>`）
雙向鏈結串列，任意位置插入/刪除都是 O(1)（前提是已經有迭代器指到那個位置），但**不支援隨機存取**（沒有 `[i]`）。

| 方法 | 說明 | 範例 | 複雜度 |
|---|---|---|---|
| `.push_back(x)` / `.push_front(x)` | 尾端 / 前端新增 | `lst.push_front(x)` | O(1) |
| `.pop_back()` / `.pop_front()` | 移除尾端 / 前端 | `lst.pop_front()` | O(1) |
| `.insert(it, x)` | 在迭代器位置前插入 | `lst.insert(it, x)` | O(1) |
| `.erase(it)` | 刪除迭代器指到的元素 | `lst.erase(it)` | O(1) |
| `.splice(pos, other, it)` | 把 `other` 中 `it` 指到的元素搬到 `pos` 前面（不複製，直接接鏈） | `lst.splice(lst.begin(), lst, it)` | O(1) |
| `.remove(val)` | 刪除所有等於 val 的元素 | `lst.remove(3)` | O(n) |
| `.unique()` | 移除**連續**重複的元素 | `lst.unique()` | O(n) |
| `.sort()` | 排序（list 專用的成員函式，因為沒有隨機存取，不能用 `std::sort`） | `lst.sort()` | O(n log n) |
| `.reverse()` | 反轉整個 list | `lst.reverse()` | O(n) |
| `.merge(other)` | 合併兩個**已排序**的 list | `lst.merge(other)` | O(n) |
| `.size()` / `.empty()` / `.clear()` | 個數 / 是否空 / 清空 | `lst.size()` | O(1)/O(1)/O(n) |
| `.front()` / `.back()` | 第一個 / 最後一個元素 | `lst.front()` | O(1) |
| `next(it, n)` | 從迭代器往後走 n 步（`<iterator>`） | `next(lst.begin(), 2)` | O(n)（list 是雙向鏈結，沒有隨機跳躍） |

> `.splice()` 是實作 **Move-To-Front (MTF)** 這類「把某個元素搬到最前面」邏輯的關鍵方法，e569 這題就是用它。

```cpp
#include <list>
#include <iterator>
list<string> words;
auto target = next(words.begin(), index - 1); // 找到第 index 個元素
words.splice(words.begin(), words, target);   // 搬到最前面，O(1)
```

---

### String（`#include <string>`）

| 方法 | 說明 | 範例 | 複雜度 |
|---|---|---|---|
| `.size()` / `.length()` | 字串長度 | `s.size()` | O(1) |
| `.empty()` | 是否為空字串 | `s.empty()` | O(1) |
| `[i]` / `.at(i)` | 存取第 i 個字元（`.at` 會邊界檢查） | `s.at(0)` | O(1) |
| `.front()` / `.back()` | 第一個 / 最後一個字元 | `s.back()` | O(1) |
| `.push_back(c)` | 尾端加一個字元 | `s.push_back('!')` | 攤銷 O(1) |
| `.pop_back()` | 刪除最後一個字元 | `s.pop_back()` | O(1) |
| `+=` / `.append(s2)` | 字串相加 | `s += "abc"` | O(n) |
| `.substr(pos, len)` | 取子字串（`len` 省略則到結尾） | `s.substr(1, 3)` | O(len) |
| `.find(sub)` | 找子字串位置，找不到回傳 `string::npos` | `s.find("abc")` | O(n*m) |
| `.rfind(sub)` | 從後面找子字串 | `s.rfind("abc")` | O(n*m) |
| `.replace(pos, len, s2)` | 取代一段字串 | `s.replace(0, 3, "xyz")` | O(n) |
| `.insert(pos, s2)` | 在指定位置插入字串 | `s.insert(2, "ab")` | O(n) |
| `.erase(pos, len)` | 刪除一段字串 | `s.erase(0, 3)` | O(n) |
| `.clear()` | 清空字串 | `s.clear()` | O(n) |
| `.c_str()` | 轉成 C 風格字串（`const char*`） | `printf("%s", s.c_str())` | O(1) |
| `.compare(s2)` | 字典序比較（也可直接用 `==` `<` `>`） | `s.compare(s2)` | O(n) |
| `string(n, c)` | 建立一個由同一個字元重複 n 次組成的字串 | `string(5, '-')` → `"-----"` | O(n) |
| `stoi(s)` / `stol(s)` / `stoll(s)` / `stod(s)` | 字串轉整數/長整數/長長整數/浮點數 | `long long x = stoll("123456789012")` | O(n) |
| `to_string(x)` | 數字轉字串 | `string s = to_string(123)` | O(n) |
| `getline(cin, s)` | 讀一整行（含空白），需要 `<string>` | `getline(cin, line)` | O(n) |

搭配 `<cctype>` 判斷字元型態（單一 `char`，非 string 的方法，但很常一起用）：

| 函式 | 說明 |
|---|---|
| `isalpha(c)` | 是否為英文字母 |
| `isdigit(c)` | 是否為數字字元 |
| `isspace(c)` | 是否為空白（空格、tab、換行等） |
| `isupper(c)` / `islower(c)` | 是否為大寫 / 小寫 |
| `toupper(c)` / `tolower(c)` | 轉大寫 / 小寫 |

常見小技巧：

```cpp
// 去掉 getline 讀到行尾殘留的 \r（Windows 換行造成）
if (!line.empty() && line.back() == '\r') line.pop_back();

// 逐字元掃描累積連續字母/數字成一個 token（e569 用到的手法）
while (i < line.size() && isalpha(line[i])) { word += line[i]; i++; }
```

---

### pair：把兩個值綁在一起（`#include <utility>`，通常 `<vector>`/`<map>` 會自動帶進來）

把兩個值包成一個整體，很常拿來存「座標點 (x,y)」、「鍵值對」這類天生成對出現的資料，可以直接放進 `vector` 裡變成 `vector<pair<T1,T2>>`，一個元素就是一組完整的資料。

| 用法 | 說明 | 範例 |
|---|---|---|
| `pair<int,int> p;` | 宣告，兩個位置型別可以不同 | `pair<int,string> p;` |
| `make_pair(a, b)` | 建立一個 pair | `auto p = make_pair(1, 2);` |
| `{a, b}` | 用大括號初始化，效果跟 `make_pair` 一樣，更常用 | `pair<int,int> p = {1, 2};` |
| `.first` / `.second` | 取出第一個 / 第二個值 | `p.first`、`p.second` |

```cpp
#include <vector>
vector<pair<int,int>> pts(n);        // 存 n 個座標點，pts[i] 就是第i個點的 (x,y)
for (int i = 0; i < n; i++) {
    cin >> pts[i].first >> pts[i].second;   // 直接讀進 .first/.second
}

int x1 = pts[i].first, y1 = pts[i].second;   // 用索引拿出第i個點，再拆開x,y
```

**跟 `tuple` 的差異**：`pair` 固定只能包 2 個值，`tuple` 可以包任意數量。剛好只需要兩個值（例如座標、或某個「值+來源位置」的組合）時，`pair` 比較常見、寫法也比較短；需要 3 個以上的值（像這題的線方程式 `A,B,C`）才需要 `tuple`。

`pair` 也跟 `tuple` 一樣內建支援 `==`、`<` 比較（先比 `.first`，相同才比 `.second`），可以直接當 `set`/`map` 的 key，或直接丟進 `sort()` 排序（預設會先照 `.first` 排序）。

---

### tuple：把好幾個值包成一個整體（`#include <tuple>`）

`pair` 只能包兩個值，`tuple` 可以包**任意數量**的值，各自型別也可以不同。最常見的用途是**當作 `set`/`map` 的 key**，把好幾個條件包成一個整體去做排序或去重比較。

| 方法 | 說明 | 範例 |
|---|---|---|
| `make_tuple(a, b, c)` | 建立一個 tuple | `auto t = make_tuple(1, 2, 3)` |
| `tuple<int,int,int> t` | 宣告型別，各個位置的型別可以不同 | `tuple<int,string,double> t` |
| `get<i>(t)` | 取出 tuple 第 i 個元素（i 從0開始，編譯期就要決定，不能用變數） | `get<0>(t)` |
| `auto [a, b, c] = t;` | C++17 結構化綁定，一次拆出所有元素存成獨立變數 | 見下方範例 |

```cpp
#include <tuple>
tuple<int,int,int> t = make_tuple(1, -1, 0);
cout << get<0>(t);          // 1

auto [A, B, C] = t;         // 結構化綁定，直接拆成三個變數用
```

**`tuple` 之間怎麼比較大小/怎麼判斷相等**：`tuple` 內建就支援 `==`、`<` 這些比較運算子，規則是**由左到右依序比較**（先比第一個元素，相同才比第二個，以此類推，跟字典排序邏輯一樣）。這個特性讓 `tuple` 可以直接丟進 `set<tuple<...>>` 或當 `map` 的 key，不用自己額外寫比較函式。

---

### set：自動排序、自動去重的容器（`#include <set>`）

跟 `vector` 最大的差異：`set` 裡的元素**永遠保持排序**，而且**不能有重複元素**——插入一個已經存在的值，`set` 會直接忽略，不會變成兩份。這個特性非常適合「數不重複的東西有幾個」這類題目。

| 方法 | 說明 | 範例 | 複雜度 |
|---|---|---|---|
| `.insert(x)` | 插入元素，重複的值會被自動忽略 | `s.insert(5)` | O(log n) |
| `.erase(x)` | 刪除值為 x 的元素 | `s.erase(5)` | O(log n) |
| `.count(x)` | 回傳 x 出現幾次（因為不重複，結果只會是 0 或 1，常拿來當「有沒有存在」用） | `s.count(5)` | O(log n) |
| `.find(x)` | 回傳指到 x 的迭代器，找不到回傳 `.end()` | `s.find(5)` | O(log n) |
| `.lower_bound(x)` / `.upper_bound(x)` | `set` **自己的成員函式**，在 set 內部找第一個 ≥x／>x 的位置 | `s.lower_bound(5)` | O(log n) |
| `.size()` | 元素個數（也就是不重複元素的總數） | `s.size()` | O(1) |
| `.empty()` | 是否為空 | `s.empty()` | O(1) |
| `.begin()` / `.end()` | 迭代器，由小到大走訪（因為 `set` 內部自動排序） | `for (auto x : s)` | - |

```cpp
#include <set>
set<int> s;
s.insert(5);
s.insert(3);
s.insert(5);        // 重複插入，會被忽略
cout << s.size();   // 輸出 2，不是 3
```

**地雷提醒**：`set` 有自己的 `.lower_bound()`/`.upper_bound()` 成員函式，跟 `<algorithm>` 裡的 `lower_bound(first,last,val)` 是**兩個不同的東西**——`set` 的迭代器不支援隨機存取，如果誤用 `<algorithm>` 的版本（`lower_bound(s.begin(), s.end(), x)`），效率會退化成 O(n log n) 甚至更差；一定要用 `s.lower_bound(x)` 這個成員函式版本，才會是正確的 O(log n)。

**判斷原則**：題目要「數不重複的東西有幾種」，或需要「邊插入邊自動保持排序」，就想到 `set`。如果不需要排序、只需要快速判斷「有沒有出現過」，`unordered_set`（雜湊版本，平均 O(1)）通常更快，但沒有自動排序、走訪順序不固定。

---

### map：key-value 的對照表（`#include <map>`）

跟 `set` 是同一個家族（內部一樣是排序好的樹狀結構），差別是 `set` 只存「值」，`map` 存的是「鍵 → 值」的配對，很適合拿來當字典查表，或統計每個值出現的次數。

| 方法 | 說明 | 範例 | 複雜度 |
|---|---|---|---|
| `m[key]` | 存取/新增 `key` 對應的值，`key` 不存在時會**自動建立**（值預設為0/空字串等） | `m['a']++;` | O(log n) |
| `.insert({k, v})` | 插入一組鍵值對，如果 `key` 已存在則不會覆蓋 | `m.insert({1, "a"});` | O(log n) |
| `.erase(key)` | 刪除某個 key 對應的整組資料 | `m.erase(1);` | O(log n) |
| `.count(key)` | 這個 key 存不存在（回傳0或1） | `m.count(1)` | O(log n) |
| `.find(key)` | 回傳指到該 key-value 的迭代器，找不到回傳 `.end()` | `m.find(1)` | O(log n) |
| `.lower_bound(key)` / `.upper_bound(key)` | `map` 自己的成員函式，找第一個 ≥key／>key 的位置（原理跟 `set` 一樣） | `m.lower_bound(5)` | O(log n) |
| `.size()` / `.empty()` | 目前有幾組資料 / 是否為空 | `m.size()` | O(1) |
| `.begin()` / `.end()` | 迭代器，依 key **由小到大**走訪 | `for (auto& [k, v] : m)` | - |

```cpp
#include <map>
map<char, int> freq;      // 統計字元出現次數的經典寫法
for (char c : s) freq[c]++;   // key不存在時自動變成0，++之後變1

for (auto& [k, v] : freq) {   // 結構化綁定，直接拆成key跟value
    cout << k << ": " << v << "\n";
}
```

**地雷提醒**：用 `m[key]` 讀取一個**不存在**的 key 時，`map` 會**自動幫你建立**這個 key（值給預設值），這個副作用有時候會不小心影響 `.size()`（多了一筆不是你本意要新增的資料）。如果只是想「檢查存不存在」，不想意外新增，要用 `m.count(key)` 或 `m.find(key)`，不要直接用 `m[key]` 去試探。

**判斷原則**：需要「依 key 排序」或需要 `.lower_bound()` 這種二分搜功能 → `map`；只需要快速查表、不在乎順序 → `unordered_map`（平均 O(1)，比 `map` 的 O(log n) 快，但走訪順序不固定）。

---

### stack：後進先出（LIFO）（`#include <stack>`）

跟 DFS/BFS 章節用到的 `stack` 是同一個容器，這裡整理成通用容器介紹（DFS 迭代版的完整範例在「圖論走訪」章節）。

| 方法 | 說明 | 範例 |
|---|---|---|
| `.push(x)` | 放進堆疊頂端 | `st.push(x)` |
| `.pop()` | 移除頂端元素（不回傳值） | `st.pop()` |
| `.top()` | 讀取頂端元素（不移除） | `st.top()` |
| `.empty()` | 是否為空 | `st.empty()` |
| `.size()` | 元素個數 | `st.size()` |

**常見用途**：
- DFS 迭代版（見「圖論走訪」章節）
- **括號匹配**：遇到左括號就 push，遇到右括號就檢查 `top()` 是否配對、配對就 pop，最後 stack 要清空才算合法
- **運算式求值 / 中序轉後序**：計算機常見題型，用 stack 暫存還沒處理完的運算子或數字

```cpp
// 括號匹配的經典寫法
stack<char> st;
for (char c : s) {
    if (c == '(') st.push(c);
    else if (c == ')') {
        if (st.empty()) { /* 不合法：多了右括號 */ }
        st.pop();
    }
}
bool valid = st.empty();   // 跑完之後stack是空的，才算全部配對成功
```

---

### queue：先進先出（FIFO）（`#include <queue>`）

跟 DFS/BFS 章節用到的 `queue` 是同一個容器，這裡整理成通用容器介紹（BFS 的完整範例在「圖論走訪」章節）。

| 方法 | 說明 | 範例 |
|---|---|---|
| `.push(x)` | 放進佇列尾端 | `q.push(x)` |
| `.pop()` | 移除最前面的元素（不回傳值） | `q.pop()` |
| `.front()` | 讀取最前面的元素（不移除） | `q.front()` |
| `.back()` | 讀取最後面的元素 | `q.back()` |
| `.empty()` | 是否為空 | `q.empty()` |
| `.size()` | 元素個數 | `q.size()` |

**常見用途**：BFS（見「圖論走訪」章節）、模擬「排隊、輪流處理」的情境（例如模擬多個工作依序輪流執行）。

---

### deque：雙端佇列（`#include <deque>`）

念作 "deck"，是 `vector` 跟 `list` 的中間形態：**兩端都能 O(1) 新增/刪除**（`vector` 只有尾端是 O(1)），同時**支援 `[i]` 隨機存取**（`list` 不支援）。

| 方法 | 說明 | 範例 | 複雜度 |
|---|---|---|---|
| `.push_back(x)` / `.push_front(x)` | 尾端 / 前端新增 | `dq.push_front(x)` | O(1) |
| `.pop_back()` / `.pop_front()` | 移除尾端 / 前端 | `dq.pop_front()` | O(1) |
| `.front()` / `.back()` | 第一個 / 最後一個元素 | `dq.front()` | O(1) |
| `[i]` | 隨機存取第 i 個元素 | `dq[2]` | O(1) |
| `.size()` / `.empty()` | 個數 / 是否為空 | `dq.size()` | O(1) |

**常見用途**：**滑動視窗最大值/最小值**（單調隊列，monotonic deque）——維護一個「從頭到尾遞減（或遞增）」的 deque，新元素從尾端加入前，先把比它小（或大）的元素從尾端踢掉，這樣頭永遠是目前視窗內的最大值（或最小值）；也適合當「兩端都要進出」的佇列，例如需要 `push_front` 功能時，比 `queue`（只能從一端進、另一端出）更靈活。

```cpp
#include <deque>
deque<int> dq;
dq.push_back(1);
dq.push_front(0);
dq.push_back(2);
// dq 現在是 [0, 1, 2]，可以直接用 dq[1] 拿到 1
```


---

## 🧰 常用標頭檔函式（iomanip / cmath / algorithm / numeric / sstream）

### iomanip：格式化輸出（`#include <iomanip>`）

控制 `cout` 輸出的寬度、對齊、小數位數，題目要求「靠右對齊、固定欄寬」時（像找零問題的輸出格式）幾乎一定會用到。

| 方法              | 說明                                                         | 範例                                    | 效果                |
| ----------------- | ------------------------------------------------------------ | ---------------------------------------- | ------------------- |
| `setw(n)`         | 設定**下一個**輸出的欄寬為 n 個字元，不足處預設**靠右對齊、左側補空白**（只影響緊接著的下一個輸出，每次都要重打） | `cout << setw(6) << 5;`                 | `"     5"`          |
| `setfill(c)`      | 設定 `setw` 補的字元（預設是空白），設定後**會持續生效**直到下次改變 | `cout << setfill('0') << setw(4) << 5;` | `"0005"`            |
| `fixed`           | 切換成「固定小數位數」模式，設定後**會持續生效**，之後浮點數輸出都套用，不會再自動省略末尾的 0 | `cout << fixed;`                        | -                   |
| `setprecision(n)` | 搭配 `fixed` 使用時，代表小數點後固定印幾位；不搭配 `fixed` 單獨用則是控制總有效位數 | `cout << fixed << setprecision(2);`     | `2.5` 印成 `"2.50"` |
| `left` / `right`  | 設定 `setw` 補空白的對齊方向（預設就是 `right` 靠右對齊）    | `cout << left << setw(6) << 5;`         | `"5     "`          |

**地雷提醒**：`cout` 印浮點數預設是「有效位數模式」，會自動省略末尾的 0——`double` 值 `2.0` 直接印出來只會是 `"2"`，不是 `"2.00"`。如果題目要求固定小數位數（例如金額一定要印 2 位小數），**一定要加 `fixed << setprecision(2)`**，只用 `setw` 控制寬度是不夠的（`setw` 只管欄寬，不管小數位數）。

```cpp
cout << fixed << setprecision(2);   // 通常設定一次，之後所有浮點數輸出都固定小數點後2位
cout << setw(6) << money;           // 每次輸出前都要重新指定寬度（setw不像fixed/setfill會持續生效）
cout << setw(17) << count << endl;  // 這裡印的是整數，不受 fixed/setprecision 影響，只有 setw 的欄寬生效
```

---

### cmath：數學函式（`#include <cmath>`）

| 函式        | 說明                                                         | 範例                      |
| ----------- | ------------------------------------------------------------ | ------------------------- |
| `round(x)`  | 四捨五入到最近的整數（回傳 `double`），常用來修正浮點數精度誤差 | `round(2.999999)` → `3.0` |
| `floor(x)`  | 無條件捨去到比 x 小或等於的最大整數                          | `floor(2.7)` → `2.0`      |
| `ceil(x)`   | 無條件進位到比 x 大或等於的最小整數                          | `ceil(2.1)` → `3.0`       |
| `fabs(x)`   | 浮點數取絕對值（整數用 `<cstdlib>` 的 `abs`）                | `fabs(-2.5)` → `2.5`      |
| `pow(x, y)` | x 的 y 次方，回傳 `double`                                   | `pow(2, 10)` → `1024.0`   |
| `sqrt(x)`   | 開平方根                                                     | `sqrt(16)` → `4.0`        |

**地雷提醒 1**：`round`/`floor`/`ceil`/`sqrt`/`pow` 都回傳 `double`，如果要存進整數變數，記得手動轉型：

```cpp
int amount = (int)round(money * 20);
```

這也是這題（d397）用來避開浮點數誤差的關鍵：`money * 20` 因為浮點數表示法可能有微小誤差（例如理論上該是 `4.0` 卻存成 `3.9999999`），如果直接 `(int)` 強制轉型會**無條件捨去**（等於變成 `3`，算錯！），所以要先 `round()` 四捨五入把誤差修正掉，再轉型。**這件事跟要轉成 `int` 還是 `long long` 無關**——不管轉哪種整數型別，浮點數誤差都得先用 `round()` 修正。

**地雷提醒 2**：轉型要選 `int` 還是 `long long`，看的是**這個變數實際會存到多大的值**，不是看它「跟哪個大數字有關」就跟著用大的型別。以 d397 這題為例：

```cpp
int amount = (int)round(money * 20);   // amount 只是拿來當「索引」，範圍0~6000，int 就夠
vector<long long> dp(6001);            // dp[] 存的「方法數」本身會大到超過 int（例如181490736388615），這裡才需要 long long
```

容易搞混的地方：因為 `dp[amount]` 這個值很大，會直覺覺得「跟它有關的變數都要開 `long long`」，但其實**索引**（`amount`）和**陣列存的內容**（`dp[amount]`）是兩件独立的事，各自看自己實際的數值範圍決定型別就好。把 `amount` 開成 `long long` 不會出錯（`vector` 索引接受任何整數型別），只是型別選得比實際需要大，多佔了不必要的記憶體。

---

### algorithm：常用函式（`#include <algorithm>`）

| 函式                                                    | 說明                                                         | 範例                                                    | 複雜度     |
| ------------------------------------------------------- | ------------------------------------------------------------ | ------------------------------------------------------- | ---------- |
| `max(a, b)` / `min(a, b)`                               | 兩者取大 / 取小                                              | `max(3, 5)` → `5`                                       | O(1)       |
| `swap(a, b)`                                            | 交換兩個變數的值                                             | `swap(x, y)`                                            | O(1)       |
| `sort(first, last)`                                     | 由小到大排序                                                 | `sort(v.begin(), v.end())`                              | O(n log n) |
| `sort(first, last, cmp)`                                | 自訂排序規則（`cmp` 回傳 true 代表第一個排前面）             | `sort(v.begin(), v.end(), greater<int>())` （由大到小） | O(n log n) |
| `reverse(first, last)`                                  | 反轉範圍內的順序                                             | `reverse(v.begin(), v.end())`                           | O(n)       |
| `find(first, last, val)`                                | 線性搜尋，回傳指到目標的迭代器，找不到回傳 `last`            | `find(v.begin(), v.end(), 5)`                           | O(n)       |
| `count(first, last, val)`                               | 計算範圍內等於 val 的個數                                    | `count(v.begin(), v.end(), 5)`                          | O(n)       |
| `unique(first, last)`                                   | 移除範圍內**相鄰**的重複元素（要先排序過才能去掉所有重複），回傳新的邏輯結尾迭代器，實際大小要另外 `erase` 掉多餘部分 | `v.erase(unique(v.begin(), v.end()), v.end())`          | O(n)       |
| `lower_bound(first, last, val)`                         | 在**已排序**範圍裡，找第一個「≥ val」的位置（二分搜尋）      | `lower_bound(v.begin(), v.end(), 5)`                    | O(log n)   |
| `upper_bound(first, last, val)`                         | 在**已排序**範圍裡，找第一個「> val」的位置（二分搜尋）      | `upper_bound(v.begin(), v.end(), 5)`                    | O(log n)   |
| `max_element(first, last)` / `min_element(first, last)` | 回傳範圍內最大值/最小值的**迭代器**（不是值本身，要再 `*` 取值） | `*max_element(v.begin(), v.end())`                      | O(n)       |
| `next_permutation(first, last)`                         | 把範圍改成「字典序下一個排列」，回傳 `false` 代表已經是最後一個排列（沒有下一個了）。用來窮舉所有排列組合 | 見下方範例                                              | O(n)       |

> `lower_bound`/`upper_bound` 只能用在**已經排序過**的資料上，沒排序的話結果不保證正確（這是二分搜尋的前提）。

**`next_permutation` 窮舉所有排列**：一定要先排序過（從最小的排列開始），才能保證跑過所有排列：
```cpp
#include <algorithm>
vector<int> v = {1, 2, 3};
sort(v.begin(), v.end());        // 一定要先排序！
do {
    // 這裡處理目前這個排列 v
} while (next_permutation(v.begin(), v.end()));
```

---

### numeric：數值運算輔助（`#include <numeric>`）

| 函式                            | 說明                                                         | 範例                                | 複雜度   |
| ------------------------------- | ------------------------------------------------------------ | ----------------------------------- | -------- |
| `accumulate(first, last, init)` | 把範圍內的元素全部加總，`init` 是起始值（也可以是乘法等其他運算，帶第4個參數自訂） | `accumulate(v.begin(), v.end(), 0)` | O(n)     |
| `gcd(a, b)`                     | 最大公因數（C++17 起）                                       | `gcd(12, 18)` → `6`                 | O(log n) |
| `lcm(a, b)`                     | 最小公倍數（C++17 起）                                       | `lcm(4, 6)` → `12`                  | O(log n) |

> 容易搞混：`accumulate` 常常跟 `sort`、`max_element` 這些 `<algorithm>` 函式一起用，但它其實屬於**不同的標頭檔** `<numeric>`，要另外 `#include`。

---

### sstream：字串與數值互轉、切割一行裡的多個數字（`#include <sstream>`）

`stringstream` 可以把一個字串包成一個「像 `cin` 一樣可以用 `>>` 讀」的串流，最大用途是：**一行裡有不知道幾個數字**（不像前幾題「第一個數字先告訴你n，後面剛好n個」），這時候不能用固定次數的迴圈讀，要先整行讀進來，再用 `stringstream` 一個一個吐出來，讀到吐不出來為止。

| 用法 | 說明 | 範例 |
|---|---|---|
| `stringstream ss(s);` | 用字串 `s` 建立一個字串流 | `stringstream ss("3 5 7");` |
| `ss >> x` | 從串流讀出下一個空白分隔的 token，自動轉型 | `int x; ss >> x;` |
| `while (ss >> x) {...}` | 不知道有幾個數字時，讀到讀不到為止（跟 `while(cin>>x)` 讀到EOF邏輯一樣） | 見下方範例 |
| `getline(ss, token, ',')` | 用自訂分隔字元切出一段（不是空白），常用來切CSV | 見下方範例 |
| `ss.str()` | 取出字串流目前存的內容 | 拿來做「數字/多個值 → 字串」 |

```cpp
#include <sstream>
string line;
getline(cin, line);              // 先把整行讀進來（含所有數字）
stringstream ss(line);
vector<int> nums;
int x;
while (ss >> x) nums.push_back(x);   // 不管這行有幾個數字，全部讀出來
```

```cpp
// 用自訂分隔字元切字串（例如逗號分隔的資料）
stringstream ss("apple,banana,cherry");
string token;
vector<string> parts;
while (getline(ss, token, ',')) parts.push_back(token);
// parts = {"apple", "banana", "cherry"}
```

**跟前面 `cin>>`/`getline` 混用地雷的關係**：`stringstream` 正是那個問題的**解法之一**——遇到「一行裡有不確定數量的資料」，標準做法是先用 `getline(cin, line)` 把整行讀完，再用 `stringstream` 重新解析這一行的內容，這樣完全不會有 `cin>>` 跟 `getline` 混用時「殘留換行符」的問題（因為兩次讀取分別作用在不同的串流上，`cin` 跟 `ss` 互不干擾）。


---

## ⚙️ 語言基礎與常見輸入地雷（cin/getline、指標與參考、函式參數傳遞）

### `cin >>` 和 `getline` 混用

| 方法 | 說明 | 範例 | 複雜度 |
|---|---|---|---|
| `cin.ignore(n, delim)` | 從輸入串流丟棄最多 n 個字元，遇到 `delim` 就提前停止（也會把 `delim` 本身吃掉丟棄） | `cin.ignore(10000, '\n')` | O(n) |
| `cin.ignore()` | 不帶參數＝只丟棄 1 個字元 | `cin.ignore();` | O(1) |

**地雷成因**：`cin >> x` 只會讀走數值本身，**不會**吃掉後面按 Enter 留下的換行字元 `\n`，游標會停在 `\n` 的正前方。如果接下來馬上呼叫 `getline(cin, s)`，`getline` 會立刻遇到那個殘留的 `\n`，讀到「從目前位置到 `\n` 之前」= 空字串就結束了，等於**第一次 `getline` 永遠會撲空**。

```cpp
int m;
cin >> m;                     // 讀完數字，\n 還留在緩衝區
cin.ignore(10000, '\n');      // 手動把殘留的 \n 丟掉，之後 getline 才會讀到真正的下一行

string line;
getline(cin, line);           // 現在才會讀到你要的內容
```

> 補充理解：`getline` 讀到分隔字元（預設 `\n`）時，會把這個分隔字元從串流裡**讀走並丟棄**，但**不會**把它存進目標字串裡——所以字串本身永遠不含換行。這跟 `cin.ignore` 的行為機制其實一樣，只是 `ignore` 不儲存讀到的內容，`getline` 會把分隔字元前的內容存起來。

**判斷原則**：只要程式碼裡同時出現 `cin >> 數字/單一個詞` 和 `getline`，且兩者前後緊接著呼叫，中間幾乎都要補一個 `cin.ignore(...)`，否則第一次 `getline` 大概率會讀到空字串。另一個常見解法是改用 `stringstream`（見「常用標頭檔函式」章節），先整行讀完再重新解析，徹底避開這個問題。

---

### `*` 與 `&`：指標、參考、解引用、取址

這兩個符號最容易搞混的地方：**它們在「宣告型別」時和「拿來運算」時，意思完全不一樣**，同一個符號有兩種身份。

| 符號 | 宣告時的身份 | 運算時的身份 |
|---|---|---|
| `&` | 代表「這是一個參考（reference）」，例如 `int& r = x;` | **取址運算子**：`&x` 拿到 x 的記憶體位址 |
| `*` | 代表「這是一個指標（pointer）」，例如 `int* p;` | **解引用（dereference）**：`*p` 從位址 p 挖出裡面實際存的值 |

```cpp
int x = 5;
int& r = x;      // 宣告：r 是 x 的別名，兩個名字指向同一塊記憶體
int* p = &x;      // &x（運算）：取得 x 的位址；宣告 p 是指標，存放這個位址
cout << *p;        // *p（運算）：從 p 存的位址，取出裡面的值 → 印出 5
```

`&` 是「值 → 地址」，`*` 是「地址 → 值」，兩者互為反向操作：`*(&x)` 繞一圈等於 `x` 本身。

**地雷提醒**：宣告參考時右邊**不用**加 `&`（`int& r = x;`，不是 `= &x`）；宣告指標時右邊**要**加 `&` 取址（`int* p = &x;`）。同一個 `&`，出現在型別旁邊（`int&`）是宣告參考，出現在變數前面當運算子（`&x`）是取址，是兩件不同的事。

#### 指標 vs 參考對照
| | 指標 `T*` | 參考 `T&` |
|---|---|---|
| 可不可以是 null | 可以（`nullptr`） | 不行，宣告時就要綁定 |
| 可不可以事後改指向別的變數 | 可以 | 不行，一綁定就固定 |
| 要不要用 `*` 才能拿到值 | 要（`*p`） | 不用，直接當一般變數用 |

#### 對應到你寫過的程式碼
- `void dfs(..., vector<vector<char>>& grid)` → `&` 是**宣告時身份**（reference type），函式參數是原始資料的別名，不是複製一份，詳見下一節
- `*max_element(c.begin(), c.end())` → `*` 是**運算時身份**（dereference）。`max_element` 回傳的是**迭代器**（概念上很像指標，指向「最大值所在的位置」），要用 `*` 把該位置實際存的值取出來，不然拿到的只是「位置」不是「值」
- `list` 那題的 `cout << *target;`（`target` 是 `list` 的迭代器）→ 同樣是 dereference，取出迭代器指到的實際內容

---

### `T` vs `T&` vs `const T&`：函式參數傳遞

寫遞迴（例如 DFS）或任何要傳容器進函式的時候，參數要怎麼宣告，直接影響效能跟會不會動到原始資料。

| 寫法 | 中文說法 | 會不會複製 | 函式內能不能改到原本的變數 | 什麼時候用 |
|---|---|---|---|---|
| `void f(vector<int> v)` | 傳值（call by value） | 會，整個複製一份 | 不會，改的是副本 | 容器很小、或就是想要一份獨立副本 |
| `void f(vector<int>& v)` | 傳址／傳參考（call by reference） | 不會 | 會，直接改到原本的變數 | 容器很大（複製很貴），而且**就是要**修改原資料，例如 DFS 裡直接在 `grid` 上標記已拜訪 |
| `void f(const vector<int>& v)` | 傳唯讀參考（const reference） | 不會 | 不會，編譯器會擋下任何想修改 `v` 的程式碼 | 容器很大不想複製，但**不需要**（也不應該）修改它，只是要讀取內容 |

```cpp
// c129 用的就是這一種：容器很大（100x100 的 grid），
// 而且 DFS 本來就是要在原地把拜訪過的 '@' 改成 '*'，所以用 T&
void dfs(int m, int n, int x, int y, vector<vector<char>>& grid){
    ...
    grid[x][y] = '*';   // 直接改到 main 裡那個 grid，不是改副本
    ...
}
```

**判斷原則**：
- 參數是 `int`、`char`、`bool` 這種基本型別 → 直接傳值就好，複製成本低到可以忽略，不用刻意加 `&`
- 參數是 `vector`、`string`、`map` 這種容器，而且**函式裡不會去改它** → 用 `const T&`（避免複製又保證原始資料安全，最推薦的預設選擇）
- 參數是容器，而且**函式就是要修改原始資料**（像 flood fill 原地標記）→ 用 `T&`


---

## 🧭 圖論走訪（DFS / BFS，含一般圖鄰接表、最短路徑）

### DFS / BFS：圖論走訪

**共同點**：DFS 跟 BFS 都是「從一個起點出發，走遍所有相連的格子/節點」，用在這題是拿來做 **flood fill**（淹沒填色）數連通塊數量。兩者找到的連通塊數量、走到的格子集合完全一樣，**差別只在走訪的順序**。

| 走法 | 用的資料結構 | 走訪順序 | 特色 |
|---|---|---|---|
| DFS（遞迴版） | 呼叫堆疊（call stack，語言內建、大小固定） | 深度優先，一路衝到底再回頭 | 寫起來最短，但格子數很多時有極小機率 stack overflow |
| DFS（迭代版） | `std::stack`（手動維護，heap 記憶體） | 深度優先，跟遞迴版邏輯完全一樣 | 不受呼叫堆疊大小限制，本質上是自己動手做遞迴在做的事 |
| BFS | `std::queue` | 廣度優先，一層一層往外擴散 | 天生不會有堆疊爆掉的問題，常用來求「最短步數」類的題目 |

#### 8 方向 / 4 方向怎麼表示
用兩個陣列存座標偏移量，掃鄰居時跑迴圈：
```cpp
// 8方向（像踩地雷一樣，含斜角）
int dx[8] = {-1,-1,-1, 0,0, 1,1,1};
int dy[8] = {-1, 0, 1,-1,1,-1,0,1};

// 如果只要4方向（上下左右，不含斜角），拿掉斜的即可
int dx4[4] = {-1,1,0,0};
int dy4[4] = {0,0,-1,1};
```

#### DFS 遞迴版
```cpp
void dfs(int m, int n, int x, int y, vector<vector<char>>& grid){
    if(x < 0 || x >= m || y < 0 || y >= n || grid[x][y] != '@') return; // 終止條件
    grid[x][y] = '*';   // 標記已拜訪（原地淹沒，不用額外開 visited 陣列）
    for(int d = 0; d < 8; d++) dfs(m, n, x+dx[d], y+dy[d], grid);
}
```

#### DFS 迭代版（`std::stack`）
| 方法 | 說明 | 範例 |
|---|---|---|
| `.push(x)` | 放進堆疊頂端 | `st.push({i, j})` |
| `.pop()` | 移除頂端元素（不回傳值） | `st.pop()` |
| `.top()` | 讀取頂端元素（不移除） | `st.top()` |
| `.empty()` | 是否為空 | `st.empty()` |
| `.size()` | 元素個數 | `st.size()` |

```cpp
#include <stack>
stack<pair<int,int>> st;
st.push({i, j});
grid[i][j] = '*';                 // 一 push 進去就馬上標記，避免同一格被重複塞入

while (!st.empty()) {
    auto [x, y] = st.top();
    st.pop();
    for (int d = 0; d < 8; d++) {
        int nx = x + dx[d], ny = y + dy[d];
        if (nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny] == '@') {
            grid[nx][ny] = '*';
            st.push({nx, ny});
        }
    }
}
```

#### BFS（`std::queue`）
| 方法 | 說明 | 範例 |
|---|---|---|
| `.push(x)` | 放進佇列尾端 | `q.push({i, j})` |
| `.pop()` | 移除最前面的元素（不回傳值） | `q.pop()` |
| `.front()` | 讀取最前面的元素（不移除） | `q.front()` |
| `.back()` | 讀取最後面的元素 | `q.back()` |
| `.empty()` | 是否為空 | `q.empty()` |
| `.size()` | 元素個數 | `q.size()` |

```cpp
#include <queue>
queue<pair<int,int>> q;
q.push({i, j});
grid[i][j] = '*';

while (!q.empty()) {
    auto [x, y] = q.front();
    q.pop();
    for (int d = 0; d < 8; d++) {
        int nx = x + dx[d], ny = y + dy[d];
        if (nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny] == '@') {
            grid[nx][ny] = '*';
            q.push({nx, ny});
        }
    }
}
```

> `std::stack` 跟 `std::queue` 用法幾乎一樣，**唯一差在拿元素的那一端**：stack 是 `.top()`（後進先出，LIFO），queue 是 `.front()`（先進先出，FIFO），就是這個差異造成 DFS／BFS 走訪順序不同。

**判斷原則**：找連通塊數量（這題）、或單純「有沒有連在一起」→ DFS/BFS 都可以，選好寫的就好；如果題目要問「最少要走幾步」→ 用 BFS，因為 BFS 天生是一層一層擴散，第一次走到終點那一層就是最短距離。

---

#### 用 `vector<vector<int>>` 當一般圖的鄰接表

前面的 DFS/BFS 範例都是「格子/網格」（用 2D 陣列存地圖，鄰居靠 dx/dy 算出來）。但很多題目給的是**點+邊**（例如「n 個節點，m 條邊，每條邊連接u跟v」），這種**一般圖**沒有格子座標，要改用**鄰接表**存：每個節點對應一個 `vector`，裡面放它連到哪些節點。

```cpp
vector<vector<int>> adj(n + 1);   // 節點編號1~n，adj[u]存u連到的所有節點
for (每條邊 (u, v)) {
    adj[u].push_back(v);
    adj[v].push_back(u);          // 如果是雙向邊，兩邊都要加
}
```

DFS/BFS 掃鄰居的地方，從「掃 dx/dy 8個方向」換成「掃 `adj[cur]` 這個 vector 裡的每個節點」，其他邏輯（標記已拜訪、遞迴/佇列）完全一樣：

```cpp
vector<bool> visited(n + 1, false);
void dfs(int cur, const vector<vector<int>>& adj, vector<bool>& visited) {
    visited[cur] = true;
    for (int next : adj[cur]) {
        if (!visited[next]) dfs(next, adj, visited);
    }
}
```

#### BFS 求最短路徑（帶 `dist` 陣列）

前面 BFS 範例是拿來數連通塊（flood fill），如果題目要問「從起點到某個節點/格子最少要走幾步」，做法幾乎一樣，只是**把「有沒有拜訪過」的 `bool` 換成「距離是多少」的 `int`**，`-1` 代表還沒走到：

```cpp
// 一般圖版本
vector<int> dist(n + 1, -1);
dist[start] = 0;
queue<int> q;
q.push(start);
while (!q.empty()) {
    int cur = q.front(); q.pop();
    for (int next : adj[cur]) {
        if (dist[next] == -1) {           // 還沒走到過，才更新
            dist[next] = dist[cur] + 1;    // 走一步的距離就是目前距離+1
            q.push(next);
        }
    }
}
```

```cpp
// 2D 網格版本（例如迷宮找最短路徑）
vector<vector<int>> dist(m, vector<int>(n, -1));
dist[si][sj] = 0;
queue<pair<int,int>> q;
q.push({si, sj});
while (!q.empty()) {
    auto [x, y] = q.front(); q.pop();
    for (int d = 0; d < 4; d++) {
        int nx = x + dx4[d], ny = y + dy4[d];
        if (nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny] != '#' && dist[nx][ny] == -1) {
            dist[nx][ny] = dist[x][y] + 1;
            q.push({nx, ny});
        }
    }
}
```

**為什麼 BFS 求出來的 `dist` 保證是最短距離**：BFS 是「一層一層」往外擴散（先擴散完距離1的所有節點，才會開始擴散距離2的），所以**第一次**把某個節點的 `dist` 設定好的那一刻，一定是從起點走過去最少的步數——不可能有更近的路徑後來才被發現，因為 BFS 保證是照距離由近到遠的順序處理。這也是為什麼「求最短步數」一定要用 BFS，DFS 沒有這個「由近到遠」的保證，不能用來求最短路徑。


---

## 🌳 樹的遍歷（Preorder / Inorder / Postorder）

### 二元樹遍歷（Preorder / Inorder / Postorder）與重建

#### 三種遍歷的定義
- **前序（preorder）**：根 → 左子樹 → 右子樹
- **中序（inorder）**：左子樹 → 根 → 右子樹
- **後序（postorder）**：左子樹 → 右子樹 → 根

三種名稱指的都是「根什麼時候被印出來」（前序最先印、中序印在中間、後序最後印），左右子樹之間永遠是「先左後右」。

#### 核心技巧：不用建樹，靠切割字串（或陣列區間）直接推出另一種遍歷
給定 preorder + inorder，要推出 postorder，關鍵洞察：
1. **preorder 的第一個字元，一定是根**（前序定義：根先印）
2. **拿根去 inorder 裡面找位置**：根左邊的所有字元＝整個左子樹的節點，根右邊的所有字元＝整個右子樹的節點（中序定義：左子樹全部先印，才印根，才印右子樹）
3. **知道左子樹有幾個節點**（inorder裡根左邊的長度），回頭切 preorder：根之後緊接著、長度一樣的那一段，就是左子樹的 preorder；再往後剩下的是右子樹的 preorder
4. 對切出來的左、右兩段，重複同樣的邏輯遞迴下去，遞迴到空字串就停

```cpp
void solve(string pre, string in) {
    if (pre.empty()) return;

    char root = pre[0];
    int pos = in.find(root);

    string leftIn  = in.substr(0, pos);
    string rightIn = in.substr(pos + 1);
    string leftPre  = pre.substr(1, leftIn.size());
    string rightPre = pre.substr(1 + leftIn.size());

    solve(leftPre, leftIn);     // 後序：先處理左子樹
    solve(rightPre, rightIn);   // 再處理右子樹
    cout << root;               // 最後才印根
}
```

**為什麼不用真的建樹（`struct TreeNode`、指標）就能直接印出正確的遍歷結果**：後序遍歷的定義本身就是遞迴的（`postorder(左子樹) → postorder(右子樹) → 印根`），這個定義只在乎「當前子樹的根是誰、左子樹是誰、右子樹是誰」，不在乎這三個答案是怎麼取得的。`(preorder片段, inorder片段)` 這組字串，跟「一串用指標串起來的節點」一樣，都完整包含了「根＋左子樹＋右子樹」的資訊，只是換了一種表示法——遞迴呼叫的**順序**（先左、再右、最後根）才是決定輸出結果是不是正確遍歷的關鍵，跟樹是用指標存還是用字串片段表示無關。

#### 讀取「空白分隔的單個字元」技巧
節點常常是空白分隔的單一字母（例如 `A B D E F C G`），可以用迴圈搭配 `cin >> c` 讀單個字元，`cin >>` 會自動跳過空白，直接接成一個字串：
```cpp
string pre;
for (int i = 0; i < n; i++) { char c; cin >> c; pre += c; }
```

#### 這種遞迴會不會超時、需不需要改寫成堆疊？
判斷方式跟前面 DFS 的判斷原則一樣：看**遞迴深度**跟**總運算量**。這類題目節點數通常很小（例如 `n≤26`），遞迴深度最多就是樹的高度（最壞情況退化成鏈狀也只有 `n` 層），總運算量大概 `O(n²)`（每層切字串的成本），對這種規模完全不用擔心，直接寫遞迴就好，不需要像 c129 那種格子數上萬的題目才需要考慮改寫成迭代版本。


---

## 💡 動態規劃（DP 基礎、背包、賽局 DP、換零錢、LIS、LCS）

### DP：動態規劃基礎

#### 怎麼判斷一題要不要用 DP？
拿到題目沒有頭緒時，照這個順序檢查：

1. **問題能不能拆成「子問題」，而且子問題會被重複用到？**
   如果你發現「算大的答案，需要先算出好幾個更小的答案，而且這些更小的答案還會被別的地方重複用到」，這就是 DP 的訊號。（純遞迴不存結果的話，同樣的子問題會被重複計算很多次；DP 就是把算過的存起來，不重算）

2. **題目的關鍵字**，常見會用到 DP 的問法：
   - 「最少/最多需要...」→ 最佳化型
   - 「有幾種不同的方法/組合」→ 計數型（例如換零錢方法數）
   - 「能不能剛好湊出/達成...」→ 可行性型，通常是布林 DP（例如賽局必勝必敗）
   - 「最長/最短的...子序列/子字串」→ 序列型（例如 LIS、LCS）

3. **資料範圍給的暗示**：如果直接窮舉所有可能是指數時間 `O(2^n)`，但題目的 `n` 卻大到幾百、幾千甚至上百萬，代表出題者**不是**要你窮舉，是要你找出「重疊子問題」，用 DP 把時間壓到多項式等級（`O(n)`、`O(n²)`...）。

4. **反過來說，不適合只靠 DP 的情況**：如果題目要你**列出所有解本身**（不只是求數量或最優值），例如「印出所有走法」，通常要搭配 backtracking／DFS 窮舉，DP 頂多用來輔助剪枝。

#### DP 的固定套路（不管哪一種 DP，都照這 4 步驟想）
1. **狀態**：`dp[?]` 的 `?` 代表什麼（通常是「還剩多少資源」、「走到第幾個位置」、「考慮到第幾個物品」...）
2. **邊界**：最小的狀態（通常是 0 或空）答案是什麼，是遞推的起點
3. **轉移**：`dp[大狀態]` 怎麼由 `dp[小狀態]` 組合出來
4. **答案對應哪個狀態**：題目要的最終答案，是 `dp[]` 裡的哪一格

---

### 0/1 背包 vs 完全背包（Knapsack 基礎骨架）

兩種都是「有一堆物品、容量有限，怎麼選」的問題，**差別只在同一種物品能不能重複選**。

| | 0/1 背包 | 完全背包（Unbounded Knapsack） |
|---|---|---|
| 每種物品能拿幾次 | 最多 1 次 | 不限次數 |
| 內層容量迴圈方向（一維陣列優化時） | **由大到小**（遞減） | **由小到大**（遞增） |
| 例子 | 每個寶物只有一件，選或不選 | 硬幣、紙鈔面額（可以一直用同一種） |

#### 為什麼內層迴圈方向不一樣，這是最容易搞混的地方
用一維陣列 `dp[w]` 省記憶體（不開二維 `dp[i][w]`）時，迴圈方向決定了「這一輪更新 `dp[w]` 時，用到的 `dp[w-weight]` 是不是已經包含這次的物品」：

- **0/1 背包（每種只能拿一次）**：容量要**由大到小**跑，這樣算 `dp[w]` 時用到的 `dp[w-weight]` 還是「上一輪（還沒放這個物品前）」的值，保證同一個物品不會被重複計算進去。
  ```cpp
  for (每個物品 i) {
      for (int w = 容量上限; w >= weight[i]; w--) {   // 由大到小！
          dp[w] = max(dp[w], dp[w-weight[i]] + value[i]);
      }
  }
  ```

- **完全背包（可以拿無限次）**：容量要**由小到大**跑，這樣算 `dp[w]` 時用到的 `dp[w-weight]` 已經是「這一輪更新過」的值（可能已經放過同一物品一次），等於允許同一物品被重複疊加。
  ```cpp
  for (每個物品 i) {
      for (int w = weight[i]; w <= 容量上限; w++) {   // 由小到大！
          dp[w] = max(dp[w], dp[w-weight[i]] + value[i]);
      }
  }
  ```

**判斷原則**：看到題目說「同一種東西可以用好幾次」（硬幣、紙鈔、無限供應的材料）→ 完全背包，內層遞增；看到「每個東西只有一件，選了就沒了」→ 0/1 背包，內層遞減。

---

### DP 應用範例 1：賽局 DP（Win / Lose 型，完全背包變體）

跟背包（求最大值/最小值）不同，這種 DP 求的是**布林值**：「這個局面對『輪到的那個人』來說是必勝還是必敗」。

**狀態定義**：`dp[i]` = 剩 i 顆石頭、輪到某人走，這個人是不是必勝。

**邊界**：`dp[0] = false`（輪到你但沒得走 = 你輸了）。

**轉移（OR-of-NOT）**：只要存在一種合法走法，能把對手逼進 `dp[i-k] == false` 的局面，你就必勝：
```cpp
dp[i] = false;                    // 先假設會輸
for (int k : moves) {
    if (i - k >= 0 && dp[i-k] == false) {
        dp[i] = true;             // 找到一條能讓對手輸的路，你就贏
        break;                    // 賽局 DP 只要「存在」就夠，找到就能提早跳出
    }
}
```

**跟背包的差異**：
| | 背包（最佳化） | 賽局 DP（本題） |
|---|---|---|
| 求什麼 | 最大值/最小值 | 布林值（贏/輸） |
| 轉移邏輯 | `dp[i] = max(dp[i], dp[i-w]+v)` | `dp[i] = OR(dp[i-k]==false)` |
| 迴圈骨架 | 外層容量、內層物品，長得很像 | 外層容量(石頭數)、內層物品(移動集合)，長得很像 |

> 之所以直覺會連到背包，就是因為**雙層迴圈的骨架長一模一樣**（外層跑 1~n、內層跑集合裡的每個數字），差別只在裡面在算「最佳值」還是「能不能贏」。

**`vector<bool>` 用於 DP 的記憶體優勢**：`vector<bool>` 是特化過的、bit-packed（每個元素只占 1 bit，不是 1 byte），100 萬個 `dp[i]` 只要約 125KB，這題 `n` 最多到 1,000,000 也完全不會超出記憶體限制。

---

### DP 應用範例 2：換零錢方法數（計數型完全背包）

跟上面「賽局 DP」不同，這種 DP 求的是**方法數**（有幾種不同組合方式），一樣是完全背包骨架（同一種面額可以重複使用），但轉移邏輯從「取最大值」變成「累加」。

**狀態定義**：`dp[j]` = 湊出金額 `j`，有幾種不同的組合方式（換順序不算不同種）。

**邊界**：`dp[0] = 1`（湊出金額 0，只有「什麼都不拿」這一種方法）。

**轉移**：
```cpp
dp[0] = 1;
for (每一種面額 c) {                       // 外層：面額
    for (int j = c; j <= maxAmount; j++) {  // 內層：金額，由小到大（完全背包的方向）
        dp[j] += dp[j - c];
    }
}
```

**最容易搞混的地雷：外層/內層的角色不能反過來**
- 外層面額、內層金額（上面寫的）→ 算出來的是**組合數**（順序不同不算不同種），這才是這類題目要的答案
- 如果反過來，外層金額、內層面額 → 算出來的會是**排列數**（同樣的錢用不同順序湊出來，會被重複算成不同種），答案會偏大很多

這跟「0/1 背包 vs 完全背包」的內層遞增/遞減方向是**兩件不同的事**：方向決定同一物品能不能重複用；外層/內層是哪個變數，決定算出來的是組合數還是排列數。兩個都要注意，別搞混。

> 這類題目（換零錢方法數）答案通常會非常大（超過 `int` 範圍），DP 陣列記得開 `long long`。

---

### DP 應用範例 3：最長遞增子序列（LIS, Longest Increasing Subsequence）

**題目長這樣**：給一串數字，找出最長的一段「子序列」（不用連續，但順序不能變），使得這段數字是遞增的。

**狀態定義**：`dp[i]` = 以第 `i` 個元素**結尾**的最長遞增子序列長度。

**邊界**：`dp[i] = 1`（每個元素自己單獨算，長度至少是1）。

**轉移**：往前看所有比自己小的元素，接在它們後面能不能變得更長：
```cpp
vector<int> dp(n, 1);
for (int i = 0; i < n; i++) {
    for (int j = 0; j < i; j++) {
        if (a[j] < a[i]) {
            dp[i] = max(dp[i], dp[j] + 1);
        }
    }
}
int ans = *max_element(dp.begin(), dp.end());   // 答案不一定是dp[n-1]，要取全部dp[]裡的最大值
```

**複雜度**：上面雙層迴圈是 `O(n²)`。如果 `n` 很大（例如上萬），可以搭配 `lower_bound` 優化到 `O(n log n)`（維護一個「目前每個長度的子序列，最小可能的結尾值」陣列，每個新元素進來用二分搜找它該接到哪個長度後面）——這也是為什麼 `lower_bound` 這個技巧會在 LIS 的進階解法出現。

---

### DP 應用範例 4：最長共同子序列（LCS, Longest Common Subsequence）

**題目長這樣**：給兩個字串，找出兩者共同擁有的最長子序列（不用連續，但兩邊出現的順序都不能變）。

**狀態定義**：`dp[i][j]` = 字串1的前 `i` 個字元、字串2的前 `j` 個字元，最長共同子序列的長度。

**邊界**：`dp[0][*] = dp[*][0] = 0`（其中一個字串長度是0，共同子序列當然是0）。

**轉移**：
```cpp
vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
        if (s1[i-1] == s2[j-1]) {
            dp[i][j] = dp[i-1][j-1] + 1;              // 這兩個字元對上了，往前一格的答案+1
        } else {
            dp[i][j] = max(dp[i-1][j], dp[i][j-1]);   // 沒對上，取「丟掉s1這個字元」跟「丟掉s2這個字元」較好的那個
        }
    }
}
int ans = dp[n][m];
```

**為什麼是 `dp[i-1][j-1]+1` 或 `max(dp[i-1][j], dp[i][j-1])`**：字元對上時（`s1[i-1]==s2[j-1]`），這個字元一定值得放進共同子序列裡，所以直接在「兩邊都少一個字元時的答案」基礎上 +1；沒對上時，這個字元不可能同時屬於兩邊的共同子序列，所以只能選「丟掉s1這個字元繼續比」或「丟掉s2這個字元繼續比」兩者中比較好的結果，答案不會變差。


---

## 🔍 演算法技巧（二分搜、幾何共線、質數篩法、排列組合）

### Binary Search：二分法

#### 什麼時候該想到這個技巧
1. **題目在問「最小化最大值」或「最大化最小值」**（例如：切成 m 段，讓最大的一段盡量小；或是分配資源，讓最小的那份盡量大）
2. **答案具有單調性（可行性遞增或遞減）**：如果某個候選答案 `T` 可行，那麼比 `T` 更寬鬆的候選答案也一定可行；`T` 不可行，比它更嚴格的也一定不可行。有這種「一刀切」的特性，才能用二分搜快速逼近邊界，而不用一個一個試
3. **直接算不出來，但「驗證某個候選答案行不行得通」相對好寫**——這是二分搜答案最大的價值：把「求最佳解」轉換成「驗證可行性」，通常驗證函式會搭配貪心法

#### 固定套路（4 個部分）
```cpp
lo = 最小可能的答案（下界，通常從題目限制推出來）
hi = 最大可能的答案（上界，通常是「最寬鬆情況」下的值）

while (lo < hi) {
    int mid = lo + (hi - lo) / 2;   // 這樣寫比 (lo+hi)/2 安全，避免相加時提早溢位
    if (check(mid)) {                // 驗證 mid 這個候選答案是否可行
        hi = mid;                    // 可行，答案可能更小（或更大，看題目要的方向），往這邊逼近
    } else {
        lo = mid + 1;
    }
}
// 收斂後 lo == hi，就是答案
cout << lo << endl;
```

#### 範例：Fill the Containers（把 n 個桶子依序切成 m 段，最小化「最大那段」的總和）
- **下界 `lo`**：至少要能裝下單一個最大的桶子 → `*max_element(c.begin(), c.end())`
- **上界 `hi`**：全部塞進同一段（m=1 的情況）→ `accumulate(c.begin(), c.end(), 0)`
- **`check(mid)`**：用貪心法算「如果每段都不能超過 `mid`，最少要切成幾段」，貪心邏輯是「能塞就塞，塞不下才被迫切一刀」：

```cpp
bool check(int mid, int n, int m, const vector<int>& c){
    int count = 1;
    int sum = 0;
    for (int i = 0; i < n; i++) {
        if (sum + c[i] > mid) {   // 裝不下了，才開新的一段（地雷：方向不能反過來、也不能寫成 <）
            count++;
            sum = c[i];
        } else {
            sum += c[i];
        }
    }
    return count <= m;             // 切出來的段數不超過 m，代表 mid 這個上限可行
}
```

#### 常見地雷
1. **`check` 判斷式的方向寫反**：這題要判斷「裝不下了」，條件是 `sum + c[i] > mid`（超過才切），不是 `< mid`——寫反的話貪心邏輯會整個顛倒，算出離譜的容器數。
2. **忘記包 `while(lo < hi)`**：只算一次 `mid` 就直接輸出 `lo`，`lo`/`hi` 根本沒收斂，答案幾乎一定是錯的。二分搜答案一定要迴圈跑到 `lo == hi` 才能停。
3. **`mid` 算法用 `(lo+hi)/2`**：在 `lo`、`hi` 都很大的情況下，相加可能會比各自的範圍還早溢位，改用 `lo + (hi-lo)/2` 更安全（雖然這題數值範圍不至於溢位，但養成習慣比較保險）。
4. **`hi = mid` 還是 `hi = mid - 1`，`lo = mid + 1` 還是 `lo = mid`**：要跟著「`check(mid)` 回傳 true 時要不要保留 `mid` 這個候選答案」來決定。像這題，`mid` 可行時它本身仍然可能是最終答案，所以是 `hi = mid`（保留），不可行時 `mid` 一定不是答案，下一個候選要跳到 `mid+1`。這幾種邊界寫法很容易搞混，寫的時候要想清楚「這個 mid 本身還算不算數」。

---

### 整數座標判斷共線 / 直線標準化技巧

平面上任兩點 `(x1,y1)`、`(x2,y2)` 決定的直線，可以寫成標準式 `A*x + B*y = C`：
```cpp
int A = y2 - y1;
int B = x1 - x2;
int C = A*x1 + B*y1;
```

**用整數（不用浮點數斜率）表示線的好處**：完全不會有浮點數誤差，垂直線（斜率無限大）也能正常表示（`B=0`），不用另外特判。這是幾何題常見的技巧——能用整數表示的幾何關係，盡量別用浮點數。

**問題**：同一條線，不同兩點組合算出來的 `(A,B,C)` 可能是成比例的不同倍數，正負號也可能相反，必須先「標準化」成唯一表示法才能拿去比較/去重：

```cpp
int g = gcd(gcd(abs(A), abs(B)), abs(C));   // <numeric> 的 gcd
if (g != 0) { A /= g; B /= g; C /= g; }      // 化簡成最簡整數比

if (A < 0 || (A == 0 && B < 0)) {            // 固定正負號（規定A要正，A=0時B要正）
    A = -A; B = -B; C = -C;
}
```

化簡+固定正負號後，`(A,B,C)` 就是這條線唯一的標準表示法，丟進 `set<tuple<int,int,int>>` 即可自動去重，`set.size()` 就是不重複的線的數量。

**這個技巧天生涵蓋所有方向的線，不用分類討論**：水平線 `A=0`、垂直線 `B=0`、任意斜率的斜線 `A,B都非0`，全部用同一套標準化流程處理，不用寫 if 去判斷「這是哪一種線」。

---

### 質數篩法（Sieve of Eratosthenes）

**用途**：要一次找出「1 到 N 之間所有質數」，或是要快速回答很多次「這個數是不是質數」，逐個用 `for` 試除法太慢（每個數字要 `O(√n)`），篩法可以一次把 `1~N` 全部標記好，總複雜度只要 `O(N log log N)`，非常接近線性。

**概念**：從 2 開始，把每個質數的所有倍數都標記成「不是質數」（因為倍數一定是合數）；沒被標記到、還維持「是質數」的數字，就真的是質數。

```cpp
int N = 1000000;
vector<bool> isPrime(N + 1, true);
isPrime[0] = isPrime[1] = false;      // 0、1都不是質數

for (int i = 2; (long long)i * i <= N; i++) {
    if (isPrime[i]) {
        for (int j = i * i; j <= N; j += i) {   // 從 i*i 開始標記，不是從 2*i
            isPrime[j] = false;
        }
    }
}
```

**為什麼內層迴圈從 `i*i` 開始，不是從 `2*i` 開始**：因為 `i` 的所有「小於 `i*i`」的倍數（例如 `2*i, 3*i, ..., (i-1)*i`），一定早就被更小的質數（`2, 3, ..., i-1` 之中能整除它們的那個）標記過了，從 `i*i` 開始才不會重複做白工。這個小優化讓篩法從 `O(N log N)` 進一步逼近 `O(N log log N)`。

**外層迴圈為什麼用 `i*i <= N` 而不是 `i <= N`**：如果 `i > √N`，那 `i*i` 早就超過 `N` 了，這個 `i` 根本沒有「小於等於N」的倍數需要標記（除了它自己），可以提早停止外層迴圈，省下大量不必要的檢查。

---

### 排列組合（Permutation）

窮舉一個序列所有的排列方式，最簡單的做法是 `<algorithm>` 的 `next_permutation`（見「常用標頭檔函式」章節），一定要先排序過再開始窮舉：

```cpp
sort(v.begin(), v.end());
do {
    // 處理目前這個排列
} while (next_permutation(v.begin(), v.end()));
```

如果需要更多控制（例如只排列其中一部分、邊排列邊剪枝提早放棄不可能的分支），可以改用**遞迴＋回溯（backtracking）**手動生成排列：
```cpp
vector<int> path;
vector<bool> used(n, false);

void permute(vector<int>& nums) {
    if (path.size() == nums.size()) {
        // 處理一個完整排列 path
        return;
    }
    for (int i = 0; i < nums.size(); i++) {
        if (used[i]) continue;         // 這個數字已經用過，跳過
        used[i] = true;
        path.push_back(nums[i]);

        permute(nums);                  // 遞迴決定下一個位置

        path.pop_back();                // 回溯：把這個選擇「還原」，才能嘗試別的選擇
        used[i] = false;
    }
}
```

**`next_permutation` vs 手寫回溯的選擇**：只是要「跑過所有排列，沒有額外限制」→ 用 `next_permutation` 最簡短；需要「剪枝」（提早放棄不可能湊出答案的分支）或排列過程中有額外邏輯要處理 → 用回溯法，彈性比較大。


---

## 待補充
- 剪枝 / 記憶化搜尋（memoization）
