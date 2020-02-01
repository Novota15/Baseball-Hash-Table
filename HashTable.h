//Grant Novota
#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include<vector>

using namespace std;

struct PlayerNode //for storing each player's data
{
    string key;
    vector<int> yearIDVector;
    vector<string> teamIDVector;
    vector<string> leagueIDVector;
    string playerID;
    vector<int> salaryVector;
    string firstName;
    string lastName;
    int birthYear;
    string birthCountry;
    int weight;
    int height;
    string bats;
    string throws;

    PlayerNode *prev;
    PlayerNode *next;

    PlayerNode(){};

    PlayerNode(int in_yearID, string in_teamID, string in_leagueID, string in_playerID, int in_salary, string in_firstName, string in_lastName, int in_birthYear, string in_birthCountry, int in_weight, int in_height, string in_bats, string in_throws)
    {
        key = (in_firstName + in_lastName);
        yearIDVector.push_back(in_yearID);
        teamIDVector.push_back(in_teamID);
        leagueIDVector.push_back(in_leagueID);
        playerID = in_playerID;
        salaryVector.push_back(in_salary);
        firstName = in_firstName;
        lastName = in_lastName;
        birthYear = in_birthYear;
        birthCountry = in_birthCountry;
        weight = in_weight;
        height = in_height;
        bats = in_bats;
        throws = in_throws;

        prev = NULL;
        next = NULL;
    }
};

class HashTable
{
    public:
        HashTable();
        virtual ~HashTable();
        void addToTables(int, string, string, string, int, string, string, int, string, int, int, string, string);
        int getOpenAddressingCollisions();
        int getChainingCollisions();
        int getOpenAddressingSearches();
        int getChainingSearches();
        void initTables(int);
        int getUniquePlayers();
        void findAndDisplayPlayer(string);

    protected:

    private:
        int hashSum(string);
        int tableSize;
        int openAddressingCollisionCounter;
        int chainingCollisionCounter;
        int openAddressingSearchCounter;
        int chainingSearchCounter;
        void addToChainTable(PlayerNode*);
        void addToOpenAddTable(PlayerNode*);
        vector<PlayerNode*> chainTable;
        vector<PlayerNode*> openAddTable;
        //PlayerNode *Nil = new PlayerNode;
        int uniquePlayerCounter;
};

#endif // HASHTABLE_H
