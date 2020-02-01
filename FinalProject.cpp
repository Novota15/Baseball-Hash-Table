// Grant Novota
// Final Project
// Hoenigman

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include "HashTable.h"

using namespace std;

HashTable ht;

int printMenu() //main menu
{
    int input;
    cout << "======Main Menu======" << endl;
    cout << "1. Query hash table" << endl;
    cout << "2. Quit program" << endl;
    cin >> input;
    return input;
}

void queryMenu() //for searching for players
{
    string firstName;
    string lastName;
    cout << "Enter Player's first name: " << endl;
    cin.ignore();
    getline(cin, firstName);
    cout << "Enter Player's last name: " << endl;
    getline(cin, lastName);
    string key = (firstName + lastName);
    cout << endl;
    ht.findAndDisplayPlayer(key);
    cout << endl;
}

void readFile(string filename)
{
    ifstream fs;
    string line;
    fs.open(filename);
    if(!fs)
    {
        cout << "Could not open file" << endl;
    }
    else
    {
        string data[13];
        int index = 0;
        while(getline(fs, line))
        {
            istringstream ss(line);
            string token;
            while(getline(ss, token, ',')) //adds each player's data to the table
            {
                if(index == 13) //there are 13 pieces of data for each player
                {
                    istringstream buffer(data[0]);
                    int yearID;
                    buffer >> yearID; //converting string to int
                    string teamID = data[1];
                    string leagueID = data[2];
                    string playerID = data[3];
                    istringstream buffer2(data[4]);
                    int salary;
                    buffer2 >> salary;
                    string firstName = data[5];
                    string lastName = data[6];
                    istringstream buffer3(data[7]);
                    int birthYear;
                    buffer3 >> birthYear;
                    string birthCountry = data[8];
                    istringstream buffer4(data[9]);
                    int weight;
                    buffer4 >> weight;
                    istringstream buffer5(data[10]);
                    int height;
                    buffer5 >> height;
                    string bats = data[11];
                    string throws = data[12];

                    ht.addToTables(yearID, teamID, leagueID, playerID, salary, firstName, lastName, birthYear, birthCountry, weight, height, bats, throws);
                    index = 0;
                }
                data[index] = token;
                index++;
            }
        } //now to add the final player
        istringstream buffer(data[0]);
        int yearID;
        buffer >> yearID;
        string teamID = data[1];
        string leagueID = data[2];
        string playerID = data[3];
        istringstream buffer2(data[4]);
        int salary;
        buffer2 >> salary;
        string firstName = data[5];
        string lastName = data[6];
        istringstream buffer3(data[7]);
        int birthYear;
        buffer3 >> birthYear;
        string birthCountry = data[8];
        istringstream buffer4(data[9]);
        int weight;
        buffer4 >> weight;
        istringstream buffer5(data[10]);
        int height;
        buffer5 >> height;
        string bats = data[11];
        string throws = data[12];

        ht.addToTables(yearID, teamID, leagueID, playerID, salary, firstName, lastName, birthYear, birthCountry, weight, height, bats, throws);
    }
}

int main(int argc, char *argv[])
{
    string filename = argv[1]; //filename is first argument
    istringstream convert(argv[2]); //table size is second argument
    int tableSize;
    convert >> tableSize;

    ht.initTables(tableSize);
    readFile(filename);

    cout << endl;
    cout << "Hash table size: " << tableSize << endl;
    cout << "Collisions using open addressing: " << ht.getOpenAddressingCollisions() << endl;
    cout << "Collisions using chaining: " << ht.getChainingCollisions() << endl;
    cout << "Search operations using open addressing: " << ht.getOpenAddressingSearches() << endl;
    cout << "Search operations using chaining: " << ht.getChainingSearches() << endl;
    cout << "Number of unique players: " << ht.getUniquePlayers() << endl;
    cout << endl;

    int input = printMenu();
    while(input)
    {
        if(input == 1)
        {
            queryMenu();
        }
        else if(input == 2)
        {
            cout << "Goodbye!" << endl;
            break;
        }
        input = printMenu();
    }
    return 0;
}
