#include <iostream>
#include <string>
#include <algorithm>
#include <chrono>
#include <ctime>

using namespace std;

#define MAX_SISWA 100

struct Presensi {
    string nim, nama, kelas, tanggal;
};

Presensi* mahasiswa[MAX_SISWA];
int head = 0;

// Mengambil Function getCurrentDateTime dari StackOverflow
string getCurrentDateTime() { //
    // Get the current time point
    auto currentTime = chrono::system_clock::now();

    // Convert the time point to a time_t object
    time_t currentTime_t = chrono::system_clock::to_time_t(currentTime);

    // Convert the time_t object to a tm structure
    struct tm *timeInfo = localtime(&currentTime_t);

    // Format the date and time as a string
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeInfo);

    return buffer;
}

bool isFull() {
    if (head >= MAX_SISWA){
        return true;
    } else {
        return false;
    }
}

bool isEmpty() {
    if (head == 0){
        return true;
    } else {
        return false;
    }
}

void push_enqueue(Presensi& tambahPresensi) {
    if (!isFull()) {
        mahasiswa[head++] = new Presensi(tambahPresensi);
        cout << "\nPresensi berhasil ditambahkan.\n";
    } else {
        cout << "\nKuota presensi sudah penuh.\n";
    }
}

void tambahPresensi() {
    cin.ignore();
    if (!isFull()) {
        Presensi tambahPresensi;
        cout << "\nNIM    : "; getline(cin, tambahPresensi.nim);
        cout << "NAMA   : "; getline(cin, tambahPresensi.nama);
        cout << "KELAS  : "; getline(cin, tambahPresensi.kelas);
        tambahPresensi.tanggal = getCurrentDateTime();

        push_enqueue(tambahPresensi);
    }
}

void cetakPresensi() {
    cout << "\n=====================\n";
    cout << "   DAFTAR PRESENSI\n";
    cout << "=====================\n\n";
    cout << "||     NIM      ||           NAMA           ||      Kelas     ||         Tanggal & Waktu         ||\n\n";
    for (int i = 0; i < head; i++) {
        cout << "    " << mahasiswa[i]->nim << "        " << mahasiswa[i]->nama << "          " << mahasiswa[i]->kelas << "               " << mahasiswa[i]->tanggal;
        cout << "\n---------------------------------------------------------------------------------------------------\n";
    }
}

void cariMahasiswa() {
    string cariNIM;
    bool ketemu = false;
    
    cout << "\nMasukkan NIM yang ingin dicari: "; cin >> cariNIM;

    for (int i = 0; i < head; i++) {
        if (cariNIM == mahasiswa[i]->nim) {
            cout << "\nMahasiswa ditemukan :\n";
            cout << "\nNIM    : " << mahasiswa[i]->nim;
            cout << "\nNama   : " << mahasiswa[i]->nama;
            cout << "\nKelas  : " << mahasiswa[i]->kelas;
            cout << "\nTanggal & Waktu Presensi : " << mahasiswa[i]->tanggal << "\n";
            ketemu = true;
            break;
        }
    }
    if (!ketemu) {
        cout << "\nMahasiswa dengan NIM " << cariNIM << " tidak ditemukan.\n";
    }
}

void sortingPresensiNIM() {
    for (int i = 0; i < head - 1; i++) {
        for (int j = 0; j < head - i - 1; j++) {
            if (mahasiswa[j]->nim > mahasiswa[j + 1]->nim) {
                swap(mahasiswa[j], mahasiswa[j + 1]);
            }
        }
    }

    cout << "\nPresensi berhasil diurutkan berdasarkan NIM.\n";
    cetakPresensi();
}

void sortingPresensiWaktu() {
    for (int i = 0; i < head - 1; i++) {
        for (int j = 0; j < head - i - 1; j++) {
            if (mahasiswa[j]->tanggal > mahasiswa[j + 1]->tanggal) {
                swap(mahasiswa[j], mahasiswa[j + 1]);
            }
        }
    }

    cout << "\nPresensi berhasil diurutkan berdasarkan Tanggal dan Waktu.\n";
    cetakPresensi();
}

void hapusMahasiswaPertama() { // Dequeue
    if (!isEmpty()) {
        for (int i = 0; i < head - 1; i++) {
            mahasiswa[i] = mahasiswa[i + 1];
        }
        head--;
        
        cout << "\nMahasiswa pertama berhasil dihapus.\n";
    } else {
        cout << "\nTidak ada mahasiswa yang dapat dihapus.\n";
    }
}

void hapusMahasiswaTerakhir() { // POP
    if (!isEmpty()) {
        head--;

        cout << "\nMahasiswa terakhir berhasil dihapus.\n";
    } else {
        cout << "\nTidak ada mahasiswa yang dapat dihapus.\n";
    }
}


void hapusMahasiswaNIM() {
    string hapusNIM;
    if (!isEmpty()) {
        cout << "\nMasukkan NIM mahasiswa yang ingin dihapus: "; cin >> hapusNIM;

        bool ketemu = false;
        for (int i = 0; i < head; i++) {
            if (hapusNIM == mahasiswa[i]->nim) {

                delete mahasiswa[i];
                
                for (int j = i; j < head - 1; j++) {
                    mahasiswa[j] = mahasiswa[j + 1];
                }
                head--;

                cout << "\nMahasiswa dengan NIM " << hapusNIM << " berhasil dihapus.\n";
                ketemu = true;
                break;
            }
        }

        if (!ketemu) {
            cout << "\nMahasiswa dengan NIM " << hapusNIM << " tidak ditemukan.\n";
        }
    } else {
        cout << "\nTidak ada mahasiswa yang dapat dihapus.\n";
    }
}



int main() {

    while (true) {
        system("cls");

        cout << "======================\n";
        cout << "  PRESENSI MAHASISWA\n";
        cout << "======================\n\n";

        cout << "1. Input Presensi\n";
        cout << "2. Daftar Presensi\n";
        cout << "3. Cari Mahasiswa\n";
        cout << "4. Sorting NIM\n";
        cout << "5. Sorting Tanggal & Waktu\n";
        cout << "6. Hapus Mahasiswa Pertama (DeQueue)\n";
        cout << "7. Hapus Mahasiswa Terakhir (POP)\n";
        cout << "8. Hapus Mahasiswa Dengan NIM\n";
        cout << "9. Keluar\n";

        cout << "\nSilahkan Pilih Menu : ";
        int menu; cin >> menu;

        switch (menu) {
            case 1:
                tambahPresensi();
                break;

            case 2:
                cetakPresensi();
                break;

            case 3:
                cariMahasiswa();
                break;

            case 4:
                sortingPresensiNIM();
                break;

            case 5:
                sortingPresensiWaktu();
                break;

            case 6:
                hapusMahasiswaPertama();
                break;

            case 7:
                hapusMahasiswaTerakhir();
                break;

            case 8:
                hapusMahasiswaNIM();
                break;

            case 9:
                cout << "\nTerima kasih!\n\n";
                return 0;

            default:
                cout << "\nPilihan Tidak Valid, Silahkan Pilih Menu 1 - 9!\n";
                break;
        }

        cout << "\nTekan Enter untuk kembali ke menu utama...";
        cin.ignore();
        cin.get();
    }

    return 0;
}