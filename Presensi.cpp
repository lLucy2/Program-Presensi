#include <iostream>
#include <algorithm>
#include <string>
#include <chrono>
#include <ctime>

using namespace std;

#define MAX_SISWA 100

struct Presensi {
    string nim, nama, kelas, tanggal;
    Presensi* next;
};

Presensi* head = nullptr;

Presensi siswa[MAX_SISWA];
int index = 0;

string getCurrentDateTime() {
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
  
void tambahPresensi() {
    cin.ignore();
    if (index < MAX_SISWA) {
        Presensi* newPresensi = new Presensi;
        cout << "NIM: "; getline(cin, newPresensi->nim);
        cout << "Nama: "; getline(cin, newPresensi->nama);
        cout << "Kelas: "; getline(cin, newPresensi->kelas);
        newPresensi->tanggal = getCurrentDateTime();
        newPresensi->next = head;
        head = newPresensi;

        index++;

        cout << "Presensi berhasil ditambahkan.\n";
    } else {
        cout << "Kuota presensi sudah penuh.\n";
    }
}

void cetakPresensi() {
    cout << "\n=====================\n";
    cout << "   DAFTAR PRESENSI\n";
    cout << "=====================\n\n";

    cout << "||     NIM      ||           NAMA           ||      Kelas     ||         Tanggal         ||\n\n";

    Presensi* current = head;

    while (current != nullptr) {
        cout << "   " << current->nim << "        " << current->nama << "            " << current->kelas << "           " << current->tanggal;
        cout << "\n------------------------------------------------------------------------------------------\n";

        current = current->next;
    }
}


void cariMahasiswa() {
    string cariNIM;
    cout << "Masukkan NIM yang ingin dicari: "; cin >> cariNIM;

    for (int i = 0; i < index; ++i) {
        if (siswa[i].nim == cariNIM) {
            cout << "/nMahasiswa ditemukan:\n";
            cout << "NIM: " << siswa[i].nim << "\n";
            cout << "Nama: " << siswa[i].nama << "\n";
            cout << "Kelas: " << siswa[i].kelas << "\n";
            cout << "Tanggal Presensi: " << siswa[i].tanggal;
            return;
        }
    }

    cout << "Mahasiswa dengan NIM " << cariNIM << " tidak ditemukan.\n";
}

void sortingPresensiNIM() {

    for (int i = 0; i < index - 1; ++i) {
        for (int j = 0; j < index - i - 1; ++j) {
            if (siswa[j].nim > siswa[j + 1].nim) {
                swap(siswa[j], siswa[j + 1]);
            }
        }
    }

    cout << "Presensi berhasil diurutkan berdasarkan NIM.\n";

    cetakPresensi();
}

void sortingPresensiWaktu(){

        for (int i = 0; i < index - 1; ++i) {
        for (int j = 0; j < index - i - 1; j++) {
            if (siswa[j].tanggal > siswa[j + 1].tanggal) {
                swap(siswa[j], siswa[j + 1]);
            }
        }
    }

    cout << "Presensi berhasil diurutkan berdasarkan Tanggal dan Waktu.\n";

    cetakPresensi();

}

void hapusMahasiswaPertama() {
    if (head != nullptr) {
        Presensi* temp = head;
        head = head->next;
        delete temp;
        index--;

        cout << "Mahasiswa pertama berhasil dihapus.\n";
    } else {
        cout << "Tidak ada mahasiswa yang dapat dihapus.\n";
    }
}

void hapusMahasiswaTerakhir() {
    if (head != nullptr) {
        if (head->next == nullptr) {
            delete head;
            head = nullptr;
        } else {
            Presensi* current = head;
            while (current->next->next != nullptr) {
                current = current->next;
            }
            delete current->next;
            current->next = nullptr;
        }
        index--;

        cout << "Mahasiswa terakhir berhasil dihapus.\n";
    } else {
        cout << "Tidak ada mahasiswa yang dapat dihapus.\n";
    }
}

void hapusMahasiswaByNIM(string nim) {
    Presensi* current = head;
    Presensi* prev = nullptr;

    while (current != nullptr && current->nim != nim) {
        prev = current;
        current = current->next;
    }

    if (current != nullptr) {
        if (prev == nullptr) {
            head = current->next;
        } else {
            prev->next = current->next;
        }

        delete current;
        index--;
        cout << "Mahasiswa dengan NIM " << nim << " berhasil dihapus.\n";
    } else {
        cout << "Mahasiswa dengan NIM " << nim << " tidak ditemukan.\n";
    }
}

int main() {
    while (true) {
        system("cls");

        cout << "=====================\n";
        cout << "   PRESENSI MAHASISWA\n";
        cout << "=====================\n\n";

        cout << "1. Input Presensi\n";
        cout << "2. Daftar Presensi\n";
        cout << "3. Cari Mahasiswa\n";
        cout << "4. Sorting Ascending\n";
        cout << "5. Sorting Tanggal & Waktu Ascending\n";
        cout << "6. Hapus Mahasiswa Pertama\n";
        cout << "7. Hapus Mahasiswa Terakhir\n";
        cout << "8. Hapus Mahasiswa Dengan NIM\n";
        cout << "9. Keluar\n";

        cout << "\nSilahkan Pilih Menu : ";
        int menu;
        cin >> menu;

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
                {
                string nimToDelete;
                cout << "Masukkan NIM yang ingin dihapus: ";
                cin >> nimToDelete;
                hapusMahasiswaByNIM(nimToDelete);
                }
                break;

            case 9:
                cout << "\nTerima kasih!\n\n";
                return 0;

            default:
                cout << "\nPilihan Tidak Valid, Silahkan Pilih Menu 1 - 7!\n";
                break;
        }

        cout << "\nTekan Enter untuk kembali ke menu utama...";
        cin.ignore();
        cin.get();
    }

    return 0;
}
