#include "interface.h"

string UserInput()
{
    string input;                           //User's input
    bool input_empty;                       //Input's status
    bool wrong_character;                   //Existence of '^'

    //Asking for commands until it is not empty
    do{
        //Assking for a command
        Invite();
        getline(cin, input);

        //Checking if it's empty
        if(input.empty())
            input_empty = true;
        else
            input_empty = false;

        //Checking if it contains '^'
        if(input.find('^') == string::npos)
            wrong_character = false;
        else
            wrong_character = true;

        //Warnings about mistakes
        if(input_empty)
            cout << "\tPlease, do not send empty messages." << endl;
        if(wrong_character)
            cout << "\tPlease, do not use '^'." << endl;
    }while(input_empty || wrong_character);

    //Returning user's input
    return input;
}

string* InputToCommands(string input)
{
    /*First  - finding qoutes and (?) warning about unclosed qoutes.
     *Second - clearing spaces.
     *Third  - finding user-defined commands and replacing them with original.
     *Forth  - finding quotes again.
     *Fifth  - crearing spaces.
     */

    //First three steps
    string* cmds_third = UsrDefSubst(SpaceSep(QuotesSep(input)));

    //Placing everything back again in one line to put it in QuotesSep
    string cmd_line;                            //Line to contain full command separeted with spaces again
    int cmd_num = 0;                            //Counter for commands
    //Running through commands till they end
    while(!cmds_third[cmd_num].empty()){
        //Placing next word in a command to the line
        cmd_line = cmd_line + cmds_third[cmd_num] + " ";
        //Going for next iteration
        cmd_num++;
    }

    //Last two steps of processing
    return SpaceSep(QuotesSep(cmd_line));
}

int* Parser(string* commands)
///Functions nums start with 1, 0 = empty string
{
    ifstream reserved_cmds(CMDSSYN);            //In-stream to commands-file
    int* mask = new int [MAX_CMDS];             //Mask of user's request
    for(int i = 0; i < MAX_CMDS; i++)
        mask[i] = 0;
    string all_synonyms;                        //String to consist all synonyms
    string* synonyms;                           //Amount of synonyms

    //Running through user's commands
    int usr_cmd_num = 0;                                //Number of user's command
    while(!commands[usr_cmd_num].empty()){
        //Set pointer to the beginning
        reserved_cmds.seekg(0, reserved_cmds.beg);

        //Finding number of command. If nothing fitted,
        //LAST_CMD appropriated
        int command_mask = 1;                           //Command's mask (corresponding num)
        bool cmd_found = false;                         //Status of command in user's request
        while(!reserved_cmds.eof()){
            //Taking command with its synonyms
            getline(reserved_cmds, all_synonyms);
            //Brake line with synonyms in synonyms themselves
            synonyms = SynBrake(all_synonyms);

            //Running through synonyms and comparing them with
            //user's words
            int synon_num = 0;                          //Counter for synonyms
            while(!synonyms[synon_num].empty()){
                //If concurrence happened
                if(synonyms[synon_num] == commands[usr_cmd_num]){
                    cmd_found = true;
                    mask[usr_cmd_num] = command_mask;
                }
                synon_num++;
            }
            //If concurrence hasn't happened
            if(!cmd_found){
                cmd_found = false;
                mask[usr_cmd_num] = UNKNOWN_CMD;
            }
            command_mask++;
        }

        //Going for next word in user command
        reserved_cmds.clear();
        usr_cmd_num++;
    }

    //Unknown command processing
    usr_cmd_num = 0;
    while(!mask[usr_cmd_num] == 0){
        //Looking for unknown commands
        if(mask[usr_cmd_num] == UNKNOWN_CMD){
            //If command is quoted input
            if(commands[usr_cmd_num][0] == '\"')
                mask[usr_cmd_num] = QUOTED;
            //If commands are numbers
            else if(IsNum(commands[usr_cmd_num]))
                mask[usr_cmd_num] = NUMERIC;
            //Else command is really unknown
        }
        //Going for next word in command
        usr_cmd_num++;
    }

    delete [] synonyms;
    return mask;
}

