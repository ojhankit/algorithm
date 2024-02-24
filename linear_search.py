# this is a searching technique

list = []
num = int(input("enter the size of array\n"))
for i in range(int(num)):
    a = int(input("enter element\n"))
    list.append(a)
# display list
for i in list:
    print(i,end=" ")
#take input of target
target = int(input("\nenter target element\n"))
for i in list:
    if(i==target):
        print("target found")
        break
else:
    print("target not found")

