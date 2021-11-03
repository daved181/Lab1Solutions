#version 400
out vec3 frag_colour;
in float z_value;

void main () {

	// Set color proportional to the z position here, instead of a constant. 
	frag_colour = -z_value*vec3(0.5);
}
