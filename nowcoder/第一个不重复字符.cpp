class Solution
{
public:
  typedef list<char> List;
  typedef list<char>::iterator Iterator;

  List cl;
  unordered_map<char, Iterator> c2lit;

  //Insert one char from stringstream
  void Insert(char ch) {
    unordered_map<char, Iterator>::iterator it;
    it = c2lit.find(ch);

    if (it == c2lit.end()) {
      c2lit[ch] = cl.insert(cl.end(), ch);
    }
    else {
      Iterator lit = it->second;
      if (lit != cl.end()) {
        cl.erase(lit);
        it->second = cl.end();
      }
    }
  }

  //Return the first appearence once char in current stringstream
  char FirstAppearingOnce() {
    if (cl.empty())
      return '#';
    else
      return cl.front();
  }
};
