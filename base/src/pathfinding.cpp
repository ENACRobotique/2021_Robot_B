#include "pathfinding.h"
#include "params.h"
#include <math.h>

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
        float at = (float) atan(y/x)*360/(2*PI);
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
    float loc_px = lid_dist*cosf((lid_ang - robot_pos[3])*2*PI/360);
    float loc_py = lid_dist*sinf((lid_ang - robot_pos[3])*2*PI/360);
    Geom_Vec abs_pt = Geom_Vec(robot_pos[0]+loc_px, robot_pos[1]+loc_py);
    return abs_pt;
}

PseudoRoute ATC::going_to(int *parent, int index_dest, const int wp_number){
    bool reached_src = false;
    int parcours_inverse[wp_number];
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
    PseudoRoute result;
    for(int i=0;i<wp_number;i++){
        result.parcours[wp_number-i] = parcours_inverse[i];
    }
    result.reaches = shit;
    return result;
}

bool ATC::is_path_blocked(float start[2], float end[2], Lidar lidar, float robot_pos[3]){
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
        ang_span_begin = min(angle_str%360, angle_stp%360) - 22;
        ang_span_end = max(angle_str%360, angle_stp%360) + 23;
    }
    for(int ang=ang_span_begin;ang<ang_span_end;ang++){
        float dist_lid = lidar.get_distance(ang);
        Geom_Vec pt = from_pol_to_abs(robot_pos, ang, dist_lid);
        if (0 < pt.x and pt.x < 3000 and 0 < pt.y and pt.y < 2000){
            float dist_pt_attempt = Geom_Vec(start, end).dist_to_point(pt);
            if (dist_pt_attempt < SEUIL_DANGEREUX){
                return true;
            }
        }
    }
    return false;
}

Route ATC::find_route(Graph &graph, float depart[2], float destination[2], Lidar lidar, float robot_pos[3]){
    /* checking what is the closest waypoint to start */
    unsigned int min_dist_start = 65535;
    int first_wp = -1;
    for (int index=0;index<graph.wp_number;index++){
        float xyrobot[2] = {robot_pos[0], robot_pos[1]};
        float xywp[2] = {(*graph.wp_list[index]).x, (*graph.wp_list[index]).y};
        unsigned int dist_wp = (unsigned int) Geom_Vec(xyrobot, xywp).length();
        if (dist_wp < min_dist_start){
            first_wp = index;
            min_dist_start = dist_wp;
        }
    }
    /* TODO:reminder check if path between start point and first waypoint is free or not */

    /* checking what is the closest waypoint to destination */
    unsigned int min_dist_end = 65535;
    int last_wp = -1;
    for (int index=0;index<graph.wp_number;index++){
        float xyrobot[2] = {robot_pos[0], robot_pos[1]};
        float xywp[2] = {(*graph.wp_list[index]).x, (*graph.wp_list[index]).y};
        unsigned int dist_wp = (unsigned int) Geom_Vec(xyrobot, xywp).length();
        if (dist_wp < min_dist_end){
            last_wp = index;
            min_dist_end = dist_wp;
        }
    }
    /* TODO:reminder check if path between destin point and last waypoint is free or not */

    /* shortest route with dijkstra */
    DijkstraResult dijres = ATC::dijkstra_crap(graph, first_wp);
    PseudoRoute psroute = ATC::going_to(dijres.parent, last_wp, graph.wp_number);

    /* checking if route obstructed or not */
    int start = 0;
    for(int i=0;i<MAX_WP;i++){
        if (psroute.parcours[i] != -128){
            start=i;
            break;
        }
    }
    bool route_ok = true;
    for(int index=start+1;index<MAX_WP;index++){
        float xywpa[2] = {(*graph.wp_list[psroute.parcours[index-1]]).x, (*graph.wp_list[psroute.parcours[index-1]]).y};
        float xywpb[2] = {(*graph.wp_list[psroute.parcours[index]]).x, (*graph.wp_list[psroute.parcours[index]]).y};
        bool path_blocked = ATC::is_path_blocked(xywpa, xywpb, lidar, robot_pos);
        if (path_blocked){
            graph.graph[psroute.parcours[index-1]][psroute.parcours[index]] = 65535;
            graph.graph[psroute.parcours[index]][psroute.parcours[index-1]] = 65535;
            route_ok = false;
        }
    }

    /* si route ok du premier coup, constitution de la Route */
    if (route_ok){
        Route route;
        route.stuck = psroute.reaches;
        route.isfree = route_ok;
        route.isshortest = true;
        route.length = MAX_WP-start;
        route.start[0] = depart[0];
        route.start[1] = depart[1];
        route.end[0] = destination[0];
        route.end[1] = destination[1];
        for(int i=0;i<route.length;i++){
            route.wp_list[i] = graph.wp_list[psroute.parcours[i]];
        }
        return route;
    }
    else{
        /* la route est encombrée, faut recommencer */
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
            for(int index=this_start+1;index<MAX_WP;index++){
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
                route.stuck = this_psroute.reaches;
                route.isfree = true;
                route.isshortest = false;
                route.length = MAX_WP-this_start;
                route.start[0] = depart[0];
                route.start[1] = depart[1];
                route.end[0] = destination[0];
                route.end[1] = destination[1];
                for(int i=0;i<route.length;i++){
                    route.wp_list[i] = graph.wp_list[this_psroute.parcours[i]];
                }
                return route;
            }
        }
        /* route got stuck return default with not free flag */
        Route route;
        route.stuck = psroute.reaches;
        route.isfree = false;
        route.isshortest = true;
        route.length = MAX_WP-start;
        route.start[0] = depart[0];
        route.start[1] = depart[1];
        route.end[0] = destination[0];
        route.end[1] = destination[1];
        for(int i=0;i<route.length;i++){
            route.wp_list[i] = graph.wp_list[psroute.parcours[i]];
        }
        return route;
    }
}

Graph ATC::generate_graph(Waypoint *waypoint_list, int wp_number){
    Graph graph;
    graph.wp_number = wp_number;
    for(int i=0;i<wp_number;i++){
        graph.wp_list[i] = waypoint_list[i];
        for(int j=0;j<wp_number;j++){
            graph.graph[i][j] = (*waypoint_list[i]).wp_adj[j];
        }
    }
    return graph;
}
