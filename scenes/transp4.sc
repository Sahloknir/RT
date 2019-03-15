camera {
	pos(0,0,-100)
	rotation(10,0,0)
}

object {
	type(plane)
	pos(0, -20, 40)
	rotation(90, 0)
	color(210, 210, 210)
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
	pos(0, 0, 0)
}
