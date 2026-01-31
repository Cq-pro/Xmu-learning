from PIL import Image

# 读取原始的 8 位伪彩色 BMP 文件
original_image = Image.open("swift.bmp")

# 将伪彩色图像转换为真彩色图像
truecolor_image = original_image.convert("RGB")

# 存储新生成的真彩色 BMP 文件
truecolor_image.save("truecolor.bmp")
