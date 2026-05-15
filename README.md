# 💹 Saving Organizator

**Saving Organizator**, döviz, altın ve BIST100 yatırımlarınızı tek bir merkezden yönetmeniz, kar/zarar durumunuzu anlık olarak takip etmeniz için geliştirilmiş masaüstü tabanlı bir portfolyo yönetim uygulamasıdır.

🔗 **Depo Adresi:** [https://github.com/EmreBilal98/Saving_Organizator](https://github.com/EmreBilal98/Saving_Organizator.git)

---

## ✨ Özellikler

*   **Güvenli Erişim:** Kullanıcı adı ve şifre ile kişiselleştirilmiş giriş ve kayıt sistemi.
*   **Geniş Yatırım Yelpazesi:** Döviz kurları, gram altın ve BIST100 hisse senetleri takibi.
*   **Akıllı İşlem Girişi:** 
    *   Yatırım eklerken veya çıkarırken işlem yaptığınız fiyatı manuel olarak girebilirsiniz.
    *   **Otomatik Fiyat Çekme:** Fiyat kısmını boş bırakırsanız, uygulama o saniyedeki canlı piyasa verilerini otomatik olarak çeker ve işlemi o fiyattan yapmışsınız gibi kaydeder.
*   **Anlık Kar/Zarar Analizi:** Tüm varlıklarınızın toplam maliyetini ve güncel piyasa koşullarına göre anlık kar/zarar durumunuzu ana ekranda görebilirsiniz.
*   **Detaylı Hesap Hareketleri:** Yapılan her işlem görsel olarak zenginleştirilmiş HTML formatında kaydedilir.
    *   *İçerik:* Yatırım adı, işlem miktarı (+/-), özel not, işlem sonrası toplam varlık ve işlem tarihi.

---

## 📸 Ekran Görüntüleri

### 🔐 Kimlik Doğrulama
Uygulama, her kullanıcının kendi verisini saklayabilmesi için güvenli bir giriş paneli sunar.

| Kayıt Ol (Sign Up) | Giriş Yap (Login) | Oturumu Kapat (Log Out) |
| :---: | :---: | :---: |
| ![Sign Up](screenshots/signup.png) | ![Login](screenshots/login.png) | ![Log Out](screenshots/logout.png) |

---

### 🖥️ Ana Ekran ve Yönetim Paneli
Varlıklarınızı takip edebileceğiniz ve anlık değişimleri görebileceğiniz ana arayüz.

![Ana Ekran](screenshots/main_screen.png)

#### **Yatırım Ekleme & Silme Dialogları**
Döviz, Altın ve BIST100 kategorileri için optimize edilmiş, not ekleme özellikli işlem pencereleri.

| Yatırım Tipi | Ekleme (Add) | Silme (Delete) |
| :--- | :---: | :---: |
| **Döviz İşlemleri** | ![Currency Add](screenshots/currency_add.png) | ![Currency Delete](screenshots/currency_delete.png) |
| **Altın İşlemleri** | ![Gold Add](screenshots/gold_add.png) | ![Gold Delete](screenshots/gold_delete.png) |
| **BIST100 İşlemleri** | ![BIST Add](screenshots/bist_add.png) | ![BIST Delete](screenshots/bist_delete.png) |

---

### 📝 Hesap Hareketleri ve Geçmiş
Tüm finansal geçmişinizi şık bir HTML tablo yapısında, işlem notlarınızla birlikte takip edin.

![Hesap Hareketleri](screenshots/history.png)

---

## 🛠️ Teknik Altyapı

*   **Framework:** Qt 6 (Widgets)
*   **Dil:** C++
*   **Veri Kaynağı:** `QNetworkAccessManager` ile  API entegrasyonu ve webScraping.
*   **Veri İşleme:** HTML tabanlı içerik üretimi ve dinamik kar/zarar hesaplama algoritmaları.
*   **Veri Tabanı:** SQLite.

---

## 🚀 Kurulum

### Gereksinimler
*   Qt 6.x SDK
*   C++17 destekleyen bir derleyici (GCC, MSVC, Clang)

## 📦 İndir ve Çalıştır (Releases)

Uygulamayı kaynak koddan derlemekle uğraşmadan, işletim sisteminize uygun hazır paketleri kullanarak doğrudan çalıştırabilirsiniz.

### ⬇️ Güncel Sürümler
En son kararlı sürüme [Releases](https://github.com/EmreBilal98/Saving_Organizator/releases) sayfasından ulaşabilirsiniz.

#### 🐧 Linux (AppImage)
Linux kullanıcıları için tüm bağımlılıklar tek bir paket içerisindedir:
1. `Saving_Organizator-x86_64.AppImage` dosyasını indirin.
2. Dosyaya sağ tıklayıp **Özellikler > İzinler** kısmından "Dosyayı bir program gibi çalıştırmaya izin ver" seçeneğini işaretleyin (Veya terminalde `chmod +x <dosya_adi>` komutunu çalıştırın).
3. Çift tıklayarak uygulamayı başlatın.

#### 🪟 Windows (Portable / Zip)
1. `Saving_Organizator_Windows.zip` dosyasını indirin.
2. Arşivi istediğiniz bir klasöre çıkartın.
3. Klasör içindeki `Saving_Organizator.exe` dosyasını çalıştırın.

---

### Derleme Adımları
```bash
git clone [https://github.com/EmreBilal98/Saving_Organizator.git](https://github.com/EmreBilal98/Saving_Organizator.git)
cd Saving_Organizator
qmake6  # veya projenizi Qt Creator ile açın
make
