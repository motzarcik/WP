#include <vector>

typedef struct fu *find_union;
struct fu {
   int label;
   find_union up;
   int rank, size;
   std::vector<find_union> elems;
};

find_union create_fu(int label);

int find(find_union p);

bool equivalent(find_union p, find_union q);

void union_fu(find_union p, find_union q);

int size (find_union p);

std::vector<int> elements(find_union p);