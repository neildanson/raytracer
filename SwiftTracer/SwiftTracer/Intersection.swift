import Foundation

struct Intersection {
    let ray : Ray
    let distance : Double
    let object : SceneObject
    init(ray:Ray, distance:Double, object:SceneObject) {
        self.ray = ray
        self.distance = distance
        self.object = object
    }
}