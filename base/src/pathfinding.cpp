#include "pathfinding.h"
#include "params.h"
#include "Arduino.h"
#include <math.h>
#include <algorithm>


Waypoint WP_COUPE[MAX_WP] = {
        
    //{coord_x, coord_y, {liste_adjacence avec distances}}
    //ne pas changer l'ordre!
    { 450,  400, {    0,    NO,   569,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO}}, //WP pour aller cherche les gobelets dans écueuil bleu
    {1500,  572, {   NO,     0,   728,   727,    NO,   428, 828-9,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO}}, //WP Sud Centre
    { 772,  572, {  569,   728,     0,1455-9,    NO,    NO,    NO,   428,    NO, 828-9,    NO, LONGR,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO}}, //WP corner SO
    {2227,  572, {   NO,   727,1455-9,     0,   569,    NO,    NO,    NO,   428,    NO, 828-9,    NO, LONGR,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO}}, //WP corner SE
    {2550,  400, {   NO,    NO,    NO,   569,     0,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO}}, //WP pour aller checher les gobelets dans écueuil jaune
    {1500, 1000, {   NO,   428,    NO,    NO,    NO,     0,   400,   728,   727,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO}}, //WP Centre du terrain
    {1500, 1400, {   NO, 828-9,    NO,    NO,    NO,   400,     0,    NO,    NO,   728,   727,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO}}, //WP Nord Centre
    { 772, 1000, {   NO,    NO,   428,    NO,    NO,   728,    NO,     0,1455-9,   400,    NO, LONGR,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO}}, //WP Centre Ouest
    {2227, 1000, {   NO,    NO,    NO,   428,    NO,   727,    NO,1455-9,     0,    NO,   400,    NO, LONGR,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO}}, //WP Centre Est
    { 772, 1400, {   NO,    NO, 828-9,    NO,    NO,    NO,   728,   400,    NO,     0,1455-9, LONGR,    NO,   YES,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO}}, //WP corner NO
    {2227, 1400, {   NO,    NO,    NO, 828-9,    NO,    NO,   727,    NO,   400,1455-9,     0,    NO, LONGR,    NO,   YES,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO}}, //WP corner NE
    { 772, 1200, {   NO,    NO, LONGR,    NO,    NO,    NO,    NO, LONGR,    NO, LONGR,    NO,     0,    NO,    NO,    NO,    NO,    NO,    NO,    NO,   YES,    NO,    NO,    NO}}, //WP link to blue garage (do not stop at this point otherwise)
    {2227, 1200, {   NO,    NO,    NO, LONGR,    NO,    NO,    NO,    NO, LONGR,    NO, LONGR,    NO,     0,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,   YES,    NO}}, //WP link to yellow garage (do not stop at this point otherwise)
    { 670, 1600, {   NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,   YES,    NO,    NO,    NO,     0,    NO,   YES,    NO,   YES,    NO,    NO,    NO,    NO,    NO}}, //WP interm node north west (bleu)
    {2330, 1600, {   NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,   YES,    NO,    NO,    NO,     0,    NO,   YES,    NO,   YES,    NO,    NO,    NO,    NO}}, //WP interm node north east (yellow)
    { 500, 1800, {   NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,   YES,    NO,     0,    NO,    NO,    NO,    NO,    NO,    NO,    NO}}, //WP proche phare bleu
    {2500, 1800, {   NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,   YES,    NO,     0,    NO,    NO,    NO,    NO,    NO,    NO}}, //WP proche phare yellow
    { 825, 1800, {   NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,   YES,    NO,    NO,    NO,     0,    NO,    NO,    NO,    NO,    NO}}, //WP proche eceuils bleu nord
    {2175, 1800, {   NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,   YES,    NO,    NO,    NO,     0,    NO,    NO,    NO,    NO}}, //WP proche eceuils jaune nord
    { 200, 1200, {   NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,   YES,    NO,    NO,    NO,    NO,    NO,    NO,    NO,     0,    NO,    NO,    NO}}, //WP garage rob1A bleu
    {9999, 9999, {   NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,     0,    NO,    NO}}, //WP garage rob2A bleu (isolé)
    {2800, 1200, {   NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,   YES,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,     0,    NO}}, //WP garage rob1A yellow
    {9999, 9999, {   NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    0 }} //WP garage rob2A yellow (isolé)

};

LidarData ATC::lidar = LidarData(false);

Graph ATC::graph = ATC::generate_graph(WP_COUPE, 23);

Geom_Vec::Geom_Vec(float x, float y){
    this->x = x;
    this->y = y;
}

