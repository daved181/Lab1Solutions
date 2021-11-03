#version 400

layout(location=0) in vec4 vp;
uniform mat4 mvp;
out float z_value;

void main () {
  
  gl_Position = mvp*vp;
  z_value = gl_Position.z;
};
  