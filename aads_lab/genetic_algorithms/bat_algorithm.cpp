#include <bits/stdc++.h>
using namespace std;

struct Bat {
    vector<double> x;        // position
    vector<double> v;        // velocity
    double freq;             // frequency
    double fitness;          // f(x)
    double loudness;         // A_t
    double pulseRate;        // r_t (added)
};

double sphere(const vector<double>& x) {
    double s = 0.0;
    for (double xi : x) s += xi*xi;
    return s;
}

int main() {
    int nDim, nBats, nIters;
    double lower, upper;
    double fmin, fmax;
    double A0, r0, alpha, gamma;

    cout << "\nEnter number of dimensions: ";
    cin >> nDim;
    cout << "\nEnter population size (number of bats): ";
    cin >> nBats;
    cout << "\nEnter max iterations: ";
    cin >> nIters;
    cout << "\nEnter search space lower bound: ";
    cin >> lower;
    cout << "Enter search space upper bound: ";
    cin >> upper;
    cout << "\nEnter frequency range fmin and fmax (e.g., 0.0 2.0): ";
    cin >> fmin >> fmax;
    cout << "\nEnter initial loudness A0 (e.g., 0.9): ";
    cin >> A0;
    cout << "Enter initial pulse rate r0 (e.g., 0.5): ";
    cin >> r0;
    cout << "\nEnter alpha (A decay, e.g., 0.9): ";
    cin >> alpha;
    cout << "Enter gamma (r growth, e.g., 0.9): ";
    cin >> gamma;
    
    cout << "\nRunning Bat Algorithm...\n";
    mt19937_64 rng(chrono::high_resolution_clock::now().time_since_epoch().count());
    uniform_real_distribution<double> U01(0.0, 1.0);
    uniform_real_distribution<double> Uspace(lower, upper);
    uniform_real_distribution<double> Ueps(-1.0, 1.0);

    auto clamp_vec = [&](vector<double>& x){
        for (double &xi : x) {
            if (xi < lower) xi = lower;
            if (xi > upper) xi = upper;
        }
    };
    vector<Bat> bats(nBats);
    for (int i = 0; i < nBats; ++i) {
        bats[i].x.assign(nDim, 0.0);
        bats[i].v.assign(nDim, 0.0);
        for (int d = 0; d < nDim; ++d) bats[i].x[d] = Uspace(rng);
        bats[i].freq = 0.0;
        bats[i].loudness = A0;
        bats[i].pulseRate = r0;
        bats[i].fitness = sphere(bats[i].x);
    }
    // Best solution
    Bat best = bats[0];
    for (int i = 1; i < nBats; ++i)
        if (bats[i].fitness < best.fitness) best = bats[i];

    cout << "\nInitial best fitness: " << best.fitness << "\n";

    for (int t = 1; t <= nIters; ++t) {
        
        for (int i = 0; i < nBats; ++i) {
            // 1) Update frequency (beta is random [0,1])
            double beta = U01(rng);
            bats[i].freq = fmin + (fmax - fmin) * beta;
            
            // 2) Update velocity and position
            for (int d = 0; d < nDim; ++d) {
                bats[i].v[d] += (bats[i].x[d] - best.x[d]) * bats[i].freq;
                bats[i].x[d] += bats[i].v[d];
            }
            clamp_vec(bats[i].x);
            
            // 3) Local random walk (FIXED: use < instead of >)
            if (U01(rng) < bats[i].pulseRate) {
                // Calculate average loudness
                double avgLoudness = 0.0;
                for (int j = 0; j < nBats; ++j)
                    avgLoudness += bats[j].loudness;
                avgLoudness /= nBats;
                
                // Random walk around best solution
                vector<double> xLocal = best.x;
                for (int d = 0; d < nDim; ++d) {
                    xLocal[d] = best.x[d] + Ueps(rng) * avgLoudness;
                }
                clamp_vec(xLocal);
                bats[i].x = xLocal;
            }
            
            // Evaluate new position
            double fNew = sphere(bats[i].x);
            
            // 4) Accept solution (FIXED: check and update properly)
            if (fNew < bats[i].fitness && U01(rng) < bats[i].loudness) {
                bats[i].fitness = fNew;
                // Update loudness (decrease)
                bats[i].loudness *= alpha;
                // Update pulse rate (increase)
                bats[i].pulseRate = r0 * (1.0 - exp(-gamma * t));
                
                // Update global best
                if (fNew < best.fitness) {
                    best = bats[i];
                }
            }
        }
        cout << "Iter " << t << " | Best fitness = " << best.fitness << "\n";
    }
    cout << "\nResult:\n";
    cout << "Best fitness: " << best.fitness << "\n";
    cout << "Best position:";
    cout << setprecision(6);
    for (double xi : best.x) cout << " " << xi;
    cout << "\n";

    return 0;
}