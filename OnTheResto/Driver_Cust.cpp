#include "Driver_Cust.h"
#include "Restoran.h"

void createListDriver(listDriver &LD) {
    firstDriver(LD) = NULL;
    lastDriver(LD) = NULL;
}
adr_driver createElemenDriver(infotypeD dataD) {
    adr_driver D = new elementDriver;
    infoDriver(D) = dataD;
    nextDriver(D) = NULL;
    prevDriver(D) = NULL;
    firstCust(D) = NULL;
    lastCust(D) = NULL;
    return D;
}
adr_cust createElemenCust(infotypeC dataC, adr_resto R) {
    adr_cust C = new elementCust;
    infoCust(C) = dataC;
    nextCust(C) = NULL;
    prevCust(C) = NULL;
    nextRC(C) = R;
    return C;
}
void insertLastDriver(listDriver &LD, adr_driver D) {
    if (firstDriver(LD) != NULL) {
        nextDriver(D) = firstDriver(LD);
        prevDriver(D) = lastDriver(LD);
        prevDriver(firstDriver(LD)) = D;
        nextDriver(lastDriver(LD)) = D;
        lastDriver(LD) = D;
    } else {
        firstDriver(LD) = D;
        lastDriver(LD) = D;
        nextDriver(D) = D;
        prevDriver(D) = D;
    }
}
void insertLastCust(listDriver &LD, adr_driver D, adr_cust C, listResto LR, string resto) {
    adr_resto foundResto = findRestaurant(LR, resto);
    if (foundResto != NULL &&  infoRest(foundResto).stok - infoCust(C).jumlahOrder >= 0){
        D = firstDriver(LD);
        do {
            if (infoDriver(D).countCust < 3 && infoDriver(D).status == "Available") {
                break;
            }
            D = nextDriver(D);
        }while (D != firstDriver(LD) && infoDriver(D).countCust >= 3 || infoDriver(D).status == "Non-Available");
        if (infoDriver(D).countCust < 3) {
            if (firstCust(D) != NULL) {
                nextCust(lastCust(D)) = C;
                prevCust(C) = lastCust(D);
                lastCust(D) = C;
                infoDriver(D).countCust++;
            } else {
                firstCust(D) = C;
                lastCust(D) = C;
                infoDriver(D).countCust++;
            }
            nextRC(C) = foundResto;
            infoRest(foundResto).stok -= infoCust(C).jumlahOrder;
        } else {
            cout << endl << "========== DRIVER TIDAK TERSEDIA ==========" << endl << endl;
        }

    } else {
        cout << endl << "========== RESTO TIDAK TERSEDIA ==========" << endl << endl;
    }
}
void deleteFirstDriver(listDriver &LD, adr_driver &D){
    if (firstDriver(LD) != NULL){
        D = firstDriver(LD);
        if (nextDriver(D) != firstDriver(LD)){
            nextDriver(lastDriver(LD)) = nextDriver(D);
            prevDriver(nextDriver(D)) = lastDriver(LD);
            firstDriver(LD) = nextDriver(D);
            nextDriver(D) = NULL;
            prevDriver(D) = NULL;
        } else {
            firstDriver(LD) = NULL;
            lastDriver(LD) = NULL;
        }
    } else {
        cout << endl << "========== LIST DRIVER KOSONG ==========" << endl << endl;
    }
}
void deleteAfterDriver(listDriver &LD, adr_driver precDriver, adr_driver &D){
    D = nextDriver(precDriver);
    nextDriver(precDriver) = nextDriver(D);
    prevDriver(nextDriver(D)) = precDriver;
    nextDriver(D) = NULL;
}
void deleteLastDriver(listDriver &LD, adr_driver &D){
    if (firstDriver(LD) != NULL){
        D = lastDriver(LD);
        if (nextDriver(D) != lastDriver(LD)){
            nextDriver(prevDriver(D)) = firstDriver(LD);
            prevDriver(firstDriver(LD)) = prevDriver(D);
            lastDriver(LD) = prevDriver(D);
            nextDriver(D) = NULL;
            prevDriver(D) = NULL;
        } else {
            firstDriver(LD) = NULL;
            lastDriver(LD) = NULL;
        }
    } else {
        cout << endl << "========== LIST DRIVER KOSONG ==========" << endl << endl;
    }
}
void deleteDriver(listDriver &LD, adr_driver &D, string ID){
    adr_driver foundDriver;
    if (firstDriver(LD) != NULL){
        foundDriver = findDriverByID(LD, ID);
        if (foundDriver != NULL){
            if (foundDriver == firstDriver(LD)){
                deleteFirstDriver(LD, D);
            } else if (foundDriver == lastDriver(LD)){
                deleteLastDriver(LD, D);
            } else {
                deleteAfterDriver(LD, prevDriver(foundDriver), D);
            }
        } else {
            cout << endl << "========== ID DRIVER TIDAK DITEMUKAN ==========" << endl << endl;
        }
    }
}
void deleteFirstCust(listDriver &LD, adr_driver &D, adr_cust &C){
    if (firstCust(D) != NULL){
        C = firstCust(D);
        if (nextCust(C) != NULL){
            firstCust(D) = nextCust(C);
            nextCust(C) = NULL;
            prevCust(firstCust(D)) = NULL;
        } else {
            firstCust(D) = NULL;
            lastCust(D) = NULL;
        }
    } else {
        cout << endl << "========== LIST CUSTOMER KOSONG ==========" << endl << endl;
    }
}
void deleteAfterCust(listDriver &LD, adr_driver &D,adr_cust precCust, adr_cust &C){
    if (nextCust(nextCust(precCust)) == NULL) {
        C = nextCust(precCust);
        nextCust(precCust) = NULL;
        prevCust(nextCust(C)) = NULL;
    } else {
        C = nextCust(precCust);
        nextCust(precCust) = nextCust(C);
        prevCust(nextCust(C)) = precCust;
        nextCust(C) = NULL;
        prevCust(C) = NULL;
    }

}
void deleteLastCust(listDriver &LD, adr_driver &D, adr_cust &C){
    if (lastCust(D) != NULL){
        C = lastCust(D);
        if (prevCust(C) != NULL){
            lastCust(D) = prevCust(C);
            nextCust(lastCust(D)) = NULL;
            prevCust(C) = NULL;
        } else {
            firstCust(D) = NULL;
            lastCust(D) = NULL;
        }
    } else {
        cout << endl << "========== LIST CUSTOMER KOSONG ==========" << endl << endl;
    }
}
void deleteCust(listDriver &LD, adr_driver &D, adr_cust &C){
    adr_cust P;
    if (C == firstCust(D)){
        deleteFirstCust(LD, D, C);
    } else if (C == lastCust(D)){
        deleteLastCust(LD, D, C);
    } else {
        deleteAfterCust(LD, D, prevCust(C), C);
    }
    infoDriver(D).countCust--;
}
adr_driver findDriverByID(listDriver LD, string ID){
    adr_driver D;
    if (firstDriver(LD) != NULL){
        D = firstDriver(LD);
        do {
            D = nextDriver(D);
        } while (D != firstDriver(LD) && infoDriver(D).id != ID);
        if (infoDriver(D).id == ID){
            return D;
        }
    }
    return NULL;
}
void findCustByNoHP(listDriver LD, adr_driver &D, string number, adr_cust &C){
    adr_driver X;
    D = NULL;
    if (firstDriver(LD) != NULL){
        X = firstDriver(LD);
        do {
            if (firstCust(X) != NULL){
                C = firstCust(X);
                while (C != NULL && infoCust(C).noHP != number){
                    C = nextCust(C);
                }
                if (C != NULL && infoCust(C).noHP == number){
                    D = X;
                    break;
                }
            }
            X = nextDriver(X);
        } while (X != firstDriver(LD));
    }
    if (X == NULL) {
        cout << "Pelanggan tidak ditemukan." << endl;
        C = NULL;
    }
}
int countCustByDriver(adr_driver D, adr_cust C){
    int n = 0;
    if (firstCust(D) != NULL) {
        C = firstCust(D);
        while (C != NULL) {
            n++;
            C = nextCust(C);
        }
    }
    return n;
}
void countAllCustInDriver(listDriver LD, adr_driver &D, adr_cust &C){
    D = firstDriver(LD);
    int i = 1;
    do {
        cout << "Data ke-" << i << endl;
        cout << "Nama Driver    : " << infoDriver(D).nama << endl;
        cout << "ID Driver      : " << infoDriver(D).id << endl;
        int totalCust = countCustByDriver(D, C);
        cout << "Total Customer pada Driver: " << totalCust << endl;
        i++;
        D = nextDriver(D);
    } while(D != firstDriver(LD));
}
int countRestNoCust(listDriver LD, listResto LR, adr_resto R){
    int total = 0;
    R = firstRest(LR);
    while (R != NULL) {
        bool found = false;
        adr_driver D = firstDriver(LD);
        do {
            adr_cust C = firstCust(D);
            while (C != NULL && !found) {
                if (R == nextRC(C)) {
                    found = true;
                }
                C = nextCust(C);
            }
            D = nextDriver(D);
        } while(D != firstDriver(LD));
        if (!found) {
            total++;
        }
        R = nextRest(R);
    }
    return total;
}
int countCustByRest(listDriver LD, listResto LR, adr_resto R){
    adr_driver D;
    adr_cust C;
    int i = 0;
    if (firstDriver(LD) != NULL){
        D = firstDriver(LD);
        do {
            if (firstCust(D) != NULL){
                C = firstCust(D);
                while (C != NULL){
                    if (nextRC(C) == R){
                        i++;
                    }
                    C = nextCust(C);
                }
            }
            D = nextDriver(D);
        } while (D != firstDriver(LD));
    }
    return i;
}
int countRestInDriver(adr_driver D){
    int i = 0;
    if (firstCust(D) != NULL) {
        adr_cust C = firstCust(D);
        while (C != NULL) {
            adr_cust P = nextCust(C);
            while (P != NULL && infoCust(P).orderTo != infoCust(C).orderTo) {
                P = nextCust(P);
            }
            if (P == NULL) {
                i++;
            }
            C = nextCust(C);
        }
    }
    return i;
}
void countAllRestInDriver(listDriver LD, adr_driver D){
    D = firstDriver(LD);
    int i = 1;
    do {
        cout << "Data ke-" << i << endl;
        cout << "Nama Driver    : " << infoDriver(D).nama << endl;
        cout << "ID Driver      : " << infoDriver(D).id << endl;
        int totalRest = countRestInDriver(D);
        cout << "Total Restoran pada Driver: " << totalRest << endl;
        i++;
        D = nextDriver(D);
    } while(D != firstDriver(LD));
}
void showAllDriver(listDriver LD) {
    adr_driver D = firstDriver(LD);
    int i = 1;
    if (firstDriver(LD) != NULL) {
        cout << endl << "======== TAMPILKAN DATA DRIVER ========" << endl;
        do {
            cout << "Data ke-" << i << endl;
            cout << "Nama Driver    : " << infoDriver(D).nama << endl;
            cout << "ID Driver      : " << infoDriver(D).id << endl;
            cout << "Status Driver  : " << infoDriver(D).status << endl;
            cout << "Jumlah Customer: " << infoDriver(D).countCust << endl << endl;
            D = nextDriver(D);
            i++;
        } while(D != firstDriver(LD));
        cout << "=================================================" << endl << endl;
    } else {
        cout << endl << "========== LIST DRIVER KOSONG ==========" << endl << endl;
    }
}
void showAllDriverCust(listDriver LD, listResto LR) {
    adr_driver D = firstDriver(LD);
    int i = 1;
    if (firstDriver(LD) != NULL) {
        cout << endl << "======== TAMPILKAN DATA DRIVER & CUSTOMER ========" << endl;
        do {
            cout << "Data ke-" << i << endl;
            cout << "Nama Driver    : " << infoDriver(D).nama << endl;
            cout << "ID Driver      : " << infoDriver(D).id << endl;
            cout << "Status Driver  : " << infoDriver(D).status << endl;
            cout << "Jumlah Customer: " << infoDriver(D).countCust << endl;
            adr_cust C = firstCust(D);
            while (C != NULL) {
                adr_resto foundResto = findRestaurant(LR, infoCust(C).orderTo);
                cout << "==============" << endl;
                showOneCustomer(LD, D, C, foundResto);
                C = nextCust(C);
            }
            cout << endl;
            i++;
            D = nextDriver(D);
        } while(D != firstDriver(LD));
        cout << "=================================================" << endl << endl;
    } else {
        cout << endl << "========== DATA DRIVER & CUSTOMER KOSONG ==========" << endl << endl;
    }
}
void showOneDriver(listDriver LD, adr_driver D){
    cout << "Nama Driver     : " << infoDriver(D).nama << endl;
    cout << "ID Driver       : " << infoDriver(D).id << endl;
    cout << "Status Driver   : " << infoDriver(D).status << endl;
    cout << "Jumlah Customer : " << infoDriver(D).countCust << endl;
    cout << endl;
}
void showOneCustomer(listDriver LD, adr_driver D, adr_cust C, adr_resto R){
    cout << "Nama Customer\t\t: " << infoCust(C).nama << endl;
    cout << "No HP Customer\t\t: " << infoCust(C).noHP << endl;
    cout << "Jumlah Order\t\t: " << infoCust(C).jumlahOrder << endl;
    cout << "Status Customer\t\t: " << infoCust(C).status << endl;
    cout << "Pesanan Customer\t: " << infoCust(C).orderTo << endl;
    cout << "Total Pesanan Customer\t: " << infoRest(R).harga * infoCust(C).jumlahOrder << endl;
    cout << endl;
}
void showDriverToRest(listDriver LD, listResto LR, adr_resto R){
    adr_driver D;
    adr_cust C; int i;
    if (firstDriver(LD) != NULL){
        cout << endl << "======== TAMPILKAN DATA DRIVER PADA RESTAURANT TERTENTU ========" << endl;
        D = firstDriver(LD);
        do {
            i = 0;
            if (firstCust(D) != NULL){
                C = firstCust(D);
                while (C != NULL){
                    if (nextRC(C) == R){
                        i++;
                    }
                    C = nextCust(C);
                }
            }
            cout << "Nama Driver     : " << infoDriver(D).nama << endl;
            cout << "ID Driver       : " << infoDriver(D).id << endl;
            cout << "Status Driver   : " << infoDriver(D).status << endl;
            cout << "Jumlah Customer : " << i << endl;
            D = nextDriver(D);
        } while (D != firstDriver(LD));
        cout << "=================================================" << endl << endl;
    } else {
        cout << endl << "========== LIST KOSONG ==========" << endl << endl;
    }
}
void showDriverFromAllRest(listDriver LD, listResto LR){
    adr_driver D;
    adr_cust C;
    adr_resto R;
    if (firstRest(LR) != NULL){
        cout << endl << "========== Data Restaurant dan Driver ==========" << endl;
        R = firstRest(LR);
        while (R != NULL){
            cout << endl << "Restoran   : " << infoRest(R).nama << endl;
            cout << "Harga      : " << infoRest(R).harga << endl;
            cout << "Stok       : " << infoRest(R).stok << endl;
            if (firstDriver(LD) != NULL){
                cout << "Total Driver di" << infoRest(R).nama << " adalah: " << countCustByRest(LD, LR, R) << endl << endl;
                D = firstDriver(LD);
                do {
                    if (firstDriver(LD) != NULL){
                        C = firstCust(D);
                        while (C != NULL){
                            if (nextRC(C) == R){
                                showOneDriver(LD, D);
                            }
                            C = nextCust(C);
                        }
                    }
                D = nextDriver(D);
                }while (D != firstDriver(LD));
            }
            R = nextRest(R);
            cout << "=====================";
            cout << endl;
        }
        cout << "=================================================" << endl << endl;
    } else {
        cout << endl << "========== LIST KOSONG ==========" << endl << endl;
    }
}
void showAllDriverCustRest(listDriver LD, listResto LR){
    adr_cust C;
    adr_driver D;
    adr_resto R;
    if (firstDriver(LD) != NULL){
        D = firstDriver(LD);
        do {
            cout << "-------------------------------" << endl;
            showOneDriver(LD, D);
            if (firstCust(D) != NULL) {
                C = firstCust(D);
                while (C != NULL){
                    showOneCustomer(LD, D, C, nextRC(C));
                    C = nextCust(C);
                }
            }
        D = nextDriver(D);
        } while (D != firstDriver(LD));
        showAllRestoran(LR);
    } else {
        cout << endl << "========== LIST KOSONG ==========" << endl << endl;
    }
}
void showCustByDriver(listDriver LD, listResto LR, adr_driver D, adr_cust C, string ID){
    D = findDriverByID(LD, ID);
    if (D != NULL) {
        if (firstCust(D) != NULL) {
            C = firstCust(D);
            while (C != NULL) {
                adr_resto foundResto = findRestaurant(LR, infoCust(C).orderTo);
                    cout << "========" << endl;
                    showOneCustomer(LD, D, C, foundResto);
                    C = nextCust(C);
            }
        } else {
            cout << endl << "========== DRIVER TIDAK MEMILIKI CUSTOMER ==========" << endl << endl;
        }
    } else {
        cout << "Data Driver Tidak Ditemukan" << endl;
    }
}
void updateStatusMasakan(listDriver &LD, listResto &LR, adr_resto R){
    adr_driver D;
    adr_cust C, temp;
    if (firstDriver(LD) != NULL){
        D = firstDriver(LD);
        do {
            if (firstCust(D) != NULL){
                C = firstCust(D);
                while (C != NULL){
                    if (nextRC(C) == R){
                        cout << "Pesanan: " << endl;
                        infoCust(C).status = "Done";
                        showOneCustomer(LD, D, C, R);
                        temp = C;
                        C = nextCust(C);
                        deleteCust(LD, D, temp);
                        cout << "========== Telah Selesai ==========" << endl;
                    } else {
                        C = nextCust(C);
                    }
                }
            }
            D = nextDriver(D);
        } while (D != firstDriver(LD));
    }
}
void GantiDriver(listDriver &LD, listResto &LR, adr_driver &DSebelum, adr_driver &DSetelah, adr_cust &C) {
    if (infoDriver(DSetelah).countCust >= 3 || infoDriver(DSetelah).status != "Available") {
        do {
            if (infoDriver(DSetelah).countCust < 3 && infoDriver(DSetelah).status == "Available") {
                break;
            }
            DSetelah = nextDriver(DSetelah);
        } while (infoDriver(DSetelah).countCust > 3 && nextDriver(DSetelah) != DSetelah || infoDriver(DSetelah).status == "Non-Available");
    }
    cout << "Driver Awal: " << infoDriver(DSebelum).nama << endl;
    cout << "Nama Customer: " << infoCust(C).nama << endl;
    if (infoDriver(DSetelah).countCust < 3) {
        deleteCust(LD, DSebelum, C);
        cout << "Driver Akhir: " << infoDriver(DSetelah).nama << endl;
        if (firstCust(DSetelah) != NULL) {
            nextCust(lastCust(DSetelah)) = C;
            prevCust(C) = lastCust(DSetelah);
            lastCust(DSetelah) = C;
            infoDriver(DSetelah).countCust++;
        } else {
            firstCust(DSetelah) = C;
            lastCust(DSetelah) = C;
            infoDriver(DSetelah).countCust++;
        }
        cout << "Nama Customer: " << infoCust(C).nama << endl;
    } else {
        cout << "Tidak dapat ganti driver" << endl;
    }
}
void selectedMenu() {
    cout << "========== MAIN MENU ==========" << endl;
    cout << "1. RESTAURANT" << endl;
    cout << "2. DRIVER" << endl;
    cout << "3. CUSTOMER" << endl;
    cout << "4. SHOW ALL DATA" << endl;
    cout << "0. EXIT" << endl;
    cout << endl << "Masukkan Pilihan Menu: ";
}
void KelolaDriver(listDriver &LD, adr_driver &D) {
    int menu; infotypeD dataD;
    listResto LR; adr_resto R; adr_cust C;
    string IDfind;
    do {
        cout << "========== MENU DRIVER ==========" << endl;
        cout << "1. Insert Driver" << endl;
        cout << "2. Delete Driver" << endl;
        cout << "3. Find & Show Driver Tertentu" << endl;
        cout << "4. Show All Driver" << endl;
        cout << "5. Count Customer dari Driver Tertentu" << endl;
        cout << "6. Count Customer dari Setiap Driver" << endl;
        cout << "7. Count Restaurant dari Driver Tertentu" << endl;
        cout << "8. Count Restaurant dari Setiap Driver" << endl;
        cout << "9. Ganti Status Driver" << endl;
        cout << "0. Kembali" << endl;
        cout << endl << "Masukkan Pilihan Menu: ";
        cin >> menu;
        cout << "=================================================" << endl << endl;
        switch(menu) {
        case 1: //Insert element parent (Insert Data Driver)
            cout << "=================================================" << endl;
            int n;
            cout << "Jumlah insert data driver: "; cin >> n;
            for (int i = 0; i < n; i++) {
                cout << "Nama   : "; cin >> dataD.nama;
                cout << "ID     : "; cin >> dataD.id;
                cout << "Status : "; cin >> dataD.status;
                D = createElemenDriver(dataD);
                insertLastDriver(LD, D);
                cout << endl;
            }
            cout << "=================================================" << endl << endl;
            break;
        case 2: //Delete element parent (Delete Data Driver)
            cout << "=================================================" << endl;
            cout << "Input ID driver yang akan dihapus: "; cin >> IDfind;
            deleteDriver(LD, D, IDfind);
            cout << "=================================================" << endl;
            break;
        case 3: //Find element Parent (Find Data Driver)
            cout << "=================================================" << endl;
            cout << "Input ID driver yang akan dicari: "; cin >> IDfind;
            D = findDriverByID(LD, IDfind);
            if (D != NULL) {
                showOneDriver(LD, D);
            } else {
                cout << "Data Driver Tidak Ditemukan" << endl;
            }
            cout << "=================================================" << endl << endl;
            break;
        case 4: //Show all data di List Parent (Show All Data Driver)
            showAllDriver(LD);
            break;
        case 5:
            cout << "=================================================" << endl;
            cout << "ID Driver: "; cin >> IDfind;
            D = findDriverByID(LD, IDfind);
            if (D != NULL) {
                cout << "Jumlah Customer pada Driver " << countCustByDriver(D, C) << endl;
            } else {
                cout << "Data Driver Tidak Ditemukan" << endl;
            }
            cout << "=================================================" << endl << endl;
            break;
        case 6:
            cout << "=================================================" << endl;
            countAllCustInDriver(LD, D, C);
            cout << "=================================================" << endl << endl;
            break;
        case 7:
            cout << "=================================================" << endl;
            cout << "ID Driver: "; cin >> IDfind;
            D = findDriverByID(LD, IDfind);
            if (D != NULL) {
                cout << "Jumlah Restaurant dari Driver " << countRestInDriver(D) << endl;
            } else {
                cout << "Data Driver Tidak Ditemukan" << endl;
            }
            cout << "=================================================" << endl << endl;
            break;
        case 8: //Count relation dari setiap element parent (Count Restoran dari Setiap Data Driver)
            cout << "=============== Jumlah Restaurant dari Setiap Driver ===============" << endl;
            countAllRestInDriver(LD, D);
            cout << "=================================================" << endl << endl;
            break;
        case 9:
            cout << "=================================================" << endl;
            cout << "ID Driver: "; cin >> IDfind;
            D = findDriverByID(LD, IDfind);
            if (D != NULL) {
                cout << "Status Driver: " << infoDriver(D).status << endl;
                if (infoDriver(D).status == "Non-Available") {
                    infoDriver(D).status = "Available";
                    cout << "Status Driver: " << infoDriver(D).status << " (status berhasil diganti)" << endl;
                } else {
                    cout << "Status Driver Sudah Available" << endl;
                }
            } else {
                cout << "Driver Tidak Ditemukan" << endl;
            }
            cout << "=================================================" << endl << endl;
            break;
        case 0:
            return;
        }
    } while(menu != 0);
}
void KelolaCustomer(listDriver &LD, adr_driver &D, adr_cust &C, listResto LR, adr_resto R) {
    int menu; infotypeC dataC;
    adr_driver DSebelum, DSetelah;
    string number; string IDfind;
    do {
        cout << "========== MENU CUSTOMER ==========" << endl;
        cout << "1. Insert Customer" << endl;
        cout << "2. Find & Show Customer Tertentu" << endl;
        cout << "3. Show Semua Data Driver dan Customer" << endl;
        cout << "4. Show Data Customer dari Driver Tertentu" << endl;
        cout << "5. Ganti Driver" << endl;
        cout << "0. Kembali" << endl;
        cout << endl << "Masukkan Pilihan Menu: ";
        cin >> menu;
        cout << "=================================================" << endl << endl;
        switch(menu) {
        case 1: //Insert element relation (Insert Data Customer)
            cout << "=================================================" << endl;
            int n;
            cout << "Jumlah insert data customer: "; cin >> n;
            for (int i = 0; i < n; i++) {
                showAllRestoran(LR);
                cout << "Masukkan nama Resto: ";
                cin >> dataC.orderTo;
                cout << "Nama Customer      : "; cin >> dataC.nama;
                cout << "No HP Customer     : "; cin >> dataC.noHP;
                cout << "Status Customer    : "; dataC.status = "Process"; cout << dataC.status << endl;
                cout << "Jumlah Order       : "; cin >> dataC.jumlahOrder;
                C = createElemenCust(dataC, R);
                insertLastCust(LD, D, C, LR, dataC.orderTo);
            }
            cout << "=================================================" << endl << endl;
            break;
        case 2: //Find element relation (Find Data Customer)
            cout << "=================================================" << endl;
            cout << "Input no HP customer yang akan dicari: "; cin >> number;
            findCustByNoHP(LD, D, number, C);
            if (C != NULL) {
                showOneCustomer(LD, D, C, nextRC(C));
            } else {
                cout << "Data Customer yang Dicari Tidak Ada" << endl;
            }
            cout << "=================================================" << endl << endl;
            break;
        case 3:
            showAllDriverCust(LD, LR);
            break;
        case 4: //Show data child dari parent tertentu (Show All Data Customer dari Driver Tertentu)
            cout << "=================================================" << endl;
            cout << "Input ID driver: "; cin >> IDfind;
            showCustByDriver(LD, LR, D, C, IDfind);
            cout << "=================================================" << endl << endl;
            break;
        case 5: //Edit relasi (Mengganti Driver dari Customer Tertentu)
            cout << "=================================================" << endl;
            cout << "Input no HP customer yang akan dicari: "; cin >> number;
            findCustByNoHP(LD, DSebelum, number, C);
            if (C != NULL) {
                DSetelah = nextDriver(DSebelum);
                GantiDriver(LD, LR, DSebelum, DSetelah, C);
            } else {
                cout << "Customer Tidak Ditemukan" << endl;
            }
            cout << "=================================================" << endl << endl;
            break;
        case 0:
            return;
        }
    } while(menu != 0);
}
void Restaurant(listResto &LR, adr_resto R, listDriver LD) {
    int menu; infotypeR dataR;
    string nama;
    do {
        cout << "========== MENU RESTAURANT ==========" << endl;
        cout << "1. Insert Restaurant" << endl;
        cout << "2. Delete Restaurant" << endl;
        cout << "3. Update Status Pesanan" << endl;
        cout << "4. Show All Restaurant" << endl;
        cout << "5. Show Driver pada restaurant Tertentu" << endl;
        cout << "6. Show Data restaurant dan Driver" << endl;
        cout << "0. Kembali" << endl;
        cout << endl << "Masukkan Pilihan Menu: ";
        cin >> menu;
        cout << "=======================================" << endl << endl;
        switch(menu) {
        case 1: //Insert element child (Insert Data Restoran)
            int n;
            cout << "=================================================" << endl;
            cout << "Jumlah insert data restaurant: "; cin >> n;
            for (int i = 0; i < n; i++) {
                cout << "Nama Restoran  : "; cin >> dataR.nama;
                cout << "Stok           : "; cin >> dataR.stok;
                cout << "Harga          : "; cin >> dataR.harga;
                R = createElemenRestoran(dataR);
                insertLastRestoran(LR, R);
                cout << endl;
            }
            cout << "=================================================" << endl;
            break;
        case 2: //Delete element child (Delete Data Restoran)
            cout << "=================================================" << endl;
            deleteRestoran(LR, R);
            if (R == NULL) {
                cout << "DATA RESTORAN TIDAK BISA DIHAPUS, STOK != 0" << endl;
            } else {
                cout << "Data Restaurant " << infoRest(R).nama << " Telah Dihapus" << endl;
            }
            cout << "=================================================" << endl;
            break;
        case 3:
            cout << "=============== UPDATE DATA RESTAURANT ===============" << endl;
            cout << "Input nama restaurant: "; cin >> nama;
            R = findRestaurant(LR, nama);
            if (R != NULL) {
                updateStatusMasakan(LD, LR, R);
            } else {
                cout << "Restaurant Tidak Ditemukan" << endl;
            }
            cout << "=================================================" << endl;
            break;
        case 4:
            showAllRestoran(LR);
            break;
        case 5:  //Show data parent yang berelasi dengan child tertentu (Show Data Driver yang Mendatangi Restoran Tertentu)
            cout << "=================================================" << endl;
            cout << "Input nama restaurant: "; cin >> nama;
            R = findRestaurant(LR, nama);
            if (R != NULL) {
                showDriverToRest(LD, LR, R);
            } else {
                cout << "Restaurant Tidak Ditemukan" << endl;
            }
            break;
        case 6: // Show setiap data parent beserta data child yang berelasi dengannya (Show All Data Driver dari Setiap Restoran)
            showDriverFromAllRest(LD, LR);
            break;
        case 0:
            return;
        }
    } while(menu != 0);
}
