      
#ifndef KRUSKAL_H
#define KRUSKAL_H

#include "ponto.h"     // For Ponto struct definition
#include "distancia.h" // For Aresta struct definition
#include <stdlib.h>    // For NULL

// --- DSU (Disjoint Set Union) for Ponto objects ---

// Opaque type for the DSU manager specialized for Ponto objects
typedef struct DSU_Ponto_Manager DSU_Ponto_Manager;

/**
 * @brief Creates and initializes a DSU manager for a given set of Ponto objects.
 * Each Ponto* in 'todos_os_pontos' will be an element in the DSU.
 * Internally, uses union by rank and find without path compression.
 *
 * @param todos_os_pontos An array of unique Ponto* objects. These are the elements the DSU will manage.
 *                        The DSU creates an internal mapping for these Ponto objects.
 *                        The Ponto objects themselves are not copied or owned by the DSU.
 * @param num_pontos The number of Ponto objects in the 'todos_os_pontos' array.
 * @return A pointer to the newly created DSU_Ponto_Manager, or NULL on failure (e.g., memory allocation).
 */
DSU_Ponto_Manager* dsu_pontos_criar(Ponto **todos_os_pontos, int num_pontos);

/**
 * @brief Frees all resources used by the DSU_Ponto_Manager.
 * This includes internal arrays and mappings. It does NOT free the Ponto objects themselves,
 * as their lifecycle is managed externally.
 *
 * @param manager A pointer to the DSU_Ponto_Manager to be freed. If NULL, the function does nothing.
 */
void dsu_pontos_liberar(DSU_Ponto_Manager *manager);

/**
 * @brief Unites the sets containing Ponto p1 and Ponto p2.
 * Uses union by rank. Does nothing if they are already in the same set.
 *
 * @param manager The DSU_Ponto_Manager instance.
 * @param p1 Pointer to the first Ponto object.
 * @param p2 Pointer to the second Ponto object.
 * @return 1 if p1 and p2 were in different sets and their sets are now united.
 *         0 if p1 and p2 were already in the same set.
 *        -1 if an error occurred (e.g., manager is NULL, or p1/p2 not found in DSU's mapping).
 */
int dsu_pontos_unir(DSU_Ponto_Manager *manager, Ponto *p1, Ponto *p2);

/**
 * @brief Checks if Ponto p1 and Ponto p2 belong to the same set.
 * Uses find without path compression.
 *
 * @param manager The DSU_Ponto_Manager instance.
 * @param p1 Pointer to the first Ponto object.
 * @param p2 Pointer to the second Ponto object.
 * @return 1 if p1 and p2 are in the same set.
 *         0 if they are in different sets.
 *        -1 if an error occurred (e.g., manager is NULL, or p1/p2 not found in DSU's mapping).
 */
int dsu_pontos_mesmo_conjunto(DSU_Ponto_Manager *manager, Ponto *p1, Ponto *p2);


// --- Kruskal's Algorithm ---

/**
 * @brief Finds the Minimum Spanning Tree (MST) or Minimum Spanning Forest (MSF) of a graph.
 * The graph is defined by a list of vertices (Ponto objects) and a list of edges (Aresta objects).
 * The DSU implementation used internally employs union by rank and find WITHOUT path compression.
 *
 * @param todos_os_pontos_unicos Array of all unique Ponto* vertices in the graph. This list is used
 *                               to initialize the DSU structure.
 * @param num_total_pontos Number of unique vertices in 'todos_os_pontos_unicos'.
 * @param arestas_ordenadas Array of Aresta* edges. IMPORTANT: These edges MUST be pre-sorted by
 *                          weight (tamanho) in non-decreasing order.
 * @param num_arestas Number of edges in 'arestas_ordenadas'.
 * @param tamanho_mst_resultado Pointer to an integer where the number of edges in the resulting MST/MSF
 *                              will be stored.
 * @param custo_total_mst Pointer to a double where the total cost (sum of weights) of the MST/MSF
 *                        will be stored.
 * @return An array of Aresta* pointers representing the edges in the MST/MSF.
 *         The size of this array is given by '*tamanho_mst_resultado'.
 *         The caller is responsible for freeing this returned array of pointers (e.g., using free()).
 *         The Aresta objects pointed to by the array are NOT freed by this function (they are assumed
 *         to be managed externally, similar to the input 'arestas_ordenadas').
 *         Returns NULL if an error occurs (e.g., memory allocation failure, invalid parameters) or
 *         if the MST/MSF is empty (e.g., graph with 0 or 1 vertex, or no edges).
 */
Aresta** algoritmo_kruskal(Ponto **todos_os_pontos_unicos, int num_total_pontos,
                             Aresta **arestas_ordenadas, int num_arestas,
                             int *tamanho_mst_resultado, double *custo_total_mst);

#endif // KRUSKAL_H

    