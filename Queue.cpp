#include <iostream>
#include <iomanip>
#include <string>
#define MAX 5

using namespace std;

struct DataPajak
{
	string plat[MAX];
	int nominal[MAX] = { 0 };
	string keterangan[MAX];

	int awal = -1;
} data_pajak;
struct AntreanPembayar
{
	struct DataPembayar { 
		string nama, nik, plat; 
	} data_pembayar[MAX];

	int awal = 0, akhir = -1;
} antrean;

// Function List
void showDataAntrean()
{
	int i = 0, j = 0;

	cout << "DATA PEMBAYAR\t\t\t\t\t\t\tDATA PAJAK" << endl;
	cout << "==================================================\t\t==================================================" << endl;
	cout << char(186)
		<< setw(5)  << left << " No"	<< char(186)
		<< setw(15) << left << " Nama"  << char(186)
		<< setw(10) << left << " NIK"	<< char(186)
		<< setw(15) << left << " Plat"  << char(186)
		<< "\t\t"
		<< char(186)
		<< setw(5)  << left << " No"		 << char(186)
		<< setw(15) << left << " Plat"		 << char(186)
		<< setw(10) << left << " Nominal"	 << char(186)
		<< setw(15) << left << " Keterangan" << char(186)
		<< endl;
	cout << "==================================================\t\t==================================================" << endl;

	int min = antrean.awal > 0 ? antrean.awal : 0;

	for (i = min, j = 0; j < MAX; i++, j++)
	{
		cout << char(186);
		if (i > MAX - 1 || antrean.data_pembayar[i].nama == "")
		{
			cout << setw(5)  << left  << ' ' << char(186);
			cout << setw(15) << left << ' ' << char(186);
			cout << setw(10) << left << ' ' << char(186);
			cout << setw(15) << left << ' ' << char(186);
		}
		else
		{
			cout << setw(5)  << left << ' ' + to_string(i + 1) + ". "		<< char(186);
			cout << setw(15) << left << ' ' + antrean.data_pembayar[i].nama << char(186);
			cout << setw(10) << left << ' ' + antrean.data_pembayar[i].nik	<< char(186);
			cout << setw(15) << left << ' ' + antrean.data_pembayar[i].plat << char(186);
		}

		cout << "\t\t";
		cout << char(186);

		if (data_pajak.plat[j] == "")
		{
			cout << setw(5)  << left << ' ' << char(186);
			cout << setw(15) << left << ' ' << char(186);
			cout << setw(10) << left << ' ' << char(186);
			cout << setw(15) << left << ' ' << char(186);
		}

		else
		{
			// Sorting
			int awal = 0;

			for (int i = 0; i < MAX; i++)
			{
				if (data_pajak.keterangan[i] == "LUNAS")
				{
					string plat_temp = data_pajak.plat[awal];
					int nom_temp = data_pajak.nominal[awal];
					string ket_temp = data_pajak.keterangan[awal];

					data_pajak.plat[awal] = data_pajak.plat[i];
					data_pajak.nominal[awal] = data_pajak.nominal[i];
					data_pajak.keterangan[awal] = data_pajak.keterangan[i];

					data_pajak.plat[i] = plat_temp;
					data_pajak.nominal[i] = nom_temp;
					data_pajak.keterangan[i] = ket_temp;

					awal++;
				}
			}

			cout << setw(5)  << left << ' ' + to_string(j + 1) + ". "			<< char(186);
			cout << setw(15) << left << ' ' + data_pajak.plat[j]				<< char(186);
			cout << setw(10) << left << ' ' + to_string(data_pajak.nominal[j])	<< char(186);
			cout << setw(15) << left << ' ' + data_pajak.keterangan[j]			<< char(186);
		}
		cout << endl;
	}
	cout << "==================================================\t\t==================================================" << endl;

	cout << endl;
}
bool antreanKosong()
{
	return antrean.akhir == -1;
}
bool antreanPenuh()
{
	return antrean.akhir == MAX - 1;
}
void prosesTambahAntrean(string *nama, string *plat, string*nik)
{
	antrean.data_pembayar[antrean.akhir].nama = *nama;
	antrean.data_pembayar[antrean.akhir].plat = *plat;
	antrean.data_pembayar[antrean.akhir].nik = *nik;
}
void tambahAntrean()
{
	system("cls");

	string nama, nik, plat;

	showDataAntrean();

	cout << "Tambah Data Antrean" << endl;
	cout << "============================" << endl;

	if (!antreanPenuh())
	{
		antrean.akhir++;

		cout << "Input Nama\t: ";
		cin >> nama;
		cout << "Input NIK\t: ";
		cin >> nik;
		cout << "Input Plat\t: ";
		cin.ignore();
		getline(cin, plat);

		// Mencocokkan dengan data pajak (berdasarkan plat)
		bool ketemu = false;
		for (int i = 0; i < MAX; i++)
		{
			if (plat == data_pajak.plat[i])
			{
				ketemu = true;
				break;
			}
		}

		if (ketemu == true)
		{
			prosesTambahAntrean(&nama, &plat, &nik);
			cout << "\nData berhasil ditambahkan" << endl;
		}
		else
		{
			cout << "\nPlat tidak ditemukan" << endl;
			antrean.akhir--;
		}
	}
	else
	{
		cout << "\nAntrean Pembayar Penuh" << endl;

	}
	cout << "============================" << endl;

}
void prosesHapusAntrean()
{
	for (int i = 0; i < MAX; i++)
	{
		if (antrean.data_pembayar[antrean.awal].plat == data_pajak.plat[i])
		{
			data_pajak.keterangan[i] = "LUNAS";
		}
	}

	antrean.awal++;
}
void hapusAntrean()
{
	system("cls");

	showDataAntrean();

	cout << "Hapus Data Antrean" << endl;
	cout << "============================" << endl;

	if (!antreanKosong() && antrean.data_pembayar[antrean.awal].nik != "")
	{
		prosesHapusAntrean();
		cout << "\nAntrean Pertama Keluar" << endl;
	}
	else
	{
		cout << "\nData Pembayar Kosong" << endl;
	}
	cout << "============================" << endl;
}
bool menuAntrean()
{
	system("cls");

	int pilihan = -1;

	while (pilihan != 0)
	{
		showDataAntrean();

		cout << "Menu Antrean Pembayar" << endl;
		cout << "============================" << endl;
		cout << "[1] Tambah Antrean" << endl;
		cout << "[2] Hapus Antrean" << endl;
		cout << "[3] Menu Pajak" << endl;
		cout << "[0] Exit" << endl;
		cout << "============================" << endl;
		cout << "\nPilih[1..3] : ";
		cin >> pilihan;
		cout << "============================" << endl;

		switch (pilihan)
		{
		case 1:
			tambahAntrean();
			break;
		case 2:
			hapusAntrean();
			break;
		case 3:
			system("cls");
			return 1;
		case 0:
			cout << "\nExit" << endl;
			cout << "============================" << endl;
			return 0;
		default:
			cout << "\nInput Salah" << endl;
			cout << "============================" << endl;
			break;
		}

		system("pause");
		system("cls");
	}
	return 1;
}

