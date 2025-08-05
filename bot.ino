// ESP32-CAM FPV 로봇 최적화 전체 코드
#include <WiFi.h>
#include <esp_camera.h>
#include <WebSocketsServer.h>
#include <esp_http_server.h>

// CAMERA_MODEL_AI_THINKER 설정
#define CAMERA_MODEL_AI_THINKER
#include "camera_pins.h"

// 모터 제어 핀
#define MOTOR_L1_PIN 12
#define MOTOR_L2_PIN 13
#define MOTOR_R1_PIN 14
#define MOTOR_R2_PIN 15

// 플래시 LED 핀
#define FLASH_LED_PIN 4

// WiFi SoftAP 설정
const char* ssid = "ESP_CAM";
const char* password = "12345678";

WebSocketsServer webSocket = WebSocketsServer(81);

// 스트리밍 핸들러
static esp_err_t stream_handler(httpd_req_t *req) {
  camera_fb_t *fb = NULL;
  esp_err_t res = ESP_OK;
  int frame_id = 0;

  res = httpd_resp_set_type(req, "multipart/x-mixed-replace; boundary=frame");
  if (res != ESP_OK) return res;

  while (true) {
    fb = esp_camera_fb_get();
    if (!fb) continue;

    char part[64];
    size_t hlen = snprintf(part, sizeof(part),
      "--frame\r\nContent-Type: image/jpeg\r\nContent-Length: %u\r\n\r\n", fb->len);

    res  = httpd_resp_send_chunk(req, part, hlen);
    res |= httpd_resp_send_chunk(req, (const char *)fb->buf, fb->len);
    res |= httpd_resp_send_chunk(req, "\r\n", 2);

    esp_camera_fb_return(fb);
    if (res != ESP_OK) break;

    vTaskDelay(100 / portTICK_PERIOD_MS);  // 약 10fps
  }
  return res;
}

