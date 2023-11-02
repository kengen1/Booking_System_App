
#ifndef CLIENTREQUEST_H_
#define CLIENTREQUEST_H_

#include "Constants.h"
#include <bits/stdc++.h>

class CustomerRequirement {
public:
	int cId;
	string hotelType;
	bool games[NUMBEROFGAMES];
	int budget;
	int range;
	int arrival;
	int departure;
	int trueCounter=0;

	CustomerRequirement() {
		cId = -1;
		hotelType = "";
		budget = -1;
		for (int i = 0; i < NUMBEROFGAMES; i++)
			games[i] = false;
	}

	CustomerRequirement(int customerID, int bud, string hotel, bool game[]){
		cId = customerID;
		budget = bud;
		hotelType = hotel;
		for (int i=0; i < NUMBEROFGAMES; i++){
			games[i] = game[i];
			if(games[i] == true){
				trueCounter++;
			}
		}
		arrival = earliestGameDay();
		departure = latestGameDay();
		range = departure - arrival;
	}

	int earliestGameDay() {
		int flyin = 9;
		for (int i = 0; i < NUMBEROFGAMES; i++) {
			if (games[i] && gameDayMap[i] < flyin)
				flyin = gameDayMap[i];
		}
		return flyin;
	}

	int latestGameDay() {
		int flyout = 0;
		for (int i = 0; i < NUMBEROFGAMES; i++) {
			if (games[i] && gameDayMap[i] > flyout)
				flyout = gameDayMap[i];
		}
		return flyout;
	}

	void print() {
	cout << setw(8) << cId << ":" << setw(8) << budget << setw(8)
				<< hotelType << setw(8);

		for (int i = 0; i < NUMBEROFGAMES; i++) {
			if (games[i]) {
				cout << i;
				if (i < NUMBEROFGAMES - 1)
					cout << setw(4);
			}
		}

    cout << endl;
	}
};

#endif /* CLIENTREQUEST_H_ */
