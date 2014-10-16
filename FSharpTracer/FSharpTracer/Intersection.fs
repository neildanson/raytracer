namespace FSharpTracer

type SceneObject = 
   abstract Intersects : Ray -> Intersection option
   abstract Normal : Vector -> Vector
   abstract GetSurface : unit -> Surface

and Intersection = 
   { Ray : Ray
     Distance : float
     Object : SceneObject }
