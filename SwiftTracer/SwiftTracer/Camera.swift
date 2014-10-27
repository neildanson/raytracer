import Foundation

class Camera {
    let position, forward, up, right : Vector
    init(position:Vector, forward:Vector, up:Vector, right:Vector) {
        self.position = position
        self.forward = forward
        self.up = up
        self.right = right
    }
    
    class func CreateCamera(position: Vector, lookAt : Vector) -> Camera {
        let forward = lookAt.Subtract(position).Normalize()
        let down = Vector(x: 0.0, y: -1.0, z: 0.0)
        let right = forward.Cross(down).Normalize().Scale(1.5)
        let up = forward.Cross(right).Normalize().Scale(1.5)
        return Camera(position: position, forward: forward, up: up, right: right)
    }
}