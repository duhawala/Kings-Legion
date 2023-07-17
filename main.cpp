/*
* Brief description 
* Two cowboy shooters in a small town face off, taking a few steps back. With a swift draw at 1..2..3, one falls.
*/

// Header Files - Murtuza Duhawala
#include<iostream> // I/O Operations
#include<string> // Working with Strings
#include<fstream> // Working with Files 
#include<cstdlib> // Utility Functions
#include<ctime> // Working with Time and Date

using namespace std;

// Functions - Murtuza Duhawala
void greetings();
void each_word(const int, ifstream &, string []);
void score_marker(ofstream &, const int [], const string [], int);
int user_input(const string [], char [], const int);
int figure_input(int, const string[], int);
int letter_checker(const string[], char [], int &);

// Main Function - Murtuza Duhawala
int main()
{
    const int list_limit = 100;
    const int word_limit = 100;

    string words[word_limit]; 

    unsigned random_words = time(0);
    srand(random_words);

    greetings();

    ifstream inputFile;
    inputFile.open("ListOfWords.txt");

    if (!inputFile) 
        cout << "You have a future yet to be determined\n";
    else
    {
        int word_index, game_score;
        int try_index = 0;
        char blank_for_word[word_limit];
        int score_list[list_limit];
        string words_list[list_limit];
        char option;

        each_word(list_limit, inputFile, words);

        do
        {
            word_index = user_input(words, blank_for_word, list_limit);
            game_score = letter_checker(words, blank_for_word, word_index);
            
            words_list[try_index] = words[word_index];
            score_list[try_index] = game_score;

            try_index++;

        } while (option == 'y' || option == 'n');

        inputFile.close();

        ofstream outputFile;
        outputFile.open("PointsOfScores.txt");

        score_marker(outputFile, score_list, words_list, try_index);

        outputFile.close();

    }

    return 0;
}

// Welcome Message - ABDULLAH ABDULLAH
void greetings()
{
    char ch;
    cout << "Welcome to Hangman!\n\n";
    cout << "Rules of the game:\n";
    cout << "1. There were will be a number of blanks generated depending on the word.\n";
    cout << "2. Try to guess each letter of the word.\n";
    cout << "3. Each wrong guess displays the parts of the hangman.\n";
    cout << "4. When the hangman is fully drawn, you're out!.\n";
    cout << "5. Correct guess: +1 point || Wrong guess: -1 point\n";
    cout << "6. Guessing the full word: +2 points and without errors: +3 points\n";
    cout << "7. Good Luck!\n\n";
    cout << "Press any key to continue to game: ";
    cin >> ch;
}

// User Inputs - ABDULLAH ABDULLAH
int user_input(const string words[], char blank_for_word[], const int list_limit)
{
    int random_word = rand() % 12;

    for (int blanks = 0; blanks < words[random_word].length(); blanks++)
    {
        blank_for_word[blanks] = '_';
        cout << blank_for_word[blanks] << " ";
    }
    return random_word;
}

// Check Words - Umer Zahir
void each_word(const int list_limit, ifstream &inputFile, string words[])
{
    int i = 0;

        while (i < list_limit && getline(inputFile, words[i]))
        {
            i++;
        }
}

// Score - ABDULLAH ABDULLAH
int letter_checker(const string words[], char blank_for_word[], int &word_index)
{
    char letter;
    int i = 0;
    int wrong_choice = 0;
    int score = 0, rounded_score = 0;
    const int MAX_GUESS = 26;

    while (i < MAX_GUESS)
    {
        cout << "\n\nEnter a letter to guess: ";
        cin >> letter;

        int search_letter = 0;
        int count_letter = 0;
        bool found_letter = false;

        while (search_letter < words[word_index].length())
        {
            if (blank_for_word[search_letter] == letter)
            {
                cout << "You have already guessed the letter!";
                score--;
            }
            if (words[word_index][search_letter] == letter)
            {
                blank_for_word[search_letter] = letter;
                found_letter = true;
                score++;
            }
            search_letter++;
        }
        i++;

        int j = 0;
        while (j < words[word_index].length())
        {
            if (blank_for_word[j] != '_')
                count_letter++;
            j++;
        }

        int k = 0;
        while (k < words[word_index].length())
        {
            cout << blank_for_word[k] << " ";
            k++;
        }

        if (!found_letter)
        {
            cout << "\n\nWrong letter!\n";
            wrong_choice++;
            score--;
        }

        cout << "\n\nFigure Display\n";
        int check = figure_input(wrong_choice, words, word_index);

        rounded_score = static_cast<double>(score) / words[word_index].length() * 10;

        if (count_letter == words[word_index].length() && check == 0)
        {
            cout << "\n\nYou guessed the right word! ";
            rounded_score += 2;

            if (wrong_choice == 0)
            {
                cout << "\n\nCongrats on the first try! ";
                rounded_score++;
            }

            break;
        }
        else if (check == -1)
        {
            if (rounded_score < 0)
                rounded_score = 0;
            break;
        }
    }

    cout << "\n\nYour score is: " << rounded_score << "/10" ;

    return rounded_score;
}

// ASCII Drawing - Umer Zahir
int figure_input(int wrong_choice, const string words[], int word_index)
{
    char head = 'O', left_body = '/', right_body = '\\', body = '|';

    if (wrong_choice > 0)
        cout << "\t\t " << head << endl;
    if (wrong_choice == 2)
        cout << "\t\t " << body;
    else if (wrong_choice > 2)
        cout << "\t\t" << left_body << body;
    if (wrong_choice > 3)
        cout << right_body << endl;
    if (wrong_choice > 4)
        cout << "\t\t" << left_body;
    if (wrong_choice > 5)
        cout << " " << right_body;
    if (wrong_choice > 6)
    {
        cout << "\n\nGame Over! ";
        cout << "\n\nYour word is " << words[word_index];

        return -1;
    }
    return 0;
}

// Score Board - Umer Zahir
void score_marker(ofstream &outputFile, const int score_list[], const string words_list[], int try_index)
{
    int i = 0;

    while (i < try_index)
    {
        outputFile << words_list[i] << ": " << score_list[i] << endl;
        i++;
    }

}