bool Insurance()
{
    string inv;                                 //Invitation
    string usr_ans;                             //User's answer

    cout << "\tAre you sure? <Y> - yes, <N> - no." << endl;

    while(1){
        Invite();
        //User's input
        getline(cin, usr_ans);
        //Check
        if( usr_ans == "y" || usr_ans == "Y" ||
            usr_ans == "yes" || usr_ans == "Yes")
            return true;
        else if(usr_ans == "n" || usr_ans == "N" ||
                 usr_ans == "no" || usr_ans == "No")
            return false;
        else
            cout << "\tInvalid enter." << endl;
    }
}

void PasswordCheck()
{
    ifstream invite(INVITE);                    //Stream to file with password
    string psw;                                 //Line with password
    string name;                                //Line with name
    string usr_try;

    //Getting password
    getline(invite, psw);
    getline(invite, psw);

    cout << "\tEnter password:" << endl;

    while(1){
        Invite();
        //User's input
        getline(cin, usr_try);
        //Check
        if(usr_try == psw){
            //Greetings
            getline(invite, name);
            cout << "\tWelcom, " << name << "!" << endl;
            break;
        }else
            cout << "\tOops... Try again." << endl;
    }
}

int ChangePassword()
{
    ifstream i_invite(INVITE);                      //In-stream into invite-file
    string psw;                                     //Password
    string usr_input;

    //Getting password
    getline(i_invite, psw);
    getline(i_invite, psw);

    //Ask for password
    cout << "\tEnter current password:" << endl;
    Invite();
    getline(cin, usr_input);

    //Check if it is correct
    if(usr_input != psw){
        cout << "\tIncorrect." << endl;
        return ABORTED;
    }
    //If correct, ask if User's sure
    cout << "\tCorrect. You are going to change password." << endl;
    if(!Insurance()){
        return ABORTED;
    }
    //If user's sure, ask twice for new password
    string new_psw_1, new_psw_2;                            //Strings for new passwords
    bool empty_input = true;                                //Check if input is empty

    //First ask
    cout << "\tEnter new password:" << endl;
    while(empty_input){
        cout << "\tPassword can not be empty." << endl;
        Invite();
        getline(cin, new_psw_1);
        //Check if input's empty
        if(!new_psw_1.empty())
            empty_input = false;
    }
    //Second ask
    //Warning
    cout << "\tEnter new password again.\n\tBe careful. In case of non-concurrence procedure will be aborted." << endl;
    //Getting new pasword again
    Invite();
    getline(cin, new_psw_2);

    //Check if user hasn't mistaken
    if(new_psw_1 != new_psw_2)
        return ABORTED;

    //If everything is ok, changing password
    //Resetting pointer in invite-file
    i_invite.clear();
    i_invite.seekg(0, i_invite.beg);
    //Creating tmp file
    ofstream o_tmp(TMP);

    string line;
    //Copeing everything from invite-file to tmp
    for(int i = 0; i < 3; i++){
        getline(i_invite, line);
        o_tmp << line << "\n";
    }
    //Clearing invite-file
    i_invite.close();
    ofstream o_invite(INVITE, ios::trunc);
    //Resetting tmp
    o_tmp.close();
    ifstream i_tmp(TMP);

    //Copeing everithing back
    //Placing first one
    getline(i_tmp, line);
    o_invite << line << "\n";
    //Placing new password
    o_invite << new_psw_2 << "\n";
    //Placing last line
    getline(i_tmp, line);
    getline(i_tmp, line);
    o_invite << line;

    //Deleting tmp file
    o_invite.close();
    i_tmp.close();
    remove(TMP);

    //Success
    return 0;
}

//
//=======================================================================================
//

void Prompt()
{
    cout << "\tWelcome! Here are couple of rules.\n\tIgnoring may lead to missunderstanding." << endl;
    cout << "\t1. Use low register" << endl;
    cout << "\t2. Do not use symbol '^'" << endl;
    cout << "\t3. Your functions should only consist of alphabet letters and" << endl;
    cout << "\t   Symbols '-' or '_'" << endl;
    cout << "\t   Example: \"my_function\", \"my-function\"" << endl;
    cout << "\t4. Write numbers carefully or you might be missunderstood" << endl;
    cout << "\t5. Try \"help\" in case you need help" << endl;
    cout << endl;
}

