import Foundation

protocol SceneObject {
    func Intersects(Ray) -> Optional<Intersection>
    func Normal(Vector) -> Vector
    func GetSurface() -> Surface
}