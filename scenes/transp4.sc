camera {
	pos(0,0,-25)
	rotation(20,0,0)
}

object {
	type(plane)
	rotation(90, 0)
	pos(0, -25, 50)
	transparent(1.33, 90)
}

object {
	type(cylinder)
	pos(0, 0, 50)
	rotation(90, -45)
	color(200, 200, 255)
	radius(15)
}

light {
	pos(20, 10, -100)
}
