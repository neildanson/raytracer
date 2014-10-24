#![feature(globs)]
//Compile with 
//rustc main.rs --opt-level 3
extern crate time;
use raytracer::vector::*;
use raytracer::color::*;
use raytracer::camera::*;
use raytracer::light::*;
use raytracer::scene_object::*;
use raytracer::sphere::*;
use raytracer::plane::*;
use raytracer::shiny::*;
use raytracer::checkerboard::*;
use raytracer::scene::*;
use std::io::File;
pub mod raytracer;

fn main() {
	let width = 1920;
	let height = 1080;
	let camera = create_camera(Vector{x: 3.0,y: 2.0,z: 4.0}, Vector{x: -1.0, y: 0.5, z: 0.0});
	let sphere1 = Sphere { position: Vector{x:0.0, y:1.0, z:0.0}, radius: 1.0, surface: &Shiny};
	let sphere2 = Sphere { position: Vector{x:-1.0, y:0.5, z:1.5}, radius: 0.5, surface: &Shiny} ;
	let plane = Plane { plane_normal: Vector{x:0.0, y:1.0, z:0.0}, offset: 0.0, surface: &Checkerboard};
	let objects : Vec<&SceneObject> = vec! [
		(&sphere1 as &SceneObject), 
		(&sphere2 as &SceneObject), 
		(&plane as &SceneObject)];
	let lights : Vec<Light> = vec! [
		Light{position:Vector {x:-2.0, y:2.5,z:0.0}, color:Color{r:0.49, g:0.07, b:0.07}},
		Light{position:Vector {x:1.5, y:2.5,z:1.5}, color:Color{r:0.07, g:0.07, b:0.49}},
		Light{position:Vector {x:1.5, y:2.5,z:-1.5}, color:Color{r:0.07, g:0.49, b:0.07}},
		Light{position:Vector {x:0.0, y:3.5,z:0.0}, color:Color{r:0.21, g:0.21, b:0.21}},
	];
	let scene = Scene {camera: camera, objects:objects, lights:lights};

	let start = time::get_time();
	let result = scene.render(width, height);
	let end = time::get_time();
	let duration = end - start;
	println!("{}", duration);

	let mut file = File::create(&Path::new("Rust.tga"));
	file.write_i8(0 as i8).ok(); //identsize
	file.write_i8(0 as i8).ok(); //colormaptype
	file.write_i8(2 as i8).ok(); //datatypecode
	file.write_le_i16(0 as i16).ok(); //colormapStart
	file.write_le_i16(0 as i16).ok(); //colormapLength
	file.write_i8(0 as i8).ok(); //colormapbits
	file.write_le_i16(0 as i16).ok(); //xstart
	file.write_le_i16(0 as i16).ok(); //ystart
	file.write_le_i16(width as i16).ok(); //width
	file.write_le_i16(height as i16).ok(); //height
	file.write_i8(32 as i8).ok(); //bits
	file.write_i8(8 as i8).ok(); //descriptor
	for color in result.iter() {
		file.write_le_i32(*color as i32).ok();
	}
	file.flush().ok();
}