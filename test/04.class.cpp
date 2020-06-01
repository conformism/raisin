
class E {
public:
	E(void) = default;
private:
	int e;
};

class A : public E {
public:
	float a;
};

void func(void) {

	typedef int ok;
	ok a;

	class E {
	public:
		E(void) = default;
	private:
		int e;
	};

	class A : public E {
	public:
		float a;
	};
}