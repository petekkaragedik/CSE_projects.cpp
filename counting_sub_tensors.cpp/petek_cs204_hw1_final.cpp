// Petek Karagedik 34042
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <limits>
using namespace std;

vector <vector <vector <double> > > createEmptyMatrixOfDimensions (int width, int length, int depth){
    return vector <vector <vector <double> > >(width, vector <vector <double> >(length, vector <double> (depth, 0))); // forming the empty matrix of given dimensions
}

int main(int argc, char* argv[]){
    // i will first check if the filename is entered by the user
    if (argc < 2){
        cerr << "useage of" << argv[0] << "no_filename_input" << endl;     //cerr is used for outputing error messages and displays immaditely it occurs
        return 1; // i returned the error code
    }
    // now i will open the file given as the second input --> argv[1]
    
    ifstream dataFile(argv[1]);
    // now cheking if it's opened properly
    if (!dataFile.is_open()){ // if it did not open
        cerr << "can_not_open_file" << argv[1] << endl;
        return 1; // i returned the error code
    }

    //initializing the inputs from the first 3 lines
    int width, length, depth;
    double targettedSum;
    int lineCount;

    dataFile >> width >> length >> depth; //dimensions
    dataFile >> targettedSum; // target sum
    dataFile >> lineCount; // how many non-zero elements

    dataFile.ignore(numeric_limits<streamsize>::max(), '\n'); //found this with a little bit of search - cleans the remaining chars

    vector<vector<vector<double> > > tensorMatrix = createEmptyMatrixOfDimensions(width, length, depth); // i created the empty tensor called tensorMatrix here

    for (int i = 0; i < lineCount; i++){
        string readALine;
        getline (dataFile, readALine); // to read each line one by one

        //to get the values from each line:
        istringstream iss(readALine);
        int a, b, c;
        double valueOfElem;

        if (iss >> a >> b >> c >> valueOfElem){
            tensorMatrix[a][b][c] = valueOfElem; // i added each non-zero element to the empty matrix this way

        }else{
            cerr << "cannot_parse_line" << readALine << endl; // if parsing failed
        }
    }

    // now i need to create the sub-tensors and find each of their sums, then compare them with the targetted sum
    // also i need to keep the count of the number of sub-tensors that are equal to the target sum when added
    // for this i need starting and ending coordinates for the sub-tensors and i will keep iterating over them with nested loops

    int countOfTargetSubTensors = 0; //setting a counter to count the output
    //starting points first
    for(int s_a = 0; s_a < width; s_a  ++){
        for(int s_b = 0; s_b < length; s_b ++){
            for(int s_c = 0; s_c < depth; s_c ++){
                //now ending points
                for(int e_a = s_a; e_a < width; e_a ++){
                    for(int e_b = s_b; e_b < length; e_b ++){
                        for(int e_c = s_c; e_c < depth; e_c ++){
                            //now i will compute the sum of each sub-tensor
                            double sumOfSubTensor = 0;
                            //now iterating through each element to add them up
                            for(int a_index = s_a; a_index <= e_a; a_index ++){
                                for( int b_index = s_b; b_index <= e_b; b_index ++){
                                    for(int c_index = s_c; c_index <= e_c; c_index ++){
                                        sumOfSubTensor += tensorMatrix[a_index][b_index][c_index]; // calculating the sum by this statement
                                    }
                                }
                            }

                            //now here i will compare the sum to the target sum and increase the counter if they are equal
                            if(sumOfSubTensor == targettedSum){
                                countOfTargetSubTensors ++;
                            }

                        }
                    }
                }
            }
        }
    }

    //now i will print the output (i.e. the number of sub-tensors that add up to the target sum)
    cout << countOfTargetSubTensors << endl;


    // close the file at the end
    dataFile.close();

    return 0; //success
}