[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver TSL2561

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/tsl2561/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

TSL2560およびTSL2561は、光強度を直接IIC（TSL2561）またはSMBus（TSL2560）インターフェースが可能なデジタル信号出力に変換する光からデジタルへのコンバーターです。各デバイスは、1つのブロードバンドフォトダイオード（可視と赤外線）と1つの赤外線応答フォトダイオードを単一のCMOS集積回路に組み合わせて、有効な20ビットダイナミックレンジ（16ビット解像度）でフォトピックに近い応答を提供できます。 2つの統合ADCは、フォトダイオード電流を各チャネルで測定された放射照度を表すデジタル出力に変換します。このデジタル出力はマイクロプロセッサに入力できます。マイクロプロセッサでは、人間の目の反応を概算するための実験式を使用して、ルクス単位の照度（周囲光レベル）が導き出されます。 TSL2560デバイスはSMBアラートスタイルの割り込みを許可し、TSL2561デバイスはファームウェアがそれをクリアするまでアサートされたままである従来のレベルスタイルの割り込みをサポートします。 TSL2560 / 61デバイスは、汎用の光検知アプリケーションに役立ちますが、バッテリ寿命を延ばし、さまざまな照明条件で最適な表示を提供することを目的として、特にディスプレイパネル（LCD、OLEDなど）用に設計されています。プラットフォームの総電力の最大30〜40％を占める可能性があるディスプレイパネルのバックライトは、自動的に管理できます。どちらのデバイスも、周囲の照明条件に基づいてキーボードの照明を制御するのに理想的です。照度情報は、デジタルカメラの露出制御を管理するためにさらに使用できます。 TSL2560 / 61デバイスは、ノートブック/タブレットPC、LCDモニター、フラットパネルテレビ、携帯電話、およびデジタルカメラに最適です。さらに、他のアプリケーションには、街路灯制御、防犯灯、太陽光収集、マシンビジョン、および自動車計装クラスターが含まれます。

LibDriver TSL2561は、LibDriverによって起動されたTSL2561全機能ドライバーであり、輝度の読み取り、輝度の割り込み検出、およびその他の機能を提供します。 LibDriverはMISRAに準拠しています。

### 目次

  - [説明](#説明)
  - [インストール](#インストール)
  - [使用](#使用)
    - [example basic](#example-basic)
    - [example interrupt](#example-interrupt)
  - [ドキュメント](#ドキュメント)
  - [貢献](#貢献)
  - [著作権](#著作権)
  - [連絡して](#連絡して)

### 説明

/ srcディレクトリには、LibDriver TSL2561のソースファイルが含まれています。

/ interfaceディレクトリには、LibDriver TSL2561用のプラットフォームに依存しないIICバステンプレートが含まれています。

/ testディレクトリには、チップの必要な機能を簡単にテストできるLibDriver TSL2561ドライバーテストプログラムが含まれています。

/ exampleディレクトリには、LibDriver TSL2561プログラミング例が含まれています。

/ docディレクトリには、LibDriver TSL2561オフラインドキュメントが含まれています。

/ datasheetディレクトリには、TSL2561データシートが含まれています。

/ projectディレクトリには、一般的に使用されるLinuxおよびマイクロコントローラー開発ボードのプロジェクトサンプルが含まれています。 すべてのプロジェクトは、デバッグ方法としてシェルスクリプトを使用しています。詳細については、各プロジェクトのREADME.mdを参照してください。

/ misraはLibDriver misraコードスキャン結果を含む。

### インストール

/ interfaceディレクトリにあるプラットフォームに依存しないIICバステンプレートを参照して、指定したプラットフォームのIICバスドライバを完成させます。

/src ディレクトリ、プラットフォームのインターフェイス ドライバー、および独自のドライバーをプロジェクトに追加します。デフォルトのサンプル ドライバーを使用する場合は、/example ディレクトリをプロジェクトに追加します。

### 使用

/example ディレクトリ内のサンプルを参照して、独自のドライバーを完成させることができます。 デフォルトのプログラミング例を使用したい場合の使用方法は次のとおりです。

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

### ドキュメント

オンラインドキュメント: [https://www.libdriver.com/docs/tsl2561/index.html](https://www.libdriver.com/docs/tsl2561/index.html)。

オフラインドキュメント: /doc/html/index.html。

### 貢献

CONTRIBUTING.mdを参照してください。

### 著作権

著作権（c）2015-今 LibDriver 全著作権所有

MITライセンス（MIT）

このソフトウェアおよび関連するドキュメントファイル（「ソフトウェア」）のコピーを取得した人は、無制限の使用、複製、変更、組み込み、公開、配布、サブライセンスを含む、ソフトウェアを処分する権利を制限なく付与されます。ソフトウェアのライセンスおよび/またはコピーの販売、および上記のようにソフトウェアが配布された人の権利のサブライセンスは、次の条件に従うものとします。

上記の著作権表示およびこの許可通知は、このソフトウェアのすべてのコピーまたは実体に含まれるものとします。

このソフトウェアは「現状有姿」で提供され、商品性、特定目的への適合性、および非侵害の保証を含むがこれらに限定されない、明示または黙示を問わず、いかなる種類の保証もありません。 いかなる場合も、作者または著作権所有者は、契約、不法行為、またはその他の方法で、本ソフトウェアおよび本ソフトウェアの使用またはその他の廃棄に起因または関連して、請求、損害、またはその他の責任を負わないものとします。

### 連絡して

お問い合わせくださいlishifenging@outlook.com。