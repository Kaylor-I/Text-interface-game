//main.cpp
//a fanatasy game.
//author: Mingkai Lou, Kehan lv, Ruilin Wang
//date: 24/12/2020

//include header file
#include "cboard.h"

using namespace std;

//the postion of role currently
struct pos
{
    int x;
    int y;
};

//a struct of player that contains attributes
struct player
{
    string name;
    int attack;
    int defence;
    int health;
    int chance;
    int carrying;
    int totalCarrying;
    pos position;
};
//a string array to contain name of five races
string characters[5] =
{
    "Human Sandtiger",
    "Elf Longleaf",
    "Halfling Sam",
    "Dwarf Bupu",
    "Orc Smellbad"
};

//The attributes of each race
player p[5] =
{
    {characters[0], 30, 20, 60, 2, 0, 100, {0, 0}},
    {characters[1], 40, 10, 40, 3, 0, 70, {0, 0}},
    {characters[2], 30, 20, 50, 4, 0, 130, {0, 0}},
    {characters[3], 25, 20, 70, 5, 0, 85, {0, 0}},
    {characters[4], 25, 10, 50, 6, 0, 130, {0, 0}},
};

//
Orcs orc;
//steps of a game
uint32_t step;
//the postion of a game currently
pos currentPos;
//a map of the game
cBoard board;
// the role choice of player
player currentPlayer;
//number of gold that player gets
uint32_t gold;
//one-dimensional array to put items of role get
vector<item*> carryingItems;

//print messages of current role
void printPos(pos p)
{
    //attributes of role
    cout << "Player : " << currentPlayer.name << " ; ";
    cout << "Attack = " << currentPlayer.attack << " ; ";
    cout << "Defense = " << currentPlayer.defence << " ; ";
    cout << "Health = " << currentPlayer.health << " ; ";
    cout << "Carrying " << currentPlayer.carrying << " of " << currentPlayer.totalCarrying << endl;

    item* it = board.itemAt(p.x, p.y);
    int type = it->type;
    cout << "Position[" << currentPos.x << "][" << currentPos.y << "] " ;//position coordinates
    if(type == 0)//there is no item
    {
        cout << "is empty" << endl;
    }
    if(type == 1)//there is a weapon or armor
    {
        cout << "contains item " << it->name << endl;
    }
    if(type == 2)//there is an enemy
    {
        cout << "contains enemy " << it->name << " Attack = " << it->attack
             << " Defense = " << it->defense
             << " Health = " << it->health
             << " Carrying " << it->carrying
             << " of " << it->amount
             << endl;
    }
}

//calculate the weight carrier by role
int calcWeight()
{
    if(carryingItems.empty())
    {
        return 0;
    }
    else
    {
        int sum = 0;
        for(unsigned int i = 0; i < carryingItems.size(); ++i)//add all the item carried by role
        {
            sum += carryingItems[i]->weight;
        }
        return sum;
    }
}
// the process of the game
//North, South, East, West – character moves to the square in the indicated direction
bool GameProcess()
{
    string strInput;

    cin >> strInput;

    //y position sub 1
    if(strInput == "w")
    {
        if(currentPos.y > 0)
        {
            currentPos.y--;
        }
        currentPlayer.position = currentPos;
        return true;
    }
    //y position add 1
    else if(strInput == "e")
    {
        currentPos.y++;
        //if the position beyond limit. return previously position
        if(currentPos.y >= board.Width())
        {
            currentPos.y = board.Width() - 1;
        }
        currentPlayer.position = currentPos;
        return true;
    }
    //x position sub 1
    else if(strInput == "n")
    {
        if(currentPos.x > 0)
        {
            currentPos.x--;
        }
        currentPlayer.position = currentPos;
        return true;
    }
    //y position add 1
    else if(strInput == "s")
    {
        currentPos.x++;
        //if the position beyond limit. return previously position
        if(currentPos.x >= board.Height())
        {
            currentPos.x = board.Height() - 1;
        }
        currentPlayer.position = currentPos;
        return true;
    }
    //if the pos has an enemy attack it
    else if(strInput == "a")
    {
        item* it = board.itemAt(currentPos.x, currentPos.y);
        if(it->type != 2)
        {
            return true;
        }
        //p to e

        if(it->health <= 0)
        {
            cout << "no enemy to attack" << endl;
            return true;
        }
        //judge the chance to attack successful
        if(rand() % currentPlayer.chance == 0)
        {
            it->health = it->health - currentPlayer.attack + it->defense;
            cout << "Player " << currentPlayer.name << " attacked successfully " << endl;
            if(it->health <= 0)
            {
                cout << it->name << " is dead " << endl;
                gold += it->defense; //role defeat enemy and get some gold equle to the value of enemy's defence 
            }
            else
            {

            }
        }
        else
        {
            cout << "Player " << currentPlayer.name << " attacked failed " << endl;
        }
        //enemy attack role
        if(rand() % it->chance == 0 && it->health > 0)
        {
            currentPlayer.health = currentPlayer.health - it->attack + currentPlayer.defence;
            if(currentPlayer.health > 0)
            {
                cout << "enemy " << it->name << " attacked successfully " << endl;
            }
            else
            {
                cout << currentPlayer.name << " is dead " << endl;
                exit(0);
            }
        }
        else
        {
            cout << "enemy " << it->name << " attacked failed " << endl;
            gold += it->defense; //role defeat enemy and get some gold equle to the value of enemy's defence 
        }

        return true;
    }
    //drop item to local place
    //
    else if(strInput == "d")
    {
        if(carryingItems.empty())
        {
            cout << "nothing to drop!" << endl;
        }
        else
        {
            if(board.itemAt(currentPlayer.position.x, currentPlayer.position.y)->type == 0)
            {
                board.setItem(currentPlayer.position.x, currentPlayer.position.y, carryingItems[0]);
                carryingItems.erase(carryingItems.begin());
                cout << "carrying item " << carryingItems[0]->name << " was dropped " << endl;
            }
            else
            {
                cout << "this position is not empty, drop failed!" << endl;
            }
        }

        return true;
    }
    //pick item from currently place
    else if(strInput == "p")
    {
        if(board.itemAt(currentPlayer.position.x, currentPlayer.position.y)->type == 1)
        {
            currentPlayer.carrying = calcWeight();
            if(board.itemAt(currentPlayer.position.x, currentPlayer.position.y)->weight
                    + currentPlayer.carrying
                    > currentPlayer.totalCarrying)
            {
                cout << "over weight, can not pick" << endl;
            }
            else
            {
                carryingItems.push_back(board.itemAt(currentPlayer.position.x, currentPlayer.position.y));
                currentPlayer.carrying += board.itemAt(currentPlayer.position.x, currentPlayer.position.y)->weight;
                item* it = new item;
                it->type = 0;
                board.setItem(currentPlayer.position.x, currentPlayer.position.y, it);
                cout << currentPlayer.name << " picked up " << carryingItems.back()->name << endl;
            }
        }
        else if(board.itemAt(currentPlayer.position.x, currentPlayer.position.y)->type == 0)
        {
            cout << "nothing to pick" << endl;
        }
        else if(board.itemAt(currentPlayer.position.x, currentPlayer.position.y)->type == 2)
        {
            cout << "can not carry enemy" << endl;
        }


        return true;
    }
    //look message of the current place. return to process to get the message
    else if(strInput == "l")
    {

        return true;
    }
    //show the gold carries by role
    else if(strInput == "i")
    {
        cout << currentPlayer.name << " is carrying " << gold << " gold" << endl;

        if(!carryingItems.empty())
        {
            for(unsigned int i = 0; i < carryingItems.size(); ++i)
            {
                cout << carryingItems[i]->name << " , weight " << carryingItems[i]->weight << endl;
            }
        }

        return true;
    }
    //exit the system
    else if(strInput == "x")
    {
        return false;
    }
    else
    {
        return true;
    }

}



