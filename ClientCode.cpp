#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <regex>
#include <algorithm>
#include <fstream>
#include <unordered_map>

using namespace std;

// Utility function to remove leading and trailing spaces
std::string trim(const std::string& str) {
    std::string trimmed = str;
    std::size_t start = trimmed.find_first_not_of(' ');
    std::size_t end = trimmed.find_last_not_of(' ');
    if (start != std::string::npos && end != std::string::npos) {
        trimmed.erase(0, start);
        trimmed.erase(end + 1);
    }
    return trimmed;
}

// Function to count the number of lines in a script
int countLines(const std::string& script) {
    int lineCount = 0;
    for (char ch : script) {
        if (ch == '\n') {
            lineCount++;
        }
    }
    return lineCount;
}

// Function to check if a string is a valid email address
bool isValidEmail(const std::string& email) {
    std::regex emailRegex("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    return std::regex_match(email, emailRegex);
}

// Function to extract and return the first email address found in the script
std::string extractFirstEmail(const std::string& script) {
    std::regex emailRegex("[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}");
    std::smatch match;

    if (std::regex_search(script, match, emailRegex)) {
        return match.str();
    }
    else {
        return "";
    }
}

// Function to split the script into an array of words
std::vector<std::string> splitScriptToWords(const std::string& script) {
    std::regex wordRegex("\\b[a-zA-Z0-9'-]+\\b");
    std::vector<std::string> words;
    std::sregex_iterator rit(script.begin(), script.end(), wordRegex);
    std::sregex_iterator end;

    for (; rit != end; ++rit) {
        words.push_back(rit->str());
    }

    return words;
}

// Function to count the frequency of each word in the script
std::unordered_map<std::string, int> countWordFrequency(const std::string& script) {
    std::unordered_map<std::string, int> wordCount;
    std::vector<std::string> words = splitScriptToWords(script);

    for (std::string& word : words) {
        std::string lowerWord = word;
        for (auto& ch : lowerWord) {
            ch = tolower(static_cast<unsigned char>(ch));
        }
        wordCount[word]++;

    }

    return wordCount;
}

int main() {
    const char* scriptFileName = "film_script.txt";  // Replace with your actual script file name
    std::ifstream scriptFile(scriptFileName);
    std::string script((std::istreambuf_iterator<char>(scriptFile)), std::istreambuf_iterator<char>());

    if (scriptFile.fail()) {
        std::cout << "Error: Failed to open script file." << std::endl;
        return 1;
    }

    std::cout << "Number of lines in the script: " << countLines(script) << std::endl;

    std::string firstEmail = extractFirstEmail(script);
    if (!firstEmail.empty()) {
        std::cout << "First email address found in the script: " << firstEmail << std::endl;
    }
    else {
        std::cout << "No email address found in the script." << std::endl;
    }

    std::unordered_map<std::string, int> wordFrequency = countWordFrequency(script);
    std::cout << "Word Frequency in the script:" << std::endl;
    for (const auto& entry : wordFrequency) {
        std::cout << entry.first << ": " << entry.second << std::endl;
    }

    return 0;
}