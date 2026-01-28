varying vec4 cameraPos;
varying vec4 vertexPos;
varying mat4 texgen;

uniform sampler3D volume;
int samples;

void main(void)
{   
  vec3 position  = (vertexPos * texgen).xyz;
  vec3 camera    = (cameraPos * texgen).xyz;
  vec3 direction = normalize(position - camera);
  vec4 dst       = vec4(0.0);
  samples = 512;
  
  float stepWidth = (1.0 / (float)samples);	
  vec3 step = direction * stepWidth;  
  
  for(int i = 0; i  < samples; i++)
  {
	float intensity = texture(volume, position).r;
	vec4 src = vec4(intensity);

    dst = (1.0 - dst.w) * src + dst;
	
	//if(dst.w > 0.95)
	//	break;
    position += step;

    vec3 tmp1 = sign(position - vec3(0.0));
    vec3 tmp2 = sign(vec3(1.0) - position);
	
    float inside = dot(tmp1, tmp2);
    if(inside < 3.0)
    { break; }
  }
  // 
  gl_FragData[0] = dst;
}