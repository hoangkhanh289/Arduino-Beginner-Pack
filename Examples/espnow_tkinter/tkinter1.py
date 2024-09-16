import tkinter as tk
import serial #pip install pyserial (lệnh tải thư viện)

ser = serial.Serial('COM3', 115200)#Thay thế băng cổng COM đang kết nối với esp_TX

def on_arrow_click(direction):#Các nút bên trái (mũi tên định hướng) sẽ gọi hàm này để giửi dữ liệu qua serial cho esp
    print(f"Left buttons: {direction}")
    ser.write((direction + '\r').encode())


def on_label_click(label):#Các nút bên phải (A,B,C,D) sẽ gọi hàm này để giửi dữ liệu qua serial cho esp
    print(f"Right buttons: {label}")
    ser.write((label + '\r').encode())

def create_gradient(canvas, color1, color2):
    width = canvas.winfo_width()
    height = canvas.winfo_height()
    
    for i in range(width):
        r1, g1, b1 = canvas.winfo_rgb(color1)
        r2, g2, b2 = canvas.winfo_rgb(color2)
        
        r = int(r1 + (r2 - r1) * i / width)
        g = int(g1 + (g2 - g1) * i / width)
        b = int(b1 + (b2 - b1) * i / width)
        
        color = f'#{r:04x}{g:04x}{b:04x}'
        canvas.create_line(i, 0, i, height, fill=color)

#Phần giao diện điều khiên bằng Tkinter
root = tk.Tk()
root.title("Esp32 now with Tkinter")
root.geometry("1200x600")  

canvas = tk.Canvas(root, width=1200, height=600)
canvas.pack(fill="both", expand=True)


root.update()
create_gradient(canvas, '#0000FF', '#FF00FF')


arrow_frame = tk.Frame(canvas, bg="")
arrow_frame.place(relx=0.25, rely=0.5, anchor='center')

button_font = ("Arial", 24)


up_button = tk.Button(arrow_frame, text="↑", command=lambda: on_arrow_click("Up"), width=5, height=2, font=button_font, bg="#00FFFF")
up_button.grid(row=0, column=1, padx=10, pady=10)

left_button = tk.Button(arrow_frame, text="←", command=lambda: on_arrow_click("Left"), width=5, height=2, font=button_font, bg="#00FFFF")
left_button.grid(row=1, column=0, padx=10, pady=10)

down_button = tk.Button(arrow_frame, text="↓", command=lambda: on_arrow_click("Down"), width=5, height=2, font=button_font, bg="#00FFFF")
down_button.grid(row=2, column=1, padx=10, pady=10)

right_button = tk.Button(arrow_frame, text="→", command=lambda: on_arrow_click("Right"), width=5, height=2, font=button_font, bg="#00FFFF")
right_button.grid(row=1, column=2, padx=10, pady=10)


label_frame = tk.Frame(canvas, bg="")
label_frame.place(relx=0.75, rely=0.5, anchor='center')


label_a = tk.Button(label_frame, text="A", width=5, height=2, font=button_font, command=lambda: on_label_click("A"), bg="#00FFFF")
label_a.grid(row=1, column=0, padx=20, pady=20)

label_b = tk.Button(label_frame, text="B", width=5, height=2, font=button_font, command=lambda: on_label_click("B"), bg="#00FFFF")
label_b.grid(row=0, column=1, padx=20, pady=20)

label_c = tk.Button(label_frame, text="C", width=5, height=2, font=button_font, command=lambda: on_label_click("C"), bg="#00FFFF")
label_c.grid(row=2, column=1, padx=20, pady=20)

label_d = tk.Button(label_frame, text="D", width=5, height=2, font=button_font, command=lambda: on_label_click("D"), bg="#00FFFF")
label_d.grid(row=1, column=2, padx=20, pady=20)

root.mainloop()
#Phần giao diện điều khiên bằng Tkinter
# Các bạn có thể cải tiến để phù hợp với dự án các nhân

