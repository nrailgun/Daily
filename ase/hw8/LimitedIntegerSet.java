public class LimitedIntegerSet {

    public final int limit;

    private /*@ spec_public @*/ int arr[];
    

    public LimitedIntegerSet(int limit) {
	this.arr = new int[limit];
    }


    /*@ public normal_behavior
      @ ensures \result == (\exists int i;
      @                             0 <= i && i < size;
      @                             arr[i] == elem);
      @*/
    public /*@ pure @*/ boolean contains(int elem) {/*...*/ return true;}

    /*@ public normal_behavior
      @ requires size < limit && !contains(elem);
      @ ensures \result == true;
      @ ensures contains(elem); 
      @ ensures (\forall int e;
      @                  e != elem;
      @                  contains(e) <==> \old(contains(e)));
      @ ensures size == \old(size) + 1;
      @ assignable size, arr[*];
      @ also
      @
      @ public normal_behavior
      @ requires (size == limit) || contains(elem);
      @ ensures \result == false; 
      @ ensures (\forall int e;
      @                  contains(e) <==> \old(contains(e)));
      @ ensures size == \old(size);
      @ assignable \nothing;
      @*/
    public boolean add(int elem) {/*...*/ return true;}
    

    /*@ public normal_behavior
      @ ensures !contains(elem); 
      @ ensures (\forall int e;
      @                  e != elem;
      @                  contains(e) <==> \old(contains(e)));
      @ ensures \old(contains(elem))
      @         ==> size == \old(size) - 1;
      @ ensures !\old(contains(elem))
      @         ==> size == \old(size);
      @*/
    public void remove(int elem) {/*...*/}


    // we specify that the array is sorted afterwards and that the set ha snot changed; the latter works in this case and is easier 
    // as if we would have to try to formalize permutation
    /*@ public normal_behavior
      @ ensures
      @   (\forall int i; \forall int j; i>=0 && i<j && j<size; arr[i]<arr[j]);
      @ ensures (\forall int e;  
      @                  contains(e) <==> \old(contains(e)));
      @*/
    public void sort() { /* ... */ }
    // other methods
}
