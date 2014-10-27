import Foundation
import Cocoa
import AppKit


class Scene {
    let objects : [SceneObject]
    let lights : [Light]
    let camera : Camera
    
    init(objects:[SceneObject], lights:[Light], camera : Camera) {
        self.objects = objects
        self.lights = lights
        self.camera = camera
    }
    
    func intersection(ray:Ray) -> Optional<Intersection> {
        var intersection2 : Optional<Intersection> = .None
        for object in self.objects {
            let isect = object.Intersects(ray)
            switch (isect, intersection2) {
            case (let .Some(i1), let .Some(i2)) where i1.distance < i2.distance : intersection2 = i1
            case (let .Some(_), .None) : intersection2 = isect
            case (_, let i) : intersection2 = i
            }
        }
        return intersection2
    }
    
    func testRay(ray:Ray) -> Double {
        let intersection = self.intersection(ray)
        switch intersection {
        case let .Some(intersection) : return intersection.distance
        case let .None : return 0.0
        }
    }
    
    func traceRay(ray:Ray, depth:Int) -> Color {
        let black = Color(r:0.0, g:0.0, b:0.0)
        let isect = self.intersection(ray)
        switch isect {
        case .Some(let isect) : return self.shade(isect, depth: depth)
        case .None : return black
        }
    }
    
    func shade(intersection:Intersection, depth:Int) -> Color {
        let pos = intersection.ray.direction.Scale(intersection.distance).Add(intersection.ray.position)
        let normal = intersection.object.Normal(pos)
        let dot = normal.Dot(intersection.ray.direction)
        let reflectDir = intersection.ray.direction.Subtract(normal.Scale (2.0 * dot))
        let natural = self.getNaturalColor(intersection.object, position: pos, normal: normal, rayDirection: reflectDir)
        if depth < 5 {
            let reflectPos = reflectDir.Scale(0.001).Add(pos)
            let reflectColor : Color = self.getReflectionColor (intersection.object, position: reflectPos, rayDirection: reflectDir, depth: depth)
            return reflectColor.Add(natural)
        } else {
            return Color(r:0.5,g:0.5,b:0.5).Add(natural)
        }
    }
    
    func getNaturalColor(sceneObject : SceneObject, position : Vector, normal : Vector, rayDirection : Vector) -> Color {
        let black = Color(r:0.0, g:0.0, b:0.0)
        var result = black
        for light in scene.lights {
            let lightDistance = light.position.Subtract(position)
            let livec = lightDistance.Normalize()
            let ray = Ray(position: position, direction: livec)
            let isect = scene.testRay(ray)
            let isInShadow = (isect > lightDistance.Length() || isect == 0.0)
            if isInShadow {
                let illum = livec.Dot(normal)
                
                var lcolor = black
                if illum > 0.0 {
                    lcolor = light.color.Scale(illum)
                }
                let normalizedRayDirection = rayDirection.Normalize()
                let specular = livec.Dot(normalizedRayDirection)
                var scolor = black
                if specular > 0.0 {
                    scolor = light.color.Scale(pow(specular, sceneObject.GetSurface().Roughness()))
                }
                
                let diffuseResult = sceneObject.GetSurface().Diffuse(position).Multiply(lcolor)
                let specularResult = sceneObject.GetSurface().Specular(position).Multiply(scolor)
                
                result = result.Add(diffuseResult).Add(specularResult)
            }
        }
        return result
    }
    
    func getReflectionColor(sceneObject : SceneObject, position : Vector, rayDirection : Vector, depth : Int) -> Color {
        let ray = Ray(position: position, direction: rayDirection)
        return (traceRay(ray, depth: depth + 1).Scale(sceneObject.GetSurface().Reflect(position)))
    }
    
    func recenterX (x:Int, halfWidth:Double, invWidth:Double) -> Double {
        let x = Double(x)
        return (x - halfWidth) * invWidth
    }
    
    func recenterY (y:Int, halfHeight:Double, invHeight:Double) -> Double {
        let y = Double(y)
        return -(y - halfHeight) * invHeight
    }
    
    func getPoint(x:Int, y:Int, halfWidth:Double, halfHeight:Double, invWidth:Double, invHeight:Double, camera : Camera) -> Vector {
        let right = camera.right.Scale(recenterX(x, halfWidth: halfWidth, invWidth: invWidth))
        let up = camera.up.Scale(recenterY(y, halfHeight: halfHeight, invHeight: invHeight))
        return right.Add(up).Add(camera.forward).Normalize()
    }
    
    func Render(width:Int, height:Int) -> [NSColor] {
        let fWidth = Double(width)
        let fHeight = Double(height)
        let inverseAspectRatio = fHeight / fWidth
        let scaleWidth = fWidth * inverseAspectRatio
        let halfWidth = scaleWidth / 2.0
        let halfHeight = fHeight / 2.0
        let invWidth = 1.0 / (scaleWidth * 2.0)
        let invHeight = 1.0 / (fHeight * 2.0)
        var result = Array<NSColor>(count:width * height, repeatedValue:NSColor())
        var basey = 0
        for y in 0 ... height - 1 {
            basey = y * width
            for x in  0 ... width - 1 {
                let rayDir = getPoint(x, y: y, halfWidth: halfWidth, halfHeight: halfHeight, invWidth: invWidth, invHeight: invHeight, camera: self.camera)
                let ray = Ray(position: self.camera.position, direction: rayDir)
                result[x + basey] = self.traceRay(ray, depth:0).ToColor()
            }
        }
        return result
    }
}