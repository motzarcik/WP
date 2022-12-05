#include "find_union.h"

find_union create_fu(int label) {
  find_union res = (find_union)malloc(sizeof(struct fu));
  res->label = label;
  res->up = NULL;
  res->rank = 0;
  res->size = 1;
  std::vector<find_union> empty_vec;
  res->elems = empty_vec;
  return res;
}

find_union go_up(find_union p) {
  if (p->up == NULL) return p;
  p->up = go_up(p->up);
  return p->up;
}

int find(find_union p) {
  return go_up(p)->label;
}

bool equivalent(find_union p, find_union q) {
  return go_up(p) == go_up(q);
}

void union_fu(find_union p, find_union q) {
  find_union rp = go_up(p);
  find_union rq = go_up(q);
  if (rp == rq) return;
  if (rp->rank > rq->rank) {
    rq->up = rp;
    rp->size += rq->size;
    rp->elems.push_back(rq);
  } else {
    rp->up = rq;
    rq->size += rp->size;
    rq->elems.push_back(rp);
    if (rq->rank == rp->rank) rq->rank++;
  }
}

int size (find_union p) {
  return go_up(p)->size;
}

void traverse(find_union p, std::vector<int> & res) {
  res.push_back(p->label);
  for (int i = 0; i < p->elems.size(); i++) {
    traverse(p->elems[i], res);
  }
}

std::vector<int> elements(find_union p) {
  std::vector<int> res;
  traverse(go_up(p), res);
  return res;
}