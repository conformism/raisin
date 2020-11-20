#ifndef A_HPP
#define A_HPP

void func();

namespace Namespace {

class A {
public:
	A() = default;
	~A() {}
	int ret(int a);
private:
	int a;
};

} // namespace Namespace

typedef int tin;
using rahc = char;

int x = 1;

class B : public Namespace::A {
	Namespace::A a;
	int b;
	tin c;
	rahc d;
};

#endif // A_HPP