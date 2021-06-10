#ifndef PATHFINDING
#define PATHDINFING

#include "lidar/Lidar.h"
#include "params.h"

const int MAX_WP = 30; /* à augmenter si bcp de points ajoutés */
const unsigned int NO = 65535; /* entier max arduino non-signé, "approche l'infini" */
const unsigned int YES = 4000; /* raccourci pour connecter deux wp sur le graphe sans calculer la vraie distance */
const unsigned int SHORT = 3500; /* raccourci pour connecter deux wp sur le graphe sans calculer la vraie distance, avec un chemin avantagé */
const unsigned int LONGR = 4500; /* raccourci pour connecter deux wp sur le graphe sans calculer la vraie distance, avec un chemin désavantagé */

const float PERIM_MAX = 1300;
const float SEUIL_DANGEREUX = (PERIM_MAX/(2*PI)*1.5)*1.1;

struct Waypoint
{
    /* coordonées sur le terrain, en mm, depuis le coin bleu sud */
    float x;
    float y;
    /* liste de distances séparant le waypoint des autres sur la carte */
    int wp_adj[MAX_WP];
};

/* à virer autre part ptet
Waypoint wp_list[MAX_WP] = {
    
};*/

/* Un graphe de distance entre des Waypoints*/
struct Graph
{
    /* le nombre de wp présents dans le graphe */
    int wp_number;
    /* La liste des Waypoints concernés (attention à l'ordre) */
    Waypoint* wp_list[MAX_WP];
    /* le graphe */
    int graph[MAX_WP][MAX_WP];
};

/* Désigne une suite de points à emprunter pour se rendre d'un point A à un point B via les Waypoints*/
struct Route
{
    /* Quantité de waypoints à emprunter (destination omises, point de départ omis) */
    int length;
    /* Référence au point de départ*/
    float start[2];
    /* Référence au point de destination */
    float end[2];
    /* Liste des Waypoints à emprunter dans l'ordre */
    Waypoint* wp_list[MAX_WP];
    /* La route ne mène pas à la destination (dijkstra ne donne pas de solution) */
    bool stuck;
    /* La route est libre immédiatement */
    bool isfree;
    /* La route est la plus courte, sans compter les éventuels obstacles */
    bool isshortest;
};

/* Élement retourné par dijkstra */
struct DijkstraResult
{
    /* Index du point de départ dans le graphe */
    int dep_index;
    /* Liste des distances depuis le point de départ */
    int dist[MAX_WP];
    /* Liste des parents de chaque waypoint */
    int parent[MAX_WP];
};

/* Un chemin qui pourrait être une route mais n'a pas encore été confirmée ou vérifiée*/
struct PseudoRoute
{
    /* Les indices des sommets du graphe à parcourir */
    int parcours[MAX_WP];
    /* Le chemin amène t'il à la destination */
    bool reaches;
};

class Geom_Vec
{
    public:
        Geom_Vec(float x, float y);
        Geom_Vec(float start[2], float end[2]);
        Geom_Vec scale(float factor);
        float length();
        float dot(Geom_Vec other); 
        float get_angle();
        float dist_to_point(float point[2]);
        float dist_to_point(Geom_Vec vec_point);
        float x;
        float y;
};

namespace ATC
{
    Graph generate_graph(Waypoint *waypoint_list, int wp_number);
    Route find_route(Graph &graph, float depart[2], float destination[2], Lidar lidar, float robot_pos[3]);
    bool is_path_blocked(float start[2], float end[2], Lidar lidar, float robot_pos[3]);
    int min_dist(unsigned int *dist, bool *Dset, int wp_number);
    DijkstraResult dijkstra_crap(Graph graph, int src_index);
    Geom_Vec from_pol_to_abs(float robot_pos[3], int lid_ang, float lid_dist);
    PseudoRoute going_to(int *parent, int index_dest, int wp_number);
}

#endif //PATHFINDING
