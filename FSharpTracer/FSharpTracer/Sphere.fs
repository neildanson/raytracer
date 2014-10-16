namespace FSharpTracer

type Sphere = 
   { Position : Vector
     Radius : float
     Surface : Surface }
   interface SceneObject with
      
      member s.Intersects ray = 
         let eo = s.Position.Subtract(ray.Position)
         let v = eo.Dot ray.Direction
         if v < 0.0 then None
         else 
            let disc = (pown s.Radius 2) - (eo.Dot(eo) - pown v 2)
            if disc < 0.0 then None
            else 
               let distance = v - sqrt disc
               Some({ Ray = ray
                      Distance = distance
                      Object = s })
      
      member s.Normal pos = pos.Subtract(s.Position).Normalize()
      member s.GetSurface() = s.Surface
