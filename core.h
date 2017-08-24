#ifndef CORE_H_INCLUDED
#define CORE_H_INCLUDED

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

//Files

#define USR_DATA "files/usrdata.txt"
#define TMP_FILE "files/tmp.txt"

//Extremal sises

#define MAX_PRI 9
#define MIN_PRI 0
#define HIGH_PRI_MIN 7
#define MED_PRI_MAX 6
#define MED_PRI_MIN 3
#define LOW_PRI_MAX 2
#define DONE 1
#define UNDONE 0

using namespace std;


///Related to database
void AddData(int priority, int status, const string data);  //Add data                  +
void DeleteRecord(int position);                        //Delete one record             +
void DeleteAll();                                       //Delete all data               +
void DeleteStatus(int status);                          //Delete data with certain
                                                        //  status                      +
void DeletePriority(int pri_min, int pri_max);          //Delete all records with
                                                        //  priority between min_pri and
                                                        //  max_pri                     +
void SetPriority(int position, int priority);           //Change priority               +
void SetStatus(int position, int status);               //Change status                 +
string GetData(int position);                           //Get data                      +

//=======================================================================================

///Help-functions
int RecordsAmount();                                    //Returns amount of records     +


#endif // CORE_H_INCLUDED
