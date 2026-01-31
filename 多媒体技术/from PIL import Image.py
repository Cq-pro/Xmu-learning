from PIL import Image

# 读取原始的 24 位真彩色 BMP 文件
original_image = Image.open("swift.bmp")

# 获取图像的宽度和高度
width, height = original_image.size

# 创建一个新的图像对象，用于存储灰度图像
gray_image = Image.new("L", (width, height))

# 遍历每个像素，并将 RGB 值转换为灰度值
for y in range(height):
    for x in range(width):
        # 获取当前像素的 RGB 值
        r, g, b = original_image.getpixel((x, y))
        
        # 根据转换公式计算灰度值
        gray = int(r * 0.299 + g * 0.587 + b * 0.114)
        
        # 在新的灰度图像中设置当前像素的值
        gray_image.putpixel((x, y), gray)

# 存储新生成的灰度图像
gray_image.save("gray.bmp")