//the main function of the system
int main(int argc, char *argv[])
{
  //intial gold and step
    gold = 0;
    step = 0;
    //set the broad og the map
    board.setheight(200);
    board.setwidth(200);
    board.init_items();

    //let player to choose a role
    cout << "Please chose your character:" << endl;

    for(unsigned int i = 0; i < 5; ++i)
    {
        cout << "(" << i + 1 << ")" << characters[i] << endl;
    }

    cout << "Please enter 1 - 5 : " ;

    int NumCh;
    //player input choice
    cin >> NumCh;
    cinerror();
    while(NumCh < 1 || NumCh > 5)
    {
        cout << "Wrong Number, please input again :" << endl;
        cin >> NumCh;
    }

    currentPlayer = p[NumCh - 1];

    currentPos = {0, 0};

    cout << "Player : " << currentPlayer.name << " ; ";
    cout << "Attack = " << currentPlayer.attack << " ; ";
    cout << "Defense = " << currentPlayer.defence << " ; ";
    cout << "Health = " << currentPlayer.health << " ; ";
    cout << "Carrying " << currentPlayer.carrying << " of " << currentPlayer.totalCarrying << endl;

    //make a circle of the main function, let role to choose its command
    while(1)
    {
        cout << "please choose direction N,S,E,W or" << endl;
        cout << "command (A)ttack, (P)ickup, (D)rop, (L)ook, (I)nventory or e(X)it:";

        //if false end of the game; if true continue game
        if(!GameProcess())
        {
            cout << "Press any key to Exit ! ";
            exit(0);
        }
        else
        {
            cout << endl;
            printPos(currentPos);
        }


        step++;

        int numdaylight = step % 10;

        if (numdaylight >= 0 && numdaylight < 5)//the first five step is daytime
        {
            if (currentPlayer.name == "Orc Smellbad") {
                orc.setDay();
                currentPlayer.attack = orc.getAttack();
                currentPlayer.defence = orc.getDefense();
                currentPlayer.health = orc.getHealth();
            }
            cout << "daytime(" << step << ")" << endl;
        }
        //the last five step is nightime
        else//否则兽人进入黑夜
        {
            if (currentPlayer.name == "Orc Smellbad") {
                orc.setNight();
                currentPlayer.attack = orc.getAttack();
                currentPlayer.defence = orc.getDefense();
                currentPlayer.health = orc.getHealth();
            }
            cout << "nightime(" << step << ")" << endl;
        }
        cout << endl;
        printPos(currentPos);
    }

   // return a.exec();
    return EXIT_SUCCESS;
}


/*
Please chose your character:
(1) Human Sandtiger
(2) Elf Longleaf
(3) Halfling Sam
(4) Dwarf Bupu
(5) Orc Smellbad
Please enter 1-5:

*/
