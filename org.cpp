#include "org.h"

void Organizer()
{
    //Welcom user
    Prompt();
    //Ask for his password
    PasswordCheck();

    string* commands;                       //Array with commands (string)
    int* mask;                              //Array with commands' numbers

    //Run till user wants to quit
    bool quit = false;                      //User's wish to quit
    while(!quit){
        //Ask for command
        commands = InputToCommands(UserInput());
        //Get mask
        mask = Parser(commands);

        //Command processing
        switch (mask[0]){
            //Add
            case 1:{
                Add(mask, commands);
                break;
            }
            //Delete
            case 2:{
                Delete(mask, commands);
                break;
            }
            //Set
            case 3:{
                Set(mask, commands);
                break;
            }
            //Show
            case 4:{
                Show(mask, commands);
                break;
            }
            //Change
            case 5:{
                Change(mask, commands);
                break;
            }
            //Define
            case 6:{
                Define(mask, commands);
                break;
            }
            //Undefine
            case 7:{
                Undefine(mask, commands);
                break;
            }
            //Help
            case 8:{
                Help(mask, commands);
                break;
            }
            //Quit
            case 9:{
                quit = Quit(mask, commands);
                break;
            }
            //Invalid command
            default:{
                ErrorWarning(UNKNOWN_CMD, commands[0]);
                break;
            }
        }
    }
    //Preventing memory leak
    delete [] mask;
    //Say good bye
    Bye();
}

//
//=======================================================================================
//

void Add(int* mask, string* cmds)
{
    switch (mask[1]){
        //Not enough arguments
        case 0:{
            ErrorWarning(NOT_ENOUGH_ARGUMENTS);
            break;
        }
        //"Message"
        case QUOTED:{
            switch (mask[2]){
                //Сommand ended
                case 0:{
                    AddData(MIN_PRI, UNDONE, cmds[1]);
                    ErrorWarning();
                    break;
                }
                //<priority>
                case NUMERIC:{
                    switch (mask[3]){
                        //Command ended
                        case 0:{
                            //Check if priority lies not out of range
                            if(!OutOfRange(MIN_PRI, MAX_PRI, stoi(cmds[2]))){
                                AddData(stoi(cmds[2]), UNDONE, cmds[1]);
                                ErrorWarning();
                            }
                            else
                                ErrorWarning(OUT_OF_RANGE);
                            break;
                        }
                        //done
                        case 13:{
                            //Command ended
                            switch (mask[4]){
                                //Command ended
                                case 0:{
                                    //Check if priority is out of range
                                    if(!OutOfRange(MIN_PRI, MAX_PRI, stoi(cmds[2]))){
                                        AddData(stoi(cmds[2]), DONE, cmds[1]);
                                        ErrorWarning();
                                    }
                                    else
                                        ErrorWarning(OUT_OF_RANGE);
                                    break;
                                }
                                default:{
                                    ErrorWarning(UNEXPECTED, cmds[4]);
                                    break;
                                }
                            }
                            break;
                        }
                        //undone
                        case 14:{
                            switch (mask[4]){
                                //Command ended
                                case 0:{
                                    //If priority is not out of range
                                    if(!OutOfRange(MIN_PRI, MAX_PRI, stoi(cmds[2]))){
                                        AddData(stoi(cmds[2]), UNDONE, cmds[1]);
                                        ErrorWarning();
                                    }
                                    else
                                        ErrorWarning(OUT_OF_RANGE);
                                    break;
                                }
                                default:{
                                    ErrorWarning(UNEXPECTED, cmds[4]);
                                    break;
                                }
                            }
                            break;
                        }
                        default:{
                            ErrorWarning(INVALID_INPUT, cmds[3]);
                            break;
                        }
                    }
                    break;
                }
                //done
                case 13:{
                    switch (mask[3]){
                        //Command ended
                        case 0:{
                            AddData(MIN_PRI, DONE, cmds[1]);
                            ErrorWarning();
                            break;
                        }
                        //<priority>
                        case NUMERIC:{
                            switch (mask[4]){
                                //Command ended
                                case 0:{
                                    //Check if priority is out of range
                                    if(!OutOfRange(MIN_PRI, MAX_PRI, stoi(cmds[3]))){
                                        AddData(stoi(cmds[3]), DONE, cmds[1]);
                                        ErrorWarning();
                                    }
                                    else
                                        ErrorWarning(OUT_OF_RANGE);
                                    break;
                                }
                                default:{
                                    ErrorWarning(UNEXPECTED, cmds[4]);
                                    break;
                                }
                            }
                            break;
                        }
                        default:{
                            ErrorWarning(INVALID_INPUT, cmds[3]);
                            break;
                        }
                    }
                    break;
                }
                //undone
                case 14:{
                    switch (mask[3]){
                        //Command ended
                        case 0:{
                            AddData(MIN_PRI, UNDONE, cmds[1]);
                            ErrorWarning();
                            break;
                        }
                        //<priority>
                        case NUMERIC:{
                            switch (mask[4]){
                                //Command ended
                                case 0:{
                                    //Check if priority is out of range
                                    if(!OutOfRange(MIN_PRI, MAX_PRI, stoi(cmds[3]))){
                                        AddData(stoi(cmds[3]), UNDONE, cmds[1]);
                                        ErrorWarning();
                                    }
                                    else
                                        ErrorWarning(OUT_OF_RANGE);
                                    break;
                                }
                                default:{
                                    ErrorWarning(UNEXPECTED, cmds[4]);
                                    break;
                                }
                            }
                            break;
                        }
                        default:{
                            ErrorWarning(INVALID_INPUT, cmds[3]);
                            break;
                        }
                    }
                    break;
                }
                default:{
                    ErrorWarning(INVALID_INPUT, cmds[2]);
                    break;
                }
            }
            break;
        }
        //synonym
        case 23:{
            switch (mask[2]){
                //Command ended
                case 0:{
                    ErrorWarning(NOT_ENOUGH_ARGUMENTS);
                    break;
                }
                //Some number
                case NUMERIC:{
                    ErrorWarning(INVALID_INPUT, cmds[2]);
                    break;
                }
                //Quoted
                case QUOTED:{
                    ErrorWarning(INVALID_INPUT, cmds[2]);
                    break;
                }
                default:{
                    switch (mask[3]){
                        //Command ended
                        case 0:{
                            ErrorWarning(NOT_ENOUGH_ARGUMENTS);
                            break;
                        }
                        default:{
                            switch (mask[4]){
                                //Command ended
                                case 0:{
                                    ErrorWarning(AddSynonym(cmds[2], cmds[3]));
                                    break;
                                }
                                default:{
                                    ErrorWarning(UNEXPECTED, cmds[4]);
                                    break;
                                }
                            }
                            break;
                        }
                    }
                    break;
                }
            }
            break;
        }
        default:{
            ErrorWarning(INVALID_INPUT, cmds[1]);
            break;
        }
    }
}

