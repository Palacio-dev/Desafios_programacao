#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <set>

// Função para construir a base linear
std::vector<long long> build_basis(const std::vector<long long>& nums) {
    std::vector<long long> basis;
    for (long long val : nums) {
        for (long long b : basis) {
            val = std::min(val, val ^ b);
        }
        if (val > 0) {
            basis.push_back(val);
            std::sort(basis.rbegin(), basis.rend()); // Manter ordenado ajuda
        }
    }
    return basis;
}

// Função para gerar todos os XORs de subconjuntos a partir da base
void generate_subset_xors(int k, long long current_xor, const std::vector<long long>& basis, std::set<long long>& reachable_xors) {
    if (k == basis.size()) {
        reachable_xors.insert(current_xor);
        return;
    }
    generate_subset_xors(k + 1, current_xor, basis, reachable_xors);
    generate_subset_xors(k + 1, current_xor ^ basis[k], basis, reachable_xors);
}


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n;

    std::vector<long long> nums(n);
    long long total_xor = 0;
    for (int i = 0; i < n; i++) {
        std::cin >> nums[i];
        total_xor ^= nums[i];
    }

    // 1. Construir a base
    std::vector<long long> basis = build_basis(nums);

    // 2. Gerar todos os XORs de subconjuntos possíveis
    std::set<long long> subset_xors;
    generate_subset_xors(0, 0, basis, subset_xors);

    // 3. Encontrar o valor máximo
    long long max_val = 0;
    for (long long x : subset_xors) {
        long long y = total_xor ^ x;
        
        // Opção 1: Adicionar 1 ao XOR do primeiro subconjunto
        max_val = std::max(max_val, (x + 1) ^ y);
        
        // Opção 2: Adicionar 1 ao XOR do segundo subconjunto
        max_val = std::max(max_val, x ^ (y + 1));
    }

    std::cout << max_val << std::endl;

    return 0;
}