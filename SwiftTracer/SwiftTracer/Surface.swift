import Foundation

protocol Surface {
    func Roughness() -> Double
    func Diffuse(Vector) -> Color
    func Specular(Vector) -> Color
    func Reflect(Vector) -> Double
}

class Shiny : Surface {
    func Roughness() -> Double {
        return 50.0
    }
    
    func Diffuse(_: Vector) -> Color {
        return Color(r:1.0, g:1.0,b:1.0)
    }
    
    func Specular(_: Vector) -> Color {
        return Color(r:0.5,g:0.5,b:0.5)
    }
    func Reflect(_: Vector) -> Double {
        return 0.3
    }
}

class Checkerboard : Surface {
    func Roughness() -> Double {
        return 150.0
    }
    
    func Diffuse(v: Vector) -> Color {
        if (floor(v.x) + floor(v.z)) % 2 != 0.0 {
            return Color(r:1.0, g:1.0,b:1.0)
        } else {
            return Color(r:0.0, g:0.0,b:0.0)
        }
    }
    
    func Specular(_: Vector) -> Color {
        return Color(r:1.0, g:1.0,b:1.0)
    }
    func Reflect(v: Vector) -> Double {
        if (floor(v.x) + floor(v.z)) % 2 != 0.0 {
            return 1.0
        } else {
            return 0.7
        }
    }
}