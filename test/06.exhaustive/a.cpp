#include "a.hpp"

void func() {
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
		if(d)
			d++;
	} while(b>c);

	if(b>0) {
		b += 1;
	} else if(b=0) {
		b += 1 << 2;
	} else {
		b += 1 | 2;
	}

	switch(b) {
		case 1:
			b += 1;
			break;
		case 2:
			b += 2;
			break;
		case 3:
			b += 3;
			break;
		default:
			b = 0;
			break;
	}

	{
		int funk(int b);
		class E : private B {
		private:
			int a;
			friend int funk(int b);
		public:
			E(int _a) : a(_a) {}
		};
	}

label:

	if(b)
		goto label;
}

int funk(int b) { return(b); }


namespace Namespace {

int A::ret(int a) {
	return a;
}

}
