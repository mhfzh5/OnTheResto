#ifndef RESTORAN_H_INCLUDED
#define RESTORAN_H_INCLUDED
#include "Driver_Cust.h"
#include "Restoran.h"
using namespace std;
#define infoRest(P) (P)->infoRest
#define nextRest(P) (P)->nextRest
#define nextRC(P)   (P)->nextRC
#define firstRest(L)((L).firstRest)

struct restoran {
	string nama;
	int stok, harga;
};
typedef restoran infotypeR;
typedef struct elementResto *adr_resto;
struct elementResto {
    infotypeR infoRest;
	adr_resto nextRest;
};
struct listResto {
	adr_resto firstRest;
};


void createListRestoran(listResto &LR);
adr_resto createElemenRestoran(infotypeR dataR);
void insertLastRestoran(listResto &LR, adr_resto R);
void deleteRestoran(listResto &LR, adr_resto &R);
void deleteFirstRestoran(listResto &LR, adr_resto &R);
void deleteLastRestoran(listResto &LR, adr_resto &R);
void deleteAfterRestoran(listResto &LR, adr_resto &R, adr_resto Prec);
void showAllRestoran(listResto LR);
adr_resto findRestaurant(listResto LR, string nama);

#endif // RESTORAN_H_INCLUDED
