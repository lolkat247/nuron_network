# nuron_network

Project aimed at allowing users to create custom nural networks in C++ without the hassle of learning calculus.

## Getting Started

These instructions will get you a copy of the headers and the functions inside them.

### Prerequisites

Things you should have:
* General C++ knowlege
* patience

## Explanation of functions

### Sigmoid
Used for probability.
```
var2 = sigmoid(var1);
```

### Sigmoid Prime
Used as internal function.
```
var2 = sigmoid_p(var1);
```

### Randint
Random integer between 0 and var1.
```
var2 = randint(var1);
```

### fexists
Check if a file exists for not, returns 1 on success.
```
if (fexists("file.txt")){
  //Some code
};
```

### nuron_tr?
Used to generate algorithm from training data.

* tr2 uses 2 weights,
* tr3 uses 3 weights,
* etc...

This function will create a file named with the string you provided + .txt (text file).
_YOU MUST EDIT THIS DATA IN ORDER FOR IT TO WORK!_
The data file created _MUST_ have an empty newline at the end or backp will not work.
The function nuron_tr? will return 0 on success and 1 on error.

Currently supports 2-3
```
float w1, w2, b
if (nuron_tr3("nuron1", w1, w2, b, true){ // True is optional, it allows debug output
  cout << "Algorithm not generated." << endl;
}
else {
  // next bit of code
};
```

### determine_?
Used to generate probable output based on algorithm and outputs to provided variables (float type).
Output will be: 0 < output < 1.

* _2 uses 2 weights,
* _3 uses 3 weights,
* etc...

```
float var1 = 1 // test points
float var2 = 1

float w1 = 0.5 // weights and bias
float w2 = 0.5
float b = 0.5

cout << determine_2(var1, var2, w1, w2, b) << endl;
```

### backp
Used to back propagate data into the training file.
```
string new_data_line = "2;4;1;0";
backp("nuron1", new_data_line);
```

## Deployment

Download newest version and #include all modules you'd like to use.
All nuron_3.h or higher files depend on nuron_2.h.

## Example

Test code:

main.cpp
```
#include "nuron_2.h"
#include "nuron_3.h"
using namespace std;

int main(){
    float aw1, aw2, aw3, ab, ar;
    nuron_tr3("nuron_1-1", aw1, aw2, aw3, ab, true);

    float var1, var2, var3;
    cout << "var1: ";
    cin >> var1;
    cout << "var2: ";
    cin >> var2;
    cout << "var3: ";
    cin >> var3;

    ar = determine_3(var1, var2, var3, aw1, aw2, aw3, ab);
    cout << ar << endl;

    return 0;
};
```

nuron_1-1.txt
```
0;0;0
4;4;0
6;6;1
9;9;1

```

**First Run**

Output:
```
nuron_1-1: No data file to load, making new file...done
nuron_1-1: Please exit and edit data file: nuron_1-1.txt accordingly.
var1: (cin)1
var2: (cin)1
var3: (cin)1
0.500000
```

**Second Run**

Output
```
nuron_1-1: File acknowledged.
nuron_1-1: File loaded.
nuron_1-1: 1s to train
var1: (cin)1
var2: (cin)1
var3: (cin)1
0.000048
```
## Authors

* **Jacob Iglesias** - *Initial work* - [lolkat247](https://github.com/lolkat247)

## License

This project is licensed under the GNU v3 License - see the [LICENSE.md](LICENSE.md) file for details.

## Acknowledgments

* [giant_nural_network](https://www.youtube.com/user/LogicGodTV)
* My friends over at [Stack Overflow](https://stackoverflow.com)
* Hat tip to anyone whose code was used.
