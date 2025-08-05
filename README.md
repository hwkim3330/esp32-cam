# 🚗 ESP32-CAM WiFi FPV Robot Car with Live MJPEG Streaming + Web Control

📷 실시간 카메라 스트리밍과 Web 버튼으로 제어하는 2WD 로봇카 프로젝트입니다.  
ESP32-CAM 보드를 기반으로 **SoftAP + MJPEG 스트리밍 + WebSocket 모터 제어 + 플래시 버튼**을 구현합니다.

---

## 📸 기능 개요

- ✅ 실시간 MJPEG 스트리밍 (`/stream`)
- ✅ SoftAP Wi-Fi 자동 생성 (ESP-CAM 접속)
- ✅ WebSocket 기반 방향 제어 버튼 (앞, 뒤, 좌, 우, 정지)
- ✅ 플래시 On/Off 제어 버튼 추가 🔦
- ✅ 안정성 향상을 위한 프레임 지연/처리 최적화
- ✅ 초경량 해상도 (QQVGA) 사용으로 프레임 속도 확보
- ✅ 1초 단위 JPEG 캡처로 안정성 극대화

---

## 🛠️ 사용 부품

| 부품 | 설명 |
|------|------|
| ESP32-CAM (AI Thinker) | WiFi + OV2640 카메라 모듈 포함 |
| 2채널 L298N 또는 드라이버 모듈 | 모터 드라이버 |
| 2WD DC 모터 + 바퀴 | 로봇 구동 |
| 전원 5V (USB 또는 배터리) | ESP32 + 모터 전원 |
| 기타 | 점퍼선, 브레드보드 등 |

---

## ⚙️ 핀맵 정리 (📌 camera_pins.h 기준)

### 📷 카메라 핀맵 (AI Thinker 모델)
| 핀 이름 | 번호 |
|---------|------|
| PWDN    | 32   |
| RESET   | -1   |
| XCLK    | 0    |
| SIOD    | 26   |
| SIOC    | 27   |
| Y9~Y2   | 35, 34, 39, 36, 21, 19, 18, 5 |
| VSYNC   | 25   |
| HREF    | 23   |
| PCLK    | 22   |

### ⚙️ DC 모터 제어 핀

| 역할 | 핀 번호 |
|------|---------|
| 왼쪽 모터 IN1 | GPIO 12 |
| 왼쪽 모터 IN2 | GPIO 13 |
| 오른쪽 모터 IN1 | GPIO 14 |
| 오른쪽 모터 IN2 | GPIO 15 |

### 🔦 플래시 LED 핀

| 역할 | 핀 번호 |
|------|---------|
| 플래시 LED 제어 | GPIO 4 |

---

## 🌐 Wi-Fi 접속

1. ESP32-CAM을 업로드 후 전원 연결
2. 스마트폰/노트북에서 Wi-Fi `ESP_CAM` 접속 (비번: `12345678`)
3. 브라우저 열고 `http://192.168.4.1` 접속

---

## 🖥️ 웹 UI

- 🖱️ 버튼 클릭 시 WebSocket으로 제어 명령 전송
- 📷 `/stream` 경로로 MJPEG 영상 송출
- 🔦 플래시 LED On/Off 가능

---

## 🚀 업로드 방법

1. 아두이노 IDE 설정:
   - 보드: `ESP32 Wrover Module`
   - Partition Scheme: `Huge APP`
   - PSRAM: `Enabled`
2. 포트 선택 후 업로드 (IO0을 GND에 연결 → Flash mode)

---

## 🛡️ 문제 해결

- **플래시 LED 안 켜짐** → GPIO 4 연결 확인, 외부 전원 부족 여부 점검
- **리셋 반복 발생** → PSRAM 사용 불가 보드일 경우 `config.psram = false`
- **스트리밍 느림** → `jpeg_quality = 10~30` 등 적절한 조정

---

## 📂 파일 구조

```

esp32-cam/
├── bot.c              # 전체 제어 코드 (카메라 + 제어)
├── camera\_pins.h      # AI Thinker 핀 정의
└── README.md

```

