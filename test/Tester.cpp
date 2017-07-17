//
// Created by ale on 12/07/17.
//


#include <gtest/gtest.h>
#include "../Node.h"
#include "../Map.h"
#include <SFML/Graphics.hpp>
#include <./SFML/Graphics.hpp>

TEST(Node, DefaultCostructor) {
    Node n(3, 5, 2);

    Node n2(3, 6, 6);
    Node n3(5, 4, 3);
    Node n4(1, 8, 7);

    std::vector<Node *> neighbours;
    neighbours.push_back(&n2);
    neighbours.push_back(&n3);
    neighbours.push_back(&n4);

    n.setParents(neighbours);

    ASSERT_EQ(n.getId(), 3);
    ASSERT_EQ(n.getParents()[0]->getId(), 3);

    ASSERT_EQ(n.getX(), 5);

    std::cout << "cc";
}

TEST(Map, DefaultCostructor) {
    Map m(50);

    Node n1(1, 100, 100, true, false);
    Node n2(2, 100, 100, true, false);
    Node n3(3, 100, 100, true, false);

    std::vector<Node *> a{&n2};
    std::vector<Node *> b{&n3};

    n1.setParents(a);

    n2.setParents(b);

    ASSERT_TRUE(m.findRoute(&n1, &n2));
    ASSERT_TRUE(m.findRoute(&n2, &n3));
    ASSERT_FALSE(m.findRoute(&n3, &n1));

}
