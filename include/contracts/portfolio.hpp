#pragma once

#include <memory>
#include <vector>

#include "contracts.hpp"
#include "../assets/asset.hpp"

using namespace std;

class Portfolio{
    private:
        double cash;
        int nr_contracts_held;
        vector<shared_ptr<Contract>> contracts;
    public:
        Portfolio();

        void add_cash(double amt);

        void add_contract(shared_ptr<Contract> cntrct, double underlying_value, double forward_rate, double volatility);
        void ingest_new_point(double dt, double S, double forward_rate, double volatility);

        double get_portfolio_value(bool include_cash = false);
        double get_portfolio_delta();
        double get_portfolio_gamma();
        double get_portfolio_vega();
};