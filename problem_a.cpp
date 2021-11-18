/* Problem A
 *
 * Check if a sentence is valid (i.e. contains no repeated words).
 * If so, return "yes", otherwise return "no".
 */


#include <iostream>
#include <sstream>
#include <string>
#include <vector>


using namespace std;


bool isValid(string sentence)
{
    istringstream iss(sentence);
    vector<string> words;
    copy(istream_iterator<string> (iss),
         istream_iterator<string> (),
         back_inserter(words));

    int i = 0;

    while (i < words.size())
    {
        if (count(words.begin(), words.end(), words[i]) > 1)     // Repeated word found
            return false;

        i++;
    }

    return true;    // No repeated words
}


int main()
{
    string sentence;
    getline(cin, sentence);

    cout << (isValid(sentence)? "yes" : "no") << endl;
}
