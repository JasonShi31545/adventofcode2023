#include <bits/stdc++.h>

/* Part 1
int main(void) {

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    FILE *input = fopen("trebuchet.in", "r");
    long lines = 0;
    if (input == NULL) {
        return -1;
    }
    while (EOF != (fscanf(input, "%*[^\n]"), fscanf(input, "%*c"))) ++ lines;
    
    fclose(input);
    freopen("trebuchet.in", "r", stdin);


    std::vector<int> results;

    for (size_t i = 0; i < (size_t)lines; i++) {
        std::string line;
        std::cin >> line;
        int leftmost_digit = -1;
        bool ltoggle = false;
        int rightmost_digit = -1;
        for (int j = 0; j < line.size(); j++) {
            if (line[j] <= '9' && line[j] >= '0') {
                if (!ltoggle) leftmost_digit = line[j] - '0';
                ltoggle = true;
                rightmost_digit = line[j] - '0';
            }
        }
        results.push_back(leftmost_digit * 10 + rightmost_digit);
    }

    int sum = 0;
    for (int n : results) {
        sum += n;
    }
    std::cout << "Sum: " << sum << std::endl;
    
    

    return 0;
}
*/


int main(void) {

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    FILE *input = fopen("trebuchet.in", "r");
    long lines = 0;
    if (input == NULL) {
        return -1;
    }
    while (EOF != (fscanf(input, "%*[^\n]"), fscanf(input, "%*c"))) ++ lines;
    
    fclose(input);
    freopen("trebuchet.in", "r", stdin);

    std::map<char, std::vector<std::string>> wordsdb = {
        {'o', {"one"}},
        {'t', {"two", "three"}},
        {'f', {"four", "five"}},
        {'s', {"six", "seven"}},
        {'e', {"eight"}},
        {'n', {"nine"}}
    };
    std::map<std::string, int> word_to_n = {
        {"one", 1},
        {"two", 2},
        {"three", 3},
        {"four", 4},
        {"five", 5},
        {"six", 6},
        {"seven", 7},
        {"eight", 8},
        {"nine", 9}
    };

    auto match = [&wordsdb, &word_to_n](const char *start, size_t strsize) -> int {
        char ch = *start;
        if (ch <= '9' && ch >= '0') return ch - '0';
        if (wordsdb.find(ch) == wordsdb.end()) return -1;
        std::vector<std::string> list = wordsdb[ch];
        for (size_t i = 0; i < list.size(); i++) {
            std::string str = list[i];
            size_t length = str.size();
            if (length > strsize) continue;
            bool match = true;
            for (int j = 0; j < length; j++) {
                if (*(start + j) != str[j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                return word_to_n[str];
            }
        }
        return -1;
    };

    int sum = 0;

    for (size_t i = 0; i < (size_t)lines; i++) {
        // zfive43two3
        std::string line;
        std::cin >> line;
        const char *cstr = line.c_str();
        size_t size = line.size();
        int lmn = -1, rmn = -1;
        bool ltoggle = false;
        for (size_t j  = 0; j < size; j++) {
            size_t rest = size - j;
            int m = match((cstr + j), rest);
            if (m != -1) {
                // success
                if (!ltoggle) { lmn = m; ltoggle = true; }
                rmn = m;
            }
        }
        sum += lmn * 10 + rmn;
    }

    printf("SUM: %d\n", sum);

    return 0;
}
