# 👏 Hệ Thống Nhận Diện Tiếng Vỗ Tay Điều Khiển Đèn Bằng ESP32

Dự án này sử dụng cảm biến âm thanh kết hợp với mô hình AI được huấn luyện từ Edge Impulse để nhận diện tiếng vỗ tay. Sau khi nhận diện, ESP32 sẽ điều khiển LED theo các hành động:

- 👏 Vỗ tay 1 lần: Bật đèn
- 👏👏 Vỗ tay 2 lần: Tắt đèn
- 👏👏👏 Vỗ tay 3 lần: Nhấp nháy đèn

---

## 🔧 Phần cứng sử dụng

| Linh kiện           | Mô tả                             |
|---------------------|-----------------------------------|
| ESP32 Dev Module    | Vi điều khiển chính                |
| Cảm biến âm thanh   | Có ký hiệu D0, A0, G, +           |
| LED                 | Đèn điều khiển                    |
| Điện trở 220Ω       | Bảo vệ LED                        |
| Breadboard + Dây    | Kết nối mạch                      |

---

## 📐 Sơ đồ kết nối phần cứng

```
ESP32      --> Cảm biến âm thanh / LED
D23        --> Dây tín hiệu LED (qua điện trở 220Ω đến chân dài)
GND        --> G (GND) của cảm biến âm thanh và chân ngắn LED
3V3        --> + (VCC) của cảm biến âm thanh
A0 hoặc D0 --> Không sử dụng nếu dùng mô hình AI
```

📸 *Ảnh sơ đồ phần cứng:*
![image](https://github.com/user-attachments/assets/9b0d8156-516a-4711-83b9-46f043ea55ed)

![Sơ đồ phần cứng]

---

## 🧠 Mô hình AI - Edge Impulse

Mô hình AI được huấn luyện trên nền tảng [Edge Impulse](https://edgeimpulse.com/) với các lớp:

- `votay_1lan`
- `votay_2lan`
- `votay_3lan`
- `khac` (không vỗ)

Sau khi huấn luyện, mô hình được xuất ra định dạng `Arduino Library` và tích hợp vào chương trình ESP32.

---

## 🧾 Hoạt động hệ thống

1. Người dùng vỗ tay
2. Cảm biến thu âm thanh và truyền vào ESP32
3. ESP32 xử lý bằng mô hình AI
4. LED phản hồi tương ứng theo số lần vỗ tay

---

## 💡 Gợi ý mở rộng

- Kết nối thêm đèn thông minh hoặc điều khiển thiết bị thật
- Hiển thị kết quả qua Web hoặc Bluetooth
- Tích hợp thêm cảm biến chuyển động để nhận diện người

---

## 📁 Cấu trúc thư mục

```
project/
├── cambienamthanh.ino         # File chính ESP32
├── images/
│   └── image1.png
├── README.md
```

---

## 👨‍💻 Tác giả

- **Họ tên**: Nguyễn Đăng Chính
