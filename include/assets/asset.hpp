#pragma once

#include <random>

#include "../contracts/portfolio.hpp"

using namespace std;

enum FREQUENCY {SECOND, MINUTE, HOUR, DAY, YEAR};

class Asset
{
    private:
        double price;
        double quantity;
    public:
        Asset(double p, double q);
        
        double getPrice();
        double getDelta();

        void buyAsset(double newquantity);
};

class GeometricBrownianMotion
{
    protected:
        double forward_rate, volatility, price, z, dt;
        double current_time;
        int frequency;

        std::default_random_engine generator;
        std::normal_distribution<double> distribution;
    public:
        GeometricBrownianMotion(double r, double vol, double p0, int freq);
        void printInfo();

        double getPrice();
        double getTimestep();

        void nextPrice();
};