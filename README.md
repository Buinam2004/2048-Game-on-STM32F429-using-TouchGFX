# BÁO CÁO PROJECT
## GIỚI THIỆU

__Đề bài__: _Game 2048 trên kit STM32F429 Discovery sử dụng TouchGFX thiết kế giao diện và joystick để điều khiển._

__Sản phẩm:__
1. Game gồm 3 giao diện màn hình: Start, Main Game và Restart
2. Lưới 4x4 với các ô số (2, 4, 8,.., 2048)
3. Xử lý điều khiển ô số bằng joystick
4. Hiển thị điểm số và xử lý điều kiện thắng/thua
- Ảnh chụp minh họa:
<img width="1253" height="677" alt="Image" src="https://github.com/user-attachments/assets/2287a63f-8473-4d65-be5c-4980c430bdec" />

---
## TÁC GIẢ

- Tên nhóm: Chưa biết đặt tên gì
- Thành viên trong nhóm
  |STT|Họ tên|MSSV|Công việc|
  |--:|--|--|--|
  |1|Bùi Văn Nam|20225211|Xử lý logic game, xử lý điều khiển joystick|
  |2|Trần Thị Nhài|20225371|Thiết kế giao diện TouchGFX, viết báo cáo|
  |3|Phạm Thị Thùy Ngân|20225369|Hoàn thiện các chức năng, debug hệ thống|
---
## MÔI TRƯỜNG HOẠT ĐỘNG

- CPU / Dev Kit: **STM32F429I-DISCOVERY**
- Các module được sử dụng:
  - Bộ joystick analog 2 trục X, Y
  - TouchGFX framework
  - Màn hình LCD tích hợp sẵn trên STM32F429I-DISCO
- Hệ điều hành: FreeRTOS, quản lý đa nhiệm cho TouchGFX và đọc joystick.
---
## SƠ ĐỒ SCHEMATIC

_Cách nối dây, kết nối giữa các linh kiện_ 
|STM32F429|Joystick|
|--|--|
|PC3 (ADC1_IN13)|Trục X|
|PA5 (ADC2_IN5)|Trục Y|
|3V|VCC|
|GND|GND|



### TÍCH HỢP HỆ THỐNG

- __Phần cứng__:
  - **STM32F429I-DISCO**: đóng vai trò là board xử lý trung tâm, đọc giá trị ADC từ joystick thông qua ngắt polling, xử lý logic game 2048, hiển thị.
  - **Màn hình cảm ứng**: hiển thị toàn bộ giao diện người dùng (bao gồm màn hình game và score).
  - **Joystick**: điều khiển di chuyển các ô số trong game theo 4 hướng lên, xuống, trái, phải.

- __Phần mềm__:
  - **TouchGFX**: thiết kế giao diện Start Screen, Game Screen, Restart Screen, xử lý sự kiện chạm nút Start game và nút Restart.
  - **FreeRTOS**: xử lý đa nhiệm, cho phép chạy song song giữa TouchGFX và luồng đọc Joystick.
  - **STM32Cube HAL**: quản lý phần cứng (ADC cho joystick, LTDC cho màn hình, I2C cho touch controller).
  - **Custom Game Logic**: xử lý thuật toán di chuyển 2048, gộp ô, tính điểm.

### ĐẶC TẢ HÀM

