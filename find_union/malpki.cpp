#include <cassert>
#include <cstdlib>
#include <vector>

#include "find_union.h"

// Na drzewie wisi n małpek ponumerowanych od 1 do n. Małpka z nr 1 trzyma się gałęzi ogonkiem.
// Pozostałe małpki albo są trzymane przez inne małpki, albo trzymają się innych małpek, albo
// jedno i drugie równocześnie. Każda małpka ma dwie przednie łapki, każdą może trzymać co najwyżej
// jedną inną małpkę (za ogon). Rozpoczynając od chwili 0, co sekundę jedna z małpek puszcza jedną
// łapkę. W ten sposób niektóre małpki spadają na ziemię, gdzie dalej mogą puszczać łapki
// (czas spadania małpek jest pomijalnie mały). Kazda małpka kiedyś puści te, które trzyma.
//
// Zaprojektuj algorytm, który na podstawie pisu łapek puszczanych w kolejnych chwilach,
// dla każdej małpki wyznaczy moment, kiedy spadnie ona na ziemię.

std::vector<int> malpki(const std::vector<std::pair<int, int> > & puszczanie) {
  std::vector<int> res(puszczanie.size() / 2 + 1, -1);
  std::vector<find_union> elems;
  for (int i = 0; i < res.size(); i++) {
    elems.push_back(create_fu(i));
  }

  for (int i = puszczanie.size() - 1; i >= 0; i--) {
    int m1 = puszczanie[i].first;
    int m2 = puszczanie[i].second;
    std::vector<int> fall;
    if (equivalent(elems[m1], elems[1]) && !equivalent(elems[m2], elems[1])) {
      fall = elements(elems[m2]);
    } else if (!equivalent(elems[m1], elems[1]) && equivalent(elems[m2], elems[1])) {
      fall = elements(elems[m1]);
    }
    for (int j = 0; j < fall.size(); j++) {
      res[fall[j]] = i;
    }
    if (!equivalent(elems[m1], elems[m2])) {
      union_fu(elems[m1], elems[m2]);
    }
  }
  return res;
}

int main()
{
  std::vector<std::pair<int, int> > puszczanie;
  puszczanie.push_back(std::make_pair(6, 9));
  puszczanie.push_back(std::make_pair(9, 3));
  puszczanie.push_back(std::make_pair(2, 9));
  puszczanie.push_back(std::make_pair(9, 1));
  puszczanie.push_back(std::make_pair(1, 8));
  puszczanie.push_back(std::make_pair(8, 6));
  puszczanie.push_back(std::make_pair(10, 1));
  puszczanie.push_back(std::make_pair(10, 2));
  puszczanie.push_back(std::make_pair(3, 10));
  puszczanie.push_back(std::make_pair(3, 2));
  puszczanie.push_back(std::make_pair(4, 6));
  puszczanie.push_back(std::make_pair(6, 4));
  puszczanie.push_back(std::make_pair(4, 5));
  puszczanie.push_back(std::make_pair(1, 7));
  puszczanie.push_back(std::make_pair(2, 1));
  puszczanie.push_back(std::make_pair(7, 2));
  puszczanie.push_back(std::make_pair(5, 7));
  puszczanie.push_back(std::make_pair(5, 6));
  puszczanie.push_back(std::make_pair(2, 3));
  puszczanie.push_back(std::make_pair(8, 2));

  std::vector<int> res = malpki(puszczanie);
  assert(res[1] == -1);
  assert(res[2] == 14);
  assert(res[3] == 14);
  assert(res[4] == 12);
  assert(res[5] == 14);
  assert(res[6] == 14);
  assert(res[7] == 14);
  assert(res[8] == 14);
  assert(res[9] == 3);
  assert(res[10] == 8);

  return 0;
}