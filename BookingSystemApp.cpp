

#ifndef BookingSystem_CPP_
#define BookingSystem_CPP_

#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
#include<vector>
#include<map>

using namespace std;
#include "BookingSystem.h"
#include "SmartBookingSystem.h"
#include "RequirementCreator.h"

void runAgain();

void classTest1() {
	cout << "Test CustomerRequirements class ... " << endl;
	BookingSystem booking;
	booking.saveData();
	booking.printData();
}

void classTest2() {
	cout << "Test FlightTicket class ... " << endl;

	FlightTicket *tickets[2];
	tickets[0] = new FlightTicket(0, 0);
	tickets[1] = new FlightTicket(1, 1);

	for (int i = 0; i < 2; i++)
		tickets[i]->printTicket();
}

void classTest3() {
	cout << "Test HotelVoucher class ... " << endl;

	HotelVoucher *vouchers[3];
	vouchers[0] = new HotelVoucher("Gold", 0, 0.0);
	vouchers[1] = new HotelVoucher("Bronze", 5,0.2);
	vouchers[2] = new HotelVoucher("Regular", 7, 0.4);

	for (int i = 0; i < 3; i++){
		vouchers[i]->getHotelPrice();
		vouchers[i]->printTicket();
	}
}

void classTest4() {
	cout << "Test GameTicket class ... " << endl;

	GameTicket *tickets[3];
	tickets[0] = new GameTicket(2);
	tickets[1] = new GameTicket(5);
	tickets[2] = new GameTicket(14);

	for (int i = 0; i < 3; i++)
		tickets[i]->printTicket();

}

void classTest5() {
	cout << "\nTest RequirementCreator Class ... " << endl;
	RequirementCreator rg;
	rg.createCustomerBundle();
	rg.writeBundle();
}

void classTest6() {
	cout << "\nTest Package class: \nExample package 1 ... " << endl;
	Package p;
	p.addFlightTicket(0, 3);
	p.addFlightTicket(1, 8);
	p.addGameTicket(2);
	p.addGameTicket(5);
	p.addGameTicket(14);

	p.addHotelVoucher("Regular", 4, 0.0);
	p.addHotelVoucher("Bronze", 8, 0.0);
	p.addHotelVoucher("Gold", 0, 0.0);

	p.printPackage();

	cout << "\nTest Package class: \nExmaple package 2... " << endl;
	Package p2;
	p2.addFlightTicket(0, 3);
	p2.addFlightTicket(1, 6);
	p2.addGameTicket(1);
	p2.addGameTicket(7);
	p2.addGameTicket(8);

	p2.addHotelVoucher("Gold", 3, 0.0);
	p2.addHotelVoucher("Regular", 4, 0.2);
	p2.addHotelVoucher("Gold", 5, 0.4);

	p2.printPackage();
}

void classTest7() {
	BookingSystem agent;
	agent.readCustomerRequirements();
	agent.generatePackages();
	cout<<"\nGenerated valid packages: " << endl;
	agent.printSuccessfulPackages();
	agent.printUnsuccessfulPackages();

}

void classTest8() {
	SmartBookingSystem1 smartagent;
		smartagent.readCustomerRequirements();
		smartagent.generatePackages();
		smartagent.printSuccessfulPackages();
		smartagent.printUnsuccessfulPackages();
}

int main() {
	srand(time(0)); // seed random number generator

	cout << "Choose a class to test: " << endl;
	cout << "1. Test CustomerRequirement class" << endl;
	cout << "2. Test FlightTicket class" << endl;
	cout << "3. Test HotelVoucher class" << endl;
	cout << "4. Test gameTicket class" << endl;
	cout << "5. Test RequirementCreator class" << endl;
	cout << "6. Test Package class" << endl;
	cout << "7. Test BookingSystem class" << endl;
	cout << "8. Run Smart Travel agent" << endl;
	cout << "9. Quit" << endl;

	int choice;
	cin >> choice;

	switch (choice) {
	case 1:
		classTest1();
		break;
	case 2:
		classTest2();
		break;
	case 3:
		classTest3();
		break;
	case 4:
		classTest4();
		break;
	case 5:
		classTest5();
		break;
	case 6:
		classTest6();
		break;
	case 7:
		classTest7();
		break;
	case 8:
		classTest8();
		break;
	case 9:
		cout << "Bye!" << endl;
		break;
	default:
		cout << "Invalid input!" << endl;
	}

	runAgain();
	return 0;
}

void runAgain(){
	cout << "\n Run again? [y][n]";
	char runAgain;
	cin >> runAgain;

	if(runAgain == 'y' || runAgain == 'Y'){
		main();
	}
}

#endif /* BookingSystem_CPP */
