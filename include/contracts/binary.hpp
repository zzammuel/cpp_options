#include "contracts.hpp"

class Binary : public Contract
{
    protected:
        OPTION_TYPE option_type;

        void CalculateFairPrice(double forward_rate, double volatility, bool use_imp_vol = false) override;
    public:
        Binary(OPTION_TYPE ot, double S, double p, double T, double K);

        double payoff(double price) override;

        double CalculateDelta(double forward_rate, double volatility, bool use_imp_vol = false) override;
        double CalculateGamma(double forward_rate, double volatility, bool use_imp_vol = false) override;
        double CalculateVega(double forward_rate, double volatility, bool use_imp_vol = false) override;
};