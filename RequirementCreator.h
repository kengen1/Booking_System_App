#ifndef REQUIREMENT_CREATOR_H_
#define REQUIREMENT_CREATOR_H_

class RequirementCreator{
    public:
        int budget, size;
        string hotel;
        bool games[NUMBEROFGAMES];
        vector<int> gameIndex;
        vector<CustomerRequirement> requests;
        RequirementCreator() {
            for (int i = 0; i < NUMBEROFGAMES; i++) {
                games[i] = false;
            }
        }
        ~RequirementCreator() {}
        void setBudget();
        void setHotel();
        void setGames();
        void clearGames();
        bool isValid(int);
        void createCustomerBundle();
        void writeBundle();
};

void RequirementCreator::setBudget() {
    budget = 0;
    if (games[0] == true) {     //if the games include the opening ceremony, randomly generate the budget between 4500-7500
        budget = rand() % (7500 - 4500) + 4500;
    } else if (games[size - 1] == true) {       //if the games include the closing ceremony, randomly generate the budget between 3800-6800
        budget = rand() % (6800 - 3800) + 3800;
    } else {                                    //otherwise randomly generate the budget between 3250-5250
        budget = rand() % (5250 - 3250) + 3250;
    }
    budget = budget + (150 * NUMBEROFGAMES);   //universal calculation for budget for all conditions
}

void RequirementCreator::setHotel() {
    hotel = hotelIndexToTypeMap[rand() % 3];    //randomly generate int to access hotel hashmap
}

void RequirementCreator::setGames() {
    int days = rand() % 10 + 1;
    int random;

    for (int i = 0; i < days; i++) {
        do {
            random = rand() % NUMBEROFGAMES;
        } while (games[random] == true);
        games[random] = true;                   //set random instances of the bool array to true
        size++;
    }
}

void RequirementCreator::clearGames() {
    for (int i = 0; i < NUMBEROFGAMES; i++) {
        games[i] = false;
    }
}

void RequirementCreator::createCustomerBundle() {
    int numReq = rand() % 50 + 100; //randomly generate a number between 100-150
                                    //generate x number of records
    for (int i = 0; i < numReq; i++) {
        setHotel();
        setGames();
        setBudget();
        requests.push_back(CustomerRequirement(i, budget, hotel, games));
        clearGames();   //clear bool array for next iteration
    }
}

void RequirementCreator::writeBundle() {    //write to new txt file
    ofstream fout;
    fout.open("./TextFiles/generated_requests.txt");

    if (fout.fail())    {
        cout << "Output file opening failed.\n";
        exit(1);
    }

    for (int i = 0; i < requests.size(); i++) {
        fout << requests[i].budget << "," << requests[i].hotelType << "[";
        for (int j = 0; j < NUMBEROFGAMES; j++) {
            if (requests[i].games[j] == true) {
                fout << j;
                if (j < NUMBEROFGAMES - 1) {
                    fout << ",";
                }
            }
        }
        fout << "]" << endl;
    }
}

#endif