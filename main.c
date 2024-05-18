#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

//Albero per le auto
typedef struct nodo_auto{
    int autonomia_auto;
    int ric;
    struct nodo_auto* left;
    struct nodo_auto* right;
}Nodo_auto;
typedef Nodo_auto* Albero_auto;

Albero_auto Inserire_auto(Albero_auto nd_Auto, int valore){          //Inserisco un nodo nell'albero_auto
    if(nd_Auto == NULL){
        Albero_auto nuova_auto = (Albero_auto)malloc(sizeof(Nodo_auto));
        nuova_auto->autonomia_auto = valore;
        nuova_auto->ric = 1;
        nuova_auto->right = NULL;
        nuova_auto->left = NULL;
        return nuova_auto;
    }

    if(valore == nd_Auto->autonomia_auto){
        nd_Auto->ric++;
        return nd_Auto;
    }

    if(valore < nd_Auto->autonomia_auto){
        nd_Auto->left = Inserire_auto(nd_Auto->left, valore);
    }
    else{
        nd_Auto->right = Inserire_auto(nd_Auto->right, valore);
    }

    return nd_Auto;
}

Albero_auto Rimuovi_min_a(Albero_auto P, Albero_auto T){
    if(P == NULL || T == NULL)
        return NULL;
    if(T->left != NULL){
        return Rimuovi_min_a(T, T->left);
    }

    if(T == P->left)
        P->left = T->right;
    else
        P->right = T->right;

    return T;
}

Albero_auto Rimuovi_nodo_a(Albero_auto radice){
    Albero_auto n_radice = NULL;
    if(radice == NULL)
        return  NULL;

    if(radice->ric>1){
        radice->ric--;
        printf("rottamata\n");
        return radice;
    }

    if(radice->right != NULL && radice->left != NULL){
        Albero_auto min = NULL;
        min = Rimuovi_min_a(radice, radice->right);
        printf("rottamata\n");
        radice->autonomia_auto = min->autonomia_auto;
        free(min);
        return radice;
    }
    if(radice->left == NULL)
        n_radice = radice->right;
    else
        n_radice = radice->left;

    printf("rottamata\n");
    free(radice);

    return n_radice;
}

// Rimuove un nodo con un determinato valore dall'albero
Albero_auto Rimuovi_auto(Albero_auto radice, int a_auto) {
    if(radice == NULL) {
        printf("non rottamata\n");
        return NULL;
    }

    if(radice->autonomia_auto > a_auto)
        radice->left = Rimuovi_auto(radice->left, a_auto);
    else if(radice->autonomia_auto < a_auto)
        radice->right = Rimuovi_auto(radice->right, a_auto);
    else
        radice = Rimuovi_nodo_a(radice);

    return radice;
}

int Auto_maggiore(Albero_auto radice){
    if(radice == NULL)
        return -1;
    if(radice->right == NULL)
        return radice->autonomia_auto;
    return Auto_maggiore(radice->right);
}

void Distruggi_tutte_Auto(Albero_auto nd_Auto){
    if(nd_Auto == NULL){
        return;
    }
    Distruggi_tutte_Auto(nd_Auto->left);

    Distruggi_tutte_Auto((nd_Auto->right));

    free(nd_Auto);
}

void stampa_auto_in_stazione(Albero_auto radice){
    if(radice == NULL){
        return;
    }
    stampa_auto_in_stazione(radice->left);
    printf("%d(%d) ", radice->autonomia_auto, radice->ric);
    stampa_auto_in_stazione(radice->right);
}

//  /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   //

//Lista per le stazioni
typedef struct nodo_lista{
    int km_s;
    int max;
    struct nodo_lista* prev;
    struct nodo_lista* next;
}NodoLis;
typedef NodoLis* NodoL;

