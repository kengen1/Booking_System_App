#ifndef GAMETICKET_H_
#define GAMETICKET_H_

class GameTicket: public Ticket{
    private:
        int gameNum;

    public:
        GameTicket(int gNum):
            Ticket(0, 0){
                gameNum = gNum;
                fullPrice = gamePriceMap[gameNum];
            }
        void printTicket(){
            cout << "Game ticket for " << nameMap[gameNum] << " on day " << gameDayMap[gameNum] << " at price $" << getTicketPrice() << endl;
        }
};
#endif