Geom_Vec::Geom_Vec(float start[2], float end[2]){
    this->x = end[0] - start[0];
    this->y = end[1] - start[1];
}

Geom_Vec Geom_Vec::scale(float factor){
    return Geom_Vec(x*factor, y*factor);
}

float Geom_Vec::length(){
    return sqrtf(x*x + y*y);
}

float Geom_Vec::dot(Geom_Vec other){
    return x*other.x + y*other.y;
}

float Geom_Vec::get_angle(){
    if (x != 0){
        float at = (float) atan(y/x)*360/(2*3.1415);
        if (x >= 0){ return at; }
        else{ return 180 + at; }
    }
    else{
        if (y>0){ return 90; }
        else if (y < 0){ return -90; }
        else{ return 0; }
    }
}

float Geom_Vec::dist_to_point(float point[2]){
    Geom_Vec vec_point(point[0], point[1]);
    float len_line = this->length();
    Geom_Vec sc_line = this->scale(1/len_line);
    Geom_Vec sc_ptvec = vec_point.scale(1/len_line);
    float t = sc_line.dot(sc_ptvec);
    if (t < 0){
        t = 0;
    }
    else if (t > 1) {
        t = 1;
    }
    Geom_Vec nearest = this->scale(t);
    float nearest_coords[2] = {nearest.x, nearest.y};
    float dist = Geom_Vec(point, nearest_coords).length();
    return dist;
}

float Geom_Vec::dist_to_point(Geom_Vec vec_point){
    float len_line = this->length();
    Geom_Vec sc_line = this->scale(1/len_line);
    Geom_Vec sc_ptvec = vec_point.scale(1/len_line);
    float t = sc_line.dot(sc_ptvec);
    if (t < 0){
        t = 0;
    }
    else if (t > 1) {
        t = 1;
    }
    Geom_Vec nearest = this->scale(t);
    float nearest_coords[2] = {nearest.x, nearest.y};
    float pt[2] = {vec_point.x, vec_point.y};
    float dist = Geom_Vec(pt, nearest_coords).length();
    return dist;
}

int ATC::min_dist(unsigned int *dist, bool *Dset, int wp_number){
    unsigned int min = 65535;
    int index = 0;
    for(int i=0;i<wp_number;i++){
        if(Dset[i]==false and dist[i] <= min){
            min = dist[i];
            index = i;
        }
    }
    return index;
}

DijkstraResult ATC::dijkstra_crap(Graph graph, int src_index){
    unsigned int dist[MAX_WP];
    bool Dset[MAX_WP];
    int parent[MAX_WP];
    for(int i=0;i<graph.wp_number;i++){
        dist[i] = 65535;
        Dset[i] = false;
        parent[i] = -128;
    }
    dist[src_index] = 0;
    parent[src_index] = -1;
    for(int i=0;i<graph.wp_number;i++){
        int u = min_dist(dist, Dset, graph.wp_number);
        Dset[u] = true;
        for(int j=0;j<graph.wp_number;j++){
            if(not(Dset[j]) and graph.graph[u][j] and dist[u] != 65535 and dist[u]+graph.graph[u][j]<dist[j]){
                dist[j]=dist[u]+graph.graph[u][j];
                parent[j]=u;
            }
        }
    }
    DijkstraResult result;
    result.dep_index = src_index;
    /* je voulais juste passer la liste dans ma struct,
    mais passer toute la liste d'un coup ne fonctionne pas,
    donc je fais ces trucs moches. désolé */
    for(int i=0;i<MAX_WP;i++){
        result.dist[i] = dist[i];
        result.parent[i] = parent[i];
    }
    return result;
}

Geom_Vec ATC::from_pol_to_abs(float robot_pos[3], int lid_ang, float lid_dist){
    /* TODO: Vérifier que les résultats sont les bons */
    float loc_px = lid_dist*cosf((lid_ang - robot_pos[3])*2*3.1415/360);
    float loc_py = lid_dist*sinf((lid_ang - robot_pos[3])*2*3.1415/360);
    Geom_Vec abs_pt = Geom_Vec(robot_pos[0]+loc_px, robot_pos[1]+loc_py);
    return abs_pt;
}