NodoL aggiungi_NodoL(int km, int max, NodoL pr, NodoL nx){
    NodoL new = (NodoL)malloc(sizeof(NodoLis)), temp = NULL;
    new->km_s = km;
    new->max = max;
    if(pr != NULL){         //Siamo nel caso right          nx = NULL       [p] -> [*]      [p] -> [f] -> [*]
        temp = pr->next;
        pr->next = new;
        new->prev = pr;
        new->next = temp;
        if(temp != NULL)
            temp->prev = new;
    }
    else if(nx != NULL){         //Siamo nel caso left          pr = NULL       [*] -> [p]      [*] -> [f] -> [p]
        temp = nx->prev;
        nx->prev = new;
        new->next = nx;
        new->prev = temp;
        if(temp != NULL)
            temp->next = new;
    }
    else{
        new->prev = NULL;
        new->next = NULL;
    }

    return new;
}

void rimuovi_NodoL(NodoL n_rm){
    if (n_rm == NULL)
        return;

    NodoL nodo_prev = n_rm->prev;
    NodoL nodo_next = n_rm->next;

    if (nodo_prev != NULL)
        nodo_prev->next = nodo_next;

    if (nodo_next != NULL)
        nodo_next->prev = nodo_prev;

    free(n_rm);
}

void rimuovi_Lista(NodoL testa) {
    while (testa != NULL) {
        NodoL nodo_corrente = NULL;
        nodo_corrente = testa;
        testa = testa->next;
        free(nodo_corrente);
    }
}

void Stampa_lista_stazioni(NodoL testa){
    if(testa == NULL){
        return;
    }
    NodoL nodocur = NULL;
    nodocur = testa;
    while(nodocur != NULL){
        printf("%d(%d)->", nodocur->km_s, nodocur->km_s+nodocur->max);
        nodocur = nodocur->next;
    }
    printf("\n");
    return;
}


//  /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   //

//Albero per stazioni
typedef struct nodo{
    int km_stazione;
    int max_auto;           //posso lasciarlo solo sulla lista
    struct nodo* left;
    struct nodo* right;
    Albero_auto Auto_in_stazione;
    NodoL ptr_to_lista;
}Nodo;
typedef Nodo* Albero_stazioni;

typedef enum{
    Right,      //Right = Padre < Figlio        [p]->[f]
    Left,       //Left = Padre > Figlio         [f]->[p]
    Nul
}dir;

//Inserisci un nodo nell'albero
Albero_stazioni Inserisci_stazione(Albero_stazioni nd_stazione, int km, int max, Albero_auto automobili, Albero_stazioni p, dir d){
    if(nd_stazione == NULL){
        Albero_stazioni nuova_staz = (Albero_stazioni)malloc(sizeof(Nodo));
        nuova_staz->km_stazione = km;
        nuova_staz->max_auto = max;
        nuova_staz->Auto_in_stazione = automobili;
        nuova_staz->left = NULL;
        nuova_staz->right = NULL;
        if(d == Nul) nuova_staz->ptr_to_lista = aggiungi_NodoL(km, max, NULL, NULL);
        else if(d == Right) nuova_staz->ptr_to_lista = aggiungi_NodoL(km, max, p->ptr_to_lista, NULL);
        else if(d == Left)  nuova_staz->ptr_to_lista = aggiungi_NodoL(km, max, NULL, p->ptr_to_lista);
        return nuova_staz;
    }
    if(km < nd_stazione->km_stazione){
        nd_stazione->left = Inserisci_stazione(nd_stazione->left, km, max, automobili, nd_stazione, Left);
    }
    else{
        nd_stazione->right = Inserisci_stazione(nd_stazione->right, km, max, automobili, nd_stazione, Right);
    }
    return nd_stazione;
}

//Cerca un nodo nell'albero
Albero_stazioni Cerca_stazione(Albero_stazioni nd_stazione, int km){
    if(nd_stazione == NULL){
        //printf("Elemento non trovato");
        return NULL;
    }

    if(nd_stazione->km_stazione == km){
        //printf("Elemento trovato");
        return nd_stazione;
    }

    if(km < nd_stazione->km_stazione){
        return Cerca_stazione(nd_stazione->left, km);
    }
    else{
        return Cerca_stazione(nd_stazione->right, km);
    }

}

