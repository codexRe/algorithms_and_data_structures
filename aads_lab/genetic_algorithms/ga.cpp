// genetic algorithm
#include <bits/stdc++.h>
using namespace std;

struct Individual {
    string genome;
    int fitness;
};

int calc_fitness(const string& genome, const string& target) {
    int f = 0;
    for (size_t i = 0; i < target.size(); ++i)
        if (genome[i] == target[i]) ++f;
    return f;
}

char random_gene(mt19937 &rng) {
    uniform_int_distribution<int> dist(32, 126);
    return static_cast<char>(dist(rng));
}

string random_genome(size_t len, mt19937 &rng) {
    string s(len, ' ');
    for (size_t i = 0; i < len; ++i) s[i] = random_gene(rng);
    return s;
}

const Individual& select_parent(const vector<Individual>& pop, mt19937 &rng) {
    // Roulette-wheel selection on (fitness + 1) to avoid zero probability
    long long sum = 0;
    for (const auto& ind : pop) sum += (ind.fitness + 1);
    uniform_int_distribution<long long> dist(1, max(1LL, sum));
    long long r = dist(rng);
    long long acc = 0;
    for (const auto& ind : pop) {
        acc += (ind.fitness + 1);
        if (acc >= r) return ind;
    }
    return pop.back(); // fallback
}

pair<string,string> crossover(const string& a, const string& b, mt19937 &rng) {
    if (a.size() <= 1) return {a, b};
    uniform_int_distribution<int> cutDist(1, (int)a.size()-1);
    int cut = cutDist(rng);
    string c1 = a.substr(0, cut) + b.substr(cut);
    string c2 = b.substr(0, cut) + a.substr(cut);
    return {c1, c2};
}

void mutate(string& g, double mutation_rate, mt19937 &rng) {
    uniform_real_distribution<double> p(0.0, 1.0);
    for (char &ch : g) {
        if (p(rng) < mutation_rate) ch = random_gene(rng);
    }
}

int main() {
    cout << "\nEnter target string: ";
    string target;
    // Use getline to allow spaces in the target
    if (cin.peek() == '\n') cin.get();
    getline(cin, target);

    cout << "\nEnter population size: ";
    int pop_size; cin >> pop_size;

    cout << "\nEnter max generations: ";
    int max_gen; cin >> max_gen;

    cout << "\nEnter mutation rate (0.0 to 1.0): ";
    double mutation_rate; cin >> mutation_rate;

    cout << "\nRunning Genetic Algorithm...\n";

    mt19937 rng((uint32_t)chrono::high_resolution_clock::now().time_since_epoch().count());

    vector<Individual> population(pop_size);
    for (int i = 0; i < pop_size; ++i) {
        population[i].genome = random_genome(target.size(), rng);
        population[i].fitness = calc_fitness(population[i].genome, target);
    }

    Individual best = *max_element(population.begin(), population.end(),
                                   [](const Individual& a, const Individual& b){ return a.fitness < b.fitness; });

    cout << "\nInitial best: \"" << best.genome << "\"  (fitness " << best.fitness << " / " << (int)target.size() << ")\n";

    // Evolution loop
    for (int gen = 1; gen <= max_gen && best.fitness < (int)target.size(); ++gen) {
        vector<Individual> next_pop;
        next_pop.reserve(pop_size);

        // Elitism: keep the best individual
        next_pop.push_back(best);

        // Fill the rest
        while ((int)next_pop.size() < pop_size) {
            const Individual& p1 = select_parent(population, rng);
            const Individual& p2 = select_parent(population, rng);

            auto [c1, c2] = crossover(p1.genome, p2.genome, rng);
            mutate(c1, mutation_rate, rng);
            mutate(c2, mutation_rate, rng);

            Individual i1{c1, calc_fitness(c1, target)};
            next_pop.push_back(i1);

            if ((int)next_pop.size() < pop_size) {
                Individual i2{c2, calc_fitness(c2, target)};
                next_pop.push_back(i2);
            }
        }

        population.swap(next_pop);

        const auto& gen_best = *max_element(population.begin(), population.end(),
                                            [](const Individual& a, const Individual& b){ return a.fitness < b.fitness; });
        if (gen_best.fitness > best.fitness) best = gen_best;

        cout << "Generation " << gen << " | Best fitness: " << best.fitness
             << " / " << (int)target.size() << " | Best: \"" << best.genome << "\"\n";
    }

    cout << "Target: \"" << target << "\"\n";
    cout << "Best   : \"" << best.genome << "\"\n";
    cout << "Fitness: " << best.fitness << " / " << (int)target.size() << "\n";

    if (best.fitness == (int)target.size()) {
        cout << "Target matched!\n";
    } else {
        cout << "WARN: Max generations reached.\n";
    }

    return 0;
}
