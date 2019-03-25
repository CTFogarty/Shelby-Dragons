//Collin Fogarty
//ctf0014
//Project1
//This code is compiled with the g++ compiler on a tux machine via SSH through PuTTY.
//I used a StackOverflow forum post to learn how to start a new line after a variable is written into a file.
//This is a simple text-based adventure game about a graduate student walking through Shelby Hall.
#include <iostream>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cassert>
using namespace std;

//Handles all functions related to random encounters.
class Encounter
{
public:
    friend class Menu;
    //Prototype of puzzle.
    void puzzle(int& timeLeft, int& intelligence, Encounter random);
    //Prototype of puzzle0.
    void puzzle0(int& intelligence, Encounter random);
    //Prototype of puzzle1.
    void puzzle1(int& intelligence, Encounter random);
    //Prototype of puzzle2.
    void puzzle2(int& intelligence, Encounter random);
    //Prototype of puzzle3.
    void puzzle3(int& intelligence, Encounter random);
    //Prototype of puzzle4.
    void puzzle4(int& intelligence, Encounter random);
    //Prototype of professor.
    void professor(int& timeLeft, int& intelligence);
    //Prototype of student.
    void student(int& timeLeft);
    //Prototype of work.
    void work(int& timeLeft, int& intelligence);
    //Prototype of gradePapers.
    void gradePapers(int& timeLeft, double& money);
};

//Handles all functions related to the game's menu.
class Menu
{
public:
    friend class Encounter;
    //Prototype of title.
    void title(int intelligence, int timeLeft, int steps, double money, bool& test,int highScores[], string players[], Menu menu, Encounter random);
    //Prototype of move.
    void move(int steps, int timeLeft, int intelligence, double money, Menu menu, Encounter random);
    //Prototype of choice.
    void choice(int steps, int intelligence, int timeLeft, double money, Menu menu, Encounter random);
    //Prototype of read.
    void read(int steps, int& intelligence, int& timeLeft, double money, Menu menu, Encounter random);
    //Prototype of search.
    void search(int intelligence, int steps, double& money, int& timeLeft, Menu menu, Encounter random);
    //Prototype of view.
    void view(int intelligence, int timeLeft, int steps, double money, Menu menu, Encounter random);
    //Prototype of quit.
    void quit(int& timeLeft, int& intelligence, double& money);
    //Prototype of randomEncounter.
    void randomEncounter(int& steps, int timeLeft, int intelligence, double money, Menu menu, Encounter random);
};

//Prototype of lose.
void lose(int timeLeft, int intelligence, double money, bool& playing);
//Prototype of win.
void win(int steps, bool& playing);
//Prototype of score.
int score(int timeLeft, int intelligence, double money);
//Prototype of addScore.
void addScore(int score, int highScores[], string name, string players[]);
//Prototype of readScore.
void readScore(int highScores[], string players[]);
//Prototype of writeScore.
void writeScore(int highScores[], string players[]);
//Prototype of displayScore.
void displayScore(int highScores[], string players[]);

//Prototype of test_Lose.
void test_Lose(void);
//Prototype of test_Win.
void test_Win(void);
//Prototype of test_Score.
void test_Score(void);
//Prototype of test_Puzzle0.
void test_Puzzle0(void);
//Prototype of test_Work.
void test_Work(void);

