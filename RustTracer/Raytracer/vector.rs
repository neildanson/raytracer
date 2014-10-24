pub struct Vector {
    pub x: f64,
    pub y: f64,
    pub z: f64
}

impl Vector {
	pub fn dot(&self, v:Vector) -> f64 {
		(self.x * v.x) + (self.y * v.y) + (self.z * v.z)
	} 

	pub fn length(&self) -> f64 {
		self.dot(*self).sqrt()
	}

	pub fn cross(&self, v:Vector) -> Vector {
		Vector {x: self.y * v.z - self.z * v.y,
				y: self.z * v.x - self.x * v.z,
				z: self.x * v.y - self.y * v.x}
	}

	pub fn add(&self, v:Vector) -> Vector {
		Vector {x: self.x + v.x, y: self.y + v.y, z: self.z + v.z }
	}

	pub fn subtract(&self, v:Vector) -> Vector {
		Vector {x: self.x - v.x, y: self.y - v.y, z: self.z - v.z }
	}

	pub fn scale(&self, s:f64) -> Vector {
		Vector {x: self.x * s, y: self.y * s, z: self.z * s }
	}

	pub fn normalize(&self) -> Vector {
		let mag = self.length();
		self.scale(if mag == 0.0 { Float::infinity() } else { 1.0 / mag })
	}
}