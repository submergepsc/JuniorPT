#include <bits/stdc++.h>

struct Person {
    char gender = '?';
    std::string father = "-1";
    std::string mother = "-1";
};

int main() {
    int n;
    if (!(std::cin >> n) || n <= 0) {
        return 0;
    }
    std::unordered_map<std::string, Person> people;
    people.reserve(n * 2);
    auto ensure = [&](const std::string &id) {
        if (id != "-1" && !people.count(id)) {
            people[id] = Person{};
        }
    };
    for (int i = 0; i < n; ++i) {
        std::string id, gender, father, mother;
        std::cin >> id >> gender >> father >> mother;
        Person &p = people[id];
        p.gender = gender.empty() ? '?' : gender[0];
        p.father = father;
        p.mother = mother;
        ensure(father);
        ensure(mother);
    }
    int k;
    if (!(std::cin >> k) || k < 0) {
        return 0;
    }
    auto collect = [&](const std::string &root) {
        std::unordered_map<std::string, int> depth;
        std::queue<std::pair<std::string, int>> q;
        q.push({root, 0});
        while (!q.empty()) {
            auto [id, d] = q.front();
            q.pop();
            if (id == "-1" || d > 4) {
                continue;
            }
            auto it = depth.find(id);
            if (it != depth.end() && it->second <= d) {
                continue;
            }
            depth[id] = d;
            const Person &p = people[id];
            q.push({p.father, d + 1});
            q.push({p.mother, d + 1});
        }
        return depth;
    };

    while (k--) {
        std::string a, b;
        std::cin >> a >> b;
        if (!std::cin) {
            break;
        }
        if (!people.count(a) || !people.count(b)) {
            std::cout << "No" << '\n';
            continue;
        }
        if (people[a].gender == people[b].gender) {
            std::cout << "Never Mind" << '\n';
            continue;
        }
        auto ancestorsA = collect(a);
        auto ancestorsB = collect(b);
        bool forbidden = false;
        for (const auto &entry : ancestorsA) {
            const std::string &ancestor = entry.first;
            if (ancestor == "-1") {
                continue;
            }
            auto it = ancestorsB.find(ancestor);
            if (it != ancestorsB.end()) {
                int depthA = entry.second;
                int depthB = it->second;
                if (depthA <= 4 && depthB <= 4) {
                    forbidden = true;
                    break;
                }
            }
        }
        if (forbidden) {
            std::cout << "No" << '\n';
        } else {
            std::cout << "Yes" << '\n';
        }
    }
    return 0;
}
