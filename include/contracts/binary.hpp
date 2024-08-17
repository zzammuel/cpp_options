#include "contracts.hpp"

class Binary : public Contract
{
    protected:
        OPTION_TYPE option_type;

    public:
        Binary(OPTION_TYPE ot, double p, double T, double K);

        double payoff(double price) override;

        double CalculateFairPrice(double underlying_value, double forward_rate, double volatility, bool use_imp_vol = false) override;
        double CalculateDelta(double underlying_value, double forward_rate, double volatility, bool use_imp_vol = false) override;
        double CalculateGamma(double underlying_value, double forward_rate, double volatility, bool use_imp_vol = false) override;
        double CalculateVega(double underlying_value, double forward_rate, double volatility, bool use_imp_vol = false) override;
};