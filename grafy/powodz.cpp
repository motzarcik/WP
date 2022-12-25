#include <cassert>
#include <cstdlib>
#include <vector>
#include <utility>
#include <queue>
#include <iostream>

// Dana jest mapa topograficzna miasta położonego w kotlinie, w postaci prostokątnej tablicy typu 
// vector<vector<pair<int, bool>>>. Liczby określają wysokość kwadratów jednostkowych, a wartości
// logiczne określają, czy dany kwadrat należy do terenu miasta. Przyjmujemy, że teren poza mapą
// jest położony wyżej niż jakikolwiek kwadrat na mapie.Miasto zostało całkowicie zalane. Żeby
// je osuszyć należy w kotlinie rozmieścić pewną liczbę pomp. Każda z pomp wypompowuję wodę aż
// do osuszenia kwadratu jednostkowego, na którym się znajduje. Osuszenie dowolnego kwadratu pociąga
// za sobą obniżenie poziomu wody lub osuszenie kwadratów jednostkowych, z których woda jest w stanie
// spłynąć do kwadratu, na którym znajduje się pompa. Woda może przepływać między kwadratami, które
// stykają się bokami.
//
// Wyznacz minimalną liczbę pomp koniecznych do osuszenia miasta. Teren nie należący do miasta
// nie musi być osuszony. Miasto nie musi tworzyć spójnego obszaru.

int powodz(const std::vector<std::vector<std::pair<int, bool> > > & mapa) {
  if (mapa.size() == 0) return 0;

  // Inicjalizujemy tablicę mówiącą, czy przeszukaliśmy juz dany wierzcholek grafu. 
  std::vector<std::vector<int> > visited;
  for (int i = 0; i < mapa.size(); i++) {
    std::vector<int> visited_row(mapa[i].size(), 0);
    visited.push_back(visited_row);
  }

  // Pierwszy element pary to wysokość, a drugi to współrzędne punktu.
  std::vector<std::pair<int, std::pair<int, int> > > city;
  for (int i = 0; i < mapa.size(); i++) {
    for (int j = 0; j < mapa[i].size(); j++) {
      if (mapa[i][j].second) {
        city.push_back(std::make_pair(mapa[i][j].first, std::make_pair(i, j)));
      } 
    }
  }
  sort(city.begin(), city.end());

  int result = 0;
  // Kolejka priorytetowa zwracająca minima. Będziemy w niej trzymać wierzchołki z priorytetem
  // odpowiadającym wysokości.
  std::priority_queue<std::pair<int, std::pair<int, int> >, 
                      std::vector<std::pair<int, std::pair<int, int> > >,
                      std::greater<std::pair<int, std::pair<int, int> > > > q;

  int i = 0;
  while (true) {  
    int x = city[i].second.first;
    int y = city[i].second.second;
    if (!visited[x][y]) {
      q.push(city[i]);
      visited[x][y] = 1;
      result++;
    }
    i++;
    if (i == city.size() - 1) {
      return result;
    }

    int next_height = city[i].first;
    while(!q.empty() && q.top().first <= next_height) {
      int cur_height = q.top().first;
      int x = q.top().second.first;
      int y = q.top().second.second;
      q.pop();
      for (int xx = -1; xx <= 1; xx++) {
        for (int yy = -1; yy <= 1; yy++) {
          // Patrzymy tylko na pola stykające się bokami.
          if (xx != 0 && yy != 0) {
            continue;
          }
          int vx = x + xx;
          int vy = y + yy;
          if (vx < 0 || vx >= mapa[0].size() || vy < 0 || vy >= mapa.size()) {
            continue;
          }
          if (visited[vx][vy]) {
            continue;
          }
          visited[vx][vy] = 1;
          q.push(std::make_pair(std::max(mapa[vx][vy].first, cur_height), std::make_pair(vx, vy)));
        }
      }
    }
  }
  return 0;
}

