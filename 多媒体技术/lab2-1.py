import cv2
import numpy as np

# 读取四张猫的图像
cat1 = cv2.imread('cat1.jpg')
cat2 = cv2.imread('cat2.jpg')
cat3 = cv2.imread('cat3.jpg')
cat4 = cv2.imread('cat4.jpg')


# 拼接四张图 已经预先处理为同一尺寸
height, width, _ = cat1.shape
cats = np.zeros((2 * height, 2 * width, 3), dtype=np.uint8)
cats[0:height, 0:width] = cat1
cats[0:height, width:2*width] = cat2
cats[height:2*height, 0:width] = cat3
cats[height:2*height, width:2*width] = cat4

# 保存拼贴画
cv2.imwrite('cats.jpg', cats)

print("拼贴画已保存为 cats.jpg")