// HTML 페이지 핸들러
static esp_err_t index_handler(httpd_req_t *req) {
  const char* html = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta charset="utf-8">
  <title>ESP32-CAM Bot</title>
  <style>
    body { background: #111; color: white; font-family: sans-serif; text-align: center; }
    img { width: 100%; max-width: 640px; border: 2px solid #444; }
    button { padding: 10px 20px; margin: 5px; font-size: 18px; }
  </style>
</head>
<body>
  <h2>📸 ESP32-CAM Live View</h2>
  <img src="/stream" id="cam" onload="imgOK()" onerror="imgErr()">
  <p id="status">⏳ Loading...</p>
  <div>
    <button onclick="sendCmd('forward')">⬆️</button>
    <br>
    <button onclick="sendCmd('left')">⬅️</button>
    <button onclick="sendCmd('stop')">⏹️</button>
    <button onclick="sendCmd('right')">➡️</button>
    <br>
    <button onclick="sendCmd('back')">⬇️</button>
    <br>
    <button onclick="sendCmd('flash')">💡 Flash</button>
  </div>
  <script>
    const socket = new WebSocket('ws://' + location.hostname + ':81');
    function sendCmd(cmd) {
      if (socket.readyState === WebSocket.OPEN) socket.send(cmd);
    }
    function imgOK() {
      document.getElementById("status").innerText = "✅ Camera OK";
    }
    function imgErr() {
      document.getElementById("status").innerText = "❌ Camera Lost";
    }
  </script>
</body>
</html>
  )rawliteral";
  httpd_resp_set_type(req, "text/html");
  return httpd_resp_send(req, html, strlen(html));
}

void startWebServer() {
  httpd_config_t config = HTTPD_DEFAULT_CONFIG();
  config.server_port = 80;
  httpd_handle_t server = NULL;

  httpd_uri_t index_uri = { .uri = "/", .method = HTTP_GET, .handler = index_handler };
  httpd_uri_t stream_uri = { .uri = "/stream", .method = HTTP_GET, .handler = stream_handler };

  if (httpd_start(&server, &config) == ESP_OK) {
    httpd_register_uri_handler(server, &index_uri);
    httpd_register_uri_handler(server, &stream_uri);
  }
}

void handleWebSocket(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  if (type != WStype_TEXT) return;
  String msg = String((char*)payload);
  Serial.println("[WS] " + msg);

  if (msg == "forward") {
    digitalWrite(MOTOR_L1_PIN, HIGH); digitalWrite(MOTOR_L2_PIN, LOW);
    digitalWrite(MOTOR_R1_PIN, HIGH); digitalWrite(MOTOR_R2_PIN, LOW);
  } else if (msg == "back") {
    digitalWrite(MOTOR_L1_PIN, LOW); digitalWrite(MOTOR_L2_PIN, HIGH);
    digitalWrite(MOTOR_R1_PIN, LOW); digitalWrite(MOTOR_R2_PIN, HIGH);
  } else if (msg == "left") {
    digitalWrite(MOTOR_L1_PIN, LOW); digitalWrite(MOTOR_L2_PIN, HIGH);
    digitalWrite(MOTOR_R1_PIN, HIGH); digitalWrite(MOTOR_R2_PIN, LOW);
  } else if (msg == "right") {
    digitalWrite(MOTOR_L1_PIN, HIGH); digitalWrite(MOTOR_L2_PIN, LOW);
    digitalWrite(MOTOR_R1_PIN, LOW); digitalWrite(MOTOR_R2_PIN, HIGH);
  } else if (msg == "stop") {
    digitalWrite(MOTOR_L1_PIN, LOW); digitalWrite(MOTOR_L2_PIN, LOW);
    digitalWrite(MOTOR_R1_PIN, LOW); digitalWrite(MOTOR_R2_PIN, LOW);
  } else if (msg == "flash") {
    digitalWrite(FLASH_LED_PIN, !digitalRead(FLASH_LED_PIN));
  }
}

void startCamera() {
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer   = LEDC_TIMER_0;
  config.pin_d0       = Y2_GPIO_NUM;
  config.pin_d1       = Y3_GPIO_NUM;
  config.pin_d2       = Y4_GPIO_NUM;
  config.pin_d3       = Y5_GPIO_NUM;
  config.pin_d4       = Y6_GPIO_NUM;
  config.pin_d5       = Y7_GPIO_NUM;
  config.pin_d6       = Y8_GPIO_NUM;
  config.pin_d7       = Y9_GPIO_NUM;
  config.pin_xclk     = XCLK_GPIO_NUM;
  config.pin_pclk     = PCLK_GPIO_NUM;
  config.pin_vsync    = VSYNC_GPIO_NUM;
  config.pin_href     = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn     = PWDN_GPIO_NUM;
  config.pin_reset    = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;

  if(psramFound()) {
    config.frame_size = FRAMESIZE_QQVGA;
    config.jpeg_quality = 20;
    config.fb_count = 2;
  } else {
    config.frame_size = FRAMESIZE_QQVGA;
    config.jpeg_quality = 20;
    config.fb_count = 1;
  }

  if (esp_camera_init(&config) != ESP_OK) {
    Serial.println("❌ Camera init failed");
    return;
  }
  Serial.println("✅ Camera initialized");
}

void setup() {
  Serial.begin(115200);
  WiFi.softAP(ssid, password);
  Serial.print("AP IP: "); Serial.println(WiFi.softAPIP());

  pinMode(MOTOR_L1_PIN, OUTPUT);
  pinMode(MOTOR_L2_PIN, OUTPUT);
  pinMode(MOTOR_R1_PIN, OUTPUT);
  pinMode(MOTOR_R2_PIN, OUTPUT);
  pinMode(FLASH_LED_PIN, OUTPUT);
  digitalWrite(FLASH_LED_PIN, LOW);

  startCamera();
  startWebServer();
  webSocket.begin();
  webSocket.onEvent(handleWebSocket);
}

void loop() {
  webSocket.loop();
}
