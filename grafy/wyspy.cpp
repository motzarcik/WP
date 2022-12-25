#include <cassert>
#include <cstdlib>
#include <vector>
#include <deque>
#include <iostream>

// Dana jest prostokątna mapa n x m przedstawiająca archipelag na oceanie, reprezentowana jako vector<vector<int>>.
// Elementy tablicy równe 1 reprezentują ląd, a 0 wodę. Na zewnątrz mapy znajduje się ocean.
// Wyspy na oceanie są wyspami rzędu 1. Na wyspach rzędu 1 mogą znajdować się jeziora rzędu 1, na nich
// mogą znajdować się wyspy rzędu 2 itd. Ogólnie:
//  * ocean ma rząd 0,
//  * wyspa na jeziorze (lub oceanie) rzędu k ma rząd k+1, 
//  * jezioro na wyspie rzędu k ma rząd k.
// Pola wody przylegające do siebie bokami lub rogami należą do tego samego jeziora (lub oceanu).
// Pola lądu przylegające do siebie bokami należą do tej samej wyspy. Napisz procedurę int wyspa(const vector<vector<int>> &mapa),
// która dla danej mapy zwróci maksymalny rząd wyspy na mapie. Jeżeli na oceanie nie ma żadnej wyspy, to procedura powinna zwrócić 0.

int wyspa(const std::vector<std::vector<int> > & mapa) {
  if (mapa.size() == 0) return 0;

  // Inicjalizujemy tablicę mówiącą, czy przeszukaliśmy juz dany wierzcholek grafu. 
  std::vector<std::vector<int> > visited;
  for (int i = 0; i < mapa.size(); i++) {
    std::vector<int> visited_row(mapa[i].size(), 0);
    visited.push_back(visited_row);
  }

  // Zmienna równa 1 jezli aktualnie przeszukujemy powierzchnię oceanu, lub równa 0, jezeli przeszukujemy ląd.
  int ocean = 1;

  // W jednej kolejce trzymamy wierzchołki do obecnego przeszukiwania, a w next, do kolejnego.
  std::deque<std::pair<int, int> > current;
  std::deque<std::pair<int, int> > next;

  // Inicjalizujemy kolejkę current, na otaczający ocean.
  for (int i = -1; i <= mapa[0].size(); i++) {
    current.push_back(std::make_pair(i, -1));
    current.push_back(std::make_pair(i, mapa.size()));
  }
  for (int i = 0; i <= mapa.size(); i++) {
    current.push_back(std::make_pair(-1, i));
    current.push_back(std::make_pair(mapa[0].size(), i));
  }

  int result = 0;
  while (true) {
    while (!current.empty()) {
      std::pair<int, int> vertex = current.back();
      current.pop_back();
      for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
          // dla lądu nie sprawdzamy pól stykających się rogami. 
          if (!ocean && i != 0 && j != 0) {
            continue;
          }
          int vx = vertex.first + i;
          int vy = vertex.second + j;
          // Kolejny punkt poza mapą.
          if (vx < 0 || vx >= mapa[0].size() || vy < 0 || vy >= mapa.size()) {
            continue;
          }
          if (visited[vx][vy]) {
            continue;
          }

          visited[vx][vy] = 1;
          if ((ocean && mapa[vx][vy] == 0) || (!ocean && mapa[vx][vy] == 1)){
            current.push_back(std::make_pair(vx, vy));
          } else {
            next.push_back(std::make_pair(vx, vy));
          }
        }
      }
    }

    if (next.empty()) {
      return result;
    }

    current = next;
    next = std::deque<std::pair<int, int> >();

    if (ocean) {
      result++;
      ocean = 0;
    } else {
      ocean = 1;
    }
  }
}

int main()
{
  const int n = 20;
  const int m = 20;

  int mapa_arr[n][m] = { 
    { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, 
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 }, 
    { 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1 }, 
    { 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1 }, 
    { 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1 }, 
    { 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1 }, 
    { 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1 }, 
    { 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1 }, 
    { 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1 }, 
    { 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1 }, 
    { 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1 }, 
    { 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1 }, 
    { 1, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1 }, 
    { 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1 }, 
    { 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1 }, 
    { 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1 }, 
    { 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1 }, 
    { 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1 }, 
    { 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 }, 
    { 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }};

  std::vector<std::vector<int> > mapa;
  for (int i = 0; i < m; i++){
    std::vector<int> row(mapa_arr[i], mapa_arr[i] + n);
    mapa.push_back(row);
  }

  assert (wyspa(mapa) == 4);
  return 0;
}