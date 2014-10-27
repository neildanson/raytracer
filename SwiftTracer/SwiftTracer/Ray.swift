import Foundation

struct Ray {
    let position, direction : Vector
    init(position:Vector, direction:Vector) {
        self.position = position
        self.direction = direction
    }
}