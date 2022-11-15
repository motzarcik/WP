// Typ elementów, które będą przechowywane w kolejce.

typedef struct elem {   
   int val1;
   int val2;
} elem;

// Tworzy element z dwóch wartości.
elem make_elem(int val1, int val2);

typedef struct queue {   
   int start;     // indeks pierwszego elementu w kolejce
   int cnt;       // liczba elementów w kolejce
   elem* data;    // tablica elementów 
   int data_size; // rozmiar tablicy
} queue;

// Tworzy nową kolejkę.
queue make_queue();

// Zwalnia pamięć kolejki. 
void delete_queue(queue q);

// Liczba elementów.
int size(queue q);

// Dodajemy element na koniec kolejki. 
void push_back(queue* q, elem e);

// Dodajemy element na początek kolejki. 
void push_front(queue* q, elem e);

// Zwracamy element na początku kolejki. 
elem front(queue q);

// Zwracamy element na końcu kolejki. 
elem back(queue q);

// Usuwamy element na początku kolejki i zwracamy go. 
elem pop_front(queue* q);

// Usuwamy element na końcu kolejki i zwracamy go. 
elem pop_back(queue* q);