void Invite()
{
    ifstream invite(INVITE);                //In-stream to invite file
    string invitation;                      //Here lies invitation

    //Getting invitation
    invite >> invitation;
    //Getting colors and invitation separately
    string* inv = SynBrake(invitation);

    //Changing invitation's color
    if(stoi(inv[0]) == 0)
        cout << "\x1b[0m";                  //Default
    else if(stoi(inv[0]) == 1)
        cout << "\x1b[31m";                 //Red
    else if(stoi(inv[0]) == 2)
        cout << "\x1b[32m";                 //Green
    else if(stoi(inv[0]) == 3)
        cout << "\x1b[33m";                 //Yellow
    else
        cout << "\x1b[34m";                 //Blue

    //Printing invitation
    cout << inv[1] << "\x1b[0m ";

    //Closing stream to the invite file
    invite.close();
    delete [] inv;
}

void Bye()
{
    ifstream invite(INVITE);                //In-stream to file with name
    string name;

    //Getting user's name
    for(int i = 0; i < 3; i++)
        getline(invite, name);
    //Printing good bye
    cout << "\n\tGood bye, " << name << "!\n" << endl;
}

void HelpPrint()
{
    ifstream help(HELP);                    //In-stream to help-file
    string help_line;

    //Running through file till it ends
    //and printing it
    cout << endl;
    while(!help.eof()){
        getline(help, help_line);
        cout << "\t" << help_line << endl;
    }
}

void ErrorWarning(int err_num, string err_cmd)
{
    //Printing errors
    switch (err_num)
    {
        case 0:
        {
            cout << "\tSuccessfully." << endl;
            break;
        }
        case TOO_MUCH:
        {
            cout << "\tToo much synonyms are already used." << endl;
            break;
        }
        case ALREADY_EXIST:
        {
            cout << "\tSuch command already exists." << endl;
            break;
        }
        case NO_SUCH_COMMAND:
        {
            cout << "\tCommand does not exist." << endl;
            break;
        }
        case ORIGINAL_COMMAND:
        {
            cout << "\tCan not delete original command." << endl;
            break;
        }
        case UNKNOWN_CMD:
        {
            cout << "\tUnknown command: <" << err_cmd << ">." << endl;
            break;
        }
        case UNEXPECTED:
        {
            cout << "\tUnexpected command: <" << err_cmd << ">." << endl;
            break;
        }
        case OUT_OF_RANGE:
        {
            cout << "\tNumber is out of range." << endl;
            break;
        }
        case NOT_ENOUGH_ARGUMENTS:
        {
            cout << "\tNot enough arguments." << endl;
            break;
        }
        case INVALID_INPUT:
        {
            cout << "\tInvalid input: <" << err_cmd << ">." << endl;
            break;
        }
        case ABORTED:
        {
            cout << "\tAborted." << endl;
            break;
        }
        case DOT_BEFORE_UNDEF:
        {
            cout << "\tPlease, begin command to delete with '.'" << endl;
            break;
        }
        case NO_RECORDS:
        {
            cout << "\tYou have no records." << endl;
            break;
        }
        case NO_SUCH_RECORDS:
        {
            cout << "\tYou have no such records." << endl;
            break;
        }
        case NO_CMDS_DEF:
        {
            cout << "\tYou have defined no commands." << endl;
            break;
        }
    }
}

void RecordsHeader()
{
    cout << "\tPos\tPri\tStatus\t\tData\n" << endl;
}

void RecordPrint(string record, int rec_num)
{
    string color;                                   //Here lies color
    string color_std = "\x1b[0m";                   //Standart color

    //Braking record in pieces
    string priority = record.substr(0, 1);
    string status = record.substr(2, 1);
    string data = record.substr(5, record.length() - 6);

    //Printing number of a record
    cout << "\t" << rec_num << "\t";

    //Choosing color for priority
    if(stoi(priority) <= 2){
        //Green = ok
        color = "\x1b[32m";
    }else if(stoi(priority) >= 7){
        //Red - user should hurry up
        color = "\x1b[31m";
    }else{
        //Yellow - so-so
        color = "\x1b[33m";
    }
    //Resetting color
    priority = color + priority + color_std;
    //Printing priority
    cout << priority << "\t";

    //Choosing color for status
    if(stoi(status) == 0){
        //Red - undone
        cout << "\x1b[31mUNDONE\x1b[0m" << "\t\t";
    }else{
        //Green - done
        cout << "\x1b[32mDONE\x1b[0m" << "\t\t";
    }
    //Printing data
    string::iterator iter = data.begin();
    int print_len = 0;                             //Lengh of already printed part
    while(iter != data.end()){
        //If max lengh reached, begin new str
        if(print_len == MAX_STR_LEN){
            cout << "\n\t\t\t\t\t";
            print_len = 0;
        }
        //Prinring symbol
        cout << *iter;
        print_len++;
        iter++;
    }
    //Beginning new line
    cout << endl;
}

