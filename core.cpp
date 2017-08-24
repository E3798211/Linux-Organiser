#include "core.h"

void AddData(int priority, int status, const string data)
{
    //Writing to the end of the memory
    ofstream memory(USR_DATA, ios::app);    //Out-stream to the database
    memory << priority << " " << status << " " << data << "\n";
    memory.close();
}

void DeleteRecord(int position)
//Position should be already checked
{
    ifstream i_memory(USR_DATA);            //In-stream to the database
    ofstream o_tmp(TMP_FILE);               //Out-stream to the temporary file
    string record;                          //Varriable to get records from database
    int curr_rec_amnt = RecordsAmount();    //Amount of records before deleting

    //Copeing records from memory to tmp
    //Running through database
    for(int record_num = 0; record_num < curr_rec_amnt; record_num++){
        getline(i_memory, record);
        //Placing "alive" messages in tmp
        if(record_num != position)
            o_tmp << record << "\n";
    }

    //Clearing database and opening out-stream to the database
    i_memory.close();
    ofstream o_memory(USR_DATA, ios::trunc);

    //Setting pointer in tmp to the beginning
    //and creating in-stream to the temporary file
    o_tmp.close();
    ifstream i_tmp(TMP_FILE);

    //Replacing records back to database
    for(int record_num = 0; record_num < curr_rec_amnt - 1; record_num++){
        getline(i_tmp, record);
        o_memory << record << "\n";
    }

    //Removing the temporary file
    i_tmp.close();
    remove(TMP_FILE);
}

void DeleteAll()
{
    ofstream memory(USR_DATA, ios::trunc);
    memory.close();
}

void DeleteStatus(int status)
{
    ifstream memory(USR_DATA);              //In-stream to database
    string record;

    //Running throuhg database
    int record_num = 0;                     //Number of a record
    while(!memory.eof()){
        //Getting line
        getline(memory, record);
        //Check if record is not empty
        if(!record.empty()){
            //Status check
            if(stoi(record.substr(2, 1)) == status){
                DeleteRecord(record_num);

                //Running from the very beginning again
                //Placing pointer to the beginning again
                memory.clear();
                memory.seekg(0, memory.beg);

                //Setting record counter to zero
                record_num = 0;
                continue;
            }
        }
        //Going for next command
        record_num++;
    }
}

void DeletePriority(int pri_min, int pri_max)
{
    ifstream memory(USR_DATA);              //In-stream into database
    string record;

    //Running through database
    int record_num = 0;                     //Counter for records
    while(!memory.eof()){
        //Getting line
        getline(memory, record);
        //Check if record is not empty
        if(!record.empty()){
            //Check if priority is out of range
            int rec_pri = stoi(record.substr(0, 1));
            if(pri_min <= rec_pri && rec_pri <= pri_max){
                //Deleting record
                DeleteRecord(record_num);

                //Running from the very beginning again
                //Resetting pointer in database
                memory.clear();
                memory.seekg(0, memory.beg);

                //Setting record counter to the zero
                record_num = 0;
                continue;
            }
        }
        //Going for next record
        record_num++;
    }
}

void SetPriority(int position, int priority)
{
    fstream memory(USR_DATA);               //Stream to the database
    string record;                          //Records from database

    //Getting to necessary position
    for(int i = 0; i < position; i++)
        getline(memory, record);

    memory.clear();

    int coords = memory.tellg();    //Remembering coordinates
    getline(memory, record);        //Copeing record
    memory.seekp(coords);           //Placing it back
    memory << priority << record.substr(1) << "\n";

    memory.close();
}

void SetStatus(int position, int status)
{
    fstream memory(USR_DATA);               //Stream to the database
    string record;                          //Records from database

    //Getting to necessary position
    for(int i = 0; i < position; i++)
        getline(memory, record);

    memory.clear();

    int coords = memory.tellg();    //Remembering coordinates
    getline(memory, record);        //Copeing record
    memory.seekp(coords);           //Placing it back
    memory << record.substr(0, 2) << status << record.substr(3) << "\n";

    memory.close();
}

string GetData(int position)
//Position should be already checked
{
    ifstream memory(USR_DATA);              //In-stream to the database
    string record;                          //Varriable to get records from database

    //Pass previous records and stop on the one we need
    for(int record_num = 0; record_num < position + 1; record_num++)
        getline(memory, record);

    return record;
}

//
//=======================================================================================
//

int RecordsAmount()
{
    ifstream memory(USR_DATA);              //Stream into database
    int records_amount = 0;                 //Counter for records
    string record;

    while(!memory.eof()){                   //Running through the database
        getline(memory, record);            //till it ends
        records_amount++;
    }

    //We have counted one extra line
    return records_amount - 1;
}
