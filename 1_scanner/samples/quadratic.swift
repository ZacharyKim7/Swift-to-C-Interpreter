let a = 1.0
let b = -3.0
let c = 2.0
print("a: ")
print(a)
print("b: ")
print(b)
print("c: ")
print(c)

let discriminant = b * b - 4 * a * c
if discriminant > 0 {
    let answer1 = (-b + discriminant.squareRoot()) / (2 * a)
    let answer2 = (-b - discriminant.squareRoot()) / (2 * a)
    print("Root 1: ")
    print(answer1)
    print("Root 2: ")
    print(answer2)
} else if discriminant == 0 {
    let root = -b / (2 * a)
    print("One root: ")
    print(root)
} else {
    print("No real roots.")
}
