

/***********************************************************************
 * COMPONENT:
 *    INTERACT
 * Author:
 *    Br. Helfrich, Ben Smith, Bretton Steiner
 * Summary:
 *    This class allows one user to interact with the system
 ************************************************************************/

#pragma once

#include <string>     // for convenience
#include "messages.h" // to interact with the collection of messages
#include "control.h"  // all the Bell-LaPadula stuff

/**************************************************************
 * USER
 * All the users currently in the system
 *************************************************************/
struct User
{
   const char *name;
   const char *password;
   Control controlLevel;
};

/****************************************************
 * INTERACT
 * One user interacting with the system
 ***************************************************/
class Interact
{
public:
   Interact(const std::string & userName,
            const std::string & password,
            Messages & messages);

   // show a single message
   void show() const;
   void testCaseShow(int id) const;

   // display the set of messages
   void display() const;

   // add a single message
   void add();
   void testCaseAdd(const std::string & message, const std::string & date);

   // update a single message
   void update();
   void testCaseUpdate(int id, std::string & message);

   // remove one message from the list
   void remove();

   // authenticate the user;
   Control authenticate(const std::string & userName,
                     const std::string & password) const;

   //set control level
   void setUserControl(Control newControlLevel);

   //get userControl
   Control getUserControl();

private:
   Messages * pMessages;
   std::string userName;
   Control userControl;

   // prompt for a line of input
   std::string promptForLine(const char * verb) const;

   // prompt for a message ID
   int promptForId(const char * verb) const;


   // find the ID of a given user
   int idFromUser(const std::string & userName) const;

};

// display the set of users in the system
void displayUsers();
