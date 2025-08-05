# 🤖 ESP32-CAM 스트리밍 로봇 (AP + MJPEG + WebSocket)

[![Platform](https://img.shields.io/badge/platform-ESP32--CAM-blue)]()
[![WiFi](https://img.shields.io/badge/wifi-SoftAP-orange)]()
[![Streaming](https://img.shields.io/badge/streaming-MJPEG-green)]()
[![WebSocket](https://img.shields.io/badge/control-WebSocket-purple)]()

ESP32-CAM을 이용한 초소형 무선 스트리밍 로봇 프로젝트입니다.  
자체 Wi-Fi AP를 생성하여 별도 라우터 없이 **스마트폰으로 직접 제어 가능**합니다.

---

## 📷 주요 기능

- **WiFi SoftAP 모드** → 스마트폰 직접 연결
- **HTML + WebSocket UI** → 전/후/좌/우/정지 버튼
- `/stream` MJPEG 스트리밍 → 실시간 카메라 확인
- **모터 제어 핀** 정의 포함 (4개)

---

## 🧰 하드웨어 구성

| 구성 요소 | 설명 |
|-----------|------|
| ESP32-CAM | AI Thinker 모듈 |
| 모터 드라이버 | L298N 또는 H-Bridge |
| DC 모터 2개 | 좌/우 구동 |
| 전원 | 5V~6V 배터리 팩 |
| (선택) 18650 배터리 | 휴대성 확보용 |

---

## ⚙️ 핀 연결

| 기능 | 핀 번호 |
|------|---------|
| 모터 좌측 + | GPIO 12 |
| 모터 좌측 - | GPIO 13 |
| 모터 우측 + | GPIO 14 |
| 모터 우측 - | GPIO 15 |

> **주의:** ESP32-CAM은 GPIO가 제한되어 있으므로 다른 장치 연결 시 충돌 주의!

---

## 🌐 접속 방법

1. ESP32-CAM에 코드 업로드
2. 전원 연결 → Wi-Fi 목록에 `ESP_CAM` 확인
3. 비밀번호 `12345678`로 연결
4. 브라우저에서 `http://192.168.4.1` 접속
5. 실시간 스트리밍 + 제어 UI 이용

---

## 📡 스트리밍 방식

- **JPEG 캡처 → MJPEG multipart stream**
- 1초당 약 2프레임 (`vTaskDelay(500ms)`)
- 프레임 버퍼 2개 사용 (PSRAM 여부에 따라 자동 조정)

| 설정 항목 | 값 |
|-----------|----|
| 해상도 | `FRAMESIZE_QQVGA (160×120)` |
| 압축 품질 | `0` (최고 품질) |
| 프레임 버퍼 수 | PSRAM: 2개 / 미탑재: 1개 |

---

## 🧠 WebSocket 명령어

| 명령 | 동작 |
|------|------|
| `forward` | 전진 |
| `back`    | 후진 |
| `left`    | 좌회전 |
| `right`   | 우회전 |
| `stop`    | 정지 |

버튼 클릭 시 JavaScript에서 WebSocket 메시지 전송 → ESP32가 모터 GPIO 제어

---

## 🛠️ 개발 환경

- Arduino IDE (v1.8 이상)
- 보드 매니저: `ESP32 Wrover Module`
- 선택 보드: `AI Thinker ESP32-CAM`
- 필수 라이브러리:
  - `esp_camera`
  - `esp_http_server`
  - `WiFi.h`
  - `WebSocketsServer.h`

---

## 📂 파일 설명

| 파일명 | 설명 |
|--------|------|
| `bot.c` | 전체 기능 포함된 메인 코드 (`.ino` 확장자 없음 주의) |
| `README.md` | 프로젝트 설명 문서 |

> `.ino`로 이름 바꾸고 업로드해도 정상 작동합니다.

---

## 🖼️ 미리보기

> 💡 직접 촬영한 사진이나 GIF를 여기에 넣어주세요 (e.g. `/docs/screenshot.jpg`)

---

## 🧪 향후 개선 아이디어

- PWM 모터 속도 제어
- 초음파 센서 거리 표시
- OTA 업그레이드
- BLE HID 키보드 모드

---

## 📜 라이선스

MIT License
