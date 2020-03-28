/***********************************************************************
* Program:
*    Lab 12, Bell-LaPadula
*    Brother Helfrich, CS470
* Author:
*    Ben Smith, Bretton Steiner, John Miller, Jed Billman
* Summary: 
*    This program is designed to keep track of a number of secret
*    messages. IT will display messages to the appropriate users
*    and withhold messages from those lacking the authority.
************************************************************************/

#include <iostream>   // standard input and output
#include <string>     // for convenience
#include <cassert>    // because I am paranoid
#include "interact.h" // the interaction code
#include "messages.h" // the collection of messages
using namespace std;

const char * FILE_NAME = "messages.txt";


/***********************************************
 * DISPLAY OPTIONS
 ***********************************************/
void displayOptions()
{
   cout << "\td .. Display the list of messages\n";
   cout << "\ts .. Show one message\n";
   cout << "\ta .. Add a new message\n";
   cout << "\tu .. Update an existing message\n";
   cout << "\tr .. Delete an existing message\n";
   cout << "\to .. Display this list of options\n";
   cout << "\tl .. Log out\n";
}

/************************************************
 * SIMPLE PROMPT
 ************************************************/
string simplePrompt(const char * prompt)
{
   string input;
   cout << prompt;
   cin  >> input;
   return input;
}

/***************************************************
 * SESSION
 * One login session
 **************************************************/
void session(Messages & messages)
{
   displayUsers();
   string userName = simplePrompt("What is your username? ");
   string password = simplePrompt("What is your password? ");

   // start a session
   Interact interact(userName, password, messages);

   //check user athentication
   Control tempLevel = interact.authenticate(userName, password);
   interact.setUserControl(tempLevel);



   cout << "Welcome, " << userName << " - " << interact.getUserControl() << " please select an option:\n";
   displayOptions();

   // inteact loop
   while (true)
   {
      char option;
      cout << "\n<" << userName << "> ";
      cin  >> option;
      cin.ignore();

      switch (option)
      {
         case 'o':
            displayOptions();
            break;
         case 'd':
            interact.display();
            break;
         case 's':
            interact.show();
            break;
         case 'a':
            interact.add();
            break;
         case 'u':
            interact.update();
            break;
         case 'r':
            interact.remove();
            break;
         case 'l':
            cout << "Goodbye, " << userName << ".\n";
            return;
         default:
            cout << "Unknown option: '" << option << "'\n";
            break;
      }
   }
}

/***************************************************
 * TESTCASES
 * Runs a number of test cases
 ***************************************************/
void testCases(Messages & messages)
{
   cout << "\n****************************\n* Begin Test Cases\n****************************\n\n";

   string usernames[4] = {"PUBLIC_User", "CONFIDENTIAL_User", "PRIVELEGED_User", "SECRET_User"};
   string controlTypes[4] = {"PUBLIC", "CONFIDENTIAL", "PRIVELEGED", "SECRET"};

   // For each control type
   cout << "    [WRITE] Add test:\n";
   for (int i = SECRET; i >= PUBLIC; i--)
   {
      Control control = static_cast<Control>(i);

      // Start a session with a user of the control type
      string username = usernames[i];
      Interact interact(username, "password", messages);

      if (interact.getUserControl() != control)
         interact.setUserControl(control);

      string message = "This message has control type of " + controlTypes[control] + '.';
      string date = "28 March, 2020";

      // Write initial test messages
      interact.testCaseAdd(message, date);
      cout << "\tAdded new message by " << username << "\n";
   }

   cout << endl;

   // For each control type
   for (int i = SECRET; i >= PUBLIC; i--)
   {
      Control control = static_cast<Control>(i);
      string username = usernames[i];
      cout << username << ", Control: " << controlTypes[control] << endl;

      // Start a session with a user of the control type
      Interact interact(username, "password", messages);

      if (interact.getUserControl() != control)
         interact.setUserControl(control);

      // Run read test
      cout << "    [READ] Display test:\n";
      interact.display();

      cout << "    [READ] Show test:\n";
      interact.testCaseShow(110);
      interact.testCaseShow(111);
      interact.testCaseShow(112);
      interact.testCaseShow(113);

      cout << "    [WRITE] Update test:\n";
      string message = " Updated by " + controlTypes[control] + ".";
      interact.testCaseUpdate(110, message);
      interact.testCaseUpdate(111, message);
      interact.testCaseUpdate(112, message);
      interact.testCaseUpdate(113, message);

      if (interact.getUserControl() != SECRET)
         interact.setUserControl(SECRET);

      interact.testCaseShow(110);
      interact.testCaseShow(111);
      interact.testCaseShow(112);
      interact.testCaseShow(113);

      cout << endl;
   }

   cout << "\n****************************\n* End Test Cases\n****************************\n\n";
}

/***************************************************
 * MAIN
 * Where it all begins and where it all ends
 ***************************************************/
int main()
{
   Messages messages(FILE_NAME);

   bool runTestCases;
   char selection;
   cout << "Run test cases? (y/n) ";
   cin >> selection;
   cin.ignore();
   runTestCases = (selection == 'y' || selection == 'Y') ? true : false;

   if (runTestCases)
      testCases(messages);

   bool done;
   do
   {
      session(messages);

      char selection;
      cout << "Will another user be logging in? (y/n) ";
      cin >> selection;
      cin.ignore();
      done = (selection == 'y' || selection == 'Y') ? false : true;
   }
   while (!done);
   
   return 0;
}
