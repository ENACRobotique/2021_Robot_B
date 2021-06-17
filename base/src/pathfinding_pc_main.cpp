

#include "pathfinding.h"
#include "lidar/Lidar.h"


int main(){
    Waypoint WP_COUPE[MAX_WP] = {
    
        //{coord_x, coord_y, {liste_adjacence avec distances}}
        //ne pas changer l'ordre!
        { 230,  400, {    0,    NO,   569,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO}}, //WP pour aller cherche les gobelets dans écueuil bleu
        {1500,  572, {   NO,     0,   728,   727,    NO,   428, 828-9,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO}}, //WP Sud Centre
        { 772,  572, {  569,   728,     0,1455-9,    NO,    NO,    NO,   428,    NO, 828-9,    NO, LONGR,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO}}, //WP corner SO
        {2227,  572, {   NO,   727,1455-9,     0,   569,    NO,    NO,    NO,   428,    NO, 828-9,    NO, LONGR,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO}}, //WP corner SE
        {2770,  400, {   NO,    NO,    NO,   569,     0,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO}}, //WP pour aller checher les gobelets dans écueuil jaune
        {1500, 1000, {   NO,   428,    NO,    NO,    NO,     0,   400,   728,   727,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO}}, //WP Centre du terrain
        {1500, 1400, {   NO, 828-9,    NO,    NO,    NO,   400,     0,    NO,    NO,   728,   727,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO}}, //WP Nord Centre
        { 772, 1000, {   NO,    NO,   428,    NO,    NO,   728,    NO,     0,1455-9,   400,    NO, LONGR,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO}}, //WP Centre Ouest
        {2227, 1000, {   NO,    NO,    NO,   428,    NO,   727,    NO,1455-9,     0,    NO,   400,    NO, LONGR,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO}}, //WP Centre Est
        { 772, 1400, {   NO,    NO, 828-9,    NO,    NO,    NO,   728,   400,    NO,     0,1455-9, LONGR,    NO,   YES,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO}}, //WP corner NO
        {2227, 1400, {   NO,    NO,    NO, 828-9,    NO,    NO,   727,    NO,   400,1455-9,     0,    NO, LONGR,    NO,   YES,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO}}, //WP corner NE
        { 772, 1200, {   NO,    NO, LONGR,    NO,    NO,    NO,    NO, LONGR,    NO, LONGR,    NO,     0,    NO,    NO,    NO,    NO,    NO,    NO,    NO,   YES,   YES,    NO,    NO}}, //WP link to blue garage (do not stop at this point otherwise)
        {2227, 1200, {   NO,    NO,    NO, LONGR,    NO,    NO,    NO,    NO, LONGR,    NO, LONGR,    NO,     0,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,   YES,   YES}}, //WP link to yellow garage (do not stop at this point otherwise)
        { 670, 1600, {   NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,   YES,    NO,    NO,    NO,     0,    NO,   YES,    NO,   YES,    NO,    NO,    NO,    NO,    NO}}, //WP interm node north west (bleu)
        {2330, 1600, {   NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,   YES,    NO,    NO,    NO,     0,    NO,   YES,    NO,   YES,    NO,    NO,    NO,    NO}}, //WP interm node north east (yellow)
        { 300, 1900, {   NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,   YES,    NO,     0,    NO,    NO,    NO,    NO,    NO,    NO,    NO}}, //WP proche phare bleu
        {2700, 1900, {   NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,   YES,    NO,     0,    NO,    NO,    NO,    NO,    NO,    NO}}, //WP proche phare yellow
        { 825, 1900, {   NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,   YES,    NO,    NO,    NO,     0,    NO,    NO,    NO,    NO,    NO}}, //WP proche eceuils bleu nord
        {2175, 1900, {   NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,   YES,    NO,    NO,    NO,     0,    NO,    NO,    NO,    NO}}, //WP proche eceuils jaune nord
        { 300, 1343, {   NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,   YES,    NO,    NO,    NO,    NO,    NO,    NO,    NO,     0,    NO,    NO,    NO}}, //WP garage rob1A bleu
        { 150, 1057, {   NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,   YES,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,     0,    NO,    NO}}, //WP garage rob2A bleu
        {2700, 1057, {   NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,   YES,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,     0,    NO}}, //WP garage rob1A yellow
        {2850, 1343, {   NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,   YES,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    NO,    0 }} //WP garage rob2A yellow

    };
    Lidar lidar;
    Graph graph_orig = ATC::generate_graph(WP_COUPE, 23);
    /*
    std::cout << "Graph:" << std::endl;
    std::cout << graph_orig.wp_number << std::endl;
    std::cout << graph_orig.wp_list << std::endl;
    std::cout << graph_orig.graph << std::endl; */
    float dept[2] = {0.0, 0.0};
    float dest[2] = {3000.0, 2000.0};
    float rbpos[3] = {0.0, 0.0, 0.0}; 
    Route route = ATC::find_route(&graph_orig, dept, dest, lidar, rbpos); /*
    std::cout << "Route:" << std::endl;
    std::cout << "long=" << route.length << std::endl;
    std::cout << "start=" << route.start << std::endl;
    std::cout << "end=" << route.end << std::endl;
    std::cout << "stuck=" << route.stuck << std::endl;
    std::cout << "isfree=" << route.isfree << std::endl;
    std::cout << "isshortest=" << route.isshortest << std::endl;
    std::cout << "Points:" << std::endl;
    */
    for(int i=0;i<route.length;i++){
        //std::cout << "point " << i << ": " << (*route.wp_list[i]).x << ", " << (*route.wp_list[i]).y << std::endl;
    }
    //std::cout << "fin prog" << std::endl;
    return 0;
}
/* g++ -g pathfinding_pc_main.cpp pathfinding.cpp lidar/Lidar.cpp -o proto */