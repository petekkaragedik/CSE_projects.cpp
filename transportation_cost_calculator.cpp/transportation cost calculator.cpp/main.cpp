#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

void getTripDetails(string& startCity, string& destinationCity, float& distance, float& gasPrice, int& passengers, int& daysInAdvance, bool& isWeekend){

    string flag;
    cout << "Enter the starting city: ";
    cin >> startCity;
    cout << "Enter the destination city: ";
    cin >> destinationCity;
    cout << "Enter the trip distance in kilometers: ";
    cin >> distance;
    cout << "Enter the price of gasoline per liter: ";
    cin >> gasPrice;
    cout << "Enter the number of passengers: ";
    cin >> passengers;
    cout << "Enter days booked in advance: ";
    cin >> daysInAdvance;
    cout << "Is the trip on a weekend? (yes/no): ";
    cin >> flag;
    if (flag == "yes"){
        isWeekend = true;
    }
    else{
        isWeekend = false;
    }
}

float calculateEnvironmentalFee(float distance, float average_fuel_consumption_per_100km){
    
    float envImpactFee;
    
    if (average_fuel_consumption_per_100km > 8){
        envImpactFee = 0.002 * distance;
    }
    else{
        envImpactFee = 0.001 * distance;
    }
    return envImpactFee;
}

float calculateCarCost(const float distance, const float gasPrice, const float average_fuel_consumption_per_100km, const float envImpactFee){
    
    float fuelCost, envCost, totalCarCost;
    fuelCost = (distance / 100) * average_fuel_consumption_per_100km * gasPrice;
    if (fuelCost > 2700){
        fuelCost = fuelCost / 2;
    }
    envCost = envImpactFee * distance;
    totalCarCost = envCost + fuelCost;
    
    return totalCarCost;
}

float calculateTieredDistanceRate(float basePrice, float distance, string type){
    
    float adjBasePrice;
    
    if (type == "bus"){
        if (distance <= 100){
            adjBasePrice = basePrice;
        }
        else if (100 < distance && distance <= 200){
            adjBasePrice = basePrice * 1.05;
        }
        else if (200 < distance && distance <= 300){
            adjBasePrice = basePrice * 1.10;
        }
        else{
            adjBasePrice = basePrice * 1.15;
        }
    }
    else{
        if (distance <= 100){
            adjBasePrice = basePrice;
        }
        else if (100 < distance && distance <= 200){
            adjBasePrice = basePrice * 1.10;
        }
        else if (200 < distance && distance <= 300){
            adjBasePrice = basePrice * 1.15;
        }
        else{
            adjBasePrice = basePrice * 1.30;
        }
    }
    return adjBasePrice;
}

float applyEarlyBookingDiscount(float cost, int daysInAdvance){
    
    if (daysInAdvance >= 30){
        cost = cost * 0.9;
    }
    return cost;
}

float applyDayOfWeekPricing(float cost, bool isWeekend){
    if (isWeekend) {
        cost *= 1.10;
    }
    return cost;
}

float calculateBusTrainCost(const float basePrice, const float distance, const int passengers, const int daysInAdvance, const bool isWeekend, string type){
    
   float passMul;
    
    passMul = calculateTieredDistanceRate(basePrice, distance, type) * passengers;
    return applyDayOfWeekPricing(applyEarlyBookingDiscount(passMul, daysInAdvance), isWeekend);
}

float findMin(float a, float b, float c, float d){
   
    float min;
    
    if ( a < b && a < c && a < d){
        min = a;
    }
    else if ( b < a && b < c && b < d){
        min = b;
    }
    else if (c < a && c < b && c < d) {
        min = c;
    }
    else{
        min = d;
    }
    return min;
}

int main() {
    string startCity, destinationCity, typetrain, typebus, bestVehicle;
    float distance, gasPrice;
    int passengers, daysInAdvance;
    bool isWeekend;
    
    typetrain = "train";
    typebus = "bus";
    
    getTripDetails(startCity, destinationCity, distance, gasPrice, passengers, daysInAdvance, isWeekend);
    
    float avgFuelCar1 = 7.9;
    float avgFuelCar2 = 8.2;
    float busBasePrice = 510;
    float trainBasePrice = 470;
    
    float costCar1, costCar2, costBus, costTrain, best_way;
    
    costCar1 = calculateCarCost(distance, gasPrice, avgFuelCar1, calculateEnvironmentalFee(distance, avgFuelCar1));
    
    costCar2 = calculateCarCost(distance, gasPrice, avgFuelCar2, calculateEnvironmentalFee(distance, avgFuelCar2));
    
    costBus = calculateBusTrainCost(busBasePrice, distance, passengers, daysInAdvance, isWeekend, typebus);
    
    costTrain = calculateBusTrainCost(trainBasePrice, distance, passengers, daysInAdvance, isWeekend, typetrain);
    
    cout << "Cost for Car 1: " << fixed << showpoint << setprecision(2) << costCar1 << " TL" << endl;
    cout << "Cost for Car 2: " << fixed << showpoint << setprecision(2) << costCar2 << " TL" << endl;
    cout << "Cost for Bus: " << fixed << showpoint << setprecision(2) << costBus << " TL" << endl;
    cout << "Cost for Train: " << fixed << showpoint << setprecision(2) << costTrain << " TL" << endl;
    
    best_way = findMin(costCar1, costCar2, costBus, costTrain);
    
    if (best_way == costCar1){
        bestVehicle = "Car 1";
    }
    else if (best_way == costCar2){
        bestVehicle = "Car 2";
    }
    else if (best_way == costBus){
        bestVehicle = "Bus";
    }
    else{
        bestVehicle = "Train";
    }
    
    cout << "The most cost-effective transportation option to travel from " << startCity << " to " << destinationCity << ": " << bestVehicle << " with a cost of " << fixed << showpoint << setprecision(2) << best_way << " TL" << endl ;
    
    return 0;
}
