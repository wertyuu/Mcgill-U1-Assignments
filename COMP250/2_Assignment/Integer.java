public class Integer implements Comparable<Integer>{
    private int a;

    public Integer(int a) {
        this.a = a;
    }

    public int getInt() {
        return a;
    }

    public int CompareTo(Integer other) {
        if (a < other.getInt()) {
            return -1;
        } else if (a == other.getInt()) {
            return 0;
        } else {
            return 1;
        }
    }
}
