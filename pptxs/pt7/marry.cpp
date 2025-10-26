#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>

using namespace std;

struct Person {
    char gender = '?';
    string father = "-1";
    string mother = "-1";
};

unordered_map<string, int> collectAncestors(const string &root, const unordered_map<string, Person> &people) {
    unordered_map<string, int> depth;
    queue<pair<string, int>> q;
    q.push(make_pair(root, 0));
    while (!q.empty()) {
        pair<string, int> node = q.front();
        q.pop();
        const string &id = node.first;
        int d = node.second;
        if (id == "-1" || d > 4) {
            continue;
        }
        unordered_map<string, int>::const_iterator it = depth.find(id);
        if (it != depth.end() && it->second <= d) {
            continue;
        }
        depth[id] = d;
        unordered_map<string, Person>::const_iterator person_it = people.find(id);
        if (person_it != people.end()) {
            const Person &p = person_it->second;
            q.push(make_pair(p.father, d + 1));
            q.push(make_pair(p.mother, d + 1));
        }
    }
    return depth;
}

int main() {
    int n;
    if (!(cin >> n) || n <= 0) {
        return 0;
    }
    unordered_map<string, Person> people;
    people.reserve(static_cast<size_t>(n) * 2);
    for (int i = 0; i < n; ++i) {
        string id, gender, father, mother;
        cin >> id >> gender >> father >> mother;
        Person &p = people[id];
        p.gender = gender.empty() ? '?' : gender[0];
        p.father = father;
        p.mother = mother;
        if (father != "-1" && people.find(father) == people.end()) {
            people[father] = Person{};
        }
        if (mother != "-1" && people.find(mother) == people.end()) {
            people[mother] = Person{};
        }
    }
    int k;
    if (!(cin >> k) || k < 0) {
        return 0;
    }

    while (k--) {
        string a, b;
        cin >> a >> b;
        if (!cin) {
            break;
        }
        if (!people.count(a) || !people.count(b)) {
            cout << "No" << '\n';
            continue;
        }
        if (people[a].gender == people[b].gender) {
            cout << "Never Mind" << '\n';
            continue;
        }
        unordered_map<string, int> ancestorsA = collectAncestors(a, people);
        unordered_map<string, int> ancestorsB = collectAncestors(b, people);
        bool forbidden = false;
        for (const auto &entry : ancestorsA) {
            const string &ancestor = entry.first;
            if (ancestor == "-1") {
                continue;
            }
            unordered_map<string, int>::const_iterator it = ancestorsB.find(ancestor);
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
            cout << "No" << '\n';
        } else {
            cout << "Yes" << '\n';
        }
    }
    return 0;
}
