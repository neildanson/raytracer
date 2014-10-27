import Foundation
import Cocoa
import AppKit

let (width, height) = (1920, 1080)

let camera = Camera.CreateCamera(Vector(x:3.0,y:2.0,z:4.0), lookAt: Vector(x: -1.0, y: 0.5, z: 0.0))

let objects : [SceneObject] = [ Sphere(position:Vector(x: 0.0, y: 1.0, z: 0.0), radius:1.0, surface:Shiny()),
                                Sphere(position:Vector(x: -1.0, y: 0.5, z: 1.5), radius:0.5, surface:Shiny()),
                                Plane(planeNormal:Vector(x: 0.0, y: 1.0, z: 0.0), offset:0.0, surface:Checkerboard())]
let lights = [ Light(position: Vector(x: -2.0, y: 2.5, z: 0.0), color: Color(r: 0.49, g: 0.07, b: 0.07)),
               Light(position: Vector(x: 1.5, y: 2.5, z: 1.5), color: Color(r: 0.07, g: 0.07, b: 0.49)),
               Light(position: Vector(x: 1.5, y: 2.5, z: -1.5), color: Color(r: 0.07, g: 0.49, b: 0.07)),
               Light(position: Vector(x: 0.0, y: 3.5, z: 0.0), color: Color(r: 0.21, g: 0.21, b: 0.21))]

let scene = Scene(objects: objects, lights: lights, camera: camera)
let start = NSDate()
var result = scene.Render(width, height:height)
let end = NSDate()
let duration = end.timeIntervalSinceDate(start)
print(duration)

let representation = NSBitmapImageRep(bitmapDataPlanes: nil, pixelsWide: width, pixelsHigh: height, bitsPerSample: 8,
                                    samplesPerPixel: 3, hasAlpha: false, isPlanar: false,
                                    colorSpaceName: NSCalibratedRGBColorSpace,
                                    bytesPerRow: width * 3, bitsPerPixel: 24)

for y in 0...height-1 {
    for x in 0...width-1 {
        let colorIndex = x + (y * width)
        let color = result[colorIndex]
        representation?.setColor(color, atX: x, y: y)
        
    }
}

let emptyDict : [NSObject: AnyObject] = Dictionary()
let pngData = representation!.representationUsingType(NSBitmapImageFileType.NSPNGFileType, properties: emptyDict)
pngData?.writeToFile("Swift.png", atomically: true)