PseudoRoute ATC::going_to(int *parent, int index_dest, const int wp_number){
    bool reached_src = false;
    int parcours_inverse[wp_number];
    for(int i=0;i<wp_number;i++){
        parcours_inverse[i] = -128;
    }
    int old_dest = index_dest;
    int i=0;
    bool shit = false;
    while (not(reached_src)){
        parcours_inverse[i]=old_dest;
        if (old_dest!=-128){
            old_dest=parent[old_dest];
            i+=1;
            if (old_dest==-1){
                reached_src = true;
            }
            if (old_dest==-128){
                reached_src = true;
                shit = true;
            }
        }
        else{
            reached_src = true;
        }
    }
    /*for(int i=0;i<wp_number;i++){
        std::cout << parcours_inverse[i] << ", ";
    }
    std::cout << std::endl;*/
    PseudoRoute result;
    for(int i=0;i<wp_number;i++){
        result.parcours[wp_number-i-1] = parcours_inverse[i];
    }
    result.reaches = not(shit);
    return result;
}

bool ATC::is_path_blocked(float start[2], float end[2], LidarData *lidar, float robot_pos[3]){
    SerialCtrl.print("is_path_blocked: start: ");
    SerialCtrl.print(start[0]);
    SerialCtrl.print(", ");
    SerialCtrl.print(start[1]);
    SerialCtrl.print(" end: ");
    SerialCtrl.print(end[0]);
    SerialCtrl.print(", ");
    SerialCtrl.print(end[1]);
    SerialCtrl.print(" rbpos: ");
    SerialCtrl.print(robot_pos[0]);
    SerialCtrl.print(", ");
    SerialCtrl.print(robot_pos[1]);
    SerialCtrl.print(", ");
    SerialCtrl.println(robot_pos[2]);

    float xyrobot[2] = {robot_pos[0], robot_pos[1]};

    int angle_str = (int) Geom_Vec(xyrobot, start).get_angle();
    int angle_stp = (int) Geom_Vec(xyrobot, end).get_angle();

    int ang_span_begin;
    int ang_span_end;
    if (Geom_Vec(xyrobot, start).length() < 10){
        /* Le robot est suffisament proche du point d'ou il souhaite partir */
        ang_span_begin = angle_stp - 22;
        ang_span_end = angle_stp + 23;
    }
    else{
        ang_span_begin = std::min(angle_str%360, angle_stp%360) - 22;
        ang_span_end = std::max(angle_str%360, angle_stp%360) + 23;
    }
    for(int ang=ang_span_begin;ang<ang_span_end;ang++){
        float dist_lid = (*lidar).get_distance(ang);
        SerialCtrl.print("ang: ");
        SerialCtrl.print(ang);
        //si mesure valide et suffisamment écartée (15cm):
        if (dist_lid>150 and (*lidar).get_quality(ang) > 0){
            SerialCtrl.print(" valide dist: ");
            SerialCtrl.print(dist_lid);
            Geom_Vec pt = from_pol_to_abs(robot_pos, ang, dist_lid);
            SerialCtrl.print(" plot x:");
            SerialCtrl.print(pt.x);
            SerialCtrl.print(" y: ");
            SerialCtrl.print(pt.y);
            if (0 < pt.x and pt.x < 3000 and 0 < pt.y and pt.y < 2000){
                SerialCtrl.print(" valide dist_to_path: ");
                float dist_pt_attempt = Geom_Vec(start, end).dist_to_point(pt);
                SerialCtrl.print(dist_pt_attempt);
                if (dist_pt_attempt < SEUIL_DANGEREUX){
                    SerialCtrl.println(" path is blocked");
                    return true;
                }
                else{
                    SerialCtrl.println(" point_does_not_block");
                }
            }
            else{
                SerialCtrl.println(" hors terrain");
            }
        }
        else{
            SerialCtrl.println(" invalide ou trop proche");
        }
        //si mesure invalide, ne rien faire
    }
    SerialCtrl.println("path is not blocked");
    return false;
}

