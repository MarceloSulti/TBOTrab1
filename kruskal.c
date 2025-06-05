#include "kruskal.h"
#include <stdio.h>  // For fprintf (error messages)
#include <stdlib.h> // For malloc, free

/* --- Internal DSU structure and low-level operations (static) --- */

// This structure holds the core DSU data arrays (parent, rank)
// and the mapping from Ponto* to integer indices.
typedef struct DSU_Internal {
    int *parent;                // parent[i] is the parent of element i
    int *rank;                  // rank[i] is the rank of the tree rooted at i (used for union by rank)
    int num_elementos;          // Number of elements (vertices) managed by DSU
    Ponto **mapeamento_pontos;  // Array to map Ponto* to an index (0 to num_elementos-1)
                                // This array stores copies of Ponto* from the input, does not own them.
} DSU_Internal;

// Static helper function to get the integer index associated with a Ponto*.
// Returns -1 if Ponto* is not found in the mapping.
static int _dsu_internal_obter_indice_ponto(DSU_Internal *dsu, Ponto *p) {
    if (!dsu || !p) return -1;
    for (int i = 0; i < dsu->num_elementos; ++i) {
        if (dsu->mapeamento_pontos[i] == p) { // Pointer comparison
            return i;
        }
    }
    return -1; // Ponto not found
}

// Static helper: Find operation (finds representative of set containing element i).
// Implements Find WITHOUT path compression.
// Returns representative's index, or -1 on error (e.g., invalid index).
static int _dsu_internal_encontrar_representante(DSU_Internal *dsu, int i) {
    if (!dsu || i < 0 || i >= dsu->num_elementos) return -1;
    
    int current = i;
    while (dsu->parent[current] != current) {
        current = dsu->parent[current]; // Move up to the parent
    }
    return current; // 'current' is now the root (representative)
}

// Static helper: Union operation (unites sets containing elements i and j).
// Implements Union by Rank.
// Returns 1 if union happened (i and j were in different sets).
// Returns 0 if i and j were already in the same set or if an error occurred finding roots.
static int _dsu_internal_unir_conjuntos(DSU_Internal *dsu, int i, int j) {
    if (!dsu || i < 0 || i >= dsu->num_elementos || j < 0 || j >= dsu->num_elementos) return 0;

    int raiz_i = _dsu_internal_encontrar_representante(dsu, i);
    int raiz_j = _dsu_internal_encontrar_representante(dsu, j);

    if (raiz_i == -1 || raiz_j == -1) return 0; // Error finding roots

    if (raiz_i == raiz_j) {
        return 0; // Already in the same set
    }

    // Union by rank: Attach smaller rank tree under root of higher rank tree
    if (dsu->rank[raiz_i] < dsu->rank[raiz_j]) {
        dsu->parent[raiz_i] = raiz_j;
    } else if (dsu->rank[raiz_i] > dsu->rank[raiz_j]) {
        dsu->parent[raiz_j] = raiz_i;
    } else {
        // Ranks are equal, arbitrarily make raiz_i the parent of raiz_j
        dsu->parent[raiz_j] = raiz_i;
        dsu->rank[raiz_i]++; // Increment rank of the new root
    }
    return 1; // Union occurred
}

// Static helper: Creates and initializes the internal DSU structure.
static DSU_Internal* _dsu_internal_criar(Ponto **todos_os_pontos, int num_pontos) {
    if (num_pontos < 0) return NULL; // Allow num_pontos = 0 for empty graph handling
    if (num_pontos > 0 && !todos_os_pontos) return NULL;


    DSU_Internal *dsu = (DSU_Internal*)malloc(sizeof(DSU_Internal));
    if (!dsu) return NULL;

    dsu->num_elementos = num_pontos;
    dsu->parent = NULL;
    dsu->rank = NULL;
    dsu->mapeamento_pontos = NULL;

    if (num_pontos > 0) { // Only allocate arrays if there are elements
        dsu->parent = (int*)malloc(sizeof(int) * num_pontos);
        dsu->rank = (int*)malloc(sizeof(int) * num_pontos);
        dsu->mapeamento_pontos = (Ponto**)malloc(sizeof(Ponto*) * num_pontos);

        if (!dsu->parent || !dsu->rank || !dsu->mapeamento_pontos) {
            free(dsu->parent);
            free(dsu->rank);
            free(dsu->mapeamento_pontos);
            free(dsu);
            return NULL;
        }
        
        for (int i = 0; i < num_pontos; ++i) {
            dsu->parent[i] = i;   // Each element is initially its own parent
            dsu->rank[i] = 0;     // Initial rank is 0
            dsu->mapeamento_pontos[i] = todos_os_pontos[i]; // Store Ponto* for mapping
        }
    }
    return dsu;
}

