#include <cassert>
#include <cstdlib>

#include "find_union.h"

int main()
{
  std::vector<find_union> elems;
  for (int i = 0; i < 10; i++) {
    elems.push_back(create_fu(i));
  }

  for (int i = 0; i < 10; i++) {
    assert(find(elems[i]) == i);
    assert(size(elems[i]) == 1);
  }

  for (int i = 0; i < 10; i++) {
    for (int j = 0; i < 10; i++) {
      if (i == j) {
        assert(equivalent(elems[i], elems[j]));
      } else {
        assert(!equivalent(elems[i], elems[j]));
      }
    }
  }

  union_fu(elems[0], elems[1]);
  assert(equivalent(elems[1], elems[0]));
  assert(size(elems[1]) == 2);
  assert(size(elems[0]) == 2);
  assert(find(elems[1]) == find(elems[0]));
  union_fu(elems[1], elems[2]);
  union_fu(elems[1], elems[3]);

  for(int i = 0; i < 4; i++) {
    assert(size(elems[i]) == 4);
    assert(elements(elems[i]).size() == 4);
      for (int j = 0; i < 4; i++) {
       assert(equivalent(elems[i], elems[j]));
       for (int k = 0; k < 4; k++) {
        assert(elements(elems[i])[k] == elements(elems[j])[k]);
       }
    }
  }

  union_fu(elems[4], elems[5]);
  union_fu(elems[6], elems[7]);
  union_fu(elems[8], elems[9]);
  union_fu(elems[4], elems[9]);
  union_fu(elems[7], elems[5]);

  for(int i = 4; i < 10; i++) {
    assert(size(elems[i]) == 6);
    assert(elements(elems[i]).size() == 6);
      for (int j = 4; i < 10; i++) {
       assert(equivalent(elems[i], elems[j]));
       for (int k = 0; k < 6; k++) {
        assert(elements(elems[i])[k] == elements(elems[j])[k]);
       }
    }
  }

  union_fu(elems[7], elems[3]);

  for(int i = 0; i < 10; i++) {
    assert(size(elems[i]) == 10);
    assert(elements(elems[i]).size() == 10);
      for (int j = 0; i < 10; i++) {
       assert(equivalent(elems[i], elems[j]));
       for (int k = 0; k < 10; k++) {
        assert(elements(elems[i])[k] == elements(elems[j])[k]);
       }
    }
  }

  for (int i = 0; i < 10; i++) {
   free(elems[i]);
  }
  return 0;
}