#version 400
uniform mat4 new_position;
layout(location=0) in vec4 vp;
out float z_value;

void main () {
	
	//-------------------------------------------------------------------------//
	// Instead of passing the `vp` variable unaffected as below, 
	// apply the model, view and projection transform to vertex
	// positions here. Forward the position to the fragment shader using
	// an appropriate `out` variable.
	// -------------------------------------------------------------------------//

	gl_Position = new_position * vp;
	z_value = gl_Position.z;

};
  
