#pragma once

enum OPTION_TYPE {CALL = 1, PUT = -1};

class Contract
{
    protected:
        double value; // Current price of the contract
        double delta, gamma, vega; // Current greeks of the contract

        double market_value; // Price at which the contract was bought or sold
        double expiry; // Time until the contract expires
        double strike; // The strike price of the contract

        double d1, d2;
        double implied_volatility;

        void ResolveContract();
        // Make an evaluator class??
        std::pair<double, double> CalculateD(double underlying_value, double forward_rate, double volatility, bool use_imp_vol = false);

        virtual double payoff(double price);
    public:
        Contract(double p, double T, double K);

        double getPrice();
        double getImpliedVol();

        void CalculateImpliedVolatility(double underlying_value, double quoted_price, double forward_rate);

        virtual double CalculateFairPrice(double underlying_value, double forward_rate, double volatility, bool use_imp_vol = false);
        virtual double CalculateDelta(double underlying_value, double forward_rate, double volatility, bool use_imp_vol = false);
        virtual double CalculateVega(double underlying_value, double forward_rate, double volatility, bool use_imp_vol = false);
        virtual double CalculateGamma(double underlying_value, double forward_rate, double volatility, bool use_imp_vol = false);

        void ingest_new_point(double dt, double S, double forward_rate, double volatility);
};