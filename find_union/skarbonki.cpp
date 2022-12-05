#include <cassert>
#include <cstdlib>

#include "find_union.h"

// Mamy n skarbonek otwieranych kluczykami. Do każdej skarbonki jest inny kluczyk. Kluczyki do 
// skarbonek są powrzucane do skarbonek -- dowolnie. Żeby dostać się do zawartości skarbonki,
// skarbonkę można otworzyć kluczykiem (jeśli się go ma) lub ją rozbić. Skarbonki są ponumerowane
// od 0 do n-1. Na podstawie tablicy a (rozmiaru n), takiej, że a[i] = numer skarbonki, w której
// znajduje się kluczyk do skarbonki numer i, oblicz minimalną liczbę skarbonek, które należy rozbić,
// tak aby dostać się do zawartości wszystkich skarbonek.

int skarbonki(int * a, int n) {
  std::vector<find_union> elems;
  for (int i = 0; i < n; i++) {
    elems.push_back(create_fu(i));
  }
  for(int i = 0; i < n; i++) {
    union_fu(elems[i], elems[a[i]]);
  }

  int res = 0;
  std::vector<bool> counted(n, false);
  for (int i = 0; i < elems.size(); i++) {
    if (!counted[find(elems[i])]) {
      counted[find(elems[i])] = true;
      res++;
    }
  }
  for (int i = 0; i < elems.size(); i++)  {
    free(elems[i]);
  }
  return res;
}

int main()
{
  int tab1[3] = {0, 1, 2};
  assert(skarbonki(tab1, 3) == 3);

  int tab2[3] = {1, 2, 0};
  assert(skarbonki(tab2, 3) == 1);

  int tab3[20] = {0, 1, 2, 4, 5, 6, 7, 3, 3, 12, 11, 12, 5, 15, 15, 15, 17, 18, 19, 16};
  assert(skarbonki(tab3, 20) == 6);

  return 0;
}