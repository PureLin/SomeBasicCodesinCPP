#include<iostream>
#include<string>
#include<sstream>
using namespace std;
inline int str2int(string T){
	return atoi(T.c_str());
}
inline string int2str(int A){
	string T;
	stringstream ss;
	ss<<A;
	ss>>T;
	return T;
} 
//bool Prime(int n){
//	if(n%2==0)return false;
//	for(int i=3;i<=(n/2+1);i+=2){
//		if(n%i==0)return false;
//	}
//	return true;
//}