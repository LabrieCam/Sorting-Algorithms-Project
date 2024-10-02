#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <iomanip>

struct DataPoint{
    std::string location;
    int confirmed;
    int probable;
    int total;

    DataPoint(std::string location, int confirmed, int probable, int total) : location(location), confirmed(confirmed), probable(probable), total(total){}
};

/*Function to get display and get user's choice
Parameter(s): None
Returns: Integer representing user's choice
*/
int make_choice(){
    int choice = 3;
    std::cout<<"How would you like to sort the data? \nEnter number to make a choice."<<std::endl;
    std::cout<<"Default choice is sorting by total cases"<<std::endl;
    std::cout<<"\t 1. Sort by confirmed cases"<<std::endl;
    std::cout<<"\t 2. Sort by probable cases"<<std::endl;
    std::cout<<"\t 3. Sort by total cases"<<std::endl;

    std::cin>>choice;
    if(choice<=3 && choice >= 1){
        return choice;
    }
    else{
        choice = 3;
        return choice;
    }
}

/*Function to retrieve the data from the file
Parameter(s): Pointer to file to read from
Returns: Vector holding all the data from the file
*/
std::vector<DataPoint> make_vector(std::ifstream& file){
    std::string lines;
    //skip the first 30 lines
    for(int i = 0; i<30; i++){
        std::getline(file, lines);
    }

    std::vector<DataPoint> data;
    std::string line1;

    int confirmed = 0, probable = 0, total = 0; // , count = 0
    std::string  line2, state, entry, entry2, type;
    while(std::getline(file, line1) && std::getline(file, line2)){

        std::stringstream streamline(line1);
        std::stringstream streamline2(line2);
        for(int i = 0; i <= 13 && std::getline(streamline, entry, ','); i++){
            if (i==3){
                entry.erase(std::find(entry.begin(), entry.end(), '"'));
                entry.erase(std::find(entry.begin(), entry.end(), '"'));
                if(!entry.empty()){
                    state = entry;
                }
                else{
                    state = "Unknown";
                }
            }

            if(i == 13){
                entry.erase(std::find(entry.begin(), entry.end(), '"'));
                entry.erase(std::find(entry.begin(), entry.end(), '"'));
                if(!entry.empty()){
                    confirmed = std::stod(entry);
                }
                else{
                    confirmed = 0;
                }
            }
        }//for loop parentheses

        for(int i = 0; i<=13 && std::getline(streamline2, entry2, ','); i++){
            if(i == 13){
                entry2.erase(std::find(entry2.begin(), entry2.end(), '"'));
                entry2.erase(std::find(entry2.begin(), entry2.end(), '"'));
                if(!entry2.empty()){
                    probable = std::stod(entry2);
                }
                else{
                    probable = 0;
                }
            }
        }//nested for loop parentheses
        total = confirmed + probable;
        data.emplace_back(state, confirmed, probable, total);
    }//while loop parentheses
    return data;
}//function parentheses


/*Function to make each state in the file have a single entry
Parameter(s): Pointer to vector holding all the data
Returns: Vector holding each state in the file as a single entry 
*/
std::vector<DataPoint> single_entry(const std::vector<DataPoint>& data) {
    std::vector<DataPoint> result;

    for (auto& dp : data) {
        bool found = false;
        for (auto& item : result) {
            if (item.location == dp.location) {
                item.confirmed += dp.confirmed;
                item.probable += dp.probable;
                item.total += dp.total;
                found = true;
                break;
            }
        }
        if (!found) {
            result.push_back(dp);
        }
    }

    return result;
}

/*Function to find the largest item in  a range in the vector using a linear search*/
int find_largest(int choice, std::vector<DataPoint>& last, int index){
    int maxIndex = 0;
    switch(choice){
        case 1: //choice 1 is sort by confirmed cases
            for(int i = 1; i <= index; i++){
                if(last[i].confirmed > last[maxIndex].confirmed){
                    maxIndex = i;
                }
            }
            break;
        
        case 2: //choice 2 is sort by probable cases;
            for(int i = 1; i <= index; i++){
                if(last[i].probable > last[maxIndex].probable){
                    maxIndex = i;
                }
            }
            break;
        
        default:
            for(int i = 1; i <= index; i++){
                if(last[i].total > last[maxIndex].total){
                    maxIndex = i;
                }
            }
            break;
    }
    return maxIndex;
}

/*Void function to flip the vector using inbuilt vector property, reverse*/
void flip(std::vector<DataPoint>& vector1, int index){
    if(index >= 0 && index <vector1.size()){
        std::reverse(vector1.begin(), vector1.begin()+ index + 1);\
    }
    return;
}

/*This function takes in a vector generated from the file parsing sorts it. */
void pancake_sort(int choice, std::vector<DataPoint>& last){
    int length = last.size();
    
    for(int current = length; current > 1; current --){
        int maxIndex = find_largest(choice, last, current-1);
        if(maxIndex != current -1){
            flip(last, maxIndex);
            flip(last, current -1);
        }
    }
}

int main(int argc, char* argv[]){
    
    std::string filename(argv[1]); //File to read from
    std::string newfile(argv[2]); //File to write to
    
    std::ifstream inFile(filename); // open file to read from
    std::ofstream outFile (newfile); // open file to write to

    if(!inFile.is_open()){
        std::cerr<<"Error: Could not open the input file."<<std::endl;
        return 1;
    }

    if(!outFile.is_open()){
        std::cerr << "Error: Could not open the output file." << std::endl;
        return 1;
    }
    
    std::vector<DataPoint> data = make_vector(inFile);
    std::vector<DataPoint> single = single_entry(data);
    int choice = make_choice();
    pancake_sort(choice, single);

    // Write sorted data to the output file
    for(int i = 0; i<single.size(); i++){//std::left << std::setw(20)<<
        outFile << std::left << "Location: "<< std::setw(15) << single[i].location
        << " Confirmed: " << single[i].confirmed << std::right << std::setw(15) 
        << " Probable: " << single[i].probable << std::right << std::setw(15) 
        << " Total: " <<single[i].total << std::endl;
    }

    std::cout<<"File successfully sorted and written."<<std::endl;
    
    return 0;
}
