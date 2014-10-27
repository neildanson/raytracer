import Foundation
import Cocoa
import AppKit

struct Color {
    let r,g,b: Double;
    init(r:Double, g:Double, b:Double) {
        self.r = r;
        self.g = g;
        self.b = b;
    }
    
    func Add(c:Color) -> Color {
        return Color(r:self.r + c.r, g:self.g + c.g, b:self.b + c.b)
    }
    
    func Subtract(c:Color) -> Color {
        return Color(r:self.r - c.r, g:self.g - c.g, b:self.b - c.b)
    }
    
    func Scale(s:Double) -> Color {
        return Color(r:self.r * s, g:self.g * s, b:self.b * s)
    }
    
    func Multiply(c:Color) -> Color {
        return Color(r:self.r * c.r, g:self.g * c.g, b:self.b * c.b)
    }
    
    func ToColor() -> NSColor {
        let legalize =  { (var i : Double) -> CGFloat in
            if i > 1.0 { return CGFloat(1.0) }
            else { return CGFloat(i) }
        };
        
        let r = legalize(self.r)
        let g = legalize(self.g)
        let b = legalize(self.b)
        let color = NSColor(calibratedRed: r, green: g, blue: b, alpha: 1.0)

        return color;
    }
}