/* Problem B
 *
 * Use the Playfair Cipher to encode each line of text
 * in a secret letter
 */


#include <iostream>
#include <string>
#include <vector>


using namespace std;


vector<string> playfairCipher(string keyPhrase)
{
    /*
     * This function prepares the grid used to encode the letters in 3 steps:
     * - Appends the alphabet (except 'J') to the keyPhrase
     * - Keeps only the first occurence of a letter
     * - Splits the phrase into a 5x5 grid
     */

    string cipher;
    vector<string> cipherGrid;
    string gridRow;

    keyPhrase += "ABCDEFGHIKLMNOPQRSTUVWXYZ";

    for (int i = 0; i < sizeof(keyPhrase); i++)
    {
        if (keyPhrase[i] == 'J')
            keyPhrase[i] = 'I';

        size_t notInCipher = cipher.find(keyPhrase[i]);

        if (notInCipher = npos::string)     // Keep first occurence of a letter
            cipher += keyPhrase[i];
    }

    for (int j = 0; j < 5; j++)      // Create grid
    {
        for (int k = 0; k < 5; k++)
            gridRow += cipher[j];

        cipherGrid.push_back(gridRow);
    }

    return cipherGrid;
}


vector<string> prepareMessage(string line)
{
    /*
     * Here, we prepare the message for encryption in 3 steps:
     * - Insert an 'X' between pairs of identical letters
     * - Append an 'X' if the line length is odd
     * - Split the letters into pairs
     */

    string pairToEncrypt;
    vector<string> lineToEncrypt;

    for (int i = 0; i < sizeof(line); i += 2)   // Iterate over pairs
    {
        if (line[i] == line[i+1])       // Insert 'X' in between if pair is identical
            line.insert(i+1, 1, 'X');
    }

    if (sizeof(line) % 2 == 1)          // If line length is odd, append an 'X'
        line += "X";

    for (int j; j < sizeof(line); j += 2)
    {
        pairToEncrypt = line[2*j] + line[2*j+1];   // Split into pairs of letters
        lineToEncrypt.push_back(pairToEncrypt);
    }

    return lineToEncrypt;
}


namespace getCoords
{
    pair<int, int> letterCoordinates(vector<string> grid, char letter)
    {
        /*
         * Finds a letter in the cipherGrid and returns its coordinates
         */

        pair<int, int> letCoords;

        for (int row = 0; row < 5; row++)           // Search the row containing the letter
        {
            if (letter == 'J')
                letter = 'I';

            size_t col = grid[row].find(letter);

            if (col != string::npos)                // If letter is found return the coordinates
            {
                letCoords.first = row;
                letCoords.second = col;
                break;
            }
        }

        return letCoords;
    }
};


string encryption(vector<string> cipherGrid, vector<string> lineToEncrypt)
{
    /*
     * This function takes cipherGrid and a lineToEncrypt as inputs and encrypts
     * letter two at a time as follows:
     * - If 'XX' encrypt as 'YY'
     * - Else call letterCoodinates on each letter in the pair
     *   - If both letters are on the same column, move 1 down or wrap around to
     *     the start of the column
     *   - If both letters are on the same row, move 1 to the right or wrap around
     *     to the start of the row
     *   - If the letters are neither in the same row nor the same column, swap
     *     their column indices
     */

    string encryptedLine;
    pair<int, int> coordsLet1;
    pair<int, int> coordsLet2;
    pair<string, string> encryptedPair;

    for (int i = 0; i < sizeof(lineToEncrypt); i++)
    {
        coordsLet1 = getCoords::letterCoordinates(cipherGrid, lineToEncrypt[i][0]);     // Get coordinates for the letter pair
        coordsLet2 = getCoords::letterCoordinates(cipherGrid, lineToEncrypt[i][1]);

        if (lineToEncrypt[i][0] == lineToEncrypt[i][1])  // If 'XX' -> 'YY'
        {
            coordsLet1 = getCoords::letterCoordinates(cipherGrid, 'Y');
            coordsLet2 = coordsLet1;
        }

        else if (coordsLet1.first == coordsLet2.first)          // Rows match, increment column by 1 or return to the start
        {
            coordsLet1.second = (coordsLet1.second + 1) % 5;
            coordsLet2.second = (coordsLet2.second + 1) % 5;
        }

        else if (coordsLet1.second == coordsLet2.second)        // Columns match, increment row by 1 or return to the start
        {
            coordsLet1.first = (coordsLet1.first + 1) % 5;
            coordsLet2.first = (coordsLet2.first + 1) % 5;
        }

        else                                                    // Neither match, swap columns coordinates
        {
            int tmp = coordsLet1.second;
            coordsLet1.second = coordsLet2.second;
            coordsLet2.second = tmp;
        }

        encryptedPair.first = cipherGrid[coordsLet1.first].find(coordsLet1.second);
        encryptedPair.second = cipherGrid[coordsLet2.first].find(coordsLet2.second);

        encryptedLine += encryptedPair.first + encryptedPair.second;
    }

    return encryptedLine;
}


int main()
{
    /*
     * Calls playfairCipher once per message
     * Calls prepareMessage and encryption functions once per line of text
     */

    int numLines;           // Assigned in the do-while loop
    string keyPhrase;
    string cipher;

    string line;            // Assigned in the nested while loop
    vector<string> lineToEncrypt;
    string encryptedLine;

    do
    {
        cin >> numLines;
        cin >> keyPhrase;

        vector<string> playfairCipher(string);
        cipher = playfairCipher(keyPhrase);

        while (numLines)
        {
            cin >> line;

            string encryption(string, vector<string>);
            lineToEncrypt = prepareMessage(line);

            encryptedLine = encryption(cipher, lineToEncrypt);

            cout << encryptedLine << "\n" << endl;
        }

        cout << "\n" << endl;
    }

    while (numLines);
}
