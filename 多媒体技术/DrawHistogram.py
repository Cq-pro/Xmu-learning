import matplotlib.pyplot as plt

# 读取文本文件
with open("alphatwice.txt", "r") as file:
    text = file.read()

# 统计字母出现次数
letter_count = {}
for char in text:
    if char.isalpha():
        char = char.lower()  # 统一转换为小写字母
        if char in letter_count:
            letter_count[char] += 1
        else:
            letter_count[char] = 1

# 选择出现次数最高的 10 个英文字母
top_letters = sorted(letter_count.items(), key=lambda x: x[1], reverse=True)[:10]
letters, counts = zip(*top_letters)

# 绘制直方图
plt.bar(letters, counts)
plt.xlabel('Letter')
plt.ylabel('Count')
plt.title('Top 10 Most Frequent Letters')
plt.savefig('letter_histogram.png')  # 保存直方图为图像文件
plt.show()
