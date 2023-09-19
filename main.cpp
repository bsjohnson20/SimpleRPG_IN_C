#include <iostream>
#include <limits>
#include <vector>
#include <random>

using std::cin;
using std::cout;
using std::flush;

/*
 * So essentially this is a simple project, you can stab,
 *
 *
 *
 *
 */


// define player data here
double player_hp = 100;
bool isDead = false;

// enemy settings
double enemy_hp = 100;

// difficulty
int difficulty = 0; // 0 - easy, 1 - normal, - 2 hard

// debug
bool debug = true;

// random generator
// chatgpt -- python: random.randint(a,b), c++: ...
double randomgen() {
    // Create a random number generator engine
    std::random_device rd;
    std::mt19937 gen(rd());

    // Create a uniform real distribution between 0 and 2
    std::uniform_real_distribution<double> distribution(0.0, 3.0);

    // Generate a random number between 0 and 2
    double randomValue = distribution(gen);
    return randomValue;

}


// copied code -- stackOverflow
int read_input()
{
    int input = -1;
    bool valid= false;
    do
    {
        std::string words = "Type 0 to stab, 1 to kick, and 2 to block\nStab deals 5 damage, \n Kick deals 2 damage but chance of stun for 2 turns\nBlock has a 100% chance to negate all damage for a turn\n Your input:";
        cout << words + " " << flush;
        cin >> input;
        // what does cin.good do?
        if ((cin.good()) and (input >= 0))
        {
            //everything went well, we'll get out of the loop and return the value
            valid = true;
        }
        else
        {
            //something went wrong, we reset the buffer's state to good
            cin.clear();
            //and empty it
            cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            cout << "Invalid input; please re-enter." << std::endl;
        }
    } while (!valid);

    return (input);
}

int askInput(){
    int choice = 0;
    choice = read_input();
    // refer to this line to get choices
    std::vector<std::string> choices = {"Stab","Kick","Block"};
    cout << "Your choice was " + choices[choice] + "\n";
    return choice;
}

int enemyChoice(){
    int choice;
    choice = randomgen();
    // debug cout << choice + "liu";
    return choice;
}


int main() {
    while (true) {
        cout << "\n\n=================\n";
        cout << "BEGIN A NEW TURN";
        cout << "\n================";
        int num = askInput();

        if (debug){
            cout << "\n TEST \n";
        }
        double player_damage = 0;
        double enemy_damage = 0;
        bool player_block = false;
        bool enemy_block = false;
        switch (num) {
            case 0:
                // stab
                player_damage = 5;
                break;

            case 1:
                // kick
                player_damage = 2;
                break;
            case 2:
                // block
                player_block = true;
                break;
            default:
                cout << "PLAYER SWITCH RECEIVED ERROR";
                break;
        } // end of player attack
        // cout << " TEST asdasda";
        // enemy choice
        int enemy_choice;
        enemy_choice = enemyChoice();
        if (debug){cout << enemy_choice;}
        switch (enemy_choice) { // enemy attack
            case 0:
                // stab
                enemy_damage = 5;
                break;
            case 1:
                // kick
                enemy_damage = 2;
                break;
            case 2:
                // block
                enemy_block = true;
                break;
            default:
                cout << "ERROR SWITCH STATEMENT NOT EXPECTED";
                break;
        }

        if (enemy_block) {
            player_damage = 0;
        }

        if (player_block) {
            enemy_damage = 0;
        }
        cout << "PLAYER DAMAGE " << enemy_damage;
        player_hp -= enemy_damage;
        enemy_hp -= player_damage;

        if (player_hp <= 0){
            cout << "\nNOOO, GG.";
            break;
        }
        if (enemy_hp <= 0){
            cout << "\nGG CHICKEN DINNER";
            break;
        }

        // separator
        cout << "\n\n===============\n";
        cout << "  ATTACK PHASE";
        cout << "\n===============\n\n";

        cout << "\nEnemy did: ";
        cout << enemy_damage;
        cout << "\nPlayer did: ";
        cout << player_damage;

        // wait for user
        // taken from stackOverflow
        printf("\n\nPress enter to continue\n");
        char enter = 0;
        cin.ignore();
        while (enter != '\r' && enter != '\n') { enter = getchar(); }

        cout << "\nPlayer hp ";
        cout << player_hp;
        cout << "\nEnemy hp ";
        cout << enemy_hp << std::endl;

        cout << "\n\n===============\n";
        cout << "  RESULT PHASE";
        cout << "\n===============\n\n";

        printf("\n\nPress enter to continue\n");
        cin.ignore();
        while (enter != '\r' && enter != '\n') { enter = getchar(); }

        // incase
        enemy_damage = 0;
        player_damage = 0;

    }
}