//Grant Novota
#include "HashTable.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include<vector>

using namespace std;

HashTable::HashTable() //all counters are initialized to 0
{
    openAddressingCollisionCounter = 0;
    chainingCollisionCounter = 0;
    openAddressingSearchCounter = 0;
    chainingSearchCounter = 0;
    uniquePlayerCounter = 0;
}

void HashTable::initTables(int in_size) //builds empty tables
{
    tableSize = in_size;
    for(int i = 0; i < in_size; i++)
    {
        PlayerNode *Nil = new PlayerNode; //fills the tables with empty Player Nodes
        chainTable.push_back(Nil);
        PlayerNode *Nil2 = new PlayerNode;
        openAddTable.push_back(Nil2);
    }
}

int HashTable::hashSum(string key) //hash sum from lecture
{
    int sum = 0;
    for(int i=0; i < key.length(); i++)
        sum = sum + key[i];
    sum = sum % tableSize;
    return sum;
}


/*int HashTable::hashSum(string key) //hash sum posted on piazza
{
    const char* str = key.c_str();
    int hash = 1;
    while(*str) hash = hash * 101 + *str++;
    return hash % tableSize;
}
*/

void HashTable::addToTables(int yearID, string teamID, string leagueID, string playerID, int salary, string firstName, string lastName, int birthYear, string birthCountry, int weight, int height, string bats, string throws)
{
    PlayerNode *newPlayer = new PlayerNode(yearID, teamID, leagueID, playerID, salary, firstName, lastName, birthYear, birthCountry, weight, height, bats, throws);
    PlayerNode *newPlayer2 = new PlayerNode(yearID, teamID, leagueID, playerID, salary, firstName, lastName, birthYear, birthCountry, weight, height, bats, throws);
    addToChainTable(newPlayer);
    addToOpenAddTable(newPlayer2);
}

void HashTable::addToChainTable(PlayerNode *newPlayer)
{
    int index = hashSum(newPlayer->key);
    if(chainTable[index]->next == NULL) //if spot is empty, place node there
    {
        chainTable[index]->next = newPlayer;
        newPlayer->prev = chainTable[index];
        uniquePlayerCounter++;
    }
    else
    {
        chainingCollisionCounter++;
        PlayerNode *tmp = chainTable[index]->next;
        while(tmp != NULL) //traverse through the chain at that index until existing player is found or until end of chain is reached
        {
            chainingSearchCounter++;
            if(tmp->playerID == newPlayer->playerID && tmp->key == newPlayer->key && tmp->birthCountry == newPlayer->birthCountry)
            {
                chainingCollisionCounter--;
                tmp->yearIDVector.push_back(newPlayer->yearIDVector[0]);
                tmp->teamIDVector.push_back(newPlayer->teamIDVector[0]);
                tmp->leagueIDVector.push_back(newPlayer->leagueIDVector[0]);
                tmp->salaryVector.push_back(newPlayer->salaryVector[0]);
                delete newPlayer; //since a new node is not being put into the table it is deleted after the previous node is updated with new info
                return;
            }
            tmp = tmp->next;
        }
        tmp = chainTable[index]->next; //reset pointer
        while(tmp->next != NULL)
        {
            //chainingSearchCounter++;
            tmp = tmp->next; //traverse through till the end of chain
        }
        tmp->next = newPlayer; //add new player to end of chain
        newPlayer->prev = tmp;
        uniquePlayerCounter++;
    }
}

void HashTable::addToOpenAddTable(PlayerNode *newPlayer)
{
    int index = hashSum(newPlayer->key);
    if(openAddTable[index]->next == NULL) //if the spot is not filled, add to that spot
    {
        openAddTable[index]->next = newPlayer;
        newPlayer->prev = openAddTable[index];
        //uniquePlayerCounter++;
    }
    else
    {
        openAddressingCollisionCounter++;
        for(int x=0; x < openAddTable.size(); x++) //see if the player already exists in table
        {
            if(openAddTable[x]->next != NULL)
            {
                if(openAddTable[x]->next->playerID == newPlayer->playerID && openAddTable[x]->next->key == newPlayer->key && openAddTable[x]->next->birthCountry == newPlayer->birthCountry)
                {
                    openAddressingCollisionCounter--;
                    openAddTable[x]->next->yearIDVector.push_back(newPlayer->yearIDVector[0]);
                    openAddTable[x]->next->teamIDVector.push_back(newPlayer->teamIDVector[0]);
                    openAddTable[x]->next->leagueIDVector.push_back(newPlayer->leagueIDVector[0]);
                    openAddTable[x]->next->salaryVector.push_back(newPlayer->salaryVector[0]);
                    delete newPlayer; //since a new node is not being put into the table it is deleted after the previous node is updated with new info
                    return;
                }
            }
        }
        for(int y=0; y < openAddTable.size(); y++) //start at 0 and traverse table until open spot is found
        {
            openAddressingSearchCounter++;
            if(openAddTable[y]->next == NULL)
            {
                openAddTable[y]->next = newPlayer;
                newPlayer->prev = openAddTable[y];
                //uniquePlayerCounter++;
                return;
            }
        }
    }
}

int HashTable::getOpenAddressingCollisions()
{
    return openAddressingCollisionCounter;
}

int HashTable::getChainingCollisions()
{
    return chainingCollisionCounter;
}

int HashTable::getOpenAddressingSearches()
{
    return openAddressingSearchCounter;
}

int HashTable::getChainingSearches()
{
    return chainingSearchCounter;
}

int HashTable::getUniquePlayers()
{
    return uniquePlayerCounter;
}

void HashTable::findAndDisplayPlayer(string key)
{
    int cSearchCount = 0;
    int oSearchCount = 0;
    int index = hashSum(key);
    bool playerFound = false;

    if(openAddTable[index]->next->key != key) //check if player is stored at the hash sum index
    {
        for(int x=0; x<openAddTable.size(); x++) //traverse through table to find player
        {
            oSearchCount++;
            if(openAddTable[x]->next->key == key)
                break;
        }
    }
    PlayerNode *curr = chainTable[index]->next;
    while(curr != NULL) //traverse through chain to find player
    {
        if(curr->key == key)
        {
            cout << "Search operations using chaining: " << cSearchCount << endl;
            cout << "Search operations using open addressing: " << oSearchCount << endl << endl;
            cout << "Player: " << curr->firstName << " " << curr->lastName << endl;
            cout << "Player ID: " << curr->playerID << endl;
            cout << "Birth Year: " << curr->birthYear << " Country: " << curr->birthCountry << endl;
            cout << "Height: " << curr->height << " Weight: " << curr->weight << endl;
            cout << "Bats: " << curr->bats << " Throws: " << curr->throws << endl;
            cout << "Teams and Salary:" << endl;
            for(int i=0; i < curr->yearIDVector.size(); i++)
            {
                cout << curr->yearIDVector[i] << ", " << curr->leagueIDVector[i] << ", " << curr->teamIDVector[i] << ", $" << curr->salaryVector[i] << endl;
            }
            cout << endl;
            playerFound = true;
        }
        cSearchCount++;
        curr = curr->next;
    }
    if(playerFound == false)
        cout << "Player not found." << endl;
}

HashTable::~HashTable()
{
    //dtor
}
