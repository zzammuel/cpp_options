#pragma once

#include <memory>
#include <vector>

#include "contracts.hpp"

using namespace std;

class Portfolio{
    private:
        int nr_contracts_held;
        vector<shared_ptr<Contract>> contracts;
    public:
        Portfolio();

        void add_contract(shared_ptr<Contract> cntrct);
        void ingest_new_point(double dt, double S, double forward_rate, double volatility);

        double get_portfolio_value();
};