class Main {
    public static void main(String[] args) {
        System.out.println(new A().cool());
    }
}

class B {
}

class A {
    public int cool() {
    	B b;
    	return b.length;
    }
}