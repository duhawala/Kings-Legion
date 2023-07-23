/*
* Brief description 
* 
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
        cout << "Yer fate's still up in them there dusty trails, partner.\n";
    else
    {
        int checker, board_points;
        int checkit = 0;
        char space[word_limit];
        int score_list[list_limit];
        string words_list[list_limit];
        char choice;

        each_word(list_limit, inputFile, words);

        do
        {
            checker = user_input(words, space, list_limit);
            board_points = letter_checker(words, space, checker);
            
            words_list[checkit] = words[checker];
            score_list[checkit] = board_points;

            checkit++;

        } while (choice == 'y' || choice == 'n');

        inputFile.close();

        ofstream outputFile;
        outputFile.open("PointsOfScores.txt");

        score_marker(outputFile, score_list, words_list, checkit);

        outputFile.close();

    }

    return 0;
}

// Welcome Message - ABDULLAH ABDULLAH
void greetings()
{
    char ch;
    cout << "Welcome to the town of Hangman, where words are the law\n\n";
    cout << "Hit the target\n";
    cout << "1. The game is designed to be quick and addictive, ensuring players stay engaged.\n";
    cout << "2. Players have 10 chances to guess the wanted cowboy's name correctly.\n";
    cout << "3. No hints or clues will be provided, making the game more intense and challenging.\n";
    cout << "4. The objective is to guess the cowboy's name and save them from harm.\n";
    cout << "5. If a wrong word is guessed, the cowboy's fate is sealed, and they will meet their untimely end.\n";
    cout << "6. Players will get opportunities to save other cowboy lives during the game.\n";
    cout << "7. Howdy, partner! Happy trails ahead!\n\n";
    cout << "Howdy, partner! Press any key to continue to the game: ";
    cin >> ch;
}

// User Inputs - ABDULLAH ABDULLAH
int user_input(const string words[], char space[], const int list_limit)
{
    int random_word = rand() % 12;

    for (int blanks = 0; blanks < words[random_word].length(); blanks++)
    {
        space[blanks] = '_';
        cout << space[blanks] << " ";
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
int letter_checker(const string words[], char space[], int &checker)
{
    char letter;
    int i = 0;
    int wrong_choice = 0;
    int score = 0, rounded_score = 0;
    const int MAX_GUESS = 26;

    while (i < MAX_GUESS)
    {
        cout << "\n\nHowdy, cowboy! Pick a letter and make your guess: ";
        cin >> letter;

        int search_letter = 0;
        int count_letter = 0;
        bool found_letter = false;

        while (search_letter < words[checker].length())
        {
            if (space[search_letter] == letter)
            {
                cout << "Yeehaw, partner! You've already wrangled that letter once! ";
                score--;
            }
            if (words[checker][search_letter] == letter)
            {
                space[search_letter] = letter;
                found_letter = true;
                score++;
            }
            search_letter++;
        }
        i++;

        int j = 0;
        while (j < words[checker].length())
        {
            if (space[j] != '_')
                count_letter++;
            j++;
        }

        int k = 0;
        while (k < words[checker].length())
        {
            cout << space[k] << " ";
            k++;
        }

        if (!found_letter)
        {
            cout << "\n\nWrong letter!\n";
            wrong_choice++;
            score--;
        }

        cout << "\n\nHangman\n";
        int check = figure_input(wrong_choice, words, checker);

        rounded_score = static_cast<double>(score) / words[checker].length() * 10;

        if (count_letter == words[checker].length() && check == 0)
        {
            cout << "\n\nYeehaw, cowboy! You've roped the right word! ";
            rounded_score += 2;

            if (wrong_choice == 0)
            {
                cout << "\n\nHowdy, partner! You hit the target on your first shot! Well done, cowboy! ";
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

    cout << "\n\nYour tally on the scoreboard, partner: " << rounded_score << "/10" ;

    return rounded_score;
}

// ASCII Drawing - Umer Zahir
int figure_input(int wrong_choice, const string words[], int checker)
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
        cout << "\n\nYeehaw, partner! Wranglin' time's up! ";
        cout << "\n\nYour word is as elusive as a tumbleweed in the wind, cowboy! " << words[checker];

        return -1;
    }
    return 0;
}

// Score Board - Umer Zahir
void score_marker(ofstream &outputFile, const int score_list[], const string words_list[], int checkit)
{
    int i = 0;

    while (i < checkit)
    {
        outputFile << words_list[i] << ": " << score_list[i] << endl;
        i++;
    }

}
