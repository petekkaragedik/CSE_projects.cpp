#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "strutils.h"
using namespace std;

struct WeatherData {
    string date;
    double precipitation, temperature;
};

WeatherData parseLine(const string& line){

    long i,k;
    WeatherData day;
    i = line.find(",");
    day.date = line.substr(0, i);
    k = line.rfind(",");
    day.temperature = atof(line.substr(i+1, k - i - 1));
    day.precipitation = atof(line.substr(k + 1));
    return day;
}


double averageTemperature(const vector<WeatherData>& data){
    int k;
    double averagetemp = 0, total = 0;
    for (k = 0; k < data.size(); k++){
        total += data[k].temperature;
    }
    averagetemp = total/data.size();
    return averagetemp;
}

double totalPrecipitation(const vector<WeatherData>& data){
    int p;
    double totalprec = 0;
    for (p = 0; p < data.size(); p++){
        totalprec += data[p].precipitation;
    }
    return totalprec;
}

WeatherData findExtremesTemperature(const vector<WeatherData>& data, bool findMax){
    int i;
    if (findMax == true){
        double maxtemp = 0;
        WeatherData maxday;
        for (i = 0; i < data.size(); i++){
            if (data[i].temperature > maxtemp){
                maxtemp = data[i].temperature;
                maxday = data[i];
            }
        }
        return maxday;
    }
    else{
        WeatherData minday;
        double mintemp = data[0].temperature;
        for (i = 0; i < data.size(); i++){
            if (data[i].temperature < mintemp){
                minday = data[i];
                mintemp = minday.temperature;
                
                
            }
        }
        return minday;
    }
}

WeatherData maxPrecipitation(const vector<WeatherData>& data){
    
    WeatherData maxprecday;
    double maxprec = 0;
    int n;
    for (n = 0; n < data.size(); n++){
        if (data[n].precipitation > maxprec){
            maxprec = data[n].precipitation;
            maxprecday = data[n];
        }
    }
    
    return maxprecday;
}

int countDryDays(const vector<WeatherData>& data){
    int drydays = 0, m;
    for (m = 0; m < data.size(); m++){
        if (data[m].precipitation == 0.0){
            drydays++;
        }
    }
    return drydays;
}

string getFormattedDate(const string& date){
    
    const string months[] = { "January", "February", "March",
        "April", "May", "June", "July", "August", "September",
        "October", "November", "December" };
    string formatteddate, year, monthnumstr, monthname, day;
    int monthnum;
    long  i, k;
    
    i = date.find("-");
    k = date.rfind("-");
    year = date.substr(0,i);
    monthnumstr = date.substr(i+1,k - i - 1);
    monthnum = atoi(monthnumstr);
    monthname = months[monthnum-1];
    day = date.substr(k + 1,2);
    formatteddate = monthname + " " + day + ", " + year;
    
    return formatteddate;
}
 
int main() {
   
vector<WeatherData> data;
string option, fileName, line;

cout << "Welcome to the Weather Data Analysis Program!" << endl;
cout << "1. Load data file" << endl;
cout << "2. Display average temperature" << endl;
cout << "3. Display total precipitation" << endl;
cout << "4. Display the number of dry days" << endl;
cout << "5. Display the hottest day" << endl;
cout << "6. Display the coldest day" << endl;
cout << "7. Display the day with the highest precipitation" << endl;
cout << "8. Close the program" << endl << endl;
while (true) {
    cout << "Choose an option: ";
    cin >> option;
    
    if (option == "8") {
        cout << "Exiting program..." << endl;
        break;
    }

    if (option == "1") {
        cout << "Enter the file name: ";
        cin >> fileName;
        ifstream input(fileName.c_str());
        if (input.fail()) {
            cout << "Cannot open the file!" << endl;
        }
        else {
            data.clear();
            while (getline(input, line)) {
                data.push_back(parseLine(line));
            }
            input.close();
            cout << "Data loaded successfully." << endl;
        }
    } else if (atoi(option) < 1 || atoi(option) > 8){
        cout << "Invalid option. Please enter a valid option." << endl;
    } else if (data.empty()) {
        cout << "Please load a data file first." << endl;
    } else if (option == "2") {
        cout << "Average Temperature: " << averageTemperature(data) << " Celsius" << endl;
    } else if (option == "3") {
        cout << "Total Precipitation: " << totalPrecipitation(data) << " mm" << endl;
    } else if (option == "4") {
        cout << "Number of Dry Days: " << countDryDays(data) << endl;
    } else if (option == "5") {
        WeatherData hottestDay = findExtremesTemperature(data, true);
        cout << "Hottest Day: " << getFormattedDate(hottestDay.date) << " with " << hottestDay.temperature << " Celsius" << endl;
    } else if (option == "6") {
        WeatherData coldestDay = findExtremesTemperature(data, false);
        cout << "Coldest Day: " << getFormattedDate(coldestDay.date) << " with " << coldestDay.temperature << " Celsius" << endl;
    } else if (option == "7") {
        WeatherData maxPrecDay = maxPrecipitation(data);
        cout << "Highest Precipitation Day: " << getFormattedDate(maxPrecDay.date) << " with " << maxPrecDay.precipitation << " mm" << endl;
    }
}
    return 0;
}
