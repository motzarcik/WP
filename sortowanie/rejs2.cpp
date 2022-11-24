#include <vector>
#include <deque>

// Tomek chciałby popłynąć z kolegami jachtem w rejs. Potrzebuje zebrać grupę kolegów, którzy chcą i 
// mogą z nim popłynąć. Od każdego ze swoich kolegów dowiedział się od kiedy do kiedy (włącznie)
// dysponuje wolnym czasem. Teraz zastanawia się, kiedy wyruszyć w rejs, tak żeby mógł on trwać jak 
// najdłużej. W trakcie rejsu załoga nie może się zmieniać.
// Napisz procedurę int rejs(int k, vector<int> start, vector<int> end), która mając daną liczbę k
// oraz informacje o dostępności kolegów Tomka, zwróci maksymalną długość rejsu. Jeżeli rejsu nie da
// się zorganizować, to poprawnym wynikiem jest 0.
//
// Na przykład: rejs(2, {12, 48, 28, 50, 0, 25}, {36, 100, 70, 80, 69, 30}) == 42.

// kolega i zaczyna być dostępny w czasie start[i], a jego ostatni dzień dostępności to end[i].
int rejs(int k, std::vector<int> start_arg, std::vector<int> end_arg) {
  int n = start_arg.size();
  // Pierwszy element pary to czas, a drugi to numer kolegi.
  std::vector<std::pair<int, int> > start;
  std::vector<std::pair<int, int> > end;
 
  for (int i = 0; i < n; i++) {
    start.push_back(std::make_pair(start_arg[i], i));
    end.push_back(std::make_pair(end_arg[i], i));
  }
  sort(start.begin(), start.end());
  sort(end.begin(), end.end());

  std::vector<bool> started_or_finished(n, false);
  int result = 0;
  int start_i = -1;
  int end_i = -1;
  int friends_started = 0;
  while (start_i < n) {
    if (friends_started < k) {
      start_i ++;
      if (!started_or_finished[start[start_i].second]) {
        friends_started++;
      }
      started_or_finished[start[start_i].second] = true;
    } else {
      end_i ++;
      result = std::max(result, end[end_i].first - start[start_i].first + 1);
      if (started_or_finished[end[end_i].second]) {
        friends_started --;
      }
      started_or_finished[end[end_i].second] = true;
    }
  }

  return result;
}


int main()
{
  int start_arr[] = {12, 48, 28, 50, 0, 25};
  std::vector<int> start(start_arr, start_arr + 6);
  int end_arr[] = {36, 100, 70, 80, 69, 30};
  std::vector<int> end(end_arr, end_arr + 6);
  int w = rejs(2, start, end);

  return 0;
}