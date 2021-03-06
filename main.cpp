#include <vector>
#include <iostream>
#include <cmath>
#include <string>
#include <map>
#include <time.h>
#include <fstream>
#include <chrono>

using namespace std;
using namespace std::chrono;

// need to find the m = (n choose 2) amount of closest pairs

// Finds the M amount of closest pairs in set p
map<pair<double, int>, vector<int>> closestPairs(int m, map<int,vector<int>> p, ofstream &output){
  auto start = high_resolution_clock::now();
  map<pair<double, int>, vector<int>> ans; // Should be format of <pair#, x1,y1,x2,y2>

  // If there is no points or only one point in the set P, then there are no shortest pairs.
  if(p.size() == 0 || p.size() == 1){
    cout << "\n0 possible pairs.";
    output << "\n 0 possible pairs.";
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop-start);
    cout << "Runtime: " << duration.count() << "ms";
  }
  else if(p.size() >= 2){
    // Variables used in calculating the distance between two points
    int x1;
    int x2;
    int y1;
    int y2;
    int xsquared;
    int ysquared;
    int xplusy;
    double dist;
    int ansSize = 0;

    // Nested loop. p[i] is a vertex that has no pairs yet with the remaining points in the set
    for(int i = 0; i < p.size() - 1; i++){
      // All possible vertices left to make a pair with the first vertex
      for(int j = i+1; j < p.size(); j++){
        x1 = p[i].at(0);
        x2 = p[j].at(0);
        y1 = p[i].at(1);
        y2 = p[j].at(1);
        xsquared = (x1 - x2) * (x1 - x2);
        ysquared = (y1 - y2) * (y1 - y2);
        xplusy = xsquared + ysquared;
        dist = sqrt(xplusy);

        //cout << x1 << y1 << " | " << x2 << y2 << "\n";
        //cout << "distance: " << dist << "\n";

        ansSize = ans.size();
        // Inserts the number of the pair (ansSize), the Euclidean distance, and the list of vertices in the pair. Format is: <<dist, pair#>,x1,y1,x2,y2>
        ans.insert(pair<pair<double, int>, vector<int>>(pair<double, int>(dist, ansSize), vector<int>()));
        ans[pair<double, int>(dist, ansSize)].push_back(x1);
        ans[pair<double, int>(dist, ansSize)].push_back(y1);
        ans[pair<double, int>(dist, ansSize)].push_back(x2);
        ans[pair<double, int>(dist, ansSize)].push_back(y2);


      }
    }
    int pairnumber = 1;
    // Prints out the format that the information is entered into the mapping. It keeps track of M, printing out only until that number has been reached.
    for(map<pair<double, int>, vector<int>>::iterator it = ans.begin(); it != ans.end(); it++){
      if(m > 0){
        cout << "\nPair: " << pairnumber << "\nDistance " << it->first.first << "\n(x1,y1): (" << it->second.at(0) << "," << it->second.at(1) << ")\n(x2,y2): (" << it->second.at(2) << "," << it->second.at(3) <<")\n\n";
        output << "\nPair: " << pairnumber << "\nDistance " << it->first.first << "\n(x1,y1): (" << it->second.at(0) << "," << it->second.at(1) << ")\n(x2,y2): (" << it->second.at(2) << "," << it->second.at(3) <<")\n\n";
        m--;
        pairnumber++;
      }
      else if(m == 0){
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop-start);
        cout << "Runtime: " << duration.count() << "ms";
        break;
      }
    }

  }

  return ans;
}

// Prints option menu
void printMenu(){
    cout << "Select option: " << "\n1. Insert pair \n2. Generate n pairs \n3. Enter 'M'\n4. Find M closest pairs\n";
}

