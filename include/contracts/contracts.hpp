#pragma once

enum OPTION_TYPE {CALL = 1, PUT = -1};

class Contract
{
    protected:
        double current_value; // Current price of the contract
        double underlying_value; // Price of underlying asset
        double market_value; // Price at which the contract was bought or sold
        double expiry; // Time until the contract expires
        double strike; // The strike price of the contract

        double d1, d2;
        double implied_volatility;

        void ResolveContract();
        // Make an evaluator class??
        std::pair<double, double> CalculateD(double forward_rate, double volatility, bool use_imp_vol = false);

        virtual double payoff(double price);
    public:
        Contract(double s, double p, double T, double K);

        double getPrice();
        double getImpliedVol();

        virtual double CalculateFairPrice(double forward_rate, double volatility, bool use_imp_vol = false);

        void CalculateImpliedVolatility(double quoted_price, double forward_rate);

        virtual double CalculateDelta(double forward_rate, double volatility, bool use_imp_vol = false);
        virtual double CalculateVega(double forward_rate, double volatility, bool use_imp_vol = false);
        virtual double CalculateGamma(double forward_rate, double volatility, bool use_imp_vol = false);

        void ingest_new_point(double dt, double S, double forward_rate, double volatility);
};