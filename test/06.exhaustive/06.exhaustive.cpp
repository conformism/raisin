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

label:

	if(b)
		goto label;

}

namespace Namespace {

class A {
public:
	A() = default;
	~A() = delete;
	int ret(int a) { return a; }
private:
	int a;
};

}

typedef int tin;
using rahc = char;

int x = 1;

class B : public Namespace::A {
	Namespace::A a;
	int b;
	tin c;
	rahc d;
};