camera {
	pos(0,0,-5)
	rotation(0,0,0)
}

object {
	type(sphere)
	pos(0, -15, 45)
	radius(12)
	color(125, 137, 228)
	transparent(2, 70)
}

object {
	type(plane)
	pos(0, -35, 100)
	rotation(0, 0)
	color(249, 209, 74)
	rlim_x(-17, 107)
	rlim_y(-27, 20)
	transparent(1.14, 70)
}

object {
	type(cone)
	pos(0, -35, 130)
	rotation(90, 0)
	angle(18)
	color(209, 109, 154)
	plim_y(-47, 40)
	transparent(1.14, 20)
}

object {
	type(plane)
	pos(0, -35, 280)
	rotation(0, 0)
	color(199, 199, 194)
}

light {
	pos(0,15,-5)
}
