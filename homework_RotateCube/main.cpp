#include <GL/freeglut.h>
#include <math.h>

GLfloat angle = 0.0;  // 旋转角度
GLfloat light0Pos[] = {-1.0, 1.0, 1.0, 1.0}; // 光源0坐标
GLfloat light1Pos[] = {1.0, 1.0, 1.0, 1.0}; // 光源1坐标
GLfloat light2Pos[] = {1.0, -1.0, 1.0, 1.0}; // 光源2坐标
GLfloat Va[]={0.4, 0.4, 0.4, 1.0};           //光源环境光强度数组  
GLfloat Vd[]={0.6, 0.6, 0.6, 1.0};           //光源散射光强度数组  
GLfloat Vs[]={0.6, 0.6, 0.6, 1.0};           //光源镜面反射光强度数组  

void init() {
    glEnable(GL_DEPTH_TEST); // 启用深度测试

    //0号光源
    glLightfv(GL_LIGHT0, GL_POSITION, light0Pos); // 光源0位置
    glLightfv(GL_LIGHT0,GL_AMBIENT,Va); //环境光属性  
    glLightfv(GL_LIGHT0,GL_DIFFUSE,Vd); //散射光属性  
    glLightfv(GL_LIGHT0,GL_SPECULAR,Vs);    //镜面反射光属性

    //1号光源
    glLightfv(GL_LIGHT1, GL_POSITION, light1Pos); // 光源1位置
    glLightfv(GL_LIGHT1,GL_AMBIENT,Va); //环境光属性  
    glLightfv(GL_LIGHT1,GL_DIFFUSE,Vd); //散射光属性  
    glLightfv(GL_LIGHT1,GL_SPECULAR,Vs);    //镜面反射光属性

    //1号光源
    glLightfv(GL_LIGHT2, GL_POSITION, light2Pos); // 位置
    glLightfv(GL_LIGHT2,GL_AMBIENT,Va); //环境光属性  
    glLightfv(GL_LIGHT2,GL_DIFFUSE,Vd); //散射光属性  
    glLightfv(GL_LIGHT2,GL_SPECULAR,Vs);    //镜面反射光属性

    glEnable(GL_LIGHT0);     // 启用光源0
    glEnable(GL_LIGHT1);    // 启用光源1
    glEnable(GL_LIGHT2);    // 启用光源2
    glEnable(GL_LIGHTING);   // 启用光照
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// 擦除背景色和深度缓存

    glLoadIdentity(); //重置模型的矩阵视图:将用户坐标系原点移到中心

    glTranslatef(0.0,0.0,-3.0); //将场景平移至z轴深度为-3.0的位置-摄像头往前移了3

    glRotatef(angle, 1.0, 1.0, 1.0); // 绕 (1, 1, 1) 轴旋转angle
    glRotatef(angle, 1.0, 0.0, 0.0); // 绕 x 轴旋转angle
    glRotatef(angle, 0.0, 1.0, 0.0); // 绕 y 轴旋转angle
    glRotatef(angle, 0.0, 0.0, 1.0); // 绕 z 轴旋转angle

    glutSolidCube(1.0);
    
	glutSwapBuffers();//交互前后缓冲区
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h); //视口大小:左下角是（0，0），宽，高

	glMatrixMode(GL_PROJECTION);  // 投影矩阵模式

	glLoadIdentity();  // 重置矩阵视图

	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0); // 视场角度，宽高比，近剪裁面，远剪裁面

	glMatrixMode(GL_MODELVIEW); // 矩阵模式切回视图矩阵模式
}


void timer(int)
{
    glutPostRedisplay(); // 请求重新绘制场景，在刷新时调用

	glutTimerFunc(1000/60, timer, 0);

	angle += 0.8; //每次angle增加0.8度

	if(angle > 360.0)
		angle = angle-360.0; // angle是否超出360度
}

int main(int argc, char** argv) {
    //初始化窗口
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);//双缓冲：防止绘制时出现闪烁
    glutInitWindowSize(800, 600);
    glutCreateWindow("Rotating Cube");

    // 当需要重新绘制窗口内容时，应该调用名为 display 的函数
    glutDisplayFunc(display);

    // 检测窗口大小改变
    glutReshapeFunc(reshape); 

    // 定时器&控制动画
    glutTimerFunc(0,timer,0); 
    
    // 光照初始化
    init();

    //调用已注册的回调函数
    glutMainLoop();  
    return 0;
}
