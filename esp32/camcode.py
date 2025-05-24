from ultralytics import YOLO
import cv2

# โหลดโมเดล 
model = YOLO("yolov8n.pt")

# แหล่ง RTSP
source = "rtsp://192.168.131.246:8554/mjpeg/1"    #เปลี่ยนแหล่งตามComputer/เน็ต

# รันโมเดลและวนลูปดูผลลัพธ์
for result in model(source, stream=True):  
    frame = result.plot()  # ใส่กรอบวัตถุในภาพ

    cv2.imshow("YOLO", frame)  #แสดงภาพ
    if cv2.waitKey(1) & 0xFF == ord('q'):  
        break

cv2.destroyAllWindows() 
