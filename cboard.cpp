//cboard.cpp
//to define functions; that in cboard.h
//author: Mingkai Lou, Kehan lv, Ruilin Wang
//date: 24/12/2020

//include header file
#include "cboard.h"


cBoard::cBoard()
{

}
//initial items function.
void cBoard::init_items()
{
//    for(int i = 0; i < 100; ++i)
//    {
//        std::cout << rand() % 3 << std::endl;
//    }
    //if the number of rows is 0 will return
    if(dt.size() == 0)//judge the number of rows 
    {
        return;
    }
    //if the number of columns in the first row is 0 will return
    if(dt[0].size() == 0)//judge the number of columns in the first row
    {
        return;
    }
    //generate items by the size of rows and columns
    for(unsigned int i = 0; i < dt.size(); ++i)//rows
    {
        for(unsigned int j = 0; j < dt[i].size(); ++j)//columns
        {

            item* nit = createItem();//call creatItem to creat items and assign to (item*) nit

            dt[i][j] = nit; 
            //std::cout << dt[i][j] << " , " ;
        }
        //std::cout << std::endl;
    }

}

//set the row size of dt. 
void cBoard::setwidth(int width)
{
    if(dt.size() > 0)
    {
        for(unsigned int i = 0; i < dt.size(); ++i)
        {
            dt[i].resize(width);//set the row size of dt. 
        }
    }
}

//set the column size of dt. 
void cBoard::setheight(int height)
{
    dt.resize(height);//set the column size of dt. 
}
//set the width of the map
int cBoard::Width()
{
    if(dt.size() == 0)
    {
        return 0;
    }
    else
    {
        return dt[0].size();
    }

}
//set the height of the map
int cBoard::Height()
{
    return dt.size();
}
//record the position of item in map
item *cBoard::itemAt(int x, int y)
{
    if(x < Width() && x >= 0 && y < Height() && y >= 0)
    {
        return dt[x][y];
    }
    return NULL;
}
//drop item to this position
bool cBoard::setItem(int x, int y, item *it)
{
    if(!itemAt(x,y))
    {
        return false;
    }
    if(itemAt(x, y)->type != 0)//type 0 empty,1 item,2 enemy
    {
        return false;
    }
    else// give input item to the current place
    {
        delete dt[x][y];
        dt[x][y] = it;
        return true;
    }
}
//Randomly generate items and enemies
item *cBoard::createItem()
{
    item* it = new item;
    it->type = rand() % 3;//type 0 empty,1 item,2 enemy
    it->subtype = rand() % 3;
    it->weight = ( it->subtype + 1 ) * 10;
    it->attack = 10 + it->subtype * 10;
    it->defense = 30 - it->subtype * 10;
    it->health = 20 + it->subtype * 10;
    it->chance = 3 + it->subtype  * 2;
    it->amount = 50 + it->subtype * 10;
    it->carrying = 0;

    if(it->type == 1 && it->subtype == 0)
    {
        it->name = "sword";
    }
    if(it->type == 1 && it->subtype == 1)
    {
        it->name = "armor";
    }
    if(it->type == 1 && it->subtype == 2)
    {
        it->name = "hat";
    }

    if(it->type == 2 && it->subtype == 0)
    {
        it->name = "typeA";
    }
    if(it->type == 2 && it->subtype == 1)
    {
        it->name = "typeB";
    }
    if(it->type == 2 && it->subtype == 2)
    {
        it->name = "typeC";
    }

    return it;
}
//when need cin a number but user enter a char, use this to deal error.
void cinerror() {
    while (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(100, '\n');
        std::cout << "You can only enter numbers." << std::endl;
    }
}