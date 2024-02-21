#ifndef DRIVER_CUST_H_INCLUDED
#define DRIVER_CUST_H_INCLUDED
#include <iostream>
#include "Driver_Cust.h"
#include "Restoran.h"
using namespace std;
#define infoDriver(P) (P)->infoDriver
#define nextDriver(P) (P)->nextDriver
#define prevDriver(P) (P)->prevDriver
#define infoCust(P)   (P)->infoCust
#define nextCust(P)   (P)->nextCust
#define prevCust(P)   (P)->prevCust
#define nextRC(P)     (P)->nextRC
#define firstDriver(L)((L).firstDriver)
#define lastDriver(L) ((L).lastDriver)
#define firstCust(L)  ((L)->firstCust)
#define lastCust(L)   ((L)->lastCust)

typedef struct elementDriver *adr_driver;
typedef struct elementCust *adr_cust;
struct driver {
	string nama, id, status;
	int countCust = 0;
};
struct customer {
	string nama, noHP, status, orderTo;
	int jumlahOrder;
};
typedef driver infotypeD;
typedef customer infotypeC;
struct listDriver {
	adr_driver firstDriver, lastDriver;
};
struct elementDriver {
    infotypeD infoDriver;
	adr_driver nextDriver, prevDriver;
	adr_cust firstCust;
	adr_cust lastCust;
};
struct elementCust {
	infotypeC infoCust;
	adr_cust nextCust, prevCust;
	adr_resto nextRC;
};

void selectedMenu();
void createListDriver(listDriver &LD);
adr_driver createElemenDriver(infotypeD dataD);
adr_cust createElemenCust(infotypeC dataC, adr_resto R);
void insertLastDriver(listDriver &LD, adr_driver D);
void insertLastCust(listDriver &LD, adr_driver D, adr_cust C, listResto LR, string resto);
void deleteFirstDriver(listDriver &LD, adr_driver &D);
void deleteAfterDriver(listDriver &LD, adr_driver precDriver, adr_driver &D);
void deleteLastDriver(listDriver &LD, adr_driver &D);
void deleteDriver(listDriver &LD, adr_driver &D, string ID);
void deleteCust(listDriver &LD, adr_driver &D, adr_cust &C);
void deleteFirstCust(listDriver &LD, adr_driver &D, adr_cust &C);
void deleteAfterCust(listDriver &LD, adr_driver &D, adr_cust precCust, adr_cust &C);
void deleteLastCust(listDriver &LD, adr_driver &D, adr_cust &C);
adr_driver findDriverByID(listDriver LD, string ID);
void findCustByNoHP(listDriver LD, adr_driver &D, string number, adr_cust &C);
int countCustByDriver(adr_driver D, adr_cust C);
void countAllCustInDriver(listDriver LD, adr_driver &D, adr_cust &C);
int countCustByRest(listDriver LD, listResto LR, adr_resto R);
int countRestNoCust(listDriver LD, listResto LR, adr_resto R);
int countRestInDriver(adr_driver D);
void countAllRestInDriver(listDriver LD, adr_driver D);
void showAllDriver(listDriver LD);
void showAllDriverCust(listDriver LD, listResto LR);
void showDriverToRest(listDriver LD, listResto LR, adr_resto R);
void showDriverFromAllRest(listDriver LD, listResto LR);
void showAllDriverCustRest(listDriver LD, listResto LR);
void showOneDriver(listDriver LD, adr_driver D);
void showOneCustomer(listDriver LD, adr_driver D, adr_cust C, adr_resto R);
void showCustByDriver(listDriver LD, listResto LR, adr_driver D, adr_cust C, string ID);
void updateStatusMasakan(listDriver &LD, listResto &LR, adr_resto R);
void GantiDriver(listDriver &LD, listResto &LR, adr_driver &DSebelum, adr_driver &DSetelah, adr_cust &C);
void KelolaDriver(listDriver &LD, adr_driver &D);
void KelolaCustomer(listDriver &LD, adr_driver &D, adr_cust &C, listResto LR, adr_resto R);
void Restaurant(listResto &LR, adr_resto R, listDriver LD);

#endif // DRIVER_CUST_H_INCLUDED
