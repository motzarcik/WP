//Grzegorz Pierczyński
//Banknoty, XII OI (szczegółowa treść zadania i omówienie:
//  https://oi.edu.pl/static/attachment/20110811/oi12.pdf)
//Testy dostępne na platformie Szkopuł:
//https://szkopul.edu.pl/problemset/problem/ucULQRwTgKsiCRWkf0t9GoqH/site/?key=statement

#include <iostream>
#include <deque>
#include <vector>
using namespace std;

#define N 201
#define K 20001

int n, k, b[N], c[N], wynik[N][K], ile[N][K];

int main() {
    ios_base::sync_with_stdio(0);

    cin >> n; //liczba nominałów
    for (int i = 1; i <= n; i++)
        cin >> b[i]; //wartości nominałów
    for (int i = 1; i <= n; i++)
        cin >> c[i]; //liczności nominałów
    cin >> k; //kwota do wydania

    /*
    Ogólna idea rozwiązania:
        * Niech wynik[i][j] oznacza optymalną liczbę banknotów dla kwoty j przy
        dodatkowym założeniu że wykorzystujemy wyłącznie nominały o indeksach
        1, 2, ..., i.
        * Wtedy wynik[n][k] jest rozwiązaniem zadania. Przy okazji trzymamy
        tablicę ile[i][j] która trzyma liczbę banknotów nominału i potrzebną do
        wypłacenia wynik[i][j]. Na tej podstawie możemy już wyliczyć dokładne
        rozwiązanie.
        * Zauważmy, że moglibyśmy wyliczać te tablice ze wzorów:
        wynik[i][j] = min_{0 <= l <= c[i]} wynik[i-1][j-l*b[i]]+l
        ile[i] = argmin_{0 <= l <= c[i]} wynik[i-1][j-l*b[i]]+l
        Bezpośrednie zaaplikowanie tych wzorów daje rozwiązanie w O(nk^2).
        * Teraz tak: chcemy przyspieszyć wyliczanie tych minimów. Bazujemy na
        pomyśle, że jeśli wyliczyliśmy już wynik[i][j-l*b[i]] dla wszystkich
        l > 0, to możemy to wykorzystać przy obliczaniu wynik[i][j].
        * Pierwsza zmiana: dla ustalonego i, zamiast wyliczać wynik[i][j] po
        kolei dla j = 0, 1, 2, ..., k będziemy "skakać" co b[i]. Dla j < b[i]
        jest łatwo; po prostu wynik[i][j] = wynik[i-1][j].
        * Idealnie by było mieć dwustronną kolejkę minimów przechowującą nam
        prefiksowe minima z ciągu wynik[i-1][j], wynik[i-1][j-b[i]]+1,
        wynik[i-1][j-2*b[i]]+2, wynik[i-1][j-3*b[i]]+3, ... Czyli liczby postaci
        wynik[i-1][j-l*b[i]]+l -- a dokładniej, pary liczb, wraz z liczbą l dla
        której wartość wynik[i-1][j-l*b[i]]+l została osiągnięta. To są nasze
        potencjalne wartości tablic wynik i ile. Gdybyśmy mieli taką kolejkę,
        moglibyśmy po prostu brać z niej pierwszą wartość. Chyba, że wtedy
        ile[i][j] przekroczyłoby nam c[i], to wtedy ją odrzucamy (nigdzie dalej
        już nam się nie przyda) i bierzemy kolejne minimum z kolejki.
        * Tylko jak utrzymywać taką kolejkę? Zauważmy, że jeśli chcielibyśmy ją
        trzymać explicite, to po wykonaniu każdego skoku o b[i] musielibyśmy
        podwyższać wszystkie wczesniej wrzucone na nią wartości na niej o 1. Nie
        brzmi to jak coś co da się robić szybko.
        * Spostrzeżenie: ale przecież takie podwyższanie wszystkich liczb o taką
        samą stałą nic nie zmienia w kontekście brania minimum! Zamiast wszystko
        podwyższać, wygodniej będzie nam założyć z góry, że wszystkie wartości
        na kolejce są obniżone o pewną (rosnącą z każdym skokiem o 1) stałą.
        * Konkretnie, ta stała będzie zawsze równa j/b[i].
        * Ostatecznie wychodzi nam rozwiązanie w O(nk).
    */

    //inicjujemy pierwszy wiersz tablic
    //dla i=j=0 wynik to 0, dla i=0, j>0 wynik to +inf, tzn. nie da się wypłacić
    //możemy użyć K jako +inf
    for (int j = 1; j <= k; j++) {
        wynik[0][j] = K;
        ile[0][j] = K;
    }
    deque<pair<int, int> > mini;
    for (int i = 1; i <= n; i++) {
        for (int r = 0; r < b[i]; r++) {
            mini.clear();
            for (int j = r; j <= k; j += b[i]) {
                int przesuniecie = j/b[i];
                pair<int, int> akt =
                        make_pair(-przesuniecie, wynik[i-1][j]-przesuniecie);
                while (!mini.empty()
                        and mini.back().second > akt.second) {
                    mini.pop_back();
                }
                mini.push_back(akt);
                while (mini.front().first + przesuniecie > c[i]) {
                    mini.pop_front();
                }
                //wiemy że mini niepusta, bo wrzuciliśmy wcześniej na nią akt
                ile[i][j] = mini.front().first + przesuniecie;
                wynik[i][j] = mini.front().second + przesuniecie;
            }
        }
    }
    cout << wynik[n][k] << "\n";
    //z tablicy ile będziemy odczytywać liczności poszczególnych nominałów w
    //odwróconej kolejności
    vector<int> wynik_dokladny(n);
    for (int i = n; i > 0; i--) {
        wynik_dokladny[i] = ile[i][k];
        k -= ile[i][k] * b[i];
    }
    for (int i = 1; i <= n; i++) {
        cout << wynik_dokladny[i] << " ";
    }
    cout << "\n";
    return 0;
}
