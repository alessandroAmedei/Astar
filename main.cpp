#include <iostream>
#include "Map.h"

int main(){

    Map m;
    std::vector<Node*> v1;
    std::vector<Node*> v2;
    std::vector<Node*> v3;
    std::vector<Node*> v4;
    std::vector<Node*> vx;
    Node n1(1,0,0);
    Node n2(2,10,10,false);
    Node nx(100,10,100);
    Node n3(3,20,20);
    Node n4(4,30,30);

    v1.push_back(&n2);
    v1.push_back(&nx);
    vx.push_back(&n1);
    vx.push_back(&n3);
    vx.push_back(&n2);
    v2.push_back(&n3);
    v2.push_back(&n1);
    v2.push_back(&nx);
    v3.push_back(&n4);
    v3.push_back(&nx);
    v3.push_back(&n2);

    v4.push_back(&n3);

    n1.setParents(v1);
    n2.setParents(v2);
    n3.setParents(v3);
    n4.setParents(v4);
    nx.setParents(vx);

    std::cout<<"INIZIO TEST 1";

    m.findRoute(&n1,&n4);

    std::cout<<"FINE TEST 1";





}