void Delete(int* mask, string* cmds)
{
    switch (mask[1]){
        //Command ended
        case 0:{
            ErrorWarning(NOT_ENOUGH_ARGUMENTS);
            break;
        }
        //all
        case 10:{
            switch (mask[2]){
                //Command ended
                case 0:{
                    //Re-ask, if User's sure
                    if(Insurance()){
                        DeleteAll();
                        ErrorWarning();
                    }else
                        ErrorWarning(ABORTED);
                    break;
                }
                default:{
                    ErrorWarning(UNEXPECTED, cmds[2]);
                    break;
                }
            }
            break;
        }
        //status
        case 11:{
            switch (mask[2]){
                //Command ended
                case 0:{
                    ErrorWarning(NOT_ENOUGH_ARGUMENTS);
                    break;
                }
                //done
                case 13:{
                    switch (mask[3]){
                        //Command ended
                        case 0:{
                            //Re-ask
                            if(Insurance()){
                                DeleteStatus(DONE);
                                ErrorWarning();
                            }
                            else
                                ErrorWarning(ABORTED);
                            break;
                        }
                        default:{
                            ErrorWarning(UNEXPECTED, cmds[3]);
                            break;
                        }
                    }
                    break;
                }
                //undone
                case 14:{
                    switch (mask[3]){
                        //Command ended
                        case 0:{
                            //Re-ask
                            if(Insurance()){
                                DeleteStatus(UNDONE);
                                ErrorWarning();
                            }
                            else
                                ErrorWarning(ABORTED);
                            break;
                        }
                        default:{
                            ErrorWarning(UNEXPECTED, cmds[3]);
                            break;
                        }
                    }
                    break;
                }
                default:{
                    ErrorWarning(INVALID_INPUT, cmds[2]);
                    break;
                }
            }
            break;
        }
        //priority
        case 12:{
            switch (mask[2]){
                //Command ended
                case 0:{
                    ErrorWarning(NOT_ENOUGH_ARGUMENTS);
                    break;
                }
                //high
                case 15:{
                    switch (mask[3]){
                        //Command ended
                        case 0:{
                            //Re-ask
                            if(Insurance()){
                                DeletePriority(HIGH_PRI_MIN, MAX_PRI);
                                ErrorWarning();
                            }else
                                ErrorWarning(ABORTED);
                            break;
                        }
                        default:{
                            ErrorWarning(UNEXPECTED, cmds[3]);
                        }
                    }
                    break;
                }
                //medium
                case 16:{
                    switch (mask[3]){
                        //Command ended
                        case 0:{
                            //Re-ask
                            if(Insurance()){
                                DeletePriority(MED_PRI_MIN, MED_PRI_MAX);
                                ErrorWarning();
                            }else
                                ErrorWarning(ABORTED);
                            break;
                        }
                        default:{
                            ErrorWarning(UNEXPECTED, cmds[3]);
                        }
                    }
                    break;
                }
                //low
                case 17:{
                    switch (mask[3]){
                        //Command ended
                        case 0:{
                            //Re-ask
                            if(Insurance()){
                                DeletePriority(MIN_PRI, LOW_PRI_MAX);
                                ErrorWarning();
                            }else
                                ErrorWarning(ABORTED);
                            break;
                        }
                        default:{
                            ErrorWarning(UNEXPECTED, cmds[3]);
                        }
                    }
                    break;
                }
                //higher
                case 18:{
                    switch (mask[3]){
                        //Command ended
                        case 0:{
                            ErrorWarning(NOT_ENOUGH_ARGUMENTS);
                            break;
                        }
                        //<priority>
                        case NUMERIC:{
                            switch (mask[4]){
                                //Command ended
                                case 0:{
                                    //Check if <priority> lies not out of range
                                    if(!OutOfRange(MIN_PRI, MAX_PRI, stoi(cmds[3]))){
                                        //Re-ask
                                        if(Insurance()){
                                            DeletePriority(stoi(cmds[3]), MAX_PRI);
                                            ErrorWarning();
                                        }else
                                            ErrorWarning(ABORTED);
                                    }else
                                        ErrorWarning(OUT_OF_RANGE);
                                    break;
                                }
                                default:{
                                    ErrorWarning(UNEXPECTED, cmds[4]);
                                    break;
                                }
                            }
                            break;
                        }
                        default:{
                            ErrorWarning(INVALID_INPUT, cmds[3]);
                            break;
                        }
                    }
                    break;
                }
                //between
                case 19:{
                    switch (mask[3]){
                        //Command ended
                        case 0:{
                            ErrorWarning(NOT_ENOUGH_ARGUMENTS);
                            break;
                        }
                        //<priority_1>
                        case NUMERIC:{
                            switch (mask[4]){
                                //Command ended
                                case 0:{
                                    ErrorWarning(NOT_ENOUGH_ARGUMENTS);
                                    break;
                                }
                                //<priority_2>
                                case NUMERIC:{
                                    switch (mask[5]){
                                        //Command ended
                                        case 0:{
                                            //Check if priorities are not out of range
                                            if(!OutOfRange(MIN_PRI, MAX_PRI, stoi(cmds[3])) &&
                                               !OutOfRange(MIN_PRI, MAX_PRI, stoi(cmds[4]))){
                                                //Re-ask
                                                if(Insurance()){
                                                    //Finding min and max priority
                                                    int pri_min = MinNum(stoi(cmds[3]), stoi(cmds[4]));
                                                    int pri_max = MaxNum(stoi(cmds[3]), stoi(cmds[4]));

                                                    //Deleting
                                                    DeletePriority(pri_min, pri_max);
                                                    ErrorWarning();
                                                }else
                                                    ErrorWarning(ABORTED);
                                            }else
                                                ErrorWarning(OUT_OF_RANGE);
                                            break;
                                        }
                                        default:{
                                            ErrorWarning(UNEXPECTED, cmds[5]);
                                            break;
                                        }
                                    }
                                    break;
                                }
                                default:{
                                    ErrorWarning(INVALID_INPUT, cmds[4]);
                                    break;
                                }
                            }
                            break;
                        }
                        default:{
                            ErrorWarning(INVALID_INPUT, cmds[3]);
                            break;
                        }
                    }
                    break;
                }
                //lower
                case 20:{
                    switch (mask[3]){
                        //Command ended
                        case 0:{
                            ErrorWarning(NOT_ENOUGH_ARGUMENTS);
                            break;
                        }
                        //<priority>
                        case NUMERIC:{
                            switch (mask[4]){
                                //Command ended
                                case 0:{
                                    //Check if <priority> lies not out of range
                                    if(!OutOfRange(MIN_PRI, MAX_PRI, stoi(cmds[3]))){
                                        //Re-ask
                                        if(Insurance()){
                                            DeletePriority(MIN_PRI, stoi(cmds[3]));
                                            ErrorWarning();
                                        }else
                                            ErrorWarning(ABORTED);
                                    }else
                                        ErrorWarning(OUT_OF_RANGE);
                                    break;
                                }
                                default:{
                                    ErrorWarning(UNEXPECTED, cmds[4]);
                                    break;
                                }
                            }
                            break;
                        }
                        default:{
                            ErrorWarning(INVALID_INPUT, cmds[3]);
                            break;
                        }
                    }
                    break;
                }
                default:{
                    ErrorWarning(INVALID_INPUT, cmds[2]);
                    break;
                }
            }
            break;
        }
        //<position>
        case NUMERIC:{
            switch (mask[2]){
                //Command ended
                case 0:{
                    //Check if position is not out of range
                    if(0 <= stoi(cmds[1]) && stoi(cmds[1]) <= RecordsAmount() - 1){
                        //Re-ask
                        if(Insurance()){
                            DeleteRecord(stoi(cmds[1]));
                            ErrorWarning();
                        }else
                            ErrorWarning(ABORTED);
                    }else
                        ErrorWarning(OUT_OF_RANGE);
                    break;
                }
                default:{
                    ErrorWarning(UNEXPECTED, cmds[2]);
                    break;
                }
            }
            break;
        }
        //synonym
        case 23:{
            switch (mask[2]){
                //Command ended
                case 0:{
                    ErrorWarning(NOT_ENOUGH_ARGUMENTS);
                    break;
                }
                default:{
                    //Check if command starts with the dot
                    if(cmds[2][0] == '.'){
                        //Check if there are no extra commands
                        switch (mask[3]){
                            //Command ended
                            case 0:{
                                //Re-ask
                                if(Insurance()){
                                    //Deleting previous symbol
                                    string del_syn = cmds[2].substr(1);
                                    //Deleting synonym
                                    ErrorWarning(DeleteSynonym(del_syn));
                                }else
                                    ErrorWarning(ABORTED);
                                break;
                            }
                            default:{
                                ErrorWarning(UNEXPECTED, cmds[3]);
                                break;
                            }
                        }
                    }else
                        ErrorWarning(DOT_BEFORE_UNDEF);
                    break;
                }
            }
            break;
        }
        default:{
            ErrorWarning(INVALID_INPUT, cmds[1]);
            break;
        }
    }
}

