#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <iterator>
#include "json.hpp"
#include "priorityqueue.h"
#include "teamdata.h"

using namespace std;

int main(int argc, char** argv) {
    nlohmann::json json_input; // make an object for the input json
    nlohmann::json json_output; // make a json object for the output
    nlohmann::json team_data_json; // declare a json object for the data of single combos of players

    ifstream json_file; // create an in file stream to take in the json file
    json_file.open(argv[1]); // open the json file

    nlohmann::json::iterator iterator1; // declare an iterator for the json file
    nlohmann::json::iterator iterator2; // declare a second iterator for the second json file

    if (argc != 2) { // check if argc is not equal to 2
        cerr << "Usage ./createteams.exe [file1.json]" << endl; // output correct usage of the program
        exit(1); // exit if correct usage is not followed
    }

    if (!json_file) { // check if the json file has been opened
        cerr << "Error: cannot open file " << argv[1] << endl; // file doesn't exist
        exit(1); //exit the program if no file is opened
    }

    if(json_file){ // check if json file is opened
        json_file >> json_input; // read json file into json input object
    }

    int num_players = json_input["metadata"]["numPlayers"]; // declare variable number of players
    int number_of_possible_teams = (num_players * (num_players - 1))/2; // declare variable with the number of possible teams.
    vector<vector<int>> made_teams; // declare a vector of vectors which hold the teams that have been made with the gready algorithm
    vector<int> single_team; // declare a vector of ints which holds the singular teams the gready algoirthm makes
    int teams_needed = num_players/2; // declare a variable teams needed which is initalized to num players divided by 2
    int teams_chosen = 0; // declare a variable for teams chose and intialize the variable to zero
    double win_percentage; // declare variable win_percentage to store the win percentage of each team
    double win_percentage_difference; // declare a variable win percnetage difference which will store the difference between 50 and the win percentage of each team
    KeyValuePair lowest_win_diff; // declare a KeyValuePair which will store the lowest win difference of a set of players
    double** team_matrix = new double*[num_players]; // declare a pointer to an array of size num players of type double
    for (int i = 0; i < num_players; i++) { // iterate through the array
        team_matrix[i] = new double[num_players]; // in each row of the array intial a pointer to a new array in each row creating a matrix where rows are player one for a team and columns are player two
    }
    for (int i = 0; i < num_players; i++) { // iterate throught the rows of the array
        for (int j = 0; j < num_players; j++) { // iterate through the columns of the array
            team_matrix[i][j] = 0; // fill the matrix with value zero
        }
    }
    int player_one; // declare a variable player one
    int player_two; //declare a variable player two

    PriorityQueue team_data = PriorityQueue(number_of_possible_teams); // initialize a priority queue of size 1000

    for (iterator1 = json_input.begin(); iterator1 != json_input.end(); ++iterator1) {// iterate through the first level of the json object
        if (iterator1.key() == "teamStats") {// check if iterator1's key is equal to teamStats
            int j = 1; // set a new variable j equal to 1
            for (iterator2 = json_input[iterator1.key()].begin(); j <= number_of_possible_teams; j++, ++iterator2){ // iterate through what is in the json object at key teamStats
                team_data_json = iterator2.value(); // set team_data_json equal to the value of iterator2 which will give us a json object for each team
                win_percentage = team_data_json["winPercentage"]; // get the win percentage of the team store this value to a variable win_percentage
                player_one = team_data_json["playerOne"]; // get the first player from the team data json
                player_two = team_data_json["playerTwo"]; // get the second player from the team data json
                win_percentage_difference = abs(50 - win_percentage); // set win percentage difference equal to the absolute value of difference between 50 and the win percentage
                team_data.insert(win_percentage_difference); // insert the win percentage difference of each team into 
                team_matrix[player_one][player_two] = win_percentage_difference; // place the win percentage difference of team with players at it's location in the matrix
            }
        }
    }
    while (!team_data.isEmpty()) { // iterate while the priority queue is not empty
        if (teams_chosen == teams_needed) { // check if teams needed is equal to the teams chose
            break; // break out of program if teams chosen if equal to teams needed
        } 
        lowest_win_diff = team_data.removeMin(); // set the lowest win diff equal to the highest priority element in the priority queue
        for (int i = 0; i < num_players; i++) { // iterate throguht the rows of the matrix
            for(int j = 0; j < num_players; j++) { // iterate through the columns of the matrix
                if (lowest_win_diff.first == team_matrix[i][j]) { // check if the key of the key value pair lowest win diff is equal to the matrix of teams at i, j
                    for (int k = 0; k < num_players; k++) { // iterate using k for the number of players
                        team_matrix[i][k] = -1; // set the colums of the player one equal to -1 in the matrix
                        team_matrix[k][j] = -1; // set the rows of the player two equal to -1 in the matrix
                        team_matrix[k][i] = -1; // set the rows of the player one equal to -1 in the matrix
                        team_matrix[j][k] = -1; // set the colums of the player two equal to -1 in the matrix
                    }
                    single_team.push_back(i); // place the first player into the single team vector
                    single_team.push_back(j); // place the second player into the single team vector and we have a full two player team
                    made_teams.push_back(single_team); // put the single team into a vector of finsihed teams
                    single_team.clear(); // clear out the single team vector in order to reset it
                    teams_chosen++; // add 1 to the chose teams
                }
            }
        }
    
    }
    json_output["teams"] = made_teams; // place the vector made teams into the teams object of the json output object
    cout << json_output.dump(2) << endl; // output the output json to the console
}


