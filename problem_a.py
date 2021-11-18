# Problem A

# Check if a sentence is valid (i.e. contains no repeated words).
# If so, return "yes", otherwise return "no"


import sys


def isvalid(sentence):
    """
        Returns False if repeated words are found and True otherwise.
    """

    for word in sentence:
        if sentence.count(word) > 1:
            return False
    return True


if __name__ == '__main__':
    fptr = sys.stdout

    sentence = input().split()

    if isvalid(sentence):
        fptr.write('yes' + '\n')
    else:
        fptr.write('no' + '\n')

    fptr.close()