void Set(int* mask, string* cmds)
{
    switch (mask[1]){
        //Command ended
        case 0:{
            ErrorWarning(NOT_ENOUGH_ARGUMENTS);
            break;
        }
        //status
        case 11:{
            switch (mask[2]){
                //Command ended
                case 0:{
                    ErrorWarning(NOT_ENOUGH_ARGUMENTS);
                    break;
                }
                //<position>
                case NUMERIC:{
                    switch (mask[3]){
                        //Command ended
                        case 0:{
                            ErrorWarning(NOT_ENOUGH_ARGUMENTS);
                            break;
                        }
                        //done
                        case 13:{
                            switch (mask[4]){
                                //Command ended
                                case 0:{
                                    //Check if position is not out of range
                                    if(!OutOfRange(0, RecordsAmount() - 1, stoi(cmds[2]))){
                                        SetStatus(stoi(cmds[2]), DONE);
                                        ErrorWarning();
                                    }else
                                        ErrorWarning(OUT_OF_RANGE);
                                    break;
                                }
                                default:{
                                    ErrorWarning(UNEXPECTED, cmds[4]);
                                }
                            }
                            break;
                        }
                        //undone
                        case 14:{
                            switch (mask[4]){
                                //Command ended
                                case 0:{
                                    //Check if position is not out of range
                                    if(!OutOfRange(0, RecordsAmount() - 1, stoi(cmds[2]))){
                                        SetStatus(stoi(cmds[2]), UNDONE);
                                        ErrorWarning();
                                    }else
                                        ErrorWarning(OUT_OF_RANGE);
                                    break;
                                }
                                default:{
                                    ErrorWarning(UNEXPECTED, cmds[4]);
                                }
                            }
                            break;
                        }
                        default:{
                            ErrorWarning(INVALID_INPUT, cmds[3]);
                            break;
                        }
                    }
                    break;
                }
                //all
                case 10:{
                    switch (mask[3]){
                        //Command ended
                        case 0:{
                            ErrorWarning(NOT_ENOUGH_ARGUMENTS);
                            break;
                        }
                        //done
                        case 13:{
                            switch (mask[4]){
                                //Command ended
                                case 0:{
                                    //Changing everything
                                    for(int i = 0; i < RecordsAmount(); i++)
                                        SetStatus(i, DONE);
                                    ErrorWarning();
                                    break;
                                }
                                default:{
                                    ErrorWarning(UNEXPECTED, cmds[4]);
                                    break;
                                }
                            }
                            break;
                        }
                        //undone
                        case 14:{
                            switch (mask[4]){
                                //Command ended
                                case 0:{
                                    //Changing everything
                                    for(int i = 0; i < RecordsAmount(); i++)
                                        SetStatus(i, UNDONE);
                                    ErrorWarning();
                                    break;
                                }
                                default:{
                                    ErrorWarning(UNEXPECTED, cmds[4]);
                                    break;
                                }
                            }
                            break;
                        }
                        default:{
                            ErrorWarning(INVALID_INPUT, cmds[3]);
                            break;
                        }
                    }
                    break;
                }
                default:{
                    ErrorWarning(INVALID_INPUT, cmds[2]);
                    break;
                }
            }
            break;
        }
        //priority
        case 12:{
            switch (mask[2]){
                //Command ended
                case 0:{
                    ErrorWarning(NOT_ENOUGH_ARGUMENTS);
                    break;
                }
                //<position>
                case NUMERIC:{
                    switch (mask[3]){
                        //Command ended
                        case 0:{
                            ErrorWarning(NOT_ENOUGH_ARGUMENTS);
                            break;
                        }
                        //<priority>
                        case NUMERIC:{
                            switch (mask[4]){
                                //Command ended
                                case 0:{
                                    //Check if priority and position are not out of range
                                    if(!OutOfRange(0, RecordsAmount() - 1, stoi(cmds[2])) &&
                                       !OutOfRange(MIN_PRI, MAX_PRI, stoi(cmds[3]))){
                                        //Changing
                                        SetPriority(stoi(cmds[2]), stoi(cmds[3]));
                                        ErrorWarning();
                                    }else
                                        ErrorWarning(OUT_OF_RANGE);
                                    break;
                                }
                                default:{
                                    ErrorWarning(UNEXPECTED, cmds[4]);
                                    break;
                                }
                            }
                            break;
                        }
                        default:{
                            ErrorWarning(INVALID_INPUT, cmds[3]);
                            break;
                        }
                    }
                    break;
                }
                default:{
                    ErrorWarning(INVALID_INPUT, cmds[2]);
                    break;
                }
            }
            break;
        }
        default:{
            ErrorWarning(INVALID_INPUT, cmds[1]);
            break;
        }
    }
}

