
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define vertex int


// ------------------ VARIABLES GLOBALES DFS ------------------

static int cnt;
static int pre[1000];
static int indent = 0;

// ------------------ ESTRUCTURAS ------------------



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

<<<<<<< HEAD
// ------------------ DFS CON RASTREO ------------------

void printIndent() {
    for (int i = 0; i < indent; i++)
        printf("  ");
}

static void dfsR(Graph G, vertex v) {
    pre[v] = cnt++;
    indent++;

    for (link a = G->adj[v]; a != NULL; a = a->next) {
        vertex w = a->w;

        printIndent();
        printf("%d-%d", v, w);

        if (pre[w] == -1) {
            printf(" dfsR(G,%d)\n", w);
            dfsR(G, w);
        } else {
            printf("\n");
        }
    }

    indent--;
    printIndent();
    printf("%d\n", v);
}

void GRAPHdfs(Graph G) {
    cnt = 0;
    indent = 0;

    for (vertex v = 0; v < G->V; v++)
        pre[v] = -1;

    for (vertex v = 0; v < G->V; v++) {
        if (pre[v] == -1) {
            printIndent();
            printf("%d dfsR(G,%d)\n", v, v);
            dfsR(G, v);
        }
    }
}


// ------------------ MAIN DE PRUEBA ------------------
=======
>>>>>>> 8832bf3c28456960bb6a8c17f64f8cfb65434dc5

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

    printf("\n--- RASTREO DFS ---\n");
    GRAPHdfs(G);

    GRAPHdestroy(G);
    printf("\nMemoria liberada correctamente.\n");


    return 0;
}