int main()
{
  const int n = 20;
  const int m = 20;

  int czy_miasto_arr[n][m] = { 
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, 
    { 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, 
    { 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1 }, 
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, 
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, 
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, 
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, 
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, 
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, 
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, 
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, 
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, 
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, 
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, 
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, 
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, 
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, 
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, 
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }, 
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }};

  int miasto_wysokosci_arr[n][m] = { 
    { 0, 1, 1, 6, 6, 6, 1, 7, 8, 9, 9, 6, 6, 6, 6, 6, 6, 6, 6, 9 }, 
    { 1, 2, 0, 4, 4, 4, 2, 4, 5, 9, 9, 7, 9, 9, 9, 9, 9, 9, 6, 9 }, 
    { 5, 1, 0, 5, 4, 3, 3, 5, 7, 9, 9, 7, 9, 1, 8, 8, 8, 9, 6, 9 }, 
    { 1, 3, 2, 6, 4, 3, 3, 4, 9, 8, 9, 7, 9, 9, 9, 9, 7, 9, 6, 9 }, 
    { 1, 1, 0, 7, 6, 5, 3, 7, 9, 8, 9, 7, 7, 7, 7, 7, 7, 9, 6, 9 }, 
    { 9, 9, 9, 9, 9, 9, 9, 9, 9, 8, 9, 9, 9, 9, 9, 9, 9, 9, 6, 9 }, 
    { 1, 1, 0, 1, 9, 8, 7, 8, 9, 7, 7, 5, 6, 6, 6, 6, 6, 6, 6, 9 }, 
    { 1, 1, 0, 1, 9, 1, 7, 6, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9 }, 
    { 1, 1, 0, 1, 9, 1, 7, 6, 9, 8, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8 }, 
    { 1, 1, 0, 1, 9, 1, 7, 4, 9, 8, 9, 8, 9, 8, 9, 9, 9, 9, 9, 9 }, 
    { 1, 1, 0, 1, 9, 1, 0, 1, 9, 8, 9, 8, 9, 8, 8, 8, 8, 8, 8, 9 }, 
    { 1, 1, 0, 1, 9, 1, 4, 3, 9, 8, 9, 8, 9, 9, 9, 8, 8, 8, 8, 9 }, 
    { 1, 1, 0, 1, 9, 1, 5, 5, 9, 8, 9, 8, 9, 8, 8, 8, 8, 9, 9, 8 }, 
    { 1, 1, 0, 1, 9, 1, 6, 7, 9, 8, 8, 8, 9, 8, 9, 9, 9, 9, 9, 8 }, 
    { 1, 1, 0, 1, 9, 1, 8, 8, 9, 8, 9, 8, 9, 8, 7, 7, 7, 8, 8, 8 }, 
    { 1, 1, 0, 1, 9, 1, 1, 1, 9, 8, 9, 8, 9, 9, 9, 9, 9, 8, 8, 9 }, 
    { 1, 1, 0, 1, 9, 2, 3, 4, 9, 8, 9, 8, 9, 9, 9, 9, 9, 9, 9, 9 }, 
    { 1, 1, 0, 0, 9, 9, 9, 5, 9, 8, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8 }, 
    { 0, 1, 1, 1, 9, 9, 9, 6, 9, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9 }, 
    { 0, 0, 0, 1, 9, 6, 6, 6, 9, 8, 8, 8, 8, 8, 8, 8, 8, 7, 7, 7 }};

  std::vector<std::vector<std::pair<int, bool> > > mapa;
  for (int i = 0; i < m; i++){
    std::vector<std::pair<int, bool> > row;
    for (int j = 0; j < n; j++) {
      row.push_back(std::make_pair(miasto_wysokosci_arr[i][j], czy_miasto_arr[i][j]));
    }
    mapa.push_back(row);
  }

  assert(powodz(mapa) == 9);
  return 0;
}