void Show(int* mask, string* cmds)
{
    switch (mask[1]){
        //Command ended
        case 0:{
            ErrorWarning(NOT_ENOUGH_ARGUMENTS);
            break;
        }
        //all
        case 10:{
            switch (mask[2]){
                //Command ended
                case 0:{
                    RecordsHeader();
                    //Check if there are any records
                    if(RecordsAmount() != 0){
                        //Printing whole table
                        for(int i = 0; i < RecordsAmount(); i++)
                            RecordPrint(GetData(i), i);
                    }else
                        ErrorWarning(NO_RECORDS);
                    break;
                }
                default:{
                    ErrorWarning(UNEXPECTED, cmds[2]);
                    break;
                }
            }
            break;
        }
        //status
        case 11:{
            switch (mask[2]){
                //Command ended
                case 0:{
                    ErrorWarning(NOT_ENOUGH_ARGUMENTS);
                    break;
                }
                //done
                case 13:{
                    switch (mask[3]){
                        //Command ended
                        case 0:{
                            RecordsHeader();
                            int rec_printed = 0;
                            //Printing the whole table
                            for(int i = 0; i < RecordsAmount(); i++){
                                //Check if status is correct
                                string record = GetData(i);
                                if(stoi(record.substr(2, 1)) == DONE){
                                    //Printing
                                    RecordPrint(record, i);
                                    rec_printed++;
                                }
                            }
                            //If we have printed nothing
                            if(rec_printed == 0)
                                ErrorWarning(NO_SUCH_RECORDS);
                            break;
                        }
                        default:{
                            ErrorWarning(UNEXPECTED, cmds[3]);
                            break;
                        }
                    }
                    break;
                }
                //undone
                case 14:{
                    switch (mask[3]){
                        //Command ended
                        case 0:{
                            RecordsHeader();
                            int rec_printed = 0;
                            //Printing the whole table
                            for(int i = 0; i < RecordsAmount(); i++){
                                //Check if status is correct
                                string record = GetData(i);
                                if(stoi(record.substr(2, 1)) == UNDONE){
                                    //Printing
                                    RecordPrint(record, i);
                                    rec_printed++;
                                }
                            }
                            //If we have printed nothing
                            if(rec_printed == 0)
                                ErrorWarning(NO_SUCH_RECORDS);
                            break;
                        }
                        default:{
                            ErrorWarning(UNEXPECTED, cmds[3]);
                            break;
                        }
                    }
                    break;
                }
                default:{
                    ErrorWarning(INVALID_INPUT, cmds[2]);
                    break;
                }
            }
            break;
        }
        //priority
        case 12:{
            switch (mask[2]){
                //Command ended
                case 0:{
                    ErrorWarning(NOT_ENOUGH_ARGUMENTS);
                    break;
                }
                //high
                case 15:{
                    switch (mask[3]){
                        //Command ended
                        case 0:{
                            RecordsHeader();
                            int rec_printed = 0;
                            //Printing only records with correct priority
                            for(int i = 0; i < RecordsAmount(); i++){
                                string record = GetData(i);
                                //Printing only if priority is correct
                                if(HIGH_PRI_MIN <= stoi(record.substr(0, 1))){
                                    //Printing
                                    RecordPrint(record, i);
                                    rec_printed++;
                                }
                            }
                            //Check if we have printed nothing
                            if(rec_printed == 0)
                                ErrorWarning(NO_SUCH_RECORDS);
                            break;
                        }
                        default:{
                            ErrorWarning(UNEXPECTED, cmds[3]);
                            break;
                        }
                    }
                    break;
                }
                //medium
                case 16:{
                    switch (mask[3]){
                        //Command ended
                        case 0:{
                            RecordsHeader();
                            int rec_printed = 0;
                            //Printing only records with correct priority
                            for(int i = 0; i < RecordsAmount(); i++){
                                string record = GetData(i);
                                //Printing only if priority is correct
                                if(MED_PRI_MIN <= stoi(record.substr(0, 1)) &&
                                   MED_PRI_MAX >= stoi(record.substr(0, 1))){
                                    //Printing
                                    RecordPrint(record, i);
                                    rec_printed++;
                                }
                            }
                            //Check if we have printed nothing
                            if(rec_printed == 0)
                                ErrorWarning(NO_SUCH_RECORDS);
                            break;
                        }
                        default:{
                            ErrorWarning(UNEXPECTED, cmds[3]);
                            break;
                        }
                    }
                    break;
                }
                //low
                case 17:{
                    switch (mask[3]){
                        //Command ended
                        case 0:{
                            RecordsHeader();
                            int rec_printed = 0;
                            //Printing only records with correct priority
                            for(int i = 0; i < RecordsAmount(); i++){
                                string record = GetData(i);
                                //Printing only if priority is correct
                                if(LOW_PRI_MAX >= stoi(record.substr(0, 1))){
                                    //Printing
                                    RecordPrint(record, i);
                                    rec_printed++;
                                }
                            }
                            //Check if we have printed nothing
                            if(rec_printed == 0)
                                ErrorWarning(NO_SUCH_RECORDS);
                            break;
                        }
                        default:{
                            ErrorWarning(UNEXPECTED, cmds[3]);
                            break;
                        }
                    }
                    break;
                }
                //higher
                case 18:{
                    switch (mask[3]){
                        //Command ended
                        case 0:{
                            ErrorWarning(NOT_ENOUGH_ARGUMENTS);
                            break;
                        }
                        //<priority>
                        case NUMERIC:{
                            switch (mask[4]){
                                //Command ended
                                case 0:{
                                    //Check if priority is not out of range
                                    if(!OutOfRange(MIN_PRI, MAX_PRI, stoi(cmds[3]))){
                                        RecordsHeader();
                                        int pri = stoi(cmds[3]);
                                        int rec_printed = 0;
                                        //Running through database
                                        for(int i = 0; i < RecordsAmount(); i++){
                                            string record = GetData(i);
                                            //Check if priority's correct
                                            if(stoi(record.substr(0, 1)) >= pri){
                                                RecordPrint(record, i);
                                                rec_printed++;
                                            }
                                        }
                                        //Check if we have printed anything
                                        if(rec_printed == 0)
                                            ErrorWarning(NO_SUCH_RECORDS);
                                    }else
                                        ErrorWarning(OUT_OF_RANGE);
                                    break;
                                }
                                default:{
                                    ErrorWarning(UNEXPECTED, cmds[4]);
                                    break;
                                }
                            }
                            break;
                        }
                        default:{
                            ErrorWarning(INVALID_INPUT, cmds[3]);
                            break;
                        }
                    }
                    break;
                }
                //between
                case 19:{
                    switch (mask[3]){
                        //Command ended
                        case 0:{
                            ErrorWarning(NOT_ENOUGH_ARGUMENTS);
                            break;
                        }
                        //<priority_1>
                        case NUMERIC:{
                            switch (mask[4]){
                                //Command ended
                                case 0:{
                                    ErrorWarning(NOT_ENOUGH_ARGUMENTS);
                                    break;
                                }
                                //<priority_2>
                                case NUMERIC:{
                                    switch (mask[5]){
                                        //Command ended
                                        case 0:{
                                            //Check if numbers are not out of range
                                            if(!OutOfRange(MIN_PRI, MAX_PRI, stoi(cmds[3])) &&
                                               !OutOfRange(MIN_PRI, MAX_PRI, stoi(cmds[4]))){
                                                //Printing
                                                RecordsHeader();
                                                int min_pri = MinNum(stoi(cmds[3]), stoi(cmds[4]));
                                                int max_pri = MaxNum(stoi(cmds[3]), stoi(cmds[4]));
                                                int rec_printed = 0;
                                                //Running through the database
                                                for(int i = 0; i < RecordsAmount(); i++){
                                                    string record = GetData(i);
                                                    //Check if priority's correct
                                                    if(stoi(record.substr(0, 1)) >= min_pri &&
                                                       stoi(record.substr(0, 1)) <= max_pri){
                                                        RecordPrint(record, i);
                                                        rec_printed++;
                                                    }
                                                }
                                                //Check if we have printed anything
                                                if(rec_printed == 0)
                                                    ErrorWarning(NO_SUCH_RECORDS);
                                            }else
                                                ErrorWarning(OUT_OF_RANGE);
                                            break;
                                        }
                                        default:{
                                            ErrorWarning(UNEXPECTED, cmds[5]);
                                            break;
                                        }
                                    }
                                    break;
                                }
                                default:{
                                    ErrorWarning(INVALID_INPUT, cmds[4]);
                                    break;
                                }
                            }
                            break;
                        }
                        default:{
                            ErrorWarning(INVALID_INPUT, cmds[3]);
                            break;
                        }
                    }
                    break;
                }
                //lower
                case 20:{
                    switch (mask[3]){
                        //Command ended
                        case 0:{
                            ErrorWarning(NOT_ENOUGH_ARGUMENTS);
                            break;
                        }
                        //<priority>
                        case NUMERIC:{
                            switch (mask[4]){
                                //Command ended
                                case 0:{
                                    //Check if priority is not out of range
                                    if(!OutOfRange(MIN_PRI, MAX_PRI, stoi(cmds[3]))){
                                        RecordsHeader();
                                        int pri = stoi(cmds[3]);
                                        int rec_printed = 0;
                                        //Running through database
                                        for(int i = 0; i < RecordsAmount(); i++){
                                            string record = GetData(i);
                                            //Check if priority's correct
                                            if(stoi(record.substr(0, 1)) <= pri){
                                                RecordPrint(record, i);
                                                rec_printed++;
                                            }
                                        }
                                        //Check if we have printed anything
                                        if(rec_printed == 0)
                                            ErrorWarning(NO_SUCH_RECORDS);
                                    }else
                                        ErrorWarning(OUT_OF_RANGE);
                                    break;
                                }
                                default:{
                                    ErrorWarning(UNEXPECTED, cmds[4]);
                                    break;
                                }
                            }
                            break;
                        }
                        default:{
                            ErrorWarning(INVALID_INPUT, cmds[3]);
                            break;
                        }
                    }
                    break;
                }
                //decrease
                case 21:{
                    switch (mask[3]){
                        //Command ended
                        case 0:{
                            RecordsHeader();
                            //Check if user has records
                            if(RecordsAmount() != 0){
                                //Taking every priority
                                for(int pri = MAX_PRI; pri >= MIN_PRI; pri--){
                                    //Running through the database
                                    for(int i = 0; i < RecordsAmount(); i++){
                                        string record = GetData(i);
                                        //Check if record's priority is current (pri)
                                        if(stoi(record.substr(0, 1)) == pri)
                                            RecordPrint(record, i);
                                    }
                                }
                            }else
                                ErrorWarning(NO_RECORDS);
                            break;
                        }
                        default:{
                            ErrorWarning(UNEXPECTED, cmds[3]);
                            break;
                        }
                    }
                    break;
                }
                //increase
                case 22:{
                    switch (mask[3]){
                        //Command ended
                        case 0:{
                            RecordsHeader();
                            //Check if user has records
                            if(RecordsAmount() != 0){
                                //Taking every priority
                                for(int pri = MIN_PRI; pri <= MAX_PRI; pri++){
                                    //Running through the database
                                    for(int i = 0; i < RecordsAmount(); i++){
                                        string record = GetData(i);
                                        //Check if record's priority is current (pri)
                                        if(stoi(record.substr(0, 1)) == pri)
                                            RecordPrint(record, i);
                                    }
                                }
                            }else
                                ErrorWarning(NO_RECORDS);
                            break;
                        }
                        default:{
                            ErrorWarning(UNEXPECTED, cmds[3]);
                            break;
                        }
                    }
                    break;
                }
                default:{
                    ErrorWarning(INVALID_INPUT, cmds[2]);
                    break;
                }
            }
            break;
        }
        //synonym
        case 23:{
            switch (mask[2]){
                //Command ended
                case 0:{
                    SynonymPrint();
                    break;
                }
                default:{
                    ErrorWarning(UNEXPECTED, cmds[2]);
                    break;
                }
            }
            break;
        }
        //define
        case 6:{
            switch (mask[2]){
                //Command ended
                case 0:{
                    //Check if there are any commands exist
                    if(CommandsAmount() != 0)
                        CmdsDefPrint();
                    else
                        ErrorWarning(NO_CMDS_DEF);
                    break;
                }
                default:{
                    ErrorWarning(UNEXPECTED, cmds[2]);
                    break;
                }
            }
            break;
        }
        default:{
            ErrorWarning(INVALID_INPUT, cmds[1]);
            break;
        }
    }
}

