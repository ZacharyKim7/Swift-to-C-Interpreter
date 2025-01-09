var array = [4,3,2,1,5,9,7,0,6,8]
let n = array.count

print("Unsorted array is: ")
var k = 0
while k < n {
    print(array[k])
    k = k + 1
}
print()
        
for i in 1...n - 1 {
    var j = i
    while j > 0 && array[j] < array[j - 1] {
        let temp = array[j]
        array[j] = array[j - 1]
        array[j - 1] = temp
        j = j - 1
    }
}

print("Sorted array is: ")
var m = 0
while m < n {
    print(array[m])
    m = m + 1
}
print()
