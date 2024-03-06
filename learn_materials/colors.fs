#version 330 core
out vec4 FragColor;

struct Material{
	vec3 ambient; // 表面反射什么颜色 = 物体颜色
	vec3 diffuse; // = 物体颜色
	vec3 specular; // 镜面高光颜色，可以特定
	float shininess; // 反光度：影响镜面高光的散射（半径）
}; // 不要忘记“；”

uniform Material material;

uniform vec3 objColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos; 
uniform vec3 ambientColor;

in vec3 Normal;
in vec3 FragPos;

void main()
{
    // 环境光照
    // float ambientStrength = 0.1;
    // vec3 ambient = ambientStrength * lightColor;
    vec3 ambient = lightColor * material.ambient * vec3(0.1); // 光照颜色* 物体颜色 * 0.1(要不然环境光太强了)

    // 漫反射光照
    vec3 norm = normalize(Normal); // 标准化
    vec3 lightDir = normalize(lightPos -  FragPos); // 光照方向的反方向：光照位置指向光源方向，此时点乘结果才会为正
    float diff = max(dot(norm,lightDir), 0.0); // 这里的diff不能为负数，要在0-1之间，要不然会影响其他光照的表现
    // vec3 diffuse = diff* lightColor;
    vec3 diffuse = diff * material.diffuse * lightColor; // 这里改了之后已经加上物体颜色了，下面就不需要再乘物体颜色了

    // 镜面光照
    // float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess); // 这里使用了shininess���是镜面高光的散射半径
    vec3 specular = material.specular * spec * lightColor;  


    vec3 result = ambient + diffuse + specular; // 
    FragColor = vec4(result, 1.0); 
}