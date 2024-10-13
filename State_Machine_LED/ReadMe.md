## 1. main.c Dosyası

* Bu dosya, STM32 mikrodenetleyicisini başlatan ve durmadan dönen ana uygulama döngüsünü içeren bir yapıdadır.

**Genel Akış :**
* **HAL Kütüphanesi :** STM32'de donanımı başlatan HAL_Init() ve sistem saatini ayarlayan SystemClock_Config() fonksiyonları kullanılıyor. Bu fonksiyonlar temel olarak STM32'nin donanım altyapısını başlatıyor.
* **TIMER :** MX_TIM1_Init() fonksiyonu, TIM1 zamanlayıcısının başlatılması için kullanılıyor ve HAL_TIM_Base_Start_IT(&htim1) fonksiyonu, bu zamanlayıcı kesmesinin aktif edilmesini sağlıyor. Böylece her belirlenen sürede bir zamanlayıcı kesmesi tetikleniyor.
* **while(1) :** while (1) döngüsü içinde, yazılmış olan durum makinesindeki mevcut duruma göre, state_table\[current_state\]() fonksiyonu çağrılıyor. Bu her bir durumda yapılacak işlemi temsil ediyor. Burada state_table[] fonksiyonu, hangi durumun çalıştırılacağını belirleyen dizidir.

* **state_machine_init() :** Başlangıçta durum makinesi STATE_LED1 durumuna ayarlanıyor ve tüm LED'ler kapatılıyor. Bu durum makinesinin başlatma fonksiyonudur.
* **Zamanlayıcı Kesme Callback Fonksiyonu (HAL_TIM_PeriodElapsedCallback):** Zamanlayıcı her çalıştıüında clock_counter değeri artırılıyor. Bu sayede belirli bir sürede bir işlem yapılabiliyor.

-----------------------------------------------------------------------------------------------------------------------------------------------------------------

## 2. TIM1 konfigürasyonu

**MX_TIM1_Init() fonksiyonu, TIM1 zamanlayıcısının ayarlarını yapar:**
* **Prescaler :** 17999 değeri, TIM1 e uygulanan saat frekansını bölerek daha yavaş bir sayaç sağlar.
* **Period :** 9999 değeri ile belirlenen periyod sonunda zamanlayıcı kesmesi tetiklenir.
Bu ayarlar, zamanlayıcıyı belirli periyodik aralıklarla kesme üretmesi için yapılandırıyor. Yani her zamanlayıcı kesmesinde (1 saniyede bir) clock_counter artılıyor.

------------------------------------------------------------------------------------------------------------------------------------------------------------------

## 3. GPIO konfigürasyonu

**MX_GPIO_Init() fonksiyonu, GPIO portlarını başlatır ve LED pinlerini çıkış moduna ayarlar:**
* LED'ler, GPIOA portunda 5, 6, 7 ve 8 numaralı pinlere bağlı.
* Başlangıçta bu LED'lerin hepsi kapalı (HAL_GPIO_WritePin(GPIOA, LED1_Pin | LED2_Pin | LED3_Pin | LED4_Pin, GPIO_PIN_RESET)).

------------------------------------------------------------------------------------------------------------------------------------------------------------------

## 4. STATE MACHINE

* **state_machine.c Dosyası**
  * Bu dosya, durum makinesini ve her bir duruma ait fonksiyonları içerir.
  * **Durumlar :** Dört farklı durum vardır: STATE_LED1, STATE_LED2, STATE_LED3, STATE_LED4.
  * **Durum Tablosu :** void (*state_table[])(void) dizisi, her duruma ait fonksiyonları içerir.
    * **state_LED1 :** LED1 yanar.
    * **state_LED2 :** LED1 ve LED2 yanar.
    * **state_LED3 :** LED1, LED2 ve LED3 yanar.
    * **state_LED4 :** Tüm LED'ler yanar ve ardından tekrar başa dönülür.
  * **state_machine_init() :** Durum makinesi STATE_LED1 olarak başlatılır ve başlangıçta tüm LED'ler söndürülür.
  * **state_LED1() :** Zamanlayıcı kesmesi (clock_counter == 1) ile LED1 yanar ve sonraki duruma geçilir.
  * **state_LED2() :** clock_counter == 2 olduğunda, LED1 ve LED2 yanar ve sonraki duruma geçilir.
  * **state_LED3() :** clock_counter == 3 olduğunda, LED1, LED2 ve LED3 yanar.
  * **state_LED4() :** clock_counter == 4 olduğunda, tüm LED'ler yanar, 100 ms'lik bir bekleme süresi ile LED'ler söndürülür ve tekrar STATE_LED1 durumuna dönülür. clock_counter sıfırlanır.

------------------------------------------------------------------------------------------------------------------------------------------------------------------

* **state_machine.h Dosyası**
  * Bu dosya, durum makinesiyle ilgili fonksiyonların ve durumların prototiplerini içerir.
  * **State_Type :** LED'leri yöneten dört farklı durum.
  * Durum fonksiyonlarının prototipleri (state_LED1, state_LED2, vb.).
  * **Genel İşleyiş :**
    * Program başlangıçta tüm LED'leri söndürür.
    * Zamanlayıcı kesmesiyle birlikte clock_counter her bir saniyede bir artar.
    * Her kesmede ilgili duruma geçilir ve bir sonraki LED yanar.
    * Dördüncü duruma gelindiğinde tüm LED'ler yanar ve döngü baştan başlar.


**NOT :** HAL_Delay() kullanımı yerine zamanlayıcı kesmeleriyle daha doğru zamanlama kontrolü yapılabilir.



