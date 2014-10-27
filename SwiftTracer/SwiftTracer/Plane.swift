import Foundation

class Plane : SceneObject {
    let planeNormal : Vector
    let offset : Double
    let surface : Surface
    init(planeNormal:Vector, offset:Double, surface:Surface) {
        self.planeNormal = planeNormal
        self.offset = offset
        self.surface = surface
    }
    
    func Intersects(ray: Ray) -> Optional<Intersection> {
        let denom = self.planeNormal.Dot(ray.direction)
        if denom > 0.0 {
            return .None
        } else {
            return .Some(Intersection(ray: ray, distance: (self.planeNormal.Dot(ray.position) + self.offset) / -denom, object: self))
        }
    }
    
    func Normal(_: Vector) -> Vector {
        return self.planeNormal
    }
    
    func GetSurface() -> Surface {
        return self.surface
    }
}