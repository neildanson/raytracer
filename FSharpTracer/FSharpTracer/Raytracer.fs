module FSharpTracer.Raytracer

let intersection (scene : Scene) ray = 
   scene.Objects |> Array.fold (fun i o -> 
                       let isect = o.Intersects ray
                       match isect, i with
                       | Some(i1), Some(i2) -> 
                          if i1.Distance < i2.Distance then isect
                          else i
                       | Some(isect), None -> Some(isect)
                       | None, i -> i) None

let testRay scene ray = 
   let intersection = intersection scene ray
   match intersection with
   | Some(i) -> i.Distance
   | None -> 0.0

let rec traceRay scene ray depth = 
   let black = 
      { R = 0.0
        G = 0.0
        B = 0.0 }
   
   let isect = intersection scene ray
   match isect with
   | Some(isect) -> shade scene isect depth
   | None -> black

and shade scene (intersection : Intersection) depth = 
   let pos = intersection.Ray.Direction.Scale(intersection.Distance).Add(intersection.Ray.Position)
   let normal = intersection.Object.Normal pos
   let dot = normal.Dot(intersection.Ray.Direction)
   let reflectDir = intersection.Ray.Direction.Subtract(normal.Scale (2.0 * dot))
   let natural = getNaturalColor scene intersection.Object pos normal reflectDir
   if depth < 5 then 
      let reflectPos = reflectDir.Scale(0.001).Add pos
      let reflectColor : Color = getReflectionColor scene intersection.Object reflectPos reflectDir depth
      reflectColor.Add natural
   else 
      { R = 0.5
        G = 0.5
        B = 0.5 }.Add(natural)

and getNaturalColor scene (sceneObject : SceneObject) position normal (rayDirection : Vector) = 
   let black = 
      { R = 0.0
        G = 0.0
        B = 0.0 }
   scene.Lights |> Array.fold (fun result light -> 
                      let lightDistance = light.Position.Subtract position
                      let livec = lightDistance.Normalize()
                      
                      let ray = 
                         { Position = position
                           Direction = livec }
                      
                      let isect = testRay scene ray
                      let isInShadow = (isect > lightDistance.Length() || isect = 0.0)
                      if isInShadow then 
                         let illum = livec.Dot normal
                         
                         let lcolor = 
                            if illum > 0.0 then light.Color.Scale illum
                            else black
                         
                         let normalizedRayDirection = rayDirection.Normalize()
                         let specular = livec.Dot normalizedRayDirection
                         
                         let scolor = 
                            if specular > 0.0 then 
                               light.Color.Scale(System.Math.Pow(specular, sceneObject.GetSurface().Roughness()))
                            else black
                         
                         let diffuseResult = sceneObject.GetSurface().Diffuse(position).Multiply(lcolor)
                         let specularResult = sceneObject.GetSurface().Specular(position).Multiply(scolor)
                         result.Add(diffuseResult).Add specularResult
                      else result) black

and getReflectionColor scene (sceneObject : SceneObject) pos rayDirection depth = 
   let ray = 
      { Position = pos
        Direction = rayDirection }
   (traceRay scene ray (depth + 1)).Scale(sceneObject.GetSurface().Reflect(pos))

let recenterX x halfWidth invWidth = 
   let x = float x
   (x - halfWidth) * invWidth

let recenterY y halfHeight invHeight = 
   let y = float y
   -(y - halfHeight) * invHeight

let getPoint x y halfWidth halfHeight invWidth invHeight (camera : Camera) = 
   let right = camera.Right.Scale(recenterX x halfWidth invWidth)
   let up = camera.Up.Scale(recenterY y halfHeight invHeight)
   right.Add(up).Add(camera.Forward).Normalize()

let Render width height scene = 
   let fWidth = float width
   let fHeight = float height
   let inverseAspectRatio = fHeight / fWidth
   let scaleWidth = fWidth * inverseAspectRatio
   let halfWidth = scaleWidth / 2.0
   let halfHeight = fHeight / 2.0
   let invWidth = 1.0 / (scaleWidth * 2.0)
   let invHeight = 1.0 / (fHeight * 2.0)
   [| for y = 0 to height - 1 do
         for x = 0 to width - 1 do
            let rayDir = getPoint x y halfWidth halfHeight invWidth invHeight scene.Camera
            
            let ray = 
               { Position = scene.Camera.Position
                 Direction = rayDir }
            yield (traceRay scene ray 0).ToColor() |]
