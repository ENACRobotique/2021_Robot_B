#include "pathfinding.h"
#include "lidar/Lidar.h"

int main(){
    Waypoint list_wp[4]={
        { 200,  200, {   0, 1600, 2600,   NO}}, 
        { 200, 1800, {1600,    0,   NO, 2600}}, 
        {2800,  200, {2600,   NO,    0, 1600}}, 
        {2800, 1800, {  NO, 2600, 1600,    0}}
    }; 
    return 0;
}