// Static helper: Frees resources used by the internal DSU structure.
static void _dsu_internal_liberar(DSU_Internal *dsu) {
    if (!dsu) return;
    free(dsu->parent);
    free(dsu->rank);
    free(dsu->mapeamento_pontos); // Frees the array of Ponto* pointers, not Ponto objects
    free(dsu);
}


/* --- Public DSU_Ponto_Manager functions (implementations) --- */

// DSU_Ponto_Manager is a wrapper around DSU_Internal.
struct DSU_Ponto_Manager {
    DSU_Internal *internal_dsu;
};

DSU_Ponto_Manager* dsu_pontos_criar(Ponto **todos_os_pontos, int num_pontos) {
    DSU_Ponto_Manager *manager = (DSU_Ponto_Manager*)malloc(sizeof(DSU_Ponto_Manager));
    if (!manager) return NULL;

    manager->internal_dsu = _dsu_internal_criar(todos_os_pontos, num_pontos);
    if (!manager->internal_dsu) {
        free(manager);
        return NULL;
    }
    return manager;
}

void dsu_pontos_liberar(DSU_Ponto_Manager *manager) {
    if (!manager) return;
    _dsu_internal_liberar(manager->internal_dsu);
    free(manager);
}

int dsu_pontos_unir(DSU_Ponto_Manager *manager, Ponto *p1, Ponto *p2) {
    if (!manager || !manager->internal_dsu || !p1 || !p2) return -1; // Invalid parameters

    int idx1 = _dsu_internal_obter_indice_ponto(manager->internal_dsu, p1);
    int idx2 = _dsu_internal_obter_indice_ponto(manager->internal_dsu, p2);

    if (idx1 == -1 || idx2 == -1) return -1; // Ponto not found in DSU mapping

    return _dsu_internal_unir_conjuntos(manager->internal_dsu, idx1, idx2);
}

int dsu_pontos_mesmo_conjunto(DSU_Ponto_Manager *manager, Ponto *p1, Ponto *p2) {
    if (!manager || !manager->internal_dsu || !p1 || !p2) return -1; // Invalid parameters

    int idx1 = _dsu_internal_obter_indice_ponto(manager->internal_dsu, p1);
    int idx2 = _dsu_internal_obter_indice_ponto(manager->internal_dsu, p2);

    if (idx1 == -1 || idx2 == -1) return -1; // Ponto not found in DSU mapping

    int raiz1 = _dsu_internal_encontrar_representante(manager->internal_dsu, idx1);
    int raiz2 = _dsu_internal_encontrar_representante(manager->internal_dsu, idx2);

    if (raiz1 == -1 || raiz2 == -1) return -1; // Error finding representatives

    return (raiz1 == raiz2) ? 1 : 0;
}


/* --- Kruskal's Algorithm Implementation --- */

