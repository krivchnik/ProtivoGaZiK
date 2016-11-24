class Main {
    public static void main(String[] args) {
        System.out.println(new A().cool());
    }
}

class A {
    public int cool() {
    	A a;
    	if (a) 
    		System.out.println(42);
        else 
            System.out.println(43);
        
        return 43;
    }
}
