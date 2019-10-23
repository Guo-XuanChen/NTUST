/*
    File      : main
    Time      : 2019-09-24 02:22:14
    Author    : Guo-XuanChen
*/
#include <iostream>
using namespace std;

void hanoi(unsigned int n, unsigned char one, unsigned char two, unsigned char three){
	if(n==1){
		cout << "Move disk " << n << " From tower " << one << " to tower " << three << endl; 
	}else{
		hanoi(n-1, one, three, two);
		cout << "Move disk " << n << " From tower " << one << " to tower " << three << endl; 
		hanoi(n-1, two, one, three);
	}
}


int main(int argc, char *argv[]){
	unsigned int n;
	while(cin >> n){
		hanoi(n, '2', '3', '1');
	}
	return 0;
}