void SynonymPrint()
{
    ifstream synonyms(CMDSSYN);                     //Stream to file with synonyms
    string syn_line;                                //Line with all synonyns to a command
    string* syns;                                   //Array to contain synonyms to a command

    //Header
    cout << "\tCommands' synonyms list:\n" << endl;

    //Running through the file and printing every command
    for(int i = 0; i < CMDS_AMNT; i++){
        //Getting line from the file
        getline(synonyms, syn_line);
        //Breaking it into synonyms
        syns = SynBrake(syn_line);
        //Printing every command
        //First one shoud not have any symbol before it
        cout << "\t" << syns[0];
        int syn_num = 1;                            //Counter for synonyms
        while(!syns[syn_num].empty()){
            //Printing synonyms
            cout << " = " << syns[syn_num];
            //Going for next synonym
            syn_num++;
        }
        //Beginning new line
        cout << endl;
    }
    //Free memory
    delete [] syns;
}

void CmdsDefPrint()
{
    ifstream usr_def_cmds(USR_DEF_CMDS);            //In-strem into file with user-defined commands
    string syn_line;                                //Line with command and its substitution
    string* syns;                                   //Array with command and its substitution

    //Header
    cout << "\tYour commands:\n" << endl;

    //Running through synonyms
    for(int i = 0; i < CommandsAmount(); i++){
        //Getting line
        getline(usr_def_cmds, syn_line);
        //Breaking it in two parts
        syns = SynBrake(syn_line);
        //Printing
        cout << "\t" << syns[0] << " = " << syns[1] << endl;
    }
    //Freeing memory
    delete [] syns;
}

//
//=======================================================================================
//

