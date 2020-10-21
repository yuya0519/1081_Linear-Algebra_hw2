//#include<stdlib.h>
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<cstdlib>
#include<stdio.h>
#include<vector>
using namespace std;

int main(int argc, char* argv[])
{
	ifstream infile1;
	ifstream infile2;
	infile1.open("q4.JSON");
	infile2.open("q4.INFO");
	string word;
	vector<string>bu;
	vector<string>object;
	int count = 0;
	int q;
	string buffer;
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
	int** objectNum = new int* [object.size()];
	for (int i = 0; i < object.size(); i++)
		objectNum[i] = new int[count]();
	int c = -1;
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
	int** ans=new int*[object.size()];
	for (int i = 0; i < object.size(); i++) 
		ans[i] = new int[object.size()]();

	getline(infile2, word);
	stringstream ss(word);
	int caseNum ;
	ss >> caseNum;
	string* info=new string [caseNum * 2] ;
	int b = 0;
	int r = 0;
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
	for (int j = 0; j < object.size(); j++) {
		if (object[j] == info[caseNum*2-2]) {
			b = j;
		}
		if (object[j] == info[caseNum * 2 - 2 + 1]) {
			c = j;
		}	
	}
	for (int k = 0; k < count; k++) {
		ans[b][c] += objectNum[b][k] * objectNum[c][k];
	}
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