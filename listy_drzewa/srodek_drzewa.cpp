#include <utility>
#include <vector>
#include <cassert>

// Napisz funkcję bin_tree srodek(bin_tree t), która w danym drzewie binarnym t znajduje
// taki węzeł, dla którego maksymalna spośród jego odległości od liści jest jak najmniejsza.
// (Mówimy tu o wszystkich liściach drzewa t, a nie tylko tych poniżej danego węzła.)
// Wynikiem powinien być wskaźnik do takiego węzła.

typedef struct node * bin_tree;
struct node {
    int val;
    bin_tree left, right;
};

// Funkcja ta dla każdego wierzchołka liczy głębokości lewego poddrzewa i prawego poddrzewa.
// Para tych wartości jest zapisana do wektora res. W wektorze res wyniki są wpisywane w kolejności:
// wynik dla aktualnego wierzchołka, wyniki z lewego poddrzewa, wyniki z prawego poddrzewa.
//
// Zwraca głębokość aktualnego drzewa.
int depths(bin_tree t, std::vector<std::pair<int, int> > & dep) {
    if (t == NULL) return -1;

    int my_ind = dep.size();
    // Wstawiamy atrapę do wektora res.
    dep.push_back(std::make_pair(0, 0));
    int l = depths(t->left, dep);
    int r = depths(t->right, dep);
    dep[my_ind].first = l;
    dep[my_ind].second = r;
    return 1 + std::max(l, r);
}

// Oblicza optymalny środek w poddrzewie t, zakładając, że maksymalna odległość korzenia t od
// wierzchołka spoza t wynosi d. Funkcja dodatkowo bierze za argument wektor głębokości
// wierzchołków (dep) i indeks i, który będzie inkrementowany w takiej kolejności w jakiej
// były dodawane wierzchołki do wektora dep. Dzięki temu będziemy w stanie odczytać głębokości
// poddrzew dla aktualnego drzewa.
//
// Funkcja zwraca optymalny środek (reprezentowany jako poddrzewo) i
// wartość maksymalnej odległości dla tego środka.
std::pair<bin_tree, int> srodek_aux(bin_tree t, int d, std::vector<std::pair<int, int> > const & dep, int & i){
    if (t == NULL) {
          return std::make_pair<bin_tree, int>(NULL, INT_MAX);
    }
    int my_ind = i;
    i++;

    std::pair<bin_tree, int> l_res = srodek_aux(t->left, std::max(d+1, dep[my_ind].second + 2), dep, i);
    std::pair<bin_tree, int> r_res = srodek_aux(t->right, std::max(d+1, dep[my_ind].first + 2), dep, i);
    int my_val = std::max(d, 1 + std::max(dep[my_ind].first, dep[my_ind].second));

    if (l_res.second < r_res.second && l_res.second < my_val) return l_res;
    if (r_res.second < my_val) return r_res;

    return std::make_pair(t, my_val);
}

bin_tree srodek(bin_tree t) { 
    std::vector<std::pair<int, int> > dep;
    depths(t, dep);
    int i = 0;
    return srodek_aux(t, 0, dep, i).first;
}

int main()
{
    assert(srodek(NULL) == NULL);
    struct node t1 = {1, NULL, NULL};
    assert(srodek(&t1) == &t1);
    struct node t2 = {2, NULL, NULL};
    assert(srodek(&t2) == &t2);
    struct node t3 = {3, &t1, &t2};
    assert(srodek(&t3) == &t3);
    struct node t4 = {4, NULL, NULL};
    struct node t5 = {5, &t4, NULL};
    struct node t6 = {6, NULL, &t5};
    assert(srodek(&t6) == &t5);
    struct node t7 = {7, &t6, NULL};
    struct node t8 = {8, &t3, &t7};
    assert(srodek(&t8) == &t7);
    struct node t9 = {9, &t7, &t3};
    assert(srodek(&t9) == &t7);

    return 0;
}