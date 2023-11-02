#ifndef SMARTBOOKING_SYSTEM_H
#define SMARTBOOKING_SYSTEM_H
#include <string>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>
#include <array>

using namespace std;

class SmartBookingSystem1: public BookingSystem{
    public:
        void generatePackages(){
        for (int i=0; i < customers.size(); i++){
            packages.push_back(Package(customers[i].cId,customers[i].budget, customers[i].hotelType, customers[i].range));
            packageCounter++;
            sort(packages.begin(),packages.end());
        }

        for (int i=0; i < customers.size(); i++){
            int flyin = customers[i].earliestGameDay();
            int flyout = customers[i].latestGameDay();

            packages[i].addFlightTicket(0,flyin);
            packages[i].addFlightTicket(1,flyout);

            flightCounter[0][flyin]++;
            flightCounter[1][flyout]++;

            double discount=0.0;
            for(int j=flyin; j < flyout; j++){
                if(customers[i].hotelType == "Regular"){
                    hotelVacancy[0][j]++;
                }else if(customers[i].hotelType == "Bronze"){
                    if(hotelVacancy[1][j] <= (0.5*20)){discount = 0.2;}
                    hotelVacancy[1][j]++;
                }else if(customers[i].hotelType == "Gold"){
                    if(hotelVacancy[2][j] <= (0.5*40)){discount = 0.4;}
                    if(hotelVacancy[2][j] <= (0.2*40)){discount = 0.2;}
                    hotelVacancy[2][j]++;
                }
                packages[i].addHotelVoucher(customers[i].hotelType, j, discount);
            }

            for(int k=0; k < NUMBEROFGAMES; k++){
                if(customers[i].games[k] == true){
                    packages[i].addGameTicket(k);
                    gameCounter[k]++;
                }
            }
        }
        }

    void printSuccessfulPackages(){
        for (int i=0; i < packages.size(); i++){
            packages[i].getPrices();
        if(packages[i].isValid(i,hotelVacancy,gameCounter)){
            cout << "\n";
            cout << "Client " << customers[i].cId << ": The package contains :" << endl;
            packages[i].printPackage();
            cout << "Total cost for the package is: $" << packages[i].getTotal() << endl;
            cout << "Customer budget is: $" << packages[i].getBudget() << endl;
                cout << "Total profit of the package is: $" << packages[i].getProfit() << endl;
                cout << "The package is valid. \n";

            systemTotal= systemTotal + packages[i].getProfit();

        }else{
                packageCounter--;
                int flyin = customers[i].earliestGameDay();
                int flyout = customers[i].latestGameDay();
                flightCounter[0][flyin]--;
                flightCounter[1][flyout]--;

                    for(int j=flyin; j < flyout; j++){
                        if(customers[i].hotelType == "Regular"){
                            hotelVacancy[0][j]--;
                        }else if(customers[i].hotelType == "Bronze"){
                            hotelVacancy[1][j]--;
                        }else if(customers[i].hotelType == "Gold"){
                            hotelVacancy[2][j]--;
                        }
                    }
                for(int k=0; k < NUMBEROFGAMES; k++){
                    if(customers[i].games[k] == true)
                        gameCounter[k]--;
                }
            }
        }
        printCounter();
    }

void readCustomerRequirements(){
    ifstream infile;
    infile.open("./TextFiles/requirementList.txt");
    if(!infile) {
		cout << "Input file does not exists. " << "Program terminates!!!"
				<< endl;
		return;
    }
    int customerID = 0;
    int budget;
    string hotel;
    int gameNum;
	bool games[NUMBEROFGAMES];
    char comma;

    while(infile >> budget){
		for (int i = 0; i < NUMBEROFGAMES; i++)
			games[i] = false;

        infile >> comma >> hotel >> comma;
        if(comma == '['){
            do{
                infile >> gameNum >> comma;
                games[gameNum] = true;
            }while(comma != ']');
        }
        customers.push_back(CustomerRequirement(customerID,budget,hotel,games));
        ++customerID;
    }
}
};
#endif