Albero_stazioni Trova_min_nel_sottoalbero_destro(Albero_stazioni P, Albero_stazioni T){
    if(T->left != NULL){
        return Trova_min_nel_sottoalbero_destro(T, T->left);
    }
    if(T == P->left)
        P->left = T->right;
    else
        P->right = T->right;

    return T;
}

Albero_stazioni Rimuovi_nodo(Albero_stazioni radice){
    if(radice == NULL)
        return  NULL;

    if(radice->right != NULL && radice->left != NULL){
        Albero_stazioni min = NULL;
        min = Trova_min_nel_sottoalbero_destro(radice, radice->right);
        printf("demolita\n");
        radice->km_stazione = min->km_stazione;
        radice->max_auto = min->max_auto;
        rimuovi_NodoL(radice->ptr_to_lista);
        radice->ptr_to_lista = min->ptr_to_lista;
        Distruggi_tutte_Auto(radice->Auto_in_stazione);
        radice->Auto_in_stazione = min->Auto_in_stazione;
        free(min);
        return radice;
    }

    Albero_stazioni n_radice = NULL;
    if(radice->left == NULL)
        n_radice = radice->right;
    else
        n_radice = radice->left;

    rimuovi_NodoL(radice->ptr_to_lista);
    Distruggi_tutte_Auto(radice->Auto_in_stazione);
    printf("demolita\n");
    free(radice);

    return n_radice;
}

// Rimuove un nodo con un determinato valore dall'albero
Albero_stazioni Cerca_staz_da_rim(Albero_stazioni radice, int km) {
    if(radice == NULL) {
        printf("non demolita\n");
        return NULL;
    }

    if(radice->km_stazione > km)
        radice->left = Cerca_staz_da_rim(radice->left, km);
    else if(radice->km_stazione < km)
        radice->right = Cerca_staz_da_rim(radice->right, km);
    else
        radice = Rimuovi_nodo(radice);

    return radice;
}

Albero_stazioni staz_min(Albero_stazioni radice){
    if(radice == NULL) return NULL;
    if(radice->left == NULL)
        return radice;
    return staz_min(radice->left);
}

//Dealloca l'intera autostrada se viene passata la radice
void Dealloca_Autostrada(Albero_stazioni radice){
    if(radice == NULL)
        return;

    Distruggi_tutte_Auto(radice->Auto_in_stazione);
    Dealloca_Autostrada(radice->left);
    Dealloca_Autostrada(radice->right);

    free(radice);
}

void inorder(Albero_stazioni nd_stazione){
    if(nd_stazione == NULL){
        return;
    }
    inorder(nd_stazione->left);
    printf("\nStazione: %d\nMax: %d\n", nd_stazione->km_stazione,nd_stazione->max_auto);
    //stampa_auto_in_stazione(nd_stazione->Auto_in_stazione);
    inorder(nd_stazione->right);
}

//  /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   //

//Definizione Lista
typedef struct nod{
    int stazione;
    struct nod *next;
} LNodo;
typedef LNodo *Lista;

//Aggiungere in testa
Lista Inserisci_in_testa(Lista Testa, int elem){
    if(Testa == NULL)
        return NULL;
    Lista N_testa = (Lista)malloc(sizeof(LNodo));
    N_testa->stazione = elem;
    N_testa->next = Testa;
    return N_testa;
};

//Liberare la lista
void rimuoviLista(Lista testa) {
    while (testa != NULL) {
        Lista nodo_corrente = NULL;
        nodo_corrente = testa;
        testa = testa->next;
        free(nodo_corrente);
    }
}

//Stampa percorso
void stampa_path(Lista Testa){
    if(Testa == NULL)
        return;
    printf("%d",Testa->stazione);
    Testa = Testa->next;
    while(Testa != NULL){
        printf(" %d",Testa->stazione);
        Testa = Testa->next;
    }
    printf("\n");
    return;
}

//  /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   /   //

//Definizione della struttura R_List
typedef struct nd{
    int km;
    int mv;
    int id;
    struct nd *next;
    struct nd *prev;
    struct nd *right;
    struct nd *pright;
} Nd;
typedef Nd *R_List;

