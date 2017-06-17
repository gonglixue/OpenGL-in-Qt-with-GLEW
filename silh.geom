#version 400 core
#extension GL_EXT_gpu_shader4: enable
#extension GL_EXT_geometry_shader4: enable
layout(triangles_adjacency) in;
//layout(triangles) in;
layout(line_strip, max_vertices = 6) out;
uniform mat4 u_projection_mat;
uniform mat4 u_model_geo;
uniform mat4 u_view_geo;

void test()
{
	vec4 v0 = vec4(-1, -1, 0, 1);
	vec4 v1 = vec4(1, 1, 0, 1);
	gl_Position = u_projection_mat *  u_view_geo * u_model_geo * v0;
	EmitVertex();
	gl_Position = u_projection_mat * u_view_geo * u_model_geo * v1;
	EmitVertex();
	EndPrimitive();
}

void main()
{
//test();

    vec3 v0 = gl_in[0].gl_Position.xyz;
    vec3 v1 = gl_in[1].gl_Position.xyz;
    vec3 v2 = gl_in[2].gl_Position.xyz;
    vec3 v3 = gl_in[3].gl_Position.xyz;
    vec3 v4 = gl_in[4].gl_Position.xyz;
    vec3 v5 = gl_in[5].gl_Position.xyz;

    vec3 N042 = cross(v4-v0, v2-v0);
    vec3 N021 = cross(v2-v0, v1-v0);
    vec3 N243 = cross(v4-v2, v3-v2);
    vec3 N405 = cross(v0-v4, v5-v4);

    //if( dot(N042, N021) < 0 )
        //N021 = vec3(0,0,0) - N021;
    //if( dot(N042, N243) < 0 )
        //N243 = vec3(0,0,0) - N243;
    //if( dot(N042, N405) < 0 )
        //N405 = vec3(0,0,0) - N405;
		
	

    if( N042.z * N021.z < 0 )
    {
        gl_Position = u_projection_mat * vec4(v0, 1.0);
        EmitVertex();
        gl_Position = u_projection_mat * vec4(v2, 1.0);
        EmitVertex();
        EndPrimitive();
    }
    if( N042.z * N243.z < 0 )
    {
        gl_Position = u_projection_mat * vec4(v2, 1.0);
        EmitVertex();
        gl_Position = u_projection_mat * vec4(v4, 1.0);
        EmitVertex();
        EndPrimitive();
    }
    if( N042.z * N405.z < 0 )
    {
        gl_Position = u_projection_mat * vec4(v4, 1.0);
        EmitVertex();
        gl_Position = u_projection_mat * vec4(v0, 1.0);
        EmitVertex();
        EndPrimitive();
    }
	
}
