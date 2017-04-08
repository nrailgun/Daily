class LoopQueue {
public:
	int head, rear;
	int sz;
	char *data;

	LoopQueue(int sz) : head(0), rear(0), sz(sz) {
		data = new char[sz];
	}

	~LoopQueue() {
		delete[] data;
	}

	int next_len() const {
		int l = 0;
		for (int i = 0; i < sizeof(int); i++) {
			((char*)&l)[i] = data[(head + i) % sz];
		}
		return l;
	}

	bool get(char buf[], int bufl) {
		if (head == rear)
			return false;
		
		int l = next_len();
		head += sizeof(int);
		for (int i = 0; i < l; i++) {
			buf[i] = data[head++ % sz];
		}
		return true;
	}

	bool push(char buf[], int bufl) {
		if (bufl > sz - (rear - head))
			return false;

		for (int i = 0; i < sizeof(int); i++) {
			data[(rear++) % sz] = ((char*)&bufl)[i];
		}
		for (int i = 0; i < bufl; i++) {
			data[(rear++) % sz] = buf[i];
		}
		return true;
	}
};