Route ATC::find_route(Graph *graph_orig, float *depart, float *destination, LidarData *lidar, float *robot_pos){
    /* checking what is the closest waypoint to start */
    Graph graph = *graph_orig;
    unsigned int min_dist_start = 65535;
    int first_wp = -1;
    for (int index=0;index<graph.wp_number;index++){
        float xyrobot[2] = {depart[0], depart[1]};
        float xywp[2] = {(*graph.wp_list[index]).x, (*graph.wp_list[index]).y};
        unsigned int dist_wp = (unsigned int) Geom_Vec(xyrobot, xywp).length();
        if (dist_wp < min_dist_start){
            first_wp = index;
            min_dist_start = dist_wp;
        }
    }
    /*std::cout << "firstwp " << first_wp << std::endl;*/

    

    /* checking what is the closest waypoint to destination */
    unsigned int min_dist_end = 65535;
    int last_wp = -1;
    for (int index=0;index<graph.wp_number;index++){
        float xyrobot[2] = {destination[0], destination[1]};
        float xywp[2] = {(*graph.wp_list[index]).x, (*graph.wp_list[index]).y};
        unsigned int dist_wp = (unsigned int) Geom_Vec(xyrobot, xywp).length();
        if (dist_wp < min_dist_end){
            last_wp = index;
            min_dist_end = dist_wp;
        }
    }
    /*std::cout << "lastwp " << last_wp << std::endl;*/

    /* si first et last wp sont les mêmes, route + courte*/
    if (first_wp == last_wp){
        //check direct route free or not
        bool direct_blocked = ATC::is_path_blocked(depart, destination, lidar, robot_pos);
        //générer la route et retourner
        Route direct_route;
        direct_route.stuck = false;
        direct_route.isfree = not(direct_blocked);
        direct_route.isshortest = true;
        direct_route.length = 0;
        direct_route.start[0] = depart[0];
        direct_route.start[1] = depart[1];
        direct_route.end[0] = destination[0];
        direct_route.end[1] = destination[1];
        return direct_route;
    }

    /* check if path between start point and first waypoint is free or not */
    float xywpdep[2] = {(*graph.wp_list[first_wp]).x, (*graph.wp_list[first_wp]).y};
    bool start_obstructed = ATC::is_path_blocked(depart, xywpdep, lidar, robot_pos);

    /* check if path between destin point and last waypoint is free or not */
    float xywpdest[2] = {(*graph.wp_list[last_wp]).x, (*graph.wp_list[last_wp]).y};
    bool end_obstructed = ATC::is_path_blocked(depart, xywpdest, lidar, robot_pos);

    bool access_to_graph_obstructed = start_obstructed and end_obstructed;

    /* shortest route with dijkstra */
    DijkstraResult dijres = ATC::dijkstra_crap(graph, first_wp);

    /*std::cout << "dijres" << std::endl;
    std::cout << "dep_index" << dijres.dep_index << std::endl;
    std::cout << "dist ";
    for(int i=0;i<MAX_WP;i++){
        std::cout << dijres.dist[i] << ", ";
    }
    std::cout << std::endl;
    std::cout << "parent ";
    for(int i=0;i<MAX_WP;i++){
        std::cout << dijres.parent[i] << ", ";
    }
    std::cout << std::endl;*/

    PseudoRoute psroute = ATC::going_to(dijres.parent, last_wp, graph.wp_number);

    /*std::cout << "psroute" << std::endl;
    std::cout << "reaches " << psroute.reaches << std::endl;
    std::cout << "parcours ";
    for(int i=0;i<graph.wp_number;i++){
        std::cout << psroute.parcours[i] << ", ";
    }
    std::cout << std::endl;*/

    /* checking if route obstructed or not */
    int start = 0;
    for(int i=0;i<graph.wp_number;i++){
        if (psroute.parcours[i] != -128){
            start=i;
            break;
        }
    }
    bool route_ok = true;
    for(int index=start+1;index<graph.wp_number;index++){
        //std::cout << "path from " << psroute.parcours[index-1] << " to " << psroute.parcours[index] << ": ";
        float xywpa[2] = {(*graph.wp_list[psroute.parcours[index-1]]).x, (*graph.wp_list[psroute.parcours[index-1]]).y};
        float xywpb[2] = {(*graph.wp_list[psroute.parcours[index]]).x, (*graph.wp_list[psroute.parcours[index]]).y};
        bool path_blocked = ATC::is_path_blocked(xywpa, xywpb, lidar, robot_pos);
        //std::cout << "blocked? " << path_blocked << std::endl;
        if (path_blocked){
            graph.graph[psroute.parcours[index-1]][psroute.parcours[index]] = 65535;
            graph.graph[psroute.parcours[index]][psroute.parcours[index-1]] = 65535;
            route_ok = false;
        }
    }

    /* si route ok du premier coup, constitution de la Route */
    if (route_ok){
        Route route;
        route.stuck = not(psroute.reaches);
        route.isfree = route_ok and not(access_to_graph_obstructed);
        route.isshortest = true;
        route.length = graph.wp_number-start;
        route.start[0] = depart[0];
        route.start[1] = depart[1];
        route.end[0] = destination[0];
        route.end[1] = destination[1];
        for(int i=start;i<graph.wp_number;i++){
            //std::cout << psroute.parcours[i] <<std::endl;
            route.wp_list[i-start] = graph.wp_list[psroute.parcours[i]];
            //std::cout << (*route.wp_list[i]).x << ", " << (*route.wp_list[i]).y <<std::endl;
        }
        return route;
    }
    else{
        /* la route est encombrée, faut recommencer */
        /* TODO: tester */
        bool another_route_found = false;
        while (not(another_route_found)){
            bool this_route_ok = true;
            /* shortest route with dijkstra */
            DijkstraResult this_dijres = ATC::dijkstra_crap(graph, first_wp);
            PseudoRoute this_psroute = ATC::going_to(this_dijres.parent, last_wp, graph.wp_number);
            if(!this_psroute.reaches){
                break;
            }
            /* checking if route obstructed or not */
            int this_start = 0;
            for(int i=0;i<MAX_WP;i++){
                if (this_psroute.parcours[i] != -128){
                    start=i;
                    break;
                }
            }
            for(int index=this_start+1;index<graph.wp_number;index++){
                float xywpa[2] = {(*graph.wp_list[this_psroute.parcours[index-1]]).x, (*graph.wp_list[this_psroute.parcours[index-1]]).y};
                float xywpb[2] = {(*graph.wp_list[this_psroute.parcours[index]]).x, (*graph.wp_list[this_psroute.parcours[index]]).y};
                bool path_blocked = ATC::is_path_blocked(xywpa, xywpb, lidar, robot_pos);
                if (path_blocked){
                    graph.graph[this_psroute.parcours[index-1]][this_psroute.parcours[index]] = 65535;
                    graph.graph[this_psroute.parcours[index]][this_psroute.parcours[index-1]] = 65535;
                    this_route_ok = false;
                }
            }
            if (this_route_ok){
                /* this route isn't the best, but it's free right now*/
                Route route;
                route.stuck = not(this_psroute.reaches);
                route.isfree = true and not(access_to_graph_obstructed);
                route.isshortest = false;
                route.length = graph.wp_number-this_start;
                route.start[0] = depart[0];
                route.start[1] = depart[1];
                route.end[0] = destination[0];
                route.end[1] = destination[1];
                for(int i=this_start;i<graph.wp_number;i++){
                    route.wp_list[i-this_start] = graph.wp_list[this_psroute.parcours[i]];
                }
                return route;
            }
        }
        /* route got stuck return default with not free flag */
        Route route;
        route.stuck = not(psroute.reaches);
        route.isfree = false;
        route.isshortest = true;
        route.length = graph.wp_number-start;
        route.start[0] = depart[0];
        route.start[1] = depart[1];
        route.end[0] = destination[0];
        route.end[1] = destination[1];
        for(int i=start;i<graph.wp_number;i++){
            //std::cout << psroute.parcours[i] <<std::endl;
            route.wp_list[i-start] = graph.wp_list[psroute.parcours[i]];
            //std::cout << (*route.wp_list[i]).x << ", " << (*route.wp_list[i]).y <<std::endl;
        }
        return route;
    }
}

