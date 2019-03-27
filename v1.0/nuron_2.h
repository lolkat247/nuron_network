#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <string>
#include <vector>
using namespace std;

//sigmoid
double sigmoid(float x){
    return 1/(1 + exp(-x));
};

//sigmoid prime
float sigmoid_p(float x){
    return ((1/(1 + exp(-x))) * (1 - (1/(1 + exp(-x)))));
};

//predict final
float determine_2(float var1, float var2, float w1, float w2, float b){
    float z = var1 * w1 + var2 * w2 + b;
    float pred = sigmoid(z);
    return pred;
};

// define random number in range functon
int randint(int r){
    return rand() % r;
};

// check if file exists
bool fexists(const std::string& filename) {
    ifstream ifile(filename.c_str());
    ifile.close();
    return (bool)ifile;
};

int nuron_tr2(const string nuron_name, float &ow1, float &ow2, float &ob, bool alg = false){
    cout << fixed;

    // set seed for rand
    srand((unsigned)time(0));

    // hold line num
    int line_num = 0;

    // reserve data array and prep for data loading
    vector< vector<float> > dat;

    // check if a dat file is open or not, if its not; create one
    if (fexists(nuron_name+".txt")) {

        //check file
        if (alg){
            cout << nuron_name << ": File acknowledged." << endl;
        };
        ifstream file;
        file.open(nuron_name+".txt", ios::in);

        //load file
        if (file.is_open()){
            if(alg){
                cout << nuron_name << ": File loaded." << endl;
            };

            //load dat
            string line;
            int ln = 0;
            int sn = 0;
            int vlc = 0;
            stringstream linestream;
            string segment;

            //get line count 
            while (getline(file, line)){
                vlc++;
            };

            file.clear();
            file.seekg(0, ios::beg);

            //use temp vector
            vector< vector<float> > tempdat (vlc, vector<float>(3));

            //parsing crap
            while (getline(file, line)){
                linestream << line;
                while (getline(linestream, segment, ';')){
                    tempdat[ln][sn] = strtof((segment).c_str(),0);
                    sn += 1;
                    if (sn == 3){
                        sn = 0;
                        break;
                    };
                };
                linestream.clear();
                ln += 1;
            };
            file.close();
            line_num = vlc;
            //define true data 
            dat = tempdat;
        };
    }
    else {
        cout << nuron_name << ": No data file to load, making new file" << flush;
        ofstream file (nuron_name+".txt");
        ofstream index_file;
        index_file.open("nuron_index.txt", ios::app);
        index_file << nuron_name << ".txt" << endl;
        file << "0;0;0\n4;4;0\n6;6;1\n9;9;1" << endl;
        cout << "...done" << endl;
        cout << nuron_name << ": Please exit and edit data file: " << nuron_name+".txt" << " accordingly." << endl;
        file.close();
        return 1;
    };

    // network start seed
    // using random numbers tends to make the AI unstable
    // you probably should leave these alone
    float w1 = .4445;
    float w2 = .4445;
    float b = .4445;

    // WARNING: Do NOT mess with these two unless you wanna screw something up
    float learning_rate = 0.0003;
    int loop_iterations = 10000000;

    // Don't touch anything past this point

    double z;
    int ri;
    float pred;
    float target;
    float cost;
    float dcost_pred;
    float dpred_dz;
    float dz_dw1;
    float dz_dw2;
    float dz_db;
    float dcost_dz;
    float dcost_dw1;
    float dcost_dw2;
    float dcost_db;
    // training loop
    int taken = time(NULL);
    for (int g = 0; g <= loop_iterations; g++){
        // use random point to train AI
        ri = randint(line_num);

        //main func
        z = dat[ri][0] * w1 + dat[ri][1] * w2 + b;
        pred = sigmoid(z);
        target = dat[ri][2];
        cost = pow((pred - target), 2);

        // WARNING: the following code is incredibly complex and should not be altered

        // how far off is the prediction
        dcost_pred = 2 * (pred - target);
        dpred_dz = sigmoid_p(z);

        // how far off are the weights and bias
        dz_dw1 = dat[ri][0];
        dz_dw2 = dat[ri][1];
        dz_db = 1;

        dcost_dz = dcost_pred * dpred_dz;

        dcost_dw1 = dcost_dz * dz_dw1;
        dcost_dw2 = dcost_dz * dz_dw2;
        dcost_db = dcost_dz * dz_db;

        w1 = w1 - learning_rate * dcost_dw1;
        w2 = w2 - learning_rate * dcost_dw2;
        b = b - learning_rate * dcost_db;
    };
    if (alg){
        cout << nuron_name << ": " << time(NULL) - taken << "s to train" << endl;
    };

    ow1 = w1;
    ow2 = w2;
    ob = b;

    return 0;
};