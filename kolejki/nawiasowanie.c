#include <cassert>
#include <cstdio>
#include <deque>
#include <utility>


// Dana jest tablica liczb całkowitych {x_1, ... x_n}, reprezentujących nawiasy. Liczba dodatnia x 
// reprezentuje nawias otwierający danego typu; nawias zamykający tego samego typu reprezentowany jest jako -x.
// Przykładowo, wyrażenie (())[}(]] może być reprezentowane jako [1, 1, -1, -1, 2, -3, 1, -2, -2].
// Napisz funkcję int nawiasy(int tab[], int n), która zwróci maksymalną długość spójnego fragmentu napisu, 
// który jest poprawnym wyrażeniem nawiasowym.

int nawiasy (int tab[], int n) {
  int wynik = 0;
  
  // W kolejce trzymamy pary (element tablicy tab, indeks elementu).
  // W kolejce pamiętamy tylko elementy odpowiadające nawiasom otwierającym  
  std::deque<std::pair<int, int>> q;
  // Strażnik, żeby zapewnić, że kolejka nie jest pusta. Elementy po strażniku, które nie są w kolejce 
  // tworzą poprawne nawiasowanie.
  q.push_back(std::make_pair(0, -1));
  
  for (int i = 0; i < n; i++) {
    if (tab[i] > 0) {
      q.push_back(std::make_pair(tab[i], i));
    }
    if (tab[i] < 0) {
      if (q.back().first == -1 * tab[i]) {
        q.pop_back();
        wynik = std::max(wynik, (i - q.back().second));
      } else {
        // Czyścimy kolejkę.
        q.push_back(std::make_pair(0, i));
      }
    }
  }
  
  return wynik;
}


int main()
{
  int tab1[9] = {1, 1, -1, -1, 2, -3, 1, -2, -2};
  assert(nawiasy(tab1, 9) == 4);
  
  int tab2[18] = {1, 1, 1, -1, -1, -1, -1, -3, 1, 2, -2, -1, 3, 1, -1, -3, 2, 3};
  assert(nawiasy(tab2, 18) == 8);
  
  int tab3[20] = {2, 1, 1, 1, -1, -1, -1, -1, -3, 1, 2, -3, -1, 3, 1, -1, -3, 2, 3, -1};
  assert(nawiasy(tab3, 20) == 6);
  return 0;
}