int AddSynonym(string new_syn, string to_cmd)
{

    ifstream i_cmds_syn(CMDSSYN);           //In-stream to file with commands
    ofstream o_tmp(TMP);                    //Out-tream to temporary file
    fstream usr_def_cmds(USR_DEF_CMDS);     //Stream to file with user-defined commands
    string syn_line;                        //String with all synonyms to a command
    string syn_to_change_line;              //String to contain line that is going to be changed
    string* syns;                           //Array to contain synonyms
    int syn_num;                            //Counter for synonyms
    int cmd_num;                            //Counter for commands

    //Checking if user's trying to add already existing command
    //and if there are already MAX_SYN reached.

    //First - check if such synonym already exists
    //Running through file with commands
    while(!i_cmds_syn.eof()){
        //Getting all synonyms to a command
        getline(i_cmds_syn, syn_line);
        syns = SynBrake(syn_line);

        //Checking if there are alresdy too much synonyms
        if(!syns[MAX_SYN - 2].empty()){
            o_tmp.close();
            remove(TMP);
            delete [] syns;
            return TOO_MUCH;
        }

        //Running through every synonym looking for concurrence
        syn_num = 0;
        while(!syns[syn_num].empty()){
            //If concurrence is found, return error
            if(syns[syn_num] == new_syn){
                o_tmp.close();
                remove(TMP);
                delete [] syns;
                return ALREADY_EXIST;
            }
            //Going for next synonym
            syn_num++;
        }
    }

    //Second - check if user has already defined such command earlier
    //Running through user-defined commands
    while(!usr_def_cmds.eof()){
        //Taking user-gefined command
        getline(usr_def_cmds, syn_line);
        string usr_cmd = syn_line.substr(0, syn_line.find('^'));    //User-defined command

        //Looking for concurrence
        if(usr_cmd == new_syn){
            o_tmp.close();
            remove(TMP);
            delete [] syns;
            return ALREADY_EXIST;
        }
    }

    //If everything is OK, adding a synonym
    //Resetting pointer in file to the beginning
    i_cmds_syn.clear();
    i_cmds_syn.seekg(0, i_cmds_syn.beg);

    //Running through file with synonyms
    cmd_num = 0;
    while(!i_cmds_syn.eof()){
        //Getting all synonyms to a command
        getline(i_cmds_syn, syn_line);
        syns = SynBrake(syn_line);

        //Running through every synonym looking for concurrence
        syn_num = 0;
        while(!syns[syn_num].empty()){
            //If concurrence is found
            if(syns[syn_num] == to_cmd){
                //Adding a synonym
                //Remembering line to change
                syn_to_change_line = syn_line;

                //Copeing all commands to TMP
                i_cmds_syn.clear();
                i_cmds_syn.seekg(0, i_cmds_syn.beg);
                for(int i = 0; i < CMDS_AMNT; i++){
                    getline(i_cmds_syn, syn_line);
                    o_tmp << syn_line << "\n";
                }
                //Deleting all from аile with commands
                i_cmds_syn.close();
                ofstream o_cmds_syn(CMDSSYN, ios::trunc);

                o_tmp.close();
                ifstream i_tmp(TMP);
                //Placing all back from tmp to commands
                for(int i = 0; i < CMDS_AMNT; i++){
                    getline(i_tmp, syn_line);       //Going to the next line in tmp
                    //If command had not to be changed
                    if(i != cmd_num)
                        o_cmds_syn << syn_line << "\n";
                    else
                        o_cmds_syn << syn_to_change_line << '^' << new_syn << "\n";
                }
                //Deleting tmp
                i_tmp.close();
                remove(TMP);

                delete [] syns;
                //Sucsess code
                return 0;
            }
            syn_num++;
        }
        cmd_num++;
    }
    //If we're here, than user tried to add a synonym to a non-existing command
    //Deleting tmp
    o_tmp.close();
    remove(TMP);
    delete [] syns;
    return NO_SUCH_COMMAND;
}

int DeleteSynonym(string del_syn)
{
    ifstream i_cmds_syn(CMDSSYN);               //In-stream to the file with synonyms
    ifstream cmds_clr(CMDSCLR);                 //In-stream to the file with original commands
    string* syns;                               //Array with synonyms to a command
    string syn_line;                            //String with comand

    //Check if user's trying to delete original command
    while(!cmds_clr.eof()){
        getline(cmds_clr, syn_line);
        if(del_syn == syn_line)
            return ORIGINAL_COMMAND;
    }

    //Running through file with synonyms
    int cmd_num = 0;                            //Number of command
    while(!i_cmds_syn.eof()){
        //Getting all synonyms
        getline(i_cmds_syn, syn_line);
        syns = SynBrake(syn_line);

        //Running through synonyms looking for concurrences
        int syn_num = 0;                        //Counter for synonyms, takes value of synonym to delete
        while(!syns[syn_num].empty()){
            //If concurrence is found
            if(del_syn == syns[syn_num]){
                //Remembering every command in tmp
                ofstream o_tmp(TMP);                    //Stream to tmp
                i_cmds_syn.seekg(0, i_cmds_syn.beg);    //Replacing pointer to the beginning

                for(int i = 0; i < CMDS_AMNT; i++){
                    getline(i_cmds_syn, syn_line);
                    o_tmp << syn_line << "\n";
                }

                //Clearing commands file
                i_cmds_syn.close();
                ofstream o_cmds_syn(CMDSSYN, ios::trunc);

                //Resetting tmp
                o_tmp.close();
                ifstream i_tmp(TMP);

                //Placing everything back from tmp to commands
                int cmd_num_1 = 0;                      //Another counter for commands
                for(int i = 0; i < CMDS_AMNT; i++){
                    getline(i_tmp, syn_line);
                    //Line-to-change should be placed another way
                    if(cmd_num_1 != cmd_num)
                        o_cmds_syn << syn_line << "\n";
                    else{
                        //Running through synonyms and replacing them back
                        //First one is original, it will definately be placed back
                        o_cmds_syn << syns[0];

                        int syn_num_1 = 1;          //Another counter for synonyms
                        while(!syns[syn_num_1].empty()){
                            //Ignoring syns[syn_num]
                            if(syn_num != syn_num_1)
                                o_cmds_syn << '^' << syns[syn_num_1];
                            //Going for next synonym
                            syn_num_1++;
                        }
                        //Beginning new line
                        o_cmds_syn << "\n";
                    }
                    cmd_num_1++;
                }
                i_tmp.close();
                remove(TMP);
                delete [] syns;
                //Sucsess code
                return 0;
            }
            syn_num++;
        }
        cmd_num++;
    }

    delete [] syns;
    //If we're here, no such command found
    return NO_SUCH_COMMAND;
}

