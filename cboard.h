#ifndef CBOARD_H
#define CBOARD_H

//include system header file
#include <stdlib.h>
#include <iostream>

#include <vector>

//define a struct to contain items in a square.
struct item
{
    int type; // 0 empty 1 item 2 enemy
    int subtype; // 0 1 2  item：add(attack defense chance)  enemy：number of (attack defense chance）
    std::string name; // item：sword armor hat    enemy：A B C
    int weight; //weight of item
    int attack;//the attribute of item
    int defense;//the attribute of item
    int chance;//the attribute of item
    int health;//the attribute of item
    int carrying;//the attribute of item
    int amount;//the num of item
};

//define a class to creat the map of the game
//it will creat some item by random
class cBoard
{
public:
    cBoard();//Constructor 

    //initial items function.
    void init_items();
    //set the width of the map
    void setwidth(int width);
    //set the height of the map
    void setheight(int height);

    int Width();
    int Height();

    item* itemAt(int x, int y);
    bool setItem(int x, int y, item* it);
private:
    item* createItem();
    std::vector<std::vector<item*>> dt;//define a two-dimensional array dt
};
class Orcs :public cBoard
{
private:
    int attack;         //attack
    double ChanceofAttack;     //attack chance
    int defense;     //defense
    double ChanceofDefense;//defense chance
    int health;         //health
    int strength; // the weight that role can carry
public:
    void setDay() {
        attack = 25;
        ChanceofAttack = 1.0 / 4l;
        defense = 10;
        ChanceofDefense = 1.0 / 4;
        health = 50;
        strength = 130;
    }
    void setNight() {
        attack = 45;
        ChanceofAttack = 1.0 / 1;
        defense = 25;
        ChanceofDefense = 1.0 / 2;
        health = 50;
        strength = 130;
    }

    int getAttack() {
        return attack;
    }

    double getChanceofAttack() {
        return ChanceofAttack;
    }

    int getDefense() {
        return defense;
    }

    double getChanceofDefense() {
        return ChanceofDefense;
    }

    int getHealth() {
        return health;
    }

    int getStrength() {
        return strength;
    }

};
//when need cin a number but user enter a char, use this to deal error.
void cinerror();

#endif // CBOARD_H
