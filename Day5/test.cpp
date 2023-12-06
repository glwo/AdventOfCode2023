#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

struct SeedRange {
    int start;
    int end;
};

struct Map {
    int destination;
    int sourceStart;
    int rangeLength;
};

std::vector<std::string> dat;

int applyMaps(const std::vector<Map>& maps, int seed) {
    int preMap = seed;
    for (const auto& m : maps) {
        for (const auto& [ds, ss, rl] : {m}) {
            if (ss <= preMap && preMap < ss + rl) {
                preMap = ds + (preMap - ss);
                break;
            }
        }
    }
    return preMap;
}

std::pair<std::vector<int>, std::vector<std::vector<Map>>> parse(bool seedRanges = false) {
    std::vector<int> seeds;
    for (const auto& x : {dat[0].substr(dat[0].find(": ") + 2)}) {
        std::istringstream iss(x);
        int seed;
        while (iss >> seed) {
            seeds.push_back(seed);
        }
    }

    if (seedRanges) {
        std::vector<SeedRange> seedRanges;
        for (size_t i = 0; i < seeds.size(); i += 2) {
            seedRanges.push_back({seeds[i], seeds[i + 1]});
        }
        seeds.clear();
        seeds.reserve(seedRanges.size());
        for (const auto& [sr] : {seedRanges}) {
            seeds.push_back(sr.start);
            seeds.push_back(sr.end);
        }
    }

    std::vector<std::vector<Map>> maps;
    std::vector<Map> currMap;
    for (const auto& d : {dat.begin() + 3, dat.end()}) {
        if (d.empty()) {
            continue;
        }
        if (d.find(":") != std::string::npos) {
            maps.push_back(currMap);
            currMap.clear();
        } else {
            std::istringstream iss(d);
            Map map;
            while (iss >> map.destination >> map.sourceStart >> map.rangeLength) {
                currMap.push_back(map);
            }
        }
    }

    maps.push_back(currMap);

    return {seeds, maps};
}

int part1(bool output = true) {
    auto [seeds, maps] = parse(false);
    std::unordered_map<int, int> locs;
    for (const auto& s : {seeds}) {
        locs[applyMaps(maps, s)] = s;
    }
    int minLoc = std::numeric_limits<int>::max();

    if (output) {
        for (const auto& [lk, lv] : {locs}) {
            if (lk == minLoc) {
                std::cout << "\033[32m";
            }
            std::cout << "Seed " << lv << " maps to location " << lk << std::endl;
            if (lk == minLoc) {
                std::cout << "\033[0m";
            }
        }
    }

    return minLoc;
}

int part2(bool output = true) {
    auto [seeds, maps] = parse(true);

    int stepSize = pow(10, ceil(log10(*std::max_element(seeds.begin(), seeds.end()) / 100.0)));
    std::unordered_map<int, int> searchVals;
    for (const auto& [ss, sl] : {seeds}) {
        for (int s = ss; s < ss + sl; s += stepSize) {
            searchVals[s] = applyMaps(maps, s);
        }
    }
    auto roughEst = *std::min_element(searchVals.begin(), searchVals.end(), [](const auto& x, const auto& y) {
        return x.second < y.second;
    });

    int seedRangeStart = roughEst.first.first;
    int seedRangeEnd = roughEst.first.second;
    int bestEst = roughEst.first.third;

    if (output) {
        std::cout << "Best estimate: " << bestEst << " in seed range " << seedRangeStart << " to " << seedRangeEnd << std::endl;
        std::cout << "Step size: " << std::setw(8) << stepSize << ", best estimate: " << std::setw(10) << bestEst
                  << " near loc " << roughEst.second << std::endl;
    }

    while (stepSize > 1) {
        int leftSearch = std::max(bestEst - stepSize, seedRangeStart);
        int rightSearch = std::min(bestEst + stepSize, seedRangeEnd);

        stepSize /= 10;
        searchVals.clear();
        for (int s = leftSearch; s < rightSearch; s += stepSize) {
            searchVals[s] = applyMaps(maps, s);
        }
        auto [bestEst, bestLoc] = *std::min_element(searchVals.begin(), searchVals.end(), [](const auto& x, const auto& y) {
            return x.second < y.second;
        });

        if (output) {
            std::cout << "Step size: " << std::setw(8) << stepSize << ", best estimate: " << std::setw(10) << bestEst
                      << " near loc " << bestLoc << std::endl;
        }
    }

    return bestLoc;
}

int main() {
    std::cout << "Part 1: " << part1(true) << std::endl;
    std::cout << "Part 2: " << part2(true) << std::endl;
    return 0;
}

