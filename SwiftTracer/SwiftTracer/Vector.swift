import Foundation

struct Vector {
    let x,y,z: Double;
    init(x:Double, y:Double, z:Double) {
        self.x = x;
        self.y = y;
        self.z = z;
    }

    func Length() -> Double {
        return sqrt(self.Dot(self))
    }
    
    func Dot(v:Vector) -> Double {
        return (self.x * v.x) + (self.y * v.y) + (self.z * v.z)
    }
    
    func Cross(v:Vector) -> Vector {
        return Vector(x: (self.y*v.z) - (self.z*v.y),
                      y: (self.z*v.x) - (self.x*v.z),
                      z: (self.x*v.y) - (self.y*v.x))
    }
    
    func Add(v:Vector) -> Vector {
        return Vector(x:self.x + v.x, y:self.y + v.y, z:self.z + v.z)
    }
    
    func Subtract(v:Vector) -> Vector {
        return Vector(x:self.x - v.x, y:self.y - v.y, z:self.z - v.z)
    }
    
    func Scale(s:Double) -> Vector {
        return Vector(x:self.x * s, y:self.y * s, z:self.z * s)
    }
    
    func Normalize() -> Vector {
        let mag = self.Length()
        if mag == 0 {
            return self.Scale(Double.infinity)
        }
        else {
            return self.Scale(1.0 / mag)
        }
    }
}