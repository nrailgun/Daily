public class Main {

    private /*@ spec_public @*/ int bar;

    public Main() {
    }

    /*@ public normal_behavior
      @ ensures \result == 123;
      @ assignable \nothing;
      @*/
    public int foo() {
        int j = 0;
        j = 123;
        return j;
    }
}
