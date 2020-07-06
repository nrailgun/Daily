int get_p(int i) {
        return (i - 1) / 2;
}

int get_l(int i) {
        return 2 * i + 1;
}

int get_r(int i) {
        return 2 * i + 2;
}

void heapify(int h[], int n, int i) {
        while (i < n) {
                int max_i = i;
                int l = get_l(i);
                if (l < n && h[l] > h[max_i]) {
                        max_i = l;
                }
                int r = get_r(i);
                if (r < n && h[r] > h[max_i]) {
                        max_i = r;
                }

                if (max_i == i) {
                        break;
                }
                else {
                        swap(h[i], h[max_i]);
                        i = max_i;
                }
        }
}

void make_heap(int h[], int n) {
        for (int i = get_p(n - 1); i >= 0; i--) {
                heapify(h, n, i);
        }
}

void push_heap(int h[], int n, int val) {
        int i = n;
        h[i] = val;
        while (i != 0) {
                int p = get_p(i);
                if (h[p] >= h[i])
                        break;
                swap(h[p], h[i]);
                i = p;
        }
}

int pop_heap(int h[], int n) {
        assert(n > 0);
        int maxv = h[0];
        h[0] = h[n - 1];
        heapify(h, n - 1, 0);
        return maxv;
}