void showDataPajak()
{
	cout << "DATA PAJAK" << endl;
	cout << "==================================================" << endl;
	cout << char(186)
		<< setw(5)  << left << " No"			<< char(186)
		<< setw(15) << left << " Plat"			<< char(186)
		<< setw(10) << left << " Nominal"		<< char(186)
		<< setw(15) << left << " Keterangan"	<< char(186)
		<< endl;
	cout << "==================================================" << endl;

	for (int i = 0; i < MAX; i++)
	{
		cout << char(186);
		if (data_pajak.plat[i] == "")
		{
			cout << setw(5) << left << ' ' << char(186);
			cout << setw(15) << left << ' ' << char(186);
			cout << setw(10) << left << ' ' << char(186);
			cout << setw(15) << left << ' ' << char(186);
		}
		else
		{
			cout << setw(5) << left << ' ' + to_string(i + 1) + ". " << char(186);
			cout << setw(15) << left << ' ' + data_pajak.plat[i] << char(186);
			cout << setw(10) << left << ' ' + to_string(data_pajak.nominal[i]) << char(186);
			cout << setw(15) << left << ' ' + data_pajak.keterangan[i] << char(186);
		}
		cout << endl;
	}
	cout << "==================================================" << endl;

	cout << endl;
}
void prosesTambahPajak(string *plat, int *nominal)
{
	data_pajak.plat[data_pajak.awal] = *plat;
	data_pajak.nominal[data_pajak.awal] = *nominal;
	data_pajak.keterangan[data_pajak.awal] = "BELUM LUNAS";
}
void tambahPajak()
{
	system("cls");
	showDataPajak();

	cout << "Tambah Data Pajak" << endl;
	cout << "============================" << endl;

	data_pajak.awal++;

	if (data_pajak.awal < MAX)
	{
		cout << "Input plat\t: ";
		string plat;
		cin.ignore();
		getline(cin, plat);

		cout << "Input nominal\t: ";
		int nominal;
		cin >> nominal;

		prosesTambahPajak(&plat, &nominal);

		cout << "\nData berhasil ditambahkan" << endl;
	}
	else
	{
		cout << "\nData sudah penuh" << endl;
	}

	cout << "============================" << endl;
}
void prosesEditPajak(int i, string *plat, int *nominal)
{
	data_pajak.plat[i] = *plat;
	data_pajak.nominal[i] = *nominal;
}
void editPajak()
{
	system("cls");
	showDataPajak();

	cout << "Edit Data Pajak" << endl;
	cout << "============================" << endl;

	cout << "Nomor\t: ";
	int nomor;
	cin >> nomor;

	int i = nomor - 1;

	if (i >= 0 && i <= data_pajak.awal)
	{
		cout << "Plat\t: ";
		string plat;
		cin.ignore();
		getline(cin, plat);

		cout << "Nominal\t: ";
		int nominal;
		cin >> nominal;

		prosesEditPajak(i, &plat, &nominal);

		cout << "\nData Berhasil Diubah" << endl;
	}
	else
	{
		cout << "\nInput Salah" << endl;
	}

	cout << "============================" << endl;
}
void menuPajak()
{
	int pilihan = -1;

	while (pilihan != 0)
	{
		// Menampilkan data Pajak
		showDataPajak();

		cout << "Menu Pajak" << endl;
		cout << "============================" << endl;
		cout << "[1] Tambah data pajak" << endl;
		cout << "[2] Edit data pajak" << endl;
		cout << "[3] Menu pembayar" << endl;
		cout << "[0] Exit" << endl;
		cout << "============================" << endl;
		cout << "\nPilih [1..3] : ";
		cin >> pilihan;
		cout << "============================" << endl;

		switch (pilihan)
		{
		case 1:
			tambahPajak();
			break;
		case 2:
			editPajak();
			break;
		case 3:
			if (!menuAntrean())
				pilihan = 0;
			else 
				continue;
			break;
		case 0:
			cout << "\nExit" << endl;
			cout << "============================" << endl;
			break;
		default:
			cout << "\nInput Salah" << endl;
			cout << "============================" << endl;
			break;
		}

		system("pause");
		system("cls");
	}
}

int main()
{
	menuPajak();

	return 0;
}