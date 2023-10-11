#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include "priorityqueue.h"
#include "json.hpp"

using namespace std;

int main(int argc, char** argv) {
    nlohmann::json json_output; // declare a json object json output
    nlohmann::json input_json; // declare a json object json input
    ifstream json_file; // declare a vaiable for an input file to read in the json file

    if (argc != 2) { // check if argc is not equal to 2
        cerr << "Usage ./buildheap.exe [file1.json]" << endl; // output correct usage of the program
        exit(1); // exit if correct usage is not followed
    }

    if (!json_file) {
        cerr << "Error: cannot open file " << argv[1] << endl; // file doesn't exist
        exit(1); // exit if file was not opened
    }

    json_file.open(argv[1]); // open the json file

    if (json_file) { // check if the json file is open
        json_file >> input_json; // read the json file into the input json object
    }
    
    size_t maxHeapSize = input_json["metadata"]["maxHeapSize"]; // declare a variable of type size_t maxHeapSize and set equal to the max heap size
    int numOperations = input_json["metadata"]["numOperations"]; // declare a variable numOperations and set equal to the number of operations

    nlohmann::json::iterator iterator1; // declare an iterator to iterate through the json object

    int i = 0; // set a variable i equal to zero
    string operation = ""; // declare a string operation and set it empty
    int player_key; // declare a variable player_key to store the key of each player


    PriorityQueue json_PQ = PriorityQueue(maxHeapSize); // declare a priority queue object with size of the maxHeapSize

    for (iterator1 = input_json.begin(); i < numOperations; ++iterator1, i++) { // iterate through each of the operations in the input json
        operation = input_json[iterator1.key()]["operation"]; // set operation equal to the operation listed in the json file
        if (operation == "insert"){ // check if operation is equal to insert
            player_key = input_json[iterator1.key()]["key"]; // set player key equal to the key of the player that is being inserted
            json_PQ.insert(player_key); // insert player key into the priority queue object
        } 
        if (operation == "removeMin") { // check if operation is equal to removeMin
            json_PQ.removeMin(); // remove the minimum key of the priority queue
        }
    }
    json_output = json_PQ.JSON(); // set json_ouput equal to the locations and keys of the priority queue
    json_output["metadata"]["maxHeapSize"] = maxHeapSize; // set maxHeapSize in the json ouput equal to the max heap size
    json_output["metadata"]["numOperations"] = numOperations; // set num operations in the json output equal to the number of operations
    cout << json_output.dump(2) << endl; // output the json output in a readable format
}

