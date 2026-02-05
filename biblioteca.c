#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct nodo {
    char *titolo;
    char *autore;
    int anno;
    struct nodo *next;
};


int lenght(struct nodo *v){
    int l = 0;

    for(; v != NULL; v = v->next){
        l++;
    }

    return l;
}


void inserisci_testa(struct nodo **s, char *titolo, char *autore, int anno){
    struct nodo *primo = (struct nodo*)malloc(sizeof(struct nodo));
    primo->titolo = (char*)malloc(strlen(titolo) + 1);
    strcpy(primo->titolo, titolo);
    primo->autore = (char*)malloc(strlen(autore) + 1);
    strcpy(primo->autore, autore);
    primo->anno = anno;
    primo->next = *s;
    *s = primo;
}

void print_list(struct nodo *s){
    struct nodo *current = s;
    while(current != NULL){
        printf("Titolo: %s, Autore: %s, Anno: %d", current->titolo, current->autore, current->anno);
        if(current->next != NULL){
            printf(" -> ");
        }
        current = current->next;
    }
    printf("\n");
}

void inserisci(struct nodo *s, struct nodo *t){
    if(t != NULL && s != NULL){
        t->next = s->next;
        s->next = t;
    }
}


void rimuovi(struct nodo **s, char* titolo){
    if(*s != NULL){
        struct nodo *q = *s;
        if(strcmp(q->titolo, titolo) == 0){
            *s = (*s)->next;
            free(s);
        } else {
            while(q->next != NULL){
                if(strcmp(q->next->titolo, titolo) == 0){
                    struct nodo *r = q->next;
                    q->next = q->next->next;
                    free(r);
                    return;
                } if (q->next != NULL){
                    q = q->next;
                }
            }
        }
    }
}

int main(){

    struct nodo *biblioteca = NULL;

    int n = 0;
    printf("Numero iniziale libri: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++){
        char titolo[50];
        printf("\nNome: ");
        scanf("%s", titolo);
        char autore[50];
        printf("Autore: ");
        scanf("%s", autore);
        int anno;
        printf("Anno: ");
        scanf("%d", &anno);
        inserisci_testa(&biblioteca, titolo, autore, anno);
    }

    print_list(biblioteca);


    int scelta;
    while(scelta != 3){
        printf("\nMENU");
        printf("\n[1]Inserisci libro");
        printf("\n[2]Rimuovi libro");
        printf("\n[3]Esci");
        scanf("%d", &scelta);

        switch(scelta){
            case 1: {
                char titolo[50];
                printf("\nTitolo: ");
                scanf("%s", titolo);
                char autore[50];
                printf("Autore: ");
                scanf("%s", autore);
                int anno;
                printf("Anno: ");
                scanf("%d", &anno);

                struct nodo *temp = (struct nodo*)malloc(sizeof(struct nodo));
                temp->titolo = strdup(titolo);
                temp->autore = strdup(autore);
                temp->anno = anno;

                temp->next = NULL;

                inserisci(biblioteca, temp);

                print_list(biblioteca);
                printf("Lunghezza lista: %d", lenght(biblioteca));
                break;
            }

            case 2: {
                char titolo[50];
                printf("Titolo da rimuovere: ");
                scanf("%s", titolo);

                rimuovi(&biblioteca, titolo);
                print_list(biblioteca);
                printf("Lunghezza lista: %d", lenght(biblioteca));
                break;
            }
            case 3: {
                exit(0);
            }
            default: {
                printf("valore non valido");

            }

        }
    }

    while(biblioteca != NULL){
        struct nodo *temp = biblioteca;
        biblioteca = biblioteca->next;
        free(temp->autore);
        free(temp->titolo);
        free(temp);
    }
}
