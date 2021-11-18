/* Problem B
 *
 * Use the Playfair Cipher to encode each line of text
 * in a secret letter
 */


#include <iostream>
#include <string>


using namespace std;


vector<string> playfairCipher(string keyPhrase)
{
    /*
     * This function prepares the grid used to encode the letters in 3 steps:
     * - Appends the alphabet (except 'J') to the keyPhrase
     * - Keeps only the first occurence of a letter
     * - Splits the phrase into a 5x5 grid
     */

    keyPhrase += "ABCDEFGHIKLMNOPQRSTUVWXYZ";
    string cipher;

    for (i = 0; i < strlen(keyPhrase); i++)
    {
        if keyPhrase[i] is 'J'
            keyPhrase[i] = 'I';
        if keyPhrase[i] not in cipher   // Keep first occurence of a letter
            cipher += letter;
    }

    vector<string> cipherGrid;

    for (int j = 0; j < 5; j++)      // Create grid
    {
        cipherGrid.push_back(cipher[j:j+5]);
    }

    return cipherGrid;
}


vector< pair<string, string> > prepareMessage(string line)
{
    /*
     * Here, we prepare the message for encryption in 3 steps:
     * - Insert an 'X' between pairs of identical letters
     * - Append an 'X' if the line length is odd
     * - Split the letters into pairs
     */

    vector< pair<int, int> > lineToEncrypt;

    for (int i = 0; i < strlen(line); i += 2)   // Iterate over pairs
    {
        if (line[i] == line[i+1])       // Insert 'X' in between if pair is identical
            line.insert(i+1, 1, 'X');
    }

    if (strlen(line) % 2 == 1)          // If line length is odd, append an 'X'
        line += "X";

    for (int j; j < strlen(line) / 2; j++)
    {
        lineToEncrypt.push_back(line[2*j:2*j+1])     // Split into pairs of letters
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
            if (letter is 'J')
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


string encryption(vector<string> cipherGrid, pair<string, string> lineToEncrypt)
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

    for (int i = 0; i < strlen(lineToEncrypt); i++)
    {
        coordsLet1 = getCoords::letterCoordinates(cipher, lineToEncrypt[i][0]);     // Get coordinates for the letter pair
        coordsLet2 = getCoords::letterCoordinates(cipher, lineToEncrypt[i][1]);

        if (lineToEncrypt[i] == pair<'X', 'X'>)     // ???     If 'XX' -> 'YY'
        {
            coordsLet1 = getCoords::letterCoordinates(cipher, 'Y');
            coordsLet2 = getCoords::lettercoordinates(cipher, 'Y');
        }

        else if (coordsLet1.second == coordsLet2.second)    // Columns match
        {
            coordsLet1.first = (coordsLet1.first + 1) % 5;
            coordsLet2.first = (coordsLet2.first + 1) % 5;
        }

        else if (coordsLet1.first == coordsLet2.first)      // Rows match
        {
            coordsLet1.second = (coordsLet1.second + 1) % 5;
            coordsLet2.second = (coordsLet2.second + 1) % 5;
        }

        else                                                // Neither match
        {
            int tmp = coordsLet1.second;
            coordsLet1.second = coordsLet2.second;
            coordsLet2.second = tmp;
        }

        encryptedPair.first = cipherGrid[coordsLet1.first].find(coordLet1.second);
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

    int numLines;           // Used in the first while loop
    string keyPhrase;
    string cipher;

    string line;            // Used in the nested while loop
    vector<string> lineToEncrypt;
    string encryptedLine;

    do
    {
        cin >> numLines;
        cin >> keyPhrase;

        cipher = playfairCipher(keyPhrase);

        while
        {
            cin >> line;

            lineToEncrypt = prepareMessage(line);
            encryptedLine = encryption(cipher, lineToEncrypt);

            cout << encryptedLine << "\n" << endl;
        }

        cout << "\n" << endl;

    }

    while numLines:

}
