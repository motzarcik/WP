#include <cassert>
#include <cstdlib>
#include <vector>
#include <iostream>

#include "find_union.h"

// Dana jest prostokątna mapa złóż gazu wraz z odwiertami pobierającymi gaz. Mapa
// jest dana w postaci dwuwymiarowej prostokątnej tablicy liczb całkowitych. Miejsca
// odwiertów są zaznaczone liczbami ujemnymi. Wartość bezwzględna elementu tablicy
// oznacza ilość znajdującego się w danym miejscu gazu.
// Pola niezerowe stykające się bokami tworzą jedno złoże. Odwierty znajdujące się w
// danym złożu pozwalają pobrać tyle gazu ile pól obejmuje złoże, po czym ilość gazu we
// wszystkich polach złoża maleje o 1. Może to spowodować zmniejszenie lub podzielenie
// się złoża. Dalej odwierty pozwalają pobierać gaz z tak zmienionych złóż.
//
// Napisz procedurę gaz : int array array -> int, która obliczy łączną ilość gazu, jaką
// wydobędą odwierty.

int gaz(const std::vector<std::vector<int> > & mapa) {
  if (mapa.size() == 0) return 0;
  const int m = mapa.size();
  const int n = mapa[0].size();

  int res = 0;

  // Inicjalizujemy tablicę mówiącą, czy pobralismy juz gaz z danego pola. 
  std::vector<std::vector<int> > used;
  for (int i = 0; i < m; i++) {
    std::vector<int> used_row(n, 0);
    used.push_back(used_row);
  }

  // Inicjalizujemy struktury find-union.
  std::vector<find_union> find_unions;
  int k = 0;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      find_unions.push_back(create_fu(k));
      k++;
    }
  }

  // Pierwszy element pary to wielkosc zloza, a drugi to współrzędne punktu.
  std::vector<std::pair<int, std::pair<int, int> > > fields;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      fields.push_back(std::make_pair(std::abs(mapa[i][j]), std::make_pair(i, j)));
      if (mapa[i][j] < 0) {
        used[i][j] = 1;
        res -= mapa[i][j];
      }
    }
  }
  sort(fields.begin(), fields.end());

  for (int i = fields.size() - 1; i >= 0; i--) {
    int h = fields[i].first;
    int x = fields[i].second.first;
    int y = fields[i].second.second;

    for (int xx = -1; xx <= 1; xx++) {
      for (int yy = -1; yy <= 1; yy++) {
        // Patrzymy tylko na pola stykające się bokami.
        if ((xx != 0 && yy != 0)  || (xx == 0 && yy == 0)) {
          continue;
        }
        int vx = x + xx;
        int vy = y + yy;

        if (vx < 0 || vx >= m || vy < 0 || vy >= n) {
          continue;
        }
        // Podłączamy zawsze niszy poziom do wyszego.
        if (std::abs(mapa[vx][vy]) < h) {
          continue;
        }

        std::vector<int> to_use;
        if (used[vx][vy] && !used[x][y]) {
          // Parę (x, y) kodujemy jako integer, aby mieć dostęp do tablicy find-union.
          // Jest to potrzebne, aby uywać elements, które zwraca integery.
          to_use = elements(find_unions[x * n + y]);
        } else if (!used[vx][vy] && used[x][y]) {
          to_use = elements(find_unions[vx * n + vy]);
        }
        if (!equivalent(find_unions[x * n + y], find_unions[vx * n + vy])) {
          union_fu(find_unions[x * n + y], find_unions[vx * n + vy]);
        }

        res += to_use.size() * h;
        for (int j = 0; j < to_use.size(); j++) {
          int x = to_use[j] / n;
          int y = to_use[j] % n;
          used[x][y] = 1;
        }
      }
    }
  }

  return res;
}

int main()
{
  const int n = 20;
  const int m = 20;
  int mapa_arr[n][m] = { 
    {-4, 3, 4, 1, 1, 0,-1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, 
    { 4, 3, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 }, 
    { 4, 1, 2, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1 }, 
    { 1, 1, 2, 1, 0, 8, 7, 5, 5, 3, 3, 0, 0, 0, 0, 0, 0, 1, 0, 1 }, 
    { 0, 0, 0, 1, 0, 1, 7, 5, 5, 3, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1 }, 
    { 1, 1, 0, 1, 0, 1, 7, 5, 5, 3, 1, 1, 1, 0, 0, 1, 0, 1, 0, 1 }, 
    { 1, 1, 0, 1, 0, 1, 7, 7, 7, 7, 7, 7, 7, 0, 0, 1, 0, 1, 0, 1 }, 
    { 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 8, 0, 0, 1, 0, 1, 0, 1 }, 
    { 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 8, 0, 0, 1, 0, 1, 0, 1 }, 
    { 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 8, 9, 3, 1, 0, 1, 0, 1 }, 
    { 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 3, 1, 0, 1, 0, 1 }, 
    { 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 3, 1, 0, 1, 0, 1 }, 
    {-7, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 3, 1, 0, 1, 0, 1 }, 
    { 3, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 3, 1, 0, 1, 0, 1 }, 
    { 3, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1 }, 
    { 3, 5, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1 }, 
    { 1, 2, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1 }, 
    { 1, 4, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1 }, 
    { 4, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 }, 
    { 2, 3, 5, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }};

  std::vector<std::vector<int> > mapa;
  for (int i = 0; i < m; i++){
    std::vector<int> row(mapa_arr[i], mapa_arr[i] + n);
    mapa.push_back(row);
  }

  assert(gaz(mapa) == 143);

  return 0;
}