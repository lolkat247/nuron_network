/*
DEPENDS: nuron_2.h
*/
using namespace std;

int nuron_backp(string nuron_name, string aline, bool alg = false){
    ifstream index;
    index.open("nuron_index.txt", ios::in);

    string line;
    bool exists;
    while (getline(index, line)){
        if (nuron_name + ".txt" == line){
            exists = true;
            if (alg){
                cout << "backp: File in index" << endl;
            };
        };
    };
    index.close();

    if (exists){
        ofstream file;
        file.open(nuron_name + ".txt", ios::app);
        file << aline << endl;
        if (alg){
            cout << "backp: Line posted" << endl;
        }
        file.close();
    }
    else {
        if (alg){
            cout << "backp: File not in index (check if filename is listed in \"nuron_index\")" << endl;
            cout << "backp: Cannot back propagate" << endl;
        };
        return 1;
    };

    return 0;
};