int DefCommand(string new_cmd, string cmd_seq)
{
    ifstream i_cmds_syn(CMDSSYN);               //Stream to commands' synonyms
    fstream usr_def_cmds(USR_DEF_CMDS);         //Stream to file with user-defined commands
    string syn_line;                            //Line with all synonyms to a command
    string* syns;                               //Array with synonyms
    int syn_num;                                //Counter for synonyms

    //Check if such command already exist

    //First - check if user's trying to add command that already lies in
    //commands synonyms
    //Running through synonyms
    while(!i_cmds_syn.eof()){
        //Getting all synonyms to a command
        getline(i_cmds_syn, syn_line);
        syns = SynBrake(syn_line);

        //Running through every synonym looking for concurrence
        syn_num = 0;
        while(!syns[syn_num].empty()){
            //If concurrence is found, return error
            if(syns[syn_num] == new_cmd){
                delete [] syns;
                return ALREADY_EXIST;
            }
            //Going for next synonym
            syn_num++;
        }
    }

    //Second - check if user has already defined such command earlier
    //Running through user-defined commands
    while(!usr_def_cmds.eof()){
        //Getting user-gefined command
        getline(usr_def_cmds, syn_line);
        string usr_cmd = syn_line.substr(0, syn_line.find('^'));    //User-defined command

        //Looking for concurrence
        if(usr_cmd == new_cmd){
            delete [] syns;
            return ALREADY_EXIST;
        }
    }

    //If command is really new, place it in the file
    //Placing pointer in file to the end
    usr_def_cmds.clear();
    usr_def_cmds.seekp(0, ios::end);
    usr_def_cmds << new_cmd << '^' << cmd_seq << "\n";

    delete [] syns;
    //Sucsess code
    return 0;
}

int UndefCommand(string del_cmd)
{
    ifstream i_usr_def_cmds(USR_DEF_CMDS);          //In-stream to file with commands
    ofstream o_tmp(TMP);                            //In-stream to tmp file
    string syn_line;                                //String with command+substitution

    //Do not need any check, just deleting
    int cmd_num = 0;                                //Number of  command
    while(!i_usr_def_cmds.eof()){
        //Getting user-defined command
        getline(i_usr_def_cmds, syn_line);
        string usr_cmd = syn_line.substr(0, syn_line.find('^'));    //User-defined command

        //Looking for concurrence
        if(usr_cmd == del_cmd){
            //Deleting command
            //Pointing pointer to the begining
            i_usr_def_cmds.clear();
            i_usr_def_cmds.seekg(0, i_usr_def_cmds.beg);

            //Copeing everything to tmp
            int curr_cmds_amnt = CommandsAmount();  //Amount of commands
            for(int i = 0; i < curr_cmds_amnt; i++){
                getline(i_usr_def_cmds, syn_line);
                o_tmp << syn_line << "\n";
            }
            //Deleting user-defined commands
            i_usr_def_cmds.close();
            ofstream o_usr_def_cmds(USR_DEF_CMDS, ios::trunc);

            //Resetting tmp
            o_tmp.close();
            ifstream i_tmp(TMP);

            //Placing commands back
            for(int i = 0; i < curr_cmds_amnt; i++){
                getline(i_tmp, syn_line);
                //Ignoring line-to-delete
                if(i != cmd_num){
                    o_usr_def_cmds << syn_line << "\n";
                }
            }
            //Deleting tmp file
            i_tmp.close();
            remove(TMP);
            //Sucsess code
            return 0;
        }
        //Going for next command
        cmd_num++;
    }
    //Deleting tmp file
    o_tmp.close();
    remove(TMP);
    //If we're here, command does not exist
    return NO_SUCH_COMMAND;
}

