# Problem B

# Use the Playfair Cipher to encode each line of text
# in secret letter


import sys


def playfair_cipher(key_phrase):
    """
        This function prepares the grid used to encode the letter in 3 steps:
        - Appends the alphabet (except 'J') to the key_phrase
        - Keeps only the first occurrence of a letter
        - Splits the phrase into a 5x5 grid
    """

    key_phrase += 'ABCDEFGHIKLMNOPQRSTUVWXYZ'
    cipher = ''

    for letter in key_phrase:
        if letter == 'J':
            letter = 'I'
        if letter not in cipher:    # Keep first occurrence of a letter
            cipher += letter

    cipher_grid = [cipher[i:i+5] for i in range(0, len(cipher), 5)]     # Make grid

    return cipher_grid


def prepare_message(line):
    """
        Here, we prepare the message for encryption in 3 steps:
        - Insert an 'X' between pairs of identical letters
        - Append an 'X' if line length is odd
        - Split the letters into pairs
    """

    for i in range(0, int(len(line) / 2), 2):       # Iterate over pairs
        if line[i] == line[i+1]:
            line = line[:i+1] + 'X' + line[i+1:]    # Insert 'X' in between if pair is identical

    if len(line) % 2 == 1:      # If line length is odd, append 'X'
        line += 'X'

    line_to_encrypt = [line[2*i:2*i+2] for i in range(0, int(len(line) / 2))]   # Split into pairs

    return line_to_encrypt


def letter_coordinates(grid, letter):
    """
        Finds a letter in the cipher_grid() and returns its coordinates
    """

    for row in range(5):
        if letter == 'J':
            letter = 'I'
        if letter in grid[row]:     # Find row index
            break

    col = grid[row].index(letter)   # Find column index

    return row, col


def encryption(grid, line_to_encrypt):
    """
        This function takes cipher_grid and a line of text as input and encrypts
        letters two at a time as follows:
        - If 'XX' encrypt as 'YY'
        - If both letters are on the same column, move 1 down or wrap around to
          the start of the column
        - If both letters are on the same row, move 1 to the right or wrap around
          to the start of the row
        - If the letters are neither in the same row nor the same column, swap
          their column indices
    """

    encrypted_line = ''

    # Here the _1 prefix refers to the first letter in a pair, and _2 the second
    for pair in line_to_encrypt:
        row_1, col_1 = letter_coordinates(grid, pair[0])    # Coordinates of letter_1
        row_2, col_2 = letter_coordinates(grid, pair[1])    # and letter_2

        if pair == 'XX':                # If 'XX' -> 'YY'
            row_1, col_1 = letter_coordinates(grid, 'Y')
            row_2, col_2 = row_1, col_1
        elif col_1 == col_2:            # For matching rows and columns
            row_1 = (row_1 + 1) % 5     # increment by 1, mod 5 returns to the start as needed
            row_2 = (row_2 + 2) % 5
        elif row_1 == row_2:
            col_1 = (col_1 + 1) % 5
            col_2 = (col_2 + 1) % 5
        else:                           # If neither match swap column coordinates
            col_1, col_2 = col_2, col_1

        encrypted_line += grid[row_1][col_1] + grid[row_2][col_2]   # Find and append letters

    return encrypted_line


if __name__ == '__main__':
    """
        Calls playfair_cipher() once per message
        Calls prepare_message() and encryption() function once per line of text
    """

    fptr = sys.stdout

    while True:
        num_lines = int(input())

        if num_lines == 0:      # '0' is the final input
            break

        key_phrase = "".join(input().split())           # Key phrase for the cipher
        cipher = playfair_cipher(key_phrase.upper())    # Create cipher once per message

        for _ in range(num_lines):
            line = "".join(input().split())
            line_to_encrypt = prepare_message(line.upper())         # Prepares line for encryption
            encrypted_line = encryption(cipher, line_to_encrypt)    # Encrypts line

            fptr.write(encrypted_line + '\n')

        fptr.write('\n')

    fptr.close()
