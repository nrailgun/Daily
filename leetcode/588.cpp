class Entry {
public:
  Entry(const string &name, bool isFile) : name_(name), isFile_(isFile) {
  }

  ~Entry() {
  }

  bool isFile() const {
    return isFile_;
  }

  bool isDir() const {
    return !isFile();
  }

  string name() const {
    return name_;
  }

  const map<string, shared_ptr<Entry> > &entries() const {
    assert(isDir());
    return entries_;
  }

  shared_ptr<Entry> createChildEntry(const string &s, bool isFile) {
    assert(isDir());
    shared_ptr<Entry> e = make_shared<Entry>(s, isFile);
    entries_.insert(make_pair(s, e));
    return e;
  }

  const string &content() const {
    return content_;
  }

  void appendContent(const string &s) {
    content_ = content_ + s;
  }
private:
  string name_;
  bool isFile_;
  map<string, shared_ptr<Entry> > entries_;
  string content_;
};

class FileSystem {
public:
  FileSystem() : root_(new Entry("", false)) {
  }

  vector<string> ls(const string &path) const {
    shared_ptr<Entry> pt = searchEntry(path);

    vector<string> vs;
    if (pt->isFile()) {
      vs = vector<string>({ pt->name() });
    } else {
      const auto &entries = pt->entries();
      vs.reserve(entries.size());
      for (auto it = entries.begin(); it != entries.end(); it++) {
        vs.push_back(it->first);
      }
    }
    return vs;
  }

  void mkdir(const string &path) {
    vector<string> vs = splitPath(path);
    shared_ptr<Entry> pt = root_;
    for (string s : vs) {
      const auto &entries = pt->entries();
      auto it = entries.find(s);
      if (it == entries.end())
        pt = pt->createChildEntry(s, false);
      else
        pt = it->second;
      assert(pt->isDir());
    }
  }

  void addContentToFile(const string &filePath, const string &content) {
    shared_ptr<Entry> e = searchEntry(filePath, true, true);
    e->appendContent(content);
  }

  string readContentFromFile(const string &filePath) {
    shared_ptr<Entry> p = searchEntry(filePath);
    assert(p->isFile());
    return p->content();
  }

private:
  vector<string> splitPath(const string &path) const {
    vector<string> tokens;
    const char *s, *e;
    tokens.reserve(16);
    s = path.c_str() + 1;
    while (*s != 0 && (e = strchr(s, '/'))) {
      if (e != s)
        tokens.push_back(string(s, e));
      s = e + 1;
    }
    if (*s != 0) {
      tokens.push_back(string(s));
    }
    return tokens;
  }

  shared_ptr<Entry> searchEntry(const string &path,
    bool createOnMissing = false, bool isFile = true) const
  {
    const vector<string> vs = splitPath(path);
    shared_ptr<Entry> pt = root_;
    for (int i = 0; i < vs.size(); i++) {
      const string &s = vs[i];
      const auto &entries = pt->entries();
      auto it = entries.find(s);
      if (it != entries.end()) {
        pt = it->second;
      } else {
        assert(createOnMissing);
        pt = pt->createChildEntry(s, (i < vs.size() - 1) ? false : isFile);
      }
    }
    return pt;
  }

  shared_ptr<Entry> root_;

  friend class FileSystemTest;
};

class FileSystemTest {
public:
  FileSystem fs_;

  FileSystemTest() {
  }

  void splitPathTest() {
    vector<string> vs;
    
    vs = fs_.splitPath("/a/b/c");
    assert(vs.size() == 3);
    assert(vs[0] == "a");
    assert(vs[1] == "b");
    assert(vs[2] == "c");

    vs = fs_.splitPath("/a/b/c/");
    assert(vs.size() == 3);
    assert(vs[0] == "a");
    assert(vs[1] == "b");
    assert(vs[2] == "c");

    vs = fs_.splitPath("/a/b/cx");
    assert(vs.size() == 3);
    assert(vs[0] == "a");
    assert(vs[1] == "b");
    assert(vs[2] == "cx");

    vs = fs_.splitPath("/a/b/cx/");
    assert(vs.size() == 3);
    assert(vs[0] == "a");
    assert(vs[1] == "b");
    assert(vs[2] == "cx");

    vs = fs_.splitPath("/a/");
    assert(vs.size() == 1);
    assert(vs[0] == "a");

    vs = fs_.splitPath("/a");
    assert(vs.size() == 1);
    assert(vs[0] == "a");
  }

  void lsTest() {
    vector<string> vs;

    FileSystem fs1;
    fs1.mkdir("/a/");
    fs1.mkdir("/b/");
    fs1.mkdir("/c/");
    vs = fs1.ls("/");
    assert(vs.size() == 3);
    assert(vs[0] == "a");
    assert(vs[1] == "b");
    assert(vs[2] == "c");

    fs1.mkdir("/a/b/c/d/e");
    vs = fs1.ls("/a/b/c/d");
    assert(vs.size() == 1);
    assert(vs[0] == "e");

    vs = fs1.ls("/a/b/c/d/");
    assert(vs.size() == 1);
    assert(vs[0] == "e");

    fs1.mkdir("/b/b1");
    fs1.mkdir("/b/b2");
    fs1.mkdir("/b/b3");
    fs1.mkdir("/b/b4");
    vs = fs1.ls("/b/");
    assert(vs.size() == 4);
    assert(vs[0] == "b1");
    assert(vs[1] == "b2");
    assert(vs[2] == "b3");
    assert(vs[3] == "b4");
  }

  void contentTest() {
    FileSystem fs;
    string fname, content, read;

    fs.mkdir("/home/nr/");
    fname = "/home/nr/main.c";
    content = "int i, j, k";
    fs.addContentToFile(fname, content);
    read = fs.readContentFromFile(fname);
    assert(content == read);

    fs.addContentToFile(fname, "= 0");
    read = fs.readContentFromFile(fname);
    assert(content + "= 0" == read);
  }
};
