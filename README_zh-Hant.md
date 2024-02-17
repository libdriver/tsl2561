[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver TSL2561

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/tsl2561/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

TSL2560和TSL2561是數字光強轉換器，它將光強度轉換為數字信號輸出，通過IIC（TSL2561）或SMBus（TSL2560）接口進行通信。每個設備使用一個寬帶光電二極管（可見光+紅外），CMOS上的紅外響應光電二極管能夠提供20位動態範圍內的響應（16位分辨率）。兩個集成ADC採集光電二極管電流的數字輸出，每路ADC表示在每個通道上測量的輻照度。輸出可以輸入到微處理器，其中照度（環境光用經驗公式推導出以勒克斯為單位的近似人眼觀察結果。TSL2560設備允許SMB警報式中斷，TSL2561設備支持傳統的中斷直到固件清除它。雖然適用於一般用途的光傳感應用，但TSL2560/61設備是專門為顯示面板設計的（LCD、OLED等）以延長電池壽命和在不同的照明條件下提供最佳的視覺效果。顯示面板背光，其中最多可占平台總功率的40%，可自動管理。這兩種設備也是控制鍵盤基於環境照明的理想選擇。照度信息可進一步用於管理數碼相機的曝光控制。TSL2560/61設備適用於筆記本/平板電腦、液晶顯示器、平板電腦電視、手機和數碼相機。此外，其他應用包括路燈控制，安全照明，採光、機器視覺和汽車儀表組等。

LibDriver TSL2561是LibDriver推出的TSL2561全功能驅動，該驅動提供亮度讀取、亮度中斷檢測等功能並且它符合MISRA標準。

### 目錄

  - [說明](#說明)
  - [安裝](#安裝)
  - [使用](#使用)
    - [example basic](#example-basic)
    - [example interrupt](#example-interrupt)
  - [文檔](#文檔)
  - [貢獻](#貢獻)
  - [版權](#版權)
  - [聯繫我們](#聯繫我們)

### 說明

/src目錄包含了LibDriver TSL2561的源文件。

/interface目錄包含了LibDriver TSL2561與平台無關的IIC總線模板。

/test目錄包含了LibDriver TSL2561驅動測試程序，該程序可以簡單的測試芯片必要功能。

/example目錄包含了LibDriver TSL2561編程範例。

/doc目錄包含了LibDriver TSL2561離線文檔。

/datasheet目錄包含了TSL2561數據手冊。

/project目錄包含了常用Linux與單片機開發板的工程樣例。所有工程均採用shell腳本作為調試方法，詳細內容可參考每個工程裡面的README.md。

/misra目錄包含了LibDriver MISRA程式碼掃描結果。

### 安裝

參考/interface目錄下與平台無關的IIC總線模板，完成指定平台的IIC總線驅動。

將/src目錄，您使用平臺的介面驅動和您開發的驅動加入工程，如果您想要使用默認的範例驅動，可以將/example目錄加入您的工程。

### 使用

您可以參考/example目錄下的程式設計範例完成適合您的驅動，如果您想要使用默認的程式設計範例，以下是它們的使用方法。

#### example basic

```C
#include "driver_tsl2561_basic.h"

uint8_t res;
uint8_t i;
uint32_t lux;

res = tsl2561_basic_init(TSL2561_ADDRESS_FLOAT);
if (res != 0)
{
    return 1;
}

...

for (i = 0; i < 3; i++)
{
    tsl2561_interface_delay_ms(1000);
    res = tsl2561_basic_read((uint32_t *)&lux);
    if (res != 0)
    {
        (void)tsl2561_basic_deinit();

        return 1;
    }
    tsl2561_interface_debug_print("tsl2561: read is %d lux.\n", lux);

    ...
    
}

...

(void)tsl2561_basic_deinit();

return 0;
```

#### example interrupt

```C
#include "driver_tsl2561_interrupt.h"

uint8_t res;
uint8_t i;
uint32_t lux;
uint8_t g_flag;

void gpio_irq(void)
{
    g_flag = 1;
}

res = tsl2561_interrupt_init(TSL2561_ADDRESS_FLOAT, TSL2561_INTERRUPT_MODE_EVERY_ADC_CYCLE, 10, 100);
if (res != 0)
{
    return 1;
}
res = gpio_interrupt_init();
if (res != 0)
{
    (void)tsl2561_interrupt_deinit();

    return 1;
}

...

g_flag = 0;
for (i = 0; i < 3; i++)
{
    tsl2561_interface_delay_ms(1000);
    res = tsl2561_interrupt_read((uint32_t *)&lux);
    if (res != 0)
    {
        (void)tsl2561_interrupt_deinit();
        (void)gpio_interrupt_deinit();

        return 1;
    }
    tsl2561_interface_debug_print("tsl2561: %d/%d.\n", (uint32_t)(i+1), (uint32_t)times);
    tsl2561_interface_debug_print("tsl2561: read is %d lux.\n", lux);

    ...
    
    if (g_flag != 0)
    {
        tsl2561_interface_debug_print("tsl2561: find interrupt.\n");

        break;
    }
    
    ...

}

...

(void)tsl2561_interrupt_deinit();
(void)gpio_interrupt_deinit();

return 0;
```

### 文檔

在線文檔: [https://www.libdriver.com/docs/tsl2561/index.html](https://www.libdriver.com/docs/tsl2561/index.html)。

離線文檔: /doc/html/index.html。

### 貢獻

請參攷CONTRIBUTING.md。

### 版權

版權 (c) 2015 - 現在 LibDriver 版權所有

MIT 許可證（MIT）

特此免費授予任何獲得本軟件副本和相關文檔文件（下稱“軟件”）的人不受限制地處置該軟件的權利，包括不受限制地使用、複製、修改、合併、發布、分發、轉授許可和/或出售該軟件副本，以及再授權被配發了本軟件的人如上的權利，須在下列條件下：

上述版權聲明和本許可聲明應包含在該軟件的所有副本或實質成分中。

本軟件是“如此”提供的，沒有任何形式的明示或暗示的保證，包括但不限於對適銷性、特定用途的適用性和不侵權的保證。在任何情況下，作者或版權持有人都不對任何索賠、損害或其他責任負責，無論這些追責來自合同、侵權或其它行為中，還是產生於、源於或有關於本軟件以及本軟件的使用或其它處置。

### 聯繫我們

請聯繫lishifenging@outlook.com。