pub struct Color {
	pub r: f64,
	pub g: f64,
	pub b: f64
}

impl Color {
	pub fn add(&self, c:Color) -> Color {
		Color {r: self.r + c.r, g: self.g + c.g, b: self.b + c.b }
	}

	pub fn subtract(&self, c:Color) -> Color {
		Color {r: self.r - c.r, g: self.g - c.g, b: self.b - c.b }
	}

	pub fn scale(&self, s:f64) -> Color {
		Color {r: self.r * s, g: self.g * s, b: self.b * s }
	}

	pub fn multiply(&self, c:Color) -> Color {
		Color {r: self.r * c.r, g: self.g * c.g, b: self.b * c.b }
	}

	fn legalize(i:f64) -> int {
		if i > 1.0 {
			255
		}
		else {
			(i * 255.0) as int
		}
	}

	pub fn to_color(&self) -> int {
		let r = Color::legalize(self.r);
		let g = Color::legalize(self.g);
		let b = Color::legalize(self.b);
		 (255 << 24) + (r << 16) + (g<<8)+b
	}
}