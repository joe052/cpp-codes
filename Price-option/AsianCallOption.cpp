#include <iostream>
#include <cmath>

using namespace std;

class AsianCallOption {
private:
    double S0;  // Initial asset price
    double U;   // Up factor
    double D;   // Down factor
    double R;   // Risk-free interest rate
    double Ka;  // Strike price
    int N;      // Number of steps to expiry

public:
    AsianCallOption(double S0_, double U_, double D_, double R_, double Ka_, int N_) {
        S0 = S0_;
        U = U_;
        D = D_;
        R = R_;
        Ka = Ka_;
        N = N_;
    }

    double price() {
        double dt = 1.0 / N;
        double u = exp(U * sqrt(dt));
        double d = exp(-D * sqrt(dt));
        double p = (exp(R * dt) - d) / (u - d);
        double q = 1.0 - p;

        double sum = 0.0;
        for (int i = 0; i <= N; i++) {
            double St = S0 * pow(u, i) * pow(d, N-i);
            sum += St;
        }

        double avg = sum / (N + 1);
        double payoff = max(avg - Ka, 0.0);

        return exp(-R * dt * N) * (p * payoff + q * 0.0);
    }
};