---

## 📜 라이선스

MIT License


<img width="1795" height="1005" alt="image" src="https://github.com/user-attachments/assets/5b1e4a8e-a080-4bbf-95e2-bee034e380a1" />

> ESP32-CAM을 활용한 실시간 카메라 스트리밍 + WebSocket 기반 로봇 제어 프로젝트  
> WiFi SoftAP 기반으로 별도 공유기 없이 휴대폰으로 접속하여 영상 확인 및 방향 제어 가능!

---

## ✅ 주요 기능

- 📡 **WiFi SoftAP** 모드 자동 시작 (SSID: `ESP_CAM`, 비밀번호: `12345678`)
- 🎥 **MJPEG 기반 실시간 카메라 스트리밍** (`/stream`)
- 🕹 **WebSocket 기반 로봇 모터 제어** (forward / back / left / right / stop)
- 🧠 안정성 강화: 메모리 오버플로우 방지 (`stack_size`, `fb_count`, `vTaskDelay` 조정)

---

## 🛠 구성 부품

| 항목         | 사양 |
|--------------|------|
| 보드         | ESP32-CAM (AI Thinker 모듈) |
| 카메라       | OV2640 |
| 모터 드라이버 | L298N 또는 L9110S |
| 구동 모터     | 2채널 DC 모터 |
| 전원         | 리튬 배터리 or USB |

---

## 🌐 웹 인터페이스

<img width="515" height="670" alt="image" src="https://github.com/user-attachments/assets/c085e57a-252e-4e6c-be33-d0062e50696d" />

- `/` : HTML 기반 UI
- `/stream` : MJPEG 스트리밍
- WebSocket : `ws://192.168.4.1:81`

제어 버튼:
- ▲: 전진
- ▼: 후진
- ◀: 좌회전
- ▶: 우회전
- ■: 정지

---

## 🔧 회로 연결 예시 (모터 핀)

| 핀 이름      | GPIO |
|--------------|------|
| LEFT_IN1     | 12   |
| LEFT_IN2     | 13   |
| RIGHT_IN1    | 14   |
| RIGHT_IN2    | 15   |

카메라 핀은 `camera_pins.h` 기준 사용 (CAMERA_MODEL_AI_THINKER)

---

## ⚙ 설정 요약

```cpp
config.frame_size = FRAMESIZE_QQVGA; // 160x120
config.jpeg_quality = 10;            // 고화질
config.fb_count = 1;                 // 버퍼 1개로 안정화
````

웹소켓 명령 처리:

```cpp
forward → 전진
back    → 후진
left    → 좌회전
right   → 우회전
stop    → 정지
```

---

## 🚀 실행 방법

1. [ESP32 Arduino Core 설치](https://github.com/espressif/arduino-esp32)
2. [ESP32-CAM 보드 설정 방법 보기](https://randomnerdtutorials.com/)
3. `.ino` 파일 열고 업로드 (보드: ESP32 Wrover Module)
4. 휴대폰 WiFi에서 `ESP_CAM` 접속 후 브라우저에 `192.168.4.1` 입력

---

## 📂 폴더 구조 예시

```
esp32-cam/
├── esp32_cam_bot.ino     // 메인 코드
├── camera_pins.h         // 카메라 핀 매핑
├── docs/
│   └── ui_preview.png    // UI 스크린샷 (선택)
└── README.md             // 설명 파일
```

---

## 🧪 성능 팁

* PSRAM 있는 경우 `fb_count = 2`도 사용 가능 (더 부드러운 스트리밍)
* 영상이 너무 느리면 `frame_size = FRAMESIZE_96X96` 또는 `jpeg_quality = 15` 설정
* 전원 부족 시 모터 or 카메라 동작 불안정 → 외부 전원 추천

---

## 🧑‍💻 개발자

* GitHub: [@hwkim3330](https://github.com/hwkim3330)
* ChatGPT 기술협력

---

## 📜 라이선스

MIT License. 자유롭게 사용하고 수정하세요.


