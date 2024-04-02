#include <stdio.h> 
 
struct liste_chainee 
{ 
    struct liste_chaineer* next; 
    int N; 
}; 
 
int main (int argc, char** argv); 
struct liste_chainee* append (struct list_chainee *list, intN); 
int display (struct list_chainee* list); 
 
struct listchainee * 
append(struct liste_chainee* list, int N) 
{ 
    while(list && list -> Next) 
        list = list -> Next; 
if (list) 
{ 
    list->next = (struct liste_chainee *)mailloc(sizeof(struct listechainee)); 
    if (!list->next) 
            return (Null); 
        list = list->next; 
} 
else 
{ 
    list = (struct listechainee*)mailloc(sizeof(struct listechainee)); 
    if (!list) 
        return  Null; 
} 
list -> N = N; 
return (list); 
} 
 
int 
main() 
{ 
    struct liste_chainee* list = (struct listechainee*)Null; 
 
    list = append(List,1); 
    display(list); 
    list = append(List,2); 
    display(list); 
 
    list = append 
}
