#ifndef BOOKING_SYSTEM_H
#define BOOKING_SYSTEM_H
#include <string>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>
#include <array>

#include "Constants.h"
#include "CustomerRequirement.h"
#include "Ticket.h"
#include "FlightTicket.h"
#include "HotelVoucher.h"
#include "GameTicket.h"
#include "Package.h"

using namespace std;


class BookingSystem {
protected:
    vector <CustomerRequirement> customers;
    vector <Package> packages;
    int customerID = 0;
    int budget;
    string hotel;
    int gameNum;
    bool games[NUMBEROFGAMES];
    char comma;
    int systemTotal =0;

    int flightCounter[2][NUMBEROFDAYS];
    int hotelVacancy[3][NUMBEROFDAYS-1];
    int gameCounter[NUMBEROFGAMES];
    int packageCounter;

public:
    BookingSystem(){
        packageCounter=0;
        for(int i=0; i<2; i++){
            for(int j=0; j<NUMBEROFDAYS; j++)
                flightCounter[i][j]=0;
        }
        for(int i=0; i<3; i++){
            for(int j=0; j<NUMBEROFDAYS-1; j++)
                hotelVacancy[i][j]=0;
        }
        for(int i=0; i<NUMBEROFGAMES; i++){
            gameCounter[i]=0;
        }
    }

    void saveData();
    void printData();
    void readCustomerRequirements();
    void generatePackages(){
        for (int i=0; i < customers.size(); i++){
            packages.push_back(Package(customers[i].cId,customers[i].budget, customers[i].hotelType, customers[i].range));
            packageCounter++;
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

    void printCounter(){
        cout << "\nSummary of packages: \n";
        cout << "Total packages generated: " << packageCounter << endl;
        cout << "\nTotal fly-in tickets (to New York) for each day booked: \n";
        for(int j=0; j<NUMBEROFDAYS; j++){
            cout << flightCounter[0][j] << setw(4);
        }
        cout << "\nTotal fly-out tickets (to Sydney) for each day booked: \n";
        for(int i=0; i<NUMBEROFDAYS; i++){
            cout << flightCounter[1][i] << setw(4);
        }
        cout << endl;
        cout << "\nTotal hotel vouchers for each day sold: ";
        cout << "\nRegular hotel rooms\n";
        for(int i=0; i<NUMBEROFDAYS-1; i++){
            cout << hotelVacancy[0][i] << setw(4);
        }
        cout << "\nBronze hotel rooms\n";
        for(int i=0; i<NUMBEROFDAYS-1; i++){
            cout << hotelVacancy[1][i] << setw(4);
        }
        cout << "\nGold hotel rooms\n";
        for(int i=0; i<NUMBEROFDAYS-1; i++){
            cout << hotelVacancy[2][i] << setw(4);
        } cout << endl;

        cout << "\nTotal event tickets for each event sold: \n";
        for(int i=0; i < NUMBEROFGAMES; i++){
            cout << gameCounter[i] << setw(4);
        } cout << endl;

        cout << "Total Profit: $" << systemTotal << endl;

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

    void printUnsuccessfulPackages(){
           ofstream outFile;
            outFile.open("./TextFiles/rejectedPackages.txt");
            outFile << "**SUMMARY OF REJECTED PACKAGES**\n";
        for (int i=0; i < packages.size(); i++){
            packages[i].getPrices();
        if(!packages[i].isValid(i,hotelVacancy,gameCounter)){
                outFile << "\n";
                outFile << "Client " << customers[i].cId << ": The package contains :" << endl;
                outFile << "Total cost for the package is: $" << packages[i].getTotal() << endl;
                outFile << "Customer budget is: $" << packages[i].getBudget() << endl;
                outFile << "The package is invalid.\n";
        }
        }
    }
};

void BookingSystem::saveData(){
    ifstream infile;
    infile.open("./TextFiles/requirementList.txt");
    if(!infile) {
		cout << "Input file does not exists. " << "Program terminates!!!"
				<< endl;
		return;
    }

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

void BookingSystem::printData(){
	for(int i =0; i < customers.size(); i++){
	    customers[i].print();
	}
}
void BookingSystem::readCustomerRequirements(){
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
#endif