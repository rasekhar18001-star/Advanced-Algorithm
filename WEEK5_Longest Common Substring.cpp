#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Function to find the Longest Common Substring
string longestCommonSubstring(string str1, string str2) {
    int m = str1.length();
    int n = str2.length();

    // Create a 2D DP table to store lengths of longest common suffixes
    vector<vector<int>> table(m + 1, vector<int>(n + 1, 0));
    int maxLength = 0;  // Store the length of the longest common substring
    int endPos = 0;     // End position of the longest common substring in str1

    // Fill the table
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (str1[i - 1] == str2[j - 1]) {
                table[i][j] = table[i - 1][j - 1] + 1;
                if (table[i][j] > maxLength) {
                    maxLength = table[i][j];
                    endPos = i;  // Update the end position
                }
            } else {
                table[i][j] = 0;
            }
        }
    }

    // Print the DP table
    cout << "\nDP Table:" << endl;
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            cout << table[i][j] << " ";
        }
        cout << endl;
    }

    // Extract the longest common substring
    return str1.substr(endPos - maxLength, maxLength);
}

int main() {
    string str1, str2;

    // Input the strings
    cout << "Enter the first string: ";
    cin >> str1;
    cout << "Enter the second string: ";
    cin >> str2;

    // Get the longest common substring
    string result = longestCommonSubstring(str1, str2);

    // Output the result
    cout << "\nThe longest common substring is: " << result << endl;

    return 0;
}