void Change(int* mask, string* cmds)
{
    switch (mask[1]){
        //Command ended
        case 0:{
            ErrorWarning(NOT_ENOUGH_ARGUMENTS);
            break;
        }
        //password
        case 24:{
            switch (mask[2]){
                //Command ended
                case 0:{
                    ErrorWarning(ChangePassword());
                    break;
                }
                default:{
                    ErrorWarning(UNEXPECTED, cmds[2]);
                    break;
                }
            }
            break;
        }
        //name
        case 25:{
            switch (mask[2]){
                //Command ended
                case 0:{
                    ErrorWarning(NOT_ENOUGH_ARGUMENTS);
                    break;
                }
                default:{
                    switch (mask[3]){
                        //Command ended
                        case 0:{
                            ChangeName(cmds[2]);
                            ErrorWarning();
                            break;
                        }
                        default:{
                            ErrorWarning(UNEXPECTED, cmds[3]);
                            break;
                        }
                    }
                    break;
                }
            }
            break;
        }
        //invite
        case 26:{
            switch (mask[2]){
                //Command ended
                case 0:{
                    ErrorWarning(NOT_ENOUGH_ARGUMENTS);
                    break;
                }
                //color
                case 27:{
                    switch (mask[3]){
                        //Command ended
                        case 0:{
                            ErrorWarning(NOT_ENOUGH_ARGUMENTS);
                            break;
                        }
                        //default
                        case 28:{
                            switch (mask[4]){
                                //Command ended
                                case 0:{
                                    ChangeInvColor(DEFAULT);
                                    break;
                                }
                                default:{
                                    ErrorWarning(UNEXPECTED, cmds[4]);
                                    break;
                                }
                            }
                            break;
                        }
                        //red
                        case 29:{
                            switch (mask[4]){
                                //Command ended
                                case 0:{
                                    ChangeInvColor(RED);
                                    break;
                                }
                                default:{
                                    ErrorWarning(UNEXPECTED, cmds[4]);
                                    break;
                                }
                            }
                            break;
                        }
                        //green
                        case 30:{
                            switch (mask[4]){
                                //Command ended
                                case 0:{
                                    ChangeInvColor(GREEN);
                                    break;
                                }
                                default:{
                                    ErrorWarning(UNEXPECTED, cmds[4]);
                                    break;
                                }
                            }
                            break;
                        }
                        //yellow
                        case 31:{
                            switch (mask[4]){
                                //Command ended
                                case 0:{
                                    ChangeInvColor(YELLOW);
                                    break;
                                }
                                default:{
                                    ErrorWarning(UNEXPECTED, cmds[4]);
                                    break;
                                }
                            }
                            break;
                        }
                        //blue
                        case 32:{
                            switch (mask[4]){
                                //Command ended
                                case 0:{
                                    ChangeInvColor(BLUE);
                                    break;
                                }
                                default:{
                                    ErrorWarning(UNEXPECTED, cmds[4]);
                                    break;
                                }
                            }
                            break;
                        }
                        default:{
                            ErrorWarning(INVALID_INPUT, cmds[3]);
                            break;
                        }
                    }
                    break;
                }
                default:{
                    switch (mask[3]){
                        //Command ended
                        case 0:{
                            ChangeInvite(cmds[2]);
                            break;
                        }
                        default:{
                            ErrorWarning(UNEXPECTED, cmds[3]);
                            break;
                        }
                    }
                    break;
                }
            }
            break;
        }
        default:{
            ErrorWarning(INVALID_INPUT, cmds[1]);
            break;
        }
    }
}

