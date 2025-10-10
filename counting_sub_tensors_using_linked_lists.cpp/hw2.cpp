// Petek Karagedik 34042
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <limits>
using namespace std;

// i will represent each element in the tensor with a node
struct node{

    double val;
    node * horizontal; // pointer to the next element of that row
    node * vertical; // pointer to the next element of that column
    node * indepth; // pointer to the next element in depth

};

// now function to initialize the empty 3d matrix
node *** emptyMatrix3D(int width, int length, int depth){
    node *** matrix_3d = new node **[width]; // creating the 3d matrix

    for (int i = 0; i < width; i++){
        matrix_3d[i] = new node *[length];
        for (int j = 0; j < length; j++){
            matrix_3d[i][j] = new node [depth];
            for ( int k = 0; k < depth; k++){
                matrix_3d[i][j][k].val = 0; // initialize to 0
            }
        }
    }
    return matrix_3d;
} 

// funtion to set non-zeros in place
void nonZeroValuePlacer( node *** & matrix_3d, double val, int x_coord, int y_coord, int z_coord){
    matrix_3d[x_coord][y_coord][z_coord].val = val;
}

// give the memory back to heap for future efficiency
void giveBackMemory( node *** & matrix_3d, int width, int length, int depth ){
    for ( int p = 0; p < width; p++ ){
        for ( int q = 0; q < length; q++ ){
            delete [] matrix_3d[p][q];
        }
        delete [] matrix_3d[p];
    }
    delete [] matrix_3d;
}

// sum of sub tensors that add up to the target sum
int countSubTensors(node *** matrix_3d, int width, int length, int depth, double targetted_sum){

    int counter = 0;
    //iterating over starting points
    for ( int s_a = 0; s_a < width; s_a++ ){
        for ( int s_b = 0; s_b < length; s_b++ ){
            for ( int s_c = 0; s_c < depth; s_c++ ){
                // iterating through ending points
                for ( int e_a = s_a; e_a < width; e_a++ ){
                    for ( int e_b = s_b; e_b < length; e_b++ ){
                        for ( int e_c = s_c; e_c < depth; e_c++ ){

                            double sum_to_compare = 0;

                            for ( int k = s_a; k <= e_a; k++ ){
                                for ( int l = s_b; l <= e_b; l++ ){
                                    for ( int m = s_c; m <= e_c; m++){

                                        sum_to_compare += matrix_3d[k][l][m].val;

                                    }
                                }
                            }

                            if ( sum_to_compare == targetted_sum){
                                counter++;
                            }
                            
                        }
                    }
                }
            }
        }
    }

    return counter;
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

    dataFile.ignore(numeric_limits<streamsize>::max(), '\n'); //cleans the remaining chars

    node *** tensorMatrix = emptyMatrix3D(width, length, depth);

    for (int i = 0; i < lineCount; i++){
        string readALine;
        getline (dataFile, readALine); // to read each line one by one

        //to get the values from each line:
        istringstream iss(readALine);
        int a, b, c;
        double valueOfElem;

        if (iss >> a >> b >> c >> valueOfElem){
            nonZeroValuePlacer(tensorMatrix, valueOfElem, a, b, c); // adding the nonzero values to matrix
        }else{
            cerr << "cannot_parse_line" << readALine << endl; // if parsing failed
        }
    }

    // printing the result with the function
    cout << countSubTensors(tensorMatrix, width, length, depth, targettedSum) << endl;

    giveBackMemory(tensorMatrix, width, length, depth); // returning all the memory used for further efficiency

    // close the file at the end
    dataFile.close();

    return 0; //success
}