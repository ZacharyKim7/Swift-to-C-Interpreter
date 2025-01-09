let a = 1.0
let b = -3.0
let c = 2.0
print("a:")
print(a)
print("b:")
print(b)
print("c:")
print(c)
let discriminant = b * b - 4 * a * c
if discriminant < 0 {
    print("No real roots.")
} else if discriminant == 0 {
    let divisor = 2 * a
    let root = -b / divisor
    print("One root:")
    print(root)
} else {
    let part1 = -b + discriminant.squareRoot()
    let answer1 = part1 / 2 / a
    let part2 = -b - discriminant.squareRoot()
    let answer2 = part2 / 2 / a
    print("Root 1:")
    print(answer1)
    print("Root 2:")
    print(answer2)
}
