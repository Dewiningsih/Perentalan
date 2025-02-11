#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <limits>

using namespace std;

const int MAX_CUSTOMERS = 100;
const int MAX_MOTORS = 100;

struct Date {
    int day, month, year;
};

struct Customer {
    string nama, alamat, no_telp, nik;
};

struct Motor {
    string merk, platNomor;
    double hargaSewa;
    bool tersedia = true;
};

struct SewaMotor {
    Customer penyewa;
    Motor motor;
    Date tgl_sewa, tgl_kembali;
    int lamaSewa;
};

vector<Customer> customers;
vector<Motor> motors;
vector<SewaMotor> sewaHistory;
stack<Motor> motorStack;
queue<Motor> motorQueue;

int tampilkanMenu() {
    int pilihan;
    cout << "=== MENU ===" << endl;
    cout << "1. Input Data Customer" << endl;
    cout << "2. Input Data Motor" << endl;
    cout << "3. Tampilkan List Motor" << endl;
    cout << "4. Sewa Motor" << endl;
    cout << "5. Tampilkan Data Sewa" << endl;
    cout << "6. Tampilkan Stack Motor" << endl;
    cout << "7. Tampilkan Queue Motor" << endl;
    cout << "8. Keluar" << endl;
    cout << "Pilih menu (1-8): ";
    while (!(cin >> pilihan) || pilihan < 1 || pilihan > 8) {
        cin.clear(); // Menghapus flag error
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Mengabaikan input yang salah
        cout << "Pilihan tidak valid. Silakan pilih lagi (1-8): ";
    }
    return pilihan;
}

void inputCustomer() {
    Customer newCustomer;
    cout << "Masukkan Nama: "; cin.ignore(); getline(cin, newCustomer.nama);
    cout << "Masukkan Alamat: "; getline(cin, newCustomer.alamat);
    cout << "Masukkan No. Telepon: "; cin >> newCustomer.no_telp;
    cout << "Masukkan NIK: "; cin >> newCustomer.nik;
    customers.push_back(newCustomer);
    cout << "Data customer berhasil ditambahkan!\n";
}

void inputMotor() {
    Motor newMotor;
    cout << "Masukkan Merk Motor: "; cin.ignore(); getline(cin, newMotor.merk);
    cout << "Masukkan Plat Nomor: "; cin >> newMotor.platNomor;
    cout << "Masukkan Harga Sewa: ";
    while (!(cin >> newMotor.hargaSewa) || newMotor.hargaSewa < 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Harga sewa tidak valid. Masukkan kembali: ";
    }
    newMotor.tersedia = true;
    motors.push_back(newMotor);
    motorStack.push(newMotor);
    motorQueue.push(newMotor);
    cout << "Data motor berhasil ditambahkan!\n";
}

void tampilkanListMotor() {
    cout << "----------------------------------------------------------------" << endl;
    cout << "||                         RENTAL MOTOR                       ||" << endl;
    cout << "||                        Struktur Data                       ||" << endl;
    cout << "----------------------------------------------------------------" << endl;
    cout << "\n=== LIST MOTOR ===" << endl;
    cout << "Merk\t\tPlat Nomor\t\tHarga Sewa (per hari)\t\tStatus" << endl;
    for (const auto& motor : motors) {
        cout << motor.merk << "\t\t" << motor.platNomor << "\t\t" << motor.hargaSewa << "\t\t"
             << (motor.tersedia ? "Tersedia" : "Sudah Disewa") << endl;
    }
    cout << "\nTekan Enter untuk melanjutkan...";
    cin.ignore();
    cin.get();
}

