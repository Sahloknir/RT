camera {
	pos(0,150,-100)
	rotation(60,0,0)
}

object {
	type(plane)
	pos(-50,0,150)
	rotation(0,-45)
	color(125,149,238)
	rlim_x(-50, 50)
	rlim_y(-50, 50)
}

object {
	type(plane)
	pos(-50,0,50)
	rotation(0,-45)
	color(149,125,238)
	rlim_x(-50, 50)
	rlim_y(-50, 50)
}

object {
	type(plane)
	pos(50,0,150)
	rotation(0,90)
	color(125,238,149)
	rlim_x(-50, 50)
	rlim_y(-50, 50)
}

object {
	type(plane)
	pos(50,0,90)
	rotation(0,45)
	color(238,149,125)
	rlim_x(-50, 50)
	rlim_y(-50, 50)
}

light {
	pos(0,100,0)
}