// Error checking for initial input to enter a pair or m value.
void setUp(string input, string m_input, int &m, bool &m_set, map<int,vector<int>> &p){
  while(1){
    while(1){
      // Tries to turn the input to a number. If it fails, then it is an invalid input type.
      try{
        stoi(input);
        break;
      }
      catch(invalid_argument s){
        cout << "\nInvalid option. Please enter '1', '2', '3', or '4'\n";
        printMenu();
        cin >> input;
      }
    }

    // If the input is 1 or 2
    if(stoi(input) == 1 || stoi(input) == 2 || stoi(input) == 3){
      // Check if input to M is an nonnegative integer less than or equal to (n choose 2) pairs of points in P.
      if(stoi(input) == 3){
        // Variable for checking that M is less than or equal to this.
        int nchoose2 = 1;
        int numerator = 1;
        int denominator = 1;

        // just subtract 2 off the size because nchoose2 is just -2 from numerator over the denominator. then divide by 2 again.
        for(int i = p.size(); i > p.size()-2; i--){
          nchoose2 = i * nchoose2;
        }
        nchoose2 = nchoose2 / 2;
        //cout << "nchoose2: " << nchoose2 << "\n";

        cout << "Enter M: ";
        cin >> m_input;
        // Checks that m_input is an integer. If it is not, go back to main menu. If it is, continue checking if it is a valid possible M.
        try{
          stoi(m_input);
          if(stoi(m_input) >= 0 && stoi(m_input) <= nchoose2){
            m = stoi(m_input);
            m_set = true;
            cout << "\nM = " << m << "\n";
            printMenu();
            cin >> input;
          }
          // If it reaches here, that means M is either negative or is larger than the possible amount of pairs of points.
          else if(stoi(m_input) < 0){
            cout << "\nPlease enter an nonnegative integer.\n";
            printMenu();
            cin >> input;
          }
          else if(stoi(m_input) > nchoose2){
            cout << "\nPlease enter smaller M or add more points.\n";
            printMenu();
            cin >> input;
          }
        }
        catch(invalid_argument s){
          cout << "\nPlease enter an nonnegative integer.\n";
          printMenu();
          cin >> input;
        }
      }

      // Adding a point to the set p
      if(stoi(input) == 1){
        string x;
        string y;
        cout << "Enter x value: ";
        cin >> x;
        cout << "Enter y value: ";
        cin >> y;

        // Checks that x and y are integers. If they are not, go back to the main menu. Else, add them repectively to the set with the format <point#, <x1,y1>>
        try{
          stoi(x);
          stoi(y);
          int pairs = p.size();

          cout << "\nAdded point " << pairs+1 << " at (" << stoi(x) << "," << stoi(y) << ")\n";
          p.insert(pair<int, vector<int>>(pairs, vector<int>()));
          p[pairs].push_back(stoi(x));
          p[pairs].push_back(stoi(y));

          printMenu();
          cin >> input;
        }
        catch(invalid_argument s){
          cout << "\nPlease enter integers only.\n";
          printMenu();
          cin >> input;
        }
      }

      // Randomly generates n pairs of points
      if(stoi(input) == 2){
        string n_input;
        int n;
        cout << "Enter n value: ";
        cin >> n_input;
        try{
          stoi(n_input);
          n = stoi(n_input);
          if(n < 0){
            cout << "\nPlease enter an nonnegative integer.\n";
            printMenu();
            cin >> input;
          }
          else if(n >= 0){
            srand(time(0));
            for(int i = 0; i < n; i++){
              int npairs = p.size();
              p.insert(pair<int, vector<int>>(npairs, vector<int>()));
              p[npairs].push_back(rand());
              p[npairs].push_back(rand());
            }
            cout << "\nSuccessfully entered " << n << " pairs.\n";
            printMenu();
            cin >> input;
          }
        }
        catch(invalid_argument s){
          cout << "\nPlease enter integers only.\n";
          printMenu();
          cin >> input;
        }
      }

    }
    // This option exits out of the setUp function only if there has been a valid M set before.
    else if(stoi(input) == 4){
      if(m_set == false){
        cout << "\nPlease set an M first\n";
        printMenu();
        cin >> input;
      }
      else{
        break;
      }
    }
    // If input option is any integer other than '1', '2', or '3'
    else{
      cout << "\nInvalid option. Please enter '1', '2', '3', or '4'\n";
      printMenu();
      cin >> input;
    }

  }
}

int main(){
    // set P has n=4 points
    ofstream output("output.txt");
    string input;
    string m_input;
    int m = 0;
    map<int, vector<int>> p;    // <point#, x,y>
    bool m_set = false;

    printMenu();
    cin >> input;
    setUp(input, m_input, m, m_set, p);
    //cout << "Finding the M=" << m << " closest pairs of points in P.\n";
    //cout << "Number of pairs in P: " << p.size() << "\n";
    closestPairs(m, p, output);

    return 0;
}
