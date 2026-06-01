# Sistem Penerangan Otomatis iSurf (Smart Lamp IoT)

Proyek ini adalah sistem lampu pintar (smart lamp) berbasis IoT menggunakan **ESP32** dan platform **Blynk**. Sistem ini mengontrol tingkat kecerahan lampu secara dinamis berdasarkan jarak objek/tangan yang dideteksi oleh sensor ultrasonik, sekaligus mengirimkan data pemantauan secara real-time ke aplikasi Blynk.

## 📌 Fitur Utama
* **Kontrol Kecerahan Otomatis:** Kecerahan lampu disesuaikan secara otomatis menggunakan PWM berdasarkan jarak objek dari sensor ultrasonik (semakin dekat objek, semakin terang lampu).
* **Integrasi Blynk IoT:** Memantau jarak objek dan kecerahan lampu secara real-time dari mana saja melalui dashboard Blynk.
* **Konektivitas Wi-Fi:** Terhubung ke jaringan internet secara nirkabel menggunakan modul bawaan ESP32.

---

## 🛠️ Komponen & Skema Pin

### Komponen yang Dibutuhkan:
1. **ESP32 Development Board**
2. **Sensor Ultrasonik HC-SR04** (untuk mendeteksi jarak)
3. **LED / Lampu** (yang mendukung kontrol analog/PWM)
4. **Kabel Jumper & Breadboard**

### Konfigurasi Pin ESP32:
| Komponen | Pin Sensor | Pin ESP32 | Keterangan |
| :--- | :--- | :--- | :--- |
| **Sensor Ultrasonik** | VCC | 5V / 3.3V | Catu Daya |
| | Trig | **GPIO 12** | Output Trigger |
| | Echo | **GPIO 27** | Input Echo |
| | GND | GND | Ground |
| **Lampu / LED** | Positif (+) | **GPIO 33** | Output PWM (Kecerahan) |
| | Negatif (-) | GND | Ground |

---

## ☁️ Konfigurasi Blynk & Wi-Fi

Untuk menghubungkan perangkat ke Blynk, sesuaikan parameter berikut pada kode [smart_lamp.ino](smart_lamp.ino):

```cpp
#define BLYNK_TEMPLATE_ID   "TMPL6_xJRHLVL"
#define BLYNK_TEMPLATE_NAME "Sistem Penerangan Otomatis iSurf"
#define BLYNK_AUTH_TOKEN    "7CV9oDHWkch5XWhUWP1j4O8QWt3keyOo"

char ssid[] = "mono";          // Nama Wi-Fi Anda
char pass[] = "iotsamsungg";   // Password Wi-Fi Anda
```

### Virtual Pins pada Blynk:
* **V0 (Virtual Pin 0):** Mengirimkan data **Jarak (Distance)** dalam satuan centimeter (cm).
* **V1 (Virtual Pin 1):** Mengirimkan data **Kecerahan Lampu (Brightness)** dengan rentang nilai `0 - 255`.

---

## ⚙️ Cara Kerja Sistem

1. Sensor ultrasonik memancarkan sinyal trigger dan menerima pantulannya (echo) untuk mengukur jarak objek di depannya.
2. Jarak yang diukur kemudian dibatasi (*constrain*) pada rentang **2 cm hingga 50 cm**.
3. Nilai jarak tersebut dipetakan (*mapping*) ke nilai PWM kecerahan lampu (`0 - 255`):
   * Jarak **2 cm** (sangat dekat) $\rightarrow$ Kecerahan Maksimal (**255**).
   * Jarak **50 cm** atau lebih (jauh) $\rightarrow$ Lampu Mati (**0**).
4. ESP32 mengirimkan nilai jarak dan kecerahan lampu ke aplikasi Blynk secara real-time.

---

## 🚀 Cara Memulai

1. **Persiapan Arduino IDE:**
   * Pastikan Anda telah menginstal Board Manager untuk **ESP32** di Arduino IDE.
   * Instal pustaka **Blynk** melalui Library Manager (*Sketch -> Include Library -> Manage Libraries...*).

2. **Koneksi Perangkat:**
   * Hubungkan ESP32 ke komputer menggunakan kabel USB.
   * Rangkai komponen sesuai dengan tabel skema pin di atas.

3. **Unggah Kode:**
   * Buka file [smart_lamp.ino](smart_lamp.ino) di Arduino IDE.
   * Ubah `ssid` dan `pass` sesuai dengan jaringan Wi-Fi Anda jika diperlukan.
   * Pilih board **ESP32 Dev Module** dan port yang sesuai.
   * Klik tombol **Upload**.

4. **Monitor Serial:**
   * Buka *Serial Monitor* dengan baud rate `115200` untuk melihat status koneksi internet dan data jarak yang terbaca secara langsung.
