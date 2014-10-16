namespace FSharpTracer

type DrawingColor = System.Drawing.Color

type Color = 
   { R : float
     G : float
     B : float }
   
   member c.Add(c1 : Color) = 
      { R = c.R + c1.R
        G = c.G + c1.G
        B = c.B + c1.B }
   
   member c.Subtract(c1 : Color) = 
      { R = c.R - c1.R
        G = c.G - c1.G
        B = c.B - c1.B }
   
   member c.Scale s = 
      { R = c.R * s
        G = c.G * s
        B = c.B * s }
   
   member c.Multiply(c1 : Color) = 
      { R = c.R * c1.R
        G = c.G * c1.G
        B = c.B * c1.B }
   
   member c.ToColor() = 
      let legalize i = 
         if i > 1.0 then 255
         else int (i * 255.0)
      
      let r, g, b = legalize c.R, legalize c.G, legalize c.B
      DrawingColor.FromArgb(r, g, b)
