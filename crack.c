#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <crypt.h>

const int MAX_PW_LENGTH = 5;
const int HASH_LENGTH = 13;

void printUsage(void);
bool compareHashes(char hash1[HASH_LENGTH + 1], char hash2[HASH_LENGTH + 1]);
bool permuteAndTest(string guess, int currentIndex, char salt[3], char hash[HASH_LENGTH + 1]);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printUsage();
        return 1;
    }
    
    string hash = argv[1]; 
    char salt[3] = { hash[0], hash[1], '\0' };
    
    // make guesses of all possible lengths
    for (int i = 0; i < MAX_PW_LENGTH; i++)
    {
        // initialize
        char guess[i + 2];
        guess[i + 1] = '\0';        
        for (int j = 0; j < i + 1; j++)
        {
            guess[i] = 'A';
        }
        
        // search password of length i
        if (permuteAndTest(guess, 0, salt, hash))
        {
            printf("%s\n", guess);
            return 0;
        }
       
        
    }
    
    return 2;
}

void printUsage(void)
{
    printf("Usage: ./crack hash\n");
}

bool compareHashes(char hash1[HASH_LENGTH + 1], char hash2[HASH_LENGTH + 1])
{
    for (int i = 0; i < HASH_LENGTH + 1; i++)
    {
        if (hash1[i] != hash2[i])
        {
            return false;
        }
    }
    return true;
}

bool permuteAndTest(string guess, int currentIndex, char salt[3], char hash[HASH_LENGTH + 1])
{
    int len = strlen(guess);
    
    // base case
    if (currentIndex == len - 1)
    {
        for (int i = 'A'; i <= 'Z'; i++)
        {
            guess[currentIndex] = i;
            if (compareHashes(crypt(guess, salt), hash))
            {
                return true;
            }
        }
        
        for (int i = 'a'; i <= 'z'; i++)
        {
            guess[currentIndex] = i;            
            if (compareHashes(crypt(guess, salt), hash))
            {
                return true;
            }
        }
    }
    else
    {
        for (int i = 'A'; i <= 'Z'; i++)
        {
            guess[currentIndex] = i;
            if (permuteAndTest(guess, currentIndex + 1, salt, hash))
            {
                return true;
            }
        }
        
        for (int i = 'a'; i <= 'z'; i++)
        {
            guess[currentIndex] = i;
            if (permuteAndTest(guess, currentIndex + 1, salt, hash))
            {
                return true;
            }
        }
    }   
    
    return false;
}
