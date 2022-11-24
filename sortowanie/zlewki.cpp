#include <vector>
#include <deque>

// Mamy n kubeczków z wodą, ponumerowanych od 1 do n (n > 0). W kubeczku nr i znajduje się x_i wody, przy 
// czym 0 < x_1 <= x_2 <= x_3 ... <= x_n. Powtarzamy k razy (dla k < n nastepującą czynność: wybieramy dwa 
// niepuste kubeczki zawierające jak najmniej wody i wodę z jednego kubeczka dolewamy do drugiego.
// Napisz procedurę int zlewki(vector<int> x, int k), która dla danych liczb {x_1, x_2, ..., x_n}
// oraz liczby k określa ile jest wody w najmniej wypełnionym kubeczku po wykonaniu k operacji przelewania.

int take_min(std::vector<int>* x, std::deque<int>* q, int* i) {
  if (*i == x->size()) {
    int res = q->front();
    q->pop_front();
    return res;
  }
  if (q->empty()) {
    (*i)++;
    return (*x)[*i - 1];
  }
  if (q->front() < (*x)[*i]) {
    int res = q->front();
    q->pop_front();
    return res;
  }
  (*i)++;
  return (*x)[*i - 1];
}

int zlewki(std::vector<int> x, int k) {
  std::deque<int> q;
  int i = 0;
  for (int j = 0; j < k; j++) {
    int val1 = take_min(&x, &q, &i);
    int val2 = take_min(&x, &q, &i);
    q.push_back(val1 + val2);
  }

  return take_min(&x, &q, &i);
}

int main()
{
  int x_arr[] = {1, 2, 2, 3, 3, 4, 10, 20, 20, 30};
  std::vector<int> x(x_arr, x_arr + 10);
  int w = zlewki(x, 1);
  assert(w == 2);
  w = zlewki(x, 2);
  assert(w == 3);
  w = zlewki(x, 3);
  assert(w == 4);
  w = zlewki(x, 4);
  assert(w == 6);
  w = zlewki(x, 5);
  assert(w == 10);
  w = zlewki(x, 6);
  assert(w == 20);
  w = zlewki(x, 7);
  assert(w == 25);
  w = zlewki(x, 8);
  assert(w == 40);
  w = zlewki(x, 9);
  assert(w == 95);

  return 0;
}