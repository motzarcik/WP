#include <vector>
#include <deque>

// Tomek chciałby popłynąć z kolegami jachtem w rejs trwający k dni. Potrzebuje zebrać grupę kolegów, którzy
// chcą i mogą z nim popłynąć. Od każdego ze swoich kolegów dowiedział się od kiedy do kiedy (włącznie)
// dysponuje wolnym czasem. Teraz zastanawia się, kiedy wyruszyć w rejs, tak żeby mogli żeglować jak
// największą grupą. W trakcie rejsu koledzy Tomka mogą się zmieniać (o ile obie osoby mają tego samego
// dnia wolne Napisz funkcję int rejs(int k, vector<int> start, vector<int> end), która mając daną liczbę k, 
// początki oraz końce dostępności kolegów Tomka, zwróci maksymalną wielkość załogi (nie licząc Tomka).
//
// Jeżeli rejsu nie da się zorganizować, to poprawnym wynikiem jest 0. 
// Na przykład: rejs(20, {12, 48, 28, 55, 0, 25}, {36, 100, 70, 80, 65, 30}) == 3.

typedef struct event {   
   int time;
  // status to +1 lub -1: +1 oznacza, ze kolega w tym momencie rozpoczyna swoją dostępność,
  // a -1 oznacza, ze kończy się jego okres dostępności (ostatni moment dostepnosci to (time-1)).
   int status;
} event;

typedef struct availability {   
   // Początkowy czas od którego ta liczba osób jest dostępna.
   int time;
   int num_available;
} availability;

bool compare_events(event a, event b){
	if(a.time < b.time)
		return 1;
	else 
		return 0;
}

// kolega i zaczyna być dostępny w czasie start[i], a jego ostatni dzień dostępności to (end[i] - 1).
int rejs(int k, std::vector<int> start, std::vector<int> end) {
  std::vector<event> events; 
  for (int i = 0; i < start.size(); i++) {
    event e = {start[i], 1};
    events.push_back(e);
  }
  for (int i = 0; i < end.size(); i++) {
    event e = {end[i], -1};
    events.push_back(e);
  }
  sort(events.begin(), events.end(), compare_events);

  // Kolejka monotoniczna. Jej najmniejszy element będzie zawsze na początku.
  std::deque<availability> q;
  int result = 0;

  for (int i = 0; i < events.size(); i++) {
    // Liczba dostępnych kolegów w czasie events[i].time.
    int available;
    if (!q.empty()) {
      available = q.back().num_available + events[i].status;
    } else {
      assert(events[i].status == 1);
      available = 1;
    }

    int time_before_change = events[i].time - 1;
    while (!q.empty() && (time_before_change - q.front().time + 1 >= k)) {
      result = std::max(result, q.front().num_available);
      q.pop_front();
    }

    // Czas z którym dodamy available do kolejki.
    int t =  events[i].time;
    while (!q.empty() && (q.back().num_available >= available)) {
      t = q.back().time;
      q.pop_back();
    }
    
    availability av = {t, available};
    q.push_back(av);
  }

  return result;
}


int main()
{
  int start_arr[] = {12, 48, 28, 55, 0, 25};
  std::vector<int> start(start_arr, start_arr + 6);
  int end_arr[] = {36, 100, 70, 80, 65, 30};
  std::vector<int> end(end_arr, end_arr + 6);
  int w = rejs(20, start, end);
  assert(w == 3);

  int start_arr2[] = {1, 2, 4, 5, 7, 8};
  std::vector<int> start2(start_arr2, start_arr2 + 6);
  int end_arr2[] = {2, 3, 5, 6, 8, 9};
  std::vector<int> end2(end_arr2, end_arr2 + 6);
  w = rejs(2, start2, end2);
  assert(w == 1);
  w = rejs(3, start2, end2);
  assert(w == 0);

  int start_arr3[] = {17, 17, 16, 4, 7, 1};
  std::vector<int> start3(start_arr3, start_arr3 + 6);
  int end_arr3[] = {22, 21, 25, 8, 18, 6};
  std::vector<int> end3(end_arr3, end_arr3 + 6);
  w = rejs(4, start3, end3);
  assert(w == 3);
  w = rejs(24, start3, end3);
  assert(w == 1);
  w = rejs(25, start3, end3);
  assert(w == 0);

  int start_arr4[] = {1, 1, 1, 1, 1, 7, 7, 7, 7, 15, 36, 7, 7, 7, 7, 7, 7};
  std::vector<int> start4(start_arr4, start_arr4 + 17);
  int end_arr4[] = {5, 4, 8, 6, 7, 12, 12, 12, 14, 35, 40, 10, 10, 10, 10, 10, 10};
  std::vector<int> end4(end_arr4, end_arr4 + 17);
  w = rejs(3, start4, end4);
  assert(w == 10);
  w = rejs(5, start4, end4);
  assert(w == 4);
  w = rejs(6, start4, end4);
  assert(w == 2);
  w = rejs(11, start4, end4);
  assert(w == 2);
  w = rejs(13, start4, end4);
  assert(w == 1);
  w = rejs(20, start4, end4);
  assert(w == 1);
  w = rejs(21, start4, end4);
  assert(w == 0);

  return 0;
}