// 状态机很有用。
// 千万要小心大陆笔试题那些题目完全不提的弱智Case，简直无力吐槽。

class Solution {
public:
  // Start with 0
  // End with non numeric part
  // Case: .xx
  bool isNumeric(const char *s) {
s_0:
    if (*s == '+' || *s == '-') {
      s++;
      goto s_1;
    }
    else if (*s == '.') {
      s++;
      goto s_2;
    }
    else if (isdigit(*s))
      goto s_1;
    else
      return false;
s_1:
    if (*s == '.') {
      s++;
      goto s_2;
    }
    else if (!isdigit(*s))
      return false;

    while (isdigit(*s)) {
      s++;
    }
    if (*s == 0)
      return true;
    else if (*s == '.') {
      s++;
      goto s_2;
    }
    else if (*s == 'e' || *s == 'E') {
      s++;
      goto s_3;
    }
    else
      return false;
s_2:
    if (!isdigit(*s))
      return false;
    while (isdigit(*s)) {
      s++;
    }
    if (*s == 0)
      return true;
    else if (*s == 'e' || *s == 'E') {
      s++;
      goto s_3;
    }
    else
      return false;
s_3:
    if (*s == '+' || *s == '-') {
      s++;
      goto s_4;
    }
    else if (isdigit(*s))
      goto s_4;
    else
      return false;
s_4:
    if (!isdigit(*s))
      return false;
    while (isdigit(*s)) {
      s++;
    }
    return (*s == 0);
  }
};
