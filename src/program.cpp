#include <iostream>

#include "../include/contracts/european.hpp"
#include "../include/assets/asset.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    double r, vol, p0, K;
    if (argc==4)
    {
        r = stod(argv[1]);
        vol = stod(argv[2]);
        p0 = stod(argv[3]);
        K = stod(argv[4]);
    }
    else
    {
        r = 0.03;
        vol = 0.1;
        p0 = 100.0;
        K = 99.0;
    }
    GeometricBrownianMotion stock = GeometricBrownianMotion(r, vol, p0, DAY);

    European call = European(OPTION_TYPE::CALL, p0, 6.0, 1, K);
    European put = European(OPTION_TYPE::PUT, p0, 6.0, 1, K);

    double price;
    for(int i=0; i<36; i++) //5 * 24 * 60
    {
        stock.nextPrice();
        price = stock.getPrice();

        call.ingest_new_point(1.0 / 365.0, price, r, vol);
        put.ingest_new_point(1.0 / 365.0, price, r, vol);

        cout << "price=" << price << ". r=" << r << ". vol=" << vol << endl;
        cout << "Call: " << call.getPrice() << endl;
        cout << "Put:  " << put.getPrice() << endl;
    }
    
    std::cout << "Final price:                   " << price << endl;
    
    return 0;
}