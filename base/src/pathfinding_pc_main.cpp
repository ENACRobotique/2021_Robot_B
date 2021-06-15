#include "pathfinding.h"
#include "lidar/Lidar.h"
#include <iostream>

int main(){
    Waypoint list_wp[4]={
        { 200,  200, {   0, 1600, 2600,   NO}}, 
        { 200, 1800, {1600,    0,   NO, 2600}}, 
        {2800,  200, {2600,   NO,    0, 1600}}, 
        {2800, 1800, {  NO, 2600, 1600,    0}}
    };
    Lidar lidar;
    Graph graph_orig = ATC::generate_graph(list_wp, 4);
    std::cout << "Graph:" << std::endl;
    std::cout << graph_orig.wp_number << std::endl;
    std::cout << graph_orig.wp_list << std::endl;
    std::cout << graph_orig.graph << std::endl;
    float dept[2] = {0.0, 0.0};
    float dest[2] = {3000.0, 2000.0};
    float rbpos[3] = {0.0, 0.0, 0.0};
    Route route = ATC::find_route(graph_orig, dept, dest, lidar, rbpos);
    std::cout << "Route:" << std::endl;
    std::cout << "long=" << route.length << std::endl;
    std::cout << "start=" << route.start << std::endl;
    std::cout << "end=" << route.end << std::endl;
    std::cout << "stuck=" << route.stuck << std::endl;
    std::cout << "isfree=" << route.isfree << std::endl;
    std::cout << "isshortest=" << route.isshortest << std::endl;
    std::cout << "Points:" << std::endl;
    for(int i=route.start_list;i<route.length+route.start_list;i++){
        //std::cout << "point " << i << ": "<< std::endl << (*route.wp_list[i]).x << std::endl;
        std::cout << "point " << i << ": " << (*route.wp_list[i]).x << ", " << (*route.wp_list[i]).y << std::endl;
    }
    std::cout << "fin prog" << std::endl;
    return 0;
}

/* g++ -g pathfinding_pc_main.cpp pathfinding.cpp lidar/Lidar.cpp -o proto */