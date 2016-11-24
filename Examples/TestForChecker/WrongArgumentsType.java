class Main {
    public static void main(String[] args) {
        System.out.println(new A().cool());
    }
}

class C {
}

class B {
	public int f(int n) {
		return 43;
	}
}

class A {
    public int cool() {
    	C c;
    	return (new B().f(c));
    }
}