void sewaMotor() {
    if (customers.empty() || motors.empty()) {
        cout << "Tidak ada customer atau motor tersedia." << endl;
        return;
    }
    
    tampilkanListMotor();
    string plat;
    cout << "Masukkan plat nomor motor yang ingin disewa: ";
    cin >> plat;
    
    for (auto& motor : motors) {
        if (motor.platNomor == plat && motor.tersedia) {
            motor.tersedia = false;
            
            SewaMotor newSewa;
            newSewa.motor = motor;
            newSewa.penyewa = customers.back();
            cout << "Masukkan lama sewa (hari): ";
            while (!(cin >> newSewa.lamaSewa) || newSewa.lamaSewa < 1) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Lama sewa tidak valid. Masukkan kembali: ";
            }
            cout << "Masukkan tanggal sewa (dd mm yyyy): ";
            while (!(cin >> newSewa.tgl_sewa.day >> newSewa.tgl_sewa.month >> newSewa.tgl_sewa.year)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Format tanggal tidak valid. Masukkan kembali (dd mm yyyy): ";
            }
            cout << "Masukkan tanggal kembali (dd mm yyyy): ";
            while (!(cin >> newSewa.tgl_kembali.day >> newSewa.tgl_kembali.month >> newSewa.tgl_kembali.year)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Format tanggal tidak valid. Masukkan kembali (dd mm yyyy): ";
            }
            
            sewaHistory.push_back(newSewa);
            cout << "Motor berhasil disewa!" << endl;
            return;
        }
    }
    cout << "Motor tidak tersedia atau tidak ditemukan." << endl;
}

void tampilkanDataSewa() {
    if (sewaHistory.empty()) {
        cout << "Belum ada transaksi sewa." << endl;
        return;
    }
    
    cout << "\n=== DATA SEWA MOTOR ===" << endl;
    for (const auto& sewa : sewaHistory) {
        cout << "Nama: " << sewa.penyewa.nama << " | NIK: " << sewa.penyewa.nik << endl;
        cout << "Motor: " << sewa.motor.merk << " | Plat: " << sewa.motor.platNomor << endl;
        cout << "Tanggal Sewa: " << sewa.tgl_sewa.day << "/" << sewa.tgl_sewa.month << "/" << sewa.tgl_sewa.year << endl;
        cout << "Tanggal Kembali: " << sewa.tgl_kembali.day << "/" << sewa.tgl_kembali.month << "/" << sewa.tgl_kembali.year << endl;
        cout << "Lama Sewa: " << sewa.lamaSewa << " hari\n" << endl;
    }
    cout << "Tekan Enter untuk melanjutkan...";
    cin.ignore();
    cin.get();
}

void tampilkanStackMotor() {
    cout << "=== STACK MOTOR (LIFO) ===" << endl;
    stack<Motor> tempStack = motorStack;
    while (!tempStack.empty()) {
        Motor current = tempStack.top();
        cout << "Merk: " << current.merk << ", Plat Nomor: " << current.platNomor << ", Harga Sewa: " << current.hargaSewa << endl;
        tempStack.pop();
    }
    cout << "Tekan Enter untuk melanjutkan...";
    cin.ignore();
    cin.get();
}

void tampilkanQueueMotor() {
    cout << "=== QUEUE MOTOR (FIFO) ===" << endl;
    queue<Motor> tempQueue = motorQueue;
    while (!tempQueue.empty()) {
        Motor current = tempQueue.front();
        cout << "Merk: " << current.merk << ", Plat Nomor: " << current.platNomor << ", Harga Sewa: " << current.hargaSewa << endl;
        tempQueue.pop();
    }
    cout << "Tekan Enter untuk melanjutkan...";
    cin.ignore();
    cin.get();
}

int main() {
    int pilihan;
    do {
        pilihan = tampilkanMenu();
        switch (pilihan) {
            case 1: inputCustomer(); break;
            case 2: inputMotor(); break;
            case 3: tampilkanListMotor(); break;
            case 4: sewaMotor(); break;
            case 5: tampilkanDataSewa(); break;
            case 6: tampilkanStackMotor(); break;
            case 7: tampilkanQueueMotor(); break;
            case 8: cout << "Terima kasih!" << endl; break;
            default: cout << "Pilihan tidak valid." << endl;
        }
    } while (pilihan != 8);
    return 0;
}
