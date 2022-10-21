// Ethan Rule
// PA 1
// last edited 9/16/2022
// Matching Game!

//    ADVANTAGES/DISADVANTAGES LINKED LIST:
//    One advantage to using a linked list for a data structure involving sotring command and descriptions is that you gain the
//    ability to insert and delete nodes in a list. This is very useful in the matching game because deleting a index in an array or vector
//    leaves an empty index behind while with a linked list you just have to reconnect the pointers.

//    One disadvantage to using linked list would be the amount of time it takes to get to a specific point in the list. Because a linked
//    list does not have indexes and must be traversed, it is less effecient than an array. However for this assignment we used an array
//    for the parts where it would be handy to use one (profile selection/storing);

//    ADVANTAGES/DISADVANTAGES ARRAY:
//   One advantage of using an array is the ability to traverse it by just selecting an index and being at the position, this is better
//   than linked lists because you are able to access data in the middle of the array, while linked lists you must traverse it using pointers.

//   One disadvantage of using an array, is that deleting a struct within an array would leave an empty index, while deleting a struct or class
//   in an linked list would be reconnected by pointers and would have no gap.

// includes
#include <cstring>
#include <iostream>
#include <vector>
#include <string>
#include <ostream>
#include <string>
#include <fstream>
#include <cstdlib>
using namespace std;
template <class T>
struct node
{
    T data;
    node *next;
};
class linked_list
{
private:
    node<string> *head, *tail;

public:
    linked_list()
    {
        head = NULL;
        tail = NULL;
    }
    void add_node(string n)
    {
        node<string> *tmp = new node<string>;
        tmp->data = n;
        tmp->next = NULL;
        if (head == NULL)
        {
            head = tmp;
            tail = tmp;
        }
        else
        {
            tail->next = tmp;
            tail = tail->next;
        }
    }
    string traverse(int numb)
    {
        node<string> *P = head;
        for (int i = 0; i < numb; i++)
        {
            // go to next node
            P = P->next;
        }
        return P->data;
    }
    void Delete(int n)
    {
        n++;
        node<string> *temp1 = head;
        if (n == 1)
        {
            head = temp1->next; // head points to 2nd node
            free(temp1);        // delete original 1st node
            return;
        }
        for (int i = 2; i < n; i++)
        {
            if (i == n - 1)
            {
                node<string> *temp2 = temp1->next;
                temp1->next = temp2->next;
            }
            temp1 = temp1->next;
        }
    }
    node<string> *getHead()
    {
        return head;
    }
    void setHead(node<string> *temp)
    {
        head = temp;
    }
    int printList()
    {
        node<string> *cur = head;
        int i = 1;
        while (cur != NULL)
        {
            cout << i;
            cout << ". " + cur->data << endl;
            cur = cur->next;
            i++;
        }
        return i;
    }
};

struct profile
{
    string name;
    int score;
};

