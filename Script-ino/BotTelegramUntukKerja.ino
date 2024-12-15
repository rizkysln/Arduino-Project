#include "CTBot.h"
CTBot myBot;
String ssid = "rizky"; // GANTI mySSID DENGAN SSID WIFI ANDA
String pass = "rizky123"; // GANTI myPassword DENGAN PASSWORD WIFI ANDA, JIKA ADA
String token = "7623718527:AAFHzdwory4hnlyVVb05rHVJAb6xcJ4cYMA"; // GANTI myToken DENGAN TOKEN BOT TELEGRAM ANDA

void setup() {
  // inisialisasi Serial
  Serial.begin(9600);
  Serial.println("Memulai TelegramBot...");

  // hubungkan ESP8266 ke titik akses yang diinginkan
  myBot.wifiConnect(ssid, pass);

  // atur token bot telegram
  myBot.setTelegramToken(token);

  // periksa apakah semuanya baik-baik saja
  if (myBot.testConnection())
    Serial.println("\ntestConnection OK");
  else
    Serial.println("\ntestConnection NOK");
}

void loop() {
  // variabel untuk menyimpan data pesan telegram
  TBMessage msg;

  // jika ada pesan masuk...
  if (CTBotMessageText == myBot.getNewMessage(msg)) {
    String message = msg.text;
    
    // Cetak pesan yang diterima di Serial Monitor
    Serial.println("Pesan Diterima: " + message);

    // Periksa apakah pesan adalah "/start"
    if (message == "/start") {
      String startMessage = "Halo! Ini adalah bot untuk mencatat pesanan.\n"
                            "Cara pakai:\n"
                            "1. Ketik 'lapor' diikuti daftar item dan jumlahnya.\n"
                            "   Contoh:\n"
                            "   lapor\n"
                            "   nasi 15\n"
                            "   ayam 25\n"
                            "   ongkos 10\n"
                            "2. Bot akan menghitung totalnya dan mengirim kembali ke Anda.";

      // Kirim pesan penjelasan kembali ke pengirim
      myBot.sendMessage(msg.sender.id, startMessage);
      Serial.println("Pesan Terkirim:\n" + startMessage);
    }

    // Periksa apakah pesan dimulai dengan "lapor"
    else if (message.startsWith("lapor")) {
      // Format ulang pesan dan hitung total
      String formattedMessage = "List Orderan:\n";
      int total = 0;

      // Pisahkan setiap baris
      int index = message.indexOf('\n') + 1; // Mulai setelah kata "lapor"
      while (index < message.length()) {
        // Cari akhir baris
        int nextLine = message.indexOf('\n', index);
        if (nextLine == -1) nextLine = message.length();

        String line = message.substring(index, nextLine);
        index = nextLine + 1;

        // Abaikan baris kosong
        if (line.length() == 0) continue;

        // Pisahkan item dan jumlah
        int spaceIndex = line.lastIndexOf(' ');
        if (spaceIndex == -1) continue;

        String item = line.substring(0, spaceIndex);
        String amountStr = line.substring(spaceIndex + 1);
        int amount = amountStr.toInt();

        // Jika item adalah "ongkos", berikan jarak dua kali enter tanpa tanda penghubung
        if (item == "ongkos") {
          formattedMessage += "\n\n" + item + ": " + amountStr + "\n";
          total += amount;  // Tambahkan ongkos ke total
        } else {
          // Tambahkan ke pesan dan hitung total
          formattedMessage += "- " + item + ": " + amountStr + "\n";
          total += amount;
        }
      }

      formattedMessage += "Total: " + String(total) + " ya kk 🙏";
      
      // Kirim pesan kembali ke pengirim
      myBot.sendMessage(msg.sender.id, formattedMessage);

      // Cetak pesan hasil format di Serial Monitor
      Serial.println("Pesan Terkirim:\n" + formattedMessage);
    }
  }

  // tunggu 500 milidetik
  delay(500);
}
