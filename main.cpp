#include <iostream>
#include <string>
#include <vector>

class solution {
  public:
    using std::string;
    using std::vector;

    string minAbbreviation(const string & target, const vector<string> & dict) {
        vector<string> abbrs = getAllAbbrs(target);
        for (auto s : abbrs) {
            bool exist = false;
            for (size_t i = 0; i < dict.size(); ++i) {
                if (isValidAbbrFor(s, dict[i])) {
                    exist = true;
                    break;
                }
            }
            if (!exist)
                return s;
        }
        return "";
    }

  private:
    bool isValidAbbrFor(const string & abbr, const string & word) {
        
    }

    vector<string> getAllAbbrs(const string & word) {
        
    }
};

int main() {
    std::string target{"apple"};
    std::vector<std::string> dict{
        "plain",
            "amber",
            "blade"
    };

    solution soln;
    string shortest = soln.minAbbreviation(target, dict);
    std::cout << "The shortest unique abbreviation of " << target << " is:\n"
              << shortest << std::endl;
}
