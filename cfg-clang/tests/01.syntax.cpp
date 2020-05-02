#include <iostream>
using namespace std;

int main(void) {

	string a;
	int b=5;
	int c=0;

	for(int i=0; i<b; i++) {
		c--;
		if(c==1) continue;
		if(c==2) break;
		c--;
		}

	while(b>c) {
		c++;
		}

	do {
		int d=0;
		c++;
		d--;
		cout << "do" << endl;
		if(d)
			cout << "d" << endl;
	} while(b>c);


	if(b>0) {
		cout << "+" << endl;
	} else if(b=0) {
		cout << "0" << endl;
	} else {
		cout << "-" << endl;
		}

	switch(b) {
		case 1:
			cout << "1" << endl;
			break;
		case 2:
			cout << "2" << endl;
			break;
		case 3:
			cout << "3" << endl;
			break;
		default:
			cout << "def" << endl;
			break;
		}

	int func(int b);// { return(b); }
	class E {
	private:
		int a;
		friend int func(int b);
	public:
		E(int _a) : a(_a) {
			cout << "CTOR" << endl;
			}
	};

	label:

	if(b)
		goto label;

	class A : public E {};


	return(0);
	}

	int func(int b) { return(b); }
//	operator<<(A& out, int& in) { return(out); }
