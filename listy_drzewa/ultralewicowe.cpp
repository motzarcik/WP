#include <utility>
#include <cassert>

// Drzewo nazwiemy ultralewicowym jeśli głębokości kolejnych liści (od lewej do prawej)
// tworzą ciąg nierosnący. Napisz funkcję bool ultraleft(bin_tree t), która sprawdza,
// czy dane drzewo jest ultralewicowe.

typedef struct node * bin_tree;
struct node {
    int val;
    bin_tree left, right;
};

// Para intów oznacza (głębokość skrajnego lewego liścia, głębokość skrajnego prawego liścia).
std::pair<bool, std::pair<int, int> > ultraleft_aux(bin_tree t){
  if (t == NULL) {
      return std::make_pair(true, std::make_pair(0, 0));
  }
  std::pair<bool, std::pair<int, int> > l_res = ultraleft_aux(t->left);
  std::pair<bool, std::pair<int, int> > r_res = ultraleft_aux(t->right);

  std::pair<int, int> depths = std::make_pair(l_res.second.first + 1, r_res.second.second + 1);
  if (!l_res.first || !r_res.first) {
    return std::make_pair(false, depths);
  }
  if (l_res.second.second >= r_res.second.first) {
    return std::make_pair(true, depths);
  }
  return std::make_pair(false, depths);
}

bool ultraleft(bin_tree t) {
  return ultraleft_aux(t).first;
}

int main()
{
  assert(ultraleft(NULL) == true);
  struct node t1 = {1, NULL, NULL};
  assert(ultraleft(&t1) == true);
  struct node t2 = {2, NULL, NULL};
  assert(ultraleft(&t2) == true);
  struct node t3 = {3, &t1, &t2};
  assert(ultraleft(&t3) == true);
  struct node t4 = {4, NULL, NULL};
  assert(ultraleft(&t4) == true);
  struct node t5 = {5, &t4, NULL};
  assert(ultraleft(&t5) == true);
  struct node t6 = {6, NULL, &t4};
  assert(ultraleft(&t6) == false);
  struct node t7 = {7, &t3, &t4};
  assert(ultraleft(&t7) == true);
  struct node t8 = {8, &t3, &t6};
  assert(ultraleft(&t8) == false);
  struct node t9 = {9, &t4, &t3};
  assert(ultraleft(&t9) == false);

  return 0;
}