void playGame(linked_list commandList, profile arr[150], int profileNum)
{
    int questionCount;
    int box = 0;
    do
    {
        cout << "How many questions would you like to complete from 5 to 30 questions?\n";

        cin >> questionCount;
        if (questionCount <= 30 && questionCount >= 5)
        {
            box++;
        }
        cin.clear();
        cin.ignore(100, '\n'); // prevents infinate looping when char is entered.
    } while (box != 1);

    if (questionCount <= 30 && questionCount >= 5) // if this is true run game
    {
        int CurrnetQuestion = 1;
        for (int i = 0; i <= questionCount - 1; i++)
        {

            // random select one command and description
            int numb;
            numb = rand() % 30 + 0;

            // traverse list / copy string to a string

            string correct = commandList.traverse(numb);

            // split the correct string into corCommand, corDescription
            string corCommand = correct.substr(0, correct.find('$'));
            string corDescription = correct.substr(correct.find('$') + 1);

            // random select 2 other descriptions that dont match the previous
            string incorrect1, incorrect2;
            int numb2, numb3;
            do
            {
                numb2 = rand() % 30 + 0;
            } while (numb2 == numb);
            do
            {
                numb3 = rand() % 30 + 0;
            } while (numb3 == numb || numb3 == numb2);
            // using numb 2 and 3 we can traverse the list by that many and take the 2nd strtok descriptions

            incorrect1 = commandList.traverse(numb2);
            incorrect2 = commandList.traverse(numb3);
            string incDescription1, incDescription2;

            incDescription1 = incorrect1.substr(incorrect1.find('$') + 1);
            incDescription2 = incorrect2.substr(incorrect2.find('$') + 1);

            // ask them to match
            cout << "Select the correct description for the following command: \n";
            cout << corCommand << endl;

            // display description options at random
            int dOrder1, dOrder2, dOrder3;

            vector<string> randomizeList;
            randomizeList.push_back(corDescription);
            randomizeList.push_back(incDescription1);
            randomizeList.push_back(incDescription2);
            int corIndex;
            int curIndex;
            while (!randomizeList.empty())
            {
                curIndex++;

                int num;
                num = rand() % randomizeList.size();
                cout << curIndex;
                cout << ". ";
                cout << randomizeList.at(num) << endl;

                if (randomizeList.at(num) == corDescription)
                {
                    corIndex = curIndex;
                }
                randomizeList.erase(randomizeList.begin() + num);
            }
            // take user input
            int answer;
            int box2 = 0;
            do
            {

                cin >> answer;
                if (answer <= 3 && answer >= 1)
                {
                    box2++;
                }
                cin.clear();
                cin.ignore(100, '\n'); // prevents infinate looping when char is entered.
                cout << "invalid input\n";
            } while (box2 != 1);

            curIndex = 0;
            if (answer == corIndex)
            {

                arr[profileNum].score++;
            }
            else
            {
                arr[profileNum].score--;
            }
        }
    }
    // write array to contents to profiles.csv
    ofstream profiles;
    profiles.open("profiles.csv", ofstream::out | ofstream::trunc); // clears previous data in csv incase edits were made to list
    for (int i = 0; i < 145; i++)
    {
        if (arr[i].name == "")
        {
            continue;
        }
        profiles << arr[i].name;
        profiles << ",";
        profiles << arr[i].score << endl;
    }

    profiles.close();
}