void Define(int* mask, string* cmds)
{
    switch (mask[1]){
        //Command ended
        case 0:{
            ErrorWarning(NOT_ENOUGH_ARGUMENTS);
            break;
        }
        //Some number
        case NUMERIC:{
            ErrorWarning(INVALID_INPUT, cmds[1]);
            break;
        }
        //Quoted
        case QUOTED:{
            ErrorWarning(INVALID_INPUT, cmds[1]);
            break;
        }
        default:{
            switch (mask[2]){
                //Command ended
                case 0:{
                    ErrorWarning(NOT_ENOUGH_ARGUMENTS);
                    break;
                }
                default:{
                    //Placing command in file
                    //Creating substitution for command to place it in file
                    string cmd_sequence = cmds[2];
                    int cmd_num = 3;                //Counter for mask-array
                    while(mask[cmd_num] != 0){
                        cmd_sequence = cmd_sequence + " " + cmds[cmd_num];
                        //Going for next command
                        cmd_num++;
                    }
                    //Placing it in the file
                    ErrorWarning(DefCommand(cmds[1], cmd_sequence), "");
                    break;
                }
            }
            break;
        }
    }
}

void Undefine(int* mask, string* cmds)
{
    switch (mask[1]){
        //Command ended
        case 0:{
            ErrorWarning(NOT_ENOUGH_ARGUMENTS);
            break;
        }
        default:{
            //Check if command started with the dot
            if(cmds[1][0] == '.'){
                //Check if there are no extra commands
                switch (mask[2]){
                    //Command ended
                    case 0:{
                        //Re-ask
                        if(Insurance()){
                            //Deleting previous symbol
                            string del_cmd = cmds[1].substr(1);
                            //Undefinig command
                            ErrorWarning(UndefCommand(del_cmd));
                        }else
                            ErrorWarning(ABORTED);
                        break;
                    }
                    default:{
                        ErrorWarning(UNEXPECTED, cmds[2]);
                        break;
                    }
                }
            }else
                ErrorWarning(DOT_BEFORE_UNDEF);
            break;
        }
    }
}

void Help(int* mask, string* cmds)
{
    switch (mask[1]){
        //Command ended
        case 0:{
            HelpPrint();
            break;
        }
        default:{
            ErrorWarning(UNEXPECTED, cmds[1]);
            break;
        }
    }
}

bool Quit(int* mask, string* cmds)
{
    switch (mask[1]){
        //Command ended
        case 0:{
            //Re-ask
            if(Insurance()){
                return true;
            }
            //If "NO", abort
            ErrorWarning(ABORTED);
            return false;
            break;
        }
        default:{
            ErrorWarning(UNEXPECTED, cmds[1]);
            break;
        }
    }
    //User can not be here
    return true;
}

//
//=======================================================================================
//

bool OutOfRange(int min_num, int max_num, int num)
{
    if(num >= min_num && num <= max_num)
        return false;
    return true;
}

int MinNum(int num_1, int num_2)
{
    if(num_1 < num_2)
        return num_1;
    return num_2;
}

int MaxNum(int num_1, int num_2)
{
    if(num_1 < num_2)
        return num_2;
    return num_1;
}

