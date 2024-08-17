#include <iostream>

#include "../../include/assets/asset.hpp"

using namespace std;

Asset::Asset(double p, double q){
    price = p;
    quantity = q;
}

double Asset::getPrice(){
    return price * quantity;
}

double Asset::getDelta(){
    return 1.0 * quantity;
}

void Asset::buyAsset(double newquantity){
    double diff = newquantity - quantity;
    quantity = newquantity;

    // C->add_cash(diff);
}

GeometricBrownianMotion::GeometricBrownianMotion(double r, double vol, double p0, int freq)
{
    forward_rate = r;
    volatility = vol;
    price = p0;

    switch (freq)
    {
    case SECOND:
        dt = 1 / (double) (365 * 24 * 60 * 60);
        break;
    case MINUTE:
        dt = 1 / (double) (365 * 24 * 60);
        break;
    case HOUR:
        dt = 1 / (double) (365 * 24);
        break;
    case DAY:
        dt = 1 / (double) (365);
        break;
    default:
        dt = 1.0;
        break;
    }
    
    current_time = 0.0;

    distribution = normal_distribution(0.0, 1.0);
}

void GeometricBrownianMotion::printInfo()
{
    cout << "Current price: " << price << endl;
}

void GeometricBrownianMotion::nextPrice()
{
    current_time += dt;

    z = distribution(generator);
    price *= std::exp((forward_rate - volatility * volatility / 2) * dt - std::sqrt(dt) * volatility * z);
}

double GeometricBrownianMotion::getPrice()
{
    return price;
}

double GeometricBrownianMotion::getTimestep()
{
    return dt;
}