int main()
{
    int num;
    srand(time(NULL));

    // create initial head and tail pointers for linked list
    linked_list commandList;

    // read in the file and create nodes attached onto link list until end of file

    fstream f("commands.csv", ios::in);
    string line;
    if (f.is_open())
    {
        getline(f, line);
        while (f)
        {
            commandList.add_node(line); // adds node with string "line" contents
            getline(f, line);
        }

        f.close();
    }
    else
    {
        cout << "ERROR!\n";
    }

    // create array of structs

    profile arr[150];
    int i = 0;
    fstream pro("profiles.csv", ios::in);
    if (pro.is_open())
    {
        string line2;
        int i1;
        while (std::getline(pro, line2))
        {
            arr[i1].name = line2.substr(0, line2.find(','));
            arr[i1].score = stoi(line2.substr(line2.find(',') + 1));
            i1++;
        }
        i = i1;
        pro.close();
    }

    else
    {
        cout << "ERROR!\n";
    }
    while (true)
    {

        cout << "~!Linux Matcher!~\nPlease select an option listed below:\n1. Game Rules\n2. Play Game\n3. Load Previous Game\n4. Add Command\n5. Remove Command\n6. Exit\n";
        int box3 = 0;
        do
        {
            cin >> num;
            if (num <= 6 && num >= 1)
            {
                box3++;
            }
            else if (num > 6 || num < 1)
            {
                cout << "invalid input\n";
            }
            cin.clear();
            cin.ignore(100, '\n'); // prevents infinate looping when char is entered.

        } while (box3 != 1);
        char menu = 'n';

        if (num == 1)
        {
            while (menu != 89 && menu != 121)
            {
                system("clear");
                cout << "You have selected Game Rules!\n";
                cout << "Linux Matcher Game Rules:\n";
                cout << "1. Match the correct Linux command to the correct corrosponding description of the command to gain 1 point.\n";
                cout << "2. If the match is incorrectly matched, you lose one point (negative points are possible).\n";
                cout << "3. Prior to a game beginning, the player is allowed to select the number of match questions they would like to complete.\n";

                cout << "Return to menu Y/n?\n";
                cin >> menu;
            }
        }
        else if (num == 2)
        {
            cout << "You have selected Play Game!\n";
            int num2;
            cout << "1. Create new profile\n2. Select existing profile\n";
            int box5 = 0;
            do
            {
                cin >> num2;
                if (num2 <= 2 && num2 >= 1)
                {
                    box5++;
                }
                else if (num2 > 6 || num2 < 1)
                {
                    cout << "invalid input\n";
                }
                cin.clear();
                cin.ignore(100, '\n'); // prevents infinate looping when char is entered.

            } while (box5 != 1);

            if (num2 == 1)
            {
                string name;
                cout << "Enter new profile name\n";
                cin >> name;
                arr[i].name = name;
                arr[i].score = 0;
                playGame(commandList, arr, i);
            }
            else if (num2 == 2)
            {
                // prints profiles from array of structs
                int profileNum = 0;
                int selection;
                int count = 1;
                cout << "Select a profile";
                while (profileNum < 150)
                {
                    if (arr[profileNum].name == "")
                    {
                        break;
                    }
                    cout << endl;
                    cout << count;
                    cout << ". ";
                    cout << arr[profileNum].name;
                    cout << ",";
                    cout << arr[profileNum].score << endl;
                    profileNum++;
                    count++;
                }
                // take input from user for specific file

                int box6 = 0;
                do
                {
                    cin >> selection;
                    if (selection <= count - 1 && selection >= 1)
                    {
                        box6++;
                    }
                    cin.clear();
                    cin.ignore(100, '\n'); // prevents infinate looping when char is entered.
                    cout << "invalid input\n";
                } while (box6 != 1);
                profileNum = selection - 1;
                // gameplay begins
                playGame(commandList, arr, profileNum);
            }


        }
        else if (num == 3)
        {
            cout << "You have selected Load Previous Game\n";
            // prints profiles from array of structs
            int profileNum = 0;
            int selection;
            int count = 1;
            cout << "Select a profile";
            while (profileNum < 150)
            {
                if (arr[profileNum].name == "")
                {
                    break;
                }
                cout << endl;
                cout << count;
                cout << ". ";
                cout << arr[profileNum].name;
                cout << ",";
                cout << arr[profileNum].score << endl;
                profileNum++;
                count++;
            }
            // take input from user for specific file
            int box6 = 0;
            do
            {
                cin >> selection;
                if (selection <= count - 1 && selection >= 1)
                {
                    box6++;
                }
                cin.clear();
                cin.ignore(100, '\n'); // prevents infinate looping when char is entered.
                cout << "invalid input\n";
            } while (box6 != 1);
            profileNum = selection - 1;
            // repete the play game after selecting a profile
            playGame(commandList, arr, profileNum);
        }
        else if (num == 4)
        {

            cout << "You have selected Add Command\n";
            // ask user for a command name
            string commandName;
            string commandDescription;
            string newCommand;
            cout << "Enter the command name.\n";

            cin >> commandName;
            cout << "Enter the command description\n";
            cin >> commandDescription;
            // combine both strings
            newCommand = commandName + '$' + commandDescription;
            // insert new node at head with the new command
            commandList.add_node(newCommand);

            // duplicates SHOULD NOT BE ALLOWED
        }
        else if (num == 5)
        {
            cout << "You have selected Remove Command\n";

            int input;
            int amount;
            amount = commandList.printList();
            cout << "type the number next to the command you wish to delete\n";
            int box8 = 0;
            do
            {
                cin >> input;
                if (input <= amount - 1 && input >= 1)
                {
                    box8++;
                }
                else if (input > amount - 1 || input < 1)
                {
                    cout << "invalid input\n";
                }
                cin.clear();
                cin.ignore(100, '\n'); // prevents infinate looping when char is entered.

            } while (box8 != 1);

            commandList.Delete(input);

            // delete the selected command
        }
        else if (num == 6)
        {
            cout << "You have selected Exit\n";
            cout << "Goodbye!\n";

            ofstream writeCommand;
            writeCommand.open("commands.csv", ofstream::out | ofstream::trunc); // clears previous data in csv incase edits were made to list
            while (commandList.getHead() != NULL)
            {
                node<string> *cur = commandList.getHead();

                writeCommand << cur->data << endl;
                commandList.setHead(cur->next); // update head to the next node
            }

            writeCommand.close();

            // writes to profiles.csv
            ofstream profiles;
            profiles.open("profiles.csv", ofstream::out | ofstream::trunc); // clears previous data in csv incase edits were made to list
            for (int i = 0; i < 145; i++)
            {
                if (arr[i].name == "")
                {
                    continue;
                }
                profiles << arr[i].name;
                profiles << ",";
                profiles << arr[i].score << endl;
            }

            profiles.close();
            return 0;
        }
    }

    system("clear");
}