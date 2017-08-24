#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED

#include <iostream>
#include <fstream>
#include <cctype>
#include <cstdlib>

//Files' paths

#define INVITE "files/invite.txt"
#define USR_DEF_CMDS "files/usrdefcmds.txt"
#define CMDSSYN "files/cmdssyn.txt"
#define CMDSCLR "files/cmdsclr.txt"
#define TMP "files/tmp.txt"
#define HELP "files/help.txt"

//Errors

enum ERRORS {   TOO_MUCH = 1,
                ALREADY_EXIST,
                NO_SUCH_COMMAND,
                ORIGINAL_COMMAND,
                UNEXPECTED,
                OUT_OF_RANGE,
                NOT_ENOUGH_ARGUMENTS,
                INVALID_INPUT,
                ABORTED,
                DOT_BEFORE_UNDEF,
                NO_RECORDS,
                NO_SUCH_RECORDS,
                NO_CMDS_DEF
            };

//Colors

enum COLORS {   DEFAULT = 0,
                RED,
                GREEN,
                YELLOW,
                BLUE
            };

//Max size of commands and synonyms

#define MAX_CMDS 200
#define MAX_SYN  100
#define CMDS_AMNT 32                //Change if new commands added
#define MAX_STR_LEN 30

//Special commands' numbers in mask

#define UNKNOWN_CMD -1
#define QUOTED -2
#define NUMERIC -3

using namespace std;


///Work with input
string UserInput();                                     //Gets string, entered by User
                                                        //  No '^'                      +
string* InputToCommands(string input);                  //Returns array with commands,
                                                        //  makes substitutions         +
int* Parser(string* commands);                          //Completes syntax analysys and
                                                        //  returns command mask        +
bool Insurance();                                       //Asks user "Are you sure?"     +
void PasswordCheck();                                   //Checks user's password       -+
int ChangePassword();                                   //Changes password              -

//=======================================================================================

///Work with output
void Prompt();                                          //Prevent user about symbols
                                                        //  allowed, low register, etc  +
void Invite();                                          //Invites User                  +
void Bye();                                             //Says good bye                 +
void HelpPrint();                                       //Prints all commands           +
void ErrorWarning(int err_num = 0, string err_cmd = "");//Prints error, "succsessfully"
                                                        // if no arguments given        +
void RecordsHeader();                                   //Prints header for records     +
void RecordPrint(string record, int rec_num);           //Prints record                 +
void SynonymPrint();                                    //Prints whole dictionary       +
void CmdsDefPrint();                                    //Prints all user-defined
                                                        // commands                     +

//=======================================================================================

///Related to commands
int AddSynonym(string new_syn, string to_cmd);          //Add a synonym to a command    +
int DeleteSynonym(string del_syn);                      //Delete a synonym              +
int DefCommand(string new_cmd, string cmd_seq);         //Define new command            +
int UndefCommand(string del_cmd);                       //Delete defined command        +
void ChangeName(string new_name);                       //Changes user's name           +
void ChangeInvite(string new_inv);                      //Changes invite                +
void ChangeInvColor(int color_num);                     //Changes invite's color        +

//=======================================================================================

///Help functions
string* QuotesSep(string input);                        //Carries out quotes separation +
string* SpaceSep(string* raw_commands);                 //Craries out space separation  +
string* UsrDefSubst(string* raw_commands);              //Substitutes original commands
                                                        //  instead of user-defined     +
string* SynBrake(string syn_line);                      //Returns array of synonyms     +
bool IsNum(string cmd);                                 //Returns TRUE if command is
                                                        //number, else FALSE            +
int CommandsAmount();                                   //Returns amount of user-defined
                                                        //  commands                    +

#endif // INTERFACE_H_INCLUDED
