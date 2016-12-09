#include <iostream>
#include <algorithm>

using namespace std;

bool my_permutation(int *beg, int *end) {
  if (beg == end || beg + 1 == end)
    return false;

  int *i = end - 1;
  while (true) {
    int *j = i;
    i--;
    if (*i < *j) {
      int *k = end;
      while (*i >= *(--k))
        ;
      swap(*i, *k);
      reverse(j, end);
      return true;
    }
    if (i == beg) {
      return false;
    }
  }
}

int main(int argc, char *argv[]) {

  int nums[] = { 1, 2, 3, 4, 5 };

  do {
    cout << nums[0] << ' ';
    cout << nums[1] << ' ';
    cout << nums[2] << ' ';
    cout << nums[3] << endl;
  } while (my_permutation(nums, nums + 4));
  
  return EXIT_SUCCESS;
}
