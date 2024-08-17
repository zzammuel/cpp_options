#include <execution>
#include <algorithm>

#include "../../include/contracts/portfolio.hpp"

Portfolio::Portfolio(){
    contracts = vector<shared_ptr<Contract>> {};
    nr_contracts_held = 0;
}

void Portfolio::ingest_new_point(double dt, double S, double forward_rate, double volatility){
    for (int i=0; i<contracts.size(); i++){
        contracts[i]->ingest_new_point(dt, S, forward_rate, volatility);
    }
}

double Portfolio::get_portfolio_value(){
    double portfolio_value = 0.0;

    // for (int i=0; i<contracts.size(); ++i){
    //     portfolio_value += contracts[i]->getPrice();
    // }

    for_each(execution::par, contracts.begin(), contracts.end(), [&portfolio_value](shared_ptr<Contract> c){
        portfolio_value += c->getPrice();
    });

    return portfolio_value;
}

double Portfolio::get_portfolio_delta(){
    double portfolio_delta = 0.0;

    for_each(execution::par, contracts.begin(), contracts.end(), [&portfolio_delta](shared_ptr<Contract> c){
        portfolio_delta += c->getDelta();
    });

    return portfolio_delta;
};

double Portfolio::get_portfolio_gamma(){
    double portfolio_gamma = 0.0;

    for_each(execution::par, contracts.begin(), contracts.end(), [&portfolio_gamma](shared_ptr<Contract> c){
        portfolio_gamma += c->getGamma();
    });

    return portfolio_gamma;
}

double Portfolio::get_portfolio_vega(){
    double portfolio_vega = 0.0;

    for_each(execution::par, contracts.begin(), contracts.end(), [&portfolio_vega](shared_ptr<Contract> c){
        portfolio_vega += c->getVega();
    });

    return portfolio_vega;
}

void Portfolio::add_contract(shared_ptr<Contract> cntrct){
    contracts.push_back(cntrct);
    nr_contracts_held++;
}