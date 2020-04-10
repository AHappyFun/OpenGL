#version 330 core
layout (triangles) in;
layout (line_strip, max_vertices = 2) out;

in VERT_OUT {
	vec3 Normal;
}gs_in[];

vec3 GetNormal()
{
    vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
    vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
    return normalize(cross(a, b));
}

const float MAGNITUDE = 0.4;
void GenerateLine(int index)
{
    gl_Position = gl_in[index].gl_Position;
    EmitVertex();
    gl_Position = gl_in[index].gl_Position + vec4(GetNormal(), 0.0) * MAGNITUDE;
    EmitVertex();
    EndPrimitive();
}

vec3 GetInternalPos()
{
	float a = distance(gl_in[0].gl_Position, gl_in[1].gl_Position);
	float b = distance(gl_in[0].gl_Position, gl_in[2].gl_Position);
	float c = distance(gl_in[1].gl_Position, gl_in[2].gl_Position);
	float x = (a * gl_in[0].gl_Position.x + b * gl_in[1].gl_Position.x + c * gl_in[2].gl_Position.x) / (a+b+c);
	float y = (a * gl_in[0].gl_Position.y + b * gl_in[1].gl_Position.y + c * gl_in[2].gl_Position.y) / (a+b+c);
	float z = (a * gl_in[0].gl_Position.z + b * gl_in[1].gl_Position.z + c * gl_in[2].gl_Position.z) / (a+b+c);
	return vec3(x,y,z);
}

void main() {    
	GenerateLine(0); 
}