Graph ATC::generate_graph(Waypoint *waypoint_list, int wp_number){
    Graph graph;
    graph.wp_number = wp_number;
    for(int i=0;i<wp_number;i++){
        graph.wp_list[i] = &waypoint_list[i];
        for(int j=0;j<wp_number;j++){
            graph.graph[i][j] = (waypoint_list[i]).wp_adj[j];
        }
    }
    return graph;
}

PointSeq ATC::read_route(Route &route){
    PointSeq psq;
    for(int i=0;i<route.length;i++){
        psq.point[i][0] = (*route.wp_list[i]).x;
        psq.point[i][1] = (*route.wp_list[i]).y;
    }
    psq.point[route.length][0] = route.end[0];
    psq.point[route.length][1] = route.end[1];
    psq.tot_len = route.length+1;
    return psq;
}

bool ATC::proximity_check(LidarData *lidar, bool front, float *robot_pos){
    int ang_start = (front)? -15 : (180-15);
    int ang_stop = (front)? 16 : (180+16);
    for(int ang=ang_start;ang<ang_stop;ang++){
        if ((*lidar).get_quality(ang%360)>0){
            float dist_lid = (*lidar).get_distance(ang%360);
            if (dist_lid < 500){
                Geom_Vec pt = from_pol_to_abs(robot_pos, ang, dist_lid);
                if (0 < pt.x and pt.x < 3000 and 0 < pt.y and pt.y < 2000){
                    SerialCtrl.print("proximity_check: ang:");
                    SerialCtrl.print(ang);
                    SerialCtrl.print(" dist: ");
                    SerialCtrl.print(dist_lid);
                    SerialCtrl.println(" in zone and too close(50cm)");
                    return true;
                }
            }
        }
    }
    return false;
}