int main() {
    srand(time(0));

    int steps = 20;
    int timeLeft = rand() % 10 + 25;
    int intelligence = rand() % 10 + 25;
    double money = rand() % 10;
    Menu menu;
    Encounter random;
    string name;
    char debug;
    int highScores[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    string players[10] = {"EMPTY", "EMPTY", "EMPTY", "EMPTY", "EMPTY", "EMPTY", "EMPTY", "EMPTY", "EMPTY", "EMPTY"};
    readScore(highScores, players);
    bool testing = false;

    cout << "Would you like to enable debug mode?" << endl;
    cout << "Note: Debug mode will run tests for the program instead of the game." << endl;
    cout << "Y or N?" << endl;
    cin >> debug;

    if (debug == 'Y' || debug == 'y') {
        testing = true;
    }

    if (testing == true) {
        cout << "Debug mode enabled. Tests running." << endl << endl;
        test_Lose();
        test_Win();
        test_Score();
        test_Puzzle0();
        test_Work();
    }
    else {
        cout << "What is your name?" << endl;
        cin >> name;
        cout << endl << endl << endl;
        cout << "Welcome, " << name << "!" << endl;
        cout << name << " you are a graduate student walking through Shelby Hall." << endl;
        cout << "Try and get through without running out of time, intelligence, and money." << endl << endl;
        menu.title(intelligence, timeLeft, steps, money, testing, highScores, players, menu, random);
        int scores = score(timeLeft, intelligence, money);
        addScore(scores, highScores, name, players);
        writeScore(highScores, players);
        cout << "You got " << scores << " points.";
    }  
}

//Checks if time, intelligence, or money has reached zero, ending the game if so.
void lose(int timeLeft, int intelligence, double money, bool& playing) {
    if (timeLeft <= 0) {
        cout << "TIME HAS FALLEN TO ZERO. YOU DIE." << endl;
        playing = false;
    }
    else if (intelligence <= 0) {
        cout << "INTELLIGENCE HAS FALLEN TO ZERO. YOU DIE." << endl;
        playing = false;
    }
    else if (money <= 0) {
        cout << "MONEY HAS FALLEN TO ZERO. YOU DIE." << endl;
        playing = false;
    }
}

//Checks if steps has reached zero, if so ending the game in victory.
void win(int steps, bool& playing) {
    if (steps <= 0) {
        cout << "CONGRATULATIONS! YOU WON!" << endl;
        playing = false;
    }
}

//Calculates total score.
int score(int timeLeft, int intelligence, double money) {
    int iMoney = money;
    int score = timeLeft + intelligence + iMoney;
    return score;
}

//Takes the player's score from the game and checks if it is higher than any of the other highscores.
//If the score is higher than any of the highscores it is placed on the list accordingly from 
void addScore(int score, int highScores[], string name, string players[]) {
    int temp;
    string tempName;
    for (int i = 9; i >= 0; i--) {
        if (i == 9 && score > highScores[i]) {
            highScores[9] = score;
            players[9] = name;

        }
        else {
            if (score > highScores[i]) {
                temp = highScores[i];
                highScores[i] = score;
                highScores[i + 1] = temp;
                tempName = players[i];
                players[i] = name;
                players[i + 1] = tempName;
            }
        }
    }
}

//Reads scores from a file into the highScores and players arrays.
void readScore(int highScores[], string players[]) {
    ifstream inStream;
    int i = 0;
    inStream.open("saves.txt");
    if (inStream.fail()) {
        cout << "No save file." << endl;
    }
    else {
        while (inStream >> players[i] >> highScores[i] ) {
            i++;
        }
    }
    inStream.close();
}

//Writes scores from highScores array onto the "saves.txt" file.
void writeScore(int highScores[], string players[]) {
    ofstream outStream;
    outStream.open("saves.txt");
    int i = 0;
    int arraySize = 10;
    while (i < arraySize) {
		//The "\r\n" escape sequences are used to keep each player and high scores on different lines.
        //The method was shown on a StackOverflow forum.
        outStream << players[i] << "\r\n" << highScores[i] << "\r\n";
        i++;
    }
}

//Displays the high scores printed off from an array.
void displayScore(int highScores[], string players[]) {
    cout << "High Scores" << endl;
    for (int i = 0; i < 10; i++) {
        cout << players[i] << endl;
        cout << highScores[i] << endl;
    }
}

//Handles the title menu.
void Menu::title(int intelligence, int timeLeft, int steps, double money, bool& test,int highScores[], string players[], Menu menu, Encounter random) {
    cout << "1) Start a New Game of Shelby Center and Dragons!" << endl;
    cout << "2) View top 10 High Scores" << endl;
    cout << "3) Quit" << endl << endl;

    char option;
    cout << "\tPlease choose an option: " << endl << endl;
    cin >> option;

    switch (option)
    {
        case '1':
            menu.view(intelligence, timeLeft, steps, money, menu, random);
            break;
        case '2':
            displayScore(highScores, players);
            menu.title(intelligence, timeLeft, steps, money, test, highScores, players, menu, random);
            break;
        case '3':
            cout << "That's too bad. Come back sometime." << endl;
            break;
        default:
             cout << "Please choose a valid input." << endl << endl;
             title(intelligence, timeLeft, steps, money, test, highScores, players, menu, random);
    }

}

//Displays player's current stats.
void Menu::view(int intelligence, int timeLeft, int steps, double money, Menu menu, Encounter random) {
    cout << "You have:" << endl << endl;
    cout << "Intelligence: " << intelligence << endl;
    cout << "Time: " << timeLeft << endl;
    cout << "Money: " << money << endl << endl;
    cout << "You are " << steps << " steps from the goal. Time left: " << timeLeft << "." << endl << endl;
    menu.choice(steps, intelligence, timeLeft, money, menu, random);
}

//Displays current options the player may take in-game.
void Menu::choice(int steps, int intelligence, int timeLeft, double money, Menu menu, Encounter random) {
    cout << "\t\t1) Move forward (take time, may trigger an encounter)" << endl;
    cout << "\t\t2) Read technical papers (boost intelligence, takes time)" << endl;
    cout << "\t\t3) Search for loose change (boost money, takes time)" << endl;
    cout << "\t\t4) View character" << endl;
    cout << "\t\t5) Quit the game" << endl << endl;

    char option;
    cin >> option;
    cout << endl;
    
    switch (option)
    {
        case '1':
            menu.move(steps, timeLeft, intelligence, money, menu, random);
            break;
        case '2':
            menu.read(steps, intelligence, timeLeft, money, menu, random);
            break;
        case '3':
            menu.search(intelligence, steps, money, timeLeft, menu, random);
            break;
        case '4':
            menu.view(intelligence, timeLeft, steps, money, menu, random);
            break;
        case '5':
            menu.quit(timeLeft, intelligence, money);
            break;
        default:
            cout << "Please select a valid option." << endl << endl;
            choice(steps, intelligence, timeLeft, money, menu, random);
    }
}

//Option that will increase intelligence and decrease time.
void Menu::read(int steps, int& intelligence, int& timeLeft, double money, Menu menu, Encounter random) {
    cout << "You read a paper related to your field of study. Intelligence up!" << endl << endl;
    intelligence = intelligence + 2;
    timeLeft = timeLeft - 1;
    if (timeLeft <= 0) {
        timeLeft = 0;
    }
    bool playing = true;
    if (timeLeft <= 0) {
        lose(timeLeft, intelligence, money, playing);
    }
    if (playing == true) {
        menu.choice(steps, intelligence, timeLeft, money, menu, random);
    }
}

//Option that will increase money and decrease time.
void Menu::search(int intelligence, int steps, double& money, int& timeLeft, Menu menu, Encounter random) {
    cout << "You search for loose change. " << endl;
    bool playing = true;
    double change = rand()% 3;
    money = money + change;
    cout << "Its your lucky day. You found $" << change << ". You now have $" << money << "." << endl << endl;
    timeLeft = timeLeft - 1;
    if (timeLeft <= 0) {
        timeLeft = 0;
    }
    lose(timeLeft, intelligence, money, playing);
    if (playing == true) {
        menu.choice(steps, intelligence, timeLeft, money, menu, random);
    }
}

//Option that will end the game.
void Menu::quit(int& timeLeft, int& intelligence, double& money) {
    cout << "Come back some time." << endl << endl;
    timeLeft = 0;
    intelligence = 0;
    money = 0;
}

//Option that will move the player forward, possibly triggering a random encounter.
void Menu::move(int steps, int timeLeft, int intelligence, double money, Menu menu, Encounter random) {
    menu.randomEncounter(steps, timeLeft, intelligence, money, menu, random);
}

//Runs the different types of random encounters.
void Menu::randomEncounter(int& steps, int timeLeft, int intelligence, double money, Menu menu, Encounter random) {
    bool playing = true;
    int encounterType = rand() % 100 + 1;
    if (encounterType > 0 && encounterType <= 25) {
		cout << "Nothing happens. You are enjoying your peaceful walk through Shelby." << endl << endl;
	}
    else if (encounterType > 25 && encounterType <= 50) {
        random.puzzle(timeLeft, intelligence, random);
    }
    else if (encounterType > 50 && encounterType <= 60) {
        random.professor(timeLeft, intelligence);
    }
    else if (encounterType > 60 && encounterType <= 70) {
        random.student(timeLeft);
    }
    else if (encounterType > 70 && encounterType <= 85) {
        random.work(timeLeft, intelligence);
    }
    else if (encounterType > 85 && encounterType <= 100) {
        random.gradePapers(timeLeft, money);
    }

    steps = steps - 1;
    lose(timeLeft, intelligence, money, playing);
    if (playing == true) {
        win(steps, playing);
    }
    if (playing == true) {
        menu.choice(steps, intelligence, timeLeft, money, menu, random);
    }

}

//Plays one of four riddles for the player to solve.
void Encounter::puzzle(int& timeLeft, int& intelligence, Encounter random) {
    int puzzle = rand() % 5;
    cout << "Solve a riddle correctly to gain intelligence." << endl << endl;
    switch (puzzle)
    {
        case 0:
            random.puzzle0(intelligence, random);
            break;
        case 1:
            random.puzzle1(intelligence, random);
            break;
        case 2:
            random.puzzle2(intelligence, random);
            break;
        case 3:
            random.puzzle3(intelligence, random);
            break;
        case 4:
            random.puzzle4(intelligence, random);
            break;
        default:
			cout << "You shouldn't see this." << endl << endl;
    }
    cout << "Lost time solving the riddle." << endl << endl;
    timeLeft = timeLeft - 1;
    if (timeLeft <= 0) {
        timeLeft = 0;
    }
}

//Displays one of four randomly selected riddles for the puzzle(int& timeLeft, int& intelligence) function.
void Encounter::puzzle0(int& intelligence, Encounter random) {
    cout << "What is 2 + 2?" << endl;
    cout << "1) 2" << endl;
    cout << "2) 4" << endl;
    cout << "3) 6" << endl;
    cout << "4) 8" << endl;
    char answer;
    cin >> answer;
    switch (answer)
    {
        case '1':
            cout << "Wrong. You've lost intelligence." << endl << endl;
            intelligence = intelligence - 2;
            if (intelligence <= 0) {
                intelligence = 0;
            }
            break;
        case '2':
            cout << "Correct. You've gained intelligence." << endl << endl;
            intelligence = intelligence + 2;
            if (intelligence <= 0) {
                intelligence = 0;
            }
            break;
        case '3':
            cout << "Wrong. You've lost intelligence." << endl << endl;
            intelligence = intelligence - 2;
            if (intelligence <= 0) {
                intelligence = 0;
            }
            break;
        case '4':
            cout << "Wrong. You've lost intelligence." << endl << endl;
            intelligence = intelligence - 2;
            if (intelligence <= 0) {
                intelligence = 0;
            }
            break;
        default:
            cout << "Please choose a valid input." << endl << endl;
            random.puzzle0(intelligence, random);
    }
}

//Displays one of four randomly selected riddles for the puzzle(int& timeLeft, int& intelligence) function.
void Encounter::puzzle1(int& intelligence, Encounter random) {
    cout << "What is the capital of Alabama?" << endl << endl;
    cout << "1) Mobile" << endl;
    cout << "2) Birmingham" << endl;
    cout << "3) Montgomery" << endl;
    cout << "4) Auburn" << endl << endl;
    char answer;
    cin >> answer;
    switch (answer)
    {
        case '1':
            cout << "Wrong. You've lost intelligence." << endl << endl;
            intelligence = intelligence - 2;
            if (intelligence <= 0) {
                intelligence = 0;
            }
            break;
        case '2':
            cout << "Wrong. You've lost intelligence." << endl << endl;
            intelligence = intelligence - 2;
            if (intelligence <= 0) {
                intelligence = 0;
            }
            break;
        case '3':
            cout << "Correct. You've gained intelligence." << endl << endl;
            intelligence = intelligence + 2;
            break;
        case '4':
            cout << "Wrong. You've lost intelligence." << endl << endl;
            intelligence = intelligence - 2;
            if (intelligence <= 0) {
                intelligence = 0;
            }
            break;
        default:
            cout << "Please choose a valid input." << endl << endl;
            random.puzzle1(intelligence, random);
    }
}

//Displays one of four randomly selected riddles for the puzzle(int& timeLeft, int& intelligence) function.
void Encounter::puzzle2(int& intelligence, Encounter random) {
    cout << "What is the product of 7 and 6?" << endl << endl;
    cout << "1) 13" << endl;
    cout << "2) 25" << endl;
    cout << "3) 42" << endl;
    cout << "4) 52" << endl << endl;
    char answer;
    cin >> answer;
    switch (answer)
    {
        case '1':
            cout << "Wrong. You've lost intelligence." << endl << endl;
            intelligence = intelligence - 2;
            if (intelligence <= 0) {
                intelligence = 0;
            }
            break;
        case '2':
            cout << "Wrong. You've lost intelligence." << endl << endl;
            intelligence = intelligence - 2;
            if (intelligence <= 0) {
                intelligence = 0;
            }
            break;
        case '3':
            cout << "Correct. You've gained intelligence." << endl << endl;
            intelligence = intelligence + 2;
            break;
        case '4':
            cout << "Wrong. You've lost intelligence." << endl << endl;
            intelligence = intelligence - 2;
            if (intelligence <= 0) {
                intelligence = 0;
            }
            break;
        default:
            cout << "Please choose a valid input." << endl << endl;
            random.puzzle2(intelligence, random);
    }
    
}

//Displays one of four randomly selected riddles for the puzzle(int& timeLeft, int& intelligence) function.
void Encounter::puzzle3(int& intelligence, Encounter random) {
    cout << "Who was the first President of the United States of America?" << endl << endl;
    cout << "1) George Bush" << endl;
    cout << "2) Bill Clinton" << endl;
    cout << "3) Andrew Jackson" << endl;
    cout << "4) George Washington" << endl << endl;
    char answer;
    cin >> answer;
    switch (answer)
    {
        case '1':
            cout << "Wrong. You've lost intelligence." << endl << endl;
            intelligence = intelligence - 2;
            if (intelligence <= 0) {
                intelligence = 0;
            }
            break;
        case '2':
            cout << "Wrong. You've lost intelligence." << endl << endl;
            intelligence = intelligence - 2;
            if (intelligence <= 0) {
                intelligence = 0;
            }
            break;
        case '3':
            cout << "Wrong. You've lost intelligence." << endl << endl;
            intelligence = intelligence - 2;
            if (intelligence <= 0) {
                intelligence = 0;
            }
            break;
        case '4':
            cout << "Correct. You've gained intelligence." << endl << endl;
            intelligence = intelligence + 2;
            break;
        default:
            cout << "Please choose a valid input." << endl << endl;
            random.puzzle3(intelligence, random);
    }
}

//Displays one of four randomly selected riddles for the puzzle(int& timeLeft, int& intelligence) function.
void Encounter::puzzle4(int& intelligence, Encounter random) {
    cout << "Which computer brand is not like the others?" << endl << endl;
    cout << "1) Macintosh" << endl;
    cout << "2) Dell" << endl;
    cout << "3) ASUS" << endl;
    cout << "4) Acer" << endl << endl;
    char answer;
    cin >> answer;
    switch (answer)
    {
        case '1':
            cout << "Correct. You've gained intelligence." << endl << endl;
            intelligence = intelligence + 2;
            break;
        case '2':
            cout << "Wrong. You've lost intelligence." << endl << endl;
            intelligence = intelligence - 2;
            if (intelligence <= 0) {
                intelligence = 0;
            }
            break;
        case '3':
            cout << "Wrong. You've lost intelligence." << endl << endl;
            intelligence = intelligence - 2;
            if (intelligence <= 0) {
                intelligence = 0;
            }
            break;
        case '4':
            cout << "Wrong. You've lost intelligence." << endl << endl;
            intelligence = intelligence - 2;
            if (intelligence <= 0) {
                intelligence = 0;
            }
            break;
        default:
            cout << "Please choose a valid input" << endl << endl;
            random.puzzle4(intelligence, random);
    }
}

//Lose time but may gain intelligence.
void Encounter::professor(int& timeLeft, int& intelligence) {
    cout << "Encounter a professor from your department. He is happy to discuss your field of study with you." << endl;
    cout << "Hopefully you can learn something new from him." << endl;
    int chance = rand() % 2;
    if (chance == 0) {
        cout << "The professor taught you something new. Gain intelligence." << endl;
        intelligence = intelligence + 1;
    }
    else {
        cout << "You learn nothing new from the professor as he goes on a tangent." << endl;
    }
    cout << "You lose time speaking to the professor." << endl << endl;
    timeLeft = timeLeft - 1;
    if (timeLeft <= 0) {
        timeLeft = 0;
    }
}

//Lose time.
void Encounter::student(int& timeLeft) {
    cout << "Encounter a fellow grad student in the hall. You lose time in a conversation with him." << endl << endl;
    timeLeft = timeLeft - 2;
    if (timeLeft <= 0) {
        timeLeft = 0;
    }
}

//Lose time and intelligence.
void Encounter::work(int& timeLeft, int& intelligence) {
    cout << "Attacked by grunt work! You lose both time and intelligence because of the boring monotony." << endl << endl;
    timeLeft = timeLeft - 2;
    intelligence = intelligence - 2;
    if (timeLeft <= 0) {
        timeLeft = 0;
    }
    if (intelligence <= 0) {
            intelligence = 0;
    }
}

//Lost time and gain money.
void Encounter::gradePapers(int& timeLeft, double& money) {
    cout << "Asked to grade a professor's test papers. Gain some extra money, but lose time." << endl << endl;
    timeLeft = timeLeft - 2;
    money = money + 3.00;
    if (timeLeft <= 0) {
        timeLeft = 0;
    }
}

//Tests the lose() function.
void test_Lose(void) {
    cout << "Unit Test Case 1: void lose(int timeLeft, int intelligence, double money, bool& playing)" << endl;
    cout << "\tCase 1.1: timeLeft = 0, intelligence = 2, money = 4.00, playing = true. Passes if playing == false." << endl;
    int timeL = 0;
    int intel = 2;
    double moneyM = 4.00;
    bool play = true;

    lose(timeL, intel, moneyM, play);
    assert(true == (play == false));
    cout << "Test passed." << endl << endl;
}

//Tests the win() function.
void test_Win(void) {
    cout << "Unit Test Case 2: void win(int steps, bool& playing)." << endl;
    cout << "\tCase 2.1: steps = 0, playing = true." << endl;
    int stp = 0;
    bool play = true;

    win(stp, play);
    assert(true == (play == false));
    cout << "Test passed." << endl << endl;
}

//Tests the score() function.
void test_Score(void) {
    cout << "Unit Test Case 3: int score(int timeLeft, int intelligence, double money)." << endl;
    cout << "\tCase 3.1: timeLeft = 3, intelligence = 8, money = 6.00" << endl;
    int timeL = 3;
    int intel = 8;
    double moneyM = 6.00;
    int scores = score(timeL, intel, moneyM);

    assert(true == (scores == 17));
    cout << "Test passed." << endl << endl;
}

//Tests the puzzle0() function.
void test_Puzzle0(void) {
    cout << "Unit Test Case 4: void Encounter::puzzle0(int& intelligence, Encounter random)." << endl;
    cout << "\tCase 4.1: intelligence = 9. Select answer 2) please." << endl;

    int intel = 9;
    Encounter random;
    random.puzzle0(intel, random);
    assert(true == (intel == 11));
    cout << "Test passed." << endl << endl;
}

//Tests the puzzle0() function.
void test_Work(void) {
    cout << "Unit Test Case 5: void work(int& timeLeft, int& intelligence)." << endl;
    cout << "\tCase 5.1: timeLeft = 6, intelligence = 4." << endl;
    int timeL = 6;
    int intel = 4;
    Encounter random;

    random.work(timeL, intel);
    assert(true == ((intel == 2)));
    cout << "Test passed." << endl << endl;
}
