#ifndef _PACKAGE_H_
#define _PACKAGE_H_

class Package {
    private:
    int customerID;
    int budget;
    string hotel;
    int total;
    double profit;
    int systemTotal=0;
    int range;

    public:
    vector<FlightTicket> flight;
    vector<GameTicket> game;
    vector<HotelVoucher> voucher;

        Package(){}
        Package(int cID, int budg, string ht, int rng){
            customerID = cID;
            budget = budg;
            hotel = ht;
            range = rng;
        }

        bool operator<(const Package& right) const {
          return (budget > right.budget && range < right.range);
        }
        void addFlightTicket(int fType, int day){
            flight.push_back(FlightTicket(fType,day));
        }
        void addGameTicket(int gameNum){
            game.push_back(GameTicket(gameNum));
        }
        void addHotelVoucher(string htype ,int d , double disc){
            voucher.push_back(HotelVoucher(htype,d,disc));
        }

        void getPrices(){
            for(int i = 0; i < flight.size(); i++){
                flight[i].getTicketPrice();
            }
            for(int i = 0; i < voucher.size(); i++){
                voucher[i].getHotelPrice();
            }
            for(int i = 0; i < game.size(); i++){
                game[i].getTicketPrice();
            }

        }
        void printPackage(){
            for(int i = 0; i < flight.size(); i++){
                flight[i].printTicket();
            }
            for(int i = 0; i < voucher.size(); i++){
                voucher[i].printTicket();
            }
            for(int i = 0; i < game.size(); i++){
                game[i].printTicket();
            }
        }

    int totalFlightPrice(){
        int totalFlightPrice=0;
        for (int i=0; i < flight.size(); i++){
            totalFlightPrice = totalFlightPrice + flight[i].getTicketPrice();
        }
        return totalFlightPrice;
    }

    int totalHotelPrice(){
        int totalHotelPrice=0;
        for (int i=0; i < voucher.size(); i++){
            totalHotelPrice = totalHotelPrice + voucher[i].getTicketPrice();
        }
        return totalHotelPrice;
    }

    int totalGamePrice(){
        int totalGamePrice=0;
        for (int i=0; i < game.size(); i++){
            totalGamePrice = totalGamePrice + game[i].getTicketPrice();
        }
        return totalGamePrice;
    }

    int getTotal(){
        total = totalFlightPrice() + totalGamePrice() + totalHotelPrice();
        return total;
    }

    double getProfit(){
        //5% profit from the sales of air tickets and hotel vouchers
        //15% profit from the sales of game tickets if it is valid
        profit = (totalFlightPrice() * 0.05) + (totalHotelPrice() * 0.05) + (totalGamePrice() * 0.15);
        return profit;
    }

    int getBudget(){
        return budget;
    }
    bool isValid(int i,int hotel[3][NUMBEROFDAYS-1], int games[]){
        int total = getTotal();
        int budget = getBudget();

        if(total > budget){     //first check if the customer can afford the package
                if(hotel[0][i] > 25){
                    return false;
                }
                if(hotel[1][i] > 20){
                    return false;
                }
                if(hotel[2][i] > 40){
                     return false;
                }
                if(games[i] > gameQuota[i]){
                    return false;
                }
            return false;
        }
        return true;
    }
};

#endif