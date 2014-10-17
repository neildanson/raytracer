open FSharpTracer
open System

[<EntryPoint>]
let main argv = 
   let camera = 
      Camera.CreateCamera({ X = 3.0
                            Y = 2.0
                            Z = 4.0 }, 
                          { X = -1.0
                            Y = 0.5
                            Z = 0.0 })
   
   let objects : SceneObject [] = 
      [| { Position = 
              { X = 0.0
                Y = 1.0
                Z = 0.0 }
           Radius = 1.0
           Surface = Shiny() }
         { Position = 
              { X = -1.0
                Y = 0.5
                Z = 1.5 }
           Radius = 0.5
           Surface = Shiny() }
         { PlaneNormal = 
              { X = 0.0
                Y = 1.0
                Z = 0.0 }
           Offset = 0.0
           Surface = Checkerboard() } |]
   
   let lights = 
      [| { Position = 
              { X = -2.0
                Y = 2.5
                Z = 0.0 }
           Color = 
              { R = 0.49
                G = 0.07
                B = 0.07 } } 
         { Position = 
              { X = 1.5
                Y = 2.5
                Z = 1.5 }
           Color = 
              { R = 0.07
                G = 0.07
                B = 0.49 } }
         { Position = 
              { X = 1.5
                Y = 2.5
                Z = -1.5 }
           Color = 
              { R = 0.07
                G = 0.49
                B = 0.07 } }
         { Position = 
              { X = 0.0
                Y = 3.5
                Z = 0.0 }
           Color = 
              { R = 0.21
                G = 0.21
                B = 0.21 } }|]
   let scene = { Camera = camera
                 Objects = objects
                 Lights = lights}
   
   let start = DateTime.Now
   let width, height = 1920, 1080
   let result = Raytracer.Render width height scene
   let endTime = DateTime.Now
   printf "%A" (endTime - start)

   let bm = new System.Drawing.Bitmap(width, height)
   for i = 0 to result.Length-1 do
      let x = i % width
      let y = i / width
      bm.SetPixel(x,y, result.[i])

   bm.Save("FSharp.png", System.Drawing.Imaging.ImageFormat.Png)
   Console.ReadLine() |> ignore
   0 // return an integer exit code
