#version 330 core
out vec4 FragColor;

struct Material{

    sampler2D diffuse; // 漫反射贴图，环境光颜色几乎等于漫反射颜色，合在一起
	sampler2D specular; // 镜面高光颜色，可以特定
	float shininess; // 反光度：影响镜面高光的散射（半径）
}; // 不要忘记“；”

struct Light{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

};

// 下面的变量都放到结构里了
// uniform vec3 lightPos;
// uniform vec3 ambientColor;
// uniform vec3 lightColor;
// uniform vec3 objColor;

uniform Material material;
uniform Light light;

uniform vec3 viewPos; 

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;  // 纹理坐标

void main()
{
    // 环境光照
    //vec3 ambient = lightColor * material.ambient * vec3(0.1); // 光照颜色* 物体颜色 * 0.1(要不然环境光太强了)
    vec3 ambient =  light.ambient * texture(material.diffuse, TexCoords).rgb;

    // 漫反射光照
    vec3 norm = normalize(Normal); // 标准化
    vec3 lightDir = normalize(light.position -  FragPos); // 光照方向的反方向：光照位置指向光源方向，此时点乘结果才会为正
    float diff = max(dot(norm,lightDir), 0.0); // 这里的diff不能为负数，要在0-1之间，要不然会影响其他光照的表现
    // vec3 diffuse = diff* lightColor;
    // vec3 diffuse = diff * material.diffuse * lightColor; // 这里改了之后已经加上物体颜色了，下面就不需要再乘物体颜色了
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb; 

    // 镜面光照
    // float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess); // 这里使用了shininess���是镜面高光的散射半径
    //  vec3 specular = light.specular * (spec * material.specular);   
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords).rgb);

    vec3 result = ambient + diffuse + specular; 
    FragColor = vec4(result, 1.0); 
}