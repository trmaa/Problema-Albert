/*

TROOTH:

There is n amount of people in a society.

Person A will be friend of Person B when: both P. A and P. B are willing to do so.
This is an AND relation:

	p = P. A is friendly with B.
	q = P. B is friendly with A.
	_________________________________
	|	p	|	q	|	friendship	|
	|-------------------------------|
	|	1	|	1	|		1		|
	|	0	|	1	|		0		|
	|	1	|	0	|		0		|
	|	0	|	0	|		0		|
	|_______|_______|_______________|

Therefore: everyones friends have at least one friend.

*/

#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

bool has_duplicate(const std::vector<int>& vec) {
    std::unordered_set<int> seen;
    for (const auto& value : vec) {
        if (seen.find(value) != seen.end()) {
            return true;
        }
        seen.insert(value);
    }
    return false;
}

class Person {
private:
    std::vector<bool> _states;
    std::vector<int> _friends_in_case;

public:
    const std::vector<bool>& get_states() { return this->_states; }
    const std::vector<int>& get_friends_in_case() { return this->_friends_in_case; }

public:
    std::vector<bool> define_states_in_case(int i, int maxid) {
        int id = i + 1;
        for (int iter = 0; iter < maxid; iter++) {
            this->_states.push_back(true);
        }
        for (int iter = id; iter < maxid; iter++) {
            this->_states[iter] = !this->_states[iter - std::pow(2, i)];
        }

        return this->_states;
    }

    std::vector<int> define_friends_in_case(int maxid, const std::vector<Person>& people) {
        this->_friends_in_case = std::vector<int>(maxid, 0);
        for (int id = 0; id < maxid; id++) {
            for (Person person : people) {
                if (this->_states[id] && person.get_states()[id]) {
                    this->_friends_in_case[id]++;
                }
            }
            this->_friends_in_case[id] -= 1;
            this->_friends_in_case[id] = this->_friends_in_case[id] <= 0 ? 0 : this->_friends_in_case[id];
        }
        return this->_friends_in_case;
    }
};

bool line_is_valid(int id, std::vector<Person> society) {
    std::vector<int> f;
    for (Person p : society) {
        f.push_back(p.get_friends_in_case()[id]);
    }
    return has_duplicate(f);
}

std::vector<Person> define_society(int hbts_n) {
    std::vector<Person> society(hbts_n);

    int maxid = std::pow(2, hbts_n);
    for (int hbt = 0; hbt < hbts_n; hbt++) {
        society[hbt].define_states_in_case(hbt, maxid);
    }
    for (int hbt = 0; hbt < hbts_n; hbt++) {
        society[hbt].define_friends_in_case(maxid, society);
    }

    return society;
}

void show_data(std::vector<Person> society) {
    int hbts_n = society.size();
    int maxid = std::pow(2, hbts_n);
    for (int id = 0; id < maxid; id++) {
        for (int hbt = 0; hbt < hbts_n; hbt++) {
            std::cout << "  |  " << society[hbt].get_states()[id];
        }
        std::cout << "  |" << std::endl;
    }
    std::cout << std::endl;
    for (int id = 0; id < maxid; id++) {
        auto red = [](std::string msg) { return "\033[31m" + msg + "\033[0m"; };
        auto green = [](std::string msg) { return "\033[32m" + msg + "\033[0m"; };
        if (line_is_valid(id, society)) {
            for (int hbt = 0; hbt < hbts_n; hbt++) {
                std::cout << green("  |  ") << green(std::to_string(society[hbt].get_friends_in_case()[id]));
            }
            std::cout << green("  |") << std::endl;
        } else {
            for (int hbt = 0; hbt < hbts_n; hbt++) {
                std::cout << red("  |  ") << red(std::to_string(society[hbt].get_friends_in_case()[id]));
            }
            std::cout << red("  |") << std::endl;
        }
    }
}

int main(int argc, char *argv[]) {
    std::vector<Person> society = define_society(std::stoi(argv[1]));
    show_data(society);
}
