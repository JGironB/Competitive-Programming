#include <iostream>
#include <float.h>
#include <cmath>

using namespace std;

int arrayTamanio;

bool hayAlgo(int visitado [], int& i) {

    for(int c = 0; c < arrayTamanio; ++c) {

        if(visitado[c] == 0) {

            i = c;
            return true;
        }
    }

    return false;
}


void buscarDistancia(double costoActual, int visitado[], int coor[][2], double& D) {

    int i = 0;

    if(!hayAlgo(visitado,i)) {

        if(costoActual < D)
            D = costoActual;

        return;
    }

    double distanciaParcial = 0;

    visitado[i] = 1;

    for(int j = i + 1; j < arrayTamanio; ++j) {

        if(visitado[j] == 0) {

            distanciaParcial = sqrt(pow((double)(coor[i][0]-coor[j][0]), 2.0) + pow((double)(coor[i][1]-coor[j][1]), 2.0));
            costoActual += distanciaParcial;

            //PRUNNING
            if(costoActual < D) {
                visitado[j] = 1;
                buscarDistancia(costoActual, visitado, coor, D);
                visitado[j] = 0;
            }

            costoActual -= distanciaParcial;
        }
    }

    visitado[i] = 0;

    return;
}

int main() {

    int N;
    int c = 1;
    string name;
    int x, y;
    double D;

    while(cin >> N) {

        if(N == 0)
            break;

        int coor[2*N][2];
        int visitado[2*N] = {0};
        arrayTamanio = 2 * N;
        D = DBL_MAX;

        for(int i = 0; i < 2*N; ++i) {

            cin >> name >> x >> y;

            coor[i][0] = x;
            coor[i][1] = y;
        }

        buscarDistancia(0, visitado, coor, D);

        printf("Case %i: %.2f\n", c, D);

        ++c;
    }

    return 0;
}
