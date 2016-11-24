class A {
    public static void main(String[] argv) {
        System.out.println(42);
    }
}

class B {
    public int cool() {
        boolean result;
        result = this.cool();
        return 42;
    }

    private boolean cool() {
        return false;
    }
}
