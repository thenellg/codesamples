#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

/*
 * What's been built here is a mock leader board entry and structuring application.
 * Rather than just a leaderboard of scores, I have created a leaderboard that shows scores and names.
 * Furthermore, leaderboards are customizable to account for an overall leaderboard and leaderboards for the Xbox and PlayStation consoles.
 * All information is stored within an array of objects that are a class called entry.
 */


class entry {
  public:
    string name;            // User name for the players
    int score;              // Player's score
    string console;         // Identifier for the console, can be just about anything (bool, int, etc.) but for the sake of this I chose to use string
};

/*
 *  Name:          organize
 *  Decription:    Normally, I would use the sort function to make an array from greatest to least, 
 *                 but since this is an array of a class and not ints (or floats), I use this function instead.
 *  Parameters:    vector<entry> leaderboard
 *  Return:        leaderboard organized from greatest score the least score
 */
vector<entry> organize(vector<entry> leaderboard) {
    entry temp;
    
    // Super basic go through array and swap values so that it is organized from greatest to least.
    // This is used in the set up process for the leaderboards. I thought about calling it every time
    // a new entry was added, but I wanted to find a more efficient way
    
    for (int i = 0; i < 10; i++)
    {
        for (int j = i + 1; j < 10; j++)
        {
            if (leaderboard[i].score < leaderboard[j].score)
            {
                temp = leaderboard[i];              //Save to be swapped value as temp for swap
                leaderboard[i] = leaderboard[j];    //swap values
                leaderboard[j] = temp;
            }
        }
    }
    return leaderboard;
}

/*
 *  Name:          setUpLeaderboard
 *  Decription:    Sets up leaderboard with my preprogrammed default players
 *  Parameters:    NONE
 *  Return:        leaderboard organized by organize()
 */
vector<entry> setUpLeaderboard() {
    vector<entry> leaderboard;

    string names[10] = {"Marcus", "Andrew", "Kurt\t", "Greg\t", "Sam\t", "Ashley", "Natalie", "Emma\t", "Nick\t", "Percy"};                         // I could have just organized these to be in the ranked order
    int scores[10] = {100, 20, 49, 10, 50, 90, 90, 5, 60, 70};                                                                                      // but I felt that that may be unrealistic to always assume the data starts in a ranked order
    string consoles[10] = {"PlayStation", "Xbox", "PlayStation", "Xbox",  "PlayStation", "Xbox",  "PlayStation", "Xbox",  "PlayStation", "Xbox"};
    entry temp;

    for (int i = 0; i < 10; i++) {
        temp.name = names[i];
        temp.score = scores[i];
        temp.console = consoles[i];
        leaderboard.push_back(temp);
    }

    return organize(leaderboard);
}

/*
 *  Name:          viewLeaderboard
 *  Decription:    View the leaderboards. The user has the option here to see the overall leaderboard, the PlayStation
 *                 leaderboard, or the Xbox leaderboard.
 *  Parameters:    vector<entry> leaderboard
 *  Return:        N/A
 */
void viewLeaderboard(vector<entry> leaderboard) {
    char choice = NULL;

    cout << "Would you like to see the overall leaderboard, the PlayStation leaderboard, or the Xbox leaderboard?" << endl;
    cout << "A. Overall\tB. PlayStation\tC.Xbox\n: ";
    cin >> choice;

    // The most important part of all of this is that position needs to be a seperate value outside of the class. That way, it can
    // be malliable between the different leaderboards. Alternatively, there could be integers inside the class for overall leaderboard position
    // and console leaderboard position, but I chose to go with this method for the sake of time.

    int position = 1;
    int lastScore = 0;

    if (choice == 'b' || choice == 'B') {
        for (int i = 0; i < leaderboard.size(); i++) {
            if (leaderboard[i].console == "PlayStation"){
                if (lastScore == 0) {                           // Last score here is used to account that not every element of the array is being printed
                    lastScore = leaderboard[i].score;           // However, lastScore also needs to be initialized within the specific circumstance which is what this
                }                                               // if statement does.

                if (i < leaderboard.size() - 1 && leaderboard[i].score != lastScore)                            //We increment the position for leaderboard if there is not a tie.
                    position++;

                lastScore = leaderboard[i].score;
                cout << position << ". " << leaderboard[i].name << '\t' << leaderboard[i].score << endl;        //The actual printing of leaderboard
            }
        }
    }
    else if (choice == 'c' || choice == 'C') {
        for (int i = 0; i < leaderboard.size(); i++) {
            if (leaderboard[i].console == "Xbox") {             // The Xbox version of the printing is the exact same as PlayStation.
                if (lastScore == 0) {                           // The only difference is that it prints the Xbox scores
                    lastScore = leaderboard[i].score;
                }

                if (i < leaderboard.size() - 1 && leaderboard[i].score != lastScore)
                    position++;

                lastScore = leaderboard[i].score;
                cout << position << ". " << leaderboard[i].name << '\t' << leaderboard[i].score << endl;
            }
        }
    }
    else {
        for (int i = 0; i < leaderboard.size(); i++) {
            cout << position << ". " << leaderboard[i].name << '\t' << leaderboard[i].score << endl;

            if (i < leaderboard.size() - 1 && leaderboard[i].score != leaderboard[i + 1].score)        //We are just using score here rather than lastScore because we don't have to worry about not using any array elements
                position++;
        }
    }

    cout << endl;
}

