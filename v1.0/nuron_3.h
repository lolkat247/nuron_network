/*
DEPENDS: nuron_2.h
*/
using namespace std;

//predict final
float determine_3(float var1, float var2, float var3, float w1, float w2, float w3, float b){
    float z = var1 * w1 + var2 * w2 + var3 * w3 + b;
    float pred = sigmoid(z);
    return pred;
};

int nuron_tr3(const string nuron_name, float &ow1, float &ow2, float &ow3, float &ob, bool alg = false){
    cout << fixed;

    // set seed for rand
    srand((unsigned)time(0));

    // reserve data array and prep for data loading
    vector< vector<float> > dat;

    // hold line num
    int line_num;

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
            if (alg){
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
            vector< vector<float> > tempdat (vlc, vector<float>(4));

            //parsing crap
            while (getline(file, line)){
                linestream << line;
                while (getline(linestream, segment, ';')){
                    tempdat[ln][sn] = strtof((segment).c_str(),0);
                    sn += 1;
                    if (sn == 4) {
                        sn = 0;
                        break;
                    };
                };
                linestream.clear();
                ln += 1;
            };
            dat = tempdat;
            line_num = vlc;
            //define true data 
        };
        file.close();
    }
    else {
        cout << nuron_name << ": No data file to load, making new file" << flush;
        ofstream file (nuron_name+".txt");
        ofstream index_file;
        index_file.open("nuron_index.txt", ios::app);
        index_file << nuron_name << ".txt" << endl;
        file << "0;0;0;0\n4;4;4;0\n6;6;6;1\n9;9;9;1" << endl;
        cout << "...done" << endl;
        cout << nuron_name << ": Please exit and edit data file: " << nuron_name+".txt" << " accordingly." << endl;
        file.close();
        return 1;
    };

    // network start seed
    // using random numbers tends to make the AI unstable
    // you probably should leave these alone
    float w1 = .5;
    float w2 = .5;
    float w3 = .5;
    float b = .5;

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
    float dz_dw3;
    float dz_db;
    float dcost_dz;
    float dcost_dw1;
    float dcost_dw2;
    float dcost_dw3;
    float dcost_db;
    // training loop
    int taken = time(NULL);
    for (int g = 0; g <= loop_iterations; g++){
        // use random point to train AI
        ri = randint(line_num);

        //main func
        z = dat[ri][0] * w1 + dat[ri][1] * w2 + dat[ri][2] * w3 + b;
        pred = sigmoid(z);
        target = dat[ri][3];
        cost = pow((pred - target), 2);

        // WARNING: the following code is incredibly complex and should not be altered

        // how far off is the prediction
        dcost_pred = 2 * (pred - target);
        dpred_dz = sigmoid_p(z);

        // how far off are the weights and bias
        dz_dw1 = dat[ri][0];

        dz_dw2 = dat[ri][1];
        dz_dw3 = dat[ri][2];
        dz_db = 1;

        dcost_dz = dcost_pred * dpred_dz;

        dcost_dw1 = dcost_dz * dz_dw1;
        dcost_dw2 = dcost_dz * dz_dw2;
        dcost_dw3 = dcost_dz * dz_dw3;
        dcost_db = dcost_dz * dz_db;

        w1 = w1 - learning_rate * dcost_dw1;
        w2 = w2 - learning_rate * dcost_dw2;
        w3 = w3 - learning_rate * dcost_dw3;
        b = b - learning_rate * dcost_db;
    };
    if (alg){
        cout << nuron_name << ": " << time(NULL) - taken << "s to train" << endl;
    };

    ow1 = w1;
    ow2 = w2;
    ow3 = w3;
    ob = b;

    return 0;
};