[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver TSL2561

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/tsl2561/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE) 

Die TSL2560 und TSL2561 sind Licht-Digital-Wandler, die die Lichtintensität in einen digitalen Signalausgang umwandeln, der für eine direkte IIC- (TSL2561) oder SMBus-Schnittstelle (TSL2560) geeignet ist. Jedes Gerät kombiniert eine Breitband-Photodiode (sichtbar plus Infrarot) und eine auf Infrarot ansprechende Photodiode auf einem einzigen integrierten CMOS-Schaltkreis, der in der Lage ist, über einen effektiven 20-Bit-Dynamikbereich (16-Bit-Auflösung) eine fast photopische Reaktion zu liefern. Zwei integrierende ADCs wandeln die Photodiodenströme in ein digitales Ausgangssignal um, das die auf jedem Kanal gemessene Bestrahlungsstärke darstellt. Diese digitale Ausgabe kann in einen Mikroprozessor eingegeben werden, wo die Beleuchtungsstärke (Umgebungslichtstärke) in Lux unter Verwendung einer empirischen Formel abgeleitet wird, um die Reaktion des menschlichen Auges anzunähern. Das TSL2560-Gerät lässt einen SMB-Alert-Stil-Interrupt zu, und das TSL2561-Gerät unterstützt einen traditionellen Level-Stil-Interrupt, der aktiviert bleibt, bis die Firmware ihn löscht. Die TSL2560/61-Bausteine sind zwar für allgemeine Lichtsensoranwendungen nützlich, wurden jedoch speziell für Anzeigetafeln (LCD, OLED usw.) entwickelt, um die Batterielebensdauer zu verlängern und eine optimale Anzeige bei unterschiedlichen Lichtverhältnissen zu ermöglichen. Die Hintergrundbeleuchtung des Anzeigefelds, die bis zu 30 bis 40 Prozent der gesamten Plattformleistung ausmachen kann, kann automatisch verwaltet werden. Beide Geräte eignen sich auch ideal zur Steuerung der Tastaturbeleuchtung basierend auf den Lichtverhältnissen der Umgebung. Informationen zur Beleuchtungsstärke können ferner verwendet werden, um die Belichtungssteuerung in Digitalkameras zu verwalten. Die TSL2560/61-Geräte eignen sich ideal für Notebooks/Tablet-PCs, LCD-Monitore, Flachbildfernseher, Mobiltelefone und Digitalkameras. Darüber hinaus umfassen andere Anwendungen die Steuerung von Straßenlaternen, Sicherheitsbeleuchtung, Sonnenlichternte, maschinelles Sehen und Automobil-Instrumentencluster.

LibDriver TSL2561 ist der TSL2561-Vollfunktionstreiber, der von LibDriver gestartet wurde. Er bietet Helligkeitsmessung, Erkennung von Helligkeitsunterbrechungen und andere Funktionen. LibDriver ist MISRA-konform.

### Inhaltsverzeichnis

  - [Anweisung](#Anweisung)
  - [Installieren](#Installieren)
  - [Nutzung](#Nutzung)
    - [example basic](#example-basic)
    - [example interrupt](#example-interrupt)
  - [Dokument](#Dokument)
  - [Beitrag](#Beitrag)
  - [Lizenz](#Lizenz)
  - [Kontaktieren Sie uns](#Kontaktieren-Sie-uns)

### Anweisung

/src enthält LibDriver TSL2561-Quelldateien.

/interface enthält die plattformunabhängige Vorlage LibDriver TSL2561 IIC.

/test enthält den Testcode des LibDriver TSL2561-Treibers und dieser Code kann die erforderliche Funktion des Chips einfach testen.

/example enthält LibDriver TSL2561-Beispielcode.

/doc enthält das LibDriver TSL2561-Offlinedokument.

/Datenblatt enthält TSL2561-Datenblatt.

/project enthält den allgemeinen Beispielcode für Linux- und MCU-Entwicklungsboards. Alle Projekte verwenden das Shell-Skript, um den Treiber zu debuggen, und die detaillierten Anweisungen finden Sie in der README.md jedes Projekts.

/misra enthält die Ergebnisse des LibDriver MISRA Code Scans.

### Installieren

Verweisen Sie auf eine plattformunabhängige IIC-Schnittstellenvorlage und stellen Sie Ihren Plattform-IIC-Treiber fertig.

Fügen Sie das Verzeichnis /src, den Schnittstellentreiber für Ihre Plattform und Ihre eigenen Treiber zu Ihrem Projekt hinzu. Wenn Sie die Standardbeispieltreiber verwenden möchten, fügen Sie das Verzeichnis /example zu Ihrem Projekt hinzu.

### Nutzung

Sie können auf die Beispiele im Verzeichnis /example zurückgreifen, um Ihren eigenen Treiber zu vervollständigen. Wenn Sie die Standardprogrammierbeispiele verwenden möchten, erfahren Sie hier, wie Sie diese verwenden.

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

```c
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

### Dokument

Online-Dokumente: [https://www.libdriver.com/docs/tsl2561/index.html](https://www.libdriver.com/docs/tsl2561/index.html).

Offline-Dokumente: /doc/html/index.html.

### Beitrag

Bitte beachten Sie CONTRIBUTING.md.

### Lizenz

Urheberrechte © (c) 2015 - Gegenwart LibDriver Alle Rechte vorbehalten



Die MIT-Lizenz (MIT)



Hiermit wird jeder Person kostenlos die Erlaubnis erteilt, eine Kopie zu erhalten

dieser Software und zugehörigen Dokumentationsdateien (die „Software“) zu behandeln

in der Software ohne Einschränkung, einschließlich, aber nicht beschränkt auf die Rechte

zu verwenden, zu kopieren, zu modifizieren, zusammenzuführen, zu veröffentlichen, zu verteilen, unterzulizenzieren und/oder zu verkaufen

Kopien der Software und Personen, denen die Software gehört, zu gestatten

dazu eingerichtet werden, unter folgenden Bedingungen:



Der obige Urheberrechtshinweis und dieser Genehmigungshinweis müssen in allen enthalten sein

Kopien oder wesentliche Teile der Software.



DIE SOFTWARE WIRD "WIE BESEHEN" BEREITGESTELLT, OHNE JEGLICHE GEWÄHRLEISTUNG, AUSDRÜCKLICH ODER

STILLSCHWEIGEND, EINSCHLIESSLICH, ABER NICHT BESCHRÄNKT AUF DIE GEWÄHRLEISTUNG DER MARKTGÄNGIGKEIT,

EIGNUNG FÜR EINEN BESTIMMTEN ZWECK UND NICHTVERLETZUNG VON RECHTEN DRITTER. IN KEINEM FALL DARF DAS

AUTOREN ODER URHEBERRECHTSINHABER HAFTEN FÜR JEGLICHE ANSPRÜCHE, SCHÄDEN ODER ANDERE

HAFTUNG, OB AUS VERTRAG, DELIKT ODER ANDERWEITIG, ENTSTEHEND AUS,

AUS ODER IM ZUSAMMENHANG MIT DER SOFTWARE ODER DER VERWENDUNG ODER ANDEREN HANDLUNGEN MIT DER

SOFTWARE.

### Kontaktieren Sie uns

Bitte senden Sie eine E-Mail an lishifenging@outlook.com.