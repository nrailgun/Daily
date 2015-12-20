public class Hashtable {

    private /*@ spec_public nullable @*/ Object[] h;
    private /*@ spec_public @*/ int capacity;
    private /*@ spec_public @*/ int size = 0;

    //@ invariant size >= 0 && size <= capacity;
    //@ invariant capacity == h.length;
    //@ invariant h != null;
    //@ invariant capacity >= 1;

    //@ invariant size == (\sum int i; 0 <= i && i < capacity && h[i] != null; 1);

    /*@ public normal_behavior
      @ ensures this.capacity == capacity;
      @ ensures size == 0;
      @ assignable h[*], capacity, size;
      @*/
    Hashtable(int capacity) {
        h = new Object[capacity];
        this.capacity = capacity;
    }

    /*@ public normal_behavior
      @ requires val > 0;
      @ ensures \result >= 0 && \result < capacity;
      @*/
    private /*@ pure @*/ int hash_function(int val) {
        return val % capacity;
    }

    /*@ public normal_behavior
      @ requires size < capacity;
      @ ensures size == \old(size);
      @ ensures (\exists int i; 0 < i && i < size; h[i] == obj);
      @ assignable h[*], size;
      @ also
      @ public exceptional_behavior
      @ requires size == capacity;
      @ signals_only Exception;
      @ assignable \nothing;
      @*/
    public void add(Object obj, int key) {
        if (size < capacity) {
            int i = hash_function(key);
            if (h[i] == null) {
                h[i] = obj;
                size++;
            }
            else {
                while (h[i] != null) {
                    if (i == capacity - 1)
                        i = 0;
                    else
                        i++;
                }
                h[i] = obj;
                size++;
            }
            return;
        }
        else {
            throw new Exception("");
        }
    }
}
