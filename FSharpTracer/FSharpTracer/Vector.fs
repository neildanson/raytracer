namespace FSharpTracer

open System

type Vector = 
   { X : float
     Y : float
     Z : float }
   member v.Dot(v1 : Vector) = (v.X * v1.X) + (v.Y * v1.Y) + (v.Z * v1.Z)
   member v.Length() = sqrt (v.Dot v)
   
   member v.Cross(v1 : Vector) = 
      { X = v.Y * v1.Z - v.Z * v1.Y
        Y = v.Z * v1.X - v.X * v1.Z
        Z = v.X * v1.Y - v.Y * v1.X }
   
   member v.Add(v1 : Vector) = 
      { X = v.X + v1.X
        Y = v.Y + v1.Y
        Z = v.Z + v1.Z }
   
   member v.Subtract(v1 : Vector) = 
      { X = v.X - v1.X
        Y = v.Y - v1.Y
        Z = v.Z - v1.Z }
   
   member v.Scale s = 
      { X = v.X * s
        Y = v.Y * s
        Z = v.Z * s }
   
   member v.Normalize() = 
      let mag = v.Length()
      v.Scale(if mag = 0.0 then Double.PositiveInfinity
              else 1.0 / mag)
