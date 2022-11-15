#include <assert.h>
#include <stdlib.h>

#include "kolejka.h"

// Dana jest tablica liczb całkowitych {x_1, ... x_n}. Dla każdego i trzeba policzyć największe 
// takie k_i, że x_i = max(x_{i - k_i + 1}, x_{i - k_i + 2}, ..., x_i). Przyjmujemy, że x_0 to nieskończoność.
int * widoczne (int* tab, int n) {
  int* wynik = (int*) malloc(n * sizeof(int));
  
  // W kolejce trzymamy pary (element tablicy tab, indeks elementu).
  // Jeżeli w kolejce pamiętamy element odpowiadający wartości x, to 
  // nie musimy pamiętać wcześniejszych elementów mniejszych niż x.  
  queue q = make_queue();
  
  for (int i = 0; i < n; i++) {
    while (size(q) > 0 && back(q).val1 <= tab[i]){
      pop_back(&q);
    }
    int pocz = -1;
    if (size(q) > 0) {
      pocz = back(q).val2;
    }
    wynik[i] = i - pocz;
    push_back(&q, make_elem(tab[i], i));
  }
  
  delete_queue(q);
  
  return wynik;
}


int main()
{
  int tab[20] = {0, 5, 10, 0, 4, 8, 9, 0, 2, 3, 0, 1, 9, 10, 0, 2, 0, 1, 3, 10};
  
  int *wynik = widoczne(tab, 20);
  assert(wynik[0] == 1);
  assert(wynik[1] == 2);
  assert(wynik[2] == 3);
  assert(wynik[3] == 1);
  assert(wynik[4] == 2);
  assert(wynik[5] == 3);
  assert(wynik[6] == 4);
  assert(wynik[7] == 1);
  assert(wynik[8] == 2);
  assert(wynik[9] == 3);
  assert(wynik[10] == 1);
  assert(wynik[11] == 2);
  assert(wynik[12] == 10);
  assert(wynik[13] == 14);
  assert(wynik[14] == 1);
  assert(wynik[15] == 2);
  assert(wynik[16] == 1);
  assert(wynik[17] == 2);
  assert(wynik[18] == 5);
  assert(wynik[19] == 20);
  
  free (wynik);
  return 0;
}
