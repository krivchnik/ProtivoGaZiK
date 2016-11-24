class Main {
    public static void main(String[] args) {
        System.out.println(new A().cool());
    }
}

class A {
    public int cool() {
    	A a;
    	while (a) 
    		System.out.println(42);
        return 43;
    }
}
