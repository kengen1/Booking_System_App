#ifndef HOTELVOUCHER_H_
#define HOTELVOUCHER_H_

class HotelVoucher: public Ticket {
private:
    string hotelType;
public:
    HotelVoucher(string ht, int d, double disc):
        Ticket(d, 0){
            hotelType = ht;
            discount = disc;
        }
    void printTicket(){
        cout << "Hotel voucher for " << hotelType << " room for " << day << " days at price $" << getTicketPrice() << endl;
    }

    void getHotelPrice(){
        switch(hotelTypeIndexMap[hotelType]){
            case 0:
                fullPrice = 150;
                break;
            case 1:
                fullPrice = 220;
                break;
            case 2:
                fullPrice = 310;
                break;
        };
    }
};
#endif