/*
 *  Name:          getIndex
 *  Decription:    Here we use a sliding window to see where the newest entry fits in the overall leaderboard as a ranking of scores.
 *  Parameters:    vector<entry> leaderboard, entry newEntry
 *  Return:        newEntry's index
 */
int getIndex(vector<entry> leaderboard, entry newEntry) {
    // Instead of inputting the enry immediately, we find the index so that we can adjust the array for inputting the newEntry

    for (int i = 0; i < leaderboard.size() - 1; i++) {
        if (i == 0) {                                           // Accounts for one of the edge cases. This edge case is if the user creates a new
            if (newEntry.score > leaderboard[i].score) {        // high score.
                cout << "New entry position is " << 1 << ".  See leaderboard for overall results." << endl;
                return 0;
            }
            else if (newEntry.score == leaderboard[i].score) {
                cout << "New entry position is " << 1 << ".  See leaderboard for overall results." << endl;
                return i + 1;
            }
        }
        else if (newEntry.score == leaderboard[i].score) {                                                   // Another edge case. This time if it the new scores is the same as a previously
            cout << "New entry position is " << i + 1 << ".  See leaderboard for overall results." << endl;  // existing score. It will always be placed after the original score. This is also copied
            return i + 1;                                                                                    // in the i == 0 section for consistency.
        }   
        else {
            if (newEntry.score < leaderboard[i - 1].score && newEntry.score > leaderboard[i].score) {        // The entrie's position is generally found when the function finds a pair of elements where the first is
                cout << "New entry position is " << i << ".  See leaderboard for overall results." << endl;  // greater than our entry's score and the second is smaller than the entry's score. 
                return i;
            }
        }
    }
    return leaderboard.size();
}

/*
 *  Name:          inputNewEntry
 *  Decription:    given the user's inputs, we add the new entry into the array
 *  Parameters:    vector<entry> leaderboard, entry newEntry
 *  Return:        leaderboard with newEntry inserted
 */
vector<entry> inputNewEntry(vector<entry> leaderboard, entry newEntry) {
    int newIndex = getIndex(leaderboard, newEntry); 

    leaderboard.push_back(newEntry);                                    // We push newEntry in at the end so that the spot is there for organization. It will be overridden.

    for (int i = (int)leaderboard.size() - 2; i >= newIndex; i--) {     // Here we move all of our elements from the index on to make room for our new entry. Once they are moved,
        leaderboard[i + 1] = leaderboard[i];                            // the new entry is placed at the index position
    }

    leaderboard[newIndex] = newEntry;
    
    return leaderboard;
}

/*
 *  Name:          addEntry
 *  Decription:    This functions as a user input and a shell for the other add entry functions
 *  Parameters:    vector<entry> leaderboard
 *  Return:        leaderboard with new entry!
 */
vector<entry> addEntry(vector<entry> leaderboard) {
    entry userEntry;
    char consoleChoice = NULL;

    cout << "Welcome to user entry." << endl;                // The user inputs a name, score and console. There is some small error handling for the functions.
    cout << "What is the user's name? :";                    // The information is stored in a temp entry (userEntry) and that temp entry is added into the array.
    cin >> userEntry.name;

    cout << endl << "What is " << userEntry.name << "'s score? :";
    cin >> userEntry.score;
    
    cout << endl << "Was " << userEntry.name << "'using a PlayStation or Xbox?" << endl;
    cout << "A for PlayStation, B for Xbox :";
    cin.get();
    cin >> consoleChoice;

    if (consoleChoice == 'a' || consoleChoice == 'A')
        userEntry.console = "PlayStation";
    else if (consoleChoice == 'b' || consoleChoice == 'B')
        userEntry.console = "Xbox";

    if (userEntry.name.length() < 5) {
        userEntry.name = userEntry.name + '\t';
    }

    leaderboard = inputNewEntry(leaderboard, userEntry);

    cout << endl;
    return leaderboard;
}

/*
 *  Name:          main
 *  Decription:    Main function that holds the general operating of the program
 *  Parameters:    N/A
 *  Return:        0
 */
int main()
{
    vector<entry> leaderboard = setUpLeaderboard();
    bool going = true;

    while (going) {
        char initialChoice = NULL;

        cout << "Would you like to view the leaderboard or add a member?" << endl;
        cout << "A for leaderboard. B for add a member\n: ";
        cin.get();
        cin >> initialChoice;

        if (initialChoice == 'a' || initialChoice == 'A') {
            viewLeaderboard(leaderboard);
        }

        else if (initialChoice == 'b' || initialChoice == 'B') {
            leaderboard = addEntry(leaderboard);
        }

        char endChoice;
        cout << endl << "Are you done?\n: ";
        cin.get();
        cin >> endChoice;

        if (endChoice == 'y' || endChoice == 'Y') {
            going = false;
        }
    }

    printf("Thank you!\n");
    return 0;
}

