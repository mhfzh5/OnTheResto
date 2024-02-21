#include "Driver_Cust.h"
#include "Restoran.h"

void createListRestoran(listResto &LR) {
    firstRest(LR) = NULL;
}
adr_resto createElemenRestoran(infotypeR dataR) {
    adr_resto R = new elementResto;
    infoRest(R) = dataR;
    nextRest(R) = NULL;
    return R;
}
void insertLastRestoran(listResto &LR, adr_resto R) {
    adr_resto P = firstRest(LR);
    if (firstRest(LR) != NULL) {
        while (nextRest(P) != NULL) {
            P = nextRest(P);
        }
        nextRest(P) = R;
    } else {
        firstRest(LR) = R;
    }
}
void deleteRestoran(listResto &LR, adr_resto &R){
    adr_resto P, temp;
    if (firstRest(LR) != NULL){
        R = firstRest(LR);
        while (R != NULL && infoRest(R).stok != 0){
            R = nextRest(R);
        }
        if (R != NULL) {
            if (R == firstRest(LR)){
                deleteFirstRestoran(LR, temp);
            } else if (nextRest(R) == NULL){
                deleteLastRestoran(LR, temp);
            } else {
                P = firstRest(LR);
                while (nextRest(P) != R){
                    P = nextRest(P);
                }
                deleteAfterRestoran(LR, temp, P);
                R = P;
            }
        }
    } else {
        cout << "===== LIST DATA RESTORAN KOSONG =====" << endl << endl;
    }
}
void deleteFirstRestoran(listResto &LR, adr_resto &R) {
    if (firstRest(LR) != NULL) {
        if (nextRest(firstRest(LR)) != NULL) {
            R = firstRest(LR);
            firstRest(LR) = nextRest(R);
            nextRest(R) = NULL;
        } else {
            R = firstRest(LR);
            firstRest(LR) = NULL;
        }
    } else {
        cout << "===== LIST DATA RESTORAN KOSONG =====" << endl << endl;
    }

}
void deleteLastRestoran(listResto &LR, adr_resto &R) {
    if (firstRest(LR) != NULL) {
        if (nextRest(firstRest(LR)) != NULL) {
            adr_resto P = firstRest(LR);
            while (nextRest(nextRest(P)) != NULL) {
                P = nextRest(P);
            }
        R = nextRest(P);
        nextRest(P) = NULL;
        } else {
            R = firstRest(LR);
            firstRest(LR) = NULL;
        }
    } else {
        cout << "===== LIST DATA RESTORAN KOSONG =====" << endl << endl;
    }
}
void deleteAfterRestoran(listResto &LR, adr_resto &R, adr_resto Prec) {
    if (firstRest(LR) != NULL) {
        if (nextRest(firstRest(LR)) != NULL) {
            R = nextRest(Prec);
            nextRest(Prec) = nextRest(R);
            nextRest(R) = NULL;
        } else {
            R = firstRest(LR);
            firstRest(LR) = NULL;
        }
    } else {
        cout << "===== LIST DATA RESTORAN KOSONG =====" << endl << endl;
    }
}
void showAllRestoran(listResto LR) {
    adr_resto R = firstRest(LR);
    if (firstRest(LR) != NULL) {
        cout << endl << "======== TAMPILKAN DATA RESTORAN ========" << endl;
        while (R != NULL) {
            cout << "Nama Restoran  : " << infoRest(R).nama << endl;
            cout << "Stok menu      : " << infoRest(R).stok << endl;
            cout << "Harga menu     : " << infoRest(R).harga << endl << endl;
            R = nextRest(R);
        }
        cout << "=================================================" << endl << endl;
    } else {
        cout << endl << "========== LIST RESTORAN KOSONG ==========" << endl << endl;
    }
}
adr_resto findRestaurant(listResto LR, string nama){
    adr_resto R;
    if (firstRest(LR) != NULL){
        R = firstRest(LR);
        while (R != NULL && infoRest(R).nama != nama){
            R = nextRest(R);
        }
    }
    return R;
}
