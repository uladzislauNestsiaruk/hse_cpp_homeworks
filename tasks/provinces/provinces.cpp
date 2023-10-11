#include "provinces.h"

int64_t CountPassports(const std::vector<int>& provinces) {
    int64_t new_passports_amount = 0;
    std::multiset<int64_t> provinces_size_order(provinces.begin(), provinces.end());
    while(provinces_size_order.size() > 1){
        new_passports_amount += *provinces_size_order.begin() + *(++provinces_size_order.begin());
        provinces_size_order.insert(*provinces_size_order.begin() + *(++provinces_size_order.begin()));
        provinces_size_order.erase(provinces_size_order.begin());
        provinces_size_order.erase(provinces_size_order.begin());
    }
    return new_passports_amount;
}
