import Foundation

class Sphere : SceneObject {
    let position : Vector
    let radius : Double
    let surface : Surface
    init (position:Vector, radius:Double, surface:Surface) {
        self.position = position
        self.radius = radius
        self.surface = surface
    }
    
    func Intersects(ray: Ray) -> Optional<Intersection> {
        let eo = self.position.Subtract(ray.position)
        let v = eo.Dot(ray.direction)
        if v < 0.0 {
            return .None
        } else {
            let disc = pow(self.radius, 2.0) - (eo.Dot(eo) - pow(v, 2.0))
            if disc < 0.0 {
                return .None
            } else {
                let distance = v - sqrt(disc)
                return .Some(Intersection(ray: ray, distance: distance, object: self))
            }
            
        }
    }
    
    func Normal(pos: Vector) -> Vector {
        return pos.Subtract(self.position).Normalize()
    }
    
    func GetSurface() -> Surface {
        return self.surface
    }
}