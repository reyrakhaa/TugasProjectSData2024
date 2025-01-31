#include <iostream>
#include <queue>
#include <fstream>
#include <string>

using namespace std;

/*nama anggota :
1. Reynard Rakha Fatin Nugraha 2300018234
2. Septia Nenengsih 2300018239
3. Lanang Fajri Ramadhan 2300018264
*/


// Struktur data untuk menyimpan informasi pasien
struct Pasien {
    string nama;
    string nim;
    string tgl_lahir;
    string alamat;
    string agama;
    string kewarganegaraan;
    string ktp;
    string waktu_kedatangan;
    string kode_obat;
};

// Fungsi untuk memuat data pasien dari file (dengan atribut baru)
void muatDataPasien(queue<Pasien> &antrian) {
    ifstream file("pasien.txt");
    if (!file.is_open()) {
        cout << "File pasien.txt tidak ditemukan. Memulai dengan antrian kosong.\n";
        return;
    }

    Pasien pasien;
    while (file >> pasien.ktp >> pasien.nim >> pasien.tgl_lahir >> pasien.alamat >> pasien.agama 
                >> pasien.kewarganegaraan >> pasien.waktu_kedatangan >> pasien.kode_obat) {
        antrian.push(pasien);
    }
    file.close();
}

// Fungsi untuk menyimpan data pasien ke file (dengan atribut baru)
void simpanDataPasien(queue<Pasien> antrian) {
    ofstream file("pasien.txt");
    while (!antrian.empty()) {
        Pasien pasien = antrian.front();
        antrian.pop();
        file << pasien.ktp << " " << pasien.nim << " " << pasien.tgl_lahir << " " 
             << pasien.alamat << " " << pasien.agama << " " << pasien.kewarganegaraan << " " 
             << " " << pasien.waktu_kedatangan << " " << pasien.kode_obat << "\n";
    }
    file.close();
}

// Struktur data untuk menyimpan informasi obat di gudang
struct DataObat{
    string kode_obat;
    string nama_obat;
    int jumlah;
};

// Fungsi untuk memuat data obat dari file
void muatDataObat(DataObat gudang[], int &jumlah_obat) {
    ifstream file("obat.txt");
    if (!file.is_open()) {
        cout << "File obat.txt tidak ditemukan. Memulai dengan gudang kosong.\n";
        return;
    }

    jumlah_obat = 0;
    while (file >> gudang[jumlah_obat].kode_obat >> gudang[jumlah_obat].nama_obat >> gudang[jumlah_obat].jumlah) {
        jumlah_obat++;
    }
    file.close();
}

// Fungsi untuk menyimpan data obat ke file
void simpanDataObat(DataObat gudang[], int jumlah_obat) {
    ofstream file("obat.txt");
    for (int i = 0; i < jumlah_obat; i++) {
        file << gudang[i].kode_obat << "   " << gudang[i].nama_obat << "   " << gudang[i].jumlah << "\n";
    }
    file.close();
}

