/**********************************************************************************************************************
 * Author:Anthony Ellis                                                                                               *
 * Date: 6/23/2024                                                                                                    *
 * Description:This program is intended to take an input file of items sold, then create a map of items with their    *
 * quantities. This map can then be displayed as a single item with its quantity, every item with its quantity, or as *
 * a text based histogram.                                                                                            *
 **********************************************************************************************************************/
#include <iostream>
#include <fstream>
#include <map>
#include <string>
using namespace std;
class ItemsSold{
private:
    map<string,int> ItemsMap;//map needed to store items
    string inFName;//input file name
    string outFname;//output file name
    ifstream inFS;//input stream from file
    ofstream outFS;//output stream to file
public:
    ItemsSold(string inFileName,string outFileName );//constructor
    void ItemWasSold(string item);//add or increment item
    void ItemsQuantitiesToFile();//send items with quantities to file
    void ItemsHistogramToFile();//set histogram of items to file
    void singleItemInquiry(string itemName);//inquiry on items sold for one item.

};
//Constructor
//Takes two string parameters, to define file in and out names.
ItemsSold::ItemsSold(string inFileName,string outFileName) {
    string tempName;
    this->inFName = inFileName;
    this->outFname = outFileName;
    inFS.open(inFName);
    if(!inFS.is_open()){
        cout<<"File Error DID NOT OPEN";
        return;
    }
    while(!inFS.eof()){
        inFS>>tempName;
        ItemWasSold(tempName);
    }
    inFS.close();
}
//Items sold are added to the map only if the item is not already in the map, otherwise increment the item sold quantity
void ItemsSold::ItemWasSold(string item) {
    if(ItemsMap.count(item)==1){//if item is in map
        ItemsMap.at(item) = ItemsMap.at(item)+1;//increment Item count sold
    }
    else{//if item not in map
        ItemsMap.emplace(item,1);//add item to map
    }
}
//outputs a single item inquiry
void ItemsSold::singleItemInquiry(string itemName) {
    if(ItemsMap.count(itemName)==1){//if item not found
        cout<<"Item not found."<<endl;//output item not found and go back to menu
    }
    else{//if item found
        cout<<itemName<<" "<<ItemsMap.at(itemName)<<endl;//Output item inquiry
    }
}
//Print Items and their quantities as a histogram using * to a file.
void ItemsSold::ItemsHistogramToFile() {
    outFS.open(outFname);//open file
    if(!outFS.is_open()){//if file is open
        cout<<"Unable to open file";//inform user and return
        return;
    }

    for(auto it = ItemsMap.begin();it != ItemsMap.end();++it){//creates an auto iterator to loop through map
        outFS.width(15);//set width to adjust for item name length
        outFS<<it->first<<" "<<string(it->second,'*')<<endl;//outputting the item and quantity in * to file
    }
    outFS.close();//close the file
}
//Prints to file all the items sold with their respective quantities
void ItemsSold::ItemsQuantitiesToFile() {
    outFS.open(outFname);//open file
    if(!outFS.is_open()){//if file did not open correctly inform user
        cout<<"Unable to open file";
        return;
    }

    for(auto it = ItemsMap.begin();it != ItemsMap.end();++it){//use map iterator to traverse map
        outFS<<it->first<<" "<<it->second<<endl;//output item name and quantity
    }
    outFS.close();//close file
}

//Menu helper function just used to make formatting the menu easier.
void PrintMenu(){
    cout<<"*************************************************************************"<<endl;
    cout<<"********Please enter a number corresponding to the desired option********"<<endl;
    cout<<"*************************************************************************"<<endl;
    cout<<"(1): To see a single item with its quantity."<<endl;
    cout<<"(2): To print a list of the items sold today with quantity sold"<<endl;
    cout<<"(3): To print a text based histogram of the items with frequency sold."<<endl;
    cout<<"(4): To quit the program."<<endl;
    cout<<"*************************************************************************"<<endl;
}

/*Menu Function                                     *
 *This function displays the menu to the user and   *
 *returns the input. This function will recursively *
 *call until a valid input is made.                 */
int Menu() {
    //Variable Declaration
    int input;
    PrintMenu();

    try {
        cin>>input;
        if (input <= 4 && input > 0)
            return input;
        else
            throw exception();//throws if input is integer but is out of range.
    }
    catch(exception e){
        cin.clear();//clear input string to allow for next input.
        string temp;
        getline(cin,temp);
        cout<<"***Invalid Input***: Please select an option from the displayed menu."<<endl;
        return Menu();//if input is invalid, the menu function is displayed again and user is prompted again.
    }

}

/*Menu Options function is called and will run until*
 *option 4 is selected.                             *
 *Parameter is one int between 1 and 4              *
 *output is a boolean used to determine if user     *
 *wishes to continue.                               */
bool MenuOptions(int selection,ItemsSold* items){
    string temp;
    bool quit;
    switch (selection) {
        case 1:
            cout<<"Which item do you want to inquire about?"<<endl;
            cin>>temp;
            items->singleItemInquiry(temp);
            break;
        case 2:
            items->ItemsQuantitiesToFile();
            quit = true;
            break;
        case 3:
            items->ItemsHistogramToFile();
            quit = true;
            break;
        case 4:
            cout<<"Good Bye"<<endl;
            quit = false;
            break;
    }
    return quit;
}
//Main funtion Program starting point where while loop is used to continue the program.
int main() {
    string inName = "C:\\Users\\Anthony\\CLionProjects\\ProjectThreeProgrammingLanguages\\CS210_Project_Three_Input_File.txt";
    string outName = "C:\\Users\\Anthony\\CLionProjects\\ProjectThreeProgrammingLanguages\\CS210_Project_Three_Output_File.txt";
    ItemsSold* itemsSold = new ItemsSold(inName, outName);
    while(MenuOptions(Menu(),itemsSold)){}//while MenuOptions does not return false implying user wants to quit
    return 0;
}
