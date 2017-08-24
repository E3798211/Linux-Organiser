#ifndef ORG_H_INCLUDED
#define ORG_H_INCLUDED

#include "core.h"
#include "interface.h"

using namespace std;

void Organizer();                                       //Main function. Executes
                                                        //  everything

//=======================================================================================

///Main functions
void Add(int* mask, string* cmds);                      //  ------------------------    +
void Delete(int* mask, string* cmds);                   //  ------------------------    +
void Set(int* mask, string* cmds);                      //  ------------------------    +
void Show(int* mask, string* cmds);                     //  ------------------------    +
void Change(int* mask, string* cmds);
void Define(int* mask, string* cmds);                   //  ------------------------    +
void Undefine(int* mask, string* cmds);                 //  ------------------------    +
void Help(int* mask, string* cmds);                     //  ------------------------    +
bool Quit(int* mask, string* cmds);                     //  ------------------------    +

//=======================================================================================

///Help functions
bool OutOfRange(int min_num, int max_num, int num);     //Checks if number is out of range
int MinNum(int num_1, int num_2);                       //Returns minimum of num_1 and
                                                        //  num_2
int MaxNum(int num_1, int num_2);                       //Returns maximum of num_1 and
                                                        //  num_2

#endif // ORG_H_INCLUDED