void ChangeName(string new_name)
{
    ifstream i_invite(INVITE);                      //In-stream into invite-file
    ofstream o_tmp(TMP);                            //Of-stream into tmp file
    string line;                                    //Line from invite-file

    //Copeing everything to tmp
    for(int i = 0; i < 3; i++){
        getline(i_invite, line);
        o_tmp << line << "\n";
    }
    //Deleting everything from invite-file
    i_invite.close();
    ofstream o_invite(INVITE, ios::trunc);
    //Resetting tmp
    o_tmp.close();
    ifstream i_tmp(TMP);

    //Placing lines back from tmp, name placed separately
    for(int i = 0; i < 2; i++){
        getline(i_tmp, line);
        o_invite << line << "\n";
    }
    //Placing name
    o_invite << new_name;
    //Deleting tmp
    o_invite.close();
    i_tmp.close();
    remove(TMP);
}

void ChangeInvite(string new_inv)
{
    ifstream i_invite(INVITE);                      //In-stream into invite-file
    ofstream o_tmp(TMP);                            //Out-stream into tmp file
    string line;

    //Remembering invite's color
    getline(i_invite, line);
    string color = line.substr(0, 1);

    //Copeing everything in tmp
    i_invite.seekg(0, i_invite.beg);
    for(int i = 0; i < 3; i++){
        getline(i_invite, line);
        o_tmp << line << "\n";
    }
    //Clearing invite-file
    i_invite.close();
    ofstream o_invite(INVITE, ios::trunc);
    //Resetting tmp
    o_tmp.close();
    ifstream i_tmp(TMP);

    //Placing everything back
    //Invitation placed another way
    o_invite << color << '^' << new_inv;
    //Skipping old invitation
    getline(i_tmp, line);
    for(int i = 1; i < 3; i++){
        getline(i_tmp, line);
        o_invite << "\n" << line;
    }

    //Deleting tmp file
    o_invite.close();
    i_tmp.close();
    remove(TMP);
}

void ChangeInvColor(int color_num)
{
    fstream invite(INVITE);                 //Stream into invite-file
    string line;

    //Getting invitation
    getline(invite, line);
    //Placing pointer to the beginning
    invite.seekp(0);
    //Placing everything back
    invite << color_num << line.substr(1);

    invite.close();
}

//
//=======================================================================================
//

string* QuotesSep(string input)
{
    string::iterator iter = input.begin();

    string* commands = new string [MAX_CMDS];   //Array to save commands after first, raw
                                                //separation (quotes separation)
    int command_num = 0;                    //Amount of raw commands
    bool quotes_closed = true;              //In the very beginning quotes are closed
    bool just_closed = true;                //In the very beginning there were no quotes

    //Running through input till it ends
    //with dividing input with quotes
    while(iter != input.end()){
        //Overflow prevention
        if(command_num == MAX_CMDS - 2)
            break;

        //If symbol is quotes, starting new command
        if(*iter == '\"'){
            //Changing quotes' status
            quotes_closed = !quotes_closed;

            //If quotes are just opening and previous quotes were not
            //just closed, starting new command
            if(!quotes_closed && !just_closed)
                command_num++;
            //If quotes have just closed, placing closing quot
            //and beginning new command. Go to the beginning of
            //the loop (taking next character from input)
            if(quotes_closed){
                commands[command_num].append(1, *iter);
                iter++;
                just_closed = true;
                command_num++;
                continue;
            }
        }
        just_closed = false;

        //Placing symbol in command
        commands[command_num].append(1, *iter);
        iter++;
    }
    return commands;
}

