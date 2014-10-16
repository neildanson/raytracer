namespace FSharpTracer

type Plane = 
   { PlaneNormal : Vector
     Offset : float
     Surface : Surface }
   interface SceneObject with
      
      member p.Intersects ray = 
         let denom = p.PlaneNormal.Dot(ray.Direction)
         if denom > 0.0 then None
         else 
            Some({ Ray = ray
                   Distance = (p.PlaneNormal.Dot(ray.Position) + p.Offset) / -denom
                   Object = p })
      
      member p.Normal _ = p.PlaneNormal
      member p.GetSurface() = p.Surface
