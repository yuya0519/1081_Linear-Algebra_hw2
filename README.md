# 1082_Linear-Algebra_hw2  
## 主要目標:  
利用相鄰矩陣進行初步的購物籃分析。  

## 程式運行方式:  

**該程式執行軟體為Visual 2019。**   
請將程式碼複製至上述軟體中，再編譯執行。  
創建2個檔案，分別為 q4.JSON存放訂單資訊、q4.INFO存放問題描述。

## 簡要使用說明:  
- Input: 輸入皆由讀檔，檔案格式為: 
- q4.JSON  

![avatar](https://upload.cc/i1/2020/10/22/hEDUVd.png) 


- q4.INFO  

![avatar](https://upload.cc/i1/2020/10/22/691Muo.png) 

>> 第一行為問題個數(n) 
>> 第二行為2個物品名稱 

- Output: 共有n行，輸出內容為A物品和B物品共同出現在幾張訂單中。 
> 輸出範例  
![avatar](https://upload.cc/i1/2020/10/22/bRhEz6.png)  

## 程式結構說明:  

### 基本原理:  
相鄰矩陣(Adjacency matrix)在圖學中常被使用來表示資料點(node)間的關係。 

### 引用函式庫說明:
```cpp
#include<iostream> //負責輸出/輸入
#include<string> //負責處理string相關函式
#include<fstream> //負責讀檔
#include<sstream> //引入string恨int轉換公式
#include<vector> //引用vector
#include<cstdlib> //將相關名稱新增至 std 命名空間
```

### Global變數說明:
```cpp
  	ifstream infile1; //讀檔
	ifstream infile2; //讀檔
	infile1.open("q4.JSON");  //讀檔
	infile2.open("q4.INFO");  //讀檔
	string word;  //存放讀入未處理的變數
	vector<string>bu; //存放每張訂單中中物品數量
	vector<string>object; //存放所有物名稱
	int count = 0;	//計算有多少訂單
	string buffer;  //暫存未出裡過之資料
	int** objectNum;  //存放所有訂單中個物件個數
	int** ans;  //存放答案
	int caseNum ;  //存放問題個數
	string* info;  //存放問題
	int b = 0;  //記錄當下的陣列位置
	int r = 0;  //記錄當下的陣列位置
```
### 詳細程式碼說明

```cpp
while (getline(infile1, word)) {
		int p = 0;
		if (word.find("items") != std::string::npos) {
			bu.push_back("--");
			count++;
		}
		if (word.find("product") != std::string::npos) {
			buffer.clear();
			for (int i = word.find("product") +1; i < word.length(); i++) {			
				if (word[i] <= 'Z' && 'A' <= word[i]) {
					buffer.resize(buffer.length() + 1);
					buffer[p] = word[i];
					p++;
				}
			}	
			object.push_back(buffer);		
			for (int j = 0; j < object.size()-1; j++) {	
				if(object[j]==buffer){
					object.pop_back();
					break;
				}
			}						
			p = 0;
						
		}
		if (word.find("Number") != std::string::npos) 
			for (int i = 0; i < word.length(); i++) 
				if (word[i] <= '9' && '0' < word[i]) 
					bu.push_back(buffer);	
	}
```
> 將讀入的訂單資訊做處理，
> 將全部訂單有出現的 Object名稱存入object中，
> 並將物品個數存入bu中，
> 並且計算訂單個數。

```cpp
for (int i = 0; i < bu.size(); i++) {
		if (bu[i] == "--")
			c++;
		else{
			int j = 0;
			while (bu[i]!=object[j]) {
				j++;
			}
			objectNum[j][c] = 1;
		}
	}
```
> 將重複出現在某訂單中2個物件在矩陣中相應位置的值改為1
```cpp
    while(getline(infile2,word)){
		for(int k=0;k<word.length();k++){
			if (word[k] <= 'Z' && word[k] >= 'A') {
				info[b].resize(info[b].length() + 1);
				info[b][r] = word[k];
				r++;
			}
			else if (word[k] <= ',') {
				b++;
				r = 0;
			}
		}
		b++;
		r = 0;
	}
```
> 將問題資訊處理過後存入
```cpp
	for (int i = 0; i < caseNum*2-2; i += 2) {
		for (int j = 0; j < object.size(); j++) {
			if (object[j]==info[i]) {
				b = j;
			}
			if (object[j] == info[i + 1]) {				
				c = j;
			}
		}
		for (int k = 0; k < count; k++) {
   			ans[b][c] += objectNum[b][k] * objectNum[c][k];
		}
		cout << ans[b][c] << endl;
	}
```
> 依照公式帶入，
> 計算出結果計算出結果並存入ans中

```cpp
	cout << binding_sites.size() << endl;
		cout << ans[b][c]<<endl ;
	for (int i = 0; i < object.size(); i++)
		delete[] objectNum[i];
	delete[] objectNum;
	for (int i = 0; i < object.size(); i++)
		delete[] ans[i];
	delete[] ans;
	infile1.close();
	infile2.close();
	word.clear();
	buffer.clear();
	bu.clear();
	object.clear();
}
```
> 依照格式輸出，
> 將動態陣列刪除，
> 並關掉開啟的檔案。
