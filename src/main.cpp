#include <iostream>
#include <string>

// gets a random word from an api
std::string get_word()
{
    bool found_word = false;

    const char *command = "curl -s https://random-word-api.herokuapp.com/word";
    FILE *returned_json = popen(command, "r");

    char buffer[128];
    
    std::string result = "";

    while (fgets(buffer, sizeof(buffer), returned_json) != nullptr)
    {
        result += buffer;
    }

    std::string final_result = "";

    for (size_t i = 0; i < result.length(); i++)
    {
        if (result[i] == '[' || result[i] == ']' || result[i] == '\"')
        {
            found_word = true;
        }
        else if(found_word)
        {
            final_result += result[i];
        }

    }

    pclose(returned_json);

    return final_result;
}

// safe user input
std::string input() {
    std::string inp_str;
    char ch;
    while (std::cin.get(ch) && ch != '\n') {
        inp_str += ch;
    }
    return inp_str;
}

std::string prompt(std::string text) {
    // render the prompt text
    std::cout << text << std::endl;
    // displays the input text
    std::cout << "guess > " << std::flush;

    std::string s;
    s = input();

    // gets user input
    return s;
}

// hangman lists
int attempts = 0;
std::string guessed_words = "";
std::string words_wrong = "";
std::string words_right = "";

// prints the hangman graphics and the word progress
void print_hangman(std::string word)
{
    // hangman graphics
    std::cout << "  _____" << std::endl;
    std::cout << "  |   |" << std::endl;
    if (attempts == 0)
    {
        std::cout << "  |" << std::endl;
        std::cout << "  |" << std::endl;
        std::cout << "  |" << std::endl;
        std::cout << "  |" << std::endl;
    }
    else if (attempts == 1)
    {
        std::cout << "  |   O" << std::endl;
        std::cout << "  |" << std::endl;
        std::cout << "  |" << std::endl;
        std::cout << "  |" << std::endl;
    }
    else if (attempts == 2)
    {
        std::cout << "  |   O" << std::endl;
        std::cout << "  |   |" << std::endl;
        std::cout << "  |   |" << std::endl;
        std::cout << "  |" << std::endl;
    }
    else if (attempts == 3)
    {
        std::cout << "  |   O" << std::endl;
        std::cout << "  |  /|" << std::endl;
        std::cout << "  |   |" << std::endl;
        std::cout << "  |" << std::endl;
    }
    else if (attempts == 4)
    {
        std::cout << "  |   O" << std::endl;
        std::cout << "  |  /|\\" << std::endl;
        std::cout << "  |   |" << std::endl;
        std::cout << "  |" << std::endl;
    }
    else if (attempts == 5)
    {
        std::cout << "  |   O" << std::endl;
        std::cout << "  |  /|\\" << std::endl;
        std::cout << "  |   |" << std::endl;
        std::cout << "  |  /" << std::endl;
    }
    else
    {
        std::cout << "  |   O" << std::endl;
        std::cout << "  |  /|\\" << std::endl;
        std::cout << "  |   |" << std::endl;
        std::cout << "  |  / \\" << std::endl;
    }
    std::cout << "_/^\\_\n" << std::endl;

    bool found = false;

    int count = 0;

    // loop through word
    for (char& c : word)
    {
        found = false;
        // loop through right words
        for (size_t i2 = 0; i2 < words_right.size(); i2++)
        {
            // if the character is in the word then write the charatcer
            if (c == words_right[i2] && !found)
            {
                std::cout << c << std::flush;
                count++;
                found = true;
            }
        }
        if (!found)
        {
            // if it is not found then write a missing letter
            std::cout << "_" << std::flush;   
        }
    }

    std::cout << "\n" << std::endl;

    std::cout << "guessed letters wrong:" << std::endl;

    // writes all wrong characters
    for (size_t i = 0; i < words_wrong.length(); i++)
    {
        std::cout << words_wrong[i] << ", ";
    }
    
    std::cout << std::endl;


    // if all words are guessed then win
    if(count == int(word.size()))
    {
        std::cout << "You Win" << std::endl;
        input();
        exit(0);
    }
    // if the attempts are up then lose
    else if (attempts == 6)
    {
        std::cout << "You Lose\n" << "The word was: " << word << std::endl;
        input();
        exit(0);
    }
    

}


int main ()
{
    // initialize
    char character;
    // random word
    std::string word = get_word();
    
    // game loop
    while (true)
    {
        //std::cout << word << std::endl; // debug
        print_hangman(word);
        // gets the guess
        character = prompt("Type in a letter to guess")[0];

        // if the gussed character is already guessed
        if (guessed_words.find(character) == std::string::npos)
        {
            // if the guess is right
            if(word.find(character) != std::string::npos)
            {
                words_right += character;
            }
            // if guess is wrong
            else
            {
                words_wrong += character;
                attempts++;
            }
            guessed_words += character;
        }
        else
        {
            std::cout << "you already guessed that letter" << std::endl;
        }
        
    }

    return(0);
}