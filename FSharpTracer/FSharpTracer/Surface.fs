namespace FSharpTracer

type Surface = 
   abstract Roughness : unit -> float
   abstract Diffuse : Vector -> Color
   abstract Specular : Vector -> Color
   abstract Reflect : Vector -> float

type Shiny() = 
   interface Surface with
      member s.Roughness() = 50.0
      
      member s.Diffuse _ = 
         { R = 1.0
           G = 1.0
           B = 1.0 }
      
      member s.Specular _ = 
         { R = 0.5
           G = 0.5
           B = 0.5 }
      
      member s.Reflect _ = 0.3

type Checkerboard() = 
   interface Surface with
      member s.Roughness() = 150.0
      
      member s.Diffuse v = 
         if (floor v.X + floor v.Z) % 2.0 <> 0.0 then
            { R = 1.0
              G = 1.0
              B = 1.0 }
         else
            { R = 0.0
              G = 0.0
              B = 0.0 }
      
      member s.Specular _ = 
         { R = 1.0
           G = 1.0
           B = 1.0 }
      
      member s.Reflect v = 
         if (floor v.X + floor v.Z) % 2.0 <> 0.0 then
            1.0
         else
            0.7
      