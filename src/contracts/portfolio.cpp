#include "../../include/contracts/portfolio.hpp"

Portfolio::Portfolio(){
    contracts = vector<shared_ptr<Contract>> {};
    nr_contracts_held = 0;
}

void Portfolio::ingest_new_point(double dt, double S, double forward_rate, double volatility){
    for (int i=0; i<contracts.size(); ++i){
        contracts[i]->ingest_new_point(dt, S, forward_rate, volatility);
    }
}

double Portfolio::get_portfolio_value(){
    double portfolio_value = 0.0;

    for (int i=0; i<contracts.size(); ++i){
        portfolio_value += contracts[i]->getPrice();
    }

    return portfolio_value;
}

void Portfolio::add_contract(shared_ptr<Contract> cntrct){
    contracts.push_back(cntrct);
    nr_contracts_held++;
}