// Fungsi untuk memvalidasi admin
bool validasiAdmin(const string &ktp, const string &password) {
    ifstream file("admin.txt");
    if (!file.is_open()) {
        cout << "File admin.txt tidak ditemukan. Pastikan file tersedia.\n";
        return false;
    }

    string file_ktp, file_password;
    while (file >> file_ktp >> file_password) {
        if (file_ktp == ktp && file_password == password) {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

// Fungsi untuk sign in admin
bool adminSignIn() {
    string nama, nim, tgl_lahir, alamat, agama, kewarganegaraan, password;

    cout << "\n================== DATA ADMIN ==================\n";
    cout << "Masukkan Nama            : "; cin.ignore(); getline(cin, nama);
    cout << "Masukkan NIM/NIK         : "; cin >> nim; cin.ignore(); 
    cout << "Masukkan Tanggal Lahir   : "; getline(cin, tgl_lahir);
    cout << "Masukkan Alamat          : "; getline(cin, alamat);
    cout << "Masukkan Agama           : "; getline(cin, agama);
    cout << "Masukkan Kewarganegaraan : "; getline(cin, kewarganegaraan);
    cout << endl;
    cout << "Masukkan Password Admin  : "; cin >> password;

    if (validasiAdmin(nim, password)) {
        cout << "Sign in berhasil. Selamat datang, Admin " << nama << "!\n";
        return true;
    } else {
        cout << "Sign in gagal. NIM/NIK atau Password salah.\n";
        return false;
    }
    cout << "\n===============================================\n";
}


// Fungsi untuk menampilkan menu utama untuk admin
void tampilkanMenuAdmin() {
    cout << "\n============= MENU UTAMA ADMIN ================\n";
    cout << "1. Tambahkan Stok Obat ke Gudang\n";
    cout << "2. Daftar Obat di Gudang\n";
    cout << "3. Daftar Pembeli Obat\n";
    cout << "4. Serahkan Obat ke Pembeli\n";
    cout << "5. Keluar\n";
    cout << "\n===============================================\n";
    cout << "Pilih opsi: ";
}

// Fungsi untuk menampilkan menu utama untuk pengguna non-admin
void tampilkanMenuPengguna() {
    cout << "\n============ MENU UTAMA PENGGUNA ==============\n";
    cout << "1. Pesan Obat\n";
    cout << "2. Keluar\n";
    cout << "\n===============================================\n";
    cout << "Pilih opsi: ";
}

// Fungsi untuk mencetak daftar obat di gudang
void cetakDaftarObat(DataObat gudang[], int jumlah_obat) {
    cout << "\n============ DAFTAR OBAT DI GUDANG ==========\n";
    cout << "Kode Obat      Nama Obat          Jumlah";
    for (int i = 0; i < jumlah_obat; i++) {
        cout << gudang[i].kode_obat << "               " << gudang[i].nama_obat << "                   " << gudang[i].jumlah << endl;
    }
    cout << "\n=============================================\n";
}

// Fungsi untuk menyerahkan obat ke pasien berdasarkan FIFO
void serahkanObat(queue<Pasien> &antrian, DataObat gudang[], int jumlah_obat) {
    if (antrian.empty()) {
        cout << "Tidak ada pasien dalam antrian.\n";
        return;
    }

    Pasien pasien = antrian.front();
    antrian.pop();

    bool obat_found = false;
    for (int i = 0; i < jumlah_obat; i++) {
        if (gudang[i].kode_obat == pasien.kode_obat) {
            if (gudang[i].jumlah > 0) {
                cout << "\nPasien dengan Nama " << pasien.nama << "dan NIM/NIK " << pasien.nim << " menerima obat " << gudang[i].nama_obat << " (Kode: " << gudang[i].kode_obat << ")\n";
                gudang[i].jumlah--;
                obat_found = true;
                break;
            } else {
                cout << "\nStok obat " << pasien.kode_obat << " habis.\n";
                obat_found = true;
                break;
            }
        }
    }

    if (!obat_found) {
        cout << "\nObat dengan kode " << pasien.kode_obat << " tidak ditemukan di gudang.\n";
    }

    simpanDataPasien(antrian);
    simpanDataObat(gudang, jumlah_obat);
}


int main() {
    queue<Pasien> antrian;  // data antrian yang menyimpan objek-objek bertipe Pasien.
    DataObat gudang[100]; // Gudang obat dengan kapasitas maksimum 100 obat
    int jumlah_obat = 0;	// Jumlah obat saat ini di gudang

	// Fungsi untuk memuat data obat dan pasien dari penyimpanan eksternal
    muatDataObat(gudang, jumlah_obat);
    muatDataPasien(antrian);

	// Loop utama program
    while (true) {
        int opsi;
        bool isAdmin = false;
		
		// Menampilkan menu utama
        cout << "\n================= MENU UTAMA =================\n" << endl;
        cout << "1. Admin" << endl;
        cout << "2. Pelanggan" << endl;
        cout << "3. Keluar" << endl;
        cout << "\n==============================================\n" << endl;
        cout << "Pilihan: ";
        cin >> opsi;

        if (opsi == 1) {					// Opsi untuk Admin
            if (adminSignIn()) {			// Verifikasi login Admin
                isAdmin = true;
                while (isAdmin) {
                    tampilkanMenuAdmin();	// Menampilkan menu Admin
                    cin >> opsi;
                    switch (opsi) {
                        case 1: // Menambah obat baru ke gudang
                            if (jumlah_obat >= 100) {
                                cout << "Gudang penuh, tidak dapat menambah obat lagi.\n";
                                break;
                            }
                            cout << "Masukkan Kode Obat: ";
                            cin >> gudang[jumlah_obat].kode_obat;
                            cout << "Masukkan Nama Obat: ";
                            cin >> gudang[jumlah_obat].nama_obat;
                            cout << "Masukkan Jumlah: ";
                            cin >> gudang[jumlah_obat].jumlah;

                            jumlah_obat++;
                            simpanDataObat(gudang, jumlah_obat); // Menyimpan data obat ke penyimpanan
                            cout << "Obat berhasil ditambahkan ke gudang.\n";
                            break;
                        case 2:  // Menampilkan daftar obat di gudang
                            cout << "\n=============== DAFTAR OBAT ===============\n";
                        	cout << "|Kode Obat    |Nama Obat         |Jumlah\n";
                        	cout << "\n===========================================\n";
                        	for (int i = 0; i < jumlah_obat; i++) {
                            	cout << gudang[i].kode_obat << "           " 
                                	 << gudang[i].nama_obat << "           " 
                                 	 << gudang[i].jumlah << endl;
                        	}
                        	cout << "===========================================\n";
                            break;
                        case 3:  // Menampilkan daftar antrian pasien
                            if (antrian.empty()) {
                                cout << "Tidak ada pasien dalam antrian.\n";
                            } else {
                            	cout << "\n--------------- DAFTAR ANTRIAN PASIEN --------------\n";
                                queue<Pasien> temp_antrian = antrian;
                                while (!temp_antrian.empty()) {
                                    Pasien pasien = temp_antrian.front();
                                    cout << "Nama: " << pasien.ktp 
										 << ", NIM/NIK: " << pasien.nim
                                         << ", Waktu Kedatangan: " << pasien.waktu_kedatangan 
                                         << ", Kode Obat: " << pasien.kode_obat << endl;
                                    temp_antrian.pop();
                                }
                                cout << "\n----------------------------------------------------\n";
                            }
                            break;
                        case 4:  // Melayani pasien pertama dalam antrian
                            if (antrian.empty()) {
                                cout << "Tidak ada pasien dalam daftar pembeli.\n";
                            } else {
                                Pasien pasien = antrian.front(); // Ambil pasien pertama
                                antrian.pop();					 // Hapus dari antrian

                                bool obat_found = false;
                                for (int i = 0; i < jumlah_obat; i++) {
                                    if (gudang[i].kode_obat == pasien.kode_obat) {
                                        if (gudang[i].jumlah > 0) {
                                            cout << "\nPasien dengan KTP " << pasien.ktp 
                                                 << " menerima obat " << gudang[i].nama_obat 
                                                 << " (Kode: " << gudang[i].kode_obat << ")\n";
                                            gudang[i].jumlah--;  // Kurangi jumlah obat
                                            obat_found = true;
                                        } else {
                                            cout << "\nStok obat " << gudang[i].nama_obat << " habis.\n";
                                            obat_found = true;
                                        }
                                        break;
                                    }
                                }

                                if (!obat_found) {
                                    cout << "\nObat dengan kode " << pasien.kode_obat 
                                         << " tidak ditemukan di gudang.\n";
                                }

                                simpanDataPasien(antrian);	// Simpan data pasien setelah perubahan
                                simpanDataObat(gudang, jumlah_obat); // Simpan data obat setelah perubahan
                            }
                            break;
                        case 5: // Kembali ke menu utama
                            cout << "Kembali ke menu utama.\n";
                            isAdmin = false;
                            break;
                        default:
                            cout << "Opsi tidak valid. Silakan coba lagi.\n";
                    }
                }
            }
        } else if (opsi == 2) {  // Opsi untuk Pengguna Non-Admin
            bool isUser = true;  // Mengontrol menu pengguna non-admin
            while (isUser) {
                tampilkanMenuPengguna();  // Menampilkan menu pengguna non-admin
                cin >> opsi;
                switch (opsi) {
                    case 1: {
                        if (jumlah_obat == 0) {
                            cout << "Maaf, saat ini tidak ada obat yang tersedia di gudang.\n";
                            break;
                        }

                        // Tampilkan daftar obat yang tersedia di gudang
                        cout << "\n========== DAFTAR OBAT TERSEDIA ===========\n";
                        cout << "|Kode Obat    |Nama Obat         |Jumlah\n";
                        cout << "===========================================\n";
                        for (int i = 0; i < jumlah_obat; i++) {
                            cout << gudang[i].kode_obat << "           " 
                                 << gudang[i].nama_obat << "           " 
                                 << gudang[i].jumlah << endl;
                        }
                        cout << "===========================================\n";
                        cout << endl;
                        cout << endl;

                        // Memasukkan data pengguna setelah menampilkan daftar obat
                        Pasien pasien;
                        cout << "---------------- DATA DIRI ----------------";
                        cout << "\nMasukkan Nama Pasien: ";
                        cin.ignore(); getline(cin, pasien.ktp); 
                        cout << "Masukkan NIM Pasien: ";
                        cin >> pasien.nim;
                        cin.ignore(); 
                        cout << "Masukkan Tanggal Lahir Pasien: ";
                        getline(cin, pasien.tgl_lahir);
                        cout << "Masukkan Alamat Pasien: ";
                        getline(cin, pasien.alamat);
                        cout << "Masukkan Agama Pasien: ";
                        getline(cin, pasien.agama);
                        cout << "Masukkan Kewarganegaraan Pasien: ";
                        getline(cin, pasien.kewarganegaraan);
                        cout << "--------------------------------------------";
                        cout << endl;
                        cout << "Masukkan Waktu Kedatangan Pasien: ";
                        cin >> pasien.waktu_kedatangan;
                        cout << "Masukkan Kode Obat yang Diperlukan: ";
                        cin >> pasien.kode_obat;

                        antrian.push(pasien);		// Tambahkan pasien ke antrian
                        simpanDataPasien(antrian);	// Simpan data pasien ke penyimpanan
                        cout << "Pesanan obat berhasil ditambahkan.\n";
                        break;
                    }
                    case 2:
                        cout << "Kembali ke menu utama.\n";
                        isUser = false; // Keluar dari loop dan kembali ke menu utama
                        break;
                    default:
                        cout << "Opsi tidak valid. Sil";
				}
			}
		} else if (opsi == 3) {
		    cout << "Keluar dari program.\n";
		    break;
		} else {
		    cout << "Pilihan tidak valid. Silakan coba lagi.\n";
		}
	}
}
