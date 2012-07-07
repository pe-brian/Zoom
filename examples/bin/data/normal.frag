uniform sampler2D diffuse;
uniform sampler2D normal;
uniform sampler2D heightmap;
uniform sampler2D heightmap_screen;
uniform sampler2D screen;
uniform sampler2D shadow_map;

uniform float NBR_LIGHTS;
uniform vec4 ambient_light;
uniform vec2 screen_ratio;
uniform vec2 shadow_ratio;
uniform vec2 image_ratio;

uniform float height_factor;
uniform float flipx;

varying vec3 vertex;

float GetShadow(vec2 decal, vec3 light_direction)
{
	float h = (vertex.z+texture2D(heightmap, gl_TexCoord[0].xy + decal*image_ratio).b * height_factor);
	vec2 pos_screen = gl_FragCoord.xy + decal;
	pos_screen.x -= h*light_direction.x/light_direction.z;
	pos_screen.y += h*light_direction.y/4.0/light_direction.z;
	pos_screen.y -= h*sqrt(3.0)/2.0;
	float shadow_color = texture2D(shadow_map, pos_screen*shadow_ratio + vec2(0.5,0.5) - shadow_ratio/screen_ratio/2.0).b;
				  
	return 1.0 - min(1.0,max(0.0, 1.0 -(h/500.0 - shadow_color+0.025)/0.025));
}

void main()
{	
	float alpha_old = 0.0;
	
	vec3 v = vertex;
	
	if( texture2D(heightmap, gl_TexCoord[0].xy)[3] > 0.2)
		v.z += texture2D(heightmap, gl_TexCoord[0].xy)[2] * height_factor  / texture2D(heightmap, gl_TexCoord[0].xy)[3];
	else
		v.z += texture2D(heightmap, gl_TexCoord[0].xy)[2] * height_factor;
	
	v.y += sqrt(3.0) * v.z;
	
	if(v.z/500.0 < texture2D(heightmap_screen, vec2(gl_FragCoord.xy*screen_ratio)).b)
		alpha_old = texture2D(heightmap_screen, vec2(gl_FragCoord.xy*screen_ratio)).r;
	
	if(alpha_old < 1.0)
	{
		vec3 direction = -1.0 + 2.0 * texture2D(normal, gl_TexCoord[0].xy).rgb;
		direction.x *= flipx;
		
		direction.yz = vec2(direction.y*0.5 + direction.z*0.5*sqrt(3.0),
							direction.z*0.5 - direction.y*0.5*sqrt(3.0));
		
		vec4 color = gl_Color * texture2D(diffuse, gl_TexCoord[0].xy) * ambient_light;
		
		int i;
		for(i = 0 ; i < int(NBR_LIGHTS) ; i = i+1)
		{
			float lighting = 0.0;
			
			if(gl_LightSource[i].position.w == 0.0)
			{		
				vec3 light_direction = -gl_LightSource[i].position.xyz;
				light_direction.y *= 2.0;
				lighting = max(0.0, dot(direction,normalize(light_direction)));
				
				float f = 1.0;
				
				lighting *= (GetShadow(vec2( 0, 0)*f,light_direction) * 4.0 +
							 GetShadow(vec2( 1, 0)*f,light_direction) * 2.0 +
							 GetShadow(vec2(-1, 0)*f,light_direction) * 2.0 +
							 GetShadow(vec2( 0, 1)*f,light_direction) * 2.0 +
							 GetShadow(vec2( 0,-1)*f,light_direction) * 2.0 +
							 GetShadow(vec2( 1, 1)*f,light_direction) * 1.0 +
							 GetShadow(vec2(-1, 1)*f,light_direction) * 1.0 +
							 GetShadow(vec2(-1,-1)*f,light_direction) * 1.0 +
							 GetShadow(vec2( 1,-1)*f,light_direction) * 1.0 )/16.0;
			}
			else
			{
				vec3 light_direction = gl_LightSource[i].position.xyz - v;
				float dist = length(light_direction);
				float attenuation = 1.0/( gl_LightSource[i].constantAttenuation +
										  dist*gl_LightSource[i].linearAttenuation +
										  dist*dist*gl_LightSource[i].quadraticAttenuation);
				
				
				lighting = max(0.0, dot(direction,normalize(light_direction))) * attenuation;
			}
			
			lighting *= gl_LightSource[i].diffuse.a;
			
			color.rgb +=  gl_Color.rgb * texture2D(diffuse, gl_TexCoord[0].xy).rgb * gl_LightSource[i].diffuse.rgb  * lighting;
		}
		
		float a = gl_Color.a * texture2D(diffuse, gl_TexCoord[0].xy).a;
			
		if(alpha_old != 0.0)
		{
			color *= a * min(1.0,max(0.0,1.0 - alpha_old));
			color += texture2D(screen, vec2(gl_FragCoord.xy*screen_ratio)) * alpha_old;
			color /= alpha_old + a * min(1.0,max(0.0,1.0 - alpha_old));
			color.a = alpha_old + a * min(1.0,max(0.0,1.0 - alpha_old));
		}
		else
			color.a = gl_Color.a * texture2D(diffuse, gl_TexCoord[0].xy).a;
		
		gl_FragColor = color;
	}
	else
		gl_FragColor = vec4(0.0,0.0,0.0,0.0);
}
