#include <stdbool.h>

struct element {
    int value;
    struct element *pointer;
};




struct element * createlist(int val);


bool listisempty(struct element *list);


int lenlist(struct element *list);


void printlist (struct element *list);


void debuglist(struct element *list);


struct element * indexlist(struct element *list, int idx);


void prependlist(struct element *list, int val);


void appendlist(struct element *list, int val);


void deletefirst(struct element *list);


void deletelast(struct element *list);


void addelement(struct element *list, int idx, int val);


void removeelement(struct element *list, int idx);
