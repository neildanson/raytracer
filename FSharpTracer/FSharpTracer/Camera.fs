namespace FSharpTracer

type Camera = 
   { Position : Vector
     Forward : Vector
     Up : Vector
     Right : Vector }
   static member CreateCamera(position : Vector, lookAt : Vector) = 
      let forward = lookAt.Subtract(position).Normalize()
      
      let down = 
         { X = 0.0
           Y = -1.0
           Z = 0.0 }
      
      let right = forward.Cross(down).Normalize().Scale(1.5)
      let up = forward.Cross(right).Normalize().Scale(1.5)
      { Position = position
        Forward = forward
        Right = right
        Up = up }
