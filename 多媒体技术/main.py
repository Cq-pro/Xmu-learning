data = [1, 2, 3, 12, 20, 100, 6, 9, 12, 8, 8, 3]
average=0
largest=0
for i in range(12):
    average+=data[i]
    if(data[i]>largest):
        largest=data[i]
average/=12
print("平均值为：",average)
print("最大值为：",largest)
print("冒泡排序结果为：")
for i in range(12):
    for j in range(i,12):
        if(data[i]>data[j]):
            swap=data[i]
            data[i]=data[j]
            data[j]=swap
for i in range(12):
    print(data[i])
        

