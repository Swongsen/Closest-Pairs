#include <vector>
#include <iostream>
#include <cmath>
#include <string>
#include <map>

using namespace std;
#define n 4 // number of points

// need to find the m = (n choose 2) amount of closest pairs

// Finds the M amount of closest pairs in set p
map<pair<int, double>, vector<int>> closestPairs(int m, map<int,vector<int>> p){
  map<pair<int, double>, vector<int>> ans; // Should be format of <pair#, x1,y1,x2,y2>

  // If there is no points or only one point in the set P, then there are no shortest pairs.
  if(p.size() == 0 || p.size() == 1){
    cout << "0 Pairs";
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

        cout << x1 << y1 << " | " << x2 << y2 << "\n";
        cout << "distance: " << dist << "\n";

        ansSize = ans.size();
        ans.insert(pair<pair<int, double>, vector<int>>(pair<int,double>(ansSize, dist), vector<int>()));
        ans[pair<int,double>(ansSize, dist)].push_back(x1);
        ans[pair<int,double>(ansSize, dist)].push_back(y1);
        ans[pair<int,double>(ansSize, dist)].push_back(x2);
        ans[pair<int,double>(ansSize, dist)].push_back(y2);


      }
    }

    for(map<pair<int, double>, vector<int>>::iterator it = ans.begin(); it != ans.end(); it++){
      if(m > 0){
        cout << "Pair " << it->first.first << "\nDistance: " << it->first.second << "\n(x1,y1): (" << it->second.at(0) << "," << it->second.at(1); ;
        m--;
      }
      else if(m == 0){
        break;
      }
    }

  }

  return ans;
}

// Prints option menu
void printMenu(){
    cout << "Select option: " << "\n1. Insert pair \n2. Enter 'M'\n3. Find M closest pairs\n";
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
        cout << "\nInvalid option. Please enter '1', '2', or '3'\n";
        printMenu();
        cin >> input;
      }
    }

    // If the input is 1 or 2
    if(stoi(input) == 1 || stoi(input) == 2){
      // Check if input to M is an nonnegative integer less than or equal to (n choose 2) pairs of points in P.
      if(stoi(input) == 2){
        // Variable for checking that M is less than or equal to this.
        int nchoose2;
        int numerator = 1;
        int denominator = 1;
        for(int i = p.size(); i > 0; i--){
          numerator = numerator * i;
        }
        for(int i = p.size()-2; i > 0; i--){
          denominator = denominator * i;
        }
        denominator = denominator * 2;
        nchoose2 = numerator / denominator;
        //cout << "nchoose2: " << nchoose2 << "\n";

        cout << "Enter M: ";
        cin >> m_input;
        try{
          stoi(m_input);
          if(stoi(m_input) >= 0 && stoi(m_input) <= nchoose2){
            m = stoi(m_input);
            m_set = true;
            cout << "\nM = " << m << "\n";
            printMenu();
            cin >> input;
          }
          else if(stoi(m_input) < 0){
            cout << "\nPlease enter a nonnegative integer.\n";
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
          cout << "\nPlease enter a nonnegative integer.\n";
          printMenu();
          cin >> input;
        }
      }

      if(stoi(input) == 1){
        string x;
        string y;
        cout << "Enter x value: ";
        cin >> x;
        cout << "Enter y value: ";
        cin >> y;

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

    }
    // This option exits out of the setUp function only if there has been a valid M set before.
    else if(stoi(input) == 3){
      if(m_set == false){
        cout << "\nPlease set an M first\n";
        printMenu();
        cin >> input;
      }
      else{
        break;
      }
    }
    else if(stoi(input) == 4){
      for(map<int,vector<int>>::iterator it = p.begin(); it != p.end(); it++){
        cout << "Point " << it->first + 1 << ":" ;
        for(int i = 0; i < it->second.size(); i++){
          cout << it->second.at(i) << ",";
        }
        cout << "\n";
      }
      cout << "\n";
      printMenu();
      cin >> input;
    }
    // If input option is any integer other than '1', '2', or '3'
    else{
      cout << "\nInvalid option. Please enter '1', '2', or '3'\n";
      printMenu();
      cin >> input;
    }

  }
}

main(){
    // set P has n=4 points

    string input;
    string m_input;
    int m = 0;
    map<int, vector<int>> p;    // <point#, x,y>
    bool m_set = false;

    printMenu();
    cin >> input;
    setUp(input, m_input, m, m_set, p);

    cout << "Finding the M=" << m << " closest pairs of points in P.\n";
    cout << "Number of pairs in P: " << p.size() << "\n";
    closestPairs(m, p);

    int pe[n][2] = {{1,2}, {4,5}, {7,11}, {4,8}};

}
