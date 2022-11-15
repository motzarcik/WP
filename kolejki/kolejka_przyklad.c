#include <assert.h>

#include "kolejka.h"

int main()
{
  queue q = make_queue();
  push_back(&q, make_elem(1, 1));
  assert(1 == front(q).val1);
  assert(1 == back(q).val1);
    
  push_back(&q, make_elem(2, 2));
  assert(1 == front(q).val1);
  assert(2 == back(q).val1);
    
  push_back(&q, make_elem(3, 3));
  assert(1 == front(q).val1);
  assert(3 == back(q).val1);
    
  push_back(&q, make_elem(4, 4));
  assert(1 == front(q).val1);
  assert(4 == back(q).val1);
    
  push_back(&q, make_elem(5, 5));
  assert(1 == front(q).val1);
  assert(5 == back(q).val1);
    
  push_back(&q, make_elem(6, 6));
  assert(1 == front(q).val1);
  assert(6 == back(q).val1);
    
  pop_back(&q);
  assert(1 == front(q).val1);
  assert(5 == back(q).val1);
    
  pop_back(&q);
  assert(1 == front(q).val1);
  assert(4 == back(q).val1);
    
  pop_front(&q);
  assert(2 == front(q).val1);
  assert(4 == back(q).val1);
    
  push_front(&q, make_elem(7, 7));
  assert(7 == front(q).val1);
  assert(4 == back(q).val1);
    
  push_front(&q, make_elem(8, 8));
  assert(8 == front(q).val1);
  assert(4 == back(q).val1);
    
  push_front(&q, make_elem(9, 9));
  assert(9 == front(q).val1);
  assert(4 == back(q).val1);
    
  pop_front(&q);
  assert(8 == front(q).val1);
  assert(4 == back(q).val1);
    
  pop_front(&q);
  assert(7 == front(q).val1);
  assert(4 == back(q).val1);
  assert(4 == size(q));
    
  delete_queue(q);
    
  return 0;
}
