#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

using std::string;
using std::vector;

class solution {
  public:
    vector<string> minAbbreviation(const string & target, const vector<string> & dict) {
        std::cout << "All abbrs for " << target << " are:\n";
        vector<string> abbrs = getAllAbbrs(target);
        std::copy(abbrs.begin(), abbrs.end(), std::ostream_iterator<string>(std::cout, " "));
        vector<string> result;
        std::cout << std::endl;
        for (auto s : abbrs) {
            bool exist = false;
            for (size_t i = 0; i < dict.size(); ++i) {
                if (isValidAbbrFor(s, dict[i])) {
                    exist = true;
                    break;
                }
            }
            if (!exist)
                result.push_back(s);
        }

        std::copy(result.begin(), result.end(), std::ostream_iterator<string>(std::cout, " "));
        std::cout << std::endl;
        
        return result;
    }

  private:
    bool isValidAbbrFor(const string & abbr, const string & word) {
        size_t i = 0, begin = i;
        while(i < word.size() && begin < abbr.size()) {
            if (abbr[begin] >= '0' && abbr[begin] <= '9') {
                size_t end = abbr.find_first_not_of("0123456789", begin);
                int num = std::stoi(abbr.substr(i, end-i));
                i += num;
                if (end != string::npos)
                    begin = end;
                else
                    begin = abbr.size();
            }
            else if (abbr[begin] >= 'a' && abbr[begin] <= 'z'){
                if (abbr[begin] == word[i]) {
                    begin++;
                    i++;
                }
                else
                    return false;
            }
        }
        if (i == word.size() && begin == abbr.size())
            return true;
        return false;
    }

    vector<string> getAllAbbrs(const string & word) {
        vector<string> result;
        if (word.empty())
            result.push_back("");
        else if (word.size() == 1)
        {
            result.push_back("1");
            result.push_back(word);
        }
        else {
            auto front = getAllAbbrs(word.substr(0,1));
            auto rest = word.substr(1);
            auto temp = getAllAbbrs(rest);
            for (auto tmp : temp) {
                for (auto s : front) {
                    size_t last = s.find_last_of("0123456789");
                    size_t end_first = s.find_first_not_of("0123456789", last);
                    size_t first = tmp.find_first_of("1234567890");
                    size_t end_second = tmp.find_first_not_of("1234567890", first);
                    if (last != string::npos && end_first == string::npos && first == 0) {
                        string t = s.substr(0, last);
                        t.append(std::to_string(std::stoi(s.substr(last))+std::stoi(tmp.substr(first, end_second-first))));
                        if (end_second != string::npos)
                            t.append(tmp.substr(end_second));
                    result.push_back(t);
                    }
                    else {
                        s.append(tmp);
                        result.push_back(s);
                    }
                }
            }
        }

        auto comp = [](const string & s1, const string & s2){
            return s1.length() < s2.length();
        };
        std::sort(result.begin(), result.end(), comp);
        
        return result;
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
    auto shortest = soln.minAbbreviation(target, dict);
    std::cout << "The shortest unique abbreviation of " << target << " is:\n";
    std::copy(shortest.begin(), shortest.end(), std::ostream_iterator<string>(std::cout, " "));
    std::cout << std::endl;
}
