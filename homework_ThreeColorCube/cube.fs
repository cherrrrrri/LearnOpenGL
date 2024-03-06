#version 330 core
out vec4 FragColor;

uniform vec3 objColor;
uniform vec3 RedLightColor;
uniform vec3 RedLightPos;
uniform vec3 BlueLightColor;
uniform vec3 BlueLightPos;
uniform vec3 GreenLightColor;
uniform vec3 GreenLightPos;

uniform vec3 viewPos;

in vec3 Normal;
in vec3 FragPos;

void main()
{
    // 环境光照
    float ambientStrength = 0.5;
    vec3 ambient = ambientStrength * (RedLightColor + BlueLightColor + GreenLightColor);

    // 漫反射光照
    vec3 norm = normalize(Normal); // 标准化
    vec3 RedLightDir = normalize(RedLightPos -  FragPos); // 光照方向的反方向：光照位置指向光源方向，此时点乘结果才会为正
    float RedDiff = max(dot(norm,RedLightDir), 0.0);

    vec3 BlueLightDir = normalize(BlueLightPos -  FragPos); 
    float BlueDiff = max(dot(norm,BlueLightDir), 0.0);
    
    vec3 GreenLightDir = normalize(GreenLightPos -  FragPos); 
    float GreenDiff = max(dot(norm, GreenLightDir), 0.0);
    
    vec3 diffuse = RedDiff * RedLightColor + BlueDiff * BlueLightColor + GreenDiff * GreenLightColor;

    // 镜面光照
    float specularStrength = 0.8; // 镜面强度
    vec3 viewDir = normalize(viewPos - FragPos);

    vec3 GreenReflectDir = reflect(-GreenLightDir, norm);
    float GreenSpec = pow(max(dot(viewDir, GreenReflectDir), 0.0), 32); // 计算绿色镜面分量

    vec3 RedReflectDir = reflect(-RedLightDir, norm);
    float RedSpec = pow(max(dot(viewDir, RedReflectDir), 0.0), 32); // 计算蓝色镜面分量

    vec3 BlueReflectDir = reflect(-BlueLightDir, norm);
    float BlueSpec = pow(max(dot(viewDir, BlueReflectDir), 0.0), 32); // 计算红色镜面分量

    vec3 specular = specularStrength * (GreenSpec * GreenLightColor + RedSpec * RedLightColor + BlueSpec * BlueLightColor);


    vec3 result = (ambient + diffuse + specular) * objColor;
    FragColor = vec4(result, 1.0); 

}