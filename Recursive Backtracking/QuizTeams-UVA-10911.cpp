#include <iostream>
#include <vector>
#include <limits>
#include <cmath>
#include <algorithm>

using namespace std;

double calculate_distance(int x1, int y1, int x2, int y2){
    double r1 = y2 - y1;
    double r2 = x2 - x1;
    return sqrt(r1*r1 + r2*r2);
}

bool fully_formed(bool* paired, int n){
    return (find(paired, paired+n, false) == paired+n);
}

bool* find_first(bool* paired, int n) {
    return find(paired, paired+n, false);
}

double get_best(const vector<vector<int>>& students, double& curr_sum, double& min, bool* paired) {

    if(curr_sum >= min)
        return 1;

    if(fully_formed(paired, students.size())) {
         min = std::min(min, curr_sum);
         return 1;
    }

    int position_first = (int)(find_first(paired, students.size()) - paired);

    paired[position_first] = true;
    double distance = 0;
    for(int i = position_first+1; i < students.size(); ++i) {
        
        if(paired[i] == false){
            paired[i] = true;
            distance = calculate_distance(students[position_first][0],students[position_first][1], 
            students[i][0],students[i][1] );
            curr_sum += distance;
            get_best(students, curr_sum, min, paired);
            curr_sum -= distance;
            paired[i] = false;
        }
        
    }

    paired[position_first] = false;

    return min;
}



int main() {
    double MIN = numeric_limits<double>::max();
    int N;
    int x;
    int y;
    double min;
    double curr_sum;
    string name;
    vector<vector<int>> students;
    vector<int> coordinates;
    int my_case = 1;
    do{
        cin>>N;
        if(N == 0)
            break;

        bool* paired = new bool[2*N];

        for(int i = 0; i < 2*N; ++i) {
            paired[i] = false;
            cin>>name>>x>>y;
            coordinates.push_back(x);
            coordinates.push_back(y);
            
            students.push_back(coordinates);
            coordinates.clear();

        }
        //paired[0] = true;
        //paired[1] = true;
        //cout<<fully_formed(paired, students.size());
        //int position_first = (int)(find_first(paired, students.size()) - paired);
        //cout<<position_first<<endl;
    
        curr_sum = 0;
        min = MIN;
        //cout<< "Case "<<my_case<<": "<<get_best(students, curr_sum, min, paired)<<endl;     
        printf("Case %d: %.2f\n", my_case,get_best(students, curr_sum, min, paired));
        my_case++;
        delete[] paired;
        students.clear();

    
    }while(N != 0);

    return 0;
}