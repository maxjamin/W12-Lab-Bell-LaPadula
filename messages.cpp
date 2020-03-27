/***********************************************************************
 * COMPONENT:
 *    MESSAGES
 * Author:
 *    Br. Helfrich, Ben Smith
 * Summary:
 *    This class stores the notion of a collection of messages
 ************************************************************************/

#include <string>     // for convenience
#include <list>       // to store the messages
#include <iostream>   // standard input and output
#include <fstream>    // the messages are read from a file
#include <cassert>    // because I am paraniod
#include "control.h"  // all the Bell-LaPadula code
#include "message.h"  // all the code about a single message
#include "messages.h" // a collection messages

using namespace std;

/***********************************************
 * MESSAGES :: DISPLAY
 * display the list of messages
 ***********************************************/
void Messages::display(Control userLevel) const
{
   for (list <Message> :: const_iterator it = messages.begin();
        it != messages.end();
        ++it)
   {
      //Only show displays that have the same Control level or higher
      if(userLevel >= it->getControlLevel())
        it->displayProperties();
   }
}

/***********************************************
 * MESSAGES :: SHOW
 * show a single message
 **********************************************/
void Messages::show(int id, Control userLevel) const
{
   for (list <Message> :: const_iterator it = messages.begin();
        it != messages.end();
        ++it)
      //Only show displays that have the same Control level or higher
      if (it->getID() == id && userLevel >= it->getControlLevel())
         it->displayText();
}

/***********************************************
 * MESSAGES :: UPDATE
 * update one single message
 ***********************************************/
void Messages::update(int id, const string & text, Control userLevel)
{
   for (list <Message> :: iterator it = messages.begin();
        it != messages.end();
        ++it)

      //Only let the user change if the message is >= to the users Control level
      if (it->getID() == id && userLevel <= it->getControlLevel())
         it->updateText(text);
}

/***********************************************
 * MESSAGES :: REMOVE
 * remove a single message
 **********************************************/
void Messages::remove(int id, Control userLevel)
{
   for (list <Message> :: iterator it = messages.begin();
        it != messages.end();
        ++it)
      //Only let the user remove a message is >= to the users Control level
      if (it->getID() == id && userLevel <= it->getControlLevel())
         it->clear();
}

/***********************************************
 * MESSAGES :: ADD
 * add a new message
 **********************************************/
void Messages::add(const string & text,
                   const string & author,
                   const string & date,
                   Control userControlLevel)
{
   Message message(text, author, date, userControlLevel);
   messages.push_back(message);
}

/***********************************************
 * MESSAGES :: READ MESSAGES
 * read the messages from a file
 ***********************************************/
void Messages::readMessages(const char * fileName)
{
   // open the file
   ifstream fin(fileName);
   if (fin.fail())
   {
      cout << "ERROR! Unable to open file "
           << fileName
           << endl;
      return;
   }

   // continue reading until we fail
   while (!fin.fail() && !fin.eof())
   {
      string author;
      string date;
      string text;
      string textControl;
      getline(fin, textControl, '|');
      getline(fin, author, '|');
      getline(fin, date, '|');
      getline(fin, text);


      std::cout << "test 01 " << textControl << "\n";
      //place textcontrol into temp Control var
      Control tempControl;
      if(textControl == "Public")
          tempControl = PUBLIC;
      else if(textControl == "Confidential")
        tempControl = CONFIDENTIAL;
      else if(textControl == "Privileged")
        tempControl = PRIVILEGED;
      else if(textControl == "Secret")
        tempControl = SECRET;

      std::cout << "Test " << tempControl << "\n";

      if (!fin.fail())
      {
         Message message(text, author, date, tempControl);
         messages.push_back(message);
      }
   }

   // close up shop!
   fin.close();
}
