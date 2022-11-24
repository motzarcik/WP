#include <stdio.h>
#include <stdlib.h>

#include "kolejka.h"

#define INIT_SIZE 4

elem make_elem(int val1, int val2) {
  elem e;
  e.val1 = val1;
  e.val2 = val2;
  return e;
}

queue make_queue() {
  queue q;
  q.start = 0;
  q.cnt = 0;
  q.data_size = INIT_SIZE;
  q.data = (elem*) malloc(INIT_SIZE * sizeof(elem));
  if (q.data == NULL) {
    printf("Blad alokacji pamieci.\n");
    exit(0);
  }
  
  return q;
}

void delete_queue(queue q) {
  free(q.data);
}

int size(queue q) {
  return q.cnt;
}

void reallocate(queue* q) {
  elem* new_data = (elem*) malloc(2 * q->data_size * sizeof(elem));
  if (new_data == NULL) {
    printf("Blad alokacji pamieci.\n");
    exit(0);
  }
  
  for (int i = 0; i < q->data_size; i++) {
    new_data[i] = q->data[(q->start + i) % q->data_size];
  }
  free(q->data);
  
  q->start = 0;
  q->data = new_data;
  q->data_size = 2 * q->data_size;
}

void push_back(queue* q, elem e) {
  if (q->cnt == q->data_size) {
    reallocate(q);
  } 
  
  q->data[(q->start + q->cnt) % q->data_size] = e;
  q->cnt++;
}

void push_front(queue* q, elem e) {
  if (q->cnt == q->data_size) {
    reallocate(q);
  } 
  
  q->start = (q->start + q->data_size - 1) % q->data_size;
  q->data[q->start] = e;
  q->cnt++;
}

elem front(queue q) {
  if (q.cnt == 0) {
    printf("Empty queue.\n");
    exit(0);
  }
  
  return q.data[q.start];
}

elem back(queue q) {
  if (q.cnt == 0) {
    printf("Pusta kolejka.\n");
    exit(0);
  }
  
  return q.data[(q.start + q.cnt - 1) % q.data_size];
}
 
elem pop_front(queue* q) {
  if (q->cnt == 0) {
    printf("Pusta kolejka.\n");
    exit(0);
  }

  elem ret = q->data[q->start];
  q->cnt--;
  q->start = (q->start + 1) % q->data_size;
  return ret;
}

elem pop_back(queue* q) {
  if (q->cnt == 0) {
    printf("Empty queue.\n");
    exit(0);
  }

  elem ret = q->data[(q->start + q->cnt - 1) % q->data_size];
  q->cnt--;

  return ret;
}