string* SpaceSep(string* raw_commands)
{
    string::iterator iter;

    string* commands = new string [MAX_CMDS];   //Array to save new separation
                                                //(space separation)
    int raw_command_num = 0;                //Counter for previous commands
    int command_num = 0;                    //Amount of new commands
    bool prev_is_space = true;              //Check if previous symbol is space

    //Running through previous commands
    while(!raw_commands[raw_command_num].empty()){
        //Overflow prevention
        if(command_num == MAX_CMDS - 2)
            break;

        //Replacing parts with quotes without any changes
        //and breaking others in simple commands
        if(raw_commands[raw_command_num][0] != '\"'){
            iter = raw_commands[raw_command_num].begin();

            //Running through raw command
            while(iter != raw_commands[raw_command_num].end()){
                //Checking for spaces and beginning new command
                //in case this is first space.
                if((isspace(*iter) && !prev_is_space)){
                    command_num++;
                    prev_is_space = true;
                }
                //Placing command in new array if it's not space
                if(!isspace(*iter)){
                    commands[command_num].append(1, *iter);
                    prev_is_space = false;
                }
                iter++;
            }
            //If last character is space, we have already began new command.
            //Otherwise we have to do it now.
            if(!prev_is_space)
                command_num++;
        }else{;
            //Placing "quoted" command in new array
            commands[command_num].append(raw_commands[raw_command_num]);
            command_num++;
            //If next raw command is not "quoted", then we do not need
            //to begin new command
            prev_is_space = true;
        }
        //Going for the next iteration
        raw_command_num++;
    }

    //Clearing memory
    delete [] raw_commands;

    return commands;
}

string* UsrDefSubst(string* raw_commands)
{
    ifstream usr_cmds_file(USR_DEF_CMDS);       //In-stream to user-defined commands - file
    int raw_commands_num = 0;                   //Counter for commands
    string usr_def_cmd;                         //String to save user-defined command

    //If user-defined commands exist, check if they are used
    getline(usr_cmds_file, usr_def_cmd);

    if(!usr_def_cmd.empty()){
        //Running through commands
        while(!raw_commands[raw_commands_num].empty()){
            //Set read pointer in USR_DEF_CMDS to the beginning
            //of the file
            usr_cmds_file.seekg(0, usr_cmds_file.beg);

            //Check if it is not a "quoted" command,
            //else just skip it
            if(raw_commands[raw_commands_num][0] != '\"'){
                //Running through file with commands till it ends
                do{
                    //Reading command and its substitution
                    getline(usr_cmds_file, usr_def_cmd);

                    //Taking commands and their substitutions from the whole string
                    //that lies in file
                    string cmd = usr_def_cmd.substr(0, usr_def_cmd.find("^"));      //Command to replace
                    string sbst = usr_def_cmd.substr(usr_def_cmd.find("^") + 1);    //Substitution

                    //If such command exists, replacing it with its substitution
                    if(cmd == raw_commands[raw_commands_num])
                        raw_commands[raw_commands_num] = sbst;

                    //Last loop will give an empty string because EOF flag
                    //will be setted only after unsuccesful attempt to read
                    //unexistable line. So change something only if user_def_cmd
                    //is not empty
                }while(!usr_def_cmd.empty());
            }
            //Setting goodbit to read again
            usr_cmds_file.clear();

            //Going for the next iteration
            raw_commands_num++;
        }
    }
    return raw_commands;
}

string* SynBrake(string syn_line)
///'^' in the end of syn_line causes segmantation fault
{
    string::iterator iter = syn_line.begin();

    string* synonyms = new string [MAX_SYN];        //Array to contain synonyms
    int syn_num = 0;

    //Running through the syn_line
    while(iter != syn_line.end()){
        //If we see separator, beginning new word and
        //going to the next symbol
        if(*iter == '^'){
            syn_num++;
            iter++;
        }
        //Put characters in array
        synonyms[syn_num].append(1, *iter);
        iter++;
    }
    return synonyms;
}

bool IsNum(string cmd)
///Returns TRUE in case string consisns only of numbers or '-'
{
    string::iterator iter = cmd.begin();

    //First check: if command begins more then with 1 '-',
    //returns FALSE
    if(cmd[0] == '-' && cmd[1] == '-')
        return false;

    //Running through the command
    while(iter != cmd.end()){
        //If any character of command is not a digin or minus,
        //return false, else - true
        if((*iter != '-') && (!isdigit(*iter)))
            return false;
        iter++;
    }
    return true;
}

int CommandsAmount()
{
    ifstream usr_cmds(USR_DEF_CMDS);        //Stream into file with user-defined comands
    int commands_amount = 0;                //Counter for commands
    string syn_line;                        //String with command

    while(!usr_cmds.eof()){                 //Running through the file
        getline(usr_cmds, syn_line);        //till it ends
        commands_amount++;
    }

    //We have counted one extra line
    return commands_amount - 1;
}