//Aggiungere nodo
R_List add_Nodo(int km, int mv, int n, R_List n_prev, bool right){
    R_List N_Nodo = (R_List)malloc(sizeof(Nd));
    N_Nodo->km = km;
    N_Nodo->mv = mv;
    N_Nodo->id = n;
    N_Nodo->next = NULL;
    N_Nodo->prev = n_prev;
    N_Nodo->right = NULL;
    N_Nodo->pright = NULL;

    if(n_prev != NULL) {
        if (!right)
            n_prev->next = N_Nodo;
        else
            n_prev->right = N_Nodo;
    }

    return N_Nodo;
}

//Aggiungi nodo con pvright
R_List add_Nodo_pr(int km, int mv, int n, R_List n_prev, R_List n_pright, bool right){
    R_List N_Nodo = (R_List)malloc(sizeof(Nd));
    N_Nodo->km = km;
    N_Nodo->mv = mv;
    N_Nodo->id = n;
    N_Nodo->next = NULL;
    N_Nodo->prev = n_prev;
    N_Nodo->right = NULL;
    N_Nodo->pright = NULL;

    if(n_prev != NULL) {
        if (!right) {
            n_prev->next = N_Nodo;
            N_Nodo->pright = n_pright;
        }
        else {
            n_prev->right = N_Nodo;
            n_prev->pright = n_pright;
        }
    }

    return N_Nodo;
}

//Creazione della struttura R_List a<b
R_List Crea_RList(R_List testa, NodoL nodo_inserire, int controllore, int fine){
    if(testa == NULL){
        return NULL;
    }
    R_List prev = testa, temp = NULL, Max_s = NULL;
    int id = 1, Max_mv = 0;
    do{
        //printf("%d\n", nodo_inserire->km_s);
        //printf("%d <= %d %s\n", nodo_inserire->km_s, controllore, nodo_inserire->km_s <= controllore ? "yes" : "no" );
        if(nodo_inserire->km_s == fine){
            //printf("Stazione Finale\n");
            if(nodo_inserire->km_s <= controllore) {
                //printf("Aggiungo il nodo finale in next\n");
                temp = add_Nodo(nodo_inserire->km_s, nodo_inserire->km_s+nodo_inserire->max, id, prev, false);
                //printf("\n%d\n", temp->km);
                return temp;
            }
            else if (nodo_inserire->km_s <= Max_mv){
                //printf("Aggiungo il nodo finale in right\n");
                id++;
                temp = add_Nodo(nodo_inserire->km_s, nodo_inserire->km_s+nodo_inserire->max, id, Max_s, true);
                return temp;
            }
            else{
                printf("nessun percorso\n");
                return NULL;
            }

        }//    Gestire stazione finale
        else if(nodo_inserire->km_s <= controllore){    // S1 - S2     Si può ottimizzare l'uguale
            //printf("Aggiungendo %d: Il nodo %d ha come next %d\t\tcontrollore: %d \n",nodo_inserire->km_s, prev->km, nodo_inserire->km_s, controllore);
            temp = add_Nodo(nodo_inserire->km_s, nodo_inserire->km_s+nodo_inserire->max, id, prev, false);
            if(nodo_inserire->km_s+nodo_inserire->max >= Max_mv) {
                Max_mv = nodo_inserire->km_s+nodo_inserire->max;
                Max_s = temp;
            }
            nodo_inserire = nodo_inserire->next;
            prev = temp;
        }
        else if (nodo_inserire->km_s <= Max_mv){        // S1 |_ S2
            //printf("Aggiungendo %d: Il nodo %d ha come right %d\t\tcontrollore: %d\n",nodo_inserire->km_s, Max_s->km, nodo_inserire->km_s, controllore);
            id++;
            temp = add_Nodo(nodo_inserire->km_s, nodo_inserire->km_s+nodo_inserire->max, id, Max_s, true);
            nodo_inserire = nodo_inserire->next;
            prev = Max_s;
            //printf("%d\n", controllore);
            controllore = Max_s->mv;
            //printf("%d\n", controllore);
            Max_mv = temp->mv;
            Max_s = temp;
            prev = temp;
        }

        else {
            printf("nessun percorso\n");
            return NULL;
        }
    }while(nodo_inserire->km_s <= fine);

    return NULL;
}

