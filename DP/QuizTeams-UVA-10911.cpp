#include <cstdio>
#include <algorithm>
#include <limits>
#include <cmath>

double distances[16][16];
double memo[1 << 16];
double MAX = std::numeric_limits<double>::max();
int target;
int N;

double matching(int matched) {

    if(memo[matched] > -1)
        return memo[matched];
    if(matched == target)
        return 0;

    int s1;
    int s2;
    int new_matched;

    double min = MAX;

    for(s1 = 0; s1 < 2*N; ++s1)
        if(!(matched & (1<<s1)))
         break;
    
    for(s2 = s1+1; s2 < 2*N; ++s2){
        if(!(matched & (1<<s2))) {
            new_matched = matched | (1<<s1);
            new_matched = new_matched | (1<<s2);

            min = std::min(min, distances[s1][s2] + matching(new_matched));
        }
    }

    return memo[matched] = min;
    
}

int main(){

    int students[16][2];
    double x, y;
    int n_case = 1;
    while(scanf("%d", &N), N) {
        for(int i = 0; i < 2*N; ++i){
            scanf("%*s %lf %lf", &x, &y);
            students[i][0] = x;
            students[i][1] = y;
        }

        for(int i = 0; i < 2*N-1; ++i) {
            for(int j = i+1; j < 2*N; ++j) 
                distances[i][j]= distances[j][i] = std::hypot(students[i][0] - students[j][0], students[i][1] - students[j][1]);
        }

        for(int i = 0; i < (1<<16); ++i) 
            memo[i] = -1;

        target = (1<<(2*N)) - 1;

        printf("Case %d: %.2lf\n", n_case++, matching(0));
    }

    return 0;
}