#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define vertex int


typedef struct node *link;
struct node {
    vertex w;
    link next;
};

typedef struct graph *Graph;
struct graph {
    int V;
    int A;
    link *adj;
};


static link NEWnode(vertex w, link next) {
    link a = malloc(sizeof(struct node));
    a->w = w;
    a->next = next;
    return a;
}

Graph GRAPHinit(int V) {
    Graph G = malloc(sizeof(*G));
    G->V = V;
    G->A = 0;
    G->adj = malloc(V * sizeof(link));
    for (vertex v = 0; v < V; v++)
        G->adj[v] = NULL;
    return G;
}

void GRAPHinsertArc(Graph G, vertex v, vertex w) {
    for (link a = G->adj[v]; a != NULL; a = a->next)
        if (a->w == w) return; // ya existe
    G->adj[v] = NEWnode(w, G->adj[v]);
    G->A++;
}

void GRAPHshow(Graph G) {
    for (vertex v = 0; v < G->V; v++) {
        printf("%d: ", v);
        for (link a = G->adj[v]; a != NULL; a = a->next)
            printf("%d ", a->w);
        printf("\n");
    }
}


// 1. Verifica si un vértice está aislado
bool GRAPHisIsolated(Graph G, vertex v) {
    return G->adj[v] == NULL;
}

// 2. Grado de salida
int GRAPHoutdeg(Graph G, vertex v) {
    int count = 0;
    for (link a = G->adj[v]; a != NULL; a = a->next)
        count++;
    return count;
}

// 2. Grado de entrada
int GRAPHindeg(Graph G, vertex v) {
    int count = 0;
    for (vertex i = 0; i < G->V; i++)
        for (link a = G->adj[i]; a != NULL; a = a->next)
            if (a->w == v) count++;
    return count;
}

// 3. Verifica si dos vértices son adyacentes
bool GRAPHadjacent(Graph G, vertex v, vertex w) {
    for (link a = G->adj[v]; a != NULL; a = a->next)
        if (a->w == w) return true;
    return false;
}

// 5. Destruye el grafo y libera memoria
void GRAPHdestroy(Graph G) {
    for (vertex v = 0; v < G->V; v++) {
        link a = G->adj[v];
        while (a != NULL) {
            link temp = a;
            a = a->next;
            free(temp);
        }
    }
    free(G->adj);
    free(G);
}

// 6. Elimina un arco v-w
void GRAPHremoveArc(Graph G, vertex v, vertex w) {
    link *a = &G->adj[v];
    while (*a != NULL) {
        if ((*a)->w == w) {
            link temp = *a;
            *a = (*a)->next;
            free(temp);
            G->A--;
            return;
        }
        a = &(*a)->next;
    }
}

// 7. Verifica si el grafo es no dirigido
bool GRAPHundir(Graph G) {
    for (vertex v = 0; v < G->V; v++) {
        for (link a = G->adj[v]; a != NULL; a = a->next) {
            bool found = false;
            for (link b = G->adj[a->w]; b != NULL; b = b->next)
                if (b->w == v) { found = true; break; }
            if (!found) return false;
        }
    }
    return true;
}

// 8. Inserta una arista en grafo no dirigido
void UGRAPHinsertEdge(Graph G, vertex v, vertex w) {
    GRAPHinsertArc(G, v, w);
    GRAPHinsertArc(G, w, v);
}

// 9. Elimina una arista en grafo no dirigido
void UGRAPHremoveEdge(Graph G, vertex v, vertex w) {
    GRAPHremoveArc(G, v, w);
    GRAPHremoveArc(G, w, v);
}

// 10. Devuelve el grado máximo del grafo
int UGRAPHdegrees(Graph G) {
    int max = 0;
    for (vertex v = 0; v < G->V; v++) {
        int deg = GRAPHoutdeg(G, v);
        if (deg > max) max = deg;
    }
    return max;
}


int main() {
    Graph G = GRAPHinit(6);

    printf("Insertando arcos...\n");
    GRAPHinsertArc(G, 0, 1);
    GRAPHinsertArc(G, 0, 5);
    GRAPHinsertArc(G, 1, 0);
    GRAPHinsertArc(G, 1, 5);
    GRAPHinsertArc(G, 2, 4);
    GRAPHinsertArc(G, 3, 1);
    GRAPHinsertArc(G, 5, 3);

    printf("\nLista de adyacencia del grafo:\n");
    GRAPHshow(G);

    printf("\nGrado de salida de 1: %d\n", GRAPHoutdeg(G, 1));
    printf("Grado de entrada de 5: %d\n", GRAPHindeg(G, 5));
    printf("¿0 y 5 son adyacentes? %s\n", GRAPHadjacent(G, 0, 5) ? "Sí" : "No");
    printf("¿El vértice 4 está aislado? %s\n", GRAPHisIsolated(G, 4) ? "Sí" : "No");

    printf("\n¿El grafo es no dirigido? %s\n", GRAPHundir(G) ? "Sí" : "No");

    printf("\nEliminando arco 0->1...\n");
    GRAPHremoveArc(G, 0, 1);
    GRAPHshow(G);

    printf("\nInsertando arista no dirigida (2-3)...\n");
    UGRAPHinsertEdge(G, 2, 3);
    GRAPHshow(G);

    printf("\nEliminando arista (2-3)...\n");
    UGRAPHremoveEdge(G, 2, 3);
    GRAPHshow(G);

    printf("\nGrado máximo del grafo: %d\n", UGRAPHdegrees(G));

    GRAPHdestroy(G);
    printf("\nMemoria liberada correctamente.\n");

    return 0;
}
