# 📷 ESP32-CAM FPV Bot (with Motor Control & MJPEG Streaming)
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


