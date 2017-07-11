#include <iostream>
#include <list>
#include "Map.h"

int _mapsize=5 +2;

int main(){

    std::vector<Node*> list;

    for(int r=0;r<_mapsize;r++) {
        for (int j = 0; j < _mapsize; j++){

            if(r==0 || j==0)
                list.push_back(new Node(r* _mapsize +j, r * 10, j * 10,false));

            else if(r==_mapsize-1 || j==_mapsize-1)
                list.push_back(new Node(r* _mapsize +j, r * 10, j * 10,false));

            else
            list.push_back(new Node(r* _mapsize +j, r * 10, j * 10));  //FIXME _mapsize not magic number

    }}

    for(int r=1;r<_mapsize-1;r++) {
        for (int j = 1; j < _mapsize-1; j++){

            std::vector<Node*>& neighbour = list[r* _mapsize +j]->getParents();



            neighbour.push_back(list[(r-1)*_mapsize+j+1]);
                neighbour.push_back(list[(r-1)*_mapsize+j]);
                neighbour.push_back(list[(r-1)*_mapsize+j-1]);

            neighbour.push_back(list[(r)*_mapsize+j+1]);
            neighbour.push_back(list[(r)*_mapsize+j-1]);

            neighbour.push_back(list[(r+1)*_mapsize+j+1]);
            neighbour.push_back(list[(r+1)*_mapsize+j]);
            neighbour.push_back(list[(r+1)*_mapsize+j-1]);

        }}


    Map m;
m.findRoute(list[8],list[30]);


    std::cout<<std::endl;

    for(int r=0;r<_mapsize;r++) {
        for (int j = 0; j < _mapsize; j++) {
                std::cout<<list[r*_mapsize+j]->isWalkable() << " ";
        }
        std::cout<<std::endl;
    }

return 0;
}