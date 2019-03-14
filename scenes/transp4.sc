camera {
	pos(0,0,-60)
	rotation(10,0,0)
}

object {
	type(plane)
	rotation(90, 0)
	pos(0, -25, 50)
	color(255, 255, 255)
	transparent(1.33, 40)
}

object {
	type(cylinder)
	pos(0, 0, 50)
	rotation(90, -10)
	color(200, 200, 255)
	radius(15)
}

light {
	pos(20, 10, -100)
}
