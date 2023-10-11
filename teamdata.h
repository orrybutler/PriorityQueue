#ifndef _TEAMDATA_H_
#define _TEAMDATA_H_

#include <string>
#include <vector>
#include <iostream>
#include "json.hpp"
using namespace std;

// class TeamData {
//  public:
// 	TeamData(int num_players) {
// 		numPlayers_ = num_players; 
// 		//vector<vector<double>> winPercentages_ = new vector<vector<double>>;
// 	}
// 	void insert(int i, int j, double winPercentage) {
// 		cout << "Fuck seg Fualts" << endl;
// 		winPercentages_[i][j] = winPercentage;
// 	};
// 	void delete_i(int i) {
// 		winPercentages_.erase(winPercentages_.begin() + i);
// 	};
// 	//void delete_j(int j) {
// 		//for (int i = 0; i < numPlayers_; i++) {
// 			//winPercentages_[i].erase(winPercentages_[i].begin() + j);
// 		//}
// 	//};
//  	int numPlayers(int num_players){
// 		numPlayers_ = num_players;
// 	} ;
//  	//double winPercentages(int i, int j) const { return winPercentages_[i][j]; }

//  private:
// 	// TODO: decide the type of this variable.
// 	int numPlayers_;

// 	//vector<vector<double>> winPercentages_;

// };  // class TeamData

#endif  // _TEAMDATA_H_