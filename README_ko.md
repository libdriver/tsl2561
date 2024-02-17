[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver TSL2561

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/tsl2561/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

TSL2560 및 TSL2561은 광도를 직접 IIC(TSL2561) 또는 SMBus(TSL2560) 인터페이스가 가능한 디지털 신호 출력으로 변환하는 광-디지털 변환기입니다. 각 장치는 하나의 광대역 광다이오드(가시광선 + 적외선)와 하나의 적외선 응답 광다이오드를 단일 CMOS 집적 회로에 결합하여 유효 20비트 동적 범위(16비트 분해능)에서 거의 광도에 가까운 응답을 제공할 수 있습니다. 2개의 통합 ADC는 포토다이오드 전류를 각 채널에서 측정된 조도를 나타내는 디지털 출력으로 변환합니다. 이 디지털 출력은 인간의 눈 반응을 근사화하기 위해 경험적 공식을 사용하여 lux 단위의 조도(주변광 수준)가 유도되는 마이크로프로세서에 입력될 수 있습니다. TSL2560 장치는 SMB-Alert 스타일 인터럽트를 허용하고 TSL2561 장치는 펌웨어가 제거할 때까지 어설션된 상태로 유지되는 기존 레벨 스타일 인터럽트를 지원합니다. 범용 광 감지 애플리케이션에 유용하지만 TSL2560/61 장치는 배터리 수명을 연장하고 다양한 조명 조건에서 최적의 보기를 제공하기 위해 특별히 디스플레이 패널(LCD, OLED 등)용으로 설계되었습니다. 전체 플랫폼 전력의 최대 30~40%를 차지할 수 있는 디스플레이 패널 백라이트를 자동으로 관리할 수 있습니다. 두 장치 모두 주변 조명 조건에 따라 키보드 조명을 제어하는 데 이상적입니다. 조도 정보는 디지털 카메라의 노출 제어를 관리하는 데 추가로 사용할 수 있습니다. TSL2560/61 장치는 노트북/태블릿 PC, LCD 모니터, 평면 패널 TV, 휴대폰 및 디지털 카메라에 이상적입니다. 또한 다른 애플리케이션에는 가로등 제어, 보안 조명, 햇빛 수확, 머신 비전 및 자동차 계측 클러스터가 포함됩니다.

LibDriver TSL2561은 LibDriver에서 출시한 TSL2561 전체 기능 드라이버입니다. 밝기 읽기, 밝기 중단 감지 및 기타 기능을 제공합니다. LibDriver는 MISRA를 준수합니다.

### 콘텐츠

  - [설명](#설명)
  - [설치](#설치)
  - [사용](#사용)
    - [example basic](#example-basic)
    - [example interrupt](#example-interrupt)
  - [문서](#문서)
  - [기고](#기고)
  - [저작권](#저작권)
  - [문의하기](#문의하기)

### 설명

/src 디렉토리에는 LibDriver TSL2561의 소스 파일이 포함되어 있습니다.

/interface 디렉토리에는 LibDriver TSL2561용 플랫폼 독립적인 IIC버스 템플릿이 포함되어 있습니다.

/test 디렉토리에는 LibDriver TSL2561드라이버 테스트 프로그램이 포함되어 있어 칩의 필요한 기능을 간단히 테스트할 수 있습니다.

/example 디렉토리에는 LibDriver TSL2561프로그래밍 예제가 포함되어 있습니다.

/doc 디렉토리에는 LibDriver TSL2561오프라인 문서가 포함되어 있습니다.

/datasheet 디렉토리에는 TSL2561데이터시트가 있습니다.

/project 디렉토리에는 일반적으로 사용되는 Linux 및 마이크로컨트롤러 개발 보드의 프로젝트 샘플이 포함되어 있습니다. 모든 프로젝트는 디버깅 방법으로 셸 스크립트를 사용하며, 자세한 내용은 각 프로젝트의 README.md를 참조하십시오.

/misra 에는 LibDriver misra 코드 검색 결과가 포함됩니다.

### 설치

/interface 디렉토리에서 플랫폼 독립적인IIC 버스 템플릿을 참조하여 지정된 플랫폼에 대한 IIC버스 드라이버를 완성하십시오.

/src 디렉터리, 플랫폼용 인터페이스 드라이버 및 자체 드라이버를 프로젝트에 추가합니다. 기본 예제 드라이버를 사용하려면 /example 디렉터리를 프로젝트에 추가합니다.

### 사용

/example 디렉터리의 예제를 참조하여 자신만의 드라이버를 완성할 수 있습니다. 기본 프로그래밍 예제를 사용하려는 경우 사용 방법은 다음과 같습니다.

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

### 문서

온라인 문서: [https://www.libdriver.com/docs/tsl2561/index.html](https://www.libdriver.com/docs/tsl2561/index.html).

오프라인 문서: /doc/html/index.html.

### 기고

CONTRIBUTING.md 를 참조하십시오.

### 저작권

저작권 (c) 2015 - 지금 LibDriver 판권 소유

MIT 라이선스(MIT)

이 소프트웨어 및 관련 문서 파일("소프트웨어")의 사본을 얻은 모든 사람은 이에 따라 무제한 사용, 복제, 수정, 통합, 출판, 배포, 2차 라이선스를 포함하여 소프트웨어를 처분할 수 있는 권리가 부여됩니다. 소프트웨어의 사본에 대한 라이선스 및/또는 판매, 그리고 소프트웨어가 위와 같이 배포된 사람의 권리에 대한 2차 라이선스는 다음 조건에 따릅니다.

위의 저작권 표시 및 이 허가 표시는 이 소프트웨어의 모든 사본 또는 내용에 포함됩니다.

이 소프트웨어는 상품성, 특정 목적에의 적합성 및 비침해에 대한 보증을 포함하되 이에 국한되지 않는 어떠한 종류의 명시적 또는 묵시적 보증 없이 "있는 그대로" 제공됩니다. 어떤 경우에도 저자 또는 저작권 소유자는 계약, 불법 행위 또는 기타 방식에 관계없이 소프트웨어 및 기타 소프트웨어 사용으로 인해 발생하거나 이와 관련하여 발생하는 청구, 손해 또는 기타 책임에 대해 책임을 지지 않습니다.

### 문의하기

연락주세요lishifenging@outlook.com.