Aresta** algoritmo_kruskal(Ponto **todos_os_pontos_unicos, int num_total_pontos,
                             Aresta **arestas_ordenadas, int num_arestas,
                             int *tamanho_mst_resultado, double *custo_total_mst) {

    // Essential output pointers must be valid
    if (!tamanho_mst_resultado || !custo_total_mst) {
        return NULL; 
    }
    // Initialize outputs for all paths, including early error exits
    *tamanho_mst_resultado = 0;
    *custo_total_mst = 0.0;

    // Validate counts and corresponding data pointers
    if (num_total_pontos < 0 || (num_total_pontos > 0 && !todos_os_pontos_unicos)) {
        return NULL; // Invalid vertex count or NULL vertex array when count > 0
    }
    if (num_arestas < 0 || (num_arestas > 0 && !arestas_ordenadas)) {
        return NULL; // Invalid edge count or NULL edge array when count > 0
    }

    // Initialize DSU manager
    DSU_Ponto_Manager *dsu_manager = dsu_pontos_criar(todos_os_pontos_unicos, num_total_pontos);
    if (!dsu_manager) {
        // Already set outputs to 0, just return NULL
        return NULL; // Failed to create DSU manager
    }

    // The MST will have at most num_total_pontos - 1 edges.
    // If num_total_pontos is 0 or 1, MST has 0 edges.
    int max_arestas_mst = (num_total_pontos > 1) ? (num_total_pontos - 1) : 0;
    Aresta **mst_arestas = NULL; // This will be the array of Aresta* for the MST

    if (max_arestas_mst > 0) {
        mst_arestas = (Aresta**)malloc(sizeof(Aresta*) * max_arestas_mst);
        if (!mst_arestas) {
            dsu_pontos_liberar(dsu_manager);
            // Outputs already set to 0
            return NULL; // Memory allocation failed for MST array
        }
    }
    // If max_arestas_mst is 0, mst_arestas remains NULL, which is correct for 0 or 1 vertex.

    int arestas_adicionadas = 0;
    double custo_acumulado = 0.0;

    // Iterate through all sorted edges
    for (int i = 0; i < num_arestas; ++i) {
        Aresta *aresta_atual = arestas_ordenadas[i];

        //tinha erro aqui

        Ponto *p1 = retornaP1(aresta_atual);
        Ponto *p2 = retornaP2(aresta_atual);

        //tinha erro aqui

        // Check if p1 and p2 are already connected (in the same set)
        int mesmo_conjunto_status = dsu_pontos_mesmo_conjunto(dsu_manager, p1, p2);

        // tinha erro aqui
        if (mesmo_conjunto_status == 0) { // If p1 and p2 are in different sets
            // Try to add this edge to the MST if there's space.
            // An MST for V vertices has V-1 edges. If the graph is disconnected, it's a forest with V-C edges.
            // max_arestas_mst is V-1, which is an upper bound.
            if (arestas_adicionadas < max_arestas_mst) {
                // Attempt to unite the sets of p1 and p2
    
                //tinha erro aqui

                    mst_arestas[arestas_adicionadas] = aresta_atual; // Add edge to MST
                    custo_acumulado += retornaTamanhoAresta(aresta_atual);
                    arestas_adicionadas++;
                    //TODO: remover isso abaixo?
            }
            // If arestas_adicionadas == max_arestas_mst, the MST array is full.
            // This typically means V-1 edges have been added for a connected graph of V vertices.
            // No more edges can be added to this mst_arestas array.
            // Kruskal will continue, but subsequent 'dsu_pontos_mesmo_conjunto' should return 1
            // for edges within this now-connected component.
        }
        
        // Optimization: If we have found V-1 edges (and graph is connected), we could break.
        // However, Kruskal naturally handles disconnected graphs by producing a minimum spanning forest.
        // The loop runs through all edges. The number of edges added will be V-C (vertices - components).
        // The check `arestas_adicionadas < max_arestas_mst` correctly guards mst_arestas bounds.
        if (arestas_adicionadas == num_total_pontos -1 && num_total_pontos >0) {
            // This is a common optimization if the graph is known/expected to be connected.
            // For a general MSF, let Kruskal process all edges.
            // break; 
        }
    }

    *tamanho_mst_resultado = arestas_adicionadas;
    *custo_total_mst = custo_acumulado;

    // If no edges were added to MST (e.g. graph with 1 vertex, or no edges provided),
    // and mst_arestas was allocated (max_arestas_mst > 0), free it and return NULL.
    if (arestas_adicionadas == 0 && mst_arestas != NULL) {
        free(mst_arestas);
        mst_arestas = NULL;
    }
    // If arestas_adicionadas > 0 but less than max_arestas_mst, mst_arestas is valid but potentially oversized.
    // The caller uses '*tamanho_mst_resultado' to know how many elements are valid.
    // Optionally, one could realloc here to shrink mst_arestas, but it's not strictly necessary.
    // Aresta **temp_mst = realloc(mst_arestas, sizeof(Aresta*) * arestas_adicionadas);
    // if (arestas_adicionadas > 0 && temp_mst) mst_arestas = temp_mst; else if (arestas_adicionadas > 0 && !temp_mst) { /* realloc failed, handle */ }

    dsu_pontos_liberar(dsu_manager);
    return mst_arestas; // This could be NULL if MST is empty
}