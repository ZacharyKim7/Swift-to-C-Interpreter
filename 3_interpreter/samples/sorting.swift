var array = [0, 4, 7, 8, 5, 3, 9, 1, 6, 2]
let len = array.count
for _ in 0...len {
    for value in 1...len - 1 {
        let index = value - 1
        if array[index] > array[value] {
            let largerValue = array[index]
            array[index] = array[value]
            array[value] = largerValue
        }
    }
}
for j in 0...len - 1 {
    print(array[j])
}
