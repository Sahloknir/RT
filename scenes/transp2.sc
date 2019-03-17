camera {
	pos(0,0,-5)
	rotation(0,0,0)
}

object {
	type(sphere)
	pos(0, -15, 55)
	radius(12)
	color(125, 137, 228)
	transparent(1, 70)
}

object {
	type(plane)
	pos(0, -15, 76)
	rotation(0, 0, 0)
	color(225, 137, 128)
	rlim_x(-7, 7)
	rlim_y(-17, 17)
	transparent(1, 80)
}

object {
	type(plane)
	pos(0, -15, 70)
	rotation(0, 0, 0)
	color(125, 217, 128)
	rlim_x(-27, 27)
	rlim_y(-7, 7)
	transparent(1, 80)
}

object {
	type(plane)
	pos(15, -15, 102)
	rotation(0, 0, 0)
	color(249, 209, 74)
	rlim_x(-17, 107)
	rlim_y(-27, 27)
}

light {
	pos(0,0,-5)
}

light {
	pos(0,39,90)
}