- Giải thích một số hàm quan trọng: ý nghĩa của hàm, tham số vào, ra

  ```C
     /**
      *  Hàm task mặc định để đọc liên tục giá trị joystick trong FreeRTOS
      *  Dữ liệu lưu vào biến toàn cục JoytickX, JoytickY
      *  @param argument Tham số khởi tạo cho task (không sử dụng)
      */
     void StartDefaultTask(void *argument) {
     }
  ```
  ```cpp
     /**
      *  Hàm khởi tạo màn hình game 2048
      *  Khởi tạo ma trận 4x4, đặt hai ô ngẫu nhiên với giá trị 2 hoặc 4, và hiển thị
      */
     void Screen2View::setupScreen() {
     }
  ```
  ```cpp
     /**
      *  Hàm xử lý sự kiện tick
      *  Kiểm tra hướng di chuyển từ joystick và gọi hành động tương ứng
      */
     void Screen2View::handleTickEvent() {
     }
  ```
  ```cpp
     /**
      *  Hàm thực hiện di chuyển ô sang trái và thêm ô ngẫu nhiên
      */
     void Screen2View::Left() {
     }
  ```
  ```cpp
     /**
      *  Hàm thực hiện di chuyển ô sang phải và thêm ô ngẫu nhiên
      */
     void Screen2View::Right() {
     }
  ```
  ```cpp
     /**
      *  Hàm thực hiện di chuyển ô sang lên trên và thêm ô ngẫu nhiên
      */
     void Screen2View::Top() {
     }
  ```
  ```cpp
     /**
      *  Hàm thực hiện di chuyển ô sang xuống dưới và thêm ô ngẫu nhiên
      */
     void Screen2View::Bottom() {
     }
  ```
  ```cpp
     /**
      *  Hàm hiển thị board và điểm số (được cập nhật liên tục)
      */
     void Screen2View::Show() {
     }
  ```
  ```cpp
     /**
      *  Hàm làm mới game, đặt lại ma trận và điểm số
      */
     void Screen2View::refresh() {
     }
  ```
  ```cpp
     /**
      *  Hàm đẩy các ô về phía bên trái trong ma trận
      *  @param a[4][4] là ma trận 4x4 cần xử lý
      *  @return 1 nếu có di chuyển, 0 nếu không
      */
     int pushLeft(int a[4][4]) {
     }
  ```
  ```cpp
     /**
      *  Hàm sinh số ngẫu nhiên dựa vào seed
      *  @param seed Giá trị seed cho random
      *  @param min Giá trị nhỏ nhất
      *  @param max Giá trị lớn nhất
      *  @return giá trị ngẫu nhiên trong khoảng
      */
     int leftAction(int a[4][4], unsigned int seed) {
     }
  ```
  ```cpp
     /**
      *  Hàm xử lý hành động di chuyển trái, gộp ô giống nhau, thêm ô ngẫu nhiên và cập nhật điểm số
      *  @param a[4][4] là ma trận 4x4 cần xử lý
      *  @param seed Giá trị seed cho sinh số ngẫu nhiên
      *  @return core là điểm số tăng thêm từ việc gộp ô
      */
     int leftAction(int a[4][4], unsigned int seed) {
     }
  ```
  ```cpp
     /**
      *  Hàm đẩy các ô về phía bên phải trong ma trận
      *  @param a[4][4] là ma trận 4x4 cần xử lý
      *  @return 1 nếu có di chuyển, 0 nếu không
      */
     int pushRight(int a[4][4]) {
     }
  ```
  ```cpp
     /**
      *  Hàm xử lý hành động di chuyển phải, gộp ô giống nhau, thêm ô ngẫu nhiên và cập nhật điểm số
      *  @param a[4][4] là ma trận 4x4 cần xử lý
      *  @param seed Giá trị seed cho sinh số ngẫu nhiên
      *  @return core là điểm số tăng thêm từ việc gộp ô
      */
     int rightAction(int a[4][4], unsigned int seed) {
     }
  ```
  ```cpp
     /**
      *  Hàm đẩy các ô lên trên trong ma trận
      *  @param a[4][4] là ma trận 4x4 cần xử lý
      *  @return 1 nếu có di chuyển, 0 nếu không
      */
     int pushUp(int a[4][4]) {
     }
  ```
  ```cpp
     /**
      *  Hàm xử lý hành động di chuyển lên trên, gộp ô giống nhau, thêm ô ngẫu nhiên và cập nhật điểm số
      *  @param a[4][4] là ma trận 4x4 cần xử lý
      *  @param seed Giá trị seed cho sinh số ngẫu nhiên
      *  @return core là điểm số tăng thêm từ việc gộp ô
      */
     int upAction(int a[4][4], unsigned int seed) {
     }
  ```
  ```cpp
     /**
      *  Hàm đẩy các ô xuống dưới trong ma trận
      *  @param a[4][4] là ma trận 4x4 cần xử lý
      *  @return 1 nếu có di chuyển, 0 nếu không
      */
     int pushDown(int a[4][4]) {
     }
  ```
  ```cpp
     /**
      *  Hàm xử lý hành động di chuyển xuống dưới, gộp ô giống nhau, thêm ô ngẫu nhiên và cập nhật điểm số
      *  @param a[4][4] là ma trận 4x4 cần xử lý
      *  @param seed Giá trị seed cho sinh số ngẫu nhiên
      *  @return core là điểm số tăng thêm từ việc gộp ô
      */
     int downAction(int a[4][4], unsigned int seed) {
     }
  ```
  ```cpp
     /**
      *  Hàm kiểm tra kết thúc game
      *  @param a[4][4] là ma trận 4x4 cần xử lý
      *  @return 1 nếu game kết thúc (hết nước đi), 0 nếu game chưa kết thúc (còn nước đi)
      */
     int isFinish(int a[4][4]) {
     }
  ```
### KẾT QUẢ

- Video demo: https://drive.google.com/file/d/163mSohUCr-TOBkUZcJT80i0_B8OLViLZ/view?usp=sharing
  
