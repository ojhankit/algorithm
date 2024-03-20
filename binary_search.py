
def binarySearch(list,target):
    low = 0
    high = len(list)-1
    
    while low<=high:
        mid = int((low+high)/2)
        if list[mid] == target:
            return mid
        elif list[mid] > target:
            high = mid-1
        else:
            low = mid+1
    return -1



list = []

num = int(input("enter the size: "))

for i in range(num):
    list.append(int(input("enter number")))

target = int(input("enter the target element"))

ans = int(binarySearch(list,target))
print(ans)