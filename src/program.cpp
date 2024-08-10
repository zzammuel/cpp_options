#include <iostream>

#include "../include/contracts/european.hpp"
#include "../include/contracts/binary.hpp"
#include "../include/assets/asset.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    double r, vol, s0, K;
    if (argc==4)
    {
        r = stod(argv[1]);
        vol = stod(argv[2]);
        s0 = stod(argv[3]);
        K = stod(argv[4]);
    }
    else
    {
        r = 0.03;
        vol = 0.1;
        s0 = 100.0;
        K = 99.0;
    }
    GeometricBrownianMotion stock = GeometricBrownianMotion(r, vol, s0, DAY);
    double dt = stock.getTimestep();

    European eucall = European(OPTION_TYPE::CALL, s0, 6.0, 1.0, K);
    European euput = European(OPTION_TYPE::PUT, s0, 6.0, 1.0, K);
    Binary bincall = Binary(OPTION_TYPE::CALL, s0, 0.0, 1.0, K);
    Binary binput = Binary(OPTION_TYPE::PUT, s0, 0.0, 1.0, K);

    double price;
    for(int i=0; i<36; i++) //5 * 24 * 60
    {
        stock.nextPrice();
        price = stock.getPrice();

        eucall.ingest_new_point(dt, price, r, vol);
        euput.ingest_new_point(dt, price, r, vol);
        bincall.ingest_new_point(dt, price, r, vol);
        binput.ingest_new_point(dt, price, r, vol);

        cout << "price=" << price << ". r=" << r << ". vol=" << vol << endl;
        cout << "European call: " << eucall.getPrice() << endl;
        cout << "European put:  " << euput.getPrice() << endl;
        cout << "Binary call:   " << bincall.getPrice() << endl;
        cout << "Binary put:    " << binput.getPrice() << endl;
    }
    
    std::cout << "Final price:                   " << price << endl;
    
    return 0;
}