//Creazione della struttura R_List a>b
R_List Crea_RList_reverse(R_List testa, NodoL nodo_inserire, int controllore, int fine){
    if(testa == NULL){
        return NULL;
    }
    R_List prev = testa, temp = NULL, Min_s = NULL, p_right = testa;
    int id = 1, Min_mv = 2147483647;
    do{
        //printf("%d\n", nodo_inserire->km_s);
        //printf("%d <= %d %s\n", nodo_inserire->km_s, controllore, nodo_inserire->km_s <= controllore ? "yes" : "no" );
        if(nodo_inserire->km_s == fine){
            //printf("Stazione Finale\n");
            if(nodo_inserire->km_s >= controllore) {
                //printf("Aggiungo il nodo finale in next\n");
                temp = add_Nodo_pr(nodo_inserire->km_s, nodo_inserire->km_s-nodo_inserire->max, id, prev, p_right, false);
                //printf("\n%d\n", temp->km);
                return temp;
            }
            else if (nodo_inserire->km_s >= Min_mv){
                //printf("Aggiungo il nodo finale in right\n");
                id++;
                temp = add_Nodo_pr(nodo_inserire->km_s, nodo_inserire->km_s-nodo_inserire->max, id, Min_s, p_right, true);
                temp->pright = temp->prev;
                return temp;
            }
            else{
                printf("nessun percorso\n");
                return NULL;
            }

        }//    Gestire stazione finale
        else if(nodo_inserire->km_s >= controllore){    // S1 - S2     Si può ottimizzare l'uguale
            //printf("Aggiungendo %d: Il nodo %d ha come next %d\t\tcontrollore: %d \n",nodo_inserire->km_s, prev->km, nodo_inserire->km_s, controllore);
            temp = add_Nodo(nodo_inserire->km_s, nodo_inserire->km_s-nodo_inserire->max, id, prev, false);
            if(nodo_inserire->km_s-nodo_inserire->max <= Min_mv) {
                Min_mv = nodo_inserire->km_s-nodo_inserire->max;
                Min_s = temp;
            }
            nodo_inserire = nodo_inserire->prev;
            prev = temp;
        }
        else if (nodo_inserire->km_s >= Min_mv){        // S1 |_ S2
            //printf("Aggiungendo %d: Il nodo %d ha come right %d\t\tcontrollore: %d\n",nodo_inserire->km_s, Max_s->km, nodo_inserire->km_s, controllore);
            id++;
            temp = add_Nodo_pr(nodo_inserire->km_s, nodo_inserire->km_s-nodo_inserire->max, id, Min_s, p_right,true);
            nodo_inserire = nodo_inserire->prev;
            p_right = Min_s;
            prev = Min_s;
            //printf("%d\n", controllore);
            controllore = Min_s->mv;
            //printf("%d\n", controllore);
            Min_mv = temp->mv;
            Min_s = temp;
            prev = temp;
        }

        else {
            printf("nessun percorso\n");
            return NULL;
        }
    }while(nodo_inserire->km_s >= fine);

    return NULL;
}

//Cercare miglior percorso a<b
Lista Percorso(R_List Coda, int inizio){                //a<b
    if(Coda == NULL){
        return NULL;
    }
    R_List staz_a = Coda->prev;
    int staz_min = 2147483647, staz_min_id = 0;
    int fine = Coda->km, fine_id = Coda->id;

    Lista testa = (Lista)malloc(sizeof(LNodo));
    testa->stazione = Coda->km;                         //Coda della lista
    testa->next = NULL;

    while(staz_a != NULL){
        if(staz_a->km != inizio){
            if(fine_id-1 <= staz_a->id){
                if(staz_a->mv>=fine && staz_a->km<=staz_min){
                    staz_min = staz_a->km;
                    staz_min_id = staz_a->id;
                }
                staz_a = staz_a->prev;
            }
            else{
                testa = Inserisci_in_testa(testa, staz_min);
                //printf("Aggiunta alla lista la stazione %d\n",staz_min);
                fine = staz_min;
                fine_id = staz_min_id;
                staz_min = 2147483647;
            }
            //printf("%d != Null\n",staz_a->km);
        }
        else{
            testa = Inserisci_in_testa(testa, staz_min);
            //printf("Aggiunta alla lista la stazione %d\n",staz_min);
            testa = Inserisci_in_testa(testa, staz_a->km);
            return testa;
        }
    }
    return testa;
}

//Cerca miglior percorso a>b
Lista Percorso_r(R_List Coda, int inizio){
    int fine = 0, min_s = 0;
    R_List nodo_cur = NULL, s_right_near = NULL;
    if(Coda == NULL){
        return NULL;
    }
    Lista testa = (Lista)malloc(sizeof(LNodo));
    s_right_near = Coda->pright;
    fine = Coda->km;
    min_s = s_right_near->km;
    testa->stazione = Coda->km;
    testa->next = NULL;

    while(s_right_near->km != inizio){
        if(s_right_near->next == NULL){
            testa = Inserisci_in_testa(testa, s_right_near->km);
            fine = s_right_near->km;
            s_right_near = s_right_near->pright;
        }
        else{
            min_s = s_right_near->km;
            nodo_cur = s_right_near->next;
            while(nodo_cur != NULL){
                if(nodo_cur->km < min_s && nodo_cur->mv <= fine){
                    min_s = nodo_cur->km;
                }
                nodo_cur = nodo_cur->next;
            }
            testa = Inserisci_in_testa(testa, min_s);
            fine = min_s;
            s_right_near = s_right_near->pright;
        }
    }
    testa = Inserisci_in_testa(testa, inizio);
    return testa;
}

//Stampa la struttura R_List        a<b
void stampa_la_struttura(R_List Testa){
    if(Testa == NULL)
        return;
    if(Testa->right != NULL){
        printf("%d(%d)(%d)|__",Testa->km, Testa->mv, Testa->id);
        return stampa_la_struttura(Testa->right);
    }
    else if(Testa != NULL){
        printf("%d(%d)(%d)->", Testa->km, Testa->mv, Testa->id);
        return stampa_la_struttura(Testa->next);
    } else return;
}

//Dealloco la RLista
void Distruggi_RLista(R_List Testa){
    if(Testa->next == NULL && Testa->right == NULL){
        free (Testa);
        return;
    }
    if(Testa->right != NULL && Testa->next != NULL) {
        R_List N_right = Testa->right, N_next = Testa->next;
        free(Testa);
        Distruggi_RLista(N_next);
        Distruggi_RLista(N_right);
        return;
    }
    if(Testa->right != NULL){
        R_List N_right = Testa->right;
        free(Testa);
        return Distruggi_RLista(N_right);
    }
    if(Testa->next != NULL){
        R_List N_next = Testa->next;
        free(Testa);
        return Distruggi_RLista(N_next);
    }
    return;
}


//Stampa la struttura R_List        a>b
void stampa_la_struttura_reverse(R_List Testa){
    if(Testa == NULL)
        return;
    if(Testa->pright != NULL){
        printf("%d(%d)(%d)(%d)|__",Testa->km, Testa->mv, Testa->id, Testa->pright->km);
        return stampa_la_struttura_reverse(Testa->right);
    }
    else if(Testa != NULL){
        printf("%d(%d)(%d)->", Testa->km, Testa->mv, Testa->id);
        return stampa_la_struttura_reverse(Testa->next);
    } else return;
}



int main()
{
    char input[20] = "                   ";
    int km = 0, n_auto = 0, temp = 0, max_auto = 0, a = 0, b = 0;
    Albero_stazioni radice_stazioni = NULL;
    Albero_stazioni tv = NULL;                     //temporary variable
    Albero_auto radice_auto = NULL;
    R_List Testa = NULL, Coda = NULL;
    Lista path = NULL;

    //Inizio lettura input
    if (scanf("%s", input)!= 0){
        do {
            if (strncmp(input, "aggiungi-stazione", 17) == 0) {        //Gestisco aggiungi-stazione
                if(!scanf("%d", &km))return 0;
                if (Cerca_stazione(radice_stazioni, km) != NULL) {
                    if(!scanf("%d", &n_auto)) return 0;
                    for (int i = 0; i < n_auto; i++) {
                        if(!scanf("%d", &temp)) return 0;
                    }
                    printf("non aggiunta\n");
                } else {
                    if(!scanf("%d", &n_auto)) return 0;
                    max_auto = 0;
                    radice_auto = NULL;
                    for (int i = 0; i < n_auto; i++) {
                        if(!scanf("%d", &temp)) return 0;
                        if (temp > max_auto)
                            max_auto = temp;
                        radice_auto = Inserire_auto(radice_auto, temp);
                        temp = 0;
                    }
                    radice_stazioni = Inserisci_stazione(radice_stazioni, km, max_auto, radice_auto,
                                                         radice_stazioni, Nul);
                    printf("aggiunta\n");
                }
                continue;
            }

            if (strncmp(input, "demolisci-stazione", 18) == 0) {
                if(!scanf("%d", &km)) return 0;
                radice_stazioni = Cerca_staz_da_rim(radice_stazioni, km);
                continue;
            }

            if (strncmp(input, "aggiungi-auto",13) == 0) {
                if(!scanf("%d", &km)) return 0;
                if(!scanf("%d", &temp)) return 0;
                tv = Cerca_stazione(radice_stazioni, km);
                if (tv == NULL)
                    printf("non aggiunta\n");
                else {
                    tv->Auto_in_stazione = Inserire_auto(tv->Auto_in_stazione, temp);
                    if (tv->max_auto < temp) {
                        tv->max_auto = temp;
                        tv->ptr_to_lista->max = temp;
                    }
                    printf("aggiunta\n");
                }
                continue;
            }

            if (strncmp(input, "rottama-auto", 12) == 0) {
                if(!scanf("%d", &km)) return  0;
                if(!scanf("%d", &temp)) return 0;
                tv = Cerca_stazione(radice_stazioni, km);
                if (tv == NULL)
                    printf("non rottamata\n");
                else {
                    tv->Auto_in_stazione = Rimuovi_auto(tv->Auto_in_stazione, temp);
                    if (tv->max_auto == temp) {
                        tv->max_auto = Auto_maggiore(tv->Auto_in_stazione);
                        tv->ptr_to_lista->max = tv->max_auto;
                    }
                }
                continue;
            }

            if (strncmp(input, "pianifica-percorso", 18) == 0) {
                if(!scanf("%d", &a)) return 0;
                if(!scanf("%d", &b)) return 0;
                tv = Cerca_stazione(radice_stazioni, a);
                Testa = NULL;
                Coda = NULL;
                if (a < b) {
                    Testa = add_Nodo(tv->ptr_to_lista->km_s, tv->ptr_to_lista->km_s + tv->ptr_to_lista->max, 1,
                                     NULL, false);
                    Coda = Crea_RList(Testa, tv->ptr_to_lista->next, Testa->mv, b);
                    if (Coda != NULL) {
                        path = Percorso(Coda, a);
                        stampa_path(path);
                        rimuoviLista(path);
                    }
                    Distruggi_RLista(Testa);
                } else {
                    Testa = add_Nodo(tv->ptr_to_lista->km_s, tv->ptr_to_lista->km_s - tv->ptr_to_lista->max, 1,
                                     NULL, false);
                    Coda = Crea_RList_reverse(Testa, tv->ptr_to_lista->prev, Testa->mv, b);
                    if (Coda != NULL) {
                        path = Percorso_r(Coda, a);
                        stampa_path(path);
                        rimuoviLista(path);
                    }
                    Distruggi_RLista(Testa);
                }
                continue;
            }

        } while (scanf("%s", input) != EOF);
    }

    tv = staz_min(radice_stazioni);
    rimuovi_Lista(tv->ptr_to_lista);
    Dealloca_Autostrada(radice_stazioni);

    return 0;
}
