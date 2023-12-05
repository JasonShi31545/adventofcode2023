#include <bits/stdc++.h>

#define ull unsigned long long


std::vector<std::string> SplitAt(std::string input, std::string delim) {
    std::vector<std::string> res;
    std::string cur;
    for (size_t i = 0 ; (i - 1) + delim.size() < input.size(); i++) {
        std::string window = input.substr(i, delim.size());
        if (window == delim) {
            // break
            res.push_back(cur);
            cur = "";
        } else {
            //cur.insert(cur.end(), window.begin(), window.end());
            cur.push_back(input[i]);
        }
    }
    if (cur != "") res.push_back(cur);
    return res;
}

std::string RemoveLeadingAndTrailingSpaces(std::string input) {
    int leading_until, trailing_until;
    for (size_t i = 0; i < input.size(); i++) {
        if (input[i] != ' ') {
            leading_until = i;
            break;
        }
    }
    for (size_t i = input.size() - 1; i >= 0; i--) {
        if (input[i] != ' ') {
            trailing_until = i;
            break;
        }
    }
    return input.substr(leading_until, trailing_until - leading_until + 1);
}

// bool InterpretLine(std::string line) {
//     // tokenise, check for "red", "green", "blue", getPrevToken for number
//     assert(line.substr(0,4) == "Game");
//     std::vector<std::string> rounds = SplitAt(SplitAt(line, ":")[1], ";");
//     for (std::string round : rounds) {
//         std::vector<std::string> trials = SplitAt(round, ",");
//         for (std::string trial : trials) {
//             std::string colour = SplitAt(RemoveLeadingAndTrailingSpaces(trial), " ")[1];
//             int number = atoi((SplitAt(RemoveLeadingAndTrailingSpaces(trial), " ")[0]).c_str());
//             if (colour == "blue") {
//                 if (number > BLUE_LIMIT) return false;
//             } else if (colour == "red") {
//                 if (number > RED_LIMIT) return false;
//             } else if (colour == "green") {
//                 if (number > GREEN_LIMIT) return false;
//             }
//         }
//     }
//     return true;
// }

ull InterpretLine(std::string line) {
    assert(line.substr(0,4) == "Game");
    ull max_blue = 0, max_red = 0, max_green = 0;
    std::vector<std::string> rounds = SplitAt(SplitAt(line, ":")[1], ";");
    for (std::string round : rounds) {
        std::vector<std::string> trials = SplitAt(round, ",");
        for (std::string trial : trials) {
            std::string colour = SplitAt(RemoveLeadingAndTrailingSpaces(trial), " ")[1];
            ull number = (ull)atoi((SplitAt(RemoveLeadingAndTrailingSpaces(trial), " ")[0]).c_str());
            if (colour == "blue") {
                max_blue = std::max(max_blue, number);
            } else if (colour == "red") {
                max_red = std::max(max_red, number);
            } else if (colour == "green") {
                max_green = std::max(max_green, number);
            }
        }
    }
    return max_blue * max_red * max_green;
}


int main(void) {

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    FILE *input = fopen("cube.in", "r");
    long lines = 0;
    if (input == NULL) {
        return -1;
    }
    while (EOF != (fscanf(input, "%*[^\n]"), fscanf(input, "%*c"))) ++ lines;
    
    fclose(input);
    freopen("cube.in", "r", stdin);

    ull sum = 0;
    for (size_t game_id = 0; game_id < (size_t)lines; game_id++) {
        std::string line;
        std::getline(std::cin, line);
        sum += InterpretLine(line);
    }

    printf("%llu", sum);

    return 0;
}
