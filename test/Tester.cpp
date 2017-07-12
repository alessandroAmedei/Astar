//
// Created by ale on 12/07/17.
//


#include <gtest/gtest.h>
#include "../Node.h"
#include "../Map.h"
#include <SFML/Graphics.hpp>

TEST(Node, DefaultCostructor){
    Node n(3,2,2);
    ASSERT_EQ(n.getId(),3);
}

TEST(Map, DefaultCostructor){
    Map m(50);
    m.findRoute(new Node(1,1,1),new Node(2,2,2));
}
