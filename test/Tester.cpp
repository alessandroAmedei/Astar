//
// Created by ale on 12/07/17.
//


#include <gtest/gtest.h>
#include "../Node.h"
#include "../Map.h"
#include <SFML/Graphics.hpp>

TEST(Node, DefaultCostructor){
    Node n(3,5,2);

    Node n2(3,6,6);
    Node n3(5,4,3);
    Node n4(1,8,7);

    std::vector<Node*> neighbours;
    neighbours.push_back(&n2);
    neighbours.push_back(&n3);
    neighbours.push_back(&n4);

    n.setParents(neighbours);

    ASSERT_EQ(n.getId(),3);
    ASSERT_EQ(n.getParents()[0]->getId(),3);

    ASSERT_EQ(n.getX(),5);

    std::cout<<"cc";
}

TEST(Map, DefaultCostructor){
   Map m(50);
}
