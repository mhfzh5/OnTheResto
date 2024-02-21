#include "Driver_Cust.h"
#include "Restoran.h"

int main()
{
    listResto LR; adr_resto R; infotypeR dataR; createListRestoran(LR);
    listDriver LD; adr_driver D; infotypeD dataD; createListDriver(LD);
    adr_cust C; infotypeC dataC;

    int menu;
    bool status = 1;
    do {
        selectedMenu();
        cin >> menu;
        cout << "=================================================" << endl << endl;
        switch(menu){
        case 1:
            Restaurant(LR, R, LD);
            break;
        case 2:
            KelolaDriver(LD, D);
            break;
        case 3:
            KelolaCustomer(LD, D, C, LR, R);
            break;
        case 4:
            showAllDriverCustRest(LD, LR);
            break;
        case 0:
            status = 0;
            break;
        }